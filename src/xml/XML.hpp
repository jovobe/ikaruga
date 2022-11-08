/**
* @file XML.hpp
* @brief Imports a xml file with game specifications
*
* @author Patrick Steinforth (psteinforth@uni-osnabrueck.de)
* @author Sven Kleine-Albers (skleinealber@uni-osnabrueck.de)
* @date 23 Feb 2016
*/

#ifndef XML_HPP
#define XML_HPP

#include <vector>
#include <map>
#include <boost/exception/all.hpp>

class XML
{
public:
    //Public structs for xml nodes
    struct Weapon
    {
        std::string type;
        std::string filename;
        int colorOffsetX;
        int colorOffsetY;
        int shootingVolume;
        int soundVolume;
        int frameWidth;
        int frameHeight;
        float weaponOffsetX;
        float weaponOffsetY;
        float cooldown;
        std::string soundfile;
        int collisionDamage;
        float speed;
        int numFrames;
    };

    struct NPC
    {
        std::string type;
        std::string move_function;
        signed int move_value;
        signed int speed;
        Weapon stdWeapon;
    };

    struct Player
    {
        std::string filename;
        int numFrames;
        int frameWidth;
        int frameHeight;
        int positionX;
        int positionY;
        Weapon stdWeapon;
        int colorOffsetX;
        int colorOffsetY;
        float moveForceX;
        float moveForceY;
        float maxVel;
        int fps;
        std::string explosionSoundFile;
        int explosionVolume;
        std::string hitSoundFile;
        int hitVolume;
        int collisionDamage;
        int health;
    };

    struct Bot
    {
        std::string type;
        std::string filename;
        int numFrames;
        int frameWidth;
        int frameHeight;
        int health;
        int tileID;
        int colorOffsetX;
        int colorOffsetY;
        int fps;
        NPC npc;
        std::string explosionSoundFile;
        int explosionVolume;
        int long scorevalue;
        int collisionDamage;
    };

    struct LevelBot
    {
        Bot type;
        int positionX;
        int positionY;
        std::string color;
        int powerUpProb;
        std::string powerUpName;
    };

    struct Item
    {
        std::string type;
        std::string filename;
        Weapon weapon;
        int frameWidth;
        int frameHeight;
        int fps;
        int numFrames;
        int healPercentage;
        int collisionDamage;
    };

    struct LevelItem
    {
        Item type;
        int positionX;
        int positionY;
        int value;
    };

    struct Background
    {
        std::string filename;
        int scrollspeed;
        std::string soundfile;
        int volume;
    };

    struct Statusbar
    {
        std::string filename;
        int frameWidth;
        int frameHeight;
        int letterCount;
        int capitalOffset;
        int minusculeOffset;
        int numberOffset;
        int offsetToMid;
    };

    struct Profile
    {
        std::string name;
        Weapon actualWeapon;
        std::vector<Weapon> boughtWeapons;
        std::vector<Item> boughtPowerUps;
        std::map<std::string, int> highscores;
        int money;
    };


    /**
     * This constructor loads the settings files and profiles
     * @param resPath Path to the res-Directory
     * @param noLevel Bool if the given string points to the resPath or to a level xml file
     */
    XML(std::string resPath, bool noLevel);

    /**
     * This constructor loads the given xml file. Exceptions as documented for the load() method can occur.
     * @param xmlFilename Name of xmlFile with level information.
     */
    XML(std::string xmlFilename);

    /**
     * This constructor generates a minimal level specification with default values.
     */
    XML();

    /**
     * Stores game information into XML file. By default it overwrites the original file. If desired you can specify
     * another location by the setFilename method.
     * @throw std::ios_base::failure If file could not be saved.
     */
    void save();

    /**
     * Set XML filename.
     * @param filename XML file for game specification.
     */
    void setFilename(std::string filename)
    { m_filename = filename; }

    /**
     * Get current name of XML file for level specification.
     * @return XML filename
     */
    std::string getFilename()
    { return m_filename; }

    /**
     * Set level id.
     * @param id Unique level id.
     */
    void setId(int id)
    { m_id = id; }

    /**
     * Set level name.
     * @param levelname Name of level.
     */
    void setLevelname(const std::string& levelname)
    {
        m_levelname = levelname;
    }

    /**
     * Set tileset.
     * @param tileset The tileset.
     */
    void setTileset(const std::string& tileset)
    {
        m_tileset = tileset;
    }

    /**
     * Set background.
     * @param background The background.
     */
    void setBackground(const Background& background)
    {
        m_background = background;
    }

    /**
     * Set Player.
     * @param The player.
     */
    void setPlayer(const Player& player)
    {
        m_player = player;
    }

