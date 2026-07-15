#include "view/main_window.h"

#include <QApplication>
#include <QCloseEvent>
#include <QColorDialog>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QImage>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <cstring>
#include <memory>

#include "commands/command.h"
#include "view/scene_meta.h"
#include "view/settings_storage.h"

namespace s21 {
namespace {

constexpr int kGifWidth = 640;
constexpr int kGifHeight = 480;
constexpr int kGifFps = 10;
constexpr int kGifDurationSeconds = 5;
constexpr int kGifFrameCount = kGifFps * kGifDurationSeconds;

QDoubleSpinBox* CreateSpinBox(double min_value, double max_value,
                              double default_value, double step) {
  auto* spin_box = new QDoubleSpinBox();
  spin_box->setRange(min_value, max_value);
  spin_box->setValue(default_value);
  spin_box->setSingleStep(step);
  spin_box->setDecimals(6);
  return spin_box;
}

QColor ToQColor(const ColorRGB& color) {
  return QColor::fromRgbF(color.r, color.g, color.b);
}

ColorRGB FromQColor(const QColor& color) {
  return {static_cast<float>(color.redF()), static_cast<float>(color.greenF()),
          static_cast<float>(color.blueF())};
}

void UpdateColorButton(QPushButton* button, const ColorRGB& color) {
  const QColor qcolor = ToQColor(color);
  button->setStyleSheet(
      QString("background-color: %1;").arg(qcolor.name(QColor::HexRgb)));
}

GifFrame FrameFromImage(const QImage& image) {
  GifFrame frame;
  frame.width = image.width();
  frame.height = image.height();
  const QImage rgba = image.convertToFormat(QImage::Format_RGBA8888).copy();
  frame.rgba.resize(static_cast<std::size_t>(frame.width * frame.height * 4));
  std::memcpy(frame.rgba.data(), rgba.constBits(), frame.rgba.size());
  return frame;
}

}  // namespace

MainWindow::MainWindow(ViewerController* controller, QWidget* parent)
    : QMainWindow(parent), controller_(controller) {
  setWindowTitle("3DViewer v2.0");
  resize(1200, 760);

  const RenderSettings saved_settings = SettingsStorage::Load();
  controller_->ApplyRenderSettings(saved_settings);
  edge_color_ = saved_settings.edge_color();
  vertex_color_ = saved_settings.vertex_color();
  background_color_ = saved_settings.background_color();

  setCentralWidget(CreateCentralWidget());
  UpdateInfo();

  RegisterSceneMetaType();

  background_worker_ = new BackgroundWorker();
  background_worker_->moveToThread(&worker_thread_);
  connect(&worker_thread_, &QThread::finished, background_worker_,
          &QObject::deleteLater);
  connect(background_worker_, &BackgroundWorker::ModelLoaded, this,
          &MainWindow::OnModelLoaded);
  connect(background_worker_, &BackgroundWorker::SceneTransformed, this,
          &MainWindow::OnSceneTransformed);
  connect(background_worker_, &BackgroundWorker::Failed, this,
          &MainWindow::OnBackgroundFailed);
  worker_thread_.start();

  projection_box_->setCurrentIndex(
      saved_settings.projection() == ProjectionType::kCentral ? 1 : 0);
  edge_type_box_->setCurrentIndex(
      saved_settings.edge_type() == EdgeType::kDashed ? 1 : 0);
  edge_thickness_spin_->setValue(saved_settings.edge_thickness());
  if (saved_settings.vertex_display() == VertexDisplayType::kCircle) {
    vertex_display_box_->setCurrentIndex(1);
  } else if (saved_settings.vertex_display() == VertexDisplayType::kSquare) {
    vertex_display_box_->setCurrentIndex(2);
  } else {
    vertex_display_box_->setCurrentIndex(0);
  }
  vertex_size_spin_->setValue(saved_settings.vertex_size());
  UpdateColorButton(edge_color_button_, edge_color_);
  UpdateColorButton(vertex_color_button_, vertex_color_);
  UpdateColorButton(background_color_button_, background_color_);

  connect(&gif_timer_, &QTimer::timeout, this, &MainWindow::CaptureGifFrame);
}

MainWindow::~MainWindow() {
  ApplySettingsFromUi();
  worker_thread_.quit();
  worker_thread_.wait();
}

void MainWindow::closeEvent(QCloseEvent* event) {
  ApplySettingsFromUi();
  QMainWindow::closeEvent(event);
}

QWidget* MainWindow::CreateCentralWidget() {
  auto* central_widget = new QWidget(this);
  auto* main_layout = new QHBoxLayout(central_widget);

  model_widget_ = new ModelWidget(controller_, central_widget);
  model_widget_->setMinimumSize(760, 620);
  main_layout->addWidget(model_widget_, 1);

  auto* scroll_area = new QScrollArea(central_widget);
  scroll_area->setWidgetResizable(true);
  auto* side_panel = new QWidget(scroll_area);
  auto* side_layout = new QVBoxLayout(side_panel);
  side_layout->addWidget(CreateFilePanel());
  side_layout->addWidget(CreateTransformPanel());
  side_layout->addWidget(CreateSettingsPanel());
  side_layout->addWidget(CreateExportPanel());
  side_layout->addStretch(1);
  scroll_area->setWidget(side_panel);
  scroll_area->setMinimumWidth(340);
  main_layout->addWidget(scroll_area);

  return central_widget;
}

QWidget* MainWindow::CreateFilePanel() {
  auto* group = new QGroupBox("Модель", this);
  auto* layout = new QVBoxLayout(group);

  auto* open_button = new QPushButton("Выбрать OBJ", group);
  connect(open_button, &QPushButton::clicked, this, &MainWindow::OpenModel);

  filename_label_ = new QLabel("Файл: не выбран", group);
  vertices_label_ = new QLabel("Вершин: 0", group);
  edges_label_ = new QLabel("Рёбер: 0", group);

  layout->addWidget(open_button);
  layout->addWidget(filename_label_);
  layout->addWidget(vertices_label_);
  layout->addWidget(edges_label_);
  return group;
}

QWidget* MainWindow::CreateTransformPanel() {
  auto* panel = new QWidget(this);
  auto* layout = new QVBoxLayout(panel);

  layout->addWidget(CreateAxisBox("Перемещение", &move_x_, &move_y_, &move_z_,
                                  "Переместить", [this]() { ApplyMove(); }));
  layout->addWidget(CreateAxisBox("Поворот, градусы", &rotate_x_, &rotate_y_,
                                  &rotate_z_, "Повернуть",
                                  [this]() { ApplyRotation(); }));

  auto* scale_group = new QGroupBox("Масштаб", panel);
  auto* scale_layout = new QGridLayout(scale_group);
  scale_value_ = CreateSpinBox(-1000000.0, 1000000.0, 1.0, 0.1);
  auto* scale_button = new QPushButton("Масштабировать", scale_group);
  connect(scale_button, &QPushButton::clicked, this, &MainWindow::ApplyScale);
  scale_layout->addWidget(new QLabel("Коэффициент", scale_group), 0, 0);
  scale_layout->addWidget(scale_value_, 0, 1);
  scale_layout->addWidget(scale_button, 1, 0, 1, 2);
  layout->addWidget(scale_group);

  return panel;
}

QWidget* MainWindow::CreateSettingsPanel() {
  auto* group = new QGroupBox("Настройки отображения", this);
  auto* layout = new QGridLayout(group);

  projection_box_ = new QComboBox(group);
  projection_box_->addItems({"Параллельная", "Центральная"});
  edge_type_box_ = new QComboBox(group);
  edge_type_box_->addItems({"Сплошная", "Пунктирная"});
  edge_color_button_ = new QPushButton("Цвет рёбер", group);
  edge_thickness_spin_ = CreateSpinBox(0.1, 20.0, 1.0, 0.1);
  vertex_display_box_ = new QComboBox(group);
  vertex_display_box_->addItems({"Нет", "Круг", "Квадрат"});
  vertex_color_button_ = new QPushButton("Цвет вершин", group);
  vertex_size_spin_ = CreateSpinBox(1.0, 20.0, 3.0, 0.5);
  background_color_button_ = new QPushButton("Цвет фона", group);

  layout->addWidget(new QLabel("Проекция", group), 0, 0);
  layout->addWidget(projection_box_, 0, 1);
  layout->addWidget(new QLabel("Тип рёбер", group), 1, 0);
  layout->addWidget(edge_type_box_, 1, 1);
  layout->addWidget(edge_color_button_, 2, 0, 1, 2);
  layout->addWidget(new QLabel("Толщина рёбер", group), 3, 0);
  layout->addWidget(edge_thickness_spin_, 3, 1);
  layout->addWidget(new QLabel("Вершины", group), 4, 0);
  layout->addWidget(vertex_display_box_, 4, 1);
  layout->addWidget(vertex_color_button_, 5, 0, 1, 2);
  layout->addWidget(new QLabel("Размер вершин", group), 6, 0);
  layout->addWidget(vertex_size_spin_, 6, 1);
  layout->addWidget(background_color_button_, 7, 0, 1, 2);

  const auto settings_changed = [this]() { ApplySettingsFromUi(); };
  connect(projection_box_, QOverload<int>::of(&QComboBox::currentIndexChanged),
          settings_changed);
  connect(edge_type_box_, QOverload<int>::of(&QComboBox::currentIndexChanged),
          settings_changed);
  connect(edge_thickness_spin_,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          settings_changed);
  connect(vertex_display_box_,
          QOverload<int>::of(&QComboBox::currentIndexChanged),
          settings_changed);
  connect(vertex_size_spin_,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          settings_changed);
  connect(edge_color_button_, &QPushButton::clicked,
          [this]() { PickColor(&edge_color_, edge_color_button_); });
  connect(vertex_color_button_, &QPushButton::clicked,
          [this]() { PickColor(&vertex_color_, vertex_color_button_); });
  connect(background_color_button_, &QPushButton::clicked, [this]() {
    PickColor(&background_color_, background_color_button_);
  });

  return group;
}

QWidget* MainWindow::CreateExportPanel() {
  auto* group = new QGroupBox("Экспорт", this);
  auto* layout = new QVBoxLayout(group);

  auto* save_bmp_button = new QPushButton("Сохранить BMP", group);
  auto* save_jpeg_button = new QPushButton("Сохранить JPEG", group);
  record_gif_button_ = new QPushButton("Записать GIF (5 c)", group);
  gif_status_label_ = new QLabel("GIF: готов", group);

  connect(save_bmp_button, &QPushButton::clicked,
          [this]() { SaveImage("BMP"); });
  connect(save_jpeg_button, &QPushButton::clicked,
          [this]() { SaveImage("JPEG"); });
  connect(record_gif_button_, &QPushButton::clicked, this,
          &MainWindow::StartGifRecording);

  layout->addWidget(save_bmp_button);
  layout->addWidget(save_jpeg_button);
  layout->addWidget(record_gif_button_);
  layout->addWidget(gif_status_label_);
  return group;
}

QWidget* MainWindow::CreateAxisBox(const QString& title, QDoubleSpinBox** x,
                                   QDoubleSpinBox** y, QDoubleSpinBox** z,
                                   const QString& button_text,
                                   const std::function<void()>& handler) {
  auto* group = new QGroupBox(title, this);
  auto* layout = new QGridLayout(group);

  *x = CreateSpinBox(-1000000.0, 1000000.0, 0.0, 0.1);
  *y = CreateSpinBox(-1000000.0, 1000000.0, 0.0, 0.1);
  *z = CreateSpinBox(-1000000.0, 1000000.0, 0.0, 0.1);

  layout->addWidget(new QLabel("X", group), 0, 0);
  layout->addWidget(*x, 0, 1);
  layout->addWidget(new QLabel("Y", group), 1, 0);
  layout->addWidget(*y, 1, 1);
  layout->addWidget(new QLabel("Z", group), 2, 0);
  layout->addWidget(*z, 2, 1);

  auto* button = new QPushButton(button_text, group);
  connect(button, &QPushButton::clicked, handler);
  layout->addWidget(button, 3, 0, 1, 2);
  return group;
}

void MainWindow::OpenModel() {
  const QString path = QFileDialog::getOpenFileName(
      this, "Открыть OBJ", QString(), "OBJ files (*.obj);;All files (*)");
  if (path.isEmpty()) {
    return;
  }

  SetLoadingState(true);
  gif_status_label_->setText("Загрузка модели...");
  QMetaObject::invokeMethod(background_worker_, "LoadModel",
                            Qt::QueuedConnection, Q_ARG(QString, path));
}

void MainWindow::ApplyMove() {
  if (!controller_->HasScene()) {
    QMessageBox::warning(this, "3DViewer", "Сначала загрузите модель.");
    return;
  }
  SetLoadingState(true);
  Scene snapshot = controller_->CloneScene();
  QMetaObject::invokeMethod(
      background_worker_, "MoveScene", Qt::QueuedConnection,
      Q_ARG(Scene, snapshot), Q_ARG(double, move_x_->value()),
      Q_ARG(double, move_y_->value()), Q_ARG(double, move_z_->value()));
}

void MainWindow::ApplyRotation() {
  if (!controller_->HasScene()) {
    QMessageBox::warning(this, "3DViewer", "Сначала загрузите модель.");
    return;
  }
  SetLoadingState(true);
  Scene snapshot = controller_->CloneScene();
  QMetaObject::invokeMethod(
      background_worker_, "RotateScene", Qt::QueuedConnection,
      Q_ARG(Scene, snapshot), Q_ARG(double, rotate_x_->value()),
      Q_ARG(double, rotate_y_->value()), Q_ARG(double, rotate_z_->value()));
}

void MainWindow::ApplyScale() {
  if (!controller_->HasScene()) {
    QMessageBox::warning(this, "3DViewer", "Сначала загрузите модель.");
    return;
  }
  SetLoadingState(true);
  Scene snapshot = controller_->CloneScene();
  QMetaObject::invokeMethod(background_worker_, "ScaleScene",
                            Qt::QueuedConnection, Q_ARG(Scene, snapshot),
                            Q_ARG(double, scale_value_->value()));
}

void MainWindow::RunCommand(Command& command) {
  const FacadeOperationResult result = command.Execute();
  if (!result.IsSuccess()) {
    QMessageBox::warning(this, "3DViewer",
                         QString::fromStdString(result.GetErrorMessage()));
    return;
  }
  UpdateInfo();
  model_widget_->update();
}

void MainWindow::UpdateInfo() {
  filename_label_->setText(
      QString("Файл: %1")
          .arg(controller_->Filename().empty()
                   ? QString("не выбран")
                   : QString::fromStdString(controller_->Filename())));
  vertices_label_->setText(
      QString("Вершин: %1").arg(controller_->VerticesCount()));
  edges_label_->setText(QString("Рёбер: %1").arg(controller_->EdgesCount()));
}

void MainWindow::ApplySettingsFromUi() {
  RenderSettings settings = controller_->RenderSettingsRef();
  settings.SetProjection(projection_box_->currentIndex() == 1
                             ? ProjectionType::kCentral
                             : ProjectionType::kParallel);
  settings.SetEdgeType(edge_type_box_->currentIndex() == 1 ? EdgeType::kDashed
                                                           : EdgeType::kSolid);
  settings.SetEdgeColor(edge_color_);
  settings.SetEdgeThickness(static_cast<float>(edge_thickness_spin_->value()));

  if (vertex_display_box_->currentIndex() == 1) {
    settings.SetVertexDisplay(VertexDisplayType::kCircle);
  } else if (vertex_display_box_->currentIndex() == 2) {
    settings.SetVertexDisplay(VertexDisplayType::kSquare);
  } else {
    settings.SetVertexDisplay(VertexDisplayType::kNone);
  }
  settings.SetVertexColor(vertex_color_);
  settings.SetVertexSize(static_cast<float>(vertex_size_spin_->value()));
  settings.SetBackgroundColor(background_color_);
  controller_->ApplyRenderSettings(settings);
  SettingsStorage::Save(settings);
  model_widget_->update();
}

void MainWindow::PickColor(ColorRGB* target, QPushButton* button) {
  const QColor selected =
      QColorDialog::getColor(ToQColor(*target), this, "Выбор цвета");
  if (!selected.isValid()) {
    return;
  }
  *target = FromQColor(selected);
  UpdateColorButton(button, *target);
  ApplySettingsFromUi();
}

void MainWindow::SaveImage(const char* format) {
  if (!controller_->HasScene()) {
    QMessageBox::warning(this, "3DViewer", "Сначала загрузите модель.");
    return;
  }

  const QString filter =
      QString("Images (*.%1)").arg(QString(format).toLower());
  const QString path =
      QFileDialog::getSaveFileName(this, "Сохранить", QString(), filter);
  if (path.isEmpty()) {
    return;
  }

  model_widget_->update();
  const QImage image = model_widget_->CaptureFrame(0, 0);
  if (!image.save(path, format)) {
    QMessageBox::warning(this, "3DViewer", "Не удалось сохранить изображение.");
  }
}

void MainWindow::StartGifRecording() {
  if (!controller_->HasScene()) {
    QMessageBox::warning(this, "3DViewer", "Сначала загрузите модель.");
    return;
  }
  if (gif_timer_.isActive()) {
    return;
  }

  gif_frames_.clear();
  gif_frames_.reserve(static_cast<std::size_t>(kGifFrameCount));
  gif_frames_left_ = kGifFrameCount;
  record_gif_button_->setEnabled(false);
  gif_status_label_->setText("GIF: запись...");
  gif_timer_.start(1000 / kGifFps);
  CaptureGifFrame();
}

void MainWindow::CaptureGifFrame() {
  model_widget_->update();
  gif_frames_.push_back(
      FrameFromImage(model_widget_->CaptureFrame(kGifWidth, kGifHeight)));
  --gif_frames_left_;
  gif_status_label_->setText(QString("GIF: кадр %1/%2")
                                 .arg(kGifFrameCount - gif_frames_left_)
                                 .arg(kGifFrameCount));

  if (gif_frames_left_ <= 0) {
    FinishGifRecording();
  }
}

void MainWindow::FinishGifRecording() {
  gif_timer_.stop();
  record_gif_button_->setEnabled(true);

  const QString path = QFileDialog::getSaveFileName(
      this, "Сохранить GIF", QString(), "GIF files (*.gif)");
  if (path.isEmpty()) {
    gif_status_label_->setText("GIF: отменено");
    gif_frames_.clear();
    return;
  }

  const bool saved =
      GifEncoder::Save(path.toStdString(), gif_frames_, 100 / kGifFps);
  gif_frames_.clear();
  gif_status_label_->setText(saved ? "GIF: сохранён" : "GIF: ошибка");
  if (!saved) {
    QMessageBox::warning(this, "3DViewer", "Не удалось сохранить GIF.");
  }
}

void MainWindow::SetLoadingState(bool loading) {
  if (loading) {
    QApplication::setOverrideCursor(Qt::WaitCursor);
  } else {
    QApplication::restoreOverrideCursor();
  }
}

void MainWindow::OnModelLoaded(Scene scene) {
  ReplaceSceneCommand command(controller_, std::move(scene));
  RunCommand(command);
  SetLoadingState(false);
  gif_status_label_->setText("GIF: готов");
}

void MainWindow::OnSceneTransformed(Scene scene) {
  ReplaceSceneCommand command(controller_, std::move(scene));
  RunCommand(command);
  SetLoadingState(false);
}

void MainWindow::OnBackgroundFailed(const QString& error_message) {
  SetLoadingState(false);
  gif_status_label_->setText("GIF: готов");
  QMessageBox::warning(this, "3DViewer", error_message);
}

}  // namespace s21
