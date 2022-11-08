/*
 * LevelScene.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: Johann Arndt
 */
#include"LevelScene.hpp"

LevelScene::LevelScene(QString filename, MainWindow* window) : QGraphicsScene(window)
{

    ///Set all default values
    m_tileWidth = 40;
    m_tileHeight = 40;
    m_tileOffset = 0;
    m_numRows = 4;
    m_tilesPerRow = 10;
    m_levelWidth = 400;
    m_levelHeight = 14;
    m_tiles = new std::vector<int>[m_levelHeight];
    m_typeBackground = 3;
    m_typeItem = 2;
    m_typeBot = 1;
    m_typeTexture = 0;
    m_levelId = 0;
    m_index = 0;
    m_scrollSpeed = 2;
    m_backgroundHeight = 200;
    m_backgroundWidth = 200;
    m_lastX = 0;
    m_lastY = 0;
    m_type = m_typeTexture;
    m_mainWindow = window;
    m_color = "black";
    m_imgTexture = "../images/tileset_rocks_40x40.png";
    m_imgBackground = "../images/star_background_2_200x200.png";
    m_imgExplosion = "../images/explosions_40x40.png";
    m_imgStatusbar = "../images/font_yellow_10x10.png";
    m_imgPlayer = "../images/player_animated_55x43_transparent.png";
    m_soundfile = "../sounds/game_loop.wav";


    ///sets  default paths
    int last = (filename.lastIndexOf("/"));
    m_path = filename.mid(0, last + 1);
    int lastName = filename.lastIndexOf(".");
    m_xmlLevelName = filename.mid(last + 1, lastName - last - 1);
    m_levelName = m_xmlLevelName + ".lvl";

    ///sets default background struct
    m_background.filename = m_imgBackground.toStdString();
    m_background.scrollspeed = m_scrollSpeed;
    m_background.soundfile = m_soundfile;
    m_background.volume = 70;

    ///sets default statusbar value
    m_statusbar.filename = m_imgStatusbar.toStdString();
    m_statusbar.capitalOffset = 1;
    m_statusbar.frameHeight = 10;
    m_statusbar.frameWidth = 10;
    m_statusbar.letterCount = 26;
    m_statusbar.minusculeOffset = 2;
    m_statusbar.numberOffset = 0;
    m_statusbar.offsetToMid = 1;

    ///sets default player values
    m_player.frameWidth = 55;
    m_player.frameHeight = 43;
    m_player.colorOffsetX = 1320;
    m_player.colorOffsetY = 0;
    m_player.filename = m_imgPlayer.toStdString();
    m_player.fps = 12;
    m_player.maxVel = 200;
    m_player.moveForceX = 200;
    m_player.moveForceY = 200;
    m_player.numFrames = 24;
    m_player.positionX = 100;
    m_player.positionY = 100;
    m_player.collisionDamage = 25;
    m_player.health = 100;
    m_player.hitSoundFile = "../sounds/hit_mark.wav";
    m_player.hitVolume = 100;
    m_player.explosionSoundFile = "../sounds/player_explosion.wav";
    m_player.explosionVolume = 100;


    loadXml(filename);

    ///gets bots and set default bots
    m_bots = m_xml->getBots();
    m_items = m_xml->getItems();
    m_weapons = m_xml->getWeapons();
    m_bot = m_bots[0];
    m_item = m_items[0];
    m_weapon = m_weapons[0];
    m_player.stdWeapon = m_weapon;
    setNull();


    loadLevel(m_levelName);

    ///reset botView
    m_mainWindow->resetBot();
    m_mainWindow->resetPower();


    ///sets botView
    for (unsigned int i = 0; i < m_bots.size(); i++)
    {
        m_mainWindow->addBot(toQString(m_bots[i].type),
                             "Texture name   : \t" + toQString(m_bots[i].filename) + "\n" +
                             "Health         : \t" + toQString(std::to_string(m_bots[i].health)) + "\n" +
                             "Scorevalue     : \t" + toQString(std::to_string(m_bots[i].scorevalue)) + "\n" +
                             "Col_Damage     : \t" + toQString(std::to_string(m_bots[i].collisionDamage)) + "\n" +
                             "Type           : \t" + toQString(m_bots[i].npc.type) + "\n" +
                             "Std Weapon     : \t" + toQString(m_bots[i].npc.stdWeapon.type) + "\n" +
                             "Move function  : \t" + toQString(m_bots[i].npc.move_function) + "\n" +
                             "Move Value     : \t" + toQString(std::to_string(m_bots[i].npc.move_value)) + "\n" +
                             "Speed          : \t" + toQString(std::to_string(m_bots[i].npc.speed))
        );

    }


    ///sets ItemView
    for (unsigned int i = 0; i < m_items.size(); i++)
    {
        m_mainWindow->addPower(toQString(m_items[i].type),
                               "Texture name    : \t" + toQString(m_items[i].filename) + "\n" +
                               "Value           : \t" + toQString(std::to_string(m_items[i].healPercentage))
        );

    }

    ///Create TextureViews
    m_textureView = new TextureScene(window->ui->TextureView, this, window);


    ///sets MainViewScene
    window->ui->MainView->setScene(this);

    ///set the TextureViews to VisibleS
    window->ui->TextureView->setScene(m_textureView);


}

