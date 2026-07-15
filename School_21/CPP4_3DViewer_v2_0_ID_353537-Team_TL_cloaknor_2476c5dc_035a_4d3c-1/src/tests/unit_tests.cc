#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "model/facade.h"
#include "model/gif_encoder.h"
#include "model/obj_file_reader.h"
#include "model/render_settings.h"
#include "model/scene_drawer_base.h"
#include "model/scene_loader.h"
#include "model/transform_matrix.h"
#include "s21_matrix_oop.h"

namespace {

class TestFailure final : public std::runtime_error {
 public:
  using std::runtime_error::runtime_error;
};

void ExpectTrue(bool condition, const std::string& message) {
  if (!condition) {
    throw TestFailure(message);
  }
}

void ExpectNear(double actual, double expected, const std::string& message) {
  if (std::fabs(actual - expected) > 1e-7) {
    throw TestFailure(message + ": actual=" + std::to_string(actual) +
                      ", expected=" + std::to_string(expected));
  }
}

std::filesystem::path WriteTempObj(const std::string& content) {
  const std::filesystem::path path =
      std::filesystem::temp_directory_path() / "s21_3dviewer_test.obj";
  std::ofstream file(path);
  file << content;
  return path;
}

class NullDrawer final : public s21::SceneDrawerBase {
 public:
  void DrawScene(const s21::Scene& scene, const s21::RenderSettings& settings,
                 int viewport_width, int viewport_height) override {
    was_called_ = !scene.Empty();
    last_width_ = viewport_width;
    last_height_ = viewport_height;
    last_projection_ = settings.projection();
  }

  bool was_called() const noexcept { return was_called_; }
  int last_width() const noexcept { return last_width_; }
  int last_height() const noexcept { return last_height_; }
  s21::ProjectionType last_projection() const noexcept {
    return last_projection_;
  }

