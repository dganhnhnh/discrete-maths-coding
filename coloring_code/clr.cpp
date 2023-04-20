#include <iostream>
#include <vector>	
#include <set>
#include<fstream>
using namespace std;

int numVtx,edgeCnt;
vector<vector<int> > ajc;
vector<vector<int> > hasDeg;

vector<bool> daToMau;

string colorArr[39] = { "snow","red","green","cyan","YellowGreen","blue","SlateBlue2","lawn green","hot pink","yellow","purple","gray",
		"orange","snow1","khaki","SlateGray3","wheat","purple","pink1","VioletRed1","DarkCyan","black","LightGreen","DarkMagenta","DarkRed",
		"DarkCyan","DarkBlue","DarkGray","grey100","grey99","grey98","grey97","grey96","grey95","grey94","grey93","grey92","grey91","grey90"};

void setOrder(vector <int> v){
	int i,j;
	// TODO: thuat toan hoan vi
	for(i =numVtx-2; i>0;i--){
		if(hasDeg[i].size() >0){
			for(j=0; j<hasDeg[i].size(); j++){
				v.push_back(hasDeg[i][j]);
			}
		}
	}
}

bool chinhQuy(){
	// if hasDegree[i] == numVtx
	int i;
	for(i=1; i<hasDeg.size();i++ ){
		if (hasDeg[i].size() == numVtx) return 1;
	}
	return 0;
}

int minColorAvailable(int v,vector <int> colorOfVtx){
	int sz=ajc[v].size();
	int min=0;
	set<int> colorOfAjc;
	//TODO: test size of colorOfAjc vs size of ajc
	int j;
	for (j=0; j<sz; j++){
		if(daToMau[ajc[v][j]]==true){
			colorOfAjc.insert(colorOfVtx[ajc[v][j]]);
			// cout<<"dinh "<<ajc[v][j]<<" da to mau ";
		}
	}

	set<int>::iterator it;
	int tempMin=*colorOfAjc.begin();
	// cout<<"temp min : " << tempMin;
	for (it=colorOfAjc.begin(); it != colorOfAjc.end(); it++){
		if(colorOfAjc.size() == 1){
			if(tempMin>0)	min=0;
			else min=tempMin+1; 
			break;	
		}
		if((++it != colorOfAjc.end()) ){    
            it--;
            // cout<<"it: "<<*it<<'\n';
            if(*it+1 < *(++it)){
				it--; min=*it+1;
                break;
            }
		}
		if((++it == colorOfAjc.end())&& min==0){
			it--;
			if(tempMin>0)	min=0;
			else min=*it+1;
			break;
		}
		it--; it--;
	}
	return min;
}

void colorGraph(int numColor,vector <int> v,vector <int> colorOfVtx){
	int i;
	daToMau.resize(numVtx, false);
	// colorOfVtx.resize(numVtx);
	colorOfVtx[v[0]]=0;
	daToMau[v[0]]=true;

	for(i=1; i<numVtx; i++){
		cout<<"xet dinh "<<v[i]<<" "<<'\n';
		colorOfVtx[v[i]]=minColorAvailable(v[i],colorOfVtx);
		daToMau[v[i]]=true;
		//xet su thoa man so mau
		if(colorOfVtx[v[i]]+1> numColor) numColor=colorOfVtx[v[i]]+1;
	}
	//nhap tham so numColor vao ham nay de cap nhat gia tri
}

bool thoaManSoMau(int numColor, int maxDeg){
	//lay so bac cao nhat, so sanh voi so mau
	if (chinhQuy()) {
		// cout<<"chinh quy\n";
		maxDeg = maxDeg+1;
	}
	// else cout<<"k chinh quy\n";
	if(numColor > maxDeg) return 0;
	else return 1;
}

int main(){
	int i;
	ifstream myfile;
    myfile.open("dothi.txt");
	myfile>>numVtx>>edgeCnt;
	int deg[numVtx];
	hasDeg.resize(numVtx-1);
	ajc.resize(numVtx);

	ofstream outputFile;
	outputFile.open("dothitomau.dot");

	outputFile<<"graph dothi\n{\n";
	//lay danh sach canh
	for(i=0;i<edgeCnt; i++){
		int x,y;
		myfile>>x>>y;
		ajc[x].push_back(y);
		ajc[y].push_back(x);
		outputFile<<'\t'<<x<<" -- "<<y<<"; \n";
    }
	myfile.close();
	
	//	 lay danh sach bac cac dinh, luu vao mang dem
	int maxDeg=0;
	for(i=0;i<numVtx;i++){
		deg[i] = ajc[i].size();
		hasDeg[deg[i]].push_back(i);
		if(maxDeg<deg[i]) maxDeg=deg[i];
		// cout<<i<<" has degree: "<<deg[i]<<" "<<endl;
	}

	int t;
	for (t=0; t<10; t++){
		vector <int> v;
		vector <int> colorOfVtx(numVtx);

		int numColor=0;
		setOrder(v);
		colorGraph(numColor,v,colorOfVtx);
		// cout<<"lan thu "<<t+1<<'\n';
		if(thoaManSoMau(numColor,maxDeg)){
			// cout<<"thoa man so mau";
			for(i=0;i<numVtx;i++){
				outputFile<<'\t'<<i<<"[fillcolor="<<colorArr[colorOfVtx[i]]<<", style=filled];\n";
			}
			break;
		}
	}

	outputFile<<"}";
	outputFile.close();
	// cout<<maxDeg;

    return 0;
}
