#include "model/scene_loader.h"

#include "model/obj_file_reader.h"

namespace s21 {

Scene SceneLoader::LoadObjScene(const std::string& path) {
  ObjFileReader reader;
  return reader.ReadScene(path);
}

}  // namespace s21