    /**
     * Set Statusbar.
     * @param The statusbar.
     */
    void setStatusbar(const Statusbar& statusbar)
    {
        m_statusbar = statusbar;
    }

    /**
     * Get level id.
     * @return level id.
     */
    int getId()
    { return m_id; }

    /**
     * Get the current Levelname
     * @return m_levelname
     */
    std::string getLevelname()
    { return m_levelname; }

    /**
     * Get the current tileset
     * @return m_tileset
     */
    std::string getTileset()
    { return m_tileset; }

    /**
     * Get the current Background
     * @return m_background
     */
    Background getBackground()
    { return m_background; }

    /**
     * Get the Player
     * @return m_player
     */
    Player getPlayer()
    { return m_player; }

    /**
     * Get the Statusbar
     * @return m_statusbar
     */
    Statusbar getStatusbar()
    { return m_statusbar; }

    /************************************** LEVEL STRUCT METHODS **************************************/

    /**
     * Set single level bot.
     * @param position Number of the level bot.
     * @param lBot The level bot.
     * @throw range_error If no level bot is available with the given number.
     */
    void setLevelBot(unsigned int position, LevelBot lBot);

    /**
     * Set all level bots at a time.
     * @param levelBots Vector of level bots.
     */
    void setLevelBots(const std::vector<LevelBot>& levelBots)
    {
        m_level_bots = levelBots;
    }

    /**
     * Set single level item.
     * @param position Number of the level item.
     * @param lItem The level item.
     * @throw range_error If no level item is available with the given number.
     */
    void setLevelItem(unsigned int position, LevelItem lItem);

    /**
     * Set all level items at a time.
     * @param lItems Vector of level items
     */
    void setLevelItems(const std::vector<LevelItem>& lItems)
    {
        m_level_items = lItems;
    }

    /**
     * Get the LevelBot at given number
     * @param number Position of LevelBot
     * @return LevelBot at position number
     * @throw range_error If no LevelBot is available with the given number.
     */
    LevelBot getLevelBot(unsigned int number);

    /**
     * Get all LevelBots
     * @return Vector with all LevelBots
     */
    std::vector<LevelBot> getLevelBots()
    { return m_level_bots; }

    /**
     * Get the LevelItem at given number
     * @param number Position of LevelItem
     * @return LevelItem at position number
     * @throw range_error If no LevelItem is available with the given number.
     */
    LevelItem getLevelItem(unsigned int number);

    /**
     * Get all LevelItems
     * @return Vector with all LevelItems
     */
    std::vector<LevelItem> getLevelItems()
    { return m_level_items; }

    /**
     * Add additional LevelBot.
     * @param lBot The new LevelBot.
     */
    void addLevelBot(LevelBot lBot)
    { m_level_bots.push_back(lBot); }

    /**
     * Add an additional LevelItem.
     * @param lItem The new LevelItem.
     */
    void addLevelItem(LevelItem lItem)
    { m_level_items.push_back(lItem); }

    /**
     * Remove a LevelBot.
     * @param position Number of the LevelBot.
     * @throw range_error If no LevelBot is available with the given number.
     */
    void removeLevelBot(unsigned int position);

    /**
     * Remove a LevelItem.
     * @param position The number of the LevelItem.
     * @throw range_error If no LevelItem is available with the given number.
     */
    void removeLevelItem(unsigned int position);

    /**
     * Returns the total number of LevelBots.
     * @return Total number of LevelBots.
     */
    unsigned int levelBotSize()
    { return m_level_bots.size(); }

    /**
     * Returns the total number of LevelItems.
     * @return Total number of LevelItems.
     */
    unsigned int levelItemSize()
    { return m_level_items.size(); }

    /************************************** SETTINGS STRUCT METHODS **************************************/

    /**
     * Get the Bot at given number
     * @param number Position of Bot
     * @return Bot at position number
     * @throw range_error If no bot is available with the given number.
     */
    Bot getBot(unsigned int number);

    /**
     * Get all Bots
     * @return Vector with all Bots
     */
    std::vector<Bot> getBots()
    { return m_bots; }

    /**
     * Get the Item at given number
     * @param number Position of Item
     * @return Item at position number
     * @throw range_error If no item is available with the given number.
     */
    Item getItem(unsigned int number);

    /**
     * Get all Items
     * @return Vector with all Items
     */
    std::vector<Item> getItems()
    { return m_items; }

    /**
     * Get the Weapon at given number
     * @param number Position of Weapon
     * @return Weapon at position number
     * @throw range_error If no weapon is available with the given number.
     */
    Weapon getWeapon(unsigned int number);

