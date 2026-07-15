#include "gui/desktop/main_window.h"

#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  BuildUi();
  setFixedSize(500, 540);
  setFocusPolicy(Qt::StrongFocus);
  last_info_ = controller_.UpdateCurrentState();
  timer_ = new QTimer(this);
  connect(timer_, &QTimer::timeout, this, [this]() { UpdateView(); });
  timer_->start(50);
}

void MainWindow::BuildUi() {
  title_label_ = new QLabel(this);
  score_label_ = new QLabel(this);
  high_score_label_ = new QLabel(this);
  level_label_ = new QLabel(this);
  speed_label_ = new QLabel(this);
  help_label_ = new QLabel(this);
  tetris_button_ = new QPushButton("Tetris", this);
  snake_button_ = new QPushButton("Snake", this);

  title_label_->setGeometry(kPanelLeft, 20, 170, 24);
  score_label_->setGeometry(kPanelLeft, 60, 170, 24);
  high_score_label_->setGeometry(kPanelLeft, 90, 170, 24);
  level_label_->setGeometry(kPanelLeft, 120, 170, 24);
  speed_label_->setGeometry(kPanelLeft, 150, 170, 24);
  tetris_button_->setGeometry(kPanelLeft, 195, 80, 28);
  snake_button_->setGeometry(kPanelLeft + 90, 195, 80, 28);
  help_label_->setGeometry(kPanelLeft, 250, 180, 180);
  help_label_->setText(
      "S/Enter: start\nP: pause\nArrows: move/turn\nSpace: "
      "action/speed\nQ/Esc: quit\n1/2: Tetris/Snake");

  connect(tetris_button_, &QPushButton::clicked, this,
          [this]() { SwitchGame(DesktopGame::kTetris); });
  connect(snake_button_, &QPushButton::clicked, this,
          [this]() { SwitchGame(DesktopGame::kSnake); });
}

void MainWindow::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);
  QPainter painter(this);
  DrawField(&painter, last_info_);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  bool handled = true;
  if (event->key() == Qt::Key_1) {
    SwitchGame(DesktopGame::kTetris);
  } else if (event->key() == Qt::Key_2) {
    SwitchGame(DesktopGame::kSnake);
  } else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Return ||
             event->key() == Qt::Key_Enter) {
    controller_.UserInput(Start);
  } else if (event->key() == Qt::Key_P) {
    controller_.UserInput(Pause);
  } else if (event->key() == Qt::Key_Q || event->key() == Qt::Key_Escape) {
    controller_.UserInput(Terminate);
    close();
  } else if (event->key() == Qt::Key_Left) {
    controller_.UserInput(Left);
  } else if (event->key() == Qt::Key_Right) {
    controller_.UserInput(Right);
  } else if (event->key() == Qt::Key_Down) {
    controller_.UserInput(Down);
  } else if (event->key() == Qt::Key_Up) {
    controller_.UserInput(Up);
  } else if (event->key() == Qt::Key_Space) {
    controller_.UserInput(Action, event->isAutoRepeat());
  } else {
    handled = false;
  }

  if (handled) {
    UpdateView();
  } else {
    QWidget::keyPressEvent(event);
  }
}

void MainWindow::UpdateView() {
  last_info_ = controller_.UpdateCurrentState();
  DrawPanel(last_info_);
  update();
}

void MainWindow::DrawField(QPainter *painter, const GameInfo_t &info) {
  painter->drawRect(kFieldLeft - 1, kFieldTop - 1,
                    BRICK_GAME_FIELD_WIDTH * kCellSize + 2,
                    BRICK_GAME_FIELD_HEIGHT * kCellSize + 2);
  for (int row = 0; row < BRICK_GAME_FIELD_HEIGHT; ++row) {
    for (int col = 0; col < BRICK_GAME_FIELD_WIDTH; ++col) {
      QRect rect(kFieldLeft + col * kCellSize, kFieldTop + row * kCellSize,
                 kCellSize, kCellSize);
      painter->drawRect(rect);
      if (info.field[row][col] != 0) {
        if (info.field[row][col] == 2) {
          painter->drawEllipse(rect.adjusted(4, 4, -4, -4));
        } else {
          painter->fillRect(rect.adjusted(3, 3, -3, -3), Qt::black);
        }
      }
    }
  }
}

void MainWindow::DrawPanel(const GameInfo_t &info) {
  title_label_->setText(controller_.Title());
  score_label_->setText(QString("Score: %1").arg(info.score));
  high_score_label_->setText(QString("High score: %1").arg(info.high_score));
  level_label_->setText(QString("Level: %1").arg(info.level));
  speed_label_->setText(QString("Speed: %1 ms").arg(info.speed));
}

void MainWindow::SwitchGame(DesktopGame game) {
  controller_.SetGame(game);
  UpdateView();
}