void LevelScene::loadXml(QString fileName)
{
    ///loads xml or creates a new one
    if (QFile(fileName).exists())
    {
        m_xml = new XML(fileName.toStdString());

        m_levelName = toQString(m_xml->getTileset());
        m_xmlLevelName = toQString(m_xml->getLevelname());
        m_statusbar = m_xml->getStatusbar();
        m_player = m_xml->getPlayer();
        m_background = m_xml->getBackground();
        m_bots = m_xml->getBots();
        m_levelId = m_xml->getId();
        m_levelBots = m_xml->getLevelBots();
        m_levelItems = m_xml->getLevelItems();
    }
    else
    {
        m_xml = new XML();
        m_xml->setFilename(fileName.toStdString());
        m_xml->save();
        delete m_xml;
        m_xml = new XML(fileName.toStdString());
    }

}

void LevelScene::saveXml(QString fileName)
{
    ///saves the xml and level
    m_xml->setFilename(fileName.toStdString());
    m_xml->setTileset(m_levelName.toStdString());
    m_xml->setLevelname(m_xmlLevelName.toStdString());
    m_xml->setId(m_levelId);
    m_xml->setLevelBots(m_levelBots);
    m_xml->setLevelItems(m_levelItems);
    m_xml->setBackground(m_background);
    m_xml->setStatusbar(m_statusbar);
    m_xml->setPlayer(m_player);
    m_xml->setExplosions(m_imgExplosion.toStdString());

    m_xml->save();

    saveLevel(m_levelName);

}

