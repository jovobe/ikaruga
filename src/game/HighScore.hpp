/*
 * HighScore.hpp
 *
 * @author Patrick Nolte (pnolte@uni-osnabrueck.de)
 * @date 29.02.2016
 */
#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>
#include "Profile.hpp"

namespace ikaruga
{
    class Profile;

    /**
     * @brief 	Represents the Highscore of one Level.
     */
    class HighScore
    {
    public:
        /**
         * Creates a Highscore Instance for a level
         *
         * @param profile       profile where the infos have to be set
         * @param levelFile     name of the unique levelname where the
         *                      highscore is needed
         */
        HighScore(Profile* profile, std::string levelFile);

        /**
         * Add points to the Highscore of the level
         *
         * @param points    Count of points
         */
        void addPointsToHighscore(int points);

        /**
         * Saves the Highscore of the level and set them for profile,
         * where the currency is set.
         * Just Call this at the END OF THE LEVEL
         */
        void saveHighscore();

        /**
         * Returns the actual HighScore of the Level
         */
        long getHighscore();

        //levelfile
        std::string levelFile;
    private:
        //actual highscore
        long actualHighscore;
        //profile to manage saving
        Profile* profile;
    };
} /* namespace ikaruga */

#endif // HIGHSCORE_H
