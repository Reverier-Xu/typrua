/**
 * app_manager.cpp
 *
 * Summary: the whole app manager.
 * Author: Reverier-Xu <reverier.xu@outlook.com>
 *
 * Created: 2021-11-28
 *
 */

#include "app_manager.h"

#include <QDir>
#include <QStandardPaths>
#include <QThread>

#include "gui_manager.h"

void detectPaths();

AppManager::AppManager(QObject *parent)
        : QObject(parent) {
}

void AppManager::initialize() {
    detectPaths();
    auto guiManager = GuiManager::instance(this);
    // GuiManager::exportComponents();
    guiManager->exportManagers();
    guiManager->createUi();
}

AppManager::~AppManager() = default;

void detectPaths() {
    auto dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    auto cachePath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/TypRua";
    QDir dir;
    QStringList dataPaths = {"/Database"};
    QStringList cachePaths = {"/"};
    for (auto &i : dataPaths)
        if (!dir.exists(dataPath + i))
            dir.mkpath(dataPath + i);
    for (auto &i : cachePaths)
        if (!dir.exists(cachePath + i))
            dir.mkpath(cachePath + i);
}