void LevelScene::loadLevel(QString fileName)
{
    //open file
    QFile file(m_path + fileName);

    //readonly file open
    if (file.open(QIODevice::ReadOnly))
    {

        QTextStream in(&file);

        ///Filename
        QString line = in.readLine();

        m_pixmap = new QPixmap(m_path + m_imgTexture);

        ///list that contains all values
        QStringList list;

        ///lvl properties
        line = in.readLine();
        list = line.split(" ");
        m_tileWidth = list[0].toInt();
        m_tileHeight = list[1].toInt();
        m_tilesPerRow = list[2].toInt();
        m_numRows = list[3].toInt();
        m_tileOffset = list[4].toInt();
        m_levelWidth = list[5].toInt();
        m_levelHeight = 14;

        ///sets Background
        setBackgroundSize(m_levelWidth);

        setTileSettings(0, 0, QRect(0, 0, 40, 40));

        ///sets Labels of the Gui
        m_mainWindow->ui->level_size->setValue(m_levelWidth);
        m_mainWindow->ui->level_id->setValue(m_levelId);
        m_mainWindow->ui->level_name->setText(m_xmlLevelName);
        m_mainWindow->ui->level_name_label->setText(m_xmlLevelName);

        // Read tile indices
        for (int i = 0; i < m_levelHeight; i++)
        {
            line = in.readLine();
            list = line.split(" ");

            if (list.length() == m_levelWidth)
            {
                for (int j = 0; j < m_levelWidth; j++)
                {
                    ///puts tile_id in m_tiles
                    m_tiles[i].push_back(list[j].toInt() - 1);

                    ///creates Qrect if m_tiles >=0
                    if (m_tiles[i][j] >= 0)
                    {
                        ///Creates Rect for GraphicsTileItem
                        QRect rect((m_tileWidth) * (m_tiles[i][j] % m_tilesPerRow),
                                   (m_tileHeight) * ((int) (m_tiles[i][j] / m_tilesPerRow)),
                                   m_tileWidth,
                                   m_tileHeight);

                        ///creates new GraphicsTileItem
                        GraphicsTileItem* item = new GraphicsTileItem(m_pixmap, rect, m_tiles[i][j], m_typeTexture);

                        ///sets Position of the rect and adds it to the scene
                        item->setPos(m_tileWidth * j, m_tileHeight * i);
                        this->addItem(item);
                    }
                }
            }
        }
        ///file close
        file.close();

        ///renders bots and items
        for (unsigned int i = 0; i < m_levelBots.size(); i++)
        {

            QList<QGraphicsItem*> item_list = items(m_levelBots[i].positionX, m_levelBots[i].positionY,
                                                    m_levelBots[i].type.frameWidth, m_levelBots[i].type.frameHeight);
            while (!item_list.empty() &&
                   (dynamic_cast<GraphicsTileItem*>(item_list.first()))->getType() == m_typeBackground)
            {
                item_list.removeFirst();
            }

            if (item_list.empty())
            {
                QRect rect;
                if (m_levelBots[i].color == "white")
                {
                    QRect tmp(0, 0, m_levelBots[i].type.frameWidth, m_levelBots[i].type.frameHeight);
                    rect = tmp;
                }
                else
                {
                    QRect tmp(m_levelBots[i].type.colorOffsetX,
                              m_levelBots[i].type.colorOffsetY,
                              m_levelBots[i].type.frameWidth,
                              m_levelBots[i].type.frameHeight);
                    rect = tmp;
                }

                QPixmap* map = new QPixmap(toQString(m_path.toStdString() + m_levelBots[i].type.filename));
                GraphicsTileItem* item = new GraphicsTileItem(map, rect, 0, m_typeBot);
                item->setPos(m_levelBots[i].positionX, m_levelBots[i].positionY);
                this->addItem(item);
                delete map;

            }
            else
            {
                std::cerr << "Failed to load bot" << std::endl;
            }
        }

        for (unsigned int i = 0; i < m_levelItems.size(); i++)
        {

            QList<QGraphicsItem*> item_list = items(m_levelItems[i].positionX,
                                                    m_levelItems[i].positionY,
                                                    m_levelItems[i].type.frameWidth,
                                                    m_levelItems[i].type.frameHeight);
            while (!item_list.empty() &&
                   (dynamic_cast<GraphicsTileItem*>(item_list.first()))->getType() == m_typeBackground)
            {
                item_list.removeFirst();
            }
            if (item_list.empty())
            {
                QRect rect(0, 0, m_levelItems[i].type.frameWidth, m_levelItems[i].type.frameHeight);

                QPixmap* map = new QPixmap(toQString(m_path.toStdString() + m_levelItems[i].type.filename));
                GraphicsTileItem* item = new GraphicsTileItem(map, rect, 0, m_typeItem);
                item->setPos(m_levelItems[i].positionX, m_levelItems[i].positionY);
                this->addItem(item);
                delete map;
            }
            else
            {
                std::cerr << "Failed to load item" << std::endl;
            }
        }
    }

    else
    {
        ///creates new level
        for (int i = 0; i < m_levelHeight; i++)
        {
            for (int j = 0; j < m_levelWidth; j++)
            {
                if (i == 0)
                {
                    m_tiles[i].push_back(3);
                }
                else if (i == 1)
                {
                    m_tiles[i].push_back(7);
                }
                else if (i < m_levelHeight - 2)
                {
                    m_tiles[i].push_back(-1);
                }
                else if (i == m_levelHeight - 2)
                {
                    m_tiles[i].push_back(0);
                }
                else if (i == m_levelHeight - 1)
                { m_tiles[i].push_back(5); }
            }
        }
        ///file close
        file.close();

        saveLevel(m_levelName);
        loadLevel(fileName);
    }
}

void LevelScene::saveLevel(QString fileName)
{
    ///save all level data to .lvl file
    QFile readfile(m_path + fileName);
    QTextStream write(&readfile);

    if (readfile.open(QFile::WriteOnly | QFile::Text))
    {
        write << m_imgTexture << "\n";
        write << m_tileWidth << " ";
        write << m_tileHeight << " ";
        write << m_tilesPerRow << " ";
        write << m_numRows << " ";
        write << m_tileOffset << " ";
        write << m_levelWidth << "\n";

        for (int i = 0; i < m_levelHeight; i++)
        {
            for (int j = 0; j < m_levelWidth; j++)
            {
                ///puts tile_id in m_tiles
                if (j != m_levelWidth - 1)
                {
                    write << m_tiles[i][j] + 1 << " ";
                }
                else
                { write << m_tiles[i][j] + 1; }
            }
            write << "\n";
        }

        readfile.close();
    }
}

