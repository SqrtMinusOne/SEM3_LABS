
#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

typedef struct list list;

typedef struct node //Contains the element itself
{
	char name[80]; //Name of element
	node* next = NULL; //Next element
	list* childs = NULL; //Childen
}node;

typedef struct list //Contains children of element
{
	char name[80];
	node* elem = NULL;
	list* next = NULL;
}list;

void clear(list* ls) // Clear children
{
	if (ls != NULL) {
		if (ls->next != NULL)
			clear(ls->next);
		delete ls;
	}
}

void clear(node* gr) //Clear elements
{
	if (gr->next != NULL) {
		clear(gr->next);
	}
	clear(gr->childs);
	delete gr;
}

bool is_Edge(node* gr1, node* gr2) //Is there an edge between elements?
{	
	list* curch = gr1->childs;
	while (curch != NULL) {
		if (curch->elem == gr2)
			return 1;
		curch = curch->next;
	}
	return 0;
}

int howmuch(node* ls) //How much elements are is graph?
{
	int i = 0;
	while (ls->next != NULL) {
		ls = ls->next;
		i++;
	}
	return i;
}

int maxwidth(node* gr) {
	int wid = 0;
	while (gr != NULL) {
		if (strlen(gr->name) > wid)
			wid = strlen(gr->name);
		gr = gr->next;
	}
	return wid;
}

void readlist(node* gr, ifstream* file) //Read graph fron incedancy list from file
{
	list* curch = NULL;
	string str;
	while (getline(*file, str)) {
		char temp[80];
		strcpy_s(temp, 80, str.c_str());
		char* next_tok;
		char* tok = strtok_s(temp, " ,", &next_tok);
		strcpy_s(gr->name, 80, tok);
		tok = strtok_s(NULL, " ,", &next_tok);
		while (tok != NULL) {
			if (curch == NULL) {
				gr->childs = new list;
				curch = gr->childs;
			}
			strcpy_s(curch->name, 80, tok);
			tok = strtok_s(NULL, " ,", &next_tok);
			if (tok != NULL) {
				curch->next = new list;
				curch = curch->next;
			}
		}
		if (!(*file).eof()) {
			gr->next = new node;
			gr = gr->next;
		}
		curch = NULL;
	}
}

node* findelem(char* name, node* gr) //Find element in the graph
{
	while (gr != NULL) {
		if (strcmp(name, gr->name) == 0) {
			return gr;
		}
		gr = gr->next;
	}
	return NULL;
}

void out(node* gr) //Print graph with incidency list; make links from children to parents
{
	cout << "Structure out: " << endl;
	node* start = gr;
	list* curch = NULL;
	while (gr != NULL) {
		cout << gr->name << ": ";
		curch = gr->childs;
		while (curch != NULL) {
			curch->elem = findelem(curch->name, start);
			if (curch->elem == NULL) {
				cout << endl << "Error: graph has no member named " << curch->name << endl;
				clear(start);
				exit(0);
			}
			cout << curch->elem->name << "; ";
			curch = curch->next;
		}
		gr = gr->next;
		cout << endl;
	}
}

void out_inc(node* gr) //Print graph as an incidency matrix
{
	cout << "----------" << endl << "Incidency matrix" << endl;
	node* start = gr;
	node* gr2 = gr;
	int wid = maxwidth(gr) + 1;
	cout.width(wid);
	cout.setf(ios::left);
	cout << " ";
	while (gr != NULL) {
		cout.width(wid);
		cout << gr->name;
		gr = gr->next;
	}
	cout << endl;
	gr = start; 

	while (gr != NULL) {
		gr2 = start;
		cout.width(wid);
		cout << gr->name;
		while (gr2 != NULL) {
			cout.width(wid);
			if (is_Edge(gr, gr2))
				cout << "1";
			else
				cout << "0";
			gr2 = gr2->next;
		}
		cout << endl;
		gr = gr->next;
	}
}



int main()
{
	char name[80];
	node* gr = new node;
	cout << "Enter file name: ";
	cin >> name;
	ifstream file(name);
	if (!file.is_open()) {
		cout << "File is not open!" << endl;
		return 0;
	}
	readlist(gr, &file);
	out(gr);
	out_inc(gr);
	clear(gr);
	return 0;
}