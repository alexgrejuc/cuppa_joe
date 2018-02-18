#include "bedroom.hpp"
#include <iostream>

using std::cout;
using std::endl; 

/******************************************************************************
 * abstraction: a bedroom
 * how-to: call update() or enter_room(), call display (through base class)
 * functionality: sets up a bedroom and allows Joe to move around it, turn off
 * 				the alarm, and enter/exit the room.
 * ***************************************************************************/

/******************************************************************************
 * description: Default constructor, initializes all necessary variables,
 * 				places items, creates the layout and places Joe
 * args: none
 * restrictions: none 
 * returns: none
 * ***************************************************************************/
Bedroom::Bedroom(){
		
	first = true;
	top = left = right = bottom = nullptr; //updated once rooms are assigned

	height = 10;
	width = 10;

	welcome_message = BED_WELCOME;	

	//place and lock door
	n_door = new Door(5, width - 1, RIGHT);
	n_door->lock();

	p_door = nullptr; //only one door in this room

	alarm = new Alarm(6, 6);

	joe->set_yx(4, 4);
	joe->set_next(4,4);

	//places all items that belong in every Space
	create_layout();

	//place Joe and alarm
	layout[joe->get_y()][joe->get_x()] = joe;	
	layout[alarm->get_y()][alarm->get_x()] = alarm;
}

/******************************************************************************
 * description: updates the room by moving Joe to his new location, performing
 * 				the interaction, or turning off the alarm and unlocking the 
 * 				door. 
 * args: none
 * restrictions: none 
 * returns: true/false value that represents whether the room is to be 
 * 			displayed again (if not, this means Joe has left the room, so it does
 * 			not need to be displayed). 
 * ***************************************************************************/
bool Bedroom::update(){

	if(!alarm->is_on() ) {
		n_door->toggle_lock();
	}

	return Space::update();
}

/******************************************************************************
 * description: places Joe in the correct location if he enters the room
 * args: 
 * 		previous, the room that Joe came in from. Not used in this case, but 
 * 		used in all other Space derived classes. (and could be used if a 2nd
 * 		door is added)
 *		
 * restrictions: none
 * returns: none
 * ***************************************************************************/
void Bedroom::enter_room(Space* previous){
	//update Joe's coordinates to be by the door, then place him there
	joe->set_yx(n_door->get_y(), n_door->get_x() - 1);
	joe->next_to_current(); //set next coordinates to current
	layout[joe->get_y()][joe->get_x()] = joe;
}

/******************************************************************************
 * description: destructor
 * args: none
 *		
 * restrictions: n_door, alarm, and joe must be allocated 
 * 				joe is deleted here since he is a static member of all Spaces
 * 				must not be deleted elsewhere
 * returns: none
 * ***************************************************************************/
Bedroom::~Bedroom(){

	//free any memory that every Space derived class has, free layout
	//that was created in create_layout 
	del_layout();	

	delete n_door;
	delete alarm;
	delete joe;
}
