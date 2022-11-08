#include "HighScore.hpp"

namespace ikaruga
{
    HighScore::HighScore(Profile* profile, std::string levelFile)
    {
        this->levelFile = levelFile;
        this->actualHighscore = 0;
        this->profile = profile;
    }

    void HighScore::addPointsToHighscore(int points)
    {
        this->actualHighscore += points;
    }

    void HighScore::saveHighscore()
    {
        profile->addHighScore(levelFile, actualHighscore);
    }

    long HighScore::getHighscore()
    {
        return this->actualHighscore;
    }
} /* namespace ikaruga */
