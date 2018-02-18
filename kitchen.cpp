#include "kitchen.hpp"

/******************************************************************************
 * abstraction: a kitchen
 * purpose: allow joe to make a cup of coffee if he has correct ingredients
 * how-to: link with others spaces or use as stand-alone with nullptrs
 * functionality: can move joe around, allow him to interact
 * ***************************************************************************/
const string READY = "Making coffee...\n...\n...\n...\nCoffee Made!\n\n";
const string NOT_READY = "Joe doesn't have coffee beans or the coffee grinder\n\n";

/******************************************************************************
 * description: constructor, sets up room and allocates memory
 * args: none
 * restrictions: none 
 * returns: none
 * ***************************************************************************/
Kitchen::Kitchen(){
	//left will point to hallway, right to kitchen
	
	top = left = right = bottom = nullptr; //updated as spaces are linked
	first = true; //first time entering room
	welcome_message = K_WELCOME;
	height = 10;
	width = 30;


	p_door = new Door(5, 0, LEFT);
	n_door = new Door(height - 1, width / 2, BOTTOM);

	//set up coffee station
	coffee_station = new Station(2, width -2);
	coffee_station->set_messages(READY, NOT_READY);
	coffee_station->set_icon(COFFEE_STATION);

	create_layout();
	layout[coffee_station->get_y()][coffee_station->get_x()] = coffee_station;
}

/******************************************************************************
 * description: destructor, dellocates memory
 * args: 	
 * restrictions: 
 * returns:
 * ***************************************************************************/
Kitchen::~Kitchen(){
	del_layout();
	delete n_door;
	delete p_door;
	delete coffee_station;
}

/******************************************************************************
 * description: updates kitchen based on the user's choice of action,
 * 				checks if joe can make coffee or not and sets coffee_station
 * 				accordingly
 * args: 	
 * restrictions: 
 * returns: a bool to represent whether or not joe has left and hence whether
 * 			the room needs to be displayed again
 * ***************************************************************************/
bool Kitchen::update(){
	
	//only allow joe to make coffee if he has the correct ingredients
	if(joe->has("coffee beans") && joe->has("coffee grinder") ){
		coffee_station->make_ready();
	}
	if(coffee_station->was_used() && !joe->has("mug of coffee")){
		joe->drop_objects();
		joe->add("mug of coffee");
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
void Kitchen::enter_room(Space* previous){

	//if joe entered for the left door, place 1 spot right of it
	if(previous == left){
		joe->set_yx(p_door->get_y(), p_door->get_x() + 1);
	}
	else{
		joe->set_yx(n_door->get_y() - 1, n_door->get_x()); //1 spot above 

	}

	//reset next coords (will be updated with wasd before next move)
	joe->next_to_current();
	layout[joe->get_y()][joe->get_x()] = joe;
}

/******************************************************************************
 * description:
 * args: 
 *		
 * restrictions: 
 * returns:
 ****************************************************************************/

