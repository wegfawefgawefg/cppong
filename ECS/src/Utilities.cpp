//
// Created by Kyle Dougan on 6/6/22.
//

#include <dirent.h>
#include <sstream>
#include "Utilities.h"


glm::vec2 getAlignOffsets(Align align, int width, int height)
{
    int x = 0;
    int y = 0;
    switch (align)
    {
        case Align::TOP_LEFT:
            break;
        case Align::TOP_CENTER:
            x = -width / 2;
            break;
        case Align::TOP_RIGHT:
            x = -width;
            break;
        case Align::CENTER_LEFT:
            y = -height / 2;
            break;
        case Align::CENTER:
            x = -width / 2;
            y = -height / 2;
            break;
        case Align::CENTER_RIGHT:
            x = -width;
            y = -height / 2;
            break;
        case Align::BOTTOM_LEFT:
            y = -height;
            break;
        case Align::BOTTOM_CENTER:
            x = -width / 2;
            y = -height;
            break;
        case Align::BOTTOM_RIGHT:
            x = -width;
            y = -height;
            break;
    }
    return glm::vec2(x, y);
}

float frand(float min, float max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(mt);
}

bool stringEndsWith(std::string *s, std::string *suffix)
{
    if (!s || !suffix)
        return false;
    size_t sLng = s->length();
    size_t suffixLng = suffix->length();
    if (suffixLng > sLng)
        return false;
    return s->compare(sLng - suffixLng, suffixLng, *suffix) == 0;
}

std::vector<std::string> getFilesInDirectory(const std::string &directory, const std::string &pattern)
{
    std::vector<std::string> files;
    DIR *dir = opendir(directory.c_str());
    struct dirent *ent;
    if (dir == nullptr)
    {
        throw std::runtime_error("Failed to open directory: " + directory);
    }
    // regex pattern for file name
    std::vector<std::string> patterns;
    if (pattern.find('|') != std::string::npos)
    {
        // split by pipe
        std::stringstream ss(pattern);
        std::string item;
        while (std::getline(ss, item, '|'))
            patterns.push_back(item);
    }
    else
        patterns.push_back(pattern);

    while ((ent = readdir(dir)) != nullptr)
    {
        std::string fileName = ent->d_name;
        if (fileName == "." || fileName == "..")
            continue;
        // if the filename ends with any of the patters, add it to the list
        for (auto &patt: patterns)
            if (stringEndsWith(&fileName, &patt))
            {
                files.push_back(fileName);
                break;
            }
    }
    closedir(dir);
    return files;
}
