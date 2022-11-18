#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

#include <clique_cover.hpp>
// #include <graph.hpp>

void usage(){
    cout<<"Usage: ./clique_cover [options] col_file"<<endl;
    cout<<"Find clique cover from .col format file with greedy algorithm."<<endl;
    cout<<"\t-h\t: show help"<<endl;
    cout<<"\t-r\t: specify repitition number (default: 1)"<<endl;
    cout<<"\t-o\t: output file name"<<endl;
    cout<<"\t-s\t: seed value"<<endl;
}

int main(int argc,char *argv[]){
    int rep = 1;
    string output_file;
    string col_file;
    int opt;
    int seed;
    bool is_set_seed = false;
    while((opt = getopt(argc, argv,"r:o:s:h")) != -1){
        switch(opt){
            case 'r':
                rep = stoi(optarg);
                break;
            case 'o':
                output_file = optarg;
                break;
            case 's':
                seed = stoi(optarg);
                is_set_seed = true;
                break;
            case 'h':
                usage();
                exit(0);
            default:
                cout<<"Option error"<<endl;
                usage();
                exit(-1);
        }
    }
    if(optind != argc-1){
        cout<<"No col file."<<endl;
        usage();
        exit(-1);
    }else col_file = argv[optind];

    Graph graph = Graph::fromCol(col_file);
    vector< vector<int> > cc;
    if(is_set_seed) cc = clique_cover(graph, rep, seed);
    else cc = clique_cover(graph, rep);

    if(output_file.empty()) output_to_std(cc);
    else output_to_file(cc, output_file);
    return 0;
}
