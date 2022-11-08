/**
 * Filesystem.cpp
 * 
 * @date 29.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 * @author Patrick Steinforth (psteinforth@uni-osnabrueck.de)
 */
#include "Filesystem.hpp"

namespace ikaruga
{
    string Filesystem::getDirectoryPath(string filePath)
    {
        std::size_t found = filePath.find_last_of("/");
        string folderPath = filePath.substr(0, found + 1);
        return folderPath;
    }

    string Filesystem::getParentDirectory(string directoryPath, int level)
    {
        string folderPath = directoryPath;

        for (int i = 0; i < level; i++)
        {
            std::size_t found = folderPath.find_last_of("/");
            folderPath = folderPath.substr(0, found);
            folderPath = getDirectoryPath(folderPath);
        }

        return folderPath;
    }

    string Filesystem::setFileExtension(string filePath, string fileExtension)
    {
        string newFilePath = filePath.substr(0, filePath.find_last_of(".") + 1);
        newFilePath += fileExtension;
        return newFilePath;
    }

    std::vector<fs::path> Filesystem::findFiles(const fs::path& path,
                                                boost::regex pattern)
    {
        std::vector<fs::path> vec;
        if (!fs::is_directory(path)) //!path.empty()
        { throw std::invalid_argument("You have to provide a resource DIRECTORY!"); }

        fs::directory_iterator end; //default construction yields past-the-end

        for (fs::directory_iterator i(path); i != end; ++i)
        {
            // Skip if not a file
            if (!boost::filesystem::is_regular_file(i->status()))
            { continue; }

            boost::smatch match_result;

            if (!boost::regex_match(i->path().filename().string(), match_result, pattern))
            { continue; }

            // File matches, store it
            vec.push_back(i->path());
        }
        return vec;
    }
} /* namespace ikaruga */
