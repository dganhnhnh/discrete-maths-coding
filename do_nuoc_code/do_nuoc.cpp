#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

int max1= 10, max2=7, max3= 4;
stack<int> dinhCanXet;  // stack chua rowIndex
int vertices[100][3]; int rowIndex =1;
int nextId = rowIndex;
int v1[] = {0,7,4};

ofstream outputFile;

int maxCap(int id){
    switch (id){
        case 0: return max1;
        case 1: return max2;
        case 2: return max3;
        default: return 0;
    }
}

bool checkTrungNhau(int v1[], int v2[]){
    // cout<< v1[0]  <<" " << v1[1] <<" "<<v1[2]<<" " << v2[0]<<" "<< v2[1]<<" " << v2[2]<<"\n";
    if(v1[0] == v2[0] && v1[1] == v2[1] &&v1[2] == v2[2]){
        return true;
    }
    else return false;
}

//working
void doNuoc(int v[],int idA, int idB){
    // da qua kiem tra dieu kien de do nuoc tu a sang b
    int vNew[] = {v[0], v[1], v[2]};
    int sum = vNew[idA] +vNew[idB];
    bool trungLap=false;

    int tmp = maxCap(idB);
    if(sum<tmp){
        vNew[idB] = sum;
        vNew[idA] =0;
    }else if(sum>=tmp){
        vNew[idB] = tmp;
        vNew[idA] =sum-tmp;
    }
    for(int i=0; i<rowIndex; i++){
        if(checkTrungNhau(vertices[i], vNew) == true) {
            trungLap=true; break;
        }
    }
    
    //do nuoc thanh cong
    if(trungLap==false)
    {    for(int i=0; i<3; i++){
            vertices[rowIndex][i] = vNew[i];
        }
        rowIndex++;
        
        outputFile<<"\t"<<'"'<<v[0]<<","<<v[1]<<","<<v[2]<<'"'<<" -- "<< '"'<<vNew[0]<<","<<vNew[1]<<","<<vNew[2]<<'"'<<"; \n";
    }
}

void truongHopDoNuoc(int v[]){
    nextId = rowIndex;

    doNuoc(v,0,1);
    doNuoc(v,0,2);
    doNuoc(v,1,0);
    doNuoc(v,2,0);
    doNuoc(v,1,2);
    doNuoc(v,2,1);

    int pushFrom = nextId+1;
    int pushUntil = rowIndex;

    // luu lai cac node vao stack
    for (int k = pushFrom; k<pushUntil; k++){
        dinhCanXet.push(k);
    }
}

int main(){

	outputFile.open("graph.dot");
    outputFile<<"graph dothi\n{\n";
 
    vertices[0][0]=0;     vertices[0][1]=7; vertices[0][2]=4; 

    dinhCanXet.push(1);

    truongHopDoNuoc(vertices[rowIndex-1]);

    // chay den khi rowIndex khong tang nua, thi quay lai stack roi pop de xet tiep
    while (!dinhCanXet.empty() || rowIndex> nextId) {
        if(rowIndex> nextId) {
            truongHopDoNuoc(vertices[nextId]);
            cout << vertices[nextId][0]<<" "<< vertices[nextId][1]<<" "<< vertices[nextId][2]<<" ";
        }
        else {
            truongHopDoNuoc(vertices[dinhCanXet.top()]);
            cout << vertices[dinhCanXet.top()][0]<<" "<< vertices[dinhCanXet.top()][1]<<" "<< vertices[dinhCanXet.top()][2]<<" ";
            dinhCanXet.pop();
        }
        // cout<<dinhCanXet.top();
        cout<<"stack size: "<<dinhCanXet.size()<<"\n";
    }

    for(int i=0; i<rowIndex; i++){
        for (int j=0; j<3; j++)
            {   
                cout<<vertices[i][j]<<" ";}
        cout<<"\n";
    }
    
    outputFile<<"}";
    outputFile.close();

    return 0;
}