/**
* @file MainMenu.hpp
* @brief Definition of MainMenu
*
* @author Marius Brockmöller (mbrockmo@uos.de)
* @author Patrick Steinforth (psteinforth@uni-osnabrueck.de)
* @date 29 Feb 2016
*/
#ifndef IKARUGA_MAINMENU_HPP
#define IKARUGA_MAINMENU_HPP

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/regex.hpp>
#include <SDL_stdinc.h>
#include "MainWindow.hpp"
#include "Game.hpp"
#include "TexturedLayer.hpp"
#include "../xml/XML.hpp"
#include "RenderTable.hpp"
#include "Sound.hpp"

namespace fs = boost::filesystem;

namespace ikaruga
{
    class Game;

    class MainWindow;

    class MainMenu
    {
    public:
        static const int LEVEL_SELECT = 0;
        static const int CREDITS = 1;
        static const int MAIN_MENU = 2;
        static const int HIGHTSCORE = 3;

        /**
         * @brief MainMenu Constructor of the MainMenu class
         * @param win MainWindow* a pointer to the Window in which the Menu will be renderd
         * @param resDir fs::path path to the recources of the programm
         */
        MainMenu(MainWindow* win, fs::path resDir);

        /**
         * @brief update this will update the menu and navigate it
         * @param currentKeyStates Unit8*& keystates of the keyboard
         * @param keyDown bool* to check if a key was realeased between two uses
         */
        void update(const Uint8*& currentKeyStates, const bool* keyDown);

        /**
         * @brief shows a splash screen with a countdown before a level
         */
        void showLevelName();

        /**
         * @brief shows the Highscore of the last played level
         */
        void showLevelHighscore();

    private:

        Sound m_sound;
        std::vector<fs::path> m_levelFiles;
        MainWindow* m_win;
        fs::path m_resDir;
        Game* m_game;
        TexturedLayer* m_layer;
        Vector2f m_offset;
        SDL_Texture* m_normalFontTexture;
        std::vector<std::vector<std::string>> m_tableText;

        std::string to_string(int x);
        std::string to_string(long x);

        std::map<int, boost::filesystem::path> m_levelId_and_path;
        XML m_tmp;
        RenderTable m_table;
        int m_menu;
        bool m_first;

        /**
         * @brief sets up the background animation for the main menu
         * @param scrollspeed fload the speed in which the bachground will scroll
         * @param backgroundImage string path to the .png file which will be renderd
         */
        void setupBackground(float scrollspeed, string backgroundImage);

        /*
         * @brief changes the menu to the level selection screen
         */
        void levelSelect();

        /**
         * @brief changes the menu to the credit screen
         */
        void credits();

        /**
         * @brief changes the screen to the main menu screen
         */
        void mainMenu();

        /*
         * @brief starts the game with the last selected level
         */
        void startGame();

        /**
         * @brief changes the screen to display all saved highscores
         */
        void highscore();
    };
}  /* namespace ikaruga */

#endif //IKARUGA_MAINMENU_HPP
