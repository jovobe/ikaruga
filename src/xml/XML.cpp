#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include "XML.hpp"

using std::string;
using std::cout;
using std::endl;
using boost::property_tree::ptree;
using boost::property_tree::xml_writer_make_settings;

XML::XML(std::string resPath, bool noLevel)
{
    if (!boost::filesystem::exists(boost::filesystem::path(resPath)))
    {
        throw std::domain_error("Invalid path given!");
    }

    boost::filesystem::path res_settings(resPath);

    res_settings = boost::filesystem::absolute(res_settings);
    res_settings = res_settings.normalize();

    std::string advanced_settings;

    // Check whether it's the level path or the ressources Path
    while (res_settings.parent_path().string().size() - 1 == res_settings.parent_path().string().find_last_of("res") &&
           res_settings.parent_path().string().find_last_of("res") != 0)
    {
        res_settings = res_settings.parent_path();
    }
    res_settings = res_settings.normalize();

    if (!boost::filesystem::exists(res_settings) || !boost::filesystem::is_directory(res_settings))
    {
        throw std::domain_error("Invalid path given!");
    }

    if (res_settings.string().size() - 1 != res_settings.string().find_last_of("res") ||
        res_settings.string().find_last_of("res") == 0)
    {
        throw std::domain_error("Couldn't resolve ressources path!");
    }

    profile_path = res_settings.string();
    advanced_settings = res_settings.string();

    advanced_settings.append("/advanced_settings/");
    profile_path.append("/profiles/profiles.xml");

    loadWeapons(advanced_settings + "weapons.xml");
    loadBots(advanced_settings + "bots.xml");
    loadItems(advanced_settings + "items.xml");

    loadProfiles(profile_path);
}

XML::XML(std::string xmlFilename) : XML(xmlFilename, false)
{
    init();
    setFilename(boost::filesystem::path(xmlFilename).normalize().string());
    load();
}

XML::XML()
{
    init();

    setId(0);
    std::string relativePath = "../images/";
    setLevelname("Levelname");
    setTileset("tileset.lvl");
    Background b;
    b.filename = relativePath + "star_background_2_200x200.png";
    b.scrollspeed = 3;
    setBackground(b);
    Statusbar sb;
    sb.filename = relativePath + "statusbar_font_10x10.png";
    sb.frameWidth = 10;
    sb.frameHeight = 10;
    sb.letterCount = 26;
    sb.capitalOffset = 1;
    sb.minusculeOffset = 3;
    sb.numberOffset = 0;
    sb.offsetToMid = 1;
    setStatusbar(sb);
    Player p;
    p.filename = relativePath + "player_animated_55x43_transparent.png";
    p.numFrames = 24;
    p.frameWidth = 18;
    p.frameHeight = 32;
    p.positionX = 100;
    p.positionY = 40;
    p.stdWeapon.type = "LASER_GUN";
    p.colorOffsetX = 1320;
    p.colorOffsetY = 0;
    p.moveForceX = 100.0;
    p.moveForceY = 100.0;
    p.maxVel = 100.0;
    p.fps = 12;
    setPlayer(p);
}

void XML::init()
{
    //Initialize required attributes for a minimal xml file.
    m_requiredAttributes.insert(std::pair<string, int>("id", 0));
    m_requiredAttributes.insert(std::pair<string, int>("name", 0));
    m_requiredAttributes.insert(std::pair<string, int>("tileset", 0));
    m_requiredAttributes.insert(std::pair<string, int>("background", 0));
    m_requiredAttributes.insert(std::pair<string, int>("player", 0));
    m_requiredAttributes.insert(std::pair<string, int>("statusbar", 0));
    m_requiredAttributes.insert(std::pair<string, int>("explosions", 0));
}

