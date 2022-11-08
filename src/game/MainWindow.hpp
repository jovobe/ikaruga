/**
 * MainWindow.hpp
 * @brief Creates a main window
 *
 * @date 03.03.16
 * @author Patrick Steinforth (psteinforth@uni-osnabrueck.de)
 */

#ifndef SRC_MAINWINDOW_HPP_
#define SRC_MAINWINDOW_HPP_

#include <string>
#include <SDL.h>
#include "Game.hpp"
#include "WorldProperty.hpp"
#include "MainMenu.hpp"
#include "Profile.hpp"

namespace ikaruga
{
    class Game;

    class MainMenu;

    /**
     *	@brief Represents the main window of the game.
     */
    class MainWindow
    {
    public:

        /**
         * @brief Creates a main window with given title, width w height h.
         *
         * @param title		Title of the window
         * @param w			Width
         * @param h			Height
         * @param resPath   Path to a resource directory.
         */
        MainWindow(std::string title, int w, int h, boost::filesystem::path resPath);

        /**
         * @brief Destructor.
         */
        ~MainWindow();

        /**
         * @brief Handles user events and renders the current level.
         */
        void run();

        /**
         * @Gets the current SDL renderer
         *
         * @return Pointer to a SDL_Renderer instance.
         */
        SDL_Renderer* getRenderer();

        /**
         * @brief Provide a game object for rendering.
         *
         * @param game Game object.
         */
        void setGame(Game* game);

        /**
         * @brief Provide a menu object for rendering.
         *
         * @param Menu object.
         */
        void setMenu(MainMenu* menu);

        /**
         * @brief Returns the window width.
         *
         * @return Window width.
         */
        int w();

        /**
         * @brief Returns the window height.
         *
         * @return Window height.
         */
        int h();

        ///Constants for setting the actual renderscreen
        static const int RENDER_MAINMENU = 0;
        static const int RENDER_GAME = 1;
        static const int RENDER_CREDITS = 3; //TODO make enum
        static const int RENDER_GAMEEND = 4;

        /**
         * @brief Set the actual screen for rendering.
         * You can select  between MAINMENU, GAME, CREDITS and GAMEEND.
         *
         * @param ID ID for rendering. You can use the const from this class.
         */
        void setActualScreen(int ID);

        /**
         * @brief Get the actual renderscreen.
         *
         * @return The renderscreen (compare with the const variables of this class).
         */
        int getActualScreen();

        /**
         * @brief Method to end the game.
         */
        void quitGame()
        {
            m_quit = true;
        }

        Profile* profile;
        XML* xml;
    private:
        /// quit game if true
        bool m_quit;

        /**
         * @brief Initialize SDL.
         */
        void initSDL();

        /**
         * @brief Quits SDL and frees all resources.
         */
        void quitSDL();

        /**
         * @brief Returns time used by the main loop in ms
         */
        float getLoopTime();

        /**
         * @brief Limts the FPS by sleeping not used time
         */
        void limitFPS();

        /// SDL renderer
        SDL_Renderer* m_renderer;

        /// SDL main window
        SDL_Window* m_window;

        /// Window width
        int m_width;

        /// Window height
        int m_height;

        /// Window title
        std::string m_title;

        /// Pointer to game
        Game* m_game;

        /// Pointer to menu
        MainMenu* m_menu;

        /// Timestamp from the start of the main loop
        Uint32 m_startLoopTicks;

        /// Number of maximal fps
        static const int MAX_FPS;

        //Number for settings updatecall (actual Menu/Game)
        int actRenderID;
    };

} /* namespace ikaruga */

#endif /* SRC_MAINWINDOW_HPP_ */
