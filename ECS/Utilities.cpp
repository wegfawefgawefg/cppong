//
// Created by Kyle Dougan on 6/6/22.
//

#include <dirent.h>
#include "Utilities.h"


std::vector<int> getAlignOffsets(Align align, int width, int height)
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
    return {x, y};
}

float frand(float min, float max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(mt);
}

std::vector<std::string> getFilesInDirectory(const std::string &directory)
{
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directory.c_str())) != nullptr)
    {
        try
        {
            while ((ent = readdir(dir)) != nullptr)
            {
                std::string fileName = ent->d_name;
                if (fileName != "." && fileName != "..")
                {
                    files.push_back(fileName);
                }
            }
        }
        catch (...)
        {
            closedir(dir);
            throw;
        }
    }
    return files;
}
