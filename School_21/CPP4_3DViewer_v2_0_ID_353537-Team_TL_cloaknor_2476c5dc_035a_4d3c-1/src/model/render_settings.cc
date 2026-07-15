#include "model/render_settings.h"

#include <algorithm>

namespace s21 {
namespace {
constexpr float kMinEdgeThickness = 0.1F;
constexpr float kMaxEdgeThickness = 20.0F;
constexpr float kMinVertexSize = 1.0F;
constexpr float kMaxVertexSize = 20.0F;
}  // namespace

ProjectionType RenderSettings::projection() const noexcept {
  return projection_;
}

EdgeType RenderSettings::edge_type() const noexcept { return edge_type_; }

const ColorRGB& RenderSettings::edge_color() const noexcept {
  return edge_color_;
}

float RenderSettings::edge_thickness() const noexcept {
  return edge_thickness_;
}

VertexDisplayType RenderSettings::vertex_display() const noexcept {
  return vertex_display_;
}

const ColorRGB& RenderSettings::vertex_color() const noexcept {
  return vertex_color_;
}

float RenderSettings::vertex_size() const noexcept { return vertex_size_; }

const ColorRGB& RenderSettings::background_color() const noexcept {
  return background_color_;
}

void RenderSettings::SetProjection(ProjectionType type) noexcept {
  projection_ = type;
}

void RenderSettings::SetEdgeType(EdgeType type) noexcept { edge_type_ = type; }

void RenderSettings::SetEdgeColor(const ColorRGB& color) noexcept {
  edge_color_ = color;
}

void RenderSettings::SetEdgeThickness(float thickness) noexcept {
  edge_thickness_ = std::clamp(thickness, kMinEdgeThickness, kMaxEdgeThickness);
}

void RenderSettings::SetVertexDisplay(VertexDisplayType type) noexcept {
  vertex_display_ = type;
}

void RenderSettings::SetVertexColor(const ColorRGB& color) noexcept {
  vertex_color_ = color;
}

void RenderSettings::SetVertexSize(float size) noexcept {
  vertex_size_ = std::clamp(size, kMinVertexSize, kMaxVertexSize);
}

void RenderSettings::SetBackgroundColor(const ColorRGB& color) noexcept {
  background_color_ = color;
}

}  // namespace s21
