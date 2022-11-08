/*
 * MainWindow.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#include "MainWindow.hpp"
#include <SDL_image.h>
#include <SDL_mixer.h>

namespace ikaruga
{
    const int MainWindow::MAX_FPS = 60;

    MainWindow::MainWindow(std::string title, int w, int h, boost::filesystem::path resPath)
            : m_startLoopTicks(0)
    {
        m_quit = false;
        /// Init width and height
        m_width = w;
        m_height = h;
        m_title = title;

        /// Set pointer to NULL
        m_renderer = 0;

        /// Init the camera for all renderables
        Renderable::m_camera.m_width = w;
        Renderable::m_camera.m_height = h;
        /// Initialize SDL stuff
        initSDL();
        this->actRenderID = 0;
        std::cout << resPath.c_str() << std::endl;
        xml = new XML(resPath.c_str(), true);
        profile = new Profile(xml);
    }

    MainWindow::~MainWindow()
    {
        delete xml;
        delete profile;
        quitSDL();
    }

    SDL_Renderer* MainWindow::getRenderer()
    {
        return m_renderer;
    }


    void MainWindow::run()
    {
        SDL_Event e;
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        bool* keyDown = new bool[SDL_NUM_SCANCODES];
        m_startLoopTicks = SDL_GetTicks();

        // Start main loop and event handling
        while (!m_quit && m_renderer)
        {
            // Process events, detect quit signal for window closing
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    m_quit = true;
                }

                // collect down keys
                if (e.key.type == SDL_KEYDOWN && e.key.repeat == 0)
                {
                    keyDown[e.key.keysym.scancode] = true;
                }
            }
            //std::cout << actRenderID << std::endl; //Debug Output
            switch (actRenderID)
            {
                case MainWindow::RENDER_MAINMENU:
                    m_menu->update(currentKeyStates, keyDown);
                    break;
                case MainWindow::RENDER_GAME:
                    m_game->update(currentKeyStates, keyDown);
                    break;
                case MainWindow::RENDER_GAMEEND:
                    m_menu->showLevelHighscore();
                    break;
                case MainWindow::RENDER_CREDITS:
                    break;
                default:
                    std::cout << "You have to use setActualScreen." << std::endl;
                    break;
            }

            // reset key down
            for (int i = 0; i < SDL_NUM_SCANCODES; i++)
            {
                keyDown[i] = false;
            }

            // sleep not needed time
            limitFPS();
        }

        delete[] keyDown;
    }

    void MainWindow::setActualScreen(int ID)
    {
        actRenderID = ID;
    }

    void MainWindow::setGame(Game* game)
    {
        m_game = game;
    }

    void MainWindow::setMenu(MainMenu* menu)
    {
        m_menu = menu;
    }

    void MainWindow::initSDL()
    {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "SDL could not initialize: " << SDL_GetError() << std::endl;
            return;
        }

        // Generate SDL main window
        m_window = SDL_CreateWindow(
                m_title.c_str(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                m_width,
                m_height,
                SDL_WINDOW_SHOWN);

        if (m_window == NULL)
        {
            std::cout << "SDL window could not be generated: " << SDL_GetError() << std::endl;
        }
        else
        {

            // Create renderer for the SDL main window
            m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (m_renderer == NULL)
            {
                std::cout << "SDL could not generate renderer: " << SDL_GetError() << std::endl;
            }
            else
            {
                // Set background color for renderer
                SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
            }
        }

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        }
    }


    void MainWindow::quitSDL()
    {
        // Destroy window and renderer
        if (m_window)
        {
            SDL_DestroyWindow(m_window);
            m_window = 0;
        }

        if (m_renderer)
        {
            SDL_DestroyRenderer(m_renderer);
            m_renderer = 0;
        }

        // Quit SDL and SDL_Image
        Mix_CloseAudio();
        IMG_Quit();
        SDL_Quit();
    }

    float MainWindow::getLoopTime()
    {
        Uint32 ticks = SDL_GetTicks();
        float time = (ticks - m_startLoopTicks) / 1000.0f;
        m_startLoopTicks = ticks;
        return time;
    }

    int MainWindow::w()
    {
        return m_width;
    }

    int MainWindow::h()
    {
        return m_height;
    }

    void MainWindow::limitFPS()
    {
        // calc used time in loop
        float loopTime = getLoopTime();
        float maxLoopTime = 1.0f / MAX_FPS;

        // calc sleep time
        int sleepTime = (int) floor((maxLoopTime - loopTime) * 1000.0f);

        // sleep not used time
        if (sleepTime > 0)
        {
            Uint32 sleepTimeUint = (Uint32) sleepTime;
            SDL_Delay(sleepTimeUint);
        }
    }

    int MainWindow::getActualScreen()
    {
        return actRenderID;
    }
} /* namespace ikaruga */