void XML::load()
{
    std::size_t found = XML::getFilename().find_last_of("/\\");
    string path = XML::getFilename().substr(0, found);

    ptree pt;
    try
    {
        read_xml(XML::getFilename(), pt);
    }
    catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::xml_parser::xml_parser_error> > const& e)
    {
        std::cerr << boost::diagnostic_information(e);
        throw std::invalid_argument("Invalid path or filename.");
    }

    try
    {
        BOOST_FOREACH(const ptree::value_type& v, pt.get_child("level"))
                    {
                        if (v.first == "id")
                        {
                            m_id = v.second.get<int>("");
                            m_requiredAttributes["id"]++;
                        }
                        else if (v.first == "name")
                        {
                            m_levelname = v.second.get<string>("");
                            m_requiredAttributes["name"]++;
                        }
                        else if (v.first == "tileset")
                        {
                            m_tileset = v.second.get<string>("<xmlattr>.filename");
                            m_requiredAttributes["tileset"]++;
                        }
                        else if (v.first == "background")
                        {
                            m_background.filename = v.second.get<string>("<xmlattr>.filename");
                            m_background.scrollspeed = v.second.get<int>("scrollspeed");
                            m_background.soundfile = v.second.get<std::string>("soundfile");
                            m_background.volume = v.second.get<int>("volume");
                            m_requiredAttributes["background"]++;
                        }
                        else if (v.first == "player")
                        {
                            m_player.filename = v.second.get<string>("<xmlattr>.filename");
                            m_player.numFrames = v.second.get<int>("numFrames");
                            m_player.frameWidth = v.second.get<int>("frameWidth");
                            m_player.frameHeight = v.second.get<int>("frameHeight");
                            m_player.positionX = v.second.get<int>("positionX");
                            m_player.positionY = v.second.get<int>("positionY");

                            m_player.colorOffsetX = v.second.get<int>("colorOffsetX");
                            m_player.colorOffsetY = v.second.get<int>("colorOffsetY");
                            m_player.moveForceX = v.second.get<float>("moveForceX");
                            m_player.moveForceY = v.second.get<float>("moveForceY");
                            m_player.maxVel = v.second.get<float>("maxVel");
                            m_player.fps = v.second.get<int>("fps");
                            m_player.explosionSoundFile = v.second.get<std::string>("explosionSoundFile");
                            m_player.explosionVolume = v.second.get<int>("explosionVolume");
                            m_player.hitSoundFile = v.second.get<std::string>("hitSoundFile");
                            m_player.hitVolume = v.second.get<int>("hitVolume");
                            m_player.collisionDamage = v.second.get<int>("collisionDamage");
                            m_player.health = v.second.get<int>("health");
                            m_player.stdWeapon = getWeaponByName(v.second.get<string>("stdWeapon"));

                            m_requiredAttributes["player"]++;
                        }
                        else if (v.first == "statusBar")
                        {
                            m_statusbar.filename = v.second.get<string>("<xmlattr>.filename");
                            m_statusbar.frameWidth = v.second.get<int>("frameWidth");
                            m_statusbar.frameHeight = v.second.get<int>("frameHeight");
                            m_statusbar.letterCount = v.second.get<int>("letterCount");
                            m_statusbar.capitalOffset = v.second.get<int>("capitalOffset");
                            m_statusbar.minusculeOffset = v.second.get<int>("minusculeOffset");
                            m_statusbar.numberOffset = v.second.get<int>("numberOffset");
                            m_statusbar.offsetToMid = v.second.get<int>("offsetToMid");
                            m_requiredAttributes["statusbar"]++;

                        }
                        else if (v.first == "bot")
                        {
                            LevelBot lBot;
                            std::string type_tmp = v.second.get<string>("<xmlattr>.type");
                            bool foundType = false;
                            for (auto it = begin(m_bots); it != end(m_bots); it++)
                            {
                                if (type_tmp.compare(it->type) == 0)
                                {
                                    lBot.type = (*it);
                                    foundType = true;
                                }
                            }
                            if (false == foundType)
                            {
                                throw std::domain_error("Found unknown xml tag " + type_tmp + " on level.");
                            }
                            lBot.positionX = v.second.get<int>("positionX");
                            lBot.positionY = v.second.get<int>("positionY");
                            lBot.color = v.second.get<string>("color");
                            lBot.powerUpProb = v.second.get_child("powerUp").get<int>("<xmlattr>.probability");
                            lBot.powerUpName = v.second.get<string>("powerUp");

                            m_level_bots.push_back(lBot);
                        }
                        else if (v.first == "item")
                        {
                            LevelItem lItem;
                            std::string type_tmp = v.second.get<string>("<xmlattr>.type");
                            bool foundType = false;
                            for (auto it = begin(m_items); it != end(m_items); it++)
                            {
                                if (type_tmp.compare(it->type) == 0)
                                {
                                    lItem.type = *it;
                                    foundType = true;
                                }
                            }
                            if (false == foundType)
                            {
                                throw std::domain_error("Found unknown xml tag " + type_tmp + " on level.");
                            }
                            lItem.positionX = v.second.get<int>("positionX");
                            lItem.positionY = v.second.get<int>("positionY");
                            lItem.value = v.second.get<int>("value");

                            m_level_items.push_back(lItem);
                        }
                        else if (v.first == "explosions")
                        {
                            m_explosions = v.second.get<string>("<xmlattr>.filename");
                        }
                        else
                        {
                            throw std::domain_error(
                                    "Found unknown xml tag " + v.first + " on first child layer below level.");
                        }
                    }
    }
    catch (boost::exception const& e)
    {
        std::cerr << boost::diagnostic_information(e);
        throw std::domain_error("XML parsing failed. Did you use an invalid tag or attribute?");
    }

    //Check if it was possible to read the required number of the following tags.
    if (m_requiredAttributes["id"] != 1) //One id tag is required
    { throw std::domain_error("Required attribute id not available."); }
    if (m_requiredAttributes["name"] != 1)
    { throw std::domain_error("Required attribute name not available."); }
    if (m_requiredAttributes["tileset"] != 1)
    { throw std::domain_error("Required attribute tileset not available."); }
    if (m_requiredAttributes["background"] != 1)
    { throw std::domain_error("Required attribute background not available."); }
    if (m_requiredAttributes["player"] != 1)
    { throw std::domain_error("Required attribute player not available."); }
    if (m_requiredAttributes["statusbar"] != 1)
    { throw std::domain_error("Required attribute statusbar not available."); }
}

