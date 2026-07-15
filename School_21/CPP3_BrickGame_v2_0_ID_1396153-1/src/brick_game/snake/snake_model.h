#ifndef SRC_BRICK_GAME_SNAKE_SNAKE_MODEL_H
#define SRC_BRICK_GAME_SNAKE_SNAKE_MODEL_H

#include <array>
#include <chrono>
#include <cstdint>
#include <deque>
#include <string>

#include "brick_game/snake/snake.h"

namespace s21 {

enum class SnakeState {
  kStart = 0,
  kSpawn,
  kMoving,
  kShifting,
  kEating,
  kGameOver
};

enum class Direction { kUp = 0, kRight, kDown, kLeft };

struct Cell {
  int row;
  int col;
};

class SnakeModel {
 public:
  SnakeModel();

  void Reset();
  void Start();
  void TogglePause();
  void Terminate();
  void TurnLeft();
  void TurnRight();
  void Accelerate(bool hold);
  GameInfo_t Update();

  SnakeState state() const { return state_; }
  int length() const { return static_cast<int>(snake_.size()); }
  Cell head() const { return snake_.empty() ? Cell{0, 0} : snake_.front(); }

  void SetSeedForTesting(std::uint32_t seed);
  void SetAppleForTesting(Cell apple);
  void ForceTickForTesting();
  void SetSnakeForTesting(const std::deque<Cell> &snake, Direction direction);

 private:
  static constexpr int kFieldWidth = SNAKE_FIELD_WIDTH;
  static constexpr int kFieldHeight = SNAKE_FIELD_HEIGHT;
  static constexpr int kNextSize = SNAKE_NEXT_SIZE;
  static constexpr int kInitialLength = 4;
  static constexpr int kWinLength = kFieldWidth * kFieldHeight;
  static constexpr int kBaseSpeedMs = 600;
  static constexpr int kSpeedStepMs = 40;
  static constexpr int kMinSpeedMs = 160;
  static constexpr int kMaxLevel = 10;
  static constexpr int kScorePerLevel = 5;

  using Clock = std::chrono::steady_clock;

  void InitializeGameInfo();
  void ClearField();
  void ClearNext();
  void Render();
  void RenderSnake();
  void ProcessPendingState();
  void SpawnState();
  void ShiftState();
  void EatState();
  bool TimerExpired() const;
  void TouchTimer();
  Cell NextHead() const;
  bool IsWallCollision(Cell cell) const;
  bool IsSelfCollision(Cell cell, bool eating) const;
  bool ContainsSnakeCell(Cell cell) const;
  void SpawnApple();
  void AddScore(int points);
  int CalculateLevel() const;
  int CalculateSpeed() const;
  std::uint32_t NextRandom();
  std::string HighScorePath() const;
  void LoadHighScore();
  void SaveHighScore() const;
  void SetState(SnakeState state);
  static Direction RotateLeft(Direction direction);
  static Direction RotateRight(Direction direction);

  bool initialized_ = false;
  bool fast_mode_ = false;
  SnakeState state_ = SnakeState::kStart;
  Direction direction_ = Direction::kRight;
  std::deque<Cell> snake_;
  Cell apple_{0, 0};
  std::uint32_t rng_ = 1U;
  Clock::time_point last_tick_{};
  GameInfo_t info_{};
  std::array<std::array<int, kFieldWidth>, kFieldHeight> field_storage_{};
  std::array<int *, kFieldHeight> field_rows_{};
  std::array<std::array<int, kNextSize>, kNextSize> next_storage_{};
  std::array<int *, kNextSize> next_rows_{};
};

}  // namespace s21

#endif  // SRC_BRICK_GAME_SNAKE_SNAKE_MODEL_H