void LevelScene::setItem(QGraphicsSceneMouseEvent* event)
{
    ///manages mousecallbacks
    int x = event->scenePos().x() / m_tileWidth;
    int y = event->scenePos().y() / m_tileHeight;


    int height;
    int width;

    ///gets height and with of item
    if (!m_bot.filename.empty() && event->buttons() == Qt::LeftButton)
    {
        height = m_bot.frameHeight;
        width = m_bot.frameWidth;
    }
    else if (!m_item.filename.empty() && event->buttons() == Qt::LeftButton)
    {
        height = m_item.frameHeight;
        width = m_item.frameWidth;
    }
    else
    {
        height = m_tileHeight;
        width = m_tileWidth;
    }

    int offset = width % m_tileWidth == 0 ? 0 : 1;

    ///looking for bad positions
    if (x >= 0 && y >= 0 && (x - 1 + (width / m_tileWidth) + offset) < m_levelWidth &&
        (y - 1 + (height / m_tileHeight) + offset) < m_levelHeight)
    {
        ///last know position of item
        m_lastX = x;
        m_lastY = y;
        QList<QGraphicsItem*> item_list = items(x * m_tileWidth, y * m_tileHeight, width, height);

        for (int i = 0; i < item_list.size(); i++)
        {
            if (!item_list.empty() && (dynamic_cast<GraphicsTileItem*>(item_list[i]))->getType() == m_typeBackground)
            {
                item_list.removeAt(i--);
            }
        }
        ///delets item or bots
        if (item_list.size() == 1)
        {
            x = item_list.first()->x() / m_tileWidth;
            y = item_list.first()->y() / m_tileHeight;


            m_lastX = x;
            m_lastY = y;

            if ((dynamic_cast<GraphicsTileItem*>(item_list.first()))->getType() == m_typeBot)
            {
                m_tiles[y][x] = -1;
                for (unsigned int i = 0; i < m_levelBots.size(); i++)
                {
                    if (m_levelBots[i].positionX == x * m_tileWidth && m_levelBots[i].positionY == y * m_tileWidth)
                    {
                        if (event->buttons() == Qt::LeftButton)
                        {
                            m_color = m_levelBots[i].color;

                            if (m_color == "black")
                            {
                                m_color = "white";
                            }
                            else
                            { m_color = "black"; }

                        }
                        m_levelBots.erase(m_levelBots.begin() + i);
                    }
                }
            }

            if ((dynamic_cast<GraphicsTileItem*>(item_list.first()))->getType() == m_typeItem)
            {
                m_tiles[y][x] = -1;
                for (unsigned int i = 0; i < m_levelItems.size(); i++)
                {
                    if (m_levelItems[i].positionX == x * m_tileWidth && m_levelItems[i].positionY == y * m_tileWidth)
                    {
                        m_levelItems.erase(m_levelItems.begin() + i);
                    }
                }
            }
        }
        ///sets texture and includes bot and items
        if (event->buttons() == Qt::LeftButton)
        {
            ///if there is an item write new rect to that Item else create a new Item and set rect
            if (item_list.size() == 1)
            {

                if (!m_bot.filename.empty())
                {

                    m_item.filename.clear();
                    QRect rect;
                    if (m_color == "white")
                    {
                        QRect tmp(0, 0, m_bot.frameWidth, m_bot.frameHeight);
                        rect = tmp;
                    }
                    else
                    {
                        QRect tmp(m_bot.colorOffsetX, m_bot.colorOffsetY, m_bot.frameWidth, m_bot.frameHeight);
                        rect = tmp;
                    }

                    QPixmap* map = new QPixmap(toQString(m_path.toStdString() + m_bot.filename));
                    (dynamic_cast<GraphicsTileItem*>(item_list.first()))->changeItem(map, rect, m_typeBot);
                    delete map;

                    m_tiles[y][x] = -1;
                    XML::LevelBot bot;

                    bot.color = m_color;

                    bot.positionX = x * m_tileWidth;
                    bot.positionY = y * m_tileHeight;
                    bot.powerUpName = m_items[0].type;
                    bot.powerUpProb = 20;
                    bot.type = m_bot;

                    m_levelBots.push_back(bot);

                }
                else if (!m_item.filename.empty())
                {

                    QRect rect(0, 0, m_item.frameWidth, m_item.frameHeight);

                    m_bot.filename.clear();

                    m_tiles[y][x] = -1;
                    QPixmap* map = new QPixmap(toQString(m_path.toStdString() + m_item.filename));
                    (dynamic_cast<GraphicsTileItem*>(item_list.first()))->changeItem(map, rect, m_typeItem);
                    delete map;

                    XML::LevelItem item;
                    item.positionX = x * m_tileWidth;
                    item.positionY = y * m_tileHeight;
                    item.type = m_item;
                    item.value = 50;

                    m_levelItems.push_back(item);

                }
                else
                {
                    (dynamic_cast<GraphicsTileItem*>(item_list.first()))->changeItem(m_pixmap, m_rect, m_type,
                                                                                     m_index);
                    m_tiles[y][x] = m_index;
                    setNull();
                }
            }

                // if item_list is empty create new bot item or texture
            else if (item_list.empty())
            {
                ///creates a new Item and update View
                GraphicsTileItem* item = new GraphicsTileItem(m_pixmap, m_rect, m_index, m_type);

                if (!m_bot.filename.empty())
                {
                    m_item.filename.clear();
                    QRect rect;

                    if (m_color == "white")
                    {
                        QRect tmp(0, 0, m_bot.frameWidth, m_bot.frameHeight);
                        rect = tmp;
                    }
                    else
                    {
                        QRect tmp(m_bot.colorOffsetX, m_bot.colorOffsetY, m_bot.frameWidth, m_bot.frameHeight);
                        rect = tmp;
                    }

                    QPixmap* map = new QPixmap(toQString(m_path.toStdString() + m_bot.filename));
                    item->changeItem(map, rect, m_typeBot);

                    m_tiles[y][x] = -1;

                    XML::LevelBot bot;

                    bot.color = m_color;
                    bot.positionX = x * m_tileWidth;
                    bot.positionY = y * m_tileHeight;
                    bot.powerUpName = m_items[0].type;
                    bot.powerUpProb = 20;
                    bot.type = m_bot;

                    m_levelBots.push_back(bot);
                }
                else if (!m_item.filename.empty())
                {
                    m_bot.filename.clear();
                    QRect rect(0, 0, m_item.frameWidth, m_item.frameHeight);

                    m_tiles[y][x] = -1;
                    QPixmap* map = new QPixmap(toQString(m_path.toStdString() + m_item.filename));
                    item->changeItem(map, rect, m_typeItem);
                    delete map;

                    XML::LevelItem item;

                    item.positionX = x * m_tileWidth;
                    item.positionY = y * m_tileHeight;
                    item.type = m_item;
                    item.value = 50;

                    m_levelItems.push_back(item);

                }
                else
                {
                    setNull();
                    m_tiles[y][x] = m_index;
                }

                item->setPos(m_tileWidth * x, m_tileHeight * y);
                this->addItem(item);
            }
        }

        else if (item_list.size() == 1 && event->buttons() == Qt::RightButton)
        {
            m_tiles[y][x] = -1;
            this->removeItem(item_list.first());
            delete item_list.first();
        }
        m_mainWindow->ui->MainView->viewport()->update();
    }

}

void LevelScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    ///looks for mousemovements
    int x = event->scenePos().x() / m_tileWidth;
    int y = event->scenePos().y() / m_tileHeight;

    if (x >= 0 && y >= 0 && x < m_levelWidth && y < m_levelHeight)
    {
        QList<QGraphicsItem*> item_list = items(x * m_tileWidth, y * m_tileHeight, m_tileWidth, m_tileHeight);

        while (!item_list.empty() &&
               (dynamic_cast<GraphicsTileItem*>(item_list.first()))->getType() == m_typeBackground)
        {
            item_list.removeFirst();
        }

        if (!item_list.empty())
        {
            x = item_list.first()->x() / m_tileWidth;
            y = item_list.first()->y() / m_tileHeight;
        }
    }

    if (!(m_lastX == x && m_lastY == y))
    {
        m_lastX = x;
        m_lastY = y;
        setItem(event);
    }
}

void LevelScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    setItem(event);
}

QString LevelScene::toQString(std::string string)
{
    return QString::fromUtf8(string.c_str());
}

QPixmap* LevelScene::getPixmap()
{
    return m_pixmap;
}

void LevelScene::setTileSettings(int index, int type, QRect rect)
{
    ///sets textureType
    m_index = index;
    m_type = type;
    m_rect = rect;
}

