#ifndef SRC_GUI_DESKTOP_MAIN_WINDOW_H
#define SRC_GUI_DESKTOP_MAIN_WINDOW_H

#include <QWidget>

#include "gui/desktop/game_controller.h"

class QLabel;
class QPushButton;
class QTimer;

class MainWindow : public QWidget {
 public:
  explicit MainWindow(QWidget *parent = nullptr);

 protected:
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

 private:
  static constexpr int kCellSize = 24;
  static constexpr int kFieldLeft = 20;
  static constexpr int kFieldTop = 20;
  static constexpr int kPanelLeft = 300;

  void BuildUi();
  void UpdateView();
  void DrawField(QPainter *painter, const GameInfo_t &info);
  void DrawPanel(const GameInfo_t &info);
  void SwitchGame(DesktopGame game);

  GameController controller_;
  QTimer *timer_ = nullptr;
  QLabel *title_label_ = nullptr;
  QLabel *score_label_ = nullptr;
  QLabel *high_score_label_ = nullptr;
  QLabel *level_label_ = nullptr;
  QLabel *speed_label_ = nullptr;
  QLabel *help_label_ = nullptr;
  QPushButton *tetris_button_ = nullptr;
  QPushButton *snake_button_ = nullptr;
  GameInfo_t last_info_{};
};

#endif  // SRC_GUI_DESKTOP_MAIN_WINDOW_H
