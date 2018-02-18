#ifndef LIV_ROOM_HPP
#define LIV_ROOM_HPP

#include "space.hpp"

const string L_MESSAGE = "\n\nJoe is now in the living room. Hopefully he was able\n"
						"to make his cup of coffee and now has it in hand. If he\n"
						"does, he sure would love to sit down on the sofa[H] and\n"
						"enjoy that cup of coffee before going to outside so he can leave for work\n\n";

class Liv_room : public Space{
	private:
		Station* sofa; //joe must interact with the sofa to get to the next room
	public:
		Liv_room();
		~Liv_room();
		bool update();
		void enter_room(Space*);
};

#endif
