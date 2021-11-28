/**
 * @file display_manager.cxx
 * @author Reverier-Xu (reverier.xu@outlook.com)
 * @brief
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Wootec
 *
 */

#include "display_manager.h"

#include <QMutex>
#include <QSettings>

DisplayManager* DisplayManager::instance_ = nullptr;

DisplayManager* DisplayManager::instance(QObject* parent) {
    if (instance_ == nullptr) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if (instance_ == nullptr) instance_ = new DisplayManager(parent);
        locker.unlock();
    }
    return instance_;
}

DisplayManager::DisplayManager(QObject* parent) : QObject(parent) {
    this->loadSettings();
}

DisplayManager::~DisplayManager() { this->saveSettings(); }

void DisplayManager::loadSettings() {
    QSettings settings;
    settings.beginGroup("Display");
    this->setThemeColor(settings.value("ThemeColor", "#0078d6").toString());
    this->setAlertColor(settings.value("AlertColor", "#ff6033").toString());
    this->setColorStyle(settings.value("ColorStyle", true).toBool());
    settings.endGroup();
}

void DisplayManager::saveSettings() const {
    QSettings settings;
    settings.beginGroup("Display");
    settings.setValue("ThemeColor", this->themeColor().name());
    settings.setValue("AlertColor", this->alertColor().name());
    settings.setValue("ColorStyle", this->colorStyle());
    settings.endGroup();

    settings.sync();
}

int DisplayManager::activeTabIndex() const { return activeTabIndex_; }

void DisplayManager::setActiveTabIndex(int n) {
    activeTabIndex_ = n;
    emit activeTabIndexChanged(n);
}

bool DisplayManager::colorStyle() const { return colorStyle_; }

void DisplayManager::setColorStyle(bool value) {
    colorStyle_ = value;
    emit colorStyleChanged(value);
    emit contentColorChanged(contentColor());
}

bool DisplayManager::sideBarExpanded() const { return sideBarExpanded_; }

void DisplayManager::setSideBarExpanded(bool value) {
    sideBarExpanded_ = value;
    emit sideBarExpandedChanged(value);
}

QColor DisplayManager::themeColor() const { return themeColor_; }

void DisplayManager::setThemeColor(const QColor& value) {
    themeColor_ = value;
    emit themeColorChanged(value);
}

void DisplayManager::setThemeColor(const QString& value) {
    themeColor_.setNamedColor(value);
    emit themeColorChanged(value);
}

QColor DisplayManager::alertColor() const { return alertColor_; }

void DisplayManager::setAlertColor(const QColor& value) {
    alertColor_ = value;
    emit alertColorChanged(value);
}

void DisplayManager::setAlertColor(const QString& value) {
    alertColor_.setNamedColor(value);
    emit alertColorChanged(value);
}

QColor DisplayManager::contentColor() const {
    return colorStyle() ? QColor("#222222") : QColor("#EEEEEE");
}

void DisplayManager::setContentColor(const QColor& value) {
    emit contentColorChanged(contentColor());
}
