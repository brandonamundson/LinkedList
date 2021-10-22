/*************************************************************************/ /**
 * @file
 *****************************************************************************/

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#ifndef __FUNCTIONS__H__
#define __FUNCTIONS__H__

using namespace std;


/**************************************************************************/ /**
* @brief This class is a linked list that contains a string, frequency and both the
         previous and next word in the list.  The List is composed of words read in from a
         short story input as a text file and is used to document the frequency
         of every list in the text file.
*/
class LinkList
{
public:
	LinkList(); /*!< The constructor of the LinkedList*/
	~LinkList(); /*!< The destructor of the LinkedList*/

	/*!< The insert function of the LinkedList used to insert 
	     words alphabetically as needed.
	     @param word this is the word that is to be inserted into the LinkedList
	     @returns true - if it inserted the words
	     @return  false - if it could not insert the words*/
	bool insert(string word);

	/*!< The remove function of the LinkedList used to remove words as needed.
	     @param word this is the word that is to be removed from the LinkedList
	     @returns true - successfully deleted specified word.
	     @returns false - word could not be found in list and could not be deleted.*/
	bool remove(string word);

	/*!< The find function of the LinkedList used to find words as needed.
	     @param word this is the word that is to be found in the LinkedList
	     @returns true if the word is found
	     @returns false if the word is not found*/
	bool find(string word);

	/*!< The increment frequency function of the LinkedList used to increment
	     frequency of words as they are found in the list.
	     @param word this is the word whose frequency is to be incremented once
					 found in the LinkedList
	     @returns true if the word is found and it increases the frequency by one
	     @returns false if the word is not found*/
	bool incrementFrequency(string word);

	/*!< The isEmpty function of the LinkedList used to see if the list isEmpty
	     before inserting words.
	     @returns true - if the list is empty
	     @returns false - If the list is not empty*/
	bool isEmpty();

	/*!< The get max frequency function of the LinkedList used to find the
	     maximum frequency of all the words in the list.
	     @returns max - the maximum frequency of the words in the list.*/
	int getMaxFrequency();

	/*!< The size function of the LinkedList used to count the number of words
	     in the list.
	     @returns count - the number of words in the list.*/
	int size();

	/*!< The print function of the LinkedList prints out the words in the list
	     in order of decreasing frequency.
	     @param out this is the output stream it will print to*/
	void print(ostream &out);

	/*!< The top function of the LinkedList prints out the first word in the list
	     @param out this is the output stream it will print to*/
	void top(ostream &out);

	/*!< The print function of the LinkedList prints out the last word in the list
	     @param out this is the output stream it will print to*/
	void back(ostream &out);

private:
	/*!
	* @brief Holds word and frequency count
	*/

	struct node
	{
		int frequencyCount; /*!< Frequency count */
		string word = ""; /*!< Word of the node */
		node* next = nullptr; /*!< Next word in the list*/
		node* prev = nullptr; /*!< Previous word in the list*/
	};

	/*!< First node in the list.  This allows access to other nodes in list*/
	node* headptr;
	node* tailptr;
};
#endif
