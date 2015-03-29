/**
	Wei Ding 03597803
	Jonathan Liou 47102230





//Coded by Wei Ding and Jonathan; Debug together
void initialize_problem(struct node *n);








//Coded by Wei Ding; Debug together
int goal_test(struct state s);
void print_node(struct node *n);
void print_goal(struct node *n);
int visited(struct node *n);
float get_heu(char loc[]);
int is_same(struct node* first, struct node* second);







//Coded by Wei Ding; Jonathan has another version does not work
struct node *expand(struct node **n);






//Coded by Jonathan; Wei Ding has another version also works
struct node* delete_node(struct node* node_to_delete, struct node* node_sets);






//Coded by Wei Ding; Jonathan has another version but does not work
int general_search(char stype[], struct node *queue);







//Coded by Wei Ding; Debug by Wei Ding
struct node *uniform_cost_queue(struct node *old_queue);
struct node *depth_first_queue(struct node *old_queue);
struct node *breadth_first_queue(struct node *old_queue);







//Coded by Jonathan; Debug by Jonathan
struct node *greedy_queue(struct node *old_queue);







//Coded by Jonathan; Debug by Jonathan
struct node *astar_queue(struct node *old_queue);


*/



#include "mysearch.h"
#include <cmath>
#include <string.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

const struct transition transition_set[] =
{{"Ann Arbor","Plymouth", 17.2},
{"Ann Arbor","Romulus", 23.1},
{"Ann Arbor","Brighton", 19.2},
{"Brighton","Pontiac", 34.1},
{"Brighton","Farmington Hills", 21.4},
{"Plymouth","Romulus", 23.1},
{"Plymouth","Farmington Hills", 14.0},
{"Plymouth","Detroit", 27.9},
{"Romulus","Detroit", 23.5},
{"Farmington Hills","Royal Oak", 16.9},
{"Farmington Hills","Detroit", 28.3},
{"Farmington Hills","Pontiac", 15.5},
{"Pontiac","Sterling Heights", 17.2},
{"Pontiac","Royal Oak", 13.3},
{"Romeo","Pontiac", 27.8},
{"Romeo","Sterling Heights", 16.5}};
const struct latlon coords[] =
{ {"Ann Arbor", 42.280826,-83.743038},
 {"Brighton", 42.529477,-83.780221},
 {"Detroit", 42.331427,-83.045754},
 {"Farmington Hills", 42.482822,-83.418382},
 {"Plymouth", 42.37309,-83.50202},
 {"Pontiac", 42.638922,-83.291047},
 {"Romeo", 42.802808,-83.012987},
 {"Romulus", 42.24115,-83.612994},
 {"Royal Oak", 42.48948,-83.144648},
 {"Sterling Heights", 42.580312,-83.030203}};
 
 struct node* start;
 struct node* end;
 struct latlon beg;
 struct latlon desti;
 struct node *visit_list;
 struct node *GOAL_NODE;
 struct node *QUEUE; //initial queue



void initialize_problem(struct node *n) {
	// Wei Ding

	start = new node;
	end = new node;
	strcpy(start->s.location, n->s.location);
	start->g = 0;
	start->h = get_heu(n->s.location);
	start->next = NULL;
	start->prev = NULL;
	strcpy(end->s.location,n->linker->s.location);

	visit_list = NULL;

//initialize the queue
	QUEUE = new node;
	strcpy(QUEUE->s.location, start->s.location);
	QUEUE->linker = NULL;
	QUEUE->prev = NULL;
	QUEUE->next = NULL;
	QUEUE->g = 0;
	QUEUE->h = start->h;


	for(int i = 0; i < 10; i++){
		if(strcmp(coords[i].city, start->s.location)==0){	
			strcpy(beg.city,coords[i].city);
			beg.lat = coords[i].lat;
			beg.lon = coords[i].lon;
		}

		if(strcmp(coords[i].city,end->s.location)==0){	
			strcpy(desti.city,coords[i].city);
			desti.lat = coords[i].lat;
			desti.lon = coords[i].lon;
		}
	}



}

