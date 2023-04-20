#include <iostream>
#include <fstream>

#include <vector>
#include <set>
using namespace std;

int i,j,n,x,y;	//so canh
vector<vector<int> > dinhKe;

vector <int> prufer_code(){
	vector<bool> daXoa(n,false);
	vector<int> code(n-2);
	int deg[n];
	//leafs
	set<int> leafs;
	for(i=0;i<=n;i++){
		deg[i] = dinhKe[i].size();
		if(deg[i]==1)	leafs.insert(i);
	}
	
	for(i=0;i<n-1;i++){
		int leaf=*leafs.begin();
		leafs.erase(leafs.begin());
		daXoa[leaf] = true;
		
		int v;
		for (j=0; j<dinhKe[leaf].size(); j++){
			if (daXoa[dinhKe[leaf][j]] == false)	v = dinhKe[leaf][j];
		}
		code[i] =v;
		if(--deg[v] == 1 && v!= 0) leafs.insert(v);
	}
	
	return code;
}

int main(){
	
	ifstream myfile;
  	myfile.open ("tree_list.txt");
  	myfile>>n;
	
//	cin>>n;
	
	for(i=0;i<=n; i++){
		vector<int>vect;
		dinhKe.push_back(vect);
	}
	
//	//nhap danh sach ke
//	for(i=0;i<n; i++){
//		cin>> x >> y;
//		dinhKe[x].push_back(y);
//		dinhKe[y].push_back(x);
//	}

  	for (int i = 0; i < n; i++){
  		myfile>>x >> y;
    	dinhKe[x].push_back(y);
		dinhKe[y].push_back(x);
  	}
	myfile.close();
	
//	for(i=0;i<n; i++){
//		cin>> x >> y;
//		dinhKe[x].push_back(y);
//		dinhKe[y].push_back(x);
//	}
//	
	vector<int> result = prufer_code();
	for(i=0; i<=result.size(); i++){
		cout<<result[i]<<" ";
	}
	
	//test
//	for(i=0;i<=n;i++){
//		if(dinhKe[i].size()==1)	cout<<i<< " ";
//		cout<<'\n';
//	}
	
//	for(i=0;i<=n; i++){
//		for(j=0;j<dinhKe[i].size(); j++){
//			cout<<dinhKe[i][j]<<" ";
//		}
//		cout<<'\n';
//	}

	return 0;
}