void XML::loadBots(std::string filename)
{
    ptree pt;
    try
    {
        read_xml(filename, pt);
    }
    catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::xml_parser::xml_parser_error> > const& e)
    {
        std::cerr << boost::diagnostic_information(e);
        throw std::invalid_argument("Invalid path or filename.");
    }

    try
    {
        BOOST_FOREACH(const ptree::value_type& v, pt.get_child("bots"))
                    {
                        if (v.first == "bot")
                        {
                            Bot bot;
                            bot.type = v.second.get<string>("<xmlattr>.type");
                            bot.filename = v.second.get<string>("filename");
                            bot.numFrames = v.second.get<int>("numFrames");
                            bot.frameWidth = v.second.get<int>("frameWidth");
                            bot.frameHeight = v.second.get<int>("frameHeight");
                            bot.health = v.second.get<int>("health");
                            bot.tileID = v.second.get<int>("tileID");
                            bot.colorOffsetX = v.second.get<int>("colorOffsetX");
                            bot.colorOffsetY = v.second.get<int>("colorOffsetY");
                            bot.fps = v.second.get<int>("fps");
                            bot.explosionSoundFile = v.second.get<std::string>("explosionSoundFile");
                            bot.explosionVolume = v.second.get<int>("explosionVolume");
                            bot.scorevalue = v.second.get < int
                            long > ("scoreValue");
                            bot.collisionDamage = v.second.get<int>("collisionDamage");

                            /* Get data from child node NPC */
                            NPC npc;
                            npc.type = v.second.get_child("npc").get<string>("<xmlattr>.type");
                            npc.move_function = v.second.get_child("npc").get_child("move").get<string>(
                                    "<xmlattr>.function");
                            npc.move_value = v.second.get_child("npc").get < signed
                            int > ("move");
                            npc.speed = v.second.get_child("npc").get < signed
                            int > ("speed");
                            npc.stdWeapon = getWeaponByName(v.second.get_child("npc").get<string>("stdWeapon"));
                            bot.npc = npc;
                            m_bots.push_back(bot);
                        }
                        else
                        {
                            throw std::domain_error(
                                    "Found unknown xml tag " + v.first + " on first child layer below bots.");
                        }
                    }
    }
    catch (boost::exception const& e)
    {
        std::cerr << boost::diagnostic_information(e);
        throw std::domain_error("XML parsing failed. Did you use an invalid tag or attribute?");
    }
}

