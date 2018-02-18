#include "hall.hpp"

#include <iostream>
using std::cout;
using std::endl;

/******************************************************************************
 * abstraction: a hallway (with moving npcs)
 * purpose: a room in the cuppa_joe game
 * how-to: call update() or enter room() (also see base class functions)
 * functionality: specialized update() and enter_room(), inherits all
 * 					functionality of Space base class 
 * ***************************************************************************/

/******************************************************************************
 * description: default constructor
 * args: none
 * restrictions: none 
 * returns: none
 * ***************************************************************************/
Hall::Hall(){
	top = left = right = bottom = nullptr; //updated in set_links()
	first = true; //if user has entered room for the first time

	welcome_message = HALL_WELCOME;

	height = 6;
	width = 20;


	//dynamically allocate doors
	n_door = new Door(2, width - 1, RIGHT);
	p_door = new Door(2, 0, LEFT);

	//Z's are moving npcs 
	z1 = new Mover('z', 1, width - 2);
	z2 = new Mover('Z', 2, width - 5);
	z3 = new Mover('z', 3, 2, 1);
	z4 = new Mover('Z', 4, 2, 1);

	create_layout();

	//place z's
	layout[z1->get_y()][z1->get_x()] = z1;
	layout[z2->get_y()][z2->get_x()] = z2;
	layout[z3->get_y()][z3->get_x()] = z3;
	layout[z4->get_y()][z4->get_x()] = z4;

}

/******************************************************************************
 * description: destructor
 * args: none
 * restrictions: none
 * returns: none
 * ***************************************************************************/
Hall::~Hall(){
	del_layout();
	delete n_door; 
	delete p_door;
	delete z1;
	delete z2;
	delete z3;
	delete z4;
}

/******************************************************************************
 * description: animates the z's so they move and bounce off the walls (or joe)
 * 				They also push joe if he is in the way
 * args: z, a Mover 
 * restrictions: none
 * returns: none
 * ***************************************************************************/
void Hall::move_z(Mover* z){
	//store values in variables to make array accessing more readable
	int z_y = z->get_y();
	int z_x = z->get_x();
	int z_next = z_x + z->get_direction(); //next value
	int z_next2 = z_next + z->get_direction(); //two values ahead

	//if the next tile is not a floor
	if(layout[z_y][z_next]->get_icon() != floor->get_icon() ){
		if(layout[z_y][z_next]->get_icon() == '@'){ //if the next tile is joe
		
			//if joe has a floor tile ahead of him, in the direction of the z
			if(layout[z_y][z_next2]->get_icon() == floor->get_icon()){ 

				//push joe
				joe->set_next(joe->get_y(), z_next2); 
				joe->set_x(z_next2); 
				layout[joe->get_y()][z_next2] = joe; 	
			}
			else { //if joe has a non-traversable tile in front of him (ex: wall) 
				z->set_direction(); //z turns around
				z_next = z_x + z->get_direction();
			}
		}
		else {
			z->set_direction(); //turn if the z hits a non-traversable tile
			z_next = z_x + z->get_direction(); 
		}
	}

	//previous tile of the z is reset to floor
	layout[z_y][z_x] = floor;
	layout[z_y][z_next] = z;
	z->set_x(z_next);
}

/******************************************************************************
 * description: enters the room at the correct location, based on where he 
 * 				came in from
 * args: previous, the room that joe came in from
 * restrictions: previous must be linked to hallway
 * returns: none
 * ***************************************************************************/
void Hall::enter_room(Space* previous){
	//set joe in the correct location, based on the door he came in through
	if(previous == left){
		joe->set_yx(p_door->get_y(), p_door->get_x() + 1);
	}
	else{
		joe->set_yx(n_door->get_y(), n_door->get_x() - 1);

	}

	//place joe on the layout and ensure he has valid coordinates 
	joe->next_to_current();
	layout[joe->get_y()][joe->get_x()] = joe;
}

/******************************************************************************
 * description: updates the room for every step
 * args: none
 * restrictions: none 
 * returns: a boolean, representing whether or not the room is to be displayed
 * 			(not displayed again if joe left to another room)
 * ***************************************************************************/
bool Hall::update(){
	layout[joe->get_y()][joe->get_x()] = joe;

	//if the room is to be updated
	//most of the updates are handlded in the base class function
	if(Space::update() ){
		move_z(z1);
		move_z(z2);
		move_z(z3);
		move_z(z4);
		return true; //room was updated
	}
	else {
		return false; //room not updated, joe left 
	}
}



/******************************************************************************
 * description:
 * args: 
 *		
 * restrictions: 
 * returns:
 * ***************************************************************************/