 private:
  bool was_called_ = false;
  int last_width_ = 0;
  int last_height_ = 0;
  s21::ProjectionType last_projection_ = s21::ProjectionType::kParallel;
};

void TestObjReaderLoadsVerticesAndUniqueEdges() {
  const std::filesystem::path path = WriteTempObj(
      "v 0 0 0\n"
      "v 2 0 0\n"
      "v 2 2 0\n"
      "v 0 2 0\n"
      "f 1 2 3 4\n"
      "f 4 3 2 1\n");

  s21::ObjFileReader reader;
  const s21::Scene scene = reader.ReadScene(path.string());

  ExpectTrue(scene.VerticesCount() == 4, "OBJ reader must load 4 vertices");
  ExpectTrue(scene.EdgesCount() == 4, "OBJ reader must keep unique edges only");
  ExpectTrue(scene.filename() == path.filename().string(),
             "Scene must expose file name");
  std::filesystem::remove(path);
}

void TestReaderSupportsSlashAndNegativeIndexes() {
  const std::filesystem::path path = WriteTempObj(
      "v 0 0 0\n"
      "v 1 0 0\n"
      "v 0 1 0\n"
      "f -3/1/1 -2/2/2 -1/3/3\n");

  s21::ObjFileReader reader;
  const s21::Scene scene = reader.ReadScene(path.string());

  ExpectTrue(scene.VerticesCount() == 3,
             "OBJ reader must parse negative indexes");
  ExpectTrue(scene.EdgesCount() == 3,
             "OBJ reader must parse slash face tokens");
  std::filesystem::remove(path);
}

void TestReaderIgnoresNonGeometryLines() {
  const std::filesystem::path path = WriteTempObj(
      "# comment\n"
      "mtllib material.mtl\n"
      "v 0 0 0\n"
      "v 1 0 0\n"
      "v 0 1 0\n"
      "vn 0 0 1\n"
      "vt 0 0\n"
      "f 1/1/1 2/2/2 3/3/3\n");

  s21::ObjFileReader reader;
  const s21::Scene scene = reader.ReadScene(path.string());
  ExpectTrue(scene.VerticesCount() == 3,
             "OBJ reader must ignore comments and extra tokens");
  ExpectTrue(scene.EdgesCount() == 3, "Face must still produce edges");
  std::filesystem::remove(path);
}

void TestReaderRejectsEmptyFile() {
  const std::filesystem::path path = WriteTempObj("");
  s21::ObjFileReader reader;
  bool threw = false;
  try {
    reader.ReadScene(path.string());
  } catch (const std::exception&) {
    threw = true;
  }
  ExpectTrue(threw, "Empty OBJ must throw");
  std::filesystem::remove(path);
}

void TestReaderRejectsInvalidFaceIndex() {
  const std::filesystem::path path = WriteTempObj(
      "v 0 0 0\n"
      "v 1 0 0\n"
      "f 1 2 99\n");
  s21::ObjFileReader reader;
  bool threw = false;
  try {
    reader.ReadScene(path.string());
  } catch (const std::exception&) {
    threw = true;
  }
  ExpectTrue(threw, "Invalid face index must throw");
  std::filesystem::remove(path);
}

void TestSceneLoaderMatchesReader() {
  const std::filesystem::path path = WriteTempObj(
      "v 0 0 0\n"
      "v 1 0 0\n"
      "v 0 1 0\n"
      "f 1 2 3\n");
  const s21::Scene scene = s21::SceneLoader::LoadObjScene(path.string());
  ExpectTrue(scene.VerticesCount() == 3, "SceneLoader must load vertices");
  ExpectTrue(scene.EdgesCount() == 3, "SceneLoader must load edges");
  std::filesystem::remove(path);
}

void TestMoveScaleRotationMatrices() {
  const s21::Point3D source{1.0, 2.0, 3.0};

  s21::Point3D moved =
      s21::TransformMatrixBuilder::CreateMoveMatrix(4.0, -1.0, 2.0)
          .TransformPoint(source);
  ExpectNear(moved.x, 5.0, "Move X failed");
  ExpectNear(moved.y, 1.0, "Move Y failed");
  ExpectNear(moved.z, 5.0, "Move Z failed");

  s21::Point3D scaled =
      s21::TransformMatrixBuilder::CreateScaleMatrix(2.0).TransformPoint(
          source);
  ExpectNear(scaled.x, 2.0, "Scale X failed");
  ExpectNear(scaled.y, 4.0, "Scale Y failed");
  ExpectNear(scaled.z, 6.0, "Scale Z failed");

  s21::Point3D rotated_z =
      s21::TransformMatrixBuilder::CreateRotationMatrix(0.0, 0.0, 90.0)
          .TransformPoint({1.0, 0.0, 0.0});
  ExpectNear(rotated_z.x, 0.0, "Rotation Z X failed");
  ExpectNear(rotated_z.y, 1.0, "Rotation Z Y failed");
  ExpectNear(rotated_z.z, 0.0, "Rotation Z Z failed");

  s21::Point3D rotated_x =
      s21::TransformMatrixBuilder::CreateRotationMatrix(90.0, 0.0, 0.0)
          .TransformPoint({0.0, 1.0, 0.0});
  ExpectNear(rotated_x.x, 0.0, "Rotation X X failed");
  ExpectNear(rotated_x.y, 0.0, "Rotation X Y failed");
  ExpectNear(rotated_x.z, 1.0, "Rotation X Z failed");

  s21::Point3D rotated_y =
      s21::TransformMatrixBuilder::CreateRotationMatrix(0.0, 90.0, 0.0)
          .TransformPoint({1.0, 0.0, 0.0});
  ExpectNear(rotated_y.x, 0.0, "Rotation Y X failed");
  ExpectNear(rotated_y.z, -1.0, "Rotation Y Z failed");
}

void TestMatrixMultiplicationUsedByTransforms() {
  s21::S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;
  s21::S21Matrix vector(2, 1);
  vector(0, 0) = 5.0;
  vector(1, 0) = 6.0;
  const s21::S21Matrix result = matrix * vector;
  ExpectNear(result(0, 0), 17.0, "Matrix multiplication failed");
  ExpectNear(result(1, 0), 39.0, "Matrix multiplication failed");
}

void TestScaleZeroThrows() {
  bool threw = false;
  try {
    s21::TransformMatrixBuilder::CreateScaleMatrix(0.0);
  } catch (const std::exception&) {
    threw = true;
  }
  ExpectTrue(threw, "Zero scale must throw");
}

void TestSceneTransformUpdatesVertices() {
  s21::Figure figure({{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}, {{0, 1}});
  s21::Scene scene(std::move(figure), "test.obj");
  scene.Transform(s21::TransformMatrixBuilder::CreateMoveMatrix(2.0, 0.0, 0.0));
  ExpectNear(scene.figure().vertices()[1].x, 3.0, "Scene transform failed");
}

void TestFigureNormalizeCentersModel() {
  s21::Figure figure({{-2.0, 0.0, 0.0}, {2.0, 0.0, 0.0}}, {{0, 1}});
  figure.Normalize();
  ExpectNear(figure.vertices()[0].x, -1.0, "Normalize min X failed");
  ExpectNear(figure.vertices()[1].x, 1.0, "Normalize max X failed");
}

void TestRenderSettingsClampValues() {
  s21::RenderSettings settings;
  settings.SetEdgeThickness(100.0F);
  settings.SetVertexSize(100.0F);
  settings.SetEdgeThickness(0.01F);
  settings.SetVertexSize(0.01F);
  ExpectTrue(settings.edge_thickness() >= 0.1F, "Edge thickness min clamp");
  ExpectTrue(settings.vertex_size() >= 1.0F, "Vertex size min clamp");
  ExpectTrue(settings.edge_thickness() <= 20.0F, "Edge thickness max clamp");
  ExpectTrue(settings.vertex_size() <= 20.0F, "Vertex size max clamp");
}

void TestFacadeReturnsErrorsWithoutThrowing() {
  auto drawer = std::make_unique<NullDrawer>();
  s21::Facade facade(std::move(drawer));

  const s21::FacadeOperationResult move_result =
      facade.MoveScene(1.0, 0.0, 0.0);
  ExpectTrue(!move_result.IsSuccess(),
             "Facade must reject transforms without model");

  const s21::FacadeOperationResult load_result =
      facade.LoadScene("missing.obj");
  ExpectTrue(!load_result.IsSuccess(), "Facade must report load errors");
}

void TestFacadeLoadMoveRotateScale() {
  const std::filesystem::path path = WriteTempObj(
      "v 0 0 0\n"
      "v 1 0 0\n"
      "v 0 1 0\n"
      "f 1 2 3\n");

  auto drawer = std::make_unique<NullDrawer>();
  s21::Facade facade(std::move(drawer));

  ExpectTrue(facade.LoadScene(path.string()).IsSuccess(),
             "Facade must load valid OBJ");
  ExpectTrue(facade.GetVerticesCount() == 3, "Facade must expose vertices");

  ExpectTrue(facade.MoveScene(1.0, 0.0, 0.0).IsSuccess(),
             "Facade move must succeed");
  ExpectTrue(facade.RotateScene(90.0, 0.0, 0.0).IsSuccess(),
             "Facade rotate must succeed");
  ExpectTrue(facade.ScaleScene(2.0).IsSuccess(), "Facade scale must succeed");

  const s21::Scene cloned = facade.CloneScene();
  ExpectTrue(cloned.VerticesCount() == 3, "CloneScene must copy geometry");
  ExpectTrue(cloned.filename() == path.filename().string(),
             "CloneScene must copy filename");
  std::filesystem::remove(path);
}

void TestFacadeReplaceSceneAndSettings() {
  auto drawer = std::make_unique<NullDrawer>();
  NullDrawer* drawer_ptr = drawer.get();
  s21::Facade facade(std::move(drawer));

  s21::Figure figure({{0.0, 0.0, 0.0}}, {});
  s21::Scene scene(std::move(figure), "cube.obj");
  ExpectTrue(facade.ReplaceScene(std::move(scene)).IsSuccess(),
             "ReplaceScene must succeed");
  ExpectTrue(facade.GetVerticesCount() == 1, "Facade must expose vertex count");

  s21::Scene empty_scene;
  ExpectTrue(!facade.ReplaceScene(std::move(empty_scene)).IsSuccess(),
             "ReplaceScene must reject empty scene");

  s21::RenderSettings settings = facade.GetRenderSettings();
  settings.SetProjection(s21::ProjectionType::kCentral);
  facade.SetRenderSettings(settings);
  facade.DrawScene(800, 600);
  ExpectTrue(drawer_ptr->was_called(), "Drawer must be called");
  ExpectTrue(drawer_ptr->last_width() == 800, "Drawer width must be passed");
  ExpectTrue(drawer_ptr->last_projection() == s21::ProjectionType::kCentral,
             "Drawer must receive projection settings");
}

void TestGifEncoderWritesValidHeader() {
  s21::GifFrame frame;
  frame.width = 2;
  frame.height = 2;
  frame.rgba = {255, 0, 0,   255, 0,   255, 0, 255,
                0,   0, 255, 255, 255, 255, 0, 255};

  const std::filesystem::path path =
      std::filesystem::temp_directory_path() / "s21_3dviewer_test.gif";
  const bool saved = s21::GifEncoder::Save(path.string(), {frame, frame}, 10);
  ExpectTrue(saved, "GifEncoder must save file");
  ExpectTrue(std::filesystem::exists(path), "GIF file must exist");

  std::ifstream file(path, std::ios::binary);
  char header[6] = {};
  file.read(header, 6);
  ExpectTrue(std::string(header, 6) == "GIF89a", "GIF must use GIF89a header");
  std::error_code remove_error;
  std::filesystem::remove(path, remove_error);
}

}  // namespace

int main() {
  const std::vector<void (*)()> tests = {
      TestObjReaderLoadsVerticesAndUniqueEdges,
      TestReaderSupportsSlashAndNegativeIndexes,
      TestReaderIgnoresNonGeometryLines,
      TestReaderRejectsEmptyFile,
      TestReaderRejectsInvalidFaceIndex,
      TestSceneLoaderMatchesReader,
      TestMoveScaleRotationMatrices,
      TestMatrixMultiplicationUsedByTransforms,
      TestScaleZeroThrows,
      TestSceneTransformUpdatesVertices,
      TestFigureNormalizeCentersModel,
      TestRenderSettingsClampValues,
      TestFacadeReturnsErrorsWithoutThrowing,
      TestFacadeLoadMoveRotateScale,
      TestFacadeReplaceSceneAndSettings,
      TestGifEncoderWritesValidHeader,
  };

  try {
    for (const auto& test : tests) {
      test();
    }
  } catch (const std::exception& error) {
    std::cerr << "TEST FAILED: " << error.what() << '\n';
    return EXIT_FAILURE;
  }

  std::cout << "All unit tests passed: " << tests.size() << '\n';
  return EXIT_SUCCESS;
}
