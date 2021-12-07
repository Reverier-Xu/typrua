/**
 * @file editor_manager.h
 * @author Reverier-Xu (reverier.xu@outlook.com)
 * @brief
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright Copyright (c) 2021 Wootec
 *
 */

#pragma once

#include <QObject>

class EditorManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString currentFile READ currentFile WRITE setCurrentFile NOTIFY
                   currentFileChanged)
    Q_PROPERTY(QString exportedFile READ exportedFile WRITE setExportedFile NOTIFY
                   exportedFileChanged)
    Q_PROPERTY(QString currentFilePath READ currentFilePath WRITE
                   setCurrentFilePath NOTIFY currentFilePathChanged)
    Q_PROPERTY(
        QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(
        bool isOpened READ isOpened WRITE setOpened NOTIFY isOpenedChanged)

   private:
    QString currentFile_;
    QString exportedFile_;
    QString currentFilePath_;
    QString content_;
    bool isOpened_;

   protected:
    static EditorManager *instance_;
    explicit EditorManager(QObject *parent);
    ~EditorManager() override;

   public:
    static EditorManager *instance(QObject *parent = nullptr);

    [[nodiscard]] QString currentFile() const;
    void setCurrentFile(const QString &currentFile);

    [[nodiscard]] QString exportedFile() const;
    void setExportedFile(const QString &exportedFile);

    [[nodiscard]] QString currentFilePath() const;
    void setCurrentFilePath(const QString &currentFilePath);

    [[nodiscard]] QString content() const;
    void setContent(const QString &content);

    [[nodiscard]] bool isOpened() const;
    void setOpened(bool opened);

   public slots:
    Q_INVOKABLE void externalSetContent(const QString &content);

    Q_INVOKABLE void save();

    Q_INVOKABLE void saveAs(const QString &filePath);

    Q_INVOKABLE void requestOpen();

    Q_INVOKABLE void open(const QString &filePath);

    Q_INVOKABLE void openFolder(const QString &folderPath);

    Q_INVOKABLE void close();

    Q_INVOKABLE void exportAs(const QString &filePath);

    Q_INVOKABLE QString getLocalFilePath(const QString &urlFilePath);

    Q_INVOKABLE void handleDrop(const QString &path);

    Q_INVOKABLE void requirePaste();

   signals:
    void currentFileChanged(const QString &currentFile);
    void exportedFileChanged(const QString &exportedFile);
    void currentFilePathChanged(const QString &currentFilePath);
    void contentChanged(const QString &content);
    void isOpenedChanged(bool opened);
    void pasteRequested(const QString &content);
    void savePathRequested();
    void openFilePathRequested();
};
