#include <iostream>
#include <vector>
#include <set>
using namespace std;
// using std::vector;

vector<vector<int>> adj;

vector<int> prufer_code(){
	int n=adj.size();
	set<int> leafs;
	vector<int>degree(n);
	vector<bool> killed(n,false);
	int i;

	for (i=0;i<n;i++){
		degree[i] = adj[i].size();
		if (degree[i] ==1)	leafs.insert(i);
	}

	vector<int> code(n-2);

	for (int i=0;i<n;i++){
		int leaf = *leafs.begin();
		leafs.erase(leafs.begin());
		killed[leaf]=true;

		int v;
		for(int u : adj[leaf]){
			if (!killed[u])	v=u;
		}

		code[i] =v;
		if (--degree[v] == 1)	leafs.insert(v);
	}
	return code;
}

int main(){
	//nhap danh sach ke
}