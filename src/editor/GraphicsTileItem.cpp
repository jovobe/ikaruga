/*
 * GraphicsTileItem.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: Johann Arndt
 */
#include"GraphicsTileItem.hpp"


GraphicsTileItem::GraphicsTileItem(QPixmap* tileset, const QRect& rect, int index, int type) : QGraphicsPixmapItem()
{
    ///sets values and texture
    this->setPixmap(tileset->copy(rect));
    m_type = type;
    m_rect = rect;
    m_index = index;
}


void GraphicsTileItem::changeItem(QPixmap* map, QRect& rect, int type)
{
    ///changes texture and type
    this->setPixmap(map->copy(rect));
    m_type = type;
}

void GraphicsTileItem::changeItem(QPixmap* map, QRect& rect, int type, int index)
{
    ///set texture, type an tile id
    this->setPixmap(map->copy(rect));
    m_type = type;
    m_index = index;

}

int GraphicsTileItem::getType()
{
    return m_type;
}


QRect GraphicsTileItem::getRect()
{
    return m_rect;
}

GraphicsTileItem::~GraphicsTileItem()
{
}

