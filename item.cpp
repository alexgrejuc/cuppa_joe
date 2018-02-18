#include "item.hpp"
#include "space.hpp"
#include <iostream>

#include "utilities.hpp"

using std::cout;
using std::endl;

/******************************************************************************
 * A collection of Item derived class functions
******************************************************************************/


/******************************************************************************
 * class: Item
 * abstraction: an Item, abstract class 
 * purpose: represent the most basic elements that an item in the game needs
 * how-to: get and set values, instantiate as a derived class 
 * functionality: get and set values
 * ***************************************************************************/

/******************************************************************************
 * description: collection of getters and setters common to all Items
 * args: self-explanatory	
 * restrictions: coordinates must exist for the size of room
 * returns: self-explanatory
 * ***************************************************************************/
int Item::get_x() const{
	return x;
}

int Item::get_y() const{
	return y;
}

void Item::set_x(int x){
	this->x = x;
}

void Item::set_y(int y){
	this->y = y;
}

void Item::set_yx(int y, int x){
	this->y = y;
	this->x = x;
}

char Item::get_icon() const{
	return icon;
}

void Item::set_icon(char c){
	icon = c;
}

bool Item::is_special(){
	return special; 
}

/******************************************************************************
*******************************************************************************
 * class: door
 * abstraction: a door
 * purpose: prevent joe from entering a room he shouldn't be in yet, allow joe
 * 			to move from room to room
 * how-to: place a door on the layout in desired location
 * functionality: can lock/unlock or interact
 * ***************************************************************************
*****************************************************************************/


/******************************************************************************
 * description: Door constructors, default and non-defualt
 * args: 
 * 		y coordinate
 * 		x coordinate
 * 		location, an integer used to determine which door (top, right, etc)
 * restrictions: none
 * returns: none
 * ***************************************************************************/
Door::Door(int y, int x, int location){
	set_yx(y,x);
	special = true;
	is_locked = false;
	icon = DOOR;
	this->location = location; 
}

Door::Door(){
	set_yx(-1, -1);
	special = true;
	is_locked = false;
	icon = DOOR;
}

/******************************************************************************
 * description: prints a message if the door is locked, returns door location
 * 				to allow room traversal if not
 * args: none
 * restrictions: none
 * returns: location (evaluated as true in update, or 0 if joe does not traverse
 * 			to next room
 * ***************************************************************************/
int Door::interact(){
	if(is_locked == true){
		cout << "Joe grabs the handle, but is overcome with a feeling\n"
				"that he is forgetting something." << endl;
		return 0;
	}
	else {
		return location;
	}
}

/******************************************************************************
 * description: door getters and setters for lock and location
 * args: 	
 * restrictions: 
 * returns:
 * ***************************************************************************/
void Door::toggle_lock(){
	is_locked = false;	
}

void Door::lock(){
	is_locked = true;
}

int Door::get_location(){
	return location;
}


/******************************************************************************
*******************************************************************************
 * class: floor
 * abstraction: a floor for the layout of a space
 * purpose: represent a floor tile, allow joe to walk on it
 * how-to: place in a space
 * functionality: can interact if turned on (with special = true)
 * ***************************************************************************
*****************************************************************************/

Floor::Floor(){
	set_yx(-1, -1);
	icon = FLOOR;
	special = false;
}

int Floor::interact(){
	cout << "The floor" << endl;
	return 0;
}


/******************************************************************************
*******************************************************************************
 * class: wall
 * abstraction: a wall for the layout of a space
 * purpose: represent a wall tile, prevent joe from going off the layout
 * how-to: place in the layout of a space
 * functionality: can interact if turned on (with special = true)
 * ***************************************************************************
*****************************************************************************/

//default constructor, see .hpp for variable info
Wall::Wall(){
	set_yx(-1, -1);
	icon = WALL;
	special = false; 
}

int Wall::interact(){
	cout << "The wall" << endl;
	return 0;
}



/******************************************************************************
*******************************************************************************
 * class: alarm
 * abstraction: an alarm that must be turned off
 * purpose: one of the components necessary to beat the game, must be turned off
 * 			before joe can leave the room
 * how-to: place in the bedroom 
 * functionality: can be turned off through interact, on_state can be
 * 					viewed
 * ***************************************************************************
*****************************************************************************/


//constructors, see .hpp for variable info
Alarm::Alarm(int y, int x){
	set_yx(y, x);
	icon = ALARM;
	on_state = true;
	special = true; 
}

Alarm::Alarm(){
	set_yx(-1, -1);
	special = true;
	on_state = true;
	icon = ALARM;
}

//setter
bool Alarm::is_on(){
	return on_state;
}

/******************************************************************************
 * description: turns alarm off and prints message if on, prints that it off
 * 				otherwise
 * args: none
 * restrictions: none 
 * returns: none
 * ***************************************************************************/
int Alarm::interact(){
	if(on_state == true){
		on_state = false;
		cout << "The alarm is now off" << endl;
	}
	else{
		cout << "The alarm is off, as it should be" << endl;
	}

	return 0;
}



/******************************************************************************
*******************************************************************************
 * class: Mover
 * abstraction: a moving NPC
 * purpose: an npc that moves back and forth across a room
 * how-to: place in room, write code for their movement as desired
 * functionality: can change direction
 * ***************************************************************************
*****************************************************************************/

//constructors, see .hpp for var info
Mover::Mover(char c){
	icon = c;
	special = false;
	direction = -1;
}

