#include "brick_game/snake/snake_model.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>

namespace s21 {

SnakeModel::SnakeModel() { InitializeGameInfo(); }

void SnakeModel::InitializeGameInfo() {
  if (!initialized_) {
    for (int row = 0; row < kFieldHeight; ++row) {
      field_rows_[row] = field_storage_[row].data();
    }
    for (int row = 0; row < kNextSize; ++row) {
      next_rows_[row] = next_storage_[row].data();
    }
    info_.field = field_rows_.data();
    info_.next = next_rows_.data();
    info_.level = 1;
    info_.speed = CalculateSpeed();
    auto seed = static_cast<std::uint32_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(
            Clock::now().time_since_epoch())
            .count());
    rng_ = seed == 0U ? 1U : seed;
    LoadHighScore();
    initialized_ = true;
    Render();
  }
}

void SnakeModel::Reset() {
  InitializeGameInfo();
  snake_.clear();
  direction_ = Direction::kRight;
  fast_mode_ = false;
  info_.score = 0;
  info_.level = 1;
  info_.speed = CalculateSpeed();
  info_.pause = 0;
  LoadHighScore();
  state_ = SnakeState::kStart;
  TouchTimer();
  Render();
}

void SnakeModel::Start() {
  InitializeGameInfo();
  snake_.clear();
  direction_ = Direction::kRight;
  fast_mode_ = false;
  info_.score = 0;
  info_.level = 1;
  info_.speed = CalculateSpeed();
  info_.pause = 0;
  LoadHighScore();
  SetState(SnakeState::kSpawn);
  ProcessPendingState();
  Render();
}

void SnakeModel::TogglePause() {
  InitializeGameInfo();
  if (state_ != SnakeState::kStart && state_ != SnakeState::kGameOver) {
    info_.pause = info_.pause == 0 ? 1 : 0;
    TouchTimer();
  }
}

void SnakeModel::Terminate() {
  InitializeGameInfo();
  SetState(SnakeState::kGameOver);
  info_.pause = 0;
  if (info_.score > info_.high_score) {
    info_.high_score = info_.score;
    SaveHighScore();
  }
}

void SnakeModel::TurnLeft() {
  InitializeGameInfo();
  if (state_ == SnakeState::kMoving && info_.pause == 0) {
    direction_ = RotateLeft(direction_);
  }
}

void SnakeModel::TurnRight() {
  InitializeGameInfo();
  if (state_ == SnakeState::kMoving && info_.pause == 0) {
    direction_ = RotateRight(direction_);
  }
}

void SnakeModel::Accelerate(bool hold) {
  InitializeGameInfo();
  if (state_ == SnakeState::kMoving && info_.pause == 0) {
    fast_mode_ = hold;
    SetState(SnakeState::kShifting);
    ProcessPendingState();
    TouchTimer();
  }
}

GameInfo_t SnakeModel::Update() {
  InitializeGameInfo();
  if (info_.pause == 0 && state_ == SnakeState::kMoving && TimerExpired()) {
    SetState(SnakeState::kShifting);
  }
  if (info_.pause == 0) {
    ProcessPendingState();
  }
  Render();
  return info_;
}

void SnakeModel::ClearField() {
  for (auto &row : field_storage_) {
    row.fill(0);
  }
}

void SnakeModel::ClearNext() {
  for (auto &row : next_storage_) {
    row.fill(0);
  }
}

void SnakeModel::Render() {
  ClearField();
  ClearNext();
  RenderSnake();
  if (state_ != SnakeState::kStart && state_ != SnakeState::kGameOver &&
      !ContainsSnakeCell(apple_)) {
    field_storage_[apple_.row][apple_.col] = 2;
  }
}

void SnakeModel::RenderSnake() {
  for (Cell cell : snake_) {
    if (cell.row >= 0 && cell.row < kFieldHeight && cell.col >= 0 &&
        cell.col < kFieldWidth) {
      field_storage_[cell.row][cell.col] = 1;
    }
  }
}

void SnakeModel::ProcessPendingState() {
  int guard = 0;
  while (guard < 4 && state_ != SnakeState::kStart &&
         state_ != SnakeState::kMoving && state_ != SnakeState::kGameOver) {
    if (state_ == SnakeState::kSpawn) {
      SpawnState();
    } else if (state_ == SnakeState::kShifting) {
      ShiftState();
    } else if (state_ == SnakeState::kEating) {
      EatState();
    }
    ++guard;
  }
}

void SnakeModel::SpawnState() {
  snake_.clear();
  int row = kFieldHeight / 2;
  int head_col = kFieldWidth / 2;
  for (int i = 0; i < kInitialLength; ++i) {
    snake_.push_back(Cell{row, head_col - i});
  }
  SpawnApple();
  SetState(SnakeState::kMoving);
  TouchTimer();
}

