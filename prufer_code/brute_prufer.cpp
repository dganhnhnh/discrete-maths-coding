#include <iostream>
using namespace std;

int n,i,j,soCanh,previousLeaf=1,nextLeaf=1;
int a[100][100];    int deg[100];
int x,y;

int lowestLabelLeaf(){
    for(i=1; i<n;i++){
        if(deg[i] == 1) {
			return i;
        }
    }
}
void deleteEdge(int leaf){
    for (i=0;i<n;i++){
        if(a[leaf][i]==1 ) {
//            printf("dinh ke %d\n", i);
            break;
        }
        // check unique link
    }
    cout<<i<<" ";
    a[leaf][i]=0;   a[i][leaf]=0;
    deg[leaf]--;    deg[i]--;
    
    soCanh--;
}

int main(){
    cin>>soCanh;
    n=soCanh+1;
    
    for(i=0; i<soCanh;i++){
        cin>>x>>y;
        a[x][y]++;
        a[y][x]++;
        deg[x]++; deg[y]++;
    }
    
    while(soCanh>1){
        	deleteEdge(lowestLabelLeaf());
    }
    
    return 0;
}

