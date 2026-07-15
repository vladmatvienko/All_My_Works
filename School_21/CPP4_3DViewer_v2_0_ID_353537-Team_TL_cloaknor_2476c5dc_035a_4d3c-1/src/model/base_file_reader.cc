#include "model/base_file_reader.h"

namespace s21 {

FileReader::FileReader(const BaseFileReader& reader) : reader_(reader) {}

Scene FileReader::ReadScene(const std::string& path) const {
  return reader_.ReadScene(path);
}

}  // namespace s21
