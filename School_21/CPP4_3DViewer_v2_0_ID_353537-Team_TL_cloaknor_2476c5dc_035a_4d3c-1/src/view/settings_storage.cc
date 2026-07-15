#include "view/settings_storage.h"

#include <QSettings>

namespace s21 {
namespace {

ColorRGB LoadColor(QSettings& settings, const char* key_r, const char* key_g,
                   const char* key_b, const ColorRGB& fallback) {
  ColorRGB color = fallback;
  color.r = static_cast<float>(settings.value(key_r, fallback.r).toDouble());
  color.g = static_cast<float>(settings.value(key_g, fallback.g).toDouble());
  color.b = static_cast<float>(settings.value(key_b, fallback.b).toDouble());
  return color;
}

void SaveColor(QSettings& settings, const char* key_r, const char* key_g,
               const char* key_b, const ColorRGB& color) {
  settings.setValue(key_r, color.r);
  settings.setValue(key_g, color.g);
  settings.setValue(key_b, color.b);
}

}  // namespace

RenderSettings SettingsStorage::Load() {
  QSettings settings("School21", "3DViewer_v2");
  RenderSettings render_settings;

  const int projection = settings.value("projection", 0).toInt();
  render_settings.SetProjection(projection == 1 ? ProjectionType::kCentral
                                                : ProjectionType::kParallel);

  const int edge_type = settings.value("edge_type", 0).toInt();
  render_settings.SetEdgeType(edge_type == 1 ? EdgeType::kDashed
                                             : EdgeType::kSolid);
  render_settings.SetEdgeColor(LoadColor(settings, "edge_r", "edge_g", "edge_b",
                                         render_settings.edge_color()));
  render_settings.SetEdgeThickness(
      static_cast<float>(settings.value("edge_thickness", 1.0).toDouble()));

  const int vertex_display = settings.value("vertex_display", 0).toInt();
  if (vertex_display == 1) {
    render_settings.SetVertexDisplay(VertexDisplayType::kCircle);
  } else if (vertex_display == 2) {
    render_settings.SetVertexDisplay(VertexDisplayType::kSquare);
  } else {
    render_settings.SetVertexDisplay(VertexDisplayType::kNone);
  }
  render_settings.SetVertexColor(LoadColor(settings, "vertex_r", "vertex_g",
                                           "vertex_b",
                                           render_settings.vertex_color()));
  render_settings.SetVertexSize(
      static_cast<float>(settings.value("vertex_size", 3.0).toDouble()));
  render_settings.SetBackgroundColor(
      LoadColor(settings, "background_r", "background_g", "background_b",
                render_settings.background_color()));

  return render_settings;
}

void SettingsStorage::Save(const RenderSettings& render_settings) {
  QSettings settings("School21", "3DViewer_v2");
  settings.setValue(
      "projection",
      render_settings.projection() == ProjectionType::kCentral ? 1 : 0);
  settings.setValue("edge_type",
                    render_settings.edge_type() == EdgeType::kDashed ? 1 : 0);
  SaveColor(settings, "edge_r", "edge_g", "edge_b",
            render_settings.edge_color());
  settings.setValue("edge_thickness", render_settings.edge_thickness());

  int vertex_display = 0;
  if (render_settings.vertex_display() == VertexDisplayType::kCircle) {
    vertex_display = 1;
  } else if (render_settings.vertex_display() == VertexDisplayType::kSquare) {
    vertex_display = 2;
  }
  settings.setValue("vertex_display", vertex_display);
  SaveColor(settings, "vertex_r", "vertex_g", "vertex_b",
            render_settings.vertex_color());
  settings.setValue("vertex_size", render_settings.vertex_size());
  SaveColor(settings, "background_r", "background_g", "background_b",
            render_settings.background_color());
}

}  // namespace s21
