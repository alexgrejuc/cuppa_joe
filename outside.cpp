#include "outside.hpp"

/******************************************************************************
 * abstraction: an outdoor space, the final space in the game
 * purpose: complete the game 
 * how-to: link to previous rooms ore use as standalone by placing joe
 * functionality: can move joe around and enter/exit through doors
 * ***************************************************************************/

/******************************************************************************
 * description: constructor, sets up room and allocates memory
 * args: none
 * restrictions: none 
 * returns: none
 * ***************************************************************************/
Outside::Outside(){
	
	//updated as rooms are linked
	top = left = right = bottom = nullptr; 
	first = true;
	welcome_message = O_MESSAGE; //printed to user the first time they enter

	height = 15;
	width = 30;

	p_door = new Door(0, width/2, TOP);
	n_door = new Door(height - 1, width / 2, BOTTOM);
	
	grass = new Floor;
	grass->set_icon('~');
	create_layout();

	layout[4][4]->set_icon(' ');

	//place grass
	for(int i = 1; i < height - 1; i++){
		for(int j = 1; j < width - 1; j++){
			layout[i][j] = grass;
		}
	}

	layout[0][0]->set_icon('|');
}

/******************************************************************************
 * description: destructor, dellocates memory
 * args: 	
 * restrictions: 
 * returns:
 * ***************************************************************************/
Outside::~Outside(){
	del_layout();
	delete n_door;
	delete p_door;
	delete grass;
}

/******************************************************************************
 * description: updates kitchen based on the user's choice of action
 * args: 	
 * restrictions: 
 * returns: a bool to represent whether or not joe has left and hence whether
 * 			the room needs to be displayed again
 * ***************************************************************************/
bool Outside::update(){
	return Space::update();
}

/******************************************************************************
 * description: places joe in the correct location when he enters the room
 * args: previous, the room that joe can in through. Used to find correct 
 * 		coordinates to place joe in
 * restrictions: 
 * returns:
 ****************************************************************************/
void Outside::enter_room(Space* previous){
	//if joe entered from the top
	if(previous == top){
		joe->set_yx(p_door->get_y() + 1, p_door->get_x());
	}
	//if joe entered from elsewhere (note: doesn't actually happen, here in
	//case space structure is changed
	else{
		joe->set_yx(n_door->get_y() - 1, n_door->get_x());

	}

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






