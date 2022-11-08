/*
 * Level.hpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 *      Author: nwollek
 *      Author: darolfes
 */

#ifndef SRC_LEVEL_HPP_
#define SRC_LEVEL_HPP_

#include <string>
#include <SDL.h>
#include <vector>
#include "Camera.hpp"
#include "StaticRenderable.hpp"
#include "SparseMatrix.hpp"
#include "Vector.hpp"
#include "WorldProperty.hpp"
#include "TextureFactory.hpp"
#include <fstream>


namespace ikaruga
{

    /// Directions of actor
    enum TilesDirection
    {
        TUP,
        TDOWN,
        TLEFT,
        TRIGHT
    };

    /// Type of tiles
    enum TileType
    {
        SOLID = 1,
        NONSOLID = 2,
        EDGETOPLEFT = 3,
        EDGETOPRIGHT = 4,
        EDGEDOWNLEFT = 5,
        EDGEDOWNRIGHT = 6
    };


    class Actor;

    /**
     * @brief Represents a level in the ikaruga game.
     */
    class Level : public StaticRenderable
    {
    public:

        /**
         * Loads a level from the given .lvl file
         *
         * @param renderer	Renderer for level
         * @param filename	Filename of level
         */
        Level(SDL_Renderer* renderer, std::string filename);

        /**
         * Renders the level
         */
        virtual void render();

        /// Returns the number of tiles in a row
        int levelHeight() const;

        /// Returns the number of tile rows
        int levelWidth() const;

        /// Returns the tile width
        int tileWidth() const;

        /// Returns the tile height
        int tileHeight() const;

        /// Returns the matrix of tiles
        SparseMatrix& tiles();

        /// Returns the physical properties of the level
        WorldProperty& physics();

        /**
         * Destructor
         */
        virtual ~Level();

        /**
         * Calculates/Adjusts the possible movement for an actor (wrapper)
         *
         * @param pos 		Position of actor
         * @param width 	Width of actor
         * @param height	Height of actor
         * @param move		Wanted movement of actor
         * @param actor		Actor himself
         *
         * @return 			Adjusted movement of actor
         */
        Vector2f collide(Vector2f pos, int width, int height, Vector2f move, Actor* actor);

    private:

        /// Returns the surrounding tiles of the given position
        void getSurroundingTiles(Vector2f pos, int width, int height, Vector2i* tiles);

        /**
         * Gets the relevant (for collision) tiles surrounding the actor
         *
         * @param pos 		Position of actor
         * @param direction	Direction the actor wants to move
         * @param width 	Width of actor
         * @param height	Height of actor
         * @param tiles		Pointer to vector where to fill tiles in
         */
        void getSurroundingRelevantTiles(Vector2f pos, TilesDirection direction, int width, int height,
                                         std::vector<Vector2i>* tiles);

        /**
         * Gets the relevant (for collision) tiles the actor is located in
         *
         * @param pos 		Position of actor
         * @param direction	Direction the actor wants to move
         * @param width 	Width of actor
         * @param height	Height of actor
         * @param tiles		Pointer to vector where to fill tiles in
         */
        void getInnerTiles(Vector2f pos, TilesDirection direction, int width, int height, std::vector<Vector2i>* tiles);

        /**
         * Calculates/Adjusts the possible movement for an actor (recursive)
         *
         * @param pos 		Position of actor
         * @param width 	Width of actor
         * @param height	Height of actor
         * @param move		Wanted movement of actor
         * @param actor		Actor himself
         *
         * @return 			Adjusted movement of actor
         */
        Vector2f collideRC(Vector2f pos, int width, int height, Vector2f move, Actor* actor);

        /**
         * Calculates/Adjusts the possible movement for an actor (horizontal part)
         *
         * @param pos 		Position of actor
         * @param width 	Width of actor
         * @param height	Height of actor
         * @param move		Wanted movement of actor
         * @param actor		Actor himself
         * @param checkY	Whether to check the vertical part, too
         *
         * @return 			Adjusted movement of actor
         */
        Vector2f collideX(Vector2f pos, int width, int height, Vector2f move, Actor* actor, bool& checkY);

        /**
         * Calculates/Adjusts the possible vertical movement for an actor
         *
         * @param pos 		Position of actor
         * @param width 	Width of actor
         * @param height	Height of actor
         * @param y			Wanted vertical movement of actor
         * @param actor		Actor himself
         *
         * @return 			Adjusted vertical movement of actor
         */
        float collideY(Vector2f pos, int width, int height, float y, Actor* actor);

        /**
         * Calculates the difference to next edge
         *
         * @param playerPos 	Position of actor
         * @param playerSize	Size of actor
         * @param tileGridPos	Position of tile in grid
         * @param edgeBonus		0 - left/upper edge, 1 - right/bottom edge
         *
         * @return				Difference to next edge
         */
        float nextEdge(float playerPos, int playerSize, int tileGridPos, int edgeBonus);

        /**
         * Calculates the position relative to the tile-grid
         *
         * @param pos 	Position of actor
         * @param grid	Position of tile in grid
         *
         * @return		Position relative to the tile-grid
         */
        float posRelativToGrid(float pos, int grid);

        /**
         * Converts a grid position into pixels
         *
         * @param grid	Position in grid
         *
         * @return		Position in pixels
         */
        float gridToPos(int grid);

        /**
         * Converts pixels into a grid position
         *
         * @param pos	Position in pixels
         *
         * @return		Position in grid
         */
        int posToGrid(float pos);

        /**
         * Checks if a tile is in range of the level
         *
         * @param tile	Tile
         *
         * @return		Whether tile is in range of the level
         */
        bool tileInRange(Vector2i& tile);

        /// Tile width
        int m_tileWidth;

        /// Tile height
        int m_tileHeight;

        /// Offset between the tiles in the tile sheet
        int m_tileOffset;

        /// Number of rows in the tile sheet
        int m_numRows;

        /// Number of tiles per row
        int m_tilesPerRow;

        /// Level width
        int m_levelWidth;

        /// Level height
        int m_levelHeight;

        /// Tiletypes
        std::vector<TileType> m_tileTypes;

        ///Physical properties of level
        WorldProperty m_levelPhysics;

        /// Tile matrix
        SparseMatrix m_tiles;
    };

} /* namespace ikaruga */

#endif /* SRC_LEVEL_HPP_ */
