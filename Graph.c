//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Graph.h"
#include"List.h"


int order;
int size;
int source;


typedef struct GraphObj {
	List* neighbors;
	char* color;
	int* parent;
	int* distance;
} Graphobj;

// returns a Graph pointing to a 
//newly created GraphObj representing 
//a graph having n vertices and no edges
Graph newGraph(int n) {
	Graph G = malloc(sizeof(Graphobj));
	assert(G!=NULL);
	
	G->neighbors = calloc(n+1, sizeof(List*));
 	G->color = calloc(n+1, sizeof(char*));
 	G->parent = calloc(n+1,sizeof(int*));
 	G->distance = calloc(n+1,sizeof(int*));
	
	for(int i=1; i<=n; i++) {
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
		G->neighbors[i] = newList();
	}

	order = n;
	size = 0;
	source = NIL;
	
	return G;
}


int getOrder(Graph G) {
	return order;
}

int getSize(Graph G) {
	return size;
}

//returns the source vertex
// most recently used in function BFS(), 
//or NIL if BFS() has not yet been called
int getSource(Graph G) {
	return source;
}

//return the parent of vertex u in 
//the Breadth- First tree created by 
//BFS(), or NIL if BFS() has not yet been called
//Pre: 1 <= u <= getOrder(G) 
int getParent(Graph G, int u) {
	if(G != NULL) {
		if( u >= 1 && u <= getOrder(G) ) {
			return G->parent[u];
		}
		else if(u < 1) {
			printf("PreCondition Error: getParent: vertex u is too low \n");
			exit(1);
		}
		else {
			printf("PreCondition Error: getParent: vertex u is too high \n");
			exit(1);
		}
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
}


//Function getDist() returns
// the distance from the most recent BFS 
//source to vertex u,or INF if BFS() 
//has not yet been called
//Pre: 1 <= u <= getOrder(G) 
int getDist(Graph G, int u) {
	if(G != NULL) {
		if( u >= 1 && u <= getOrder(G) ) {
			return G->distance[u];
		}
		else if(u < 1) {
			printf("PreCondition Error: getDist: vertex u is too low \n");
			exit(1);
		}
		else {
			printf("PreCondition Error: getDist: vertex u is too high \n");
			exit(1);
		}
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
}

//appends to the List L the vertices of 
//a shortest path in G from source to u, 
//or appends to L the value NIL if no such path exists
//Pre: 1 <= u <= getOrder(G) 
void getPath(List L, Graph G, int u) {
	if( G != NULL ) {
		if( getSource(G) != NIL ) {
			if( u == source ) {
				append(L, u );
			}
			else if(G->parent[u]==NIL) {
				append(L, NIL);
			}
			else {
				getPath(L,G, G->parent[u]);
				append(L,u);
			}
		}
		else {
			printf("PreCondition Error: getPath: BFS not called yet so getSource is nil \n");
			exit(1);
		}
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
}



//inserts a new edge joining u to v, 
//i.e. u is added to the adjacency List of v, 
//and v to the adjacency List of u.
//Pre: two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v) {
	if( G != NULL ) {
		if( 1<=u && u<=getOrder(G) && 1<=v && v<=getOrder(G) ) {
			addArc(G,u,v);
			addArc(G,v,u);
			size--;
		}
		else if (1 > u) {
			printf("PreCondition Error: addEdge: vertex u is too low \n");
			exit(1);
		}
		else if(1 > v) {
			printf("PreCondition Error: addEdge: vertex v is too low \n");
			exit(1);
		}
		else if(u > getOrder(G)) {
			printf("PreCondition Error: addEdge: vertex u is too high \n");
			exit(1);
		}
		else { // v > getOrder(G)
		printf("PreCondition Error: addEdge: vertex v is too high \n");
			exit(1);
		}
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
	
}



//inserts a new directed edge from u to v, 
//i.e. v is added to the adjacency List of u 
//(but not u to the adjacency List of v)
//Pre: two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v) {
	if( G != NULL ) {
		if( 1<=u && u<=getOrder(G) && 1<=v && v<=getOrder(G) ) {
			if(length(G->neighbors[u]) == 0 ) {
				append(G->neighbors[u],v);
			}
			else {
				int len = length(G->neighbors[u])-1;
				moveFront(G->neighbors[u]);
				while( len > 0 && get(G->neighbors[u]) < v ) {
					moveNext(G->neighbors[u]);
					len--;
				}
				if( get(G->neighbors[u]) > v) {
 					insertBefore(G->neighbors[u],v);
 				}
 				else {
 					insertAfter(G->neighbors[u],v);
 				}
			}
			size++;
		}
		else if (1 > u) {
			printf("PreCondition Error: addArc: vertex u is too low \n");
			exit(1);
		}
		else if(1 > v) {
			printf("PreCondition Error: addArc: vertex v is too low \n");
			exit(1);
		}
		else if(u > getOrder(G)) {
			printf("PreCondition Error: addArc: vertex u is too high \n");
			exit(1);
		}
		else { // v > getOrder(G)
		printf("PreCondition Error: addArc: vertex v is too high \n");
			exit(1);
		}
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
}




//runs the BFS algorithm on the Graph 
// G with source s, setting the color, distance, 
//parent, and source fields of G accordingly.
void BFS(Graph G, int s) {
	if( G!= NULL ) {
		source = s;
		for(int i=1; i<= getOrder(G); i++) {
			G->color[i] = 'w';
			G->distance[i] = INF;
			G->parent[i] = NIL;
		}
		G->color[s] = 'g';
		G->distance[s] = 0;
		G->parent[s] = NIL;
		List Q = newList();
		append(Q, s);
		while(length(Q) != 0) {
			moveFront(Q);
			int x = get(Q);
			delete(Q);
			if(length(G->neighbors[x]) > 0) {
				moveFront(G->neighbors[x]);
			}
			for(int i=1; i<= length(G->neighbors[x]); i++) {
				int y = get(G->neighbors[x]);
				if( G->color[y] == 'w') {
					G->color[y] = 'g';
					G->distance[y] = G->distance[x] + 1;
					G->parent[y] = x;
					append(Q,y);
				}
				moveNext(G->neighbors[x]);
			}
			G->color[x] = 'b';
		}
		freeList(&Q);
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
}



//deletes all edges of G, 
//restoring it to its original
//(no edge) state.
void makeNull(Graph G) {
	size=0;
	source = NIL;
	for(int i=1; i<= getOrder(G); i++) {
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
		freeList(&G->neighbors[i]);
	}
}


//freeGraph() frees all dynamic 
//memory associated with the Graph 
//*pG,then sets the handle *pG to NULL
void freeGraph(Graph* pG) {
	if(*pG != NULL && pG != NULL) {
		makeNull(*pG);
		free((*pG)->distance);
 		free((*pG)->parent);
 		free((*pG)->color);
		free((*pG)->neighbors);
	}
	free(*pG);
	*pG = NULL;
}





//prints the adjacency list representation
// of G to the file pointed to by out
void printGraph(FILE* out, Graph G) {
	for(int i=1; i<= getOrder(G) ; i++) {
		fprintf(out, "%d", i);
		fprintf(out, "%s", ":");
		printList(out, G->neighbors[i]);
		fprintf(out, "%s", "\n");
	}
}

















