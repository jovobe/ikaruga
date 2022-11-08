/*
 * LevelScene.hpp
 *
 *  Created on: Feb 23, 2016
 *      Author: Johann Arndt
 */
#ifndef LEVELSCENE_HPP
#define LEVELSCENE_HPP

#include<string>
#include"QGraphicsScene"
#include"QGraphicsView"
#include"QGraphicsItem"
#include<QTextStream>
#include<QFile>
#include"MainWindow.hpp"
#include"GraphicsTileItem.hpp"
#include<QGraphicsSceneMouseEvent>
#include<iostream>
#include "TextureScene.hpp"
#include"../xml/XML.hpp"


class MainWindow;

class TextureScene;

class LevelScene : public QGraphicsScene
{
public:

    /**
     * @brief constructor for levelscene sets default params and setting the view
     * @param QString filename path of the file to change
     * @param MainWindow* window editor window
     */
    LevelScene(QString filename, MainWindow* window);

    /**
     * @brief sets the settings of the last clicked tile in the texture window
     * @param int index it is the tile_id
     * @param int type  it is the type of the texture
     * @param QRect rect the rect of the tilesheet to render
     */
    void setTileSettings(int index, int type, QRect rect);

    /**
     * @brief saves the .lvl file
     * @param QString filename name of the .lvl file
     */
    void saveLevel(QString fileName);

    /**
     * @brief saves the XML file
     * @param QString fileName name of the XML file
     * @param
     */
    void saveXml(QString fileName);

    /**
     * @brief loads the XML file or creates a new one
     * @param QString fileName name of the XML file
     * @param
     */
    void loadXml(QString fileName);

    /**
     * @brief loads the .lvl file or creates a new one
     * @param QString filename name of the .lvl file
     */
    void loadLevel(QString fileName);

    /**
     * @brief sets the Size of the MainView and updates scene
     * @param int value length of the new file
     */
    void setSize(int value);

    /**
     * @brief sets last clicked bot
     * @param QString name of the bot
     */
    void setBot(QString botName);

    /**
     * @brief sets last clicked power up
     * @param QString powerName name of the power up
     */
    void setPower(QString powerName);

    /**
     * @brief sets item and bot null
     */
    void setNull();

    /**
     * @brief sets level Id
     * @param int id  the id of the level
     */
    void setId(int id);

    /**
     * @brief  sets teh level Name seen in the menue
     * @param QString levelName
     */
    void setLevelName(QString levelName);

    /**
     * @brief sets the size of the Background
     * @param int levelWidth the Width of the level
     */
    void setBackgroundSize(int levelWidth);

    /**
     * @brief sets the item or removes it in the view by mousecallback
     * @param QGraphicsSceneMouseEvent *event mousecallback event
     */
    void setItem(QGraphicsSceneMouseEvent* event);

    /**
     * @brief converts std::string to QString
     * @param std::string string string to convert
     */
    QString toQString(std::string string);

    /**
     * @brief returns pixmap (texture)
     */
    QPixmap* getPixmap();

    virtual ~LevelScene();

protected:

    /**
     * @brief is called when mouse is pressed
     * @param QGraphicsSceneMouseEvent * event given mouse action
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

    /**
     * @brief is called when mouse is moved and pressed
     * @param QGraphicsSceneMouseEvent * event given mouse action
     */
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

private:
    void setSceneRect();

    QRect m_rect;                                    /// last copied rect
    QPixmap* m_pixmap;                            /// A QPixmap to store the tile bitmap
    QString m_path;                                    /// path to levels directory
    XML* m_xml;                                        /// xml object for XML library
    QString m_levelName;                            /// name of .lvl file
    QString m_imgTexture;                            /// path of the tile texture
    QString m_imgBackground;                        /// path of the background texture
    QString m_imgExplosion;                         /// path of the explosion texture
    QString m_imgStatusbar;                            /// path of the statusbar texture
    QString m_imgPlayer;                            /// path of the player texture
    QString m_xmlLevelName;                            /// name of the level
    std::string m_soundfile;                        /// path of the background soundfile
    std::string m_color;                            /// color to render bots
    std::vector<XML::LevelBot> m_levelBots;            /// bots for the xml file
    std::vector<XML::LevelItem> m_levelItems;        /// items for the xml file
    std::vector<XML::Bot> m_bots;                    /// properties of bots
    std::vector<XML::Item> m_items;                    /// properties of items
    std::vector<XML::Weapon> m_weapons;                /// properties of weapons
    XML::Item m_item;                                /// item to set in the mainView
    XML::Bot m_bot;                                    /// bot to set in the mainView
    XML::Weapon m_weapon;                            /// weapons to set in the xml file
    XML::Background m_background;                    /// background properties for xml file
    XML::Statusbar m_statusbar;                        /// statusbar properties for the xml file
    XML::Player m_player;                            /// player properties for the xml file
    std::vector<int>* m_tiles;                        /// The 2D tile array
    TextureScene* m_textureView;                    /// TextureScene pointer;
    int m_typeBackground;                            /// int for background type
    int m_typeItem;                                    /// int for item type
    int m_typeBot;                                    /// int for bot type
    int m_typeTexture;                                /// int for texture type
    int m_scrollSpeed;                              /// background scrollspeed
    int m_index;                                    /// Tile id
    int m_type;                                     /// texture type
    int m_tileWidth;                                /// Width of the tiles
    int m_tileHeight;                               /// Height of the tiles
    int m_tilesPerRow;                              /// Tiles per row in the tile bitmap
    int m_numRows;                                  /// Number of rows in the tile bitmap
    int m_tileOffset;                               /// Offset between the tiles
    int m_levelWidth;                               /// Level width in tiles
    int m_levelHeight;                              /// Level height in tiles
    int m_levelId;                                  /// Level id
    int m_backgroundHeight;                            /// background tile height
    int m_backgroundWidth;                            /// backgoround tile Width
    int m_lastX;                                    /// x position of last known item
    int m_lastY;                                    /// y position of last known item
    MainWindow* m_mainWindow;                       /// Pointer to a main window

};

#endif
