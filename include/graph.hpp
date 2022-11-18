#pragma once

class Graph{
    public:
        set<int> nodes;
        map<int, set<int> > neighbor;

        Graph(){}

        void add_node(int v);
        void add_edge(int u, int v);
        int degree(int v);
        int edge_size();
        void infomation();
        void info();
        static Graph fromCol(string file_name);
};
