#include <algorithm>
#include <string>

#include "Systems.hpp"

void Systems::addSystem(System* system)
{
    systems.push_back(system);
    std::sort(systems.begin(), systems.end(), [](System* a, System* b) { return a->getSortOrder() < b->getSortOrder(); });
}

void Systems::addSystem(System* system, int sortOrder)
{
    system->setSortOrder(sortOrder);
    addSystem(system);
}

void Systems::removeSystem(System* system)
{
    systems.erase(std::remove(systems.begin(), systems.end(), system), systems.end());
}

void Systems::process(double deltaTime)
{
    for (auto* system : systems) system->process(deltaTime);
}