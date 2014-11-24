// Aleksey Leshchuk
// CISP400V9AD7.cpp
// AD7 assignment, user interface for List class

#include <iostream>
#include <random>
#include <ctime>
#include "List.h"
using namespace std;

// options enum for user to select from menu
enum select{ INSERT=1, DELETE, REPOP, QUIT=-1};

// fillList template function generates a 20 NODE int array
void fillList(List<int>&);

// insertIntoList provides user interface for inserting an element into List
void insertIntoList(List<int>&);

// deleteFromList provides user interface for inserting an element into list
void deleteFromList(List<int>&);

// menu function provides user interface
select menu();

int main(){
    List<int> intList;
    fillList(intList);	// initialize List  with 20 random numbers
    select userSelection; // select variable to hold user selection
    void (*processList[4])(List<int>&);	    // function pointers 1-3, 0 is an offset
    processList[INSERT] = &insertIntoList;
    processList[DELETE] = &deleteFromList;
    processList[REPOP] = &fillList;


    do {
	intList.print(); // print generated List
	userSelection=menu();	// call menu and get user input
	processList[userSelection](intList);	// call user selected operation
    } while (userSelection != QUIT);

    return 0;
}

// fillList template function generates a 20 NODE int array
void fillList(List<int>& intList){
    int x;  // dummy variable used for deletion
    if ( !intList.isEmpty() ){ // if List isnt empty, remove all elements
	for (int i=0; i<intList.sizeOf();i++)
	    intList.removeFromBack(x);
    }
    default_random_engine generator(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> distr(0,200);

    for (int i=0; i<20; i++)
	intList.insertAtBack(distr(generator));
}

// insertIntoList provides user interface for inserting an element into List
void insertIntoList(List<int>& intList){
    int location, value;
    cout<<"\nEnter index where you want the new value to appear:"<<endl;
    cin>>location;
    cout<<"\nEnter the value you want added at this location: ";
    cin>>value;
    if (!intList.insert(location,value))    // if location is invalid print error
	cout<<"\nInvalid index, no data added to list.";
    else 
	intList.print();	// else print the list
}


// deleteFromList provides user interface for inserting an element into list
void deleteFromList(List<int>& intList){
    int value;
    cout<<"\nEnter an integer to delete: ";
    cin>>value;
    if (!intList.removeElement(value))	    // if value not found
	cout<<"\nThe number is not found.";
    else {			    // else print results
	cout<<value<<" is deleted from the list.\n";
	intList.print();
    }
}

// menu function provides user interface
select menu(){
    int selection;
    cout<<"\nPlease select one of the following selection or eneter -1 to exit:\n";
    cout<<"\t1. Insert an element to the List.\n";
    cout<<"\t2. Delete an element from the List.\n";
    cout<<"\t3. Repopulate the List information.\n:";
    cin>>selection;

    return static_cast<select>(selection);  // return user input cast to type selection
}