void XML::loadItems(std::string filename)
{
    ptree pt;
    try
    {
        read_xml(filename, pt);
    }
    catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::xml_parser::xml_parser_error> > const& e)
    {
        std::cerr << boost::diagnostic_information(e);
        throw std::invalid_argument("Invalid path or filename.");
    }

    try
    {
        BOOST_FOREACH(const ptree::value_type& v, pt.get_child("items"))
                    {
                        if (v.first == "item")
                        {
                            Item i;
                            i.type = v.second.get<string>("<xmlattr>.type");
                            i.filename = v.second.get<string>("filename");
                            i.frameWidth = v.second.get<int>("frameWidth");
                            i.frameHeight = v.second.get<int>("frameHeight");
                            i.fps = v.second.get<int>("fps");
                            i.weapon = getWeaponByName(v.second.get<string>("weapon"));
                            i.numFrames = v.second.get<int>("numFrames");
                            i.healPercentage = v.second.get<int>("healPercentage");
                            i.collisionDamage = v.second.get<int>("collisionDamage");
                            m_items.push_back(i);
                        }
                        else
                        {
                            throw std::domain_error(
                                    "Found unknown xml tag " + v.first + " on first child layer below items.");
                        }
                    }
    }
    catch (boost::exception const& e)
    {
        std::cerr << boost::diagnostic_information(e);
        throw std::domain_error("XML parsing failed. Did you use an invalid tag or attribute?");
    }
}

void XML::loadWeapons(std::string filename)
{
    ptree pt;
    try
    {
        read_xml(filename, pt);
    }
    catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::xml_parser::xml_parser_error> > const& e)
    {
        std::cerr << boost::diagnostic_information(e);
        throw std::invalid_argument("Invalid path or filename.");
    }

    try
    {
        BOOST_FOREACH(const ptree::value_type& v, pt.get_child("weapons"))
                    {
                        if (v.first == "weapon")
                        {
                            Weapon w;
                            w.type = v.second.get<string>("<xmlattr>.type");
                            w.filename = v.second.get<string>("filename");
                            w.colorOffsetX = v.second.get<int>("colorOffsetX");
                            w.colorOffsetY = v.second.get<int>("colorOffsetY");
                            w.soundfile = v.second.get<std::string>("soundfile");
                            w.frameHeight = v.second.get<int>("frameHeight");
                            w.frameWidth = v.second.get<int>("frameWidth");
                            w.weaponOffsetX = v.second.get<float>("weaponOffsetX");
                            w.weaponOffsetY = v.second.get<float>("weaponOffsetY");
                            w.cooldown = v.second.get<float>("cooldown");
                            w.shootingVolume = v.second.get<int>("projectileVolume");
                            w.collisionDamage = v.second.get<int>("collisionDamage");
                            w.speed = v.second.get<float>("speed");
                            w.numFrames = v.second.get<int>("numFrames");
                            m_weapons.push_back(w);
                        }
                        else
                        {
                            throw std::domain_error(
                                    "Found unknown xml tag " + v.first + " on first child layer below weapons.");
                        }
                    }
    }
    catch (boost::exception const& e)
    {
        std::cerr << boost::diagnostic_information(e);
        throw std::domain_error("XML parsing failed. Did you use an invalid tag or attribute?");
    }
}

