/*
 * TextureScene.hpp
 *
 *  Created on: Feb 23, 2016
 *      Author: Johann Arndt
 */

#ifndef LEVELVIEW_TEXTURESCENE_HPP
#define LEVELVIEW_TEXTURESCENE_HPP

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
#include"LevelScene.hpp"

class MainWindow;

class LevelScene;

class TextureScene : public QGraphicsScene
{
public:

    /**
     * @brief creates a new scene for the texture field
     * @param QGraphicsView* View the given View to set
     * @param LevelScene* level the given mainScene for setting values in the LevelScene
     */
    TextureScene(QGraphicsView* View, LevelScene* level, MainWindow* window);

    /**
     * @brief default constructor
     */
    TextureScene()
    { };

    /**
     * @brief returns the Scene
     */
    QGraphicsScene* getScene();

    /**
     * @brief
     */
    virtual ~TextureScene();

protected:

    /**
    * @brief overrides the last know texture id in the levelScene
    * @param QGraphicsSceneMouseEvent * event mouse event
    */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:

    LevelScene* m_levelScene;   /// Scene of the Main View
    int m_tileWidth;            /// Width of the tiles
    int m_tileHeight;           /// Height of the tiles
    int m_tilesPerRow;          /// Tiles per row in the tile bitmap
    int m_numRows;              /// Number of rows in the tile bitmap
    int m_textureHeight;        /// Level width (in tiles)
    int m_textureWidth;         /// Level height in tiles
    int m_type = 0;               /// type of the item

};

#endif //LEVELVIEW_TEXTURESCENE_HPP
