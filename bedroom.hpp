#ifndef BEDROOM_HPP
#define BEDROOM_HPP

#include "space.hpp"

const string BED_WELCOME = "\nThis is Joe's bedroom. As you can see, he has\n"
							"just woken up. turn off his alarm (A) so he can\n"
							"leave the room through the door\n";

class Bedroom : public Space{
	private:
		Alarm* alarm;
	public:
		Bedroom();
		~Bedroom();
		bool update();
		void enter_room(Space*);
};


#endif
