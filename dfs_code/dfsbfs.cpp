#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> dinhKe;
vector<int> parent;
vector<string> word_list;
int soNode=1; int cc=0;
int fromV=-1,toV=-1;

bool canConnect(string a, string b){
    int count=0;
    for(int i=0; i<5;i++){
        if(b[i] != a[i]) count++;
    }
    if (count == 1) return true;
    return false;
}

void buildGraph(){
    for (int i=0; i<word_list.size(); i++){
        for(int j=0; j<word_list.size();j++){
            if(canConnect(word_list[i],word_list[j] )){
                dinhKe[i].push_back(j); 
                // cout<<word_list[i]<<" " <<word_list[j];
            }
        }
    }
}

void previsit(int ccnum[], int v){
    ccnum[v]=cc;
}

void explore(bool visited[],int ccnum[], int v){
    visited[v] = true;
    previsit(ccnum, v);
    for (int i=0; i<dinhKe[v].size(); i++){
        if(visited[dinhKe[v][i]] == false) {
            explore(visited, ccnum, dinhKe[v][i]);
        }
    }
}

void dfs(bool visited[],int ccnum[]){
    cc=0;
    for (int i=0; i<soNode; i++){
        visited[i] = false;
    }
    for (int i=0; i<soNode; i++){
        if (visited[i] == false){
            cc++;
            explore(visited, ccnum, i);
        }
    }
}

void showq(queue<int> gq)
{
    queue<int> g = gq;
    while (!g.empty()) {
        cout << '\t' << g.front();
        g.pop();
    }
    cout << '\n';
}

void bfs(int s, int e, int dist[], int ccnum[]){

    for (int i=0; i<soNode; i++){
        if(ccnum[i] == ccnum[s]){
            dist[i] = 100000;
        }
    }
    dist[s] = 0;
    queue<int> Q;
    Q.push(s);
    int nextV = -1;
    while(!Q.empty()){
        nextV = Q.front();
        Q.pop();
        for (int j=0; j<dinhKe[nextV].size(); j++){
            int dinh = dinhKe[nextV][j];
            
            if(dist[dinh] == 100000){
                Q.push(dinh);
                dist[dinh] = dist[nextV]+1;
            }
            if(dinh == e){
                break;
            }
        }
    }
    int distance = dist[e];
    int result[distance];
    result[0] = s;
    
    cout<<"\ndistance: "<<distance-1<<"\n";
    for(int i=distance-1; i>0; i--){
        // cout<< "_\n";
        for(int j=0; j<dinhKe[e].size(); j++){
            int id=dinhKe[e][j];
            if(dist[id] == i){
                result[i] = id;
                e=id;break;
            }
        }
    }
    for(int i=0; i<distance; i++){
        cout<< word_list[result[i]]<<" ";
    }
    
}

void wordSearch(string s, string e){
    for(int i=0; i< soNode; i++){
        if(s == word_list[i]){
            fromV = i;
            break;
        }
    }
    for(int i=0; i< soNode; i++){
        if(e == word_list[i]){
            toV = i;
            break;
        }
    }
}

int main(){

    ifstream myfile;
  	myfile.open ("words.txt");
    string word;
  	while (myfile >> word)
    {
        word_list.push_back(word);
    }
    soNode = word_list.size();
    dinhKe.resize(soNode);
    buildGraph();

    int ccnum[soNode];
    bool visited[soNode];
    int dist[soNode];

    dfs(visited, ccnum);
    cout<<"So thanh phan lien thong: "<< cc;
    string startW, endW;

    cout<< "\nInput start: ";
    cin>> startW;
    cout<< "Input end: ";
    cin>> endW;
    wordSearch(startW, endW);
    bfs(fromV,toV,dist,ccnum);

    return 0;
}