void print_node(struct node *n) {
	//Wei Ding
	cout<<"Location: "<<n->s.location;
	cout<<"\t path cost: "<<n->g;
	cout<<"\t Strait-Line distance: "<<get_heu(n->s.location)<<endl;
}

void print_goal(struct node* n){
	//Wei Ding
	struct node* pt = n;
	for(; pt->prev!=NULL; pt=pt->prev){
		pt->prev->next = pt;
	}

	for (; pt!=NULL; pt=pt->next) {
		cout<<pt->s.location<<"->";
	}
	cout<<"\b"<<"\b"<<"  "<<endl;
}

int visited(struct node *n) {
	//Wei Ding
	if (n==NULL) return 0;
	struct node *pt;
	for (pt = visit_list;  pt != NULL; pt = pt->linker){
		if (strcmp(pt->s.location,n->s.location)==0)
		// if (is_same(pt,n))
			return 1;
	}
	return 0;
	}


float get_heu(char loc[]){
	//Wei Ding
	float lat_diff = 0;
	float lon_diff = 0;

	for(int i = 0; i < 10; i++) {
		if(strcmp(coords[i].city, loc)==0) {
			lat_diff = coords[i].lat - desti.lat;
			lon_diff = coords[i].lon - desti.lon;
			return sqrt((double)(lat_diff*lat_diff+lon_diff*lon_diff));
		}
	}
}

/*
struct node *expand(struct node *n) //modified to only expand one node at a time instead of passing in a list (by double pointer)
{
	//given a node list, return a node list of successors
	struct node *newnodes = NULL;
		int i=0;
		for (i = 0; i < 16; i++) //hardcoded in length of transition_set array...not sure how else to do it
		{
			if (strcmp((*n).s.location, transition_set[i].start) == 0) //if initial terminus matches node
			{
				struct node *nn = (node*)malloc(sizeof(struct node));
				
				strcpy((*nn).s.location, transition_set[i].end); 
				(*nn).prev = n;
	
				if (visited(nn) == 0) //if node has not yet been visited (checked), add to visit list 
				{
					if (newnodes == NULL)
					{
						newnodes = nn;
						(*nn).prev = n;	
					}
					else
					{
						(*newnodes).linker = nn;
						(*nn).prev = n;
					}
				}
			}
			else if (strcmp((*n).s.location, transition_set[i].end) == 0) //if final terminus matches node
			{
				struct node *nn = (node*)malloc(sizeof(struct node));
				strcpy((*nn).s.location, transition_set[i].start);
				(*nn).prev = n;
				if (visited(nn) == 0)
				{
					if (newnodes == NULL)
					{
						newnodes = nn;
						(*nn).prev = NULL;
					}
					else
					{
						(*newnodes).linker = nn;
						(*nn).prev = n;
					}
				}
			}
		}
	return newnodes;
	
}

*/

struct node* expand(struct node *n){
	//Wei Ding

	struct node* Set = NULL;//linked list
	struct node** pt = &Set;
	for(int i = 0; i < 16; i++) {
		if (strcmp(transition_set[i].start, n->s.location)==0) {

			*pt = new node;
			strcpy((*pt)->s.location, transition_set[i].end);
			(*pt)->g = n->g + transition_set[i].distance;
			(*pt)->h = get_heu((*pt)->s.location);
			(*pt)->prev = n;
			(*pt)->next = NULL;
			(*pt)->linker = NULL;
			pt = &((*pt)->linker);
		} 

		if (strcmp(transition_set[i].end, n->s.location)==0) {
	
			*pt = new node;
			strcpy((*pt)->s.location, transition_set[i].start);
			(*pt)->g = n->g + transition_set[i].distance;
			(*pt)->h = get_heu((*pt)->s.location);
			(*pt)->prev = n;
			(*pt)->next = NULL;
			(*pt)->linker = NULL;
			pt = &((*pt)->linker);
		}
	}
	return Set;
}


void print_list(struct node* list) {
	//Wei Ding
	for(struct node* pt = list; pt != NULL; pt = pt->linker) {
		cout<<pt->s.location<<"->";
	}
	cout<<"\b"<<"\b"<<"  "<<endl;

}

