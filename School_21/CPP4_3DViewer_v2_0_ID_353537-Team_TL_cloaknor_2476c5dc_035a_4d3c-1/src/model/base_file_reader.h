#ifndef SRC_MODEL_BASE_FILE_READER_H_
#define SRC_MODEL_BASE_FILE_READER_H_

#include <string>

#include "model/scene.h"

namespace s21 {

class BaseFileReader {
 public:
  virtual ~BaseFileReader() = default;
  virtual Scene ReadScene(const std::string& path) const = 0;
};

class FileReader final {
 public:
  explicit FileReader(const BaseFileReader& reader);
  Scene ReadScene(const std::string& path) const;

 private:
  const BaseFileReader& reader_;
};

}  // namespace s21

#endif  // SRC_MODEL_BASE_FILE_READER_H_
