/**
 * @file gui_manager.cxx
 * @author Reverier-Xu (reverier.xu@outlook.com)
 * @brief
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Wootec
 *
 */

#include "gui_manager.h"

#include <QMutex>
#include <QQmlContext>

#include "display_manager.h"

GuiManager* GuiManager::instance_ = nullptr;

GuiManager* GuiManager::instance(QObject* parent) {
    if (instance_ == nullptr) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if (instance_ == nullptr) {
            instance_ = new GuiManager(parent);
        }
        locker.unlock();
    }
    return instance_;
}

GuiManager::GuiManager(QObject* parent) : QObject(parent) {
    uiEngine_ = new QQmlApplicationEngine(this);
}

GuiManager::~GuiManager() = default;

void GuiManager::createUi() {
    const QUrl url(QStringLiteral("qrc:/views/MainWindow.qml"));
    uiEngine_->load(url);
}

void GuiManager::exportManagers() {
    uiEngine_->rootContext()->setContextProperty(
        "display", DisplayManager::instance(parent()));
}
