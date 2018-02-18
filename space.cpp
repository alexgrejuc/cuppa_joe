#include "space.hpp"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
/******************************************************************************
 * abstraction: parent class for the rooms in the game, which have an ascii 
 * 				layout and allow the player to move around
 * purpose: store all the core information of the spaces and the core 
 * 			functionality 
 * how-to: see derived classes (abstract, cannot be used directly)
 * functionality: 
 * ***************************************************************************/


/******************************************************************************
 * description: creates the layout for each space by allocating memory for 
 * 				each tile type, making a 2-d Item* array, then placing the 
 * 				correct tiles (wall on perimeter, floor on inside)
 * args: none
 * restrictions: none
 * returns: none
 * ***************************************************************************/
void Space::create_layout(){
	
	//allocate floor and wall tiles
	floor = new Floor;
	wall = new Wall;

	//create 2-d Item* array
	layout = new Item**[height];

	for(int i = 0; i < height; i++){
		layout[i] = new Item*[width];
	}

	//place floors
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			layout[i][j] = floor;
		}
	}

	//place walls on sides
	for(int i = 0; i < height; i++){
		layout[i][0] = wall;
		layout[i][width - 1] = wall;
	}

	//place walls on top and bottom
	for(int j = 1; j < width - 1; j++){
		layout[0][j] = wall;
		layout[height - 1][j] = wall;
	}

	//bedroom has no p_door
	if(p_door != nullptr){
		layout[p_door->get_y()][p_door->get_x()] = p_door;
	}

	//all rooms have n_door
	layout[n_door->get_y()][n_door->get_x()] = n_door;
}

/******************************************************************************
 * description: frees the memory that all spaces must have (layout, floor, walls)
 * args: none
 * restrictions: must only be used in destructor, otherwise space will not 
 * 				function correctly
 * returns:
 * ***************************************************************************/
void Space::del_layout(){
	//free the array
	for(int i = 0; i < height; i++){
		delete [] layout[i];
	}	
	delete [] layout;
	delete floor;
	delete wall;
}

/******************************************************************************
 * description: sets the links between rooms
 * args: top, right, bottom, and left rooms, respectively
 * restrictions: pointers must be valid, memory for each should not be 
 * 				deallocated until game is over
 * returns: 
 * ***************************************************************************/
void Space::set_links(Space* t, Space* r, Space* b, Space* l){
	top = t;
	right = r;
	bottom = b;
	left = l;
}

/******************************************************************************
 * description: displays the visual representation of the room
 * args: 
 * restrictions: 
 * returns:
 * ***************************************************************************/
void Space::display(){	
	//if joe has entered the room for the first time
	if(first){ 
		cout << welcome_message;
		first = false;
	}

	//print each icon in the array
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			cout << (layout[i][j])->get_icon();
		}
		cout << endl;
	}
}

/******************************************************************************
 * description: determines if the action will place joe in a valid location
 * args: none
 * restrictions: none
 * returns: bool to represent whether the move was valid or not 
 * ***************************************************************************/
bool Space::is_move() const{
	
	//if joe is within the bounds of layout
	if(joe->get_next_y() < height && joe->get_next_x() < width){
		//if floor tile
		if(layout[joe->get_next_y()][joe->get_next_x()]->get_icon() == floor->get_icon()){
			return true;
		}
		else if(layout[joe->get_next_y()][joe->get_next_x()]->get_icon() == '~'){ //used in outdoors
			return true;
		}
		else{
			joe->set_next(joe->get_y(), joe->get_x()); //joe does not move so next coords are same as current
			if(action != 'e' || action!= 'v'){
				//if joe bumped into something that he cannot walk on
				cout << "Joe is incredibly angry at the supernatual forces that stubbed his toe" << endl;
			}
			return false; 
		}
	}
}

/******************************************************************************
 * description: determine if there is a special object around Joe that he can
 * 				interact with
 * args: none
 * restrictions: joe must not be on the edge of layout (should not happen if
 * 				walls were placed correctly)
 * returns: bool to represent whether or not joe is adjacent to a special object
 * ***************************************************************************/
bool Space::is_interact(){
	int x = joe->get_x(); //to make syntax more readable
	int y = joe->get_y();

	//check previous and next tile in all directions
	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			if(layout[y + i][x + j]->is_special() ){
				item_y = y + i; //store coords of item so interact() can be called by space
				item_x = x + j;
				return true;				
			}
		}
	}

	return false; //no special items adjacent to joe
}

/******************************************************************************
 * description: updates the room by the appropriate action based on user
 * 				input
 * args: none
 * restrictions: action must be validated before set in space 
 * returns: bool, to reflect whether the room should be displayed (not displayed
 * 			if joe has left the room)
 * ***************************************************************************/
bool Space::update() {
	if(action == 'e'){ //if interacting
		if(is_interact() ){ //look for special item adjacent to joe
			//doors return a 1 if they are unlocked and interacted with
			if( layout[item_y][item_x]->interact() ){				
				return false; //returns false if joe interacted with unlocked door
			}
		}

	}
	else if(action == 'v'){ //if user wishes to see inventory
		joe->display();
	}	
	else { //if user chose to move 
		get_new_coord();
		if(is_move()){ //move joe only if valid 
			layout[joe->get_y()][joe->get_x()] = floor;
			layout[joe->get_next_y()][joe->get_next_x()] = joe;
			joe->set_yx(joe->get_next_y(), joe->get_next_x());
		}
	}
	return true; //returns true if the room should be displayed
}

/******************************************************************************
 * description: finds the correct room to move Joe to if he has 
 * 				interacted with an unlocked dooe
 * args: 
 * restrictions: correct pointers must have been set in the space
 * returns:
 * ***************************************************************************/
void Space::traverse_room(){
	int room_num = layout[item_y][item_x]->interact();

	//set the correct next room
	switch(room_num){
		case TOP: next_room = top; break;
		case RIGHT: next_room = right; break;
		case BOTTOM: next_room = bottom; break;
		case LEFT: next_room = left; break;
	}

	//joe is no longer in the room, replace with floor
	layout[joe->get_y()][joe->get_x()] = floor;
}


void Space::set_action(char a){
	action = a;
}

/******************************************************************************
 * description: gets the new coordinates for joe based on the user's desired
 * 				move direction
 * args: 
 * restrictions: new coords must be validated in update() before they are used
 * returns:
 * ***************************************************************************/
void Space::get_new_coord(){
	switch(action){
		case 'w': //move up
				joe->inc_dec_next('-', 'y');
				break;
		case 'a': //move left
				joe->inc_dec_next('-', 'x');
				break;
		case 's': //move down
				joe->inc_dec_next('+', 'y');
				break;
		case 'd': //move right
				joe->inc_dec_next('+', 'x');
				break;
	}
}

//gets the next room
Space* Space::get_next_room(){
	return next_room;
}
