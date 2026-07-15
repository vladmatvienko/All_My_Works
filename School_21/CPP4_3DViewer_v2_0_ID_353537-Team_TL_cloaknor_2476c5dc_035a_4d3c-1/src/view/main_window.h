#ifndef SRC_VIEW_MAIN_WINDOW_H_
#define SRC_VIEW_MAIN_WINDOW_H_

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QThread>
#include <QTimer>
#include <functional>
#include <vector>

#include "commands/command.h"
#include "controller/viewer_controller.h"
#include "model/gif_encoder.h"
#include "view/background_worker.h"
#include "view/model_widget.h"

namespace s21 {

class MainWindow final : public QMainWindow {
 public:
  explicit MainWindow(ViewerController* controller, QWidget* parent = nullptr);
  ~MainWindow() override;

 protected:
  void closeEvent(QCloseEvent* event) override;

 private:
  QWidget* CreateCentralWidget();
  QWidget* CreateFilePanel();
  QWidget* CreateTransformPanel();
  QWidget* CreateSettingsPanel();
  QWidget* CreateExportPanel();
  QWidget* CreateAxisBox(const QString& title, QDoubleSpinBox** x,
                         QDoubleSpinBox** y, QDoubleSpinBox** z,
                         const QString& button_text,
                         const std::function<void()>& handler);
  void OpenModel();
  void ApplyMove();
  void ApplyRotation();
  void ApplyScale();
  void RunCommand(Command& command);
  void UpdateInfo();
  void ApplySettingsFromUi();
  void PickColor(ColorRGB* target, QPushButton* button);
  void SaveImage(const char* format);
  void StartGifRecording();
  void CaptureGifFrame();
  void FinishGifRecording();
  void SetLoadingState(bool loading);
  void OnModelLoaded(Scene scene);
  void OnSceneTransformed(Scene scene);
  void OnBackgroundFailed(const QString& error_message);

  ViewerController* controller_ = nullptr;
  ModelWidget* model_widget_ = nullptr;
  QLabel* filename_label_ = nullptr;
  QLabel* vertices_label_ = nullptr;
  QLabel* edges_label_ = nullptr;
  QDoubleSpinBox* move_x_ = nullptr;
  QDoubleSpinBox* move_y_ = nullptr;
  QDoubleSpinBox* move_z_ = nullptr;
  QDoubleSpinBox* rotate_x_ = nullptr;
  QDoubleSpinBox* rotate_y_ = nullptr;
  QDoubleSpinBox* rotate_z_ = nullptr;
  QDoubleSpinBox* scale_value_ = nullptr;
  QComboBox* projection_box_ = nullptr;
  QComboBox* edge_type_box_ = nullptr;
  QPushButton* edge_color_button_ = nullptr;
  QDoubleSpinBox* edge_thickness_spin_ = nullptr;
  QComboBox* vertex_display_box_ = nullptr;
  QPushButton* vertex_color_button_ = nullptr;
  QDoubleSpinBox* vertex_size_spin_ = nullptr;
  QPushButton* background_color_button_ = nullptr;
  QPushButton* record_gif_button_ = nullptr;
  QLabel* gif_status_label_ = nullptr;

  ColorRGB edge_color_{0.1F, 0.9F, 0.9F};
  ColorRGB vertex_color_{1.0F, 1.0F, 1.0F};
  ColorRGB background_color_{0.05F, 0.05F, 0.07F};

  QThread worker_thread_;
  BackgroundWorker* background_worker_ = nullptr;
  QTimer gif_timer_;
  std::vector<GifFrame> gif_frames_;
  int gif_frames_left_ = 0;
};

}  // namespace s21

#endif  // SRC_VIEW_MAIN_WINDOW_H_
