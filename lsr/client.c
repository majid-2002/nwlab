#include <stdio.h>
#define infinity 9999
int i, j, count, min, n, start, next;
int cost[10][10], dist[10], visited[10], prev[10];
void dijk(){
    for(i=0; i<n; i++){
   	 dist[i] = cost[start][i];
   	 visited[i] = 0;
   	 prev[i] = start;
    }  
    dist[start] = 0;
    visited[start] = 1;
    count = 1;
    while(count < n-1){
   	 min = infinity;
   	 for(i=0; i<n; i++){
   		 if(!visited[i] && dist[i] < min){
   			 min = dist[i];
   			 next = i;
   		 }
   	 }
   	 visited[next] = 1;
   	 for(i=0;i<n;i++){
   		 if(!visited[i]){
   			 if(dist[i] > min + cost[next][i]){
   				 dist[i] = min + cost[next][i];
   				 prev[i] = next;
   			 }
   		 }
   	 }
   	 count++;
    }
}
void display(){
    printf("distance: ");
    for(i=0;i<n;i++){
   	 if(i!=start){
   		 printf("\ndist to node %d = %d\n",i,dist[i]);
   		 printf("path: %d",i);
   		 j = i;
   		 while(j!=start){
   			 j=prev[j];
   			 printf(" <- %d",j);
   		 }
   		 printf("\n");
   	 }
    }
    
}
void main(){
    printf("no of nodes: ");
    scanf("%d",&n);
    printf("cost matrix\n");
    for(i=0;i<n;i++){
   	 for(j=0;j<n;j++){
   		 int d;
   		 scanf("%d",&d);
   		 if(d==0)
   			 cost[i][j] = infinity    ;
   		 else
   			 cost[i][j] = d;
   	 }
    }
    printf("starting node: ");
    scanf("%d",&start);
    dijk();
    display();
}