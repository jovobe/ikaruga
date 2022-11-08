/*
 * Game.hpp
 *
 *  Created on: Dec 11, 2015
 *  @Author: twiemann
 *  @author Marius Brockmöller (mbrockmo@uos.de)
 *  @autor Jochen Saalfeld (jsaalfeld@uos.de)
 *  @author Patrick Steinforth (psteinforth@uos.de)
 */

#ifndef SRC_GAME_HPP_
#define SRC_GAME_HPP_

#include "MainWindow.hpp"
#include "Actor.hpp"
#include "Bot.hpp"
#include "Player.hpp"
#include "Level.hpp"
#include "TexturedLayer.hpp"
#include "Collidable.hpp"
#include "StatusBar.hpp"
#include "Sound.hpp"
#include "Vector.hpp"
#include "LaserWeapon.hpp"
#include "BlasterWeapon.hpp"
#include "RocketWeapon.hpp"
#include "MeatballWeapon.hpp"
#include "PowerUpHeal.hpp"
#include "PowerUpGodMode.hpp"
#include "../xml/XML.hpp"
#include "HighScore.hpp"
#include <vector>
#include "FontRender.hpp"

using std::vector;

namespace ikaruga
{
    class Bot;

    class MainWindow;

    class HighScore;

    /**
     * @brief 	Represents a game instance.
     */
    class Game
    {
    public:

        /**
         * @brief constructor of the Game class
         * @param window MainWindow* the window in which the game will be renderd
         */
        Game(MainWindow* window);

        /**
         * @brief destructor of the game class
         */
        virtual ~Game();

        /**
         * @brief adds a player to the game
         * @param player Player* a player object to add to the game
         */
        void setPlayer(Player* player);

        /**
         * @brief adds a level to the game
         * @param level *level a level object that represents the chosen level
         */
        void setLevel(Level* level);

        /**
         * @brief returns a pointer to the current level
         * @return Level* to the current level
         */
        Level* getLevel();

        /**
         * @brief adds an actor object to the game eg bot,powerups, player..
         * @param an actor object
         */
        void addActor(Actor* actor);

        /**
         * @brief updates the game and all actors in it
         * @param currentKeyStates Unit8*& key states of the keyboard
         * @param keyDown bool* to to check if a key was released
         */
        void update(const Uint8*& currentKeyStates, const bool* keyDown);

        /**
         * @brief starts the game
         */
        void start();

        /**
         * @brief Sets a layer for background rendering
         * @param layer TexturedLayer* a layer containing the background
         */
        void setLayer(TexturedLayer* layer)
        { m_layer = layer; };

        /**
         * @brief adds a statusbar to the game
         * @param b StatusBar* a StatusbarObject to be renderd
         */
        void setStatusBar(StatusBar* b)
        { m_statusBar = b; };

        /**
         * @brief adds a bot the game
         * @param bot Bot* a bot to add to the game
         */
        void addBot(Bot* bot);

        /**
         * @brief sets the background sound of the game
         * @param soundFile string path to the sound file
         * @param volume int regulates the sound level
         */
        void setSound(std::string soundFile, int volume);

        /**
         * @brief returns the players position
         * @return vector2f containing the player position
         */
        Vector2f getPlayerPosition();

        /**
         * @brief Constant Pixel Offset to spawn bots
         */
        static const int PIXELS_OFFSET_SPAWN_BOTS = 40;
        /**
         * @brief const Pixel offset to render the game
         */
        static const int PIXELS_OFFSET_RENDER = 40;

        /**
         * @brief sets up the game
         * @param filename string path to the level.xml file
         * @param w MainWindow* window to render the game
         * @param game Game* game to be created
         */
        static void setupGame(string filename, MainWindow* w, Game* game);

        /**
         * @brief creates bots and adds them to a game
         * @param bots a vector containing the XML::Level bot information
         * @param w MainWindow* window to render the game
         * @param game the game to add the bots
         * @param filepath string path to the working dir
         */
        static void setupBots(vector<XML::LevelBot> bots, MainWindow* w, Game* game, std::string filepath);

        /**
         * @brief adds items to the game
         * @param items a vector containing the XML::item item information
         * @param w MainWindow* window to render the game
         * @param game the game to add the items
         * @param filepath string path to the working dir
         */
        static void setupItems(vector<XML::LevelItem> items, MainWindow* w, Game* game, std::string filepath);

        /**
         * @brief adds the player to the game
         * @param xplayer XML::player containing the player information
         * @param w MainWindow* window to render the game
         * @param game the game to add the player
         * @param filepath string path to the working dir
         */
        static void setupPlayer(XML::Player xplayer, MainWindow* w, Game* game, std::string filepath);

