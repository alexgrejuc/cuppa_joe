#ifndef SPACE_HPP
#define SPACE_HPP

#include "player.hpp"
#include "item.hpp"
#include <string>

using std::string;

//consts used to label doors
const int TOP = 1;
const int RIGHT = 2;
const int BOTTOM = 3;
const int LEFT = 4;

class Space{
	protected:
		Space* top, *left, *right, *bottom; //links to rooms
		Space* next_room;
		int height;
		int width;
	   	bool first;
		string welcome_message;	//printed when a room is first entered
		Door* p_door, *n_door; //next and previous doors
		Floor* floor;
		Wall* wall; 
		Item*** layout; //used to keep track of each room
		static Player* joe; //joe is common to all the rooms
		char action;
		void get_new_coord();
		bool is_move() const;
		bool is_next_room() const;
		bool is_interact();	
		int item_x, item_y;
		void create_layout(); //used to construct each space 
		void del_layout(); //used in each destructor
	public:
		virtual bool update();
		void display();
		void set_action(char);
	   	void set_links(Space*, Space*, Space*, Space*);
		void traverse_room();
		Space* get_next_room();
		virtual void enter_room(Space* ) =0;
};

#endif	
