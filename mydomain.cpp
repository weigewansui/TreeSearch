#include "mysearch.h"
#include "mysearch.cpp"
#include <iostream>

using namespace std;
int main() {
	struct node* problem = new node;

	strcpy(problem->s.location, "Ann Arbor");
	problem->linker = new node;
	strcpy(problem->linker->s.location, "Romeo");

	initialize_problem(problem);

char method[50];

cout<<"---------------Test breadth function------------------------\n";
initialize_problem(problem);
	 strcpy(method,"breadth_first");
	if(general_search(method,QUEUE)!=0) print_goal(GOAL_NODE);
	
	print_node(GOAL_NODE);

cout<<"----------------Test depth function-----------------------\n";
initialize_problem(problem);
	strcpy(method,"depth_first");
	if(general_search(method,QUEUE)!=0) print_goal(GOAL_NODE);
	
	print_node(GOAL_NODE);

cout<<"----------------------Uniform cost function---------------\n";
initialize_problem(problem);
	strcpy(method,"uniform_cost");
	if(general_search(method,QUEUE)!=0) print_goal(GOAL_NODE);
	
	print_node(GOAL_NODE);

cout<<"--------------------Test greedy search function------------\n";
initialize_problem(problem);
	strcpy(method, "greedy");
	if(general_search(method,QUEUE)!=0) print_goal(GOAL_NODE);
	
	print_node(GOAL_NODE);
	
cout<<"----------------------A star function---------------------\n";
initialize_problem(problem);
	strcpy(method, "astar");
	if(general_search(method,QUEUE)!=0) print_goal(GOAL_NODE);
	print_node(GOAL_NODE);

}