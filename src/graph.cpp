#include <bits/stdc++.h>

using namespace std;

#include <for_str.hpp>
#include <graph.hpp>

set<int> nodes;
map<int, set<int> > neighbor;

void Graph::add_node(int v){ nodes.insert(v); }
void Graph::add_edge(int u, int v){
    add_node(u);
    add_node(v);
    if(neighbor.find(u) != neighbor.end()) neighbor[u].insert(v);
    else neighbor[u] = {v};
    if(neighbor.find(v) != neighbor.end()) neighbor[v].insert(u);
    else neighbor[v] = {u};
}

int Graph::degree(int v){ return neighbor[v].size();}

int Graph::edge_size(){
    int res = 0;
    for(auto itr1 = neighbor.begin(); itr1 != neighbor.end(); ++itr1){
        int u = itr1->first;
        set<int> nu = itr1->second;
        for(auto itr2 = nu.begin(); itr2 != nu.end(); ++itr2){
            int v = *itr2;
            if(u<=v) ++res; // count self loop
            // if(u<v) ++res; // not count self loop
        }
    }
    return res;
}

void Graph::infomation(){
    cout<<"--graph info--"<<endl;
    for(auto itr1 = nodes.begin(); itr1 != nodes.end(); ++itr1){
        int v = *itr1;
        cout<<"  "<<v<<" --> { ";
        for(auto itr2 = neighbor[v].begin(); itr2 != neighbor[v].end(); ++itr2) cout<<*itr2<<" ";
        cout<<"}"<<endl;
    }
}

void Graph::info(){
    cout<<"node : "<<nodes.size()<<endl;
    cout<<"edge : "<<edge_size()<<endl;
}

Graph Graph::fromCol(string file_name){
    ifstream ifs(file_name);
    string str;
    smatch results;

    if(ifs.fail()){
        cerr<<"Failed to open file."<<endl;
        exit(-1);
    }
    
    Graph g;
    while(getline(ifs,str)){
        if(str[0]=='e'){
            deleteNl2(str);
            vector<string> line = split(str,' ');
            int x = stoi(line[1]);
            int y = stoi(line[2]);
            // g.add_edge(x, y);
            if(x!=y) g.add_edge(x, y);
        }
    }

    return g;
}