struct node* delete_node(struct node *nodetoremove, struct node *listhead)
{
		// Jonathan's implementation
		//only checking by name
		struct node *n = listhead;
		if (n == NULL) //if list does not exist
		{
			return listhead;
		}
		if (strcmp((*n).s.location, (*nodetoremove).s.location) == 0) //if node to remove is at head of list
		{
			struct node *head = listhead;
			listhead = (*listhead).linker;
			return listhead;
		}
		
		while ((*n).linker != NULL)
		{
			struct node *nextnode = (*n).linker;
			if (strcmp((*nextnode).s.location, (*nodetoremove).s.location) == 0) //if node to remove is at next node over
			{
				struct node *nextnextnode = (*nextnode).linker;
				struct node *temp = nextnode;
				(*n).linker = nextnextnode;
				return listhead;			
			}
			
				n = (*n).linker;
		}
		return listhead; //return list if target is not found

		}


/*

//Wei Ding's implementation for delete;

int is_same(struct node* first, struct node* second) {
	if(strcmp(first->s.location, second->s.location) == 0) {
		if(first->prev == second->prev) { // check if has the same father
			return 1;
		}
	}

	return 0;
}

struct node* delete_node(struct node* node_to_delete, struct node* node_sets) {

	if (is_same(node_sets, node_to_delete)) {
		return node_sets->linker;
	}

	for(struct node* pt = node_sets; pt != NULL; pt = pt->linker) {
		if(is_same(pt->linker, node_to_delete)){
			pt->linker = node_to_delete->linker;
			return node_sets;
		}
	}

	return node_sets;
}

*/


int general_search(char stype[], struct node *queue) {

	//Wei Ding
	struct node* tmp;
	struct node* visit_tmp;

	while(true) {

		if(queue == NULL) return 0;

		if(visited(queue)){
			tmp = queue->linker;

			queue = tmp;
			continue;
		}
		if(strcmp(queue->s.location,end->s.location)==0) {
			GOAL_NODE = queue;
			return 1; //queue is already pointing to the answer path
		}

		visit_tmp = new node;

		strcpy(visit_tmp->s.location,queue->s.location);
		visit_tmp->linker = visit_list;
		visit_list = visit_tmp;


		if(strcmp(stype,"depth_first")==0)
			queue = depth_first_queue(queue);
		if(strcmp(stype,"breadth_first")==0)
			queue = breadth_first_queue(queue);
		if(strcmp(stype,"uniform_cost")==0)
			queue = uniform_cost_queue(queue);
		if(strcmp(stype,"greedy")==0)
			queue = greedy_queue(queue);
		if(strcmp(stype,"astar")==0)
			queue = astar_queue(queue);

		}
}

struct node *depth_first_queue(struct node *old_queue){
//Wei Ding
	struct node* ret = expand(old_queue);
	struct node* pt = ret;
	while(pt->linker != NULL){pt = pt->linker;}
	pt->linker = old_queue;
	return ret;
}

struct node *breadth_first_queue(struct node *old_queue){
//Wei Ding
	struct node* pt = old_queue;

	while(pt->linker != NULL) {pt = pt->linker;}//move to the end of the que
	pt->linker = expand(old_queue);
	return old_queue;
}

struct node* copy_node(struct node* to_copy) {
//Wei Ding
	if(to_copy == NULL) return NULL;

	struct node* copied = new node;
	strcpy(copied->s.location, to_copy->s.location);
	copied->g = to_copy->g;
	copied->h = to_copy->h;
	copied->prev = to_copy->prev;
	copied->next = to_copy->next;
	copied->linker = NULL;
}

struct node *uniform_cost_queue(struct node *old_queue){
//Wei Ding
	struct node* ordered = NULL;
	struct node** pt = &ordered;
	struct node* last_node_in_queue = old_queue;
	struct node* to_add = NULL;
	while(last_node_in_queue->linker != NULL) {
		last_node_in_queue = last_node_in_queue->linker;
	}

	last_node_in_queue->linker = expand(old_queue);

	struct node* to_order = old_queue;


