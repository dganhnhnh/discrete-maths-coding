#include <iostream>
#include <vector>	
#include <set>
#include<fstream>
// #include<set>
using namespace std;

int numVtx,edgeCnt;
vector<vector<int> > ajc;
vector <int> v;
vector <int> colorOfVtx;
vector<bool> daToMau(numVtx,false);
string colorArr[39] = { "snow","red","green","blue","SlateBlue2","yellow","purple","gray","lawn green","YellowGreen","cyan","hot pink",
		"orange","snow1","khaki","SlateGray3","wheat","purple","pink1","VioletRed1","DarkCyan","black","LightGreen","DarkMagenta","DarkRed",
		"DarkCyan","DarkBlue","DarkGray","grey100","grey99","grey98","grey97","grey96","grey95","grey94","grey93","grey92","grey91","grey90"};

void setOrder(){
	int i;
	for(i =0; i<numVtx;i++){
		v.push_back(i);
	}
	//TODO: thuat toan hoan vi
}

int minColorAvailable(int v){
	//van de!
	
	int sz=ajc[v].size();
	int min=0;
	set<int> colorOfAjc;
	int j;
	for (j=0; j<sz; j++){
		if(daToMau[ajc[v][j]]==true){
			colorOfAjc.insert(colorOfVtx[ajc[v][j]]);
			cout<<"dinh "<<ajc[v][j]<<" da to mau";
		}
		cout<<"da kt mau dinh ke "<<ajc[v][j]<<", ";
		//buggg vong lap vo tan
	}

	set<int>::iterator it;
	int tempMin=*colorOfAjc.begin();
	cout<<"temp min : " << tempMin;
	for (it=colorOfAjc.begin(); it != colorOfAjc.end(); it++){
		if(colorOfAjc.size() == 1){
			if(tempMin>0)	min=0;
			else min=tempMin+1; 
			cout<<"it: "<<*it<<" ";
			break;	
		}
		if((++it != colorOfAjc.end()) && *it+1 < *(++it)){
			min=*(--it)+1;
			cout<<"it: "<<*it<<", it+1: "<<*(++it)<<" ";
		}
		if((++it == colorOfAjc.end())&& min==0){
			it--;
			if(tempMin>0)	min=0;
			else min=*it+1; 
			cout<<"it: "<<*it<<" ";
			break;
		}
		//bug overflow?
	}
	cout<<"min: " << min<<" ";
	return min;
}

void colorGraph(){
	int i;
	setOrder();
	
	colorOfVtx.resize(numVtx);
	colorOfVtx[v[0]]=0;
	daToMau[v[0]]=true;

	//TODO: pointer in array??
	for(i=1; i<numVtx; i++){
		cout<<"xet dinh "<<v[i]<<" ";
		colorOfVtx[v[i]]=minColorAvailable(v[i]);
		daToMau[v[i]]=true;
		cout<<"color vertex "<<v[i]<<'\n';
		//debug: 2 lan minColorAvailable, 1 lan colorGraph
		//loop 1: color vertex 2?? --> lap vo han o xet dinh 3
		//lap vo han do loi bien toan cuc
	}
}

int main(){
	int i;
	// ifstream myfile;
    // myfile.open("dt.txt");
	// myfile>>numVtx>>edgeCnt;
	cin>>numVtx>>edgeCnt;
	int deg[numVtx];
	vector<vector<int> > hasDeg(numVtx);
	ajc.resize(numVtx);
//	cout<<ajc.size();	//numVtx,edgeCnt

	//lay danh sach canh
	for(i=0;i<edgeCnt; i++){
		int x,y;
		// myfile>>x>>y;
		cin>>x>>y;
		ajc[x].push_back(y);
		ajc[y].push_back(x);
    }
	// myfile.close();
	
	//	 lay danh sach bac cac dinh, luu vao mang dem
	for(i=0;i<numVtx;i++){
		deg[i] = ajc[i].size();
		hasDeg[deg[i]].push_back(i);
		cout<<i<<" has degree: "<<deg[i]<<" "<<endl;
	}

	colorGraph();
	for(i=0;i<numVtx;i++){
		cout<<i<<" color: "<<colorArr[colorOfVtx[i]]<<'\n';
	}

    return 0;
}
