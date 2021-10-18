/*************************************************************************/ /**
 * @file
 *****************************************************************************/

#include "linklist.h"

/**************************************************************************/ /**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function creates/starts the list by setting the link list to nullptr
 *
 *****************************************************************************/
LinkList::LinkList()
{
	headptr = nullptr;
}

/**************************************************************************/ /**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function deletes every member of the linked list.
 *
 *****************************************************************************/
LinkList::~LinkList()
{
	node* temp = headptr;
	node* temp2 = headptr;
	while (temp2 != nullptr)
	{
		temp2 = temp->next;
		delete temp;
		temp = temp2;
	}
}

/**
* @author Brandon Amundson
*
* @par Description:
* This is the remove function of the program.  It is used when needing to
* delete a specific word from the list.
*
* @param[in]        word - the word that is to be removed from the list.
*
* @returns true - successfully deleted specified word.
* @returns false - word could not be found in list and could not be deleted.
*
******************************************************************************/
bool LinkList::remove(string word)
{
	node* temp = headptr;
	node* prev = headptr;

	while (temp != nullptr) // while in list
	{
		if (temp->word == word) // if temp word is word
		{
			if (temp == headptr) // if temp is head
			{
				if (temp->next != nullptr) // if head is not only element
				{
					headptr = temp->next; // reassign head
					delete temp; // delete temp
				}
				else // make list empty
				{
					delete headptr; // delete head
				}
				return true;
			}
			prev->next = temp->next; // else, point prev to temp next node
			delete temp; // delete temp
			return true;
		}
		prev = temp; // make current(temp) previous and 
		temp = temp->next; // current (temp), next
	}
	return false; // unable to find/remove
}


/**
* @author Brandon Amundson
*
* @par Description:
* This is the function that returns the maximum frequency of any word that is 
* located in the list.  It is called by the print function to output the
* words in order of frequency as they appear in the list.
*
*
* @returns max - the maximum frequency of the words in the list.
*
******************************************************************************/
int LinkList::getMaxFrequency()
{
	node* curr = headptr; // start at head
	int max = 0; // init max at 0

	while (curr != nullptr) // while not at end of list
	{
		if (curr->frequencyCount >= max) // if current node freq is big than max
		{
			max = curr->frequencyCount; // set max to current freq count
		}
		curr = curr->next; // move node to next 
	}
	return max; // return max
}

/**************************************************************************/ /**
* @author Brandon Amundson
*
* @par Description:
* This function takes in a word and searches the list for the word.  If the 
* word is found the function will return true, else the function returns
* false.  
*
* @param[in]     word - a word to search for.
*
* @returns true if the word is found
* @returns false if the word is not found
*****************************************************************************/
bool LinkList::find(string word)
{
	node* temp = headptr; // start at head

	while (temp != nullptr) // while not at end of list
	{
		if (word == temp->word) // compare word to current node word
		{
			return true; // true if found
		}
		temp = temp->next; // move to next if not found
	}
	return false; // return false if not in list
}

/**************************************************************************/ /**
* @author Brandon Amundson
*
* @par Description:
* This function will go through the list of words and count the amount
* of words in the list.  The function will then return count when it is 
* finished.  
*
*
* @returns count - the number of words in the list.  
*****************************************************************************/
int LinkList::size()
{
	node* temp = headptr; // start at head
	int count = 0; // no nodes counted yet

	while (temp != nullptr) // while not at end of list
	{
		count++; // increment count
		temp = temp->next; // proceed to next node
	}

	return count; // return number of nodes in list
}

/**************************************************************************/ /**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function gets in a word and then searches for the word in the list. If
 * the word is found it will increment the frequency by one and return true.
 * If the word is not found it will return false.
 *
 * @param[in]     word - a word to search for and increment the frequency of.
 *
 * @returns true if the word is found and it increases the frequency by one
 * @returns false if the word is not found
 *****************************************************************************/
bool LinkList::incrementFrequency(string word)
{
	node* temp = headptr;
	int count = 0;
	while (temp != nullptr)
	{
		if (word == temp->word)
		{
			count = temp->frequencyCount;
			count++;
			temp->frequencyCount = count;
			return true;
		}
		temp = temp->next;
	}
	return false;
}

/**************************************************************************/ /**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function print the list out to an output file provided by the user.
 * It also formats and adds headers to each frequency to easily read the list.
 *
 * @param[in, out]     out - the output file provided by the user
 *
 *****************************************************************************/
void LinkList::print(ostream &out)
{
	node* temp = headptr; // start at head
	int max = getMaxFrequency(); // get highest frequency first
	bool header = true; // start by printing header
	int count = 0; // count words across, 4 across, then down

	while (max != 0) // while words in list
	{
		header = true; // reset header
		while (temp != nullptr) // while not at end of list
		{
			if (temp->frequencyCount == max) // if at max frequency count
			{
				if (header) // if header is needed, print it
				{
					out << "\n******************************" <<
						"****************************" << endl <<
						"\t\t Frequency of " << max << endl <<
						"***************************" <<
						"*******************************" << endl;
					header = false; // do not continue to print header
				}
				if (count == 3) // if at end of line
				{
					out << temp->word << endl; // output word and end line
					count = 0; // reset count
				}
				else // otherwise output word and a tabspace
				{
					out << temp->word << "     ";
					count++;
				}
			}
			temp = temp->next; // move to next node
		}
		temp = headptr; // reset temp to beginning of list
		count = 0; // reset count
		max--; // decrease max frequency and check list again until at zero
	}
}

/** 
* @author Brandon Amundson
* 
* @par Description: 
* insert word one into the list alphabetical order and in the same node attach
* frequency count
*  
* @param[in] word - word that will be inserted into the list
* 
* @returns true - if it inserted the words
* @return  false - if it could not insert the words
*****************************************************************************/
bool LinkList::insert(string word)
{
	node* temp = headptr;
	node* prev = headptr;
	node* new_node = nullptr;

	new_node = new(nothrow) node; // new node that will go into the list
	if (new_node == nullptr) // if new node not allocated, assigns nullptr
	{
		return false; // returns false unable to insert
	}

	if (find(word)) // check if word is in list already
	{
		return incrementFrequency(word);
		// if it is increment frequency and return
		// should return true if incremented, false if not found-> error state
	}
	new_node->word = word; //create new node data
	new_node->frequencyCount = 1;
	new_node->next = nullptr;

	if (headptr == nullptr) // if inserting at beginning
	{
		headptr = new_node;
		return true;
	}
	// if word is before headptr alphabetically
	if (new_node->word <= headptr->word)
	{
		new_node->next = headptr; // assign current headptr as new node next
		headptr = new_node; // assign headptr to new node
		return true; // return true
	}
	// while not at end of list and before alphabetical
	while (temp != nullptr && temp->word <= new_node->word)
	{
		prev = temp;
		temp = temp->next;
	}
	new_node->next = temp;
	prev->next = new_node;
	return true;
}

/** 
* @author Brandon Amundson
* 
* @par Description: 
* checks to see if the list is empty by checking to see if headptr is nullptr
* 
* 
* @returns true - if the list is empty
* @returns false - If the list is not empty
*****************************************************************************/
bool LinkList::isEmpty()
{
	if (headptr == nullptr)
		return true;
	return false;
}
