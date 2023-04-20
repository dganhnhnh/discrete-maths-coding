#include <iostream>
#include <vector>
#include <set>
using namespace std;

int i,j,n,x,y;
vector<vector<int> > dinhKe;

vector <int> prufer_code(){
	vector<bool> daXoa(n,false);
	vector<int> code(n-2);
	int deg[n];
	//lay danh sach cac dinh bac 1
	set<int> leafs;
	
	for(i=0;i<n;i++){
		deg[i] = dinhKe[i].size();
		if(deg[i]==1)	leafs.insert(i);
	}
	
	for(i=0;i<n-2;i++){
		int leaf=*leafs.begin();
		leafs.erase(leafs.begin());
		daXoa[leaf] = true;
		
		int next;
		for (j=0; j<dinhKe[leaf].size(); j++){
			if (daXoa[dinhKe[leaf][j]] == false)	next = dinhKe[leaf][j];
		}
		code[i] =next;
		if(--deg[next] == 1 && next!= 0 ) leafs.insert(next);
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
	
	vector<int> result = prufer_code();
	for(i=0; i< result.size(); i++){
		cout<<result[i]<<" ";
	}
	
//	for (i=0; i<n;i++){
//		cout<<i<<": ";
//		for(j=0; j<dinhKe[i].size(); j++){
//			cout<<dinhKe[i][j]<<" ";
//		}
//		cout<<'\n';
//	} 

	return 0;
}
