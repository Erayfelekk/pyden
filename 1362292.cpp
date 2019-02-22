/* @Author
Student Name: <Eray Felek>
Student ID : <150160081>
Date: <12/12/2018> */

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

struct queueAnt
{
	int Number_of_ants;
	int hole_total;
	int value;
	node *front;
	node *back;
	bool enqueue(int);
	int dequeue();
	void create();
	void close();
	bool isempty();

};

struct stackAnt
{
	int value;
	void create();
	void close();
	node *head;
	void push(int);
	int  pop();
	bool isempty();
};

struct Ants {
queueAnt ants ;
queueAnt holeDepths ;
stackAnt hole ;
void ReadFile ( char *);
void ShowContents ( bool );
void CrossRoad ();
};





int main (int argc , char ** argv ){
Ants a ;
a . ReadFile ( argv [1]); // store the number of ants and depths of holes
cout << "The initial Ant sequence is: ";
a . ShowContents (1); // list ant sequence ( initially : 1 , 2 , ... , N)
cout << "The depth of holes are: ";
a . ShowContents (0); // list depth of holes
a . CrossRoad ();
cout << "The final Ant sequence is: ";
a . ShowContents (1);
return 0;
}




void stackAnt::create()
{
	head = NULL;
}

int stackAnt::pop()
{
	int temp;
	node *temp_node;
	temp_node = head;

	temp = head->value;
	head = head->next;
	delete temp_node;
	return temp;

}

void stackAnt::push(int input)
{
	node *new_node;
	new_node = new node;
	new_node->value = input;
	new_node->next = head;
	head = new_node;

}

bool stackAnt::isempty()
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

bool queueAnt::isempty()
{
	if (front == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


bool queueAnt::enqueue(int input)
{
	node *new_node = new node;
	new_node->value = input;
	new_node->next = NULL;
	if (isempty())
	{
		back = new_node;
		front = back;
	}
	else
	{
		back->next = new_node;
		back = new_node;
	}

	return 1;

}
int queueAnt::dequeue()
{
	node *temp;
	int temp_int;

	temp = front;
	temp_int = front->value;

	front = front->next;
	delete temp;

	return temp_int;
}

void queueAnt::create()
{
	front = NULL;
	back = NULL;
}

void Ants::ReadFile(char *input_name)
{
	holeDepths.hole_total = 0;
	//declare a static string to hold the file name
	char filename[40];
	strcpy(filename, input_name);

	FILE* toread;
	toread = fopen(filename, "r+");

	if (!toread)
	{
		cerr << "Cannot open file" << endl;
		exit(1);
	}
	
		//make sure that head of the data structures(head , front,back) points to null.
	ants.create();
	holeDepths.create();
	hole.create();
	//move curser to the beginning of the file and get the number of ants
	fseek(toread, 0, SEEK_SET);
	fscanf(toread, "%d", &ants.Number_of_ants);

	//name the ants starting from 1
	for (int i = 1; i <= ants.Number_of_ants; i++)
	{
		//enqueue the ants i.e (1 , 2, 3 ...)
		ants.enqueue(i);
	}
	// while end of the file is not reached do the following
	while (!feof(toread))
	{
		//declare an integer to hold the holes and read it while end of file is not reached
		int read_hole;
		if (fscanf(toread, "%d", &read_hole) != EOF)
		{
			//if it is not end of the file enqueue the holes and increment hole size
			holeDepths.enqueue(read_hole);
			holeDepths.hole_total++;
		}
	}

}

void Ants::CrossRoad()
{
	for (int k = 0; k < holeDepths.hole_total; k++)
	{
		//get the first hole's size i.e depth
		int depth;
		depth = holeDepths.dequeue();

		for (int i = 0; i < depth; i++)
		{
			//push the ants to the hole
			hole.push(ants.dequeue());
		}
		for (int i = 0; i < depth; i++)
		{
			//get the ants out of the hole
			ants.enqueue(hole.pop());
		}
	}

}

void Ants::ShowContents(bool in_bool)
{
	if (in_bool == 1)
	{
		node *temp;
		temp = ants.front;

		//cout<<" " ;

		while (temp != NULL)
		{
			cout<<temp->value<<" " ;
			temp = temp->next;
		}
		
		cout<<endl ;
	}
	else if (in_bool == 0)
	{
		node *temp;
		temp = holeDepths.front;
		
		//cout<<" " ;
		
		while (temp != NULL)
		{
			cout<<temp->value<<" " ;
			temp = temp->next;
		}
		
		cout<<endl ;
	}
}