void XML::loadProfiles(std::string filename)
{
    ptree pt;
    try
    {
        read_xml(filename, pt);
    }
    catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::xml_parser::xml_parser_error> > const& e)
    {
        std::cerr << boost::diagnostic_information(e);
        throw std::invalid_argument("Invalid path or filename.");
    }

    try
    {
        BOOST_FOREACH(const ptree::value_type& v, pt.get_child("profiles"))
                    {
                        if (v.first == "profile")
                        {
                            Profile p;
                            p.name = v.second.get<string>("<xmlattr>.name");
                            p.money = v.second.get<int>("money");

                            std::string type_tmp = v.second.get_child("actualWeapon").get<string>("<xmlattr>.type");
                            bool foundType = false;
                            for (auto it = begin(m_weapons); it != end(m_weapons); it++)
                            {
                                if (type_tmp.compare(it->type) == 0)
                                {
                                    p.actualWeapon = *it;
                                    foundType = true;
                                }
                            }
                            if (false == foundType)
                            {
                                throw std::domain_error("Found unknown xml tag " + type_tmp + " on profileWeapon.");
                            }

                            /** Already bought Weapons **/
                            BOOST_FOREACH(const ptree::value_type& bw, v.second.get_child("boughtWeapons"))
                                        {
                                            if (bw.first == "weapon")
                                            {
                                                Weapon boughtWeapon;

                                                std::string type_tmp = bw.second.get<string>("<xmlattr>.type");
                                                bool foundType = false;
                                                for (auto it = begin(m_weapons); it != end(m_weapons); it++)
                                                {
                                                    if (type_tmp.compare(it->type) == 0)
                                                    {
                                                        boughtWeapon = *it;
                                                        foundType = true;
                                                    }
                                                }
                                                if (false == foundType)
                                                {
                                                    throw std::domain_error(
                                                            "Found unknown xml tag " + type_tmp + " on boughtWeapons.");
                                                }
                                                p.boughtWeapons.push_back(boughtWeapon);
                                            }
                                            else
                                            {
                                                throw std::domain_error("Found unknown xml tag " + bw.first +
                                                                        " on first child layer below boughtWeapons.");
                                            }
                                        }

                            /** Already bought PowerUps **/
                            BOOST_FOREACH(const ptree::value_type& bp, v.second.get_child("boughtPowerUps"))
                                        {
                                            if (bp.first == "powerUp")
                                            {
                                                Item boughtPowerUp;

                                                std::string type_tmp = bp.second.get<string>("<xmlattr>.type");
                                                bool foundType = false;
                                                for (auto it = begin(m_items); it != end(m_items); it++)
                                                {
                                                    if (type_tmp.compare(it->type) == 0)
                                                    {
                                                        boughtPowerUp = *it;
                                                        foundType = true;
                                                    }
                                                }
                                                if (false == foundType)
                                                {
                                                    throw std::domain_error("Found unknown xml tag " + type_tmp +
                                                                            " on boughtPowerUps.");
                                                }
                                                p.boughtPowerUps.push_back(boughtPowerUp);
                                            }
                                            else
                                            {
                                                throw std::domain_error("Found unknown xml tag " + bp.first +
                                                                        " on first child layer below boughtPowerUps.");
                                            }
                                        }

                            /** Level Highscores **/
                            BOOST_FOREACH(const ptree::value_type& scores, v.second.get_child("highscores"))
                                        {
                                            if (scores.first != "highscore")
                                            {
                                                throw std::domain_error("Found unknown xml tag " + scores.first +
                                                                        " on first child layer below highscores.");

                                            }
                                            std::string filename = scores.second.get<string>("<xmlattr>.filename");
                                            int scoreVal = scores.second.get<int>("");
                                            p.highscores.insert(std::pair<string, int>(filename, scoreVal));
                                        }

                            m_profiles.push_back(p);
                        }
                        else
                        {
                            throw std::domain_error(
                                    "Found unknown xml tag " + v.first + " on first child layer below profile.");
                        }
                    }
    }
    catch (boost::exception const& e)
    {
        std::cerr << boost::diagnostic_information(e);
        throw std::domain_error("XML-Profile parsing failed. Did you use an invalid tag or attribute?");
    }
}

