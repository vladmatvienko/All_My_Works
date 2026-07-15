#ifndef SRC_MODEL_OBJ_FILE_READER_H_
#define SRC_MODEL_OBJ_FILE_READER_H_

#include <string>
#include <vector>

#include "model/base_file_reader.h"

namespace s21 {

class ObjFileReader final : public BaseFileReader {
 public:
  Scene ReadScene(const std::string& path) const override;

 private:
  static bool IsVertexLine(const std::string& line);
  static bool IsFaceLine(const std::string& line);
  static Point3D ParseVertex(const std::string& line);
  static std::vector<std::size_t> ParseFace(const std::string& line,
                                            std::size_t vertices_count);
  static std::size_t ParseVertexIndex(const std::string& token,
                                      std::size_t vertices_count);
};

}  // namespace s21

#endif  // SRC_MODEL_OBJ_FILE_READER_H_
