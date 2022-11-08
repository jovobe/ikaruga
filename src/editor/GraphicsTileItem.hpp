/*
 * GraphicsTileItem.hpp
 *
 *  Created on: Feb 23, 2016
 *      Author: Johann Arndt
 */
#ifndef GRAPHICS_TILE_ITEM_HPP
#define GRAPHICS_TILE_ITEM_HPP

#include "QGraphicsPixmapItem"
#include<iostream>

class GraphicsTileItem : public QGraphicsPixmapItem
{

public:

    /**
     * @brief creates an item with given positon type and rect and tileset
     * @param QPixmap* tileset given tileset
     * @param QRect rect  the rectangle to copy
     * @param int index the given tile id
     * @param int type the given type of the texture
     */
    GraphicsTileItem(QPixmap* tileset, const QRect& rect, int index, int type);

    /**
     * @brief changes item texture for bots and items
     * @param QPixmap map tileset
     * @param QRect& rect reference to teh given rect
     * @param int type type of the given texture
     */
    void changeItem(QPixmap* map, QRect& rect, int type);

    /**
     * @brief changes item texture for texture
     * @param QPixmap map tileset
     * @param QRect& rect reference to teh given rect
     * @param int type type of the given texture
     * @param int index the tile id
     */
    void changeItem(QPixmap* map, QRect& rect, int type, int index);

    /**
     * @brief resturns rect of the texture
     */
    QRect getRect();

    /**
     * @brief returns type of the texture
     */
    int getType();

    /**
     * @brief returns the tile id of the item
     */
    int getIndex() const
    { return m_index; }

    /**
     * @brief sets tile id
     * @param int i id to set
     */
    void setIndex(int i)
    { m_index = i; }

    /**
     * @brief deletes item
     */
    virtual ~GraphicsTileItem();

private:


    int m_index;                    /// tile index
    int m_type;                     /// type of Texture
    QRect m_rect;                    /// copied rect

};

#endif