Mover::Mover(char c, int y, int x){
	icon = c;
	special = false;
	direction = -1;

	set_yx(y, x);
}

//allows user to set forward/backward and step size
Mover::Mover(char c, int y, int x, int direction){
	icon = c;
	special = false;
	this->direction = direction;

	set_yx(y, x);
}

//can be turned on with special = true
int Mover::interact(){
	cout << "Get out of the way!" << endl;
	return 0;
}

/******************************************************************************
 * description: getters and setters for mover
 * args: 
 * restrictions: 
 * returns:
 * ***************************************************************************/

int Mover::get_direction(){
	return direction; 
}

//reverses direction
void Mover::set_direction(){
	direction = -1 * direction;
}


/******************************************************************************
*******************************************************************************
 * class: Chest
 * abstraction: a chest that stores items
 * purpose: stores some of the items that Joe needs to make his coffee
 * how-to: place in layout of a room that needs a chest
 * functionality: add, remove, view contents, interact
 * ***************************************************************************
*****************************************************************************/

//constructors, add items to the chest in addition to normal item construction
Chest::Chest(){
	icon = CHEST;
	x = y = -1; // needs to be set to valid value
	special = true; //can be interacted with

	//poor way to do this, I was very tired
	string beans = "coffee beans";
	string grinder = "coffee grinder";
	string flour = "sack of flour";
	string tea = "tea";
	string dust = "dust";

	capacity = 5;

	contents.resize(capacity);
	contents[0] = beans;
	contents[1] = tea;
	contents[2] = flour;
	contents[3] = grinder;
	contents[4] = dust;
}

Chest::Chest(int y, int x){
	this->y = y;
	this->x = x;

	icon = CHEST;
	special = true;

	string beans = "coffee beans";
	string grinder = "coffee grinder";
	string flour = "sack of flour";
	string tea = "tea";
	string dust = "dust";

	capacity = 10;

	contents.resize(5);
	contents[0] = beans;
	contents[1] = tea;
	contents[2] = flour;
	contents[3] = grinder;
	contents[4] = dust;
}

//allows user to add, remove, or view in chest
//functions called based on return value, in the class that uses Chest
int Chest::interact(){
	int choice = 0;

	choice = menu(0, 3, "0)leave chest 1)take item 2)add item 3)view contents ");
	
	return choice; //lets Space call proper functions
}

/******************************************************************************
 * description: displays the contents of the chest
 * args: noen
 * restrictions: none (handles all cases) 
 * returns: none
 * ***************************************************************************/
void Chest::display(){
	//if chest is not empty, display all contents
	if(contents.size() > 0){
		cout << "\nchest contents: " << endl;
		for(int i = 0; i < contents.size(); i++){
			cout << i << ")" << contents[i] << " ";
		}
		cout << endl;
	}
	else {
		cout << "The chest is empty" << endl;
	}
	cout << endl;
}

/******************************************************************************
 * description: removes an item from the chest
 * args: none
 * restrictions: none
 * returns: the object that was removed from the chest 
 * ***************************************************************************/
string Chest::remove(){
	//if not empty
	if(contents.size() > 0){
		display(); //show values so user has numbers to choose from
		int choice = -1; //store users choice
		choice = menu (0, contents.size(), "Enter an item number to remove: ");
		string object = contents[choice];
		contents.erase(contents.begin() + choice); //remove choice from contents
		return object;
	}
	else {
		cout << "Nothing to remove\n" << endl;
		return "nothing"; 
	}
}

/******************************************************************************
 * description: adds an object to the chest
 * args: object, the object to be added to the chest
 * restrictions: objects must be limited as desired by user
 * returns: none
 * ***************************************************************************/
void Chest::add(string object){
	//joe returns "nothing" if he has nothing to add
	if(contents.size() < capacity && object != "nothing"){ 
		contents.push_back(object);
	}
	display();
}


/******************************************************************************
*******************************************************************************
 * class: Station
 * abstraction: a "station", something that can be interacted with to advance
 * 				the game, but only after requirements are met
 * purpose: add requirements for winning the game
 * how-to: place in room, set messages, decide on icon and conditions necessary
 * 			for readiness
 * functionality: can interact to ready
 * ***************************************************************************
*****************************************************************************/

//constructors
Station::Station(int y, int x){
	set_yx(y, x);
	ready = false;
	used = false;
	special = true;

	//placeholder values
	icon = 'Y';
	ready_message = "nothing happens";
	not_ready = "not ready";
}

/******************************************************************************
 * description: interacts with station, sets ready if conditions have been met
 * args: none
 * restrictions: none 
 * returns: integer, can be used for more complicated interactions
 * ***************************************************************************/
int Station::interact(){
	if(ready){
		cout << ready_message << endl;
		used = true;
	}
	else {
		cout << not_ready << endl;
	}

	return 0;
}

/******************************************************************************
 * description: getters and setters for Station
 * args: 
 * restrictions: 
 * returns:
 * ***************************************************************************/

bool Station::is_ready(){
	return ready;
}

void Station::make_ready(){
	ready = true;
}

bool Station::was_used(){
	return used;
}

//messages are what is printed to the user if the interaction is successful
//and the station if ready (r_mess) or what is printed if joe needs to 
//do a prerequisite thing for the station (n_mess)
void Station::set_messages(string r_mess, string n_mess){
	ready_message = r_mess;
	not_ready = n_mess;
}

