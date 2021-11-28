/*
 * app_manager.h
 *
 * Summary: the whole app manager.
 * Author: Reverier-Xu <reverier.xu@outlook.com>
 *
 * Created: 2021-11-28
 *
 */

#pragma once

#include <QObject>

class AppManager : public QObject {
Q_OBJECT
private:

public:
    explicit AppManager(QObject *parent = nullptr);

    ~AppManager() override;

    void initialize();

};
