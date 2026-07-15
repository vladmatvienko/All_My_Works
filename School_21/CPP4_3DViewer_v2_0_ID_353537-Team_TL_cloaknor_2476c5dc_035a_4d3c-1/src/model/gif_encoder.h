#ifndef SRC_MODEL_GIF_ENCODER_H_
#define SRC_MODEL_GIF_ENCODER_H_

#include <cstdint>
#include <string>
#include <vector>

namespace s21 {

struct GifFrame {
  int width = 0;
  int height = 0;
  std::vector<std::uint8_t> rgba;
};

class GifEncoder {
 public:
  static bool Save(const std::string& path, const std::vector<GifFrame>& frames,
                   int delay_centiseconds);
};

}  // namespace s21

#endif  // SRC_MODEL_GIF_ENCODER_H_
