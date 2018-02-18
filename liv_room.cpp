#include "liv_room.hpp"

/******************************************************************************
 * abstraction: a living room
 * purpose: add a space for joe to interact with in cuppa_joe game
 * how-to: link to other rooms or place joe in the room
 * functionality: can move joe around and allow him to interact with sofa
 * ***************************************************************************/
const string SOFA_READY = "Joe sits down (use your imagination) and enjoys his cuppa"
						" joe\n\n";
const string SOFA_NOT_READY = "Joe gazes longingly at the sofa, but what's a sofa without"
								"morning coffee?\n\n";
/******************************************************************************
 * description: constructor, sets up room and allocates memory
 * args: none
 * restrictions: none 
 * returns: none
 * ***************************************************************************/
Liv_room::Liv_room(){
	//left will point to hallway, right to kitchen
	top = left = right = bottom = nullptr;
	
	first = true;
	welcome_message = L_MESSAGE;
	height = 30;
	width = 30;

	//allocate door memory
	p_door = new Door(0, width/2, TOP);
	n_door = new Door(height - 1, width / 2, BOTTOM);
	n_door->lock(); //locked until joe has consued his coffee on the sofa
	
	//allocate and place sofa
	sofa = new Station(height/2, width /2); 
	sofa->set_messages(SOFA_READY, SOFA_NOT_READY);
	sofa->set_icon(SOFA);

	create_layout();
	layout[sofa->get_y()][sofa->get_x()] = sofa;
}

/******************************************************************************
 * description: destructor, dellocates memory
 * args: 	
 * restrictions: 
 * returns:
 * ***************************************************************************/
Liv_room::~Liv_room(){
	del_layout();
	delete n_door;
	delete p_door;
	delete sofa;
}

/******************************************************************************
 * description: updates living room based on the user's choice of action,
 * 				checks if joe can sit in the sofa and sets it accordingly
 * args: 	
 * restrictions: 
 * returns: a bool to represent whether or not joe has left and hence whether
 * 			the room needs to be displayed again
 * ***************************************************************************/
bool Liv_room::update(){
	
	//joe can only enjoy his coffee on the sofa once he has it
	if(joe->has("mug of coffee") ){
		sofa->make_ready();
	}
	if(sofa->was_used() && !joe->has("joy")){
		joe->drop_objects();
		joe->add("joy"); //who doesn't feel better after coffee? (Mormons, probably)
		n_door->toggle_lock();
	}

	return Space::update();
}

/******************************************************************************
 * description: places joe in the correct location when he enters the room
 * args: previous, the room that joe can in through. Used to find correct 
 * 		coordinates to place joe in
 * restrictions: 
 * returns:
 ****************************************************************************/
void Liv_room::enter_room(Space* previous){
	
	//if joe entered through top door, place 1 spot under
	if(previous == top){
		joe->set_yx(p_door->get_y() + 1, p_door->get_x());
	}
	else{
		joe->set_yx(n_door->get_y() - 1, n_door->get_x()); //1 spot above

	}

	//reset to valid coords
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

