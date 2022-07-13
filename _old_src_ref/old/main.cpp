#include <iostream>
#include <vector>
#include <string>

class Entity{
	public:
		std::string name = "Entity";
	Entity(){
		std::cout << "Entity created" << std::endl;
	}
	~Entity(){
		std::cout << "Entity destroyed" << std::endl;
	};
};

class Mortal{
	public:
		void hurt(int damage){
			hp -= damage;
		}
		bool is_dead(){
			return hp <= 0;
		}
	private:
		int hp = 100;
};

class Transient: public Entity{
	public:
		float timer = 100.0;

		Transient(){
			timer = 100.0;
		}

		void age(float dt){
			timer -= dt;
			if(timer <= 0){
				timer = 0;
			}
		}	
		bool is_expired(){
			return timer <= 0.0;
		}

		float get_timer(){
			return timer;
		}
};



int main(){
	std::vector<Transient*> entities;
	entities.push_back(new Entity());
	entities.push_back(new Entity());
	for(auto& entity: entities){
		entity->age(1.0);
		std::cout << "Entity is " << entity->timer << " seconds old" << std::endl;
		if(entity->is_expired()){
			std::cout << "Entity expired" << std::endl;
		}
		// if(entity->is_dead()){
		// 	std::cout << "Entity is dead" << std::endl;
		// }
	};
}
