/*****************************************************************************
 * Program: utilities.cpp
 * Author: Alex Grejuc
 * Date: 7/21/17
 * Description: utility functions for getting good user input and menu
 * ***************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include "utilities.hpp"

using namespace std;

/*****************************************************************************
 * Description: prompts user with options to determine program outcome
 * Args:
 * 		min: the value of the first option (assuming list is sequential)
 * 		max: the value of the last option
 * 		message: the prompt for the user, contains list of options
 * Restrictions: min and max must be correctly determined
 * 				message must correspond with options in main program
 * Return: the validated integer value of the option selected by user 
 * ***************************************************************************/
int menu(int min, int max, string message){
	int option;
	
	//cout << "\nEnter a number to choose an option" << endl;	
	option = get_int(min, max, message); //get validated user input

	return option;
}

/******************************************************************************
 * description: checks if the input is a float value
 * args: 
 *		input: string that the user enters, which will be checked char by char
 * restrictions: none
 * returns: boolean value to show whether the user input is an float or not
 * ***************************************************************************/
bool is_float(string input){
	//if user only enters whitespace
	if(input.length() == 0){
		return false;
	}

	// loop checks each character for correct ascii value (0-9,-, or .)	
	else{
		for(int i = 0; i < input.length(); i++){
				if((input[i] < '0' | input[i] > '9') && input[i] != '-' && input[i] != '.'){
					return false;
				}
		}
	}
	return true;

}

/******************************************************************************
 * description: gets an float input from user
 * args:
 * 		min: the minimum value that can be accepted
 * 		max: the max value that can be accepted
 * 		message: a program-specific prompt for the user
 *		
 * restrictions: min and max values must be the correctly determined
 * returns: the float from a a validated string
 * ***************************************************************************/
float get_float(float min, float max, string message){
	string input; //stores input before validation

	//loop until good input
	do {
		cout << message;
		getline(cin, input);
		
		//check if input is an int and if it is in range
		if(is_float(input)){
			if(stof(input) >= min && stof(input) <= max){
				return stof(input);
			}
			else{
				cout << "out of range" << endl;
			}
		}
		else {
			cout << "not an integer" << endl;
		}
		cout << endl;
	} while(true);

}


/******************************************************************************
 * description: checks if the input is an integer value
 * args: 
 *		input: string that the user enters, which will be checked char by char
 * restrictions: none
 * returns: boolean value to show whether the user input is an integer or not
 * ***************************************************************************/
bool is_int(string input){
	//if user only enters whitespace
	if(input.length() == 0){
		return false;
	}

	// loop checks each character for correct ascii value (0-9 and - for negatives)	
	else{
		for(int i = 0; i < input.length(); i++){
				if((input[i] < '0' | input[i] > '9') && input[i] != '-'){
					return false;
				}
		}
	}
	return true;
}

/******************************************************************************
 * description: gets an integer input from user
 * args:
 * 		min: the minimum value that can be accepted
 * 		max: the max value that can be accepted
 * 		message: a program-specific prompt for the user
 *		
 * restrictions: min and max values must be the correctly determined
 * returns: the integer form a a validated string
 * ***************************************************************************/
int get_int(int min, int max, string message){
	string input; //stores input before validation

	//loop until good input
	do {
		cout << message;
		getline(cin, input);
		
		//check if input is an int and if it is in range
		if(is_int(input)){
			if(stoi(input) >= min && stoi(input) <= max){
				return stoi(input);
			}
			else{
				cout << "out of range" << endl;
			}
		}
		else {
			cout << "not an integer" << endl;
		}
		cout << endl;
	} while(true);
}

void get_floats_array(float min, float max, float* nums){

	int count = get_int(0, max, "How many numbers will you enter? ");

	nums = new float[count];

	string message;

	cout << "Enter your numbers" << endl; 

	for(int i = 0; i < count; i++){
		message += i;
		message += ": ";
		get_float(min, max, message); 
	}
	

}
/******************************************************************************
 * description: checks if string has proper input
 * args: message, the user input
 *		
 * restrictions: none
 * returns: bool to represent if user input is good
 * ***************************************************************************/
bool is_good_string(int max, string message){
	if(message.length() == 0){
		cout << "You entered a blank name" << endl;
		return false;
	}
	else if(message.length() > max){
		cout << "Too long" << endl;
	}
	else{
		return true;
	}
}

/******************************************************************************
 * description: gets a string from the user
 * args: message, the message to prompt the iser
 *		
 * restrictions: none
 * returns: the user input
 * ***************************************************************************/
string get_string(int max, string message){
	string input;
	bool bad_input;

	//ask for input until good input given
	do{
		bad_input = false;
		cout << message;
		getline(cin, input);
		bad_input = !is_good_string(max, input);
	} while(bad_input);

	return input;
}

char game_menu(string message, string options){
	//char character;
	bool bad_input;
	string input;

	do{
		input = get_string(1, message);

		for(int i = 0; i < options.length(); i++){
				bad_input = !(input.at(0) == options[i]);
				if(!bad_input) break;
		}

	} while (bad_input);

	return input.at(0);
}

/*char get_char(int max, string message, string options){
	string input;
	bool bad_input;

	//ask for input until good input given
	do{
		bad_input = false;
		cout << message;
		getline(cin, input);
		//bad_input = !is_good_string(max, input);
		
		if(is_good_string(max, input)){
			for(int i = 0; i < options.length(); i++){
				bad_input = !(input.at(0) == options[i]);
				if(bad_input){
					cout << "bad" << endl;
				}
			}
		}

	} while(bad_input);

	return input.at(0);
}*/

/******************************************************************************
 * description: placeholder for future additions
 * args: 
 *		
 * restrictions: 
 * returns:
 * ***************************************************************************/

