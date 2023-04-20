#include <iostream>
#include <vector>
#include <set>
using namespace std;

int i,j,n,x,y;
vector<vector<int> > dinhKe;
vector<int> parent;

void dfs(int v) {
    for (int i=0; i< dinhKe[v].size(); i++) {
    	int u=dinhKe[v][i];
        if (u != parent[v]) {
            parent[u] = v;
//            cout<<"parent of "<<u<<" is "<<v<<'\n'<<"searching for child of "<<u<<'\n';
            dfs(u);
        }
    }
}

vector <int> prufer_code(){
	vector<bool> daXoa(n,false);
	vector<int> code(n-2);
	int deg[n], ptr=-1;
	
	for(i=0;i<n;i++){
		deg[i] = dinhKe[i].size();
		if(deg[i] == 1 && ptr ==-1)	ptr=i;
	}
	
    parent.resize(n);
    parent[n-1] = -1;
    dfs(n-1);
	
	int leaf=ptr;
	for(i=0;i<n-2;i++){
		int next=parent[leaf];	
		code[i] = next;
		
		if(--deg[next] == 1 && next<ptr&&next!= 0){
			leaf=next;
		}else{
			do{
				ptr++;
			}while(deg[ptr]!= 1 || ptr==0);
			leaf=ptr;
		}
		if(i==n-4) leaf=0;
	}
	return code;
}

int main(){
	int temp;
	cin>>temp;
	n=temp+1;
	dinhKe.resize(n); 
	
	//nhap danh sach ke
	for(i=0;i<n-1; i++){
		cin>> x >> y;
		dinhKe[x].push_back(y);
		dinhKe[y].push_back(x);
	}
//	
//    for (int i=0; i<=n;i++){
//    	cout<<i<<": "<<parent[i]<<'\n'; 
//    }
	
	vector<int> result = prufer_code();
	for(i=0; i< result.size(); i++){
		cout<<result[i]<<" ";
	}
	
	return 0;
}
