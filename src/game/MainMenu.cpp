/**
* @file MainMenu.cpp
* @brief Implementation of MainMenu
*
* @author Patrick Steinforth (psteinforth@uni-osnabrueck.de)
* @date 29 Feb 2016
*/
#include "MainMenu.hpp"
#include "Filesystem.hpp"

namespace ikaruga
{


    MainMenu::MainMenu(MainWindow* win, fs::path resDir) :
            m_win(win), m_resDir(resDir), m_table(0, 0, 0, 0)
    {
        boost::filesystem::path concat(resDir);
        concat /= "levels";
        m_levelFiles = Filesystem::findFiles(concat, boost::regex("^.*\\.xml$"));

        m_sound = Sound(m_resDir.string() + "/sounds/HammerFall_Renegade_8_bit.wav", SoundType::SONG);
        setupBackground(1.0f, m_resDir.string() + "/images/star_background_2_200x200.png");
        m_normalFontTexture = TextureFactory::instance(m_win->getRenderer()).getTexture(
                m_resDir.string() + "/images/font_white_20x20.png");
        m_table = RenderTable(m_win->getRenderer(), m_normalFontTexture, 20,
                              20);

        RenderTable::tableProperties tableProps;
        tableProps.positionX = 50;
        tableProps.positionY = 120;
        tableProps.width = 200;
        tableProps.height = 350;
        m_table.setTableProperties(tableProps);
        m_menu = MAIN_MENU;
        m_offset.setX(0.005f);
        m_offset.setY(0.005f);
        m_layer->setScrollSpeed(100.0f);
        m_first = true;
        mainMenu();
    }

    void MainMenu::update(const Uint8*& currentKeyStates, const bool* keyDown)
    {

        if (m_first)
        {
            m_first = false;
        }
        else
        {
            if (m_win->getActualScreen() == m_win->RENDER_MAINMENU)
            {
                m_sound.play(125);
                m_sound.resume();

                //Render background
                m_layer->m_camera.move(m_layer->m_camera.position() + m_offset);

                SDL_RenderClear(m_win->getRenderer());
                m_layer->render();

                //Render table
                if (keyDown[SDL_SCANCODE_DOWN])
                {
                    m_table.increase();
                }

                if (keyDown[SDL_SCANCODE_UP])
                {
                    m_table.decrease();
                }

                if (keyDown[SDL_SCANCODE_ESCAPE])
                {
                    m_table.setScrollable(true);
                    m_menu = MAIN_MENU;
                    mainMenu();
                    m_table.resetPos();
                }

                if (keyDown[SDL_SCANCODE_RETURN])
                {
                    m_table.setScrollable(true);
                    switch (m_menu)
                    {
                        case MAIN_MENU:
                            mainMenu();
                            if (m_table.getM_pos() == 0)
                            {
                                levelSelect();
                                m_menu = LEVEL_SELECT;
                            }
                            if (m_table.getM_pos() == 1)
                            {
                                highscore();
                                m_menu = HIGHTSCORE;
                            }
                            if (m_table.getM_pos() == 2)
                            {
                                credits();
                                m_menu = CREDITS;
                            }
                            if (m_table.getM_pos() == 3)
                            {
                                TextureFactory::instance(m_win->getRenderer()).deleteAll();
                                m_sound.stop();
                                m_win->quitGame();

                            }

                            break;
                        case CREDITS:
                            mainMenu();
                            m_menu = MAIN_MENU;
                            break;
                        case LEVEL_SELECT:
                            startGame();
                            break;
                        default:
                            mainMenu();
                            m_menu = MAIN_MENU;
                    }
                    m_table.resetPos();
                }

                m_table.setStringProperties(2, 1, 0, m_tableText);
                m_table.render();
                SDL_RenderPresent(m_win->getRenderer());
            }
        }
    }

    void MainMenu::showLevelHighscore()
    {
        m_table.setScrollable(false);
        long points = this->m_game->highscore->getHighscore();
        int sleepTime = 3000;
        int sleep = 10;
        std::vector<std::vector<std::string>> texts;
        texts.resize(2);
        for (unsigned int i = 0; i < texts.size(); i++)
        {
            texts.at(i).resize(2);
        }
        texts[0][0] = "Game ended: ";
        texts[0][1] = this->m_game->highscore->levelFile;
        texts[1][0] = "Your score: ";
        texts[1][1] = to_string(points);
        m_table.setStringProperties(2, 1, 0, texts);
        for (int i = 0; i < sleepTime / sleep; i++)
        {
            //Render background
            m_offset.setX(0.005f);
            m_offset.setY(0.005f);
            m_layer->setScrollSpeed(100.0f);
            m_layer->m_camera.move(m_layer->m_camera.position() + m_offset);

            SDL_RenderClear(m_win->getRenderer());
            m_layer->render();
            m_table.render();
            SDL_RenderPresent(m_win->getRenderer());
            usleep(sleep);
        }
        m_table.setStringProperties(2, 1, 0, m_tableText);
        delete m_game;
        this->m_win->setActualScreen(MainWindow::RENDER_MAINMENU);
        m_table.setScrollable(true);
    }

