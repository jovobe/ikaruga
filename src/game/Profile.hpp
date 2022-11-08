/*
 * Profile.hpp
 *
 * @author Patrick Nolte (pnolte@uni-osnabrueck.de)
 * @date 29.02.2016
 */
#ifndef PROFILE_H
#define PROFILE_H

#include <string>
#include <vector>
#include <iostream>
#include "../xml/XML.hpp"
#include <boost/foreach.hpp>

namespace ikaruga
{
    /**
     * @brief A class to load and save profile information
     */
    class Profile
    {
    public:
        /**
         * Constructor
         *
         */
        Profile();

        /**
         * Constructor
         *
         * @param xml       xmlObject for handeling
         */
        Profile(XML* xml);

        /**
         * Returns all Profilenames as strings
         */
        std::vector<std::string> getProfiles();

        /**
         * Sets the actual Profile
         *
         * @param profileName The profile-name (as returned by getProfiles())
         */
        void setProfile(std::string profileName);

        /**
         * adds a highscore for a level
         *
         * @param level         unique levelname
         * @param highscore     highscorepoints for the level
         */
        void addHighScore(std::string level, long highscore);

        /**
         * Returns all HighScores as pair with strings and int
         * of the actual player
         */
        std::vector<std::pair<std::string, int>> getHighScores();

    private:
        ///the actual profile
        XML::Profile actProfile;

        /**
         * saves the actual Profile to XML-File
         */
        void saveActProfile();

        ///xmlObject
        XML* xmlObject;
        ///the actual profileID
        int actProfileID;
    };
} /* namespace ikaruga */

#endif // PROFILE_H