void XML::save()
{
    ptree root;
    ptree level;
    ptree tileset;
    ptree explosions;
    ptree background;
    ptree player;
    ptree statusbar;

    /* Adding Level Information */
    level.put("id", m_id);
    level.put("name", m_levelname);

    /* Adding Tileset */
    tileset.put("<xmlattr>.filename", m_tileset);

    level.add_child("tileset", tileset);

    /* Adding Explosions */
    explosions.put("<xmlattr>.filename", m_explosions);

    level.add_child("explosions", explosions);

    /* Adding Background */
    background.put("<xmlattr>.filename", m_background.filename);
    background.put("scrollspeed", m_background.scrollspeed);
    background.put("soundfile", m_background.soundfile);
    background.put("volume", m_background.volume);

    level.add_child("background", background);

    /* Adding Statusbar */
    statusbar.put("<xmlattr>.filename", m_statusbar.filename);
    statusbar.put("frameWidth", m_statusbar.frameWidth);
    statusbar.put("frameHeight", m_statusbar.frameHeight);
    statusbar.put("letterCount", m_statusbar.letterCount);
    statusbar.put("capitalOffset", m_statusbar.capitalOffset);
    statusbar.put("minusculeOffset", m_statusbar.minusculeOffset);
    statusbar.put("numberOffset", m_statusbar.numberOffset);
    statusbar.put("offsetToMid", m_statusbar.offsetToMid);

    level.add_child("statusBar", statusbar);

    /* Adding Player */
    player.put("<xmlattr>.filename", m_player.filename);
    player.put("numFrames", m_player.numFrames);
    player.put("frameWidth", m_player.frameWidth);
    player.put("frameHeight", m_player.frameHeight);
    player.put("positionX", m_player.positionX);
    player.put("positionY", m_player.positionY);
    player.put("stdWeapon", m_player.stdWeapon.type);
    player.put("colorOffsetX", m_player.colorOffsetX);
    player.put("colorOffsetY", m_player.colorOffsetY);
    player.put("moveForceX", m_player.moveForceX);
    player.put("moveForceY", m_player.moveForceY);
    player.put("maxVel", m_player.maxVel);
    player.put("fps", m_player.fps);
    player.put("explosionSoundFile", m_player.explosionSoundFile);
    player.put("explosionVolume", m_player.explosionVolume);
    player.put("hitSoundFile", m_player.hitSoundFile);
    player.put("hitVolume", m_player.hitVolume);
    player.put("health", m_player.health);
    player.put("collisionDamage", m_player.collisionDamage);

    level.add_child("player", player);

    /* Adding Level_Bots */
    for (int i = 0; i < (int) m_level_bots.size(); i++)
    {
        ptree level_bot, powerUp;
        level_bot.put("<xmlattr>.type", m_level_bots[i].type.type);
        level_bot.put("positionX", m_level_bots[i].positionX);
        level_bot.put("positionY", m_level_bots[i].positionY);
        level_bot.put("color", m_level_bots[i].color);

        powerUp.put("<xmlattr>.probability", m_level_bots[i].powerUpProb);
        level_bot.add_child("powerUp", powerUp);
        level_bot.put("powerUp", m_level_bots[i].powerUpName);

        level.add_child("bot", level_bot);
    }

    /* Adding Level_Items */
    for (int i = 0; i < (int) m_level_items.size(); i++)
    {
        ptree level_item;
        level_item.put("<xmlattr>.type", m_level_items[i].type.type);
        level_item.put("positionX", m_level_items[i].positionX);
        level_item.put("positionY", m_level_items[i].positionY);
        level_item.put("value", m_level_items[i].value);

        level.add_child("item", level_item);
    }

    /* Setting up XML-Tree with root-Node */
    root.add_child("level", level);

    try
    {
        //Automatic indents of the xml file does not work on the same way with different versions because of a bug in
        //the boost library.
        //The following line works in boost 1.60, 1.58:
        //write_xml(getFilename(), root, std::locale(), xml_writer_make_settings<ptree::key_type>(' ', 4u));
        //The following line works in boost 1.54:
        //boost::property_tree::xml_writer_settings<char> settings (' ', 4u); write_xml(getFilename(), root, std::locale(), settings);
        //Without pretty format (all XML tags in one line) it works in all boost versions
        //write_xml(getFilename(), root, std::locale(), xml_writer_make_settings<ptree::key_type>(' ', 4u));
        write_xml(getFilename(), root, std::locale());
    }
    catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::xml_parser::xml_parser_error> > const& e)
    {
        std::cerr << boost::diagnostic_information(e);
        throw std::ios_base::failure("Cannot write file. Is it readonly?");
    }
}

/* Level Bots/Items - Getter/Setter */
void XML::setLevelItem(unsigned int position, XML::LevelItem lItem)
{
    if (position >= levelItemSize())
    { throw std::range_error("Index out of range."); }
    m_level_items[position] = lItem;
}

void XML::setLevelBot(unsigned int position, XML::LevelBot lBot)
{
    if (position >= levelBotSize())
    { throw std::range_error("Index out of range."); }
    m_level_bots[position] = lBot;
}

XML::LevelBot XML::getLevelBot(unsigned int number)
{
    if (number >= levelBotSize())
    { throw std::range_error("Index out of range."); }
    return m_level_bots[number];
}

XML::LevelItem XML::getLevelItem(unsigned int number)
{
    if (number >= levelItemSize())
    { throw std::range_error("Index out of range."); }
    return m_level_items[number];
}

void XML::removeLevelItem(unsigned int position)
{
    if (position >= levelItemSize())
    { throw std::range_error("Index out of range."); }
    m_level_items.erase(m_level_items.begin() + position);
}

void XML::removeLevelBot(unsigned int position)
{
    if (position >= levelBotSize())
    { throw std::range_error("Index out of range."); }
    m_level_bots.erase(m_level_bots.begin() + position);
}

/* Definition Getter */
XML::Bot XML::getBot(unsigned int number)
{
    if (number >= botSize())
    { throw std::range_error("Index out of range."); }
    return m_bots[number];
}

