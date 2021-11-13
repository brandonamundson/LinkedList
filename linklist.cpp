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
	tailptr = nullptr;
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

/**************************************************************************/ /**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function prints the last item in list to an output stream provided by
 * the user. It also formats and adds headers to each frequency to easily read
 * the list.
 *
 * @param[in,out]     out - the output file provided by the user
 *****************************************************************************/
void LinkList::back(std::ostream &out)
{
	if (headptr == nullptr)
	{
		out << "List is empty!" << std::endl;
		return;
	}
	out << "Item at the end of the list is: " << tailptr->word;
	out << "\nFrequency Count is: " << tailptr->frequencyCount;
	out << std::endl;
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
bool LinkList::find(std::string word)
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
 * This function is the wrapper for the frequency quick sort functions, resets
 * headptr to new sorted list
 *****************************************************************************/
void LinkList::frequencySort()
{
	headptr = quickSortRecur(headptr, tailptr);
}

/**************************************************************************/ /**
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
 * This function returns the end of the current node list
 *
 * @param[in,out] cur - a node list
 *
 * @returns cur the last item in list
 *****************************************************************************/
LinkList::node* LinkList::getTail(node* cur)
{
	// walks through list to get last item
	while (cur != nullptr && cur->next != nullptr)
		cur = cur->next;
	return cur;
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
bool LinkList::incrementFrequency(std::string word)
{
	node* temp = headptr;
	while (temp != nullptr)
	{
		if (word == temp->word)
		{
			int count = temp->frequencyCount;
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
* insert word one into the list alphabetical order and in the same node attach
* frequency count
*  
* @param[in] word - word that will be inserted into the list
* 
* @returns true - if it inserted the words
* @return  false - if it could not insert the words
*****************************************************************************/
bool LinkList::insert(std::string word)
{
	node* temp = headptr;
	auto new_node = new(std::nothrow) node;
	// new node that will go into the list
	if (new_node == nullptr) // if new node not allocated, assigns nullptr
	{
		return false; // returns false unable to insert
	}

	if (find(word)) // check if word is in list already
	{
		// if it is increment frequency and return
		// should return true if incremented, false if not found-> error state
		return incrementFrequency(word);
	}

	new_node->word = word; //create new node data
	new_node->frequencyCount = 1;
	new_node->next = nullptr;
	new_node->prev = nullptr;

	// if inserting in empty
	if (headptr == nullptr)
	{
		headptr = new_node;
		tailptr = new_node;
		return true;
	}
	// if inserting at beginning
	if (new_node->word <= headptr->word)
	{
		new_node->next = headptr; // assign current headptr as new node next
		headptr->prev = new_node; // assign current headptr prev to newest node
		headptr = new_node; // assign headptr to new node
		return true; // return true
	}
	// if inserting at end
	if (tailptr->word <= new_node->word)
	{
		if (headptr == tailptr) // if head and tail are same
		{
			headptr->next = new_node; // head next needs to be new node
		}
		new_node->prev = tailptr; // new prev is now tail
		tailptr->next = new_node; // tails next is new node
		tailptr = new_node; // tail is now new
	}

	else // we must be inserting in middle
	{
		// while not at end of list and new node is before current node
		// and while not off the list somehow...
		while (temp->word <= new_node->word && temp != nullptr)
		{
			temp = temp->next; // move temp to the next node

			if (temp == nullptr) // if this were to ever occur for any reason
			{
				return false; // do not try to insert
			}
		}
		// once temp is larger than new node, new node will go before it
		new_node->next = temp; // new node next is now temp
		new_node->prev = temp->prev; // new node prev is now temp's prev
		temp->prev = new_node; // temp's prev is now new node
		new_node->prev->next = new_node; // the previous nodes next is new node
		return true; // we have now inserted into list, return
	}
	return false;
}

/**************************************************************************/ /**
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
	return (headptr == nullptr) ? true : false;
}

/**************************************************************************/ /**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function merges two linked lists together
 *
 * @param[in,out]      first - first set of nodes to be linked
 * @param[in,out]      second - second set of nodes to be linked
 *
 * @returns second - fully merged list
 *****************************************************************************/
LinkList::node* LinkList::merge(node* first, node* second)
{
	// If first linked list is empty
	if (!first)
		return second;

	// If second linked list is empty
	if (!second)
		return first;

	// Pick the smaller value
	if (first->word < second->word)
	{
		first->next = merge(first->next, second);
		first->next->prev = first;
		first->prev = nullptr;
		return first;
	}
	second->next = merge(first, second->next);
	second->next->prev = second;
	second->prev = nullptr;
	return second;
}

/**************************************************************************/ /**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function is the overloaded mergesort for users to access.  Starts with
 * headptr and then splits the list as necessary, using the intermediary
 * private functions
 *****************************************************************************/
void LinkList::mergeSort()
{
	node* tmp = headptr;
	if (!tmp || !tmp->next)
		return;
	node* second = split(tmp);

	// Recur for left and right halves
	tmp = mergeSort(tmp);
	second = mergeSort(second);

	// Merge the two sorted halves
	headptr = merge(tmp, second);
}

/**************************************************************************/ /**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function is a recursive merge sort
 *
 * @param[in,out]      head - head of list to be sorted
 *
 * @returns merge function that merges separate lists together
 *****************************************************************************/
LinkList::node* LinkList::mergeSort(node* head)
{
	if (!head || !head->next)
		return head;
	node* second = split(head);

	// Recur for left and right halves
	head = mergeSort(head);
	second = mergeSort(second);

	// Merge the two sorted halves
	return merge(head, second);
}

/**************************************************************************/ /**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function partitions the list into smaller lists for the quick sort
 * function
 *
 * @param[in,out]  head - the head node
 * @param[in,out]  end - the end node
 * @param[in,out]  newHead - the new head node
 * @param[in,out]  newEnd - the new end node
 *
 * @returns pivot - the node that was moved to the end for sorting
 *****************************************************************************/
LinkList::node* LinkList::partition(node* head, node* end, node** newHead,
                                    node** newEnd)
{
	node* pivot = end;
	node *prev = nullptr, *cur = head, *tail = pivot;

	// During partition, both the head and end of the list
	// might change which is updated in the newHead and
	// newEnd variables
	while (cur != pivot)
	{
		if (cur->frequencyCount < pivot->frequencyCount)
		{
			// First node that has a value less than the
			// pivot - becomes the new head
			if ((*newHead) == nullptr)
				(*newHead) = cur;

			prev = cur;
			cur = cur->next;
		}
		else // If cur node is greater than pivot
		{
			// Move cur node to next of tail, and change
			// tail
			if (prev)
				prev->next = cur->next;
			node* tmp = cur->next;
			cur->next = nullptr;
			tail->next = cur;
			tail = cur;
			cur = tmp;
		}
	}

	// If the pivot data is the smallest element in the
	// current list, pivot becomes the head
	if ((*newHead) == nullptr)
		(*newHead) = pivot;

	// Update newEnd to the current last node
	(*newEnd) = tail;

	// Return the pivot node
	return pivot;
}

/**************************************************************************/ /**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function prints the linked list in its current order to a given output
 * stream
 *
 * @param[in,out]      out - any output stream
 *****************************************************************************/
void LinkList::print(std::ostream &out)
{
	node* tmp = headptr;

	while (tmp != nullptr)
	{
		out << "\n******************************"
			<< "****************************" << std::endl;
		out << "\nFrequency Count: " << tmp->frequencyCount;
		out << "\nWord: " << tmp->word
			<< "\n***************************"
			<< "*******************************" << std::endl;
		tmp = tmp->next;
	}
}

/**************************************************************************/ /**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function print the list out to an output file provided by the user.
 * It also formats and adds headers to each frequency to easily read the list.
 *
 * @param[in,out]     out - the output file provided by the user
 *
 *****************************************************************************/
void LinkList::printFreqCount(std::ostream &out)
{
	node* temp = headptr; // start at head
	int max = getMaxFrequency(); // get highest frequency first
	int count = 0; // count words across, 4 across, then down

	while (max != 0) // while words in list
	{
		bool header = true; // reset header
		while (temp != nullptr) // while not at end of list
		{
			if (temp->frequencyCount == max) // if at max frequency count
			{
				if (header) // if header is needed, printFreqCount it
				{
					out << "\n******************************" <<
						"****************************" << std::endl <<
						"\t\t Frequency of " << max << std::endl <<
						"***************************" <<
						"*******************************" << std::endl;
					header = false; // do not continue to printFreqCount header
				}
				if (count == 3) // if at end of line
				{
					out << temp->word << std::endl; // output word and end line
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

/**************************************************************************/ /**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function starts the quick sort by getting newHead and newEnd nodes
 * and setting the pivot node.
 *
 * @param[in,out]      head - the head node
 * @param[in,out]      end  - the end node
 *
 * @returns newHead node
 *****************************************************************************/
LinkList::node* LinkList::quickSortRecur(node* head, node* end)
{
	// base condition
	if (!head || head == end)
		return head;

	node *newHead = nullptr, *newEnd = nullptr;

	// Partition the list, newHead and newEnd will be
	// updated by the partition function
	node* pivot
		= partition(head, end, &newHead, &newEnd);

	// If pivot is the smallest element - no need to recur
	// for the left part.
	if (newHead != pivot)
	{
		// Set the node before the pivot node as nullptr
		node* tmp = newHead;
		while (tmp->next != pivot)
			tmp = tmp->next;
		tmp->next = nullptr;

		// Recur for the list before pivot
		newHead = quickSortRecur(newHead, tmp);

		// Change next of last node of the left half to
		// pivot
		tmp = getTail(newHead);
		tmp->next = pivot;
	}

	// Recur for the list after the pivot element
	pivot->next = quickSortRecur(pivot->next, newEnd);

	return newHead;
}

/**************************************************************************/ /**
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
bool LinkList::remove(std::string word)
{
	node* temp = headptr;

	// if list is empty
	if (temp == nullptr)
	{
		// nothing to delete, return true
		return true;
	}

	while (temp != nullptr) // while in list
	{
		if (temp->word == word) // if temp word is word
		{
			if (temp == headptr) // if temp is head
			{
				if (temp->next != nullptr) // if head is not only element
				{
					headptr = temp->next; // reassign head
					// ensure that the next node's prev is null
					headptr->prev = nullptr;
					delete temp; // delete temp
				}
				else // otherwise only one item in list, empty list
				{
					delete headptr; // delete head
					delete tailptr; // delete tail
				}
				return true;
			}
			if (temp == tailptr) // if temp is tail
			{
				tailptr = temp->prev; // reassign tailptr to prev node
				tailptr->next = nullptr; // reassign temp->prev->next to null
				delete temp; // delete temp
			}
			else // removing in middle
			{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				return true;
			}
		}
		temp = temp->next; // move current (temp), to next
	}
	return false; // unable to find/remove, list likely empty
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
 * This function splits a linked list into smaller component lists for merge
 * sort
 *
 * @param[in,out]      head - the head of a list
 *
 * @return temp - a split list
 *****************************************************************************/
LinkList::node* LinkList::split(node* head)
{
	node *fast = head, *slow = head;
	while (fast->next && fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	node* temp = slow->next;
	slow->next = nullptr;
	return temp;
}

/**************************************************************************/ /**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function prints the first item in list to an output stream provided by
 * the user. It also formats and adds headers to each frequency to easily read
 * the list.
 *
 * @param[in,out]     out - the output file provided by the user
 *****************************************************************************/
void LinkList::top(std::ostream &out)
{
	if (headptr == nullptr)
	{
		out << "List is empty!" << std::endl;
		return;
	}
	out << "Item at the beginning of the list is: " << headptr->word;
	out << "\nFrequency Count is: " << headptr->frequencyCount;
	out << std::endl;
}