        /**
         * @brief adds the statusbar to the game
         * @param statusbar XML::statusbar containing the statusbar information
         * @param w MainWindow* window to render the game
         * @param game the game to add the statusbar
         * @param filepath string path to the working dir
         */
        static void setupStatusbar(MainWindow* w, Game* game, XML::Statusbar statusbar, std::string filepath);

        /**
         * @brief adds the background to the game
         * @param background XML::background containing the background information
         * @param w MainWindow* window to render the game
         * @param game the game to add the background
         * @param filepath string path to the working dir
         */
        static void setupBackground(XML::Background background, std::string filepath, MainWindow* w, Game* game);

        /**
         * @brief adds the level to the game
         * @param w MainWindow* window to render the game
         * @param game the game to add the statusbar
         * @param filepath string path to the level.xml
         */
        static void setupLevel(MainWindow* w, Game* game, std::string filepath);

        /**
         * @brief adds the level bot information to a PlayerProperty for a bot
         * @param bot XML::LevelBot struct cointaining the needed information
         * @param p PlayerProperty& this will be filled with the information
         */
        static void getBotProperty(XML::LevelBot bot, PlayerProperty& p);

        /**
         * @brief adds the player information to a PlayerProperty for the player
         * @param player XML::Player struct cointaining the needed information
         * @param p PlayerProperty& this will be filled with the information
         */
        static void getPlayerProperty(XML::Player player, PlayerProperty& p);

        /**
         * Creates a weapon Object from the given XML weapon struct
         *
         * @param weapon XML weapon struct to get infos from
         * @param game Pointer to game instance
         * @param actor Pointer to actor instance
         * @param w Pointer to mainwindow instance
         * @param filepath Filepath to res folder
         * @return Weapon instance
         */
        static Weapon* createWeaponFromXML(XML::Weapon weapon, Game* game, Actor* actor, MainWindow* w,
                                           std::string filepath);

        /**
         * @brief to set the game in bossfight mode
         * @param bossfight bool true to enable bossfight mode
         */
        void setBossFight(bool bossfight);

        /**
         * @brief cares about the bossfight
         */
        void bossFight();

        /**
        * @brief return if the game is in bossfight mode
           * @return boolean true if in bossfight mode
           */
        bool getBossFight();

        /**
         * @brief sets a bossfight at the given position
         * @param bossFightAt in x coor for the bossfight
         */
        void setBossFightAt(int bossFightAt);

        /**
         * @brief get bossfight position
         * @return x coor of the bossfight
         */
        int getBossFightAt();

        /**
         * @brief cares about killed actor
         * @param actor the killed actor
         */
        void setActorOptionsOnKill(Actor* actor);

        /**
         * @brief sets the boss heath
         * @param health int the health of the boss
         */
        void setBossHealth(int health);

        /**
         * @brief removes a dead actor from the game
         * @param a actor* the dead actor
         */
        void removeActor(Actor* a);

        /**
         * @brief cares about the ending of a game
         */
        void end();

        /**
         * @brief returns the last boss of the game
         * @return last boss of the game
         */
        Actor* getLastBoss();

        HighScore* highscore;

    protected:
        bool m_bossFight;

    private:
        /**
         * @brief checks if a cheat was entert correctly
         * @param type last typed char
         */
        void checkCheat(const char type);

        int m_boss_health;

        int m_bossFightAt;

        /**
         * @brief moves all actors of the game
         */
        void moveActors();

        /**
         * @brief checks for camera collision
         */
        void checkCameraCollision();

        /**
         * Returns The time in seconds that has elapsed since the last frame.
         * @return The elapsed time.
         */
        float getElapsedTime();

        /**
         * Moves the player and camera for a given offset (m_scrollingSpeed)
         */
        void scrollHorizontal();

        void spawnBots();

        float m_startTicks;

        /// All renderables in the game
        vector<Renderable*> m_renderables;

        /// All actors
        vector<Actor*> m_actors;

        /// The user controlled player
        Player* m_player;

        /// The current level
        Level* m_level;

        MainWindow* window;

        /// A Layer
        TexturedLayer* m_layer;

        /// A score board
        StatusBar* m_statusBar;

        /// Pointer to the main window of the game
        SDL_Renderer* m_renderer;

        /// Window width
        int m_windowWidth;

        /// Window height
        int m_windowHeight;

        bool m_started;

        int m_volume;

        /**
         * @brief Is invoked by Game::update() and remove Actors with health below 0.
         */
        void removeDeadActors();

        vector<Bot*> m_bots;

        Sound m_sound;

        string m_explosionAnimation;

        std::string m_cheat;

        bool m_cheatActive;

        const std::string konamiCode = "u u d d l r l r B A";
    };

} /* namespace ikaruga */

#endif /* SRC_GAME_HPP_ */
