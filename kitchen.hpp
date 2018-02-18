#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include "space.hpp"

const string K_WELCOME = "\n\nJoe has finally made it to the kitchen!\n"
						"Assuming you have the right materials from the storage, \n"
						"Joe should be able to make a nice cup of Joe for himself.\n"
						"Head over to the coffe station [X] and make a cup of coffee\n\n";
								
class Kitchen : public Space{
	private:
		Station* coffee_station; //used to make coffee	
	public:
		Kitchen();
		~Kitchen();
		bool update();
		void enter_room(Space*);
};

#endif
