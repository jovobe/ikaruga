#include "Profile.hpp"

namespace ikaruga
{
    Profile::Profile()
    {

    }

    Profile::Profile(XML* xml)
    {
        this->xmlObject = xml;
        if (xmlObject->profileSize() > 0)
        {
            XML::Profile tmp = xmlObject->getProfile(0);
            actProfile.actualWeapon = tmp.actualWeapon;
            actProfile.boughtPowerUps = tmp.boughtPowerUps;
            actProfile.boughtWeapons = tmp.boughtWeapons;
            actProfile.highscores = tmp.highscores;
            actProfile.money = tmp.money;
            actProfile.name = tmp.name;
            actProfileID = 0;
        }
        else
        {
            actProfile.name = "FirstProfile";
            actProfile.money = 0;
            actProfile.actualWeapon = xmlObject->getWeapon(0);
            std::vector<XML::Profile> profiles;
            profiles.push_back(actProfile);
            xmlObject->setProfiles(profiles);
            actProfileID = 0;
            saveActProfile();
        }
    }

    void Profile::setProfile(std::string profileName)
    {
        std::vector<XML::Profile> profileList = xmlObject->getProfiles();
        for (unsigned int i = 0; i < profileList.size(); i++)
            if (profileList.at(i).name == profileName)
            {
                if (profileList.at(i).name != profileName)
                {
                    xmlObject->setProfile(actProfileID, actProfile);
                    actProfile = profileList.at(i);
                    xmlObject->saveProfiles();
                    break;
                }
            }
    }

    std::vector<std::string> Profile::getProfiles()
    {
        std::vector<std::string> profileNameList;
        std::vector<XML::Profile> profileList = xmlObject->getProfiles();
        for (unsigned int i = 0; i < profileList.size(); i++)
            profileNameList.push_back(profileList.at(i).name);
        return profileNameList;
    }

    void Profile::addHighScore(std::string level, long highscore)
    {
        std::map<std::string, int>::iterator iter = actProfile.highscores.find(level);
        if (iter != actProfile.highscores.end())
        {
            if (iter->second < highscore)
            {
                iter->second = highscore;
            }
        }
        else
        {
            std::pair<std::string, int> pair(level, highscore);
            actProfile.highscores.insert(pair);
        }
        saveActProfile();
    }

    void Profile::saveActProfile()
    {
        xmlObject->setProfile(actProfileID, actProfile);
        xmlObject->saveProfiles();
    }

    std::vector<std::pair<std::string, int>> Profile::getHighScores()
    {
        std::vector<std::pair<std::string, int>> highscores;
        std::pair<std::string, int> highScorePairs;
        BOOST_FOREACH(highScorePairs, actProfile.highscores)
                    {
                        highscores.push_back(highScorePairs);
                    }
        return highscores;
    }
} /* namespace ikaruga */
