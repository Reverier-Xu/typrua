/**
 * @file folder_manager.cxx
 * @author
 * @brief
 * @version 0.1
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "folder_manager.h"

#include <QMutex>

FolderManager *FolderManager::instance_ = nullptr;

FolderManager::FolderManager(QObject *parent) : QObject(parent) {}

FolderManager::~FolderManager() = default;

FolderManager *FolderManager::instance(QObject *parent) {
    if (instance_ == nullptr) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if (instance_ == nullptr) {
            instance_ = new FolderManager(parent);
        }
        locker.unlock();
    }
    return instance_;
}

QString FolderManager::currentFolder() const {
    return currentFolder_;
}

void FolderManager::setCurrentFolder(const QString &currentFolder) {
    if (currentFolder_ != currentFolder) {
        currentFolder_ = currentFolder;
        emit currentFolderChanged(currentFolder_);
    }
}
