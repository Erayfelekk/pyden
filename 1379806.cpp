/* @Author
Student Name: <Eray Felek>
Student ID : <150160081>
Date: <24/12/2018> */
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <cmath>
//in this homework I used doubly linked stack that can be erased from the bottom.
using namespace std;

struct node
{
	int value;
	node *right;
	node *left;
};

struct node_q
{
	int value;
	node_q *next;
};

struct node_s
{
	int value;
	node_s *next;
	node_s *back;
};

struct stack
{
	int total;
	int value;
	void create();
	void close();
	node_s *head;
	node_s *bottom;
	void push(int);
	int  pop();
	bool isempty();
};





struct Tree
{
	int total ;
	int target_number;

	stack myStack;
	node *tail;
	node *parent;
	int node_count;
	node *root;
	void create();
	void add(int);
	void ReadFile(char *);
	bool search(node* , int);
	void print();
	node* find_parent(int pcount, int half_pcount);
};


int main(int argc, char ** argv)
{
	Tree myTree;
	myTree.create();
	myTree.node_count = 0;
	myTree.ReadFile(argv[1]);


	myTree.myStack.create();

	//myTree.target_number = 10;


	myTree.myStack.total = 0;
	
	bool a ;


	if (myTree.root->value == myTree.target_number)
	{
		cout << "Path Found: " << myTree.root->value << endl;
	}
	else
	{

		myTree.myStack.push(myTree.root->value);
		a = myTree.search(myTree.root->left, myTree.target_number);
		if (!a)
		{
			cout << "No Path Found" << endl;
		}

	}


	myTree.myStack.create();
	myTree.myStack.total = 0;


	if (myTree.root->value == myTree.target_number)
	{
		cout << "Path Found: " << myTree.root->value << endl;
	}
	else
	{

		myTree.myStack.push(myTree.root->value);
		a = myTree.search(myTree.root->right, myTree.target_number);

		if (!a)
		{
			cout << "No Path Found" << endl;
		}
	}



}

node* Tree::find_parent(int pcount, int half_pcount)
{
	if (half_pcount != 0)
	{

		find_parent(pcount / 2, half_pcount / 2);

		if (pcount % 2 == 0)
		{
			tail = parent;
			parent = parent->left;
		}
		else if (pcount % 2 == 1)
		{
			tail = parent;
			parent = parent->right;
		}


	}


	return tail;

}

void Tree::create()
{
	root = NULL;
	parent = NULL;
	tail = NULL;
	myStack.create();
}
// this function first find the parent using recursion.
void Tree::add(int in_add)
{
	node *new_node;
	new_node = new node;

	node *found_parent;

	new_node->value = in_add;
	new_node->left = NULL;
	new_node->right = NULL;

	if (root == NULL)
	{
		root = new_node;
		node_count++;
	}
	else
	{
		found_parent = find_parent(node_count + 1, (node_count + 1) / 2);
		if (found_parent->left)
		{
			found_parent->right = new_node;
			node_count++;
		}
		else
		{
			found_parent->left = new_node;
			node_count++;
		}
	}

	tail = root;
	parent = root;


}
// while reading first I counted how many elements there and added 1 less of them to the tree
void Tree::ReadFile(char *input_name)
{
	int incoming_value;
	char filename[40];
	strcpy(filename, input_name);
	FILE* toread;
	toread = fopen(filename, "r+");

	if (!toread)
	{
		cerr << "Cannot open file" << endl;
		exit(1);
	}

	int count = 0;

	fseek(toread, 0, SEEK_SET);
	while (!feof(toread))
	{
		if (fscanf(toread, "%d", &incoming_value) != EOF)
		{
			count++;
		}
	}

	fseek(toread, 0, SEEK_SET);
	for(int i = 0 ; i < count - 1 ; i++)
	{
		fscanf(toread, "%d", &incoming_value);
		add(incoming_value);

	}
	fscanf(toread, "%d", &incoming_value);
	target_number = incoming_value;


}

bool Tree::search(node* ptr, int target)
{
	if (ptr)
	{
		//myQueue.enqueue(ptr->value) ;
		myStack.push(ptr->value);

			if (myStack.total == target)
			{
				cout << "Path Found: ";

					while (myStack.bottom != NULL)
					{
						int a = myStack.bottom->value;
						node_s* temp;
						temp = myStack.bottom;
						if (myStack.bottom->next)
						{
							myStack.bottom = myStack.bottom->next;
							if (myStack.bottom)
							{
								myStack.bottom->back = NULL;
								delete temp;
							}
						}
						else
						{
							myStack.bottom = NULL ;
						}

						cout << a << " " ;

					}


				cout << endl;

				return true;

			}
			else
			{
				bool a;
				a = search(ptr->left, target) ;

					if (!a)
					{
						bool b = search(ptr->right, target);
						myStack.pop();
						return b;
					}

			}


	}
	else
	{
		return false;
	}

	return true ;

}

void stack::create()
{
	head = NULL;
	bottom = NULL;
}

int stack::pop()
{
	int temp;
	node_s *temp_node;
	temp_node = head;

	if (head != NULL)
	{
		temp = head->value;
		head = head->back;
		delete temp_node;
		total = total - temp;
		return temp;
	}
	else
	{
		return 0;
	}
	

}

void stack::push(int input)
{
	node_s *new_node;
	new_node = new node_s;
	new_node->value = input;
	total = total + input;

	if (head == NULL)
	{
		new_node->next = NULL;
		new_node->back = NULL;
		head = new_node;
		bottom = new_node;
	}
	else
	{
		new_node->next = NULL;
		new_node->back = NULL;

		new_node->back = head;
		head->next = new_node;
		head = new_node;

	}

}

bool stack::isempty()
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



