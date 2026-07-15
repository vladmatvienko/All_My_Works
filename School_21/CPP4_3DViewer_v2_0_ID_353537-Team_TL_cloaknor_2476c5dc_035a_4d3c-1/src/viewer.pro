QT += widgets opengl
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets
CONFIG += c++20 warn_on
TEMPLATE = app
TARGET = 3DViewer_v2

INCLUDEPATH += $$PWD

SOURCES += \
    main.cc \
    s21_matrix_oop.cc \
    model/base_file_reader.cc \
    model/facade.cc \
    model/figure.cc \
    model/geometry.cc \
    model/gif_encoder.cc \
    model/obj_file_reader.cc \
    model/opengl_scene_drawer.cc \
    model/render_settings.cc \
    model/scene_loader.cc \
    model/scene.cc \
    model/transform_matrix.cc \
    controller/viewer_controller.cc \
    view/background_worker.cc \
    view/main_window.cc \
    view/model_widget.cc \
    view/settings_storage.cc \
    view/scene_meta.cc

HEADERS += \
    s21_matrix_oop.h \
    model/base_file_reader.h \
    model/facade.h \
    model/figure.h \
    model/geometry.h \
    model/gif_encoder.h \
    model/obj_file_reader.h \
    model/opengl_scene_drawer.h \
    model/render_settings.h \
    model/scene_loader.h \
    model/scene.h \
    model/scene_drawer_base.h \
    model/scene_object.h \
    model/transform_matrix.h \
    controller/viewer_controller.h \
    commands/command.h \
    view/background_worker.h \
    view/main_window.h \
    view/model_widget.h \
    view/settings_storage.h \
    view/scene_meta.h

unix:!macx: LIBS += -lGL
macx: LIBS += -framework OpenGL
