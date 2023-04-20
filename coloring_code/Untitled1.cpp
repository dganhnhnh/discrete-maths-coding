#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#pragma GCC diagnostic ignored "-Wwrite-strings"
using namespace std;


bool  inputdata(char *filename, vector<vector<int> > &vect, int &n, int &m)
{
 
    ifstream myfile;
    myfile.open(filename);
    if (myfile.fail()){
        return false;
    }
    
    myfile >> n >> m; 
    vect.resize(n+1); 
    int temp1, temp2;
    for (int i=0; i<m; i++){
        myfile >> temp1 >> temp2;
        vect[temp1].push_back(temp2); 
        vect[temp2].push_back(temp1); 
    }
    myfile.close();
    return true;
}


int tomau(vector<vector<int> > &vect, int top, int mau[], int n)
{
    int v;
    int i;
    int dem = 0;
    for (i=1; i<=n; i++){ 
        for (v=1; v<=n; v++) {
			vect[top];
            if (i == mau[v]) dem = dem +1;
        }
        if (dem == 0) break;
        dem=0;
    }
    return i;
}


void tomauALL(vector<vector<int> > vect, int n, int mau[])
{
    for (int i=1; i<=n; i++){
        mau[i] = tomau(vect,i,mau,n);
    }
    return;
}


void printdothitomaudot(char *filename, int mau[],string color[], int n, int m)
{
    ofstream fileoutput;
    fileoutput.open(filename);
    fileoutput << "graph dothi" << endl;
    fileoutput << "{" << endl;
    for (int i=1; i<=n; i++){
        fileoutput << " ";
        fileoutput << i << " ";
        fileoutput << "[fillcolor=" << color[mau[i]] << ", style=filled];" << endl;
    }

    ifstream fileinput;
    fileinput.open("dothi.txt");
    int temp1, temp2;
    fileinput >> temp1 >> temp2;
    for (int i=0; i<m; i++){
        fileinput >> temp1 >> temp2;
        fileoutput << " ";
        fileoutput << temp1 << " -- " << temp2;
        fileoutput << endl;
    }
    fileoutput << "}";
    return;
}
int main()
{
    int n, m; 
   
    vector<vector<int> > dscanh;
    if (!inputdata("dothi.txt",dscanh,n,m)){
        cout << "FILE FAIL !!!" << endl;
        return -1;
    }
    int mau[n]; 
   

    
    string color[39] = { "snow","red","green","blue","SlateBlue2","yellow","purple","gray","lawn green","YellowGreen","cyan","hot pink",
		"orange","snow1","khaki","SlateGray3","wheat","purple","pink1","VioletRed1","DarkCyan","black","LightGreen","DarkMagenta","DarkRed",
		"DarkCyan","DarkBlue","DarkGray","grey100","grey99","grey98","grey97","grey96","grey95","grey94","grey93","grey92","grey91","grey90"};
 

    for (int i=0; i<n; i++) mau[i] = 0; 
    tomauALL(dscanh,n,mau);
   
   printdothitomaudot("dothi.dot",mau,color,n,m);
    return 0;
}
