/*
 * Sound.hpp
 *
 * @author Jochen Saalfeld (jsaalfeld@uni-osnabrueck.de)
 * @date 29.02.2016
 */

#include "Level.hpp"

#ifndef IKARUGA_SOUND_HPP
#define IKARUGA_SOUND_HPP

using std::string;

namespace ikaruga
{

    namespace SoundType
    {
        enum SoundType
        {
            SONG,
            SOUND
        };
    }

    //static int NEXT_CHANNEL = 1;
    /**
     * @brief a class to play some fancy wavs
     */
    class Sound
    {

    public:
        /// used to calculate the next free channel
        static int NEXT_CHANNEL;

        /**
         * @brief Standard Constructor
         */
        Sound()
        { };

        /**
         * @brief Constructor to create a sound
         *
         * @param filename a relative path to the base to the soundfile
         * @param type the type of the sound
         */
        Sound(string filename, int type);


        /**
         * @brief Plays the sound
         *
         * @param volume the volume the sound should be played with
         */
        void play(int volume);

        /**
         * @brief Plays the sound with a fadeout
         *
         * @param volume the volume the sound should be played with
         * @param fadeOut the fadeout in ms
         */
        void play(int volume, int fadeOut);

        /**
         * @brief stops Playing
         */
        void stop();

        /**
         * @brief pauses playing
         */
        void pause();

        /**
         * @brief resumes playing
         */
        void resume();

    private:

        /// The Filename of the sound
        string m_soundFile;

        /// The Type of the Sound
        int m_type;

        /// The channel, where the sound is played
        int m_channel;
    };
}  /* namespace ikaruga */

#endif //IKARUGA_SOUND_HPP
