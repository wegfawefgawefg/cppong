// #include "game.hpp"

// int main() {
// 	Game game = Game();
//     game.run();
// 	return 0;
// }

#include <iostream>
#include <vector>
#include <string>

class Car{
	public:
		std::string name = "Car";
	Car(){
		std::cout << "Car created" << std::endl;
	};
	virtual ~Car(){
		std::cout << "Car destroyed" << std::endl;
	};
	virtual void drive(){
	}
};

class Truck: public Car{
	public:
		std::string name = "Truck";
	Truck(){
		std::cout << "Truck created" << std::endl;
	};
	~Truck(){
		std::cout << "Truck destroyed" << std::endl;
	};
	void drive(){
		std::cout << "Truck driving" << std::endl;
		std::cout << "\t" << name << " is driving" << std::endl;
	};
};

class Jeep: public Car{
	public:
		std::string name = "Jeep";
	Jeep(){
		std::cout << "Jeep created" << std::endl;
	};
	~Jeep(){
		std::cout << "Jeep destroyed" << std::endl;
	};
	void drive(){
		std::cout << "Jeep driving" << std::endl;
		std::cout << "\t" << name << " is driving" << std::endl;
	};
};

int main(){
	std::vector<Car*> cars;
	cars.push_back(new Truck());
	cars.push_back(new Jeep());
	for(auto& car: cars){
		car->drive();
	};
}

//// holder scope is managed correctly
//
// class Holder{
// 	public:
// 		int value;

// 	Holder(int value): value(value){
// 		std::cout << "Holder created with value " << value << std::endl;
// 	};
// 	~Holder(){
// 		std::cout << "Holder destroyed with value " << value << std::endl;
// 	};
// };
//
// class Grabber{
// 	public:
// 		Holder& holder;
//
// 	Grabber(Holder& holder): holder(holder){};
// };	
//
// void context(Holder& h){
// 	Grabber g(h);
// }
//
// int main(){
// 	Holder h(1);
// 	context(h);
// 	Grabber g(h);
// 	std::cout << "End of program" << std::endl;
// 	return 0;
// }

