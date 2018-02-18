#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "space.hpp"
#include "item.hpp"

const string S_WELCOME = "\n\nJoe is now in the storage room. Help him pick the\n"
						"necessary supplies for making coffee from the chest [M]\n"
						"So that he can take them to the kitchen and brew his coffee\n\n";

class Storage : public Space{
	private:
		Chest* cupboard; //stores items that joe must grab to progress in game
		void use_chest();
	public:
		Storage();
		~Storage();
		bool update();
		void enter_room(Space*);
};

#endif
