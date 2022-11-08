/*
 * FontRenderer.hpp
 *
 * @author Jochen Saalfeld (jsaalfeld@uni-osnabrueck.de)
 * @date 26.02.2016
 */

#ifndef SRC_SCOREBOARD_HPP_
#define SRC_SCOREBOARD_HPP_


#include <SDL.h>
#include <vector>
#include "FontRender.hpp"

using std::string;

namespace ikaruga
{

    /**
     * @brief A class to display points using a digit map for rendering
     */
    class StatusBar : public FontRender
    {
    public:


        /**
         * @brief Constructs a Statusbar for the given renderer
         *
         * @param renderer			A valid SDL_Renderer structure
         * @param texture			A texture that contains the 10 digits (from 0 to 9 in
         * 							that order)
         * @param digitWidth		The width of a digit within the texture
         * @param digitHeight		The height of a digit within the texture
         * @param capitalOffset     The Offset for Capital Letters
         * @param minusculeOffset   The Offset for lower Case Letters
         * @param numberOffset      The Offset for numbers
         * @param letterCount       The numbers of Lettrs
         * @param offsetMiddle      Offset to get everything perfectly to the midle
         */
        StatusBar(SDL_Renderer* renderer,
                  SDL_Texture* texture,
                  int tileWidth,
                  int tileHeight,
                  int capitalOffset,
                  int minusculeOffset,
                  int numberOffset,
                  int letterCount,
                  int offsetMiddle);

        /**
         * @brief Sets the current Score
         *
         * @param score	Sets the Current Score
         */
        void setScore(int long score);

        /**
         * @brief Gets the current Score
         *
         * @returns currentScore
         */
        int long getScore(void) const;


        /**
         * @brief Renders the Statusbar
         */
        virtual void render();

        /**
         * @brief Destructor
         */
        virtual ~StatusBar();

        /**
         * @brief Sets the StatusBar Position
         *
         * @param positionStart the lower left corner of the StatusBar
         * @param positionEnd the upper right corner of the StatusBar
         */
        void setPosition(const Vector2i& positionStart, const Vector2i& positionEnd);

        /**
         * @brief Sets the weapon name
         *
         * @param weaponName name of the weapon
         */
        void setWeaponName(string weaponName);

        /**
         * @brief Sets the evolution Stage of the weapon
         *
         * @param evolutionStage evolution Stage of the weapon
         */
        void setEvolutionStage(string evolutionStage);

        /**
         * @brief Sets the health of the Player
         *
         * @param health health of the player
         */
        void setHealth(int health);

        /**
         * @brief Sets the health of a Boss
         *
         * @param health health of the boss
         */
        void setBossHealth(int health);

    private:

        /**
         * @brief Sets the Score Position in the bar
         *
         * @param position the position of the score
         */
        void setScorePosition(const Vector2i& position);

        /**
         * @brief Sets the Weapon Position
         *
         * @param position position of the Weapon String
         */
        void setWeaponPosition(const Vector2i& position);

        /**
         * @brief Sets the Health Position
         *
         * @param position position of the players health
         */
        void setHealthPosition(const Vector2i& position);

        /// Current score
        int long m_score;

        /// Digit width
        int m_tileWidth;

        /// Digit height
        int m_tileHeight;

        //Offset for Capital Letters
        int m_capitalOffset;

        //Offset for Minuscule Letters
        int m_minusculeOffset;

        //Offset for NUmbers
        int m_numberOffset;

        //Number of Letters in Tilesheet
        int m_letterCount;

        //Number to get it exaclty in the middle of the statusbar
        int m_offsetMiddle;

        //y-Axis so its in the middle of the Statusbar
        int m_horziontalAlignemnt;

        //WeaponName
        string m_weaponName;

        //look, if the weapon changed
        bool m_weaponChanged;

        //EvolutionStage
        string m_evolutionStage;


        //the Weapon Source in the tilesheet
        std::vector<SDL_Rect> m_weaponSource;

        //the Weapon Target in the Window
        std::vector<SDL_Rect> m_weaponTarget;

        /// Scoreboard position
        Vector2i m_scorePosition;

        /// Maxim score that can be displayed
        const static int m_maxScore;

        /// lower left corner of the StatusBar
        Vector2i m_startPosition;

        /// upper Right corner of the Statusbar
        Vector2i m_endPosition;

        /// Position of the weapon String
        Vector2i m_weaponPosition;

        /// Poistion of the Players Health
        Vector2i m_healthPosition;

        /// Players Health
        int m_health;

        /// Maximum player health
        int m_max_health;

        /// width of the health bar
        const int m_healthBarWidth = 100;

        /// health of the boss
        int m_boss_health;

        /// maxmimum health of the boss
        int m_boss_max_health;

        /**
         * @brief Renders a Number at a given Position
         *
         * @param number number to render
         * @param position position where to render the number
         * @param source the sdl_rect source
         * @param target the sdl_rect target
         */
        void displayNumber(int number, Vector2i position, SDL_Rect source, SDL_Rect target);

        /**
         * @brief Renders the HP Bar
         *
         * @param position the position of the hp-bar
         * @param w width of the hp-bar
         * @param h height of the hp-bar
         * @param max_health pointer to the maximum health
         * @param health pointer the the current health status
         */
        void RenderHPBar(Vector2i& position, int w, int h, int* max_health, int* health);

        /**
         * @brief renders a rectangle
         *
         * @param renderer pointer to SDL_Renderer
         * @param position the start position of the rectangle
         * @param w width of the rectangle
         * @param h hegith of the rectangle
         * @param r red value (0-255)
         * @prarm g green value (0-255)
         * @param b blue value (0-255)
         */
        void renderRectangle(SDL_Renderer* renderer, Vector2i position, int w, int h, int r, int g, int b);

        /// the offset of the boss healthbar
        const int offsetBossHealth = 2;
    };

} /* namespace ikaruga */

#endif /* SRC_SCOREBOARD_HPP_ */
