#include "storage.hpp"

#include <iostream>

using std::cout;
using std::endl;

/******************************************************************************
 * abstraction: a storage room 
 * purpose: model to storage room, a space in the game
 * how-to: link to other rooms or place joe if using as standalone
 * functionality: can move joe, allow him to interact (with the chest), move
 * 					to other rooms
 * ***************************************************************************/

/******************************************************************************
 * description: constructor, sets up room and allocates memory
 * args: none
 * restrictions: none 
 * returns: none
 * ***************************************************************************/
Storage::Storage(){
	
	//updated as links are set 
	top = left = right = bottom = nullptr;
	first = true;
	welcome_message = S_WELCOME; //printed when joe first enters the room
	height = width = 10;

	p_door = new Door(5, 0, LEFT);
	n_door = new Door(5, width - 1, RIGHT);
	cupboard = new Chest(5, 5);

	create_layout();
	layout[cupboard->get_y()][cupboard->get_x()] = cupboard; 
}

/******************************************************************************
 * description: destructor, dellocates memory
 * args: 	
 * restrictions: 
 * returns:
 * ***************************************************************************/
Storage::~Storage(){
	del_layout();
	delete n_door;
	delete p_door;
	delete cupboard;
}

/******************************************************************************
 * description: adds functionality to the chest. Lets joe add and remove items
 * 				and lets user see the contents
 * args: none
 * restrictions: 
 * returns:
 * ***************************************************************************/
void Storage::use_chest(){
	int choice = -1;

	//static cast so specialized functions can be called
	Chest* c = static_cast<Chest*>(layout[item_y][item_x]);
	
	do{
		choice = c->interact();
		switch(choice){		
			case 1: if(!joe-> at_capacity() ){ //user would like to take an item
						joe->add( c->remove() );
					}
					else {
						cout << "Joe's hands are full!" << endl;
					}
					break;

			case 2: c->add(joe->remove()); //user would like to add item
					break;
			case 3: c->display(); //user would just like to see what's inside
		}
	} while(choice);
}

/******************************************************************************
 * description: updates storage based on the user's choice of action,
 * args: 	
 * restrictions: 
 * returns: a bool to represent whether or not joe has left and hence whether
 * 			the room needs to be displayed again
 * ***************************************************************************/
bool Storage::update() {
	int choice = -1;

	//if user would like to interact
	if(action == 'e'){
		if(is_interact() ){			
			if( layout[item_y][item_x]->get_icon() == DOOR){
				return false; //return false if joe has left the room
			}
			else { //if the special object is not a door, it must be a chest
				use_chest();	
			}
		}
	}
	else if(action == 'v'){//if user would like to see inventory
		joe->display();
	}	
	else{//user would like to move
		get_new_coord();
		if(is_move()){
			layout[joe->get_y()][joe->get_x()] = floor;
			layout[joe->get_next_y()][joe->get_next_x()] = joe;
			joe->set_yx(joe->get_next_y(), joe->get_next_x());
		}
	}
	return true;
}

/******************************************************************************
 * description: places joe in the correct location when he enters the room
 * args: previous, the room that joe can in through. Used to find correct 
 * 		coordinates to place joe in
 * restrictions: 
 * returns:
 ****************************************************************************/
void Storage::enter_room(Space* previous){
	if(previous == left){
		joe->set_yx(p_door->get_y(), p_door->get_x() + 1);
	}
	else{
		joe->set_yx(n_door->get_y(), n_door->get_x() - 1);

	}
	
	//place joe in the room
	joe->next_to_current();
	layout[joe->get_y()][joe->get_x()] = joe;
}

/******************************************************************************
 * description:
 * args: 
 *		
 * restrictions: 
 * returns:
 * ***************************************************************************/

