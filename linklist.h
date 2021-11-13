/*************************************************************************/ /**
 * @file
 *****************************************************************************/

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#ifndef __FUNCTIONS__H__
#define __FUNCTIONS__H__

//using namespace std;


/**************************************************************************/ /**
* @brief This class is a linked list that contains a string, frequency and both the
         previous and next word in the list.  The List is composed of words read in from a
         short story input as a text file and is used to document the frequency
         of every list in the text file.
*/
class LinkList
{
private:
	/*!
	* @brief Holds word and frequency count
	*/
	struct node
	{
		int frequencyCount = 1; /*!< Frequency count */
		std::string word; /*!< Word of the node */
		node* next = nullptr; /*!< Next word in the list*/
		node* prev = nullptr; /*!< Previous word in the list*/
	};

	/*!< First node in the list.  This allows access to other nodes in list*/
	node* headptr;

	/*!< Last node in the list.  This allows access to other nodes in list*/
	node* tailptr;

	/*!< This function returns the end of the current node list.
	     @param curr a node in the list
         @returns curr last node in list*/
	node* getTail(node* curr);

	/*!< This function is a recursive merge sort
		 @param head head of list to be sorted
		 @returns merge function that merges separate lists together*/
	node* mergeSort(node* head);

	/*!< This function merges two linked lists together
	     @param first first set of nodes to be linked
	     @param second second set of nodes to be linked
	     @returns second - fully merged list*/
	node* merge(node* first, node* second);

	/*!< The partition function of the LinkedList used for quick sort method
		     which places the words in order of frequency count
			 @param head - the head node
			 @param end - the end node
			 @param newHead - the new head node
			 @param newEnd - the new end node
			 @return pivot - the node that was moved to the end for sorting*/
	node* partition(node* head, node* end, node** newHead, node** newEnd);

	/*!< This function starts the quick sort by getting newHead and newEnd
	     nodes and setting the pivot node.
	     @param head - the head node
	     @param end  - the end node
	     @return newHead node*/
	node* quickSortRecur(node* head, node* end);

	/*!< This function splits a linked list into smaller component lists for
		 merge sort
	     @param head the head of the list
	     @return temp - a split list*/
	node* split(node* head);

public:
	LinkList(); /*!< The constructor of the LinkedList*/
	~LinkList(); /*!< The destructor of the LinkedList*/

	/*!< The printFreqCount function of the LinkedList prints out the last word in the list
	     @param out this is the output stream it will print to*/
	void back(std::ostream &out);

	/*!< The find function of the LinkedList used to find words as needed.
	     @param word this is the word that is to be found in the LinkedList
	     @returns true if the word is found
	     @returns false if the word is not found*/
	bool find(std::string word);

	/*!<This function is the wrapper for the frequency quick sort functions, resets
		headptr to new sorted list*/
	void frequencySort();

	/*!< The get max frequency function of the LinkedList used to find the
	     maximum frequency of all the words in the list.
	     @returns max - the maximum frequency of the words in the list.*/
	int getMaxFrequency();

	/*!< The increment frequency function of the LinkedList used to increment
	     frequency of words as they are found in the list.
	     @param word this is the word whose frequency is to be incremented once
					 found in the LinkedList
	     @returns true if the word is found and it increases the frequency by one
	     @returns false if the word is not found*/
	bool incrementFrequency(std::string word);

	/*!< The insert function of the LinkedList used to insert 
	     words alphabetically as needed.
	     @param word this is the word that is to be inserted into the LinkedList
	     @returns true - if it inserted the words
	     @return  false - if it could not insert the words*/
	bool insert(std::string word);

	/*!< The isEmpty function of the LinkedList used to see if the list isEmpty
	     before inserting words.
	     @returns true - if the list is empty
	     @returns false - If the list is not empty*/
	bool isEmpty();

	/*!< This function is the overloaded mergesort for users to access.
		 Starts with headptr and then splits the list as necessary, using the
		 intermediary private functions*/
	void mergeSort();

	/*!< This function prints the linked list in its current order to any given
		 output stream
		 @param out - used for the output stream to print to*/
	void print(std::ostream &out);

	/*!< The printFreqCount function of the LinkedList prints out the words in the list
	     in order of decreasing frequency.
	     @param out this is the output stream it will print to*/
	void printFreqCount(std::ostream &out);

	/*!< The remove function of the LinkedList used to remove words as needed.
	     @param word this is the word that is to be removed from the LinkedList
	     @returns true - successfully deleted specified word.
	     @returns false - word could not be found in list and could not be deleted.*/
	bool remove(std::string word);

	/*!< The size function of the LinkedList used to count the number of words
	     in the list.
	     @returns count - the number of words in the list.*/
	int size();

	/*!< The top function of the LinkedList prints out the first word in the list
	     @param out this is the output stream it will print to*/
	void top(std::ostream &out);
};
#endif
