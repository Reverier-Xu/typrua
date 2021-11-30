/**
 * @file display_manager.h
 * @author Reverier-Xu (reverier.xu@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021 Wootec
 * 
 */

#pragma once

#include <QColor>
#include <QObject>
#include <QTimer>


class DisplayManager : public QObject {
Q_OBJECT
    Q_PROPERTY(int activeTabIndex READ activeTabIndex WRITE
                       setActiveTabIndex NOTIFY activeTabIndexChanged)
    Q_PROPERTY(bool colorStyle READ colorStyle WRITE
                       setColorStyle NOTIFY colorStyleChanged)
    Q_PROPERTY(QColor themeColor READ themeColor WRITE
                       setThemeColor NOTIFY themeColorChanged)
    Q_PROPERTY(QColor contentColor READ contentColor WRITE setContentColor NOTIFY
                       contentColorChanged)
    Q_PROPERTY(QColor alertColor READ alertColor WRITE
                       setAlertColor NOTIFY alertColorChanged)
    Q_PROPERTY(bool sideBarExpanded READ sideBarExpanded
                       WRITE setSideBarExpanded NOTIFY sideBarExpandedChanged)
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)
private:
    int activeTabIndex_ = -1;
    bool colorStyle_ = false;
    bool sideBarExpanded_ = false;
    QColor themeColor_ = QColor(0x00, 0x78, 0xd6);
    QColor alertColor_ = QColor(0xff, 0x60, 0x33);
    QString language_ = "en_US";

protected:
    explicit DisplayManager(QObject *parent);

    ~DisplayManager() override;

    void loadSettings();

    void saveSettings() const;

    static DisplayManager *instance_;

public:
    static DisplayManager *instance(QObject *parent = nullptr);

    [[nodiscard]] int activeTabIndex() const;

    void setActiveTabIndex(int n);

    [[nodiscard]] bool colorStyle() const;

    void setColorStyle(bool value);

    [[nodiscard]] bool sideBarExpanded() const;

    void setSideBarExpanded(bool value);

    [[nodiscard]] QColor themeColor() const;

    void setThemeColor(const QColor &value);

    void setThemeColor(const QString &value);

    [[nodiscard]] QColor alertColor() const;

    void setAlertColor(const QColor &value);

    void setAlertColor(const QString &value);

    [[nodiscard]] QColor contentColor() const;

    void setContentColor(const QColor &value);

    [[nodiscard]] QString language() const;

    void setLanguage(const QString &value);

signals:

    void activeTabIndexChanged(int n);

    void colorStyleChanged(bool n);

    void sideBarExpandedChanged(bool n);

    void themeColorChanged(QColor n);

    void alertColorChanged(QColor n);

    void contentColorChanged(QColor n);

    void languageChanged(QString n);

};
