#include <cmath>
#include "test_entity.hpp"
#include "game.hpp"
#include "random.hpp"
#include "utils.hpp"

TestEntity::TestEntity(glm::vec2 pos, glm::vec2 size) : Entity(pos, size) {
    this->target = pos;
}
TestEntity::~TestEntity() {}
void TestEntity::step(Game& game) {}
void TestEntity::collide(Game& game, Entity* entity) {
    std::cout << "test collision: " << this->id << std::endl;
}