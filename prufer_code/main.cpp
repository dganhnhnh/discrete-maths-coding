#include <stdio.h>

int n,i,j,edgeCount,previousLeaf=1,nextLeaf=1,startSearching=1;
int a[100][100];    int deg[100];
int x,y;

int lowestLabelLeaf(){
	int min,temp=0;
    for(i=startSearching; i<n;i++){
        if(deg[i] == 1) {
        	if(temp==0){
        		min=i;
        		temp++;
        	}
			else{
        		nextLeaf=i;	
//				printf("next %d ", nextLeaf);
				break;
        	}
//			printf("min %d ", i);
        }
    }
    previousLeaf=min;
	return min;
}

int adjacentVertex(int leaf){
	for (i=0;i<n;i++){
        if(a[leaf][i]==1 ) {
//            printf("dinh ke %d\n", i);
            return i;
        }
    }
}

void deleteEdge(int leaf, int ajc){
    printf("%d ", ajc); 
    a[leaf][ajc]=0;   a[ajc][leaf]=0;
    deg[leaf]--;    deg[ajc]--;
    
    edgeCount--;
}

int main(){
    scanf("%d", &edgeCount);
    n=edgeCount+1;
    
    for(i=0; i<edgeCount;i++){
        scanf("%d %d", &x,&y);
        a[x][y]++;
        a[y][x]++;
        deg[x]++; deg[y]++;
    }
    int chosenLeaf, ajc;
    
    while(edgeCount>1){
    	chosenLeaf=lowestLabelLeaf();
//    	printf("chosen %d ", chosenLeaf); 
    	ajc=adjacentVertex(chosenLeaf);
//    	printf("adjacent %d ", ajc); 
        deleteEdge(chosenLeaf, ajc);
        
        if (nextLeaf<ajc){
        	if(nextLeaf!=0)	startSearching=nextLeaf;
        	else startSearching=previousLeaf;
        }else{
        	if(ajc!=0) startSearching=ajc;
        	else startSearching=previousLeaf;
        }
    }
    return 0;
}

