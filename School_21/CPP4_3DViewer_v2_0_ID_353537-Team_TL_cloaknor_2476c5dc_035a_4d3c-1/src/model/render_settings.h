#ifndef SRC_MODEL_RENDER_SETTINGS_H_
#define SRC_MODEL_RENDER_SETTINGS_H_

namespace s21 {

enum class ProjectionType { kParallel, kCentral };

enum class EdgeType { kSolid, kDashed };

enum class VertexDisplayType { kNone, kCircle, kSquare };

struct ColorRGB {
  float r = 0.0F;
  float g = 0.0F;
  float b = 0.0F;
};

class RenderSettings {
 public:
  ProjectionType projection() const noexcept;
  EdgeType edge_type() const noexcept;
  const ColorRGB& edge_color() const noexcept;
  float edge_thickness() const noexcept;
  VertexDisplayType vertex_display() const noexcept;
  const ColorRGB& vertex_color() const noexcept;
  float vertex_size() const noexcept;
  const ColorRGB& background_color() const noexcept;

  void SetProjection(ProjectionType type) noexcept;
  void SetEdgeType(EdgeType type) noexcept;
  void SetEdgeColor(const ColorRGB& color) noexcept;
  void SetEdgeThickness(float thickness) noexcept;
  void SetVertexDisplay(VertexDisplayType type) noexcept;
  void SetVertexColor(const ColorRGB& color) noexcept;
  void SetVertexSize(float size) noexcept;
  void SetBackgroundColor(const ColorRGB& color) noexcept;

 private:
  ProjectionType projection_ = ProjectionType::kParallel;
  EdgeType edge_type_ = EdgeType::kSolid;
  ColorRGB edge_color_{0.1F, 0.9F, 0.9F};
  float edge_thickness_ = 1.0F;
  VertexDisplayType vertex_display_ = VertexDisplayType::kNone;
  ColorRGB vertex_color_{1.0F, 1.0F, 1.0F};
  float vertex_size_ = 3.0F;
  ColorRGB background_color_{0.05F, 0.05F, 0.07F};
};

}  // namespace s21

#endif  // SRC_MODEL_RENDER_SETTINGS_H_
