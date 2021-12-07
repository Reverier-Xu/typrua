/**
 * @file folder_manager.h
 * @author
 * @brief
 * @version 0.1
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <QObject>
#include <QString>

class FolderManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString currentFolder READ currentFolder WRITE setCurrentFolder
                   NOTIFY currentFolderChanged)
   protected:
    QString currentFolder_;

    static FolderManager *instance_;
    explicit FolderManager(QObject *parent = nullptr);
    ~FolderManager() override;

   public:
    static FolderManager *instance(QObject *parent = nullptr);
    [[nodiscard]] QString currentFolder() const;
    void setCurrentFolder(const QString &currentFolder);

   signals:
    void currentFolderChanged(const QString &currentFolder);
};
