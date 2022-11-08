/*
 * MainWindow.hpp
 *
 * @author Patrick Nolte (pnolte@uni-osnabrueck.de)
 * @date 23.02.2016
 */
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "LevelView.h"
#include "QFileDialog"
#include "LevelScene.hpp"
#include <QStyleFactory>
#include <QList>
#include <QMap>
#include <QInputDialog>
#include <QMessageBox>
#include <QToolTip>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <iostream>
#include <QRegExp>

class LevelScene;

/**
 * @brief Class for displaying the MainWindow and interact with Controls
 */
class MainWindow : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT

public:
    /**
     * Constructs the MainWindow for the editor
     *
     * @param parent			ParentWindow
     * @param folderPath		Path to Sourcefolder
     */
    MainWindow(QMainWindow* parent = 0, std::string folderPath = "");

    /**
     * Destructor
     */
    virtual ~MainWindow();

    /**
     * Adds a bot to the QListWidget where enemys are listet
     *
     * @param botName			Name of the Bot
     * @param description		Information about the Bot to display at
     *                          mouseover
     */
    void addBot(QString botName, QString description);

    /**
     * Adds a powerup to the QListWidget where powerups are listet
     *
     * @param powerName			Name of the Powerup
     * @param description		Information about the Powerup to display
     *                          at mouseover
     */
    void addPower(QString powerName, QString description);

    /**
     * reset the QListWidget with enemys
     */
    void resetBot();

    /**
     * reset the QListWidget with powerups
     */
    void resetPower();

    ///Ui from Mainwindow
    Ui::MainWindow* ui;

private Q_SLOTS:

    /**
     * Slot for MenuOpen trigger, opens an existing File
     */
    void on_action_oeffnen_triggered();

    /**
     * Slot for MenuSave trigger, saves the actual File
     */
    void on_actionSpeichern_triggered();

    /**
     * Slot for MenuSaveAs trigger, saves the actual File
     * under another name
     */
    void on_actionSpeichern_unter_triggered();

    /**
     * Slot for MenuNew trigger, opens a new file
     */
    void on_actionNeu_triggered();

    /**
     * Slot for MenuLastOpened trigger, opens an old file
     * listet in lastOpenedFiles
     */
    void openLast(QAction* action);

    /**
     * Slot for resizeButton trigger, resizes the Levelwidth
     */
    void on_pushButton_released();

    /**
     * Slot for saveId trigger, saves the Levelname and ID
     */
    void on_save_id_released();

    /**
     * Slot for botlistItemClicked trigger, changes the actual
     * bot
     */
    void on_botList_itemClicked(QListWidgetItem* item);

    /**
     * Slot for powerlistItemClicked trigger, changes the actual
     * power
     */
    void on_powerList_itemClicked(QListWidgetItem* item);

private:
    ///Res Path
    std::string m_resPath;
    ///actual scene file for rendering
    LevelScene* scene;
    ///the actual opened file
    QString openedFile;
    //Map with all Opened Files (FileName,FilePath+FileName)
    QMap<QString, QString> lastOpenedFiles;

    /**
     * Opens the given file in Editor
     *
     * @param sFile     		Complete Filepath to open
     */
    void openFile(QString sFile);

    /**
     * Saves the actual Level to the given Path
     *
     * @param sFile             Complete Filepath to save
     */
    void saveFile(QString sFile);
};

#endif //MAINWINDOW_HPP
