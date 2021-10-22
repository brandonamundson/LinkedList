/*************************************************************************/ /**
 * @file 
 *
 * @mainpage Word Frequency - Linked Lists
 * 
 * @section course_section Course Information 
 *
 * @author Brandon Amundson 
 * 
 * @date 10/21/2021
 * 
 * @par Professor: 
 *         Doug Perez
 * 
 * @par Course: 
 *         CSC382
 * 
 * @section program_section Program Information 
 * 
 * @details A program to help book editors and authors to view the Frequency of
 * the words they used in their short stories. The editors believe that truly
 * good short stories use very few words over and over. So using the program 
 * will help the editors will prove that this is true or not and the authors can
 * use it to avoid using the same word to many times. The program will take in a
 * short story and then will read in word by word and remove punctuation and check
 * to see if the word exists and if it does it increases the frequency otherwise
 * it adds the word to the list. Once it parses the document it will output a 
 * list with the frequency and then words with that frequency.
 *
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *      None.
 * 
 * @par Usage: 
   @verbatim  
   c:\> prog1.exe  input.txt output.txt
                   input.txt - a short story or paragraph
                   output.txt - an output text that gives the frequency of a word
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ------------  -------------------------------------------------------------- 
   Mar  4, 2015  First workday
   Mar 17, 2015  Second workday
   Mar 24, 2015  Third workday
   Oct 17, 2021  Numerous modifications and improvements made
   Oct 21, 2021  Made into Doubly Linked List
   @endverbatim
 *
 *****************************************************************************/

#include "linklist.h"

bool openFiles(char* argv[], ifstream &fin, ofstream &fout);
string removePunc(string temp);

/**************************************************************************/ /**
 * @author Brandon Amundson
 *
 * @par Description:
 * Main function that is called first when the program boots. It first checks
 * to make sure that there is a valid amount of arguments and then opens the
 * files provided by the user. After the file successfully opens it reads a 
 * word in and removes the punctuation and then checks to see if it can
 * increment the frequency of the that word. If that increment fails it will
 * insert the word. It will do this for all the words in the file provided 
 * then it will output the list out to a file.
 *
 * @param[in]     argc - a count of the command line arguments used to start
 *                       the program.
 * @param[in]     argv - a 2d character array of each argument.  Each token
 *                       occupies one line in the array.
 *
 * @returns 0 program ran successful.
 * @returns 1 the program fails invalid command arguments given.
 * @returns 2 the program fails because the program couldn't open a file
 *
 *****************************************************************************/
int main(int argc, char* argv[])
{
	ifstream fin; //input stream
	ofstream fout; //output stream
	LinkList list; //linked list
	string temp; //temp string read in from file
	if (argc == 3)
	{
		if (openFiles(argv, fin, fout)) //if opened all files
		{
			while (fin >> temp) //while reading in from input file
			{
				temp = removePunc(temp); //remove punctuation
				if (!list.incrementFrequency(temp))
					//increment temp, if unable to
				{
					list.insert(temp); //if not able to increment, insert
				}
			}
			list.print(fout); // print list when done inserting
		}
		else
			return 2; // unable to open files
	}
	else //invalid number of arguments
	{
		cout << "Invalid number of commands" << endl;
		return 1;
	}
	return 0;
}

/**************************************************************************/ /**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function opens files
 *
 * @param[in]      argv - array of characters containing the file names
 * @param[out]     fin - input file provided by the user
 * @param[out]     fout - output file provided by the user
 *
 * @returns true if the files are successfully opened 
 * @returns false if the files are not successfully opened
 *****************************************************************************/
bool openFiles(char* argv[], ifstream &fin, ofstream &fout)
{
	fin.open(argv[1]);
	if (!fin)
	{
		cout << "Failed to open input file" << endl;
		return false;
	}
	fout.open(argv[2]);
	if (!fout)
	{
		cout << "Failed to open output file" << endl;
		return false;
	}
	return true;
}

/**************************************************************************/ /**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function removes the punctuation from the string and then returns the
 * string with no punctuation.
 *
 * @param[in]      temp - a word containing punctuation.
 *
 * @returns a string containing no punctuation.
 *****************************************************************************/
string removePunc(string temp)
{
	int size = temp.size();

	for (int i = 0; i < size; i++)
	{
		if (!isalnum(temp[i]) && !(temp[i] == 39))
		{
			temp.erase(i, 1);
			size = temp.size();
			if (i != 0)
			{
				i = i - 1;
			}
		}
		temp[i] = tolower(temp[i]);
	}
	return temp;
}
