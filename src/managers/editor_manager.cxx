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

#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMimeData>
#include <QMimeDatabase>
#include <QMimeType>
#include <QMutex>
#include <QStandardPaths>
#include <QTextStream>
#include <QUrl>
#include <QUuid>

#include "folder_manager.h"

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

QString EditorManager::exportedFile() const { return exportedFile_; }

void EditorManager::setExportedFile(const QString& exportedFile) {
    if (exportedFile_ != exportedFile) {
        exportedFile_ = exportedFile;
        emit exportedFileChanged(exportedFile_);
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
        if (!currentFile_.isEmpty()) save();
    }
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
        qDebug() << "external set content: " << content;
        emit contentChanged(content);
    }
}

void EditorManager::save() {
    QFile file(currentFilePath_);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << content_;
        file.close();
    } else {
        emit savePathRequested();
    }
}

void EditorManager::saveAs(const QString& filePath) {
    setCurrentFilePath(filePath);
    setCurrentFile(QFileInfo(filePath).fileName());
    save();
}

void EditorManager::open(const QString& filePath) {
    auto realFilePath = getLocalFilePath(filePath);
    QFile file(realFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        setCurrentFilePath(realFilePath);
        setCurrentFile(QFileInfo(realFilePath).fileName());
        externalSetContent(in.readAll());
        file.close();
    }
}

void EditorManager::openFolder(const QString& folderPath) {
    setCurrentFilePath(folderPath);
}

void EditorManager::close() {
    setCurrentFilePath("");
    setCurrentFile("");
    externalSetContent("");
}

void EditorManager::exportAs(const QString& filePath) {
    // qDebug() << exportedFile() << " exportAs " << filePath;
    QFile::copy(exportedFile(), filePath);
}

QString EditorManager::getLocalFilePath(const QString& urlFilePath) {
    QUrl url(urlFilePath);
    QString localFilePath = url.toLocalFile();
    if (localFilePath.isEmpty()) {
        localFilePath = urlFilePath;
    }
    return localFilePath;
}

void EditorManager::handleDrop(const QString& path) {
    // qDebug() << path;
    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile(path);
    // qDebug() << mime.name();
    if (mime.name().startsWith("image/")) {
        auto insertedMd = "![image](" + path + ")\n";
        emit pasteRequested(insertedMd);
    } else if (mime.name().startsWith("text/")) {
        // qDebug() << "Opening markdown file: " << path;
        open(path);
    } else {
        return;
    }
}

void EditorManager::requirePaste() {
    const QClipboard* clipboard = QApplication::clipboard();
    const QMimeData* mimeData = clipboard->mimeData();

    qDebug() << "requirePaste";

    if (mimeData->hasImage()) {
        QString cachePath = currentFilePath();
        if (cachePath.isEmpty()) {
            cachePath =
                QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
        }
        QString imagePath = cachePath + "/" + QUuid::createUuid().toString() +
                            ".png";
        QFile file(imagePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(mimeData->imageData().toByteArray());
            file.close();
            auto insertedMd = "![image](" + imagePath + ")\n";
            emit pasteRequested(insertedMd);
        }
    } else if (mimeData->hasText()) {
        QString text = mimeData->text();
        emit pasteRequested(text);
    }
}

void EditorManager::requestOpen() {
    emit openFilePathRequested();
}
