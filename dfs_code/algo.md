Tính liên thông trong đồ thị vô hướng

    procedure dfs(G)
        cc = 0
        for all v 2 V: visited(v) = false
        for all v 2 V:
            if not visited(v):
            cc = cc + 1
            explore(G; v)

    procedure explore(G; v)
        visited(v) = true
        previsit(v)
        for each edge (v; u) thuoc E:
            if not visited(u): explore(G; u)
        postvisit(v)

    procedure previsit(v)
        ccnum[v] = cc


directed
    // for(int i=0; i<5;i++){
    //     if (w1.find(b[i]) != w1.end()){
    //         count++;
    //     }
    // }


debug
    // for (int i=0; i<word_list.size(); i++){
    //     cout<<i<<": ";
    //     for(int j=0; j<dinhKe[i].size();j++){
    //         cout<<dinhKe[i][j]<<" "; 
    //     }
    //     cout<<endl;
    // }