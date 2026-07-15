#ifndef SRC_COMMANDS_COMMAND_H_
#define SRC_COMMANDS_COMMAND_H_

#include <string>
#include <utility>

#include "controller/viewer_controller.h"
#include "model/scene.h"

namespace s21 {

class Command {
 public:
  virtual ~Command() = default;
  virtual FacadeOperationResult Execute() = 0;
};

class LoadModelCommand final : public Command {
 public:
  LoadModelCommand(ViewerController* controller, std::string path)
      : controller_(controller), path_(std::move(path)) {}

  FacadeOperationResult Execute() override {
    return controller_->LoadModel(path_);
  }

 private:
  ViewerController* controller_;
  std::string path_;
};

class MoveModelCommand final : public Command {
 public:
  MoveModelCommand(ViewerController* controller, double x, double y, double z)
      : controller_(controller), x_(x), y_(y), z_(z) {}

  FacadeOperationResult Execute() override {
    return controller_->MoveModel(x_, y_, z_);
  }

 private:
  ViewerController* controller_;
  double x_;
  double y_;
  double z_;
};

class RotateModelCommand final : public Command {
 public:
  RotateModelCommand(ViewerController* controller, double x_degree,
                     double y_degree, double z_degree)
      : controller_(controller),
        x_degree_(x_degree),
        y_degree_(y_degree),
        z_degree_(z_degree) {}

  FacadeOperationResult Execute() override {
    return controller_->RotateModel(x_degree_, y_degree_, z_degree_);
  }

 private:
  ViewerController* controller_;
  double x_degree_;
  double y_degree_;
  double z_degree_;
};

class ScaleModelCommand final : public Command {
 public:
  ScaleModelCommand(ViewerController* controller, double scale)
      : controller_(controller), scale_(scale) {}

  FacadeOperationResult Execute() override {
    return controller_->ScaleModel(scale_);
  }

 private:
  ViewerController* controller_;
  double scale_;
};

class ReplaceSceneCommand final : public Command {
 public:
  ReplaceSceneCommand(ViewerController* controller, Scene scene)
      : controller_(controller), scene_(std::move(scene)) {}

  FacadeOperationResult Execute() override {
    return controller_->ReplaceScene(std::move(scene_));
  }

 private:
  ViewerController* controller_;
  Scene scene_;
};

}  // namespace s21

#endif  // SRC_COMMANDS_COMMAND_H_
