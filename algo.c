#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define LINK_SIZE sizeof(struct Link)
#define NODE_SIZE sizeof(struct Node)
int M,N;

struct Node{
	int id;
	int link_count;
	struct Link* link;
};

struct Link{
	int weight;
	struct Node *first, *second;
};

int find_shortest(struct Node *node,int first ,int last,int prev){
	int paths_num=0,i,weight=INT_MAX,curweight;

	for(i=0;i<node[first-1].link_count;i++){
		int id1 =node[first-1].link[i].first->id;
		int id2 =node[first-1].link[i].second->id;
		int id;

		if(id1 == last || id2 == last){
			curweight = node[first-1].link[i].weight;
			if(curweight < weight) weight = curweight;
			continue;
		}
		if(id1 != first &&  id1 != prev){
			id = id1;
		}else if(id2 != first &&  id2 != prev){
			id = id2;
		}else continue;

		curweight = node[first-1].link[i].weight + find_shortest(node,id,last,first);
		if(curweight<weight) weight = curweight; 
	}
	return weight;
}

int main(){
	printf("\n!!! num1, num2, a and b must be in range from 0 to N-1 !!!\n\n");
	printf("input N: ");
	scanf("%d",&N);
	printf("input M: ");
	scanf("%d",&M);

	if(N<=0 || M<=0){
		printf("\nWrong input !!!\n");
		return -1;
	}

	struct Node *nd = (struct Node*)malloc(N*(NODE_SIZE)+(M*LINK_SIZE));
	int i, *arr = (int*)malloc(N*sizeof(int));
	
	for(i=0; i<N; i++){
		arr[i] = 0;
		nd[i].id = i+1;
		nd[i].link_count = 0;
	}

	struct Link *link = (struct Link*)malloc(M*LINK_SIZE);

	for(i=0;i<M;i++)
		while(true){
			int num1,num2,weight;
			printf("input num1: ");
			scanf("%d",&num1);
			printf("input num2: ");
			scanf("%d",&num2);
			printf("input weight: ");
			scanf("%d",&weight);

			if(num1>N-1 || num2>N-1 || num1<0 || num2<0){
				printf("\nwrong input\n");
				continue;
			}
			arr[num1]++;
			arr[num2]++;
			link[i].first = &nd[num1];
			link[i].second = &nd[num2];
			link[i].weight =weight;

			break;
		}
//adds links,"edges" to the nodes and allocates memory for them
	for(i=0;i<N;i++){
		nd[i].link = malloc(LINK_SIZE*arr[i]);
		nd[i].link_count = arr[i];
		int j;
		for(j=0;j<arr[i];){
			int it;
			for(it=0;it<M;it++){
				if(link[it].first->id==i+1 || link[it].second->id == i+1){
					nd[i].link[j] = link[it];
					j++;
				}
			}
		}
	}

	int a, b;
	printf("input a: ");
	scanf("%d",&a);
	printf("input b: ");
	scanf("%d",&b);

	printf("shortest path %d\n",find_shortest(nd,a+1,b+1,-1));

	free(arr);
	free(link);	
	free(nd);
	return 0;
}