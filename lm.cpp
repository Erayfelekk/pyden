/*
@Author
Name : Eray Felek
Student ID : 150160081
Date : 7/11/2018
*/
// This homework prints the space character in the ' ' form
// result is printed as result: ...
// when the command line is just ./lm input.txt
// it will print out the characters with no occurences as well and say : nout occur
// This homework assummes there is no character after the sentence such as "eray." is not
// "eray. "
// This homework works with an English-input only!

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <ctype.h>
using namespace std;

struct occur_node
{
	char character;
	occur_node *next;
	int occurence;
};

struct vocab_node
{
	char character;
	vocab_node *next;
	occur_node *list;
};

struct vocab_list
{
	vocab_node *head;
	vocab_node *head_other;
	void add_char(char);
	void add_char2(char);
	void add_together();
	void create();
	int get_occurence(char);
	int get_union_occurence(char ch_in1, char ch_in2);
	void add_occurence(char, char);
	void print();

};

struct language_model
{
	void readData(char* filename);
	vocab_list *vocabularylist;
	double Calculate(char, char);

};


int main(int argc, char* argv[])
{

// Check language model
	language_model l_model;
	//Gets the first second string i.e "txt" name as an argument
	//Adds characters and occurences
	l_model.readData(argv[1]);
	if (argc == 2)
	{
		//if there is only 2 argument i.e ./lm input.txt prints entire multilist
		l_model.vocabularylist->print();
	}
	else
	{
		//if there is 4 argument, i.e ./lm input.txt r a
		//gets r as a left operand and a as a right operand(to be explained)
		char left = argv[2][0];
		char right = argv[3][0];
		double result;
		result = l_model.Calculate(left, right);
		cout << "result:" << result << endl;
	}



}

void language_model::readData(char* name)
{
	//gets the incoming string and stores it as a "filename"
	char filename[25];
	strcpy(filename, name);

	//opens the file to read
	ifstream input(filename);
	vocabularylist = new vocab_list;
	vocabularylist->create();

	char ch;
	//while loop reads the txt file character by characater
	while (input.get(ch))
	{
		//add_char adds the characters from a to z
		vocabularylist->add_char(ch);
		//add_char2 adds special characters
		vocabularylist->add_char2(ch);
		
	}
	//add_together binds characters with special characters
	vocabularylist->add_together();
	input.close();


	//opens the file again to add occurences
	ifstream input2(filename);
	//prev and next chars are set for add_occurence function
	char prev_char = '\0';
	char next_char = '\0';
	while (input2.get(ch))
	{
		ch = tolower(ch);

		//if the character is not a newline character
		if ((int)ch != 10)
		{
			if (prev_char != '\0')
			{

				next_char = ch;
				//add_occurence will be explained under the function implementation
				vocabularylist->add_occurence(prev_char, next_char);
				prev_char = next_char;

			}
			else
			{
				prev_char = ch;
			}
		}
		else
		{
			//if the newline character is reached prev and next chars are set to zero
			//to resemble the getline function behaviour
			//I wrote it assuming "abcnewlined" d comes after a then changed it this way
			//so that everyline would start like it is read with the function getline.
			prev_char = '\0';
			next_char = '\0';
		}

	}




	input2.close();



}

void vocab_list::create()
{

	head = NULL;

}

void vocab_list::add_char(char ch_input)
{
	ch_input = tolower(ch_input);
	int ch_int;
	ch_int = (int)ch_input;

	if (ch_input > 96 && ch_input < 123)
	{

		if ((int)ch_input != 10)
		{
			//traverse and new node are created
			vocab_node *traverse;
			vocab_node *new_node;
			// vocab_node *insert_after ;
			new_node = new vocab_node;
			new_node->character = ch_input;
			new_node->next = NULL;
			new_node->list = NULL;
			traverse = head;


			if (head == NULL)
			{
				head = new_node;


			}

			else if (new_node->character < head->character)
			{
				//incase the incoming character must be the new head
				new_node->next = head;
				head = new_node;
			}

			else
			{
				traverse = head;
				//consider "abce". incoming character is d.
				//d is bigger than c and smaller than e as its ascii value
				//while loop traverses till c and stops at c
				while (traverse->next != NULL && traverse->next->character < new_node->character)
				{
					traverse = traverse->next;
				}

				if (traverse)
				{
					if (traverse->next)
					{
						//if there is another character after c and the incoming character
						//is not equal to c and e
						if (new_node->character != traverse->character && new_node->character != traverse->next->character)
						{
							//I dont know why I wrote this again
							//there were times when my code was not working so I changed or added some things
							//without thinking. And I didn't want to check if it works without it
							if (traverse->next)
							{
								//assign d-next to e
								//assign c-next to d
								new_node->next = traverse->next;
								traverse->next = new_node;

							}
							//traverse->next = new_node ;
						}
					}
					//if we head stopped at e
					else if (traverse->next == NULL)
					{
						if (new_node->character != traverse->character)
						{
							traverse->next = new_node;
						}
					}


				}



			}




		}

	}



}

