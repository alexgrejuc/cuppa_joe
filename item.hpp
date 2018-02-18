#ifndef ITEM_HPP
#define ITEM_HPP

#include <vector>
#include <string>
using std::string;
using std::vector;

//consts for item icons
const char DOOR = '}';
const char FLOOR = '.';
const char WALL = '#';
const char INTERACT = 'e';
const char ALARM = 'A';
const char CHEST = 'M';
const char COFFEE_STATION = 'X';
const char SOFA = 'H';

/******************************************************************************
 * A collection of Items, grouped together due to similar nature of each
 * and the number of Items
 * ***************************************************************************/

//abstract class
class Item{
	//friend class Space;

	protected:
		char icon;
		int x, y; //coordinates 
		bool special; //whether or not object can be interacted with

	public:
		int get_x() const;
		int get_y() const;
		void set_x(int);
		void set_y(int);
		void set_yx(int, int);
		char get_icon() const;
		void set_icon(char);
		bool is_special();
		virtual int interact()=0;
};

//#include "player.hpp"

class Door : public Item{
	private:
		bool is_open;
		bool is_locked;
		int location; //Top, right, left, bottom door, not coordinates
	public:
		Door(int, int, int);
		Door();
		int interact();
		void toggle_open();
		void toggle_lock();
		void lock();
		int get_location();
		//int set_trav(); 
};

class Alarm : public Item{
	private:
		bool on_state;
	public:
		Alarm();
		Alarm(int, int);
		int interact();
		bool is_on();
};

class Station : public Item{
	private:
		bool ready, used; //whether station can be used and has been used
		string ready_message; //prints if ready (when joe interacts)
		string not_ready; //prints if not ready 
	public:
		Station(int, int);
		int interact();
		bool is_ready();
		void make_ready();
		void set_messages(string, string);
		bool was_used();
};

class Floor : public Item{
	public:
		Floor();
		int interact();
};

class Wall : public Item{
	public:
		Wall();
		int interact();
};

class Mover: public Item{
	private:
		int direction; //+/-, increases or decreases y,x coordinates
	public:
		Mover(char = 'Z');
		Mover(char, int, int);
		Mover(char, int, int, int);
		int get_direction();
		void set_direction();
		int interact();
};


class Chest : public Item{
	//friend class Player; 
	private:
		int capacity; 
		vector<string> contents;
	public:
		Chest();
		Chest(int, int);
		int interact();
		void display();
		string remove();
		void add(string);
};

#endif