    /**
     * Get all Weapons
     * @return Vector with all Weapons
     */
    std::vector<Weapon> getWeapons()
    { return m_weapons; }

    /**
     * Returns the total number of bots.
     * @return Total number of bots.
     */
    unsigned int botSize()
    { return m_bots.size(); }

    /**
     * Returns the total number of items.
     * @return Total number of items.
     */
    unsigned int itemSize()
    { return m_items.size(); }

    /**
     * Returns the total number of weapons.
     * @return Total number of weapons.
     */
    unsigned int weaponSize()
    { return m_weapons.size(); }

    /************************************** PROFILE STRUCT METHODS **************************************/

    /**
     * Set single profile.
     * @param position Number of the profile.
     * @param profile The profile.
     * @throw range_error If no profile is available with the given number.
     */
    void setProfile(unsigned int position, Profile profile);

    /**
     * Set all profiles at a time.
     * @param profiles Vector of profiles
     */
    void setProfiles(const std::vector<Profile>& profiles)
    {
        m_profiles = profiles;
    }

    /**
     * Get the Profile at given number
     * @param number Position of Profile
     * @return Profile at position number
     * @throw range_error If no profile is available with the given number.
     */
    Profile getProfile(unsigned int number);

    /**
     * Get all Profiles
     * @return Vector with all Profiles
     */
    std::vector<Profile> getProfiles()
    { return m_profiles; }

    /**
     * Add an additional Profile.
     * @param profile The new Profile.
     */
    void addProfile(Profile profile)
    { m_profiles.push_back(profile); }

    /**
     * Remove a Profile.
     * @param position Number of the Profile.
     * @throw range_error If no Profile is available with the given number.
     */
    void removeProfile(unsigned int position);

    /**
     * Returns the total number of profiles.
     * @return Total number of profiles.
     */
    unsigned int profileSize()
    { return m_profiles.size(); }

    /**
     * Saves the profile file
     * @throw std::ios_base::failure If file could not be saved.
     */
    void saveProfiles();

    /**
     * Get the explosion image filename
     * @return string with the explosion image filename
     */
    std::string getExplosions();

    /**
     * Set the explosion image filename
     * @param filename Path to the explosion image file
     */
    void setExplosions(std::string filename)
    {
        m_explosions = filename;
    }

private:
    /* XML Filename */
    std::string m_filename;

    /* XML Data Variables */
    int m_id;
    std::string m_levelname;
    std::string m_tileset;
    Background m_background;
    Player m_player;
    Statusbar m_statusbar;
    std::string m_explosions;


    std::vector<XML::LevelBot> m_level_bots;
    std::vector<XML::LevelItem> m_level_items;

    std::vector<XML::Bot> m_bots;
    std::vector<XML::Item> m_items;
    std::vector<XML::Weapon> m_weapons;

    /* File Path to profiles.xml */
    std::string profile_path;
    std::vector<XML::Profile> m_profiles;

    std::map<std::string, int> m_requiredAttributes;


    /**
     * Load XML game information into several structures.
     * @throw domain_error If unknown tag found or the xml file does not contain all required attributes.
     * @throw invalid_argument If xml file could not be accessed.
     */
    void load();

    /**
     * Initialize our requiredAttributes-Map with default values. Required by the constructors.
     */
    void init();

    /**
     * Load XML game bots into several structures.
     * @param filename location of the settings file
     * @throw domain_error If unknown tag found or the xml file does not contain all required attributes.
     * @throw invalid_argument If xml file could not be accessed.
     */
    void loadBots(std::string filename);

    /**
     * Returns the weapon struct from m_weapons by the given name
     *
     * @param weaponName Name of the weapon to search for
     * @return Weapon struct
     * @throws domain_error When weapon was not found
     */
    XML::Weapon getWeaponByName(std::string weaponName);

    /**
     * Load XML game items into several structures.
     * @param filename location of the settings file
     * @throw domain_error If unknown tag found or the xml file does not contain all required attributes.
     * @throw invalid_argument If xml file could not be accessed.
     */
    void loadItems(std::string filename);

    /**
     * Load XML game weapons into several structures.
     * @param filename location of the settings file
     * @throw domain_error If unknown tag found or the xml file does not contain all required attributes.
     * @throw invalid_argument If xml file could not be accessed.
     */
    void loadWeapons(std::string filename);

    /**
     * Load XML game profiles into several structures.
     * @param filename location of the profiles file
     * @throw domain_error If unknown tag found or the xml file does not contain all required attributes.
     * @throw invalid_argument If xml file could not be accessed.
     */
    void loadProfiles(std::string filename);
};

#endif //XML_HPP
