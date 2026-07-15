#include "model/opengl_scene_drawer.h"

#include <cmath>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

namespace s21 {
namespace {
constexpr double kPi = 3.14159265358979323846;
constexpr double kPerspectiveFov = 45.0;
constexpr double kNearPlane = 0.1;
constexpr double kFarPlane = 100.0;
constexpr double kOrthoHalfSpan = 1.6;

void DrawSquare(const Point3D& point, double half_size) {
  glBegin(GL_QUADS);
  glVertex3d(point.x - half_size, point.y - half_size, point.z);
  glVertex3d(point.x + half_size, point.y - half_size, point.z);
  glVertex3d(point.x + half_size, point.y + half_size, point.z);
  glVertex3d(point.x - half_size, point.y + half_size, point.z);
  glEnd();
}
}  // namespace

void OpenGLSceneDrawer::ApplyProjection(const RenderSettings& settings,
                                        int viewport_width,
                                        int viewport_height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  const double aspect = viewport_height > 0
                            ? static_cast<double>(viewport_width) /
                                  static_cast<double>(viewport_height)
                            : 1.0;

  if (settings.projection() == ProjectionType::kCentral) {
    const double radians = kPerspectiveFov * kPi / 360.0;
    const double top = kNearPlane * std::tan(radians);
    const double right = top * aspect;
    glFrustum(-right, right, -top, top, kNearPlane, kFarPlane);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, 0.0, -3.0);
    return;
  }

  if (aspect >= 1.0) {
    glOrtho(-kOrthoHalfSpan * aspect, kOrthoHalfSpan * aspect, -kOrthoHalfSpan,
            kOrthoHalfSpan, -kFarPlane, kFarPlane);
  } else {
    glOrtho(-kOrthoHalfSpan, kOrthoHalfSpan, -kOrthoHalfSpan / aspect,
            kOrthoHalfSpan / aspect, -kFarPlane, kFarPlane);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void OpenGLSceneDrawer::DrawEdges(const Figure& figure,
                                  const RenderSettings& settings) {
  const ColorRGB color = settings.edge_color();
  glColor3f(color.r, color.g, color.b);
  glLineWidth(settings.edge_thickness());

  if (settings.edge_type() == EdgeType::kDashed) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }

  const auto& vertices = figure.vertices();
  glBegin(GL_LINES);
  for (const Edge& edge : figure.edges()) {
    const Point3D& first = vertices[edge.begin()];
    const Point3D& second = vertices[edge.end()];
    glVertex3d(first.x, first.y, first.z);
    glVertex3d(second.x, second.y, second.z);
  }
  glEnd();
  glDisable(GL_LINE_STIPPLE);
}

void OpenGLSceneDrawer::DrawVertices(const Figure& figure,
                                     const RenderSettings& settings) {
  if (settings.vertex_display() == VertexDisplayType::kNone) {
    return;
  }

  const ColorRGB color = settings.vertex_color();
  glColor3f(color.r, color.g, color.b);

  if (settings.vertex_display() == VertexDisplayType::kCircle) {
    glPointSize(settings.vertex_size());
    glBegin(GL_POINTS);
    for (const Point3D& vertex : figure.vertices()) {
      glVertex3d(vertex.x, vertex.y, vertex.z);
    }
    glEnd();
    return;
  }

  const double half_size = static_cast<double>(settings.vertex_size()) * 0.01;
  for (const Point3D& vertex : figure.vertices()) {
    DrawSquare(vertex, half_size);
  }
}

void OpenGLSceneDrawer::DrawScene(const Scene& scene,
                                  const RenderSettings& settings,
                                  int viewport_width, int viewport_height) {
  const ColorRGB background = settings.background_color();
  glClearColor(background.r, background.g, background.b, 1.0F);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  ApplyProjection(settings, viewport_width, viewport_height);

  if (scene.Empty()) {
    return;
  }

  const Figure& figure = scene.figure();
  DrawEdges(figure, settings);
  DrawVertices(figure, settings);
}

}  // namespace s21