void LevelScene::setBackgroundSize(int m_levelWidth)
{

    ///sets new backgroundsize
    QPixmap* map = new QPixmap(m_path + m_imgBackground);


    int height = (int) (m_levelHeight * m_tileHeight / m_backgroundHeight) + 1;
    int width = (int) (m_levelWidth * m_tileWidth / m_backgroundWidth) + 1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            if (i < height - 1)
            {
                QRect rect(0, 0, m_backgroundWidth, m_backgroundHeight);
                GraphicsTileItem* item = new GraphicsTileItem(map, rect, 0, m_typeBackground);
                item->setPos(j * m_backgroundWidth, i * m_backgroundHeight);
                this->addItem(item);
            }
            else
            {
                QRect rect(0, 0, m_backgroundWidth, (m_levelHeight * m_tileHeight) % (m_backgroundHeight + 1));
                GraphicsTileItem* item = new GraphicsTileItem(map, rect, 0, m_typeBackground);
                item->setPos(j * m_backgroundWidth, i * m_backgroundHeight);
                this->addItem(item);
            }
        }
    }


    setSceneRect();
    m_mainWindow->ui->MainView->setScene(this);
    delete map;
}

void LevelScene::setSize(int value)
{

    ///resize and rerender Window
    while (!this->items().empty())
    {
        delete this->items().takeAt(0);
    }
    this->clear();

    if (value < m_levelWidth)
    {


        for (int i = 0; i < m_levelHeight; i++)
        {
            for (int j = value; j < m_levelWidth; j++)
            {
                m_tiles[i].pop_back();
            }
        }
    }

    else
    {
        for (int i = 0; i < m_levelHeight; i++)
        {
            for (int j = 0; j < value; j++)
            {

                if (i == 0)
                {
                    m_tiles[i].push_back(3);
                }
                else if (i == 1)
                {
                    m_tiles[i].push_back(7);
                }
                else if (i < m_levelHeight - 2)
                {
                    m_tiles[i].push_back(-1);
                }
                else if (i == m_levelHeight - 2)
                {
                    m_tiles[i].push_back(0);
                }
                else if (i == m_levelHeight - 1)
                { m_tiles[i].push_back(5); }
            }
        }
    }
    m_levelWidth = value;
    saveLevel("tmp.lvl");
    loadLevel("tmp.lvl");
    QFile(m_path + "tmp.lvl").deleteLater();
    m_mainWindow->ui->MainView->setScene(this);

}

void LevelScene::setSceneRect()
{
    //resize SceneRect(scrollbar fix)
    m_mainWindow->ui->MainView->setSceneRect(m_mainWindow->ui->MainView->sceneRect().x(),
                                             m_mainWindow->ui->MainView->sceneRect().y(),
                                             m_tileWidth * m_levelWidth,
                                             m_tileHeight * m_levelHeight);
}

void LevelScene::setBot(QString botName)
{
    for (unsigned int i = 0; i < m_bots.size(); i++)
    {
        if (m_bots[i].type == botName.toStdString())
        {
            m_bot = m_bots[i];
        }
    }
    m_item.filename.clear();
}

void LevelScene::setPower(QString powerName)
{
    for (unsigned int i = 0; i < m_items.size(); i++)
    {
        if (m_items[i].type == powerName.toStdString())
        {
            m_item = m_items[i];
        }
    }
    m_bot.filename.clear();
}

void LevelScene::setId(int id)
{
    m_levelId = id;
    m_mainWindow->ui->level_id->setValue(m_levelId);
}

void LevelScene::setLevelName(QString levelName)
{
    m_xmlLevelName = levelName;
    m_mainWindow->ui->level_name->setText(m_xmlLevelName);
    m_mainWindow->ui->level_name_label->setText(m_xmlLevelName);
}

void LevelScene::setNull()
{
    m_bot.filename.clear();
    m_item.filename.clear();
}

LevelScene::~LevelScene()
{
    while (!this->items().empty())
    {
        delete this->items().takeAt(0);
    }
    this->clear();

    delete m_textureView;
    delete[] m_tiles;
    delete m_xml;
}
