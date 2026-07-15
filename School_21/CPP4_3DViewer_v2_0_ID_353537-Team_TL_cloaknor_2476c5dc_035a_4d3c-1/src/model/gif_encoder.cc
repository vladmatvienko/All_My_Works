#include "model/gif_encoder.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <unordered_map>
#include <vector>

namespace s21 {
namespace {

constexpr int kGifDelayCentiseconds = 10;
constexpr int kMaxLzwBits = 12;

struct PaletteColor {
  std::uint8_t r = 0;
  std::uint8_t g = 0;
  std::uint8_t b = 0;
};

struct Palette {
  std::array<PaletteColor, 256> colors{};
  int size = 256;
};

int FindNearestColor(const Palette& palette, int palette_size, std::uint8_t r,
                     std::uint8_t g, std::uint8_t b) {
  int best_index = 0;
  int best_distance = 1 << 30;
  for (int i = 0; i < palette_size; ++i) {
    const int dr = static_cast<int>(r) - static_cast<int>(palette.colors[i].r);
    const int dg = static_cast<int>(g) - static_cast<int>(palette.colors[i].g);
    const int db = static_cast<int>(b) - static_cast<int>(palette.colors[i].b);
    const int distance = dr * dr + dg * dg + db * db;
    if (distance < best_distance) {
      best_distance = distance;
      best_index = i;
    }
  }
  return best_index;
}

Palette BuildPalette(const std::vector<GifFrame>& frames) {
  Palette palette{};
  for (int i = 0; i < 256; ++i) {
    palette.colors[i].r = static_cast<std::uint8_t>((i & 7) * 36);
    palette.colors[i].g = static_cast<std::uint8_t>(((i >> 3) & 7) * 36);
    palette.colors[i].b = static_cast<std::uint8_t>(((i >> 6) & 3) * 85);
  }
  palette.size = 256;
  (void)frames;
  return palette;
}

std::vector<std::uint8_t> QuantizeFrame(const GifFrame& frame,
                                        const Palette& palette,
                                        int palette_size) {
  std::vector<std::uint8_t> indices(frame.width * frame.height);
  for (int y = 0; y < frame.height; ++y) {
    for (int x = 0; x < frame.width; ++x) {
      const std::size_t offset =
          static_cast<std::size_t>(y * frame.width + x) * 4U;
      indices[static_cast<std::size_t>(y * frame.width + x)] =
          static_cast<std::uint8_t>(
              FindNearestColor(palette, palette_size, frame.rgba[offset],
                               frame.rgba[offset + 1], frame.rgba[offset + 2]));
    }
  }
  return indices;
}

void WriteByte(std::vector<std::uint8_t>& buffer, std::uint8_t value) {
  buffer.push_back(value);
}

void WriteWord(std::vector<std::uint8_t>& buffer, std::uint16_t value) {
  buffer.push_back(static_cast<std::uint8_t>(value & 0xFFU));
  buffer.push_back(static_cast<std::uint8_t>((value >> 8) & 0xFFU));
}

void WriteSubBlocks(std::vector<std::uint8_t>& buffer,
                    const std::vector<std::uint8_t>& data) {
  std::size_t offset = 0;
  while (offset < data.size()) {
    const std::size_t chunk = std::min<std::size_t>(255U, data.size() - offset);
    buffer.push_back(static_cast<std::uint8_t>(chunk));
    buffer.insert(buffer.end(), data.begin() + static_cast<long>(offset),
                  data.begin() + static_cast<long>(offset + chunk));
    offset += chunk;
  }
  buffer.push_back(0x00);
}

std::vector<std::uint8_t> LzwEncode(const std::vector<std::uint8_t>& pixels,
                                    int min_code_size) {
  const int clear_code = 1 << min_code_size;
  const int end_code = clear_code + 1;

  int code_size = min_code_size + 1;
  int next_code = end_code + 1;
  int max_code = 1 << code_size;

  std::unordered_map<std::string, int> dictionary;
  for (int i = 0; i < clear_code; ++i) {
    dictionary[std::string(1, static_cast<char>(i))] = i;
  }

  std::vector<std::uint8_t> packed;
  int bit_buffer = 0;
  int bit_count = 0;

  auto emit_code = [&](int code) {
    bit_buffer |= (code << bit_count);
    bit_count += code_size;
    while (bit_count >= 8) {
      packed.push_back(static_cast<std::uint8_t>(bit_buffer & 0xFF));
      bit_buffer >>= 8;
      bit_count -= 8;
    }
  };

  emit_code(clear_code);

  std::string sequence(1, static_cast<char>(pixels.front()));
  for (std::size_t i = 1; i < pixels.size(); ++i) {
    const std::string next_sequence = sequence + static_cast<char>(pixels[i]);
    if (dictionary.find(next_sequence) != dictionary.end()) {
      sequence = next_sequence;
      continue;
    }

    emit_code(dictionary.at(sequence));
    if (next_code < (1 << kMaxLzwBits)) {
      dictionary[next_sequence] = next_code++;
      if (next_code > max_code && code_size < kMaxLzwBits) {
        ++code_size;
        max_code = 1 << code_size;
      }
    } else {
      emit_code(clear_code);
      dictionary.clear();
      for (int j = 0; j < clear_code; ++j) {
        dictionary[std::string(1, static_cast<char>(j))] = j;
      }
      next_code = end_code + 1;
      code_size = min_code_size + 1;
      max_code = 1 << code_size;
    }
    sequence = std::string(1, static_cast<char>(pixels[i]));
  }
  emit_code(dictionary.at(sequence));
  emit_code(end_code);

  if (bit_count > 0) {
    packed.push_back(static_cast<std::uint8_t>(bit_buffer & 0xFF));
  }
  return packed;
}

void WriteHeader(std::vector<std::uint8_t>& buffer, int width, int height,
                 const Palette& palette, int palette_size) {
  buffer.insert(buffer.end(), {'G', 'I', 'F', '8', '9', 'a'});
  WriteWord(buffer, static_cast<std::uint16_t>(width));
  WriteWord(buffer, static_cast<std::uint16_t>(height));
  const std::uint8_t packed_fields =
      static_cast<std::uint8_t>(0x80 | ((palette_size - 1) << 0));
  WriteByte(buffer, packed_fields);
  WriteByte(buffer, 0x00);
  WriteByte(buffer, 0x00);
  for (int i = 0; i < palette_size; ++i) {
    WriteByte(buffer, palette.colors[i].r);
    WriteByte(buffer, palette.colors[i].g);
    WriteByte(buffer, palette.colors[i].b);
  }
}

void WriteFrame(std::vector<std::uint8_t>& buffer,
                const std::vector<std::uint8_t>& indices, int width, int height,
                int delay_centiseconds) {
  WriteByte(buffer, 0x21);
  WriteByte(buffer, 0xF9);
  WriteByte(buffer, 0x04);
  WriteByte(buffer, 0x00);
  WriteWord(buffer, static_cast<std::uint16_t>(delay_centiseconds));
  WriteByte(buffer, 0x00);
  WriteByte(buffer, 0x00);

  WriteByte(buffer, 0x2C);
  WriteWord(buffer, 0x0000);
  WriteWord(buffer, 0x0000);
  WriteWord(buffer, static_cast<std::uint16_t>(width));
  WriteWord(buffer, static_cast<std::uint16_t>(height));
  WriteByte(buffer, 0x00);

  const int min_code_size = 8;
  WriteByte(buffer, static_cast<std::uint8_t>(min_code_size));
  const std::vector<std::uint8_t> lzw_data = LzwEncode(indices, min_code_size);
  WriteSubBlocks(buffer, lzw_data);
}

}  // namespace

bool GifEncoder::Save(const std::string& path,
                      const std::vector<GifFrame>& frames,
                      int delay_centiseconds) {
  if (frames.empty() || frames.front().width <= 0 ||
      frames.front().height <= 0) {
    return false;
  }

  const int width = frames.front().width;
  const int height = frames.front().height;
  for (const GifFrame& frame : frames) {
    if (frame.width != width || frame.height != height ||
        static_cast<int>(frame.rgba.size()) != width * height * 4) {
      return false;
    }
  }

  const Palette palette = BuildPalette(frames);
  const int palette_size = palette.size;
  const int delay =
      delay_centiseconds > 0 ? delay_centiseconds : kGifDelayCentiseconds;

  std::vector<std::uint8_t> buffer;
  WriteHeader(buffer, width, height, palette, palette_size);
  for (const GifFrame& frame : frames) {
    const std::vector<std::uint8_t> indices =
        QuantizeFrame(frame, palette, palette_size);
    WriteFrame(buffer, indices, width, height, delay);
  }
  WriteByte(buffer, 0x3B);

  std::ofstream file(path, std::ios::binary);
  if (!file.is_open()) {
    return false;
  }
  file.write(reinterpret_cast<const char*>(buffer.data()),
             static_cast<std::streamsize>(buffer.size()));
  return static_cast<bool>(file);
}

}  // namespace s21