	float min_cost;

while(to_order != NULL) {
	min_cost = to_order->g;

		for(struct node* tmp = to_order; tmp != NULL; tmp = tmp->linker) {
			if(tmp->g <= min_cost) {
				min_cost = tmp->g;
				to_add = tmp;
			}
		}

		*pt = copy_node(to_add);
		pt = &((*pt)->linker);
		*pt = NULL;// the last node's linker = NULL
		to_order = delete_node(to_add, to_order);

	}

	return ordered;

}

struct node *greedy_queue(struct node *old_queue){
// Jonathan Liou
//returns old queue with the successors appended in the right place
//for greedy queue
//get_heu gets heuristic of the node (in this case a straight-line distance to the goal node)
	struct node* successors = expand(old_queue);
	struct node *pt = old_queue;
	while ((*pt).linker != NULL)
	{
		pt = (*pt).linker;
	}
	(*pt).linker = successors;

	// cout << "Expanded nodes and parent nodes before ordering: \n";
	// print_list(old_queue);
	//reorder the list of successors AND the old queue according to heuristic in increasing order, sequential sorting
	struct node* ret = NULL;
	struct node* retend = ret;
	while (old_queue != NULL)
	{
		struct node *closest = NULL;
		struct node *n = old_queue;
		while (n != NULL)
		{
			if (closest == NULL)
			{
				closest = n;
			}
			else if (get_heu((*n).s.location) < get_heu((*closest).s.location))
			{
				closest = n;
			}
			n = (*n).linker;
		}

		//copy-construct a copy of the closest node
		struct node *newclosest = new node;
		strcpy((*newclosest).s.location, (*closest).s.location);
		(*newclosest).g = (*closest).g;
		(*newclosest).h = (*closest).h;
		(*newclosest).prev = (*closest).prev;
		(*newclosest).linker = NULL;
		
		if (ret == NULL && retend == NULL)
		{
			ret = newclosest;
			retend = ret;
		}
		else
		{		
			(*retend).linker = newclosest;
			retend = (*retend).linker;
		}

		//delete closest from old_queue
		//TODO: build this function
		old_queue = delete_node(closest, old_queue);
		
	}
	// cout << "Final ordered pre-fringe list: \n";
	// print_list(ret);
	// struct node *h = ret;
	// while (h != NULL)
	// {
	// 	cout << get_heu((*h).s.location) << " ";
	// 	h = (*h).linker;
	// }
	// cout << "\n";
	return ret;
}


struct node *astar_queue(struct node *old_queue){
	// Jonathan Liou
//copied and pasted from greedy queue, adjustments made as necessary
//get_heu gets heuristic of the node (in this case a straight-line distance to the goal node)
	struct node* successors = expand(old_queue);
	struct node *pt = old_queue;
	while ((*pt).linker != NULL)
	{
		pt = (*pt).linker;
	}
	(*pt).linker = successors;

	//reorder the list of successors AND the old queue according to heuristic in increasing order, sequential sorting
	struct node* ret = NULL;
	struct node* retend = ret;
	while (old_queue != NULL)
	{
		struct node *closest = NULL;
		struct node *n = old_queue;
		while (n != NULL)
		{
			if (closest == NULL)
			{
				closest = n;
			}
			else if ((*n).g + (get_heu((*n).s.location)) < (*closest).g + (get_heu((*closest).s.location)))
			{
				closest = n;
			}
			n = (*n).linker;
		}

		//copy-construct a copy of the closest node
		struct node *newclosest = new node;
		strcpy((*newclosest).s.location, (*closest).s.location);
		(*newclosest).g = (*closest).g;
		(*newclosest).h = (*closest).h;
		(*newclosest).prev = (*closest).prev;
		(*newclosest).linker = NULL;
		
		if (ret == NULL && retend == NULL)
		{
			ret = newclosest;
			retend = ret;
		}
		else
		{		
			(*retend).linker = newclosest;
			retend = (*retend).linker;
		}

		//delete closest from old_queue
		//TODO: build this function
		old_queue = delete_node(closest, old_queue);
		
	}

	return ret;
}