void SnakeModel::ShiftState() {
  Cell next = NextHead();
  bool eating = next.row == apple_.row && next.col == apple_.col;

  if (IsWallCollision(next) || IsSelfCollision(next, eating)) {
    Terminate();
  } else {
    snake_.push_front(next);
    if (eating) {
      SetState(SnakeState::kEating);
    } else {
      snake_.pop_back();
      SetState(SnakeState::kMoving);
    }
    TouchTimer();
  }
}

void SnakeModel::EatState() {
  AddScore(1);
  if (length() >= kWinLength) {
    Terminate();
  } else {
    SpawnApple();
    SetState(SnakeState::kMoving);
  }
}

bool SnakeModel::TimerExpired() const {
  int effective_speed =
      fast_mode_ ? std::max(kMinSpeedMs, info_.speed / 2) : info_.speed;
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                     Clock::now() - last_tick_)
                     .count();
  return elapsed >= effective_speed;
}

void SnakeModel::TouchTimer() { last_tick_ = Clock::now(); }

Cell SnakeModel::NextHead() const {
  Cell next = head();
  if (direction_ == Direction::kUp) {
    --next.row;
  } else if (direction_ == Direction::kRight) {
    ++next.col;
  } else if (direction_ == Direction::kDown) {
    ++next.row;
  } else if (direction_ == Direction::kLeft) {
    --next.col;
  }
  return next;
}

bool SnakeModel::IsWallCollision(Cell cell) const {
  return cell.row < 0 || cell.row >= kFieldHeight || cell.col < 0 ||
         cell.col >= kFieldWidth;
}

bool SnakeModel::IsSelfCollision(Cell cell, bool eating) const {
  bool collision = false;
  int last_index = eating ? length() : length() - 1;

  for (int i = 0; i < last_index && !collision; ++i) {
    collision = snake_[i].row == cell.row && snake_[i].col == cell.col;
  }
  return collision;
}

bool SnakeModel::ContainsSnakeCell(Cell cell) const {
  return std::any_of(snake_.begin(), snake_.end(), [cell](Cell part) {
    return part.row == cell.row && part.col == cell.col;
  });
}

void SnakeModel::SpawnApple() {
  if (length() >= kWinLength) {
    apple_ = Cell{0, 0};
  } else {
    bool placed = false;
    while (!placed) {
      int index = static_cast<int>(NextRandom() % (kFieldWidth * kFieldHeight));
      Cell candidate{index / kFieldWidth, index % kFieldWidth};
      if (!ContainsSnakeCell(candidate)) {
        apple_ = candidate;
        placed = true;
      }
    }
  }
}

void SnakeModel::AddScore(int points) {
  if (points > 0) {
    info_.score += points;
    info_.level = CalculateLevel();
    info_.speed = CalculateSpeed();
    if (info_.score > info_.high_score) {
      info_.high_score = info_.score;
      SaveHighScore();
    }
  }
}

int SnakeModel::CalculateLevel() const {
  int level = info_.score / kScorePerLevel + 1;
  return std::min(level, kMaxLevel);
}

int SnakeModel::CalculateSpeed() const {
  int speed = kBaseSpeedMs - (info_.level - 1) * kSpeedStepMs;
  return std::max(speed, kMinSpeedMs);
}

std::uint32_t SnakeModel::NextRandom() {
  rng_ = rng_ * 1103515245U + 12345U;
  return rng_;
}

std::string SnakeModel::HighScorePath() const {
  const char *path = std::getenv("BRICKGAME_SNAKE_HIGHSCORE_FILE");
  if (path == nullptr || path[0] == '\0') {
    path = "snake_high_score.dat";
  }
  return path;
}

void SnakeModel::LoadHighScore() {
  std::ifstream file(HighScorePath());
  int loaded_score = 0;
  if (file >> loaded_score && loaded_score > 0) {
    info_.high_score = loaded_score;
  } else {
    info_.high_score = 0;
  }
}

void SnakeModel::SaveHighScore() const {
  std::ofstream file(HighScorePath());
  if (file.is_open()) {
    file << info_.high_score << '\n';
  }
}

void SnakeModel::SetState(SnakeState state) { state_ = state; }

Direction SnakeModel::RotateLeft(Direction direction) {
  return static_cast<Direction>((static_cast<int>(direction) + 3) % 4);
}

Direction SnakeModel::RotateRight(Direction direction) {
  return static_cast<Direction>((static_cast<int>(direction) + 1) % 4);
}

void SnakeModel::SetSeedForTesting(std::uint32_t seed) {
  InitializeGameInfo();
  rng_ = seed == 0U ? 1U : seed;
}

void SnakeModel::SetAppleForTesting(Cell apple) {
  InitializeGameInfo();
  if (!IsWallCollision(apple)) {
    apple_ = apple;
  }
  Render();
}

void SnakeModel::ForceTickForTesting() {
  InitializeGameInfo();
  last_tick_ = Clock::time_point{};
}

void SnakeModel::SetSnakeForTesting(const std::deque<Cell> &snake,
                                    Direction direction) {
  InitializeGameInfo();
  snake_ = snake;
  direction_ = direction;
  SetState(SnakeState::kMoving);
  TouchTimer();
  Render();
}

}  // namespace s21
