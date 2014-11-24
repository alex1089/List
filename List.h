// Fig. 19.5: List.h 
//
// Template List class definition.
// Edited by Aleksey Leshchuk
// Added insert() and remove() methods
// CISP400 AD7 assignment

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "ListNode.h" // ListNode class definition


template< typename NODETYPE >
class List 
{
public:
    // default constructor
   List()
      : firstPtr( nullptr ), lastPtr( nullptr ) 
   { 
      // empty body
   } // end List constructor

   // destructor
   ~List()
   {
      if ( !isEmpty() ) // List is not empty
      {    
         std::cout << "Destroying nodes ...\n";

         ListNode< NODETYPE > *currentPtr = firstPtr;
         ListNode< NODETYPE > *tempPtr;

         while ( currentPtr != nullptr ) // delete remaining nodes
         {  
            tempPtr = currentPtr;
            std::cout << tempPtr->data << '\n';
            currentPtr = currentPtr->nextPtr;
            delete tempPtr;
         } // end while
      } // end if

      std::cout << "All nodes destroyed\n\n";
   } // end List destructor

   // insert(int location,NODETYPE &value) inserts value at location, returns true on sucess
   bool insert(const int& location, const NODETYPE& value){
       if (location<0 || location>size-1)   // if location is out of range
	   return false;
       if (location==0 || isEmpty())	// if insert at 1st element, or List is empty
	   insertAtFront(value);
       else if (location==size-1)	    // if insertAtBack
	   insertAtBack(value);
       else {
	   ListNode<NODETYPE>* newNode = getNewNode(value);  // get new node
	   ListNode<NODETYPE>* nodePtr = firstPtr;
	   ListNode<NODETYPE>* prevPtr;
	   for (int i=0;i<location;i++){	// iterate through array to reach the location element
	       prevPtr=nodePtr;		// save previous ptr
	       nodePtr=nodePtr->nextPtr;    
	   }
	   prevPtr->nextPtr=newNode;	// set location-1's nextPtr to point to newPtr
	   newNode->nextPtr=nodePtr;	// set newPtr's nextPtr to pointer and previous location
	   size++;			// increase size of List
       }
       return true;
   }

   // insert node at front of list
   void insertAtFront( const NODETYPE &value )
   {
      ListNode< NODETYPE > *newPtr = getNewNode( value ); // new node

      if ( isEmpty() ) // List is empty
         firstPtr = lastPtr = newPtr; // new list has only one node
      else // List is not empty
      {
         newPtr->nextPtr = firstPtr; // point new node to old 1st node
         firstPtr = newPtr; // aim firstPtr at new node
      } // end else
      size++;	    // increment size of List
   } // end function insertAtFront

   // insert node at back of list
   void insertAtBack( const NODETYPE &value )
   {
      ListNode< NODETYPE > *newPtr = getNewNode( value ); // new node

      if ( isEmpty() ) // List is empty
         firstPtr = lastPtr = newPtr; // new list has only one node
      else // List is not empty
      {
         lastPtr->nextPtr = newPtr; // update previous last node
         lastPtr = newPtr; // new last node
      } // end else
      size++;	// increment size of List
   } // end function insertAtBack

   // removeElement(NODETYPE) removes element if it exists in the List
   bool removeElement(const NODETYPE& value){
       ListNode<NODETYPE>* nodePtr= firstPtr;	// first node in list
       NODETYPE temp;
       for (int i=0; i<sizeOf(); i++){	// itirate through List 
	   if (nodePtr->data == value){	// if a match is found
	       removeIndex(i,temp);	// remove the element matched
	       return true;
	   } else { 
	       nodePtr=nodePtr->nextPtr;
	   }
       }
       return false;	// return false if value is not found in List
   }

   // removeIndex(int,NODETYPE) removes element from List, returns true on sucessful operation
   bool removeIndex(int element, NODETYPE &value){
       if (element >= size || element < 0)	// if element is out of bound, return false
	   return false;
       if (element == 0 && !isEmpty()) // if first element and List is not emepty
	   return removeFromFront(value);
       else if (element == size-1) {	// if last element selected
	   return removeFromBack(value);
       } else {
	   ListNode<NODETYPE>* tempPtr=firstPtr;
	   ListNode<NODETYPE>* prevPtr=nullptr;
	   for (int i=0; i<element; i++) {
	       prevPtr=tempPtr;
	       tempPtr=tempPtr->nextPtr;
	   }
	   value=tempPtr->data;
	   prevPtr->nextPtr=tempPtr->nextPtr;
	   delete tempPtr;  // deallocate memory
	   size--;	    // decrement size of List
	   return true;	    // successful remove of element
       }
   }

   // delete node from front of list
   bool removeFromFront( NODETYPE &value )
   {
      if ( isEmpty() ) // List is empty
         return false; // delete unsuccessful
      else 
      {
         ListNode< NODETYPE > *tempPtr = firstPtr; // hold item to delete

         if ( firstPtr == lastPtr )
            firstPtr = lastPtr = nullptr; // no nodes remain after removal
         else
            firstPtr = firstPtr->nextPtr; // point to previous 2nd node

         value = tempPtr->data; // return data being removed
         delete tempPtr; // reclaim previous front node
	 size--;    // decrement size of List
         return true; // delete successful
      } // end else
   } // end function removeFromFront

   // delete node from back of list
   bool removeFromBack( NODETYPE &value )
   {
      if ( isEmpty() ) // List is empty
         return false; // delete unsuccessful
      else 
      {
         ListNode< NODETYPE > *tempPtr = lastPtr; // hold item to delete

         if ( firstPtr == lastPtr ) // List has one element
            firstPtr = lastPtr = nullptr; // no nodes remain after removal
         else 
         {
            ListNode< NODETYPE > *currentPtr = firstPtr;

            // locate second-to-last element            
            while ( currentPtr->nextPtr != lastPtr )    
               currentPtr = currentPtr->nextPtr; // move to next node

            lastPtr = currentPtr; // remove last node
            currentPtr->nextPtr = nullptr; // this is now the last node
         } // end else

         value = tempPtr->data; // return value from old last node
         delete tempPtr; // reclaim former last node
	 size--;		// decrement size of List
         return true; // delete successful
      } // end else
   } // end function removeFromBack

   // is List empty?
   bool isEmpty() const 
   { 
      return firstPtr == nullptr; 
   } // end function isEmpty

   // display contents of List
   void print() const
   {
      if ( isEmpty() ) // List is empty
      {
         std::cout << "The list is empty\n\n";
         return;
      } // end if

      ListNode< NODETYPE > *currentPtr = firstPtr;

      std::cout << "The list is: ";

      while ( currentPtr != nullptr ) // get element data
      {
         std::cout << currentPtr->data << ' ';
         currentPtr = currentPtr->nextPtr;
      } // end while

      std::cout << "\n\n";
   } // end function print

   // sizeOf() returns number of elements in the List
   size_t sizeOf() const {
       return size;
   }

private:
   ListNode< NODETYPE > *firstPtr; // pointer to first node
   ListNode< NODETYPE > *lastPtr; // pointer to last node
   size_t   size;

   // utility function to allocate new node
   ListNode< NODETYPE > *getNewNode( const NODETYPE &value )
   {
	size++;	    // increment size of List
      return new ListNode< NODETYPE >( value );
   } // end function getNewNode
}; // end class List

#endif

/**************************************************************************
 * (C) Copyright 1992-2014 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
