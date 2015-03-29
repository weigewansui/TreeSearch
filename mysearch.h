//
// mysearch.h  
// C or C++ implementation acceptable & possible with the below "struct" definitions.
// Feel free to augment/modify data structures as you'd like.
//
// Declares "General Search" software parameters and functions.
//

#ifndef  MYSEARCH
#define MYSEARCH

/* Domain-specific structure to define world state */
struct state {
  char location[20];  /* Map location for route planning */
  struct state *prev;        /* Link to previous location along the route */
};

/* Domain-specific structure to define transitions  */
struct transition {
  char start[20];  // Initial location of map "route segment"
  char end[20];    // Final location of map "route segment"
  float distance;  // Distance (cost) of travelling on this route segment
};

/* Structure for distance-based heuristic (h) computation */
struct latlon {
  char  city[20];
  float lat;
  float lon;
};

/* General structure to define each search tree node and open/closed list element */
struct node {
  struct state s;       /* Domain-specific state description */
  float g, h;           /* Path cost (g) and heuristic (h) values for this node */
  struct node *prev;    /* Doubly-linked list to earlier and subsequent node values */
  struct node *next;
  struct node *linker; // used for linked list of node
};


/* Global variable:  "Closed list" / list of visited nodes */
#ifdef MYSEARCH_MAIN
  struct node *visit_list=NULL;
#else
  extern struct node *visit_list;
#endif

/* Domain-specific function prototypes (suggested - please change as you'd like) */

void initialize_problem(struct node *n);
int goal_test(struct state s);
void print_node(struct node *n);
void print_goal(struct node *n);
int visited(struct node *n);
float get_heu(char loc[]);
struct node *expand(struct node **n);
int is_same(struct node* first, struct node* second);
struct node* delete_node(struct node* node_to_delete, struct node* node_sets);

/* General search function prototypes (suggested - please change as you'd like) */

int general_search(char stype[], struct node *queue);
struct node *uniform_cost_queue(struct node *old_queue);
struct node *greedy_queue(struct node *old_queue);
struct node *astar_queue(struct node *old_queue);
struct node *depth_first_queue(struct node *old_queue);
struct node *breadth_first_queue(struct node *old_queue);
#endif
