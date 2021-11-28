/**
 * @file entry.cxx
 * @author Reverier-Xu (reverier.xu@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021 Wootec
 * 
 */

#include <QApplication>
#include <QFont>
#include <QIcon>
#include <QtWebEngine>

#ifdef __unix__

#include <malloc.h>

#endif

#include "managers/app_manager.h"

int main(int argc, char *argv[]) {
#ifdef Q_OS_LINUX
    mallopt(M_ARENA_MAX, 1);
#endif
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QtWebEngine::initialize();

    QApplication app(argc, argv);

    QApplication::setApplicationDisplayName("TypRua");
    QApplication::setApplicationName("TypRua");
    QApplication::setOrganizationName("Wootec");
    QApplication::setOrganizationDomain("woooo.tech");
    QApplication::setWindowIcon(QIcon(":/assets/logo.svg"));


    auto main_app = AppManager();
    main_app.initialize();

    return QApplication::exec();
}

