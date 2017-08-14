//-----------------------------------------------------------------------------
// FindPath.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
#include"List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){

	FILE *in, *out;
	char line[MAX_LEN];
	int n = 0;

	// check command line for correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	// open files for reading and writing 
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if( out==NULL ){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	
	fgets(line, MAX_LEN, in);
	sscanf(line, "%d", &n);
	
	Graph G = newGraph(n);
		
	while( fgets(line, MAX_LEN, in) != NULL)  {
		int u=0;
		int v=0;
		
		sscanf(line, "%d %d", &u, &v);
		
		if(u==0 && v==0) {
			break;
		}
		
		addEdge(G,u,v);
	
	}
	
	printGraph(out,G);
	
	
	
	
	while( fgets(line, MAX_LEN, in) != NULL)  {
		int u=0;
		int v=0;
		
		sscanf(line, "%d %d", &u, &v);
		
		if(u==0 && v==0) {
			break;
		}
		fprintf(out, "%s", "\n");
		BFS(G,u);
		fprintf(out,"%s", "The distance from ");
		fprintf(out, "%d", u);
		fprintf(out, "%s", " to ");
		fprintf(out, "%d", v);
		fprintf(out, "%s", " is ");
		int gD = getDist(G,v);
		if(gD == INF) {
			fprintf(out, "%s\n", "infinity");
			
			fprintf(out, "%s", "No ");
			fprintf(out, "%d",u);
			fprintf(out, "%s", "-");
			fprintf(out, "%d", v);
			fprintf(out, "%s\n", " path exists");
			fprintf(out, "%s", "\n");
		}
		else {
			fprintf(out, "%d\n", getDist(G,v));
			
			List L = newList();
			getPath(L,G,v);
			fprintf(out, "%s", "A shortest ");
			fprintf(out, "%d",u);
			fprintf(out, "%s", "-");
			fprintf(out, "%d", v);
			fprintf(out, "%s", " path is:");
			printList(out,L);
			fprintf(out, "%s", "\n");
			freeList(&L);
		}
		
	}

	fclose(in);
	fclose(out);
	freeGraph(&G);


}