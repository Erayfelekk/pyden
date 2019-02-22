/*
Author: Eray Felek
Homework 3
Student ID : 150160081
*/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <cmath>

using namespace std;

struct node
{
	int value;
	node *next;
};

struct Stack
{
	int deck_count;
	void create();
	void close();
	node *head;
	void push(int);
	int  pop();
	bool isempty();
	void print();
};

int main(int argc, char* argv[])
{
	int player_deck_count;
	Stack bin;
	Stack table_deck;
	Stack player1_deck;
	Stack player2_deck;
	table_deck.create();
	player1_deck.create();
	player2_deck.create();
	bin.create();
	bin.deck_count = 0;

	char filename[35];
	strcpy(filename, argv[argc-1]);

	FILE* toread;
	toread = fopen(filename, "r+");

	if (!toread)
	{
		cerr << "Cannot open file" << endl;
		exit(1);
	}

	fseek(toread, 0, SEEK_SET);
	fscanf(toread, "%d %d", &table_deck.deck_count, &player_deck_count);
	player1_deck.deck_count = player_deck_count;
	player2_deck.deck_count = player_deck_count;
	int in_loop;

	while (!feof(toread))
	{

		for (int i = 0; i < table_deck.deck_count; i++)
		{
			{
				if
					(fscanf(toread, "%d", &in_loop) != EOF)
				{
					table_deck.push(in_loop);
				}
			}
		}

		for (int i = 0; i < player_deck_count; i++)
		{
			{
				if
					(fscanf(toread, "%d", &in_loop) != EOF)
				{
					player1_deck.push(in_loop);
				}
			}
		}

		for (int i = 0; i < player_deck_count; i++)
		{
			{
				if
					(fscanf(toread, "%d", &in_loop) != EOF)
				{
					player2_deck.push(in_loop);
				}
			}
		}

	}

	int player_turn = 1;

	while (table_deck.deck_count > 0)
	{

		int table_card;
		table_card = table_deck.pop();
		if (player_turn == 1)
		{
			int temp1;
			int temp2;
			if (table_card < 0)
			{
				for (int i = 0; i < abs(table_card); i++)
				{
					if (player1_deck.head == NULL || player2_deck.head == NULL)
					{
						cout << bin.deck_count << endl;
						
						return 0;
					}
					temp1 = player1_deck.pop();
					temp2 = player2_deck.pop();
					if (temp1 > temp2)
					{
						player2_deck.push(temp2);
						player2_deck.push(temp1);
					}
					else
					{
						player2_deck.push(temp2);
						bin.push(temp1);
						bin.deck_count++;
					}
				}
			}
			if (table_card > 0)
			{
				for (int i = 0; i < abs(table_card); i++)
				{
					if (player1_deck.head == NULL || player2_deck.head == NULL)
					{
						cout << bin.deck_count << endl;
						return 0;
					}

					temp1 = player1_deck.pop();
					temp2 = player2_deck.pop();
					if (temp2 > temp1)
					{
						player1_deck.push(temp1);
						player1_deck.push(temp2);
					}
					else
					{
						player1_deck.push(temp1);
						bin.push(temp2);
						bin.deck_count++;
					}
				}

			}


		}
		else if (player_turn == 2)
		{

			int temp1;
			int temp2;
			if (table_card < 0)
			{
				for (int i = 0; i < abs(table_card); i++)
				{
					if (player1_deck.head == NULL || player2_deck.head == NULL)
					{
						cout << bin.deck_count << endl;

						return 0;
					}
					temp1 = player1_deck.pop();
					temp2 = player2_deck.pop();
					if (temp2 > temp1)
					{
						player1_deck.push(temp1);
						player1_deck.push(temp2);
					}
					else
					{
						player1_deck.push(temp1);
						bin.push(temp2);
						bin.deck_count++;
					}
				}
			}
			if (table_card > 0)
			{

				for (int i = 0; i < abs(table_card); i++)
				{
					if (player1_deck.head == NULL || player2_deck.head == NULL)
					{
						cout << bin.deck_count << endl;

						return 0;
					}

					temp1 = player1_deck.pop();
					temp2 = player2_deck.pop();
					if (temp1 > temp2)
					{
						player2_deck.push(temp2);
						player2_deck.push(temp1);
					}
					else
					{
						player2_deck.push(temp2);
						bin.push(temp1);
						bin.deck_count++;
					}
				}

			}

		}


		if (player_turn == 1)
		{
			player_turn = 2;
		}
		else if (player_turn == 2)
		{
			player_turn = 1;
		}

		table_deck.deck_count--;

	}


	//cout<<"hehe"<<endl ;
	if (player1_deck.head == NULL) {
		cout << "hehe" << endl;
	}
	cout << bin.deck_count << endl;


	//cout<<a<<endl ;
	//cout<<player1_deck.deck_count<<endl ;
}

void Stack::create()
{
	head = NULL;
}

int Stack::pop()
{
	int temp;
	node *temp_node;
	temp_node = head;
	
	temp = head->value;
	head = head->next;
	delete temp_node;
	return temp;

}

void Stack::push(int input)
{
	node *new_node;
	new_node = new node;
	new_node->value = input;
	new_node->next = head;
	head = new_node;

}

bool Stack::isempty()
{
	if (head == NULL)
	{
		return 1;
	}

	else
	{
		return 0;
	}
}


