/**
 * @file gui_manager.h
 * @author Reverier-Xu (reverier.xu@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021 Wootec
 * 
 */

#pragma once


#include <QObject>
#include <QQmlApplicationEngine>


class GuiManager : public QObject {
    Q_OBJECT
   private:
    QQmlApplicationEngine* uiEngine_{};

   protected:
    static GuiManager* instance_;
    explicit GuiManager(QObject* parent=nullptr);
    ~GuiManager() override;

   public:
    static GuiManager* instance(QObject* parent=nullptr);

    void createUi();

    void exportManagers();
};
