/**
 * @file editor_manager.cxx
 * @author Reverier-Xu (reverier.xu@outlook.com)
 * @brief
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright Copyright (c) 2021 Wootec
 *
 */

#include "editor_manager.h"

#include <QMutex>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>

EditorManager* EditorManager::instance_ = nullptr;

EditorManager::EditorManager(QObject* parent) : QObject(parent) {}

EditorManager::~EditorManager() = default;

EditorManager* EditorManager::instance(QObject* parent) {
    if (instance_ == nullptr) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if (instance_ == nullptr) {
            instance_ = new EditorManager(parent);
        }
        locker.unlock();
    }
    return instance_;
}

QString EditorManager::currentFile() const { return currentFile_; }

void EditorManager::setCurrentFile(const QString& currentFile) {
    if (currentFile_ != currentFile) {
        currentFile_ = currentFile;
        emit currentFileChanged(currentFile_);
    }
}

QString EditorManager::currentFilePath() const { return currentFilePath_; }

void EditorManager::setCurrentFilePath(const QString& currentFilePath) {
    if (currentFilePath_ != currentFilePath) {
        currentFilePath_ = currentFilePath;
        emit currentFilePathChanged(currentFilePath_);
    }
}

QString EditorManager::content() const { return content_; }

void EditorManager::setContent(const QString& content) {
    if (content_ != content) {
        content_ = content;
    }
    save();
}

bool EditorManager::isOpened() const { return isOpened_; }
void EditorManager::setOpened(bool isOpened) {
    if (isOpened_ != isOpened) {
        isOpened_ = isOpened;
        emit isOpenedChanged(isOpened_);
    }
}

void EditorManager::externalSetContent(const QString& content) {
    if (content_ != content) {
        content_ = content;
        emit contentChanged(content_);
    }
}

void EditorManager::save() {
    QFile file(currentFilePath_);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << content_;
        file.close();
    }
}

void EditorManager::saveAs(const QString& filePath) {
    setCurrentFilePath(filePath);
    save();
}

void EditorManager::open(const QString& filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        setCurrentFilePath(filePath);
        setCurrentFile(QFileInfo(filePath).fileName());
        externalSetContent(in.readAll());
        file.close();
    }
}
