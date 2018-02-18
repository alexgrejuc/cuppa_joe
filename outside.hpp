#ifndef OUTSIDE_HPP
#define OUTSIDE_HPP

#include "space.hpp"

const string O_MESSAGE = "Phew! Joe made it through yet another morning, but he\n"
						"couldn't have done it without you. It looks like you'll\n"
						"soon be parting ways, but Joe will always remember you \n"
						"(and any of the stubbed toes you gave him).\n" 
						"Make a path across the grass with all your extra steps and\n"
						"bring Joe to work when you are ready\n\n";

class Outside: public Space{
	private:
		Floor* grass;
	public:
		Outside();
		~Outside();
		bool update();
		void enter_room(Space*);
};

#endif
