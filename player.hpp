#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "item.hpp"

class Player : public Item{
	//friend class Bedroom;
	//friend class Chest;

	private:
		int next_y;
		int next_x;
		int capacity; //the max objects joe can hold
		vector<string> hands;	

	public:
		Player();
		Player(int, int);
		void set_next(int, int); //set next coordinates
		void next_to_current(); //set the next coordinates to the current ones
		void inc_dec_next(char, char);
		int get_next_y();
		int get_next_x();
		int interact();
		string remove();
		void add(string);
		void display();
		bool has(string) const;
		void drop_objects();
		bool at_capacity();
};

#endif
