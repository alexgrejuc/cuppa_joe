#ifndef HALL_HPP
#define HALL_HPP

#include "space.hpp"

//printed when joe enters the room for the first time
const string HALL_WELCOME = "\n\nShhhhh! Everyone else in the house is still sleeping\n"
					"Guide Joe through the hallway quietely by avoiding the\n"
					"z's. If Joe thinks he might wake someone up he will start\n"
					"walking away from their z's, which might make it hard for him\n"
					"to get to the next room\n\n";

class Hall : public Space{
	private:
		//animated npc's
		Mover* z1;
		Mover* z2;
		Mover* z3;
		Mover* z4;
		void move_z(Mover*); //move the npc's correctly
	public:
		Hall();
		~Hall();
		bool update();
		void enter_room(Space*);
};

#endif