void vocab_list::add_occurence(char voc, char occ)
{
    //we are dealing with 2 characters for occurence left and right
    //left is the character we want to add the occurence
    //right is the character that is occurence i.e erayfelera
    //"ra" set will make the character r's occurence character a's occurence = 1
    // when second ra is encountered as prev = r next = a whice is voc = r occ = a
    //occurence of the character a will be 2 for the character r.
	vocab_node *traverse;
	occur_node *traverse_occur;

	voc = tolower(voc);
	occ = tolower(occ);


	traverse = head;

	while (traverse && traverse->character != voc)
	{
        //find the char in vocabulary
		traverse = traverse->next;
	}


	if (traverse == NULL)
	{
		cout << "could not find" << endl;
	}
	else
	{
		traverse_occur = traverse->list;
        //set the occurence traverse pointer to list
        //did this list == NULL and add thing because i am checking
        //traverse_occur->next after that and it isn't alowed without having a traverse_occur
        //that's why occurence is set to zero
        //it is just a precaution.
		if (traverse->list == NULL)
		{
			occur_node *new_occur;
			new_occur = new occur_node;

			new_occur->occurence = 0;
			new_occur->character = occ;
			new_occur->next = NULL;

			traverse->list = new_occur;


		}

		traverse_occur = traverse->list;


		while (traverse_occur->next && traverse_occur->character != occ)
		{

			traverse_occur = traverse_occur->next;
		}

		if (traverse_occur && traverse_occur->character == occ)
		{
			traverse_occur->occurence = traverse_occur->occurence + 1;
		}
		else
		{
			occur_node *new_occur;
			new_occur = new occur_node;

			new_occur->occurence = 1;
			new_occur->character = occ;
			new_occur->next = NULL;

			traverse_occur->next = new_occur;


		}


	}


}

int vocab_list::get_occurence(char ch_in)
{
	//ch_in = tolower(ch_in) ;
	vocab_node *traverse;
	occur_node *traverse_occur;
	traverse = head;

	int count = 0;

	if (head != NULL)
	{

		while (traverse->next && traverse->character != ch_in)
		{
			traverse = traverse->next;
		}

		traverse_occur = traverse->list;

		if (traverse->list == NULL)
		{
			cout << "nout occur" << endl;
		}
		else
		{

			while (traverse_occur != NULL)
			{
				count = count + traverse_occur->occurence;
				traverse_occur = traverse_occur->next;
			}
		}

	}
	else
	{
		cout << "headnull" << endl;
	}

	return count;

}

int vocab_list::get_union_occurence(char ch_in1, char ch_in2)
{

	ch_in1 = tolower(ch_in1);
	ch_in2 = tolower(ch_in2);
	vocab_node *traverse;
	occur_node *traverse_occur;
	traverse = head;

	int count = 0;

	if (head != NULL)
	{

		while (traverse->next && traverse->character != ch_in1)
		{
			traverse = traverse->next;
		}

		traverse_occur = traverse->list;


		if (traverse->list == NULL)
		{
			cout << "nout occur" << endl;
		}
		else
		{
			while (traverse_occur && traverse_occur->character != ch_in2)
			{

				traverse_occur = traverse_occur->next;
			}
			if (traverse_occur != NULL && traverse_occur->character == ch_in2)
			{
				count = traverse_occur->occurence;
			}
			else
			{
				cout << "doesnt occur" << endl;
			}

		}

	}
	else
	{
		cout << "headnull" << endl;
	}

	return count;

}

double language_model::Calculate(char left, char right)
{
	int total;
	int together;
	double prob;

	total = vocabularylist->get_occurence(left);
	together = vocabularylist->get_union_occurence(left, right);
	prob = (double)together / (double)total;
	//cout<<together<<endl;
	//cout<<total<<endl;
	return prob;
}

void vocab_list::print()
{
	//ch_in = tolower(ch_in) ;
	vocab_node *traverse;
	occur_node *traverse_occur;
	traverse = head;

	int count = 0;

	if (head != NULL)
	{

		while (traverse->next)
		{
			cout << traverse->character << ":" << endl;
			//traverse = traverse->next ;

			traverse_occur = traverse->list;

			if (traverse->list == NULL)
			{
				cout << "nout occur" << endl;
			}
			else
			{

				while (traverse_occur != NULL)
				{
					cout << "     <" << traverse_occur->character << "," << traverse_occur->occurence << ">" << endl;
					traverse_occur = traverse_occur->next;
				}

			}

			traverse = traverse->next;
		}
		cout << traverse->character << ":" << endl;

		traverse_occur = traverse->list;

		if (traverse->list == NULL)
		{
			cout << "nout occur" << endl;
		}
		else
		{

			while (traverse_occur != NULL)
			{
				cout << "     <" << traverse_occur->character << "," << traverse_occur->occurence << ">" << endl;
				traverse_occur = traverse_occur->next;
			}

		}


	}
	//else
	//{
	  //  cout<<"headnull"<<endl;
	//}


}

void vocab_list::add_char2(char ch_input)
{

	ch_input = tolower(ch_input);
	int ch_int;
	ch_int = (int)ch_input;

	if (ch_input < 97 || ch_input > 122)
	{
		if ((int)ch_input != 10)
		{
			vocab_node *traverse;
			vocab_node *new_node;
			// vocab_node *insert_after ;
			new_node = new vocab_node;
			new_node->character = ch_input;
			new_node->next = NULL;
			new_node->list = NULL;
			traverse = head_other;


			if (head_other == NULL)
			{
				head_other = new_node;


			}

			else if (new_node->character < head_other->character)
			{

				new_node->next = head_other;
				head_other = new_node;
			}

			else
			{
				traverse = head_other;
				while (traverse->next != NULL && traverse->next->character < new_node->character)
				{
					traverse = traverse->next;
				}

				if (traverse)
				{
					if (traverse->next)
					{
						if (new_node->character != traverse->character && new_node->character != traverse->next->character)
						{

							if (traverse->next)
							{
								new_node->next = traverse->next;
								traverse->next = new_node;

							}
							//traverse->next = new_node ;
						}
					}

					else if (traverse->next == NULL)
					{
						if (new_node->character != traverse->character)
						{
							traverse->next = new_node;
						}
					}


				}



			}




		}
	}




}

void vocab_list::add_together()
{
	vocab_node *traverse;
	traverse = head;

	while (traverse->next)
	{
		traverse = traverse->next;
	}

	traverse->next = head_other;

}