XML::Item XML::getItem(unsigned int number)
{
    if (number >= itemSize())
    { throw std::range_error("Index out of range."); }
    return m_items[number];
}

XML::Weapon XML::getWeapon(unsigned int number)
{
    if (number >= weaponSize())
    { throw std::range_error("Index out of range."); }
    return m_weapons[number];
}

void XML::setProfile(unsigned int position, XML::Profile profile)
{
    if (position >= profileSize())
    { throw std::range_error("Index out of range."); }
    m_profiles[position] = profile;
}

XML::Profile XML::getProfile(unsigned int number)
{
    if (number >= profileSize())
    { throw std::range_error("Index out of range."); }
    return m_profiles[number];
}

void XML::removeProfile(unsigned int position)
{
    if (position >= profileSize())
    { throw std::range_error("Index out of range."); }
    m_profiles.erase(m_profiles.begin() + position);
}

std::string XML::getExplosions()
{
    return m_explosions;
}

void XML::saveProfiles()
{
    ptree root;
    ptree profiles;

    for (int iProfile = 0; iProfile < (int) profileSize(); iProfile++)
    {
        ptree profile;
        ptree actualWeapon;
        ptree boughtWeapons;
        ptree boughtPowerUps;
        ptree highscores;

        Profile curProfile = getProfile(iProfile);

        /* Adding Profile Information */
        profile.put("<xmlattr>.name", curProfile.name);

        /* Adding actual Weapon */
        actualWeapon.put("<xmlattr>.type", curProfile.actualWeapon.type);
        profile.add_child("actualWeapon", actualWeapon);

        /* Adding bought Weapons */
        BOOST_FOREACH(Weapon weapon, curProfile.boughtWeapons)
                    {
                        ptree bWeapon;
                        bWeapon.put("<xmlattr>.type", weapon.type);
                        boughtWeapons.add_child("weapon", bWeapon);
                    }
        profile.add_child("boughtWeapons", boughtWeapons);

        /* Adding bought PowerUps */
        BOOST_FOREACH(Item item, curProfile.boughtPowerUps)
                    {
                        ptree powerup;
                        powerup.put("<xmlattr>.type", item.type);
                        boughtPowerUps.add_child("powerUp", powerup);
                    }
        profile.add_child("boughtPowerUps", boughtPowerUps);

        /* Adding highscores */
        std::pair<std::string, int> highScorePairs;
        BOOST_FOREACH(highScorePairs, curProfile.highscores)
                    {
                        ptree highscore;
                        highscore.put("<xmlattr>.filename", highScorePairs.first);
                        highscore.put_value(highScorePairs.second);
                        highscores.add_child("highscore", highscore);
                    }

        profile.add_child("highscores", highscores);

        /* Adding player money */
        profile.put("money", curProfile.money);

        /* Adding the profile to the upper level node */
        profiles.add_child("profile", profile);
    }

    /* Setting up XML-Tree with root-Node */
    root.add_child("profiles", profiles);

    try
    {
        //Automatic indents of the xml file does not work on the same way with different versions because of a bug in
        //the boost library.
        //The following line works in boost 1.60, 1.58:
        //write_xml(getFilename(), root, std::locale(), xml_writer_make_settings<ptree::key_type>(' ', 4u));
        //The following line works in boost 1.54:
        //boost::property_tree::xml_writer_settings<char> settings (' ', 4u); write_xml(getFilename(), root, std::locale(), settings);
        //Without pretty format (all XML tags in one line) it works in all boost versions
        //write_xml(getFilename(), root, std::locale(), xml_writer_make_settings<ptree::key_type>(' ', 4u));
        write_xml(profile_path, root, std::locale());
    }
    catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::xml_parser::xml_parser_error> > const& e)
    {
        std::cerr << boost::diagnostic_information(e);
        throw std::ios_base::failure("Cannot write file. Is it readonly?");
    }

};

XML::Weapon XML::getWeaponByName(std::string weaponName)
{
    Weapon foundWeapon;

    bool foundType = false;
    for (auto weapon : m_weapons)
    {
        if (weaponName.compare(weapon.type) == 0)
        {
            foundWeapon = weapon;
            foundType = true;
        }
    }

    if (false == foundType)
    {
        throw std::domain_error("Found unknown xml tag " + weaponName + " on level.");
    }

    return foundWeapon;
}