    void MainMenu::showLevelName()
    {
        m_table.setScrollable(false);
        int sleepTime = 3100;
        int sleep = 10;
        std::vector<std::vector<std::string>> texts;
        texts.resize(3);
        for (unsigned int i = 0; i < texts.size(); i++)
        {
            texts.at(i).resize(1);
        }
        texts[0][0] = "Start level";
        texts[1][0] = this->m_game->highscore->levelFile;
        texts[2][0] = to_string(sleepTime / 1000);
        m_table.setStringProperties(2, 1, 0, texts);
        for (int i = 0; i < sleepTime / sleep; i++)
        {
            //Render background
            m_offset.setX(0.005f);
            m_offset.setY(0.005f);
            m_layer->setScrollSpeed(100.0f);
            m_layer->m_camera.move(m_layer->m_camera.position() + m_offset);

            texts[2][0] = to_string((sleepTime - (i * sleep)) / 1000 + 1);
            m_table.setStringProperties(2, 1, 0, texts);
            SDL_RenderClear(m_win->getRenderer());
            m_layer->render();
            m_table.render();
            SDL_RenderPresent(m_win->getRenderer());
            usleep(sleep);
        }
        m_table.setStringProperties(2, 1, 0, m_tableText);
    }

    std::string MainMenu::to_string(long x)
    {
        std::stringstream ss;
        ss << x;
        return ss.str();
    }

    std::string MainMenu::to_string(int x)
    {
        std::stringstream ss;
        ss << x;
        return ss.str();
    }


    //Creates the highscore background
    void MainMenu::setupBackground(float scrollspeed, std::string backgroundImage)
    {
        SDL_RenderClear(m_win->getRenderer());
        SDL_Texture* texture = TextureFactory::instance(m_win->getRenderer()).getTexture(backgroundImage);
        m_layer = new TexturedLayer(m_win->getRenderer(), texture, 1);
    }

    void MainMenu::levelSelect()
    {
        int z = 0;
        for (unsigned int i = 0; i < m_levelFiles.size(); i++)
        {
            try
            {
                XML m_tmp(m_levelFiles[i].string());
                m_levelId_and_path.insert(std::pair<int, boost::filesystem::path>(m_tmp.getId(), m_levelFiles[i]));
            }
            catch (...)
            {
                std::cerr << "Failed to read file " + m_levelFiles[i].string() << std::endl;
                continue;
            }
        }
        m_tableText.resize(m_levelId_and_path.size());
        for (std::map<int, boost::filesystem::path>::iterator it = m_levelId_and_path.begin();
             it != m_levelId_and_path.end(); it++)
        {
            m_tableText[z].resize(2);
            m_tableText[z][0] = std::to_string(it->first) + ".";
            XML m_tmp2(it->second.string());
            m_tableText[z++][1] = m_tmp2.getLevelname();
        }
    }

    void MainMenu::startGame()
    {
        m_game = new Game(m_win);
        Game::setupGame(m_levelId_and_path.at(std::stoi(
                                m_tableText[m_table.getM_pos()][0].substr(0, m_tableText[m_table.getM_pos()][0].size() -
                                                                             1))).string(), m_win, m_game);
        m_win->setGame(m_game);
        this->showLevelName();
        m_win->setActualScreen(MainWindow::RENDER_GAME);
        m_sound.stop();
        m_game->start();
    }

    void MainMenu::mainMenu()
    {
        m_tableText.resize(4);
        for (int i = 0; i < 4; i++)
        {
            m_tableText[i].resize(1);
        }
        m_tableText[0][0] = "Level Select";
        m_tableText[1][0] = "Highscore";
        m_tableText[2][0] = "Credits";
        m_tableText[3][0] = "Quit";
    }

    void MainMenu::credits()
    {
        m_table.setScrollable(false);
        m_tableText.resize(5);

        int offsetRow = 2;
        m_tableText.resize(13 + offsetRow);
        m_tableText[0].resize(1);
        m_tableText[0][0] = "Credits";
        m_tableText[1].resize(0);

        for (int i = offsetRow; i < 13 + offsetRow; i++)
        {
            m_tableText[i].resize(1);
        }
        m_tableText[0 + offsetRow][0] = "Ben";
        m_tableText[1 + offsetRow][0] = "David";
        m_tableText[2 + offsetRow][0] = "Dennis";
        m_tableText[3 + offsetRow][0] = "Jochen";
        m_tableText[4 + offsetRow][0] = "Johan";
        m_tableText[5 + offsetRow][0] = "Johann";
        m_tableText[6 + offsetRow][0] = "Marius";
        m_tableText[7 + offsetRow][0] = "Nathan";
        m_tableText[8 + offsetRow][0] = "Patrick N.";
        m_tableText[9 + offsetRow][0] = "Patrick S.";
        m_tableText[10 + offsetRow][0] = "Sven";
        m_tableText[11 + offsetRow][0] = "Thorsten";
        m_tableText[12 + offsetRow][0] = "Timo";
    }

    void MainMenu::highscore()
    {
        m_table.setScrollable(false);
        std::vector<std::pair<std::string, int>> scores = m_win->profile->getHighScores();
        unsigned int offsetRow = 2;
        m_tableText.resize(scores.size() + offsetRow);
        m_tableText[0].resize(1);
        m_tableText[0][0] = "Highscores";
        m_tableText[1].resize(0);

        for (unsigned int i = offsetRow; i < scores.size() + offsetRow; i++)
        {
            m_tableText[i].resize(2);
            m_tableText[i][0] = scores.at(i - offsetRow).first;
            m_tableText[i][1] = to_string(scores.at(i - offsetRow).second);
        }
    }
}  /* namespace ikaruga */
