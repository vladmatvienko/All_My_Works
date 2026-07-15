#ifndef SRC_VIEW_SETTINGS_STORAGE_H_
#define SRC_VIEW_SETTINGS_STORAGE_H_

#include "model/render_settings.h"

namespace s21 {

class SettingsStorage {
 public:
  static RenderSettings Load();
  static void Save(const RenderSettings& settings);
};

}  // namespace s21

#endif  // SRC_VIEW_SETTINGS_STORAGE_H_
