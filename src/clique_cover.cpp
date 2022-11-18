#include <bits/stdc++.h>

using namespace std;

#include <graph.hpp>
#include <clique_cover.hpp>

vector< vector<int> > clique_cover(Graph graph, int repetition){
    int seed = 0;
    return clique_cover(graph, repetition, seed);
}

vector< vector<int> > clique_cover(Graph graph, int repetition, int seed){
    return greedy(graph, repetition, seed);
    // return same_degree_random(graph, repetition, seed);
    // return first_random(graph, repetition, seed);
    // return first_ascending(graph, repetition, seed);
}

vector< vector< vector<int> > > multi_clique_cover(Graph graph, int repetition, int seed, int cc_num){
    vector< vector< vector<int> > > res;
    srand(seed);
    for(int i=0; i<cc_num; ++i) res.push_back(clique_cover(graph, repetition, rand()));
    return res;
}

vector< pair<int,int> > random_sort(vector< pair<int,int> > degree, vector< pair<int,int> > ranges, int seed){
    mt19937_64 get_rand_mt(seed);
    for(pair<int,int> p: ranges){
        shuffle(degree.begin() + p.first, degree.begin() + p.second + 1, get_rand_mt);
    }
    return degree;
}

vector< vector<int> > greedy(Graph graph, int repetition, int seed){
    vector< pair<int, int> > degree;
    for(auto itr = graph.nodes.begin(); itr != graph.nodes.end(); ++itr) degree.push_back(make_pair(-1*graph.neighbor[*itr].size(),*itr));

    sort(degree.begin(),degree.end());

    vector< pair<int,int> > ranges;
    int d_head = 0;
    int d_value = degree[0].first;
    for(int i=0;i<degree.size()-1;++i){
        if(d_value!=degree[i+1].first){
            if(d_head!=i) ranges.push_back(make_pair(d_head,i));
            d_head = i+1;
            d_value = degree[d_head].first;
        }
    }
    if(d_head!=degree.size()-1) ranges.push_back(make_pair(d_head,degree.size()-1));

    vector< vector<int> > result(graph.nodes.size());
    for(int rep=0; rep<repetition; ++rep){
        if(rep>0) degree = random_sort(degree, ranges, seed + rep);
        map<int, bool> used;
        for(auto itr = graph.nodes.begin(); itr != graph.nodes.end(); ++itr){
            int v = *itr;
            used[v] = false;
        }
        vector< vector<int> > cliques;
        for(int i=0; i<degree.size(); ++i){
            if(used[degree[i].second]) continue;
            vector<int> clique;
            set<int> candidate = graph.neighbor[degree[i].second];
            clique.push_back(degree[i].second);
            used[degree[i].second] = true;
            for(int j=i+1;j<degree.size();++j){
                int vtx = degree[j].second;
                if(!used[vtx] && candidate.find(vtx)!=candidate.end()){
                    set<int> bufset;
                    set_intersection(candidate.begin(), candidate.end(), graph.neighbor[vtx].begin(), graph.neighbor[vtx].end(), inserter(bufset,bufset.end()));
                    candidate = bufset;
                    clique.push_back(vtx);
                    used[vtx] = true;
                    if(candidate.empty()) break;
                }
            }
            cliques.push_back(clique);
        }
        if(cliques.size()<result.size()) result = cliques;
    }
    return result;
}

vector< vector<int> > same_degree_random(Graph graph, int repetition, int seed){
    vector< pair<int, int> > degree;
    for(auto itr = graph.nodes.begin(); itr != graph.nodes.end(); ++itr) degree.push_back(make_pair(-1*graph.neighbor[*itr].size(),*itr));

    sort(degree.begin(), degree.end());

    vector< pair<int,int> > ranges;
    int d_head = 0;
    int d_value = degree[0].first;
    for(int i=0;i<degree.size()-1;++i){
        if(d_value!=degree[i+1].first){
            if(d_head!=i) ranges.push_back(make_pair(d_head,i));
            d_head = i+1;
            d_value = degree[d_head].first;
        }
    }
    if(d_head!=degree.size()-1) ranges.push_back(make_pair(d_head,degree.size()-1));

    vector< vector<int> > result(graph.nodes.size());
    for(int rep=0;rep<repetition;++rep){
        degree = random_sort(degree, ranges, seed + rep);
        // set<int> used;
        map<int, bool> used;
        for(auto itr = graph.nodes.begin(); itr != graph.nodes.end(); ++itr){
            int v = *itr;
            used[v] = false;
        }
        vector< vector<int> > cliques;
        for(int i=0;i<degree.size();++i){
            // if(used.find(degree[i].second) != used.end()) continue;
            if(used[degree[i].second]) continue;
            vector<int> clique;
            set<int> candidate = graph.neighbor[degree[i].second];
            clique.push_back(degree[i].second);
            // used.insert(degree[i].second);
            used[degree[i].second] = true;
            for(int j=i+1;j<degree.size();++j){
                int vtx = degree[j].second;
                // if(used.find(vtx)==used.end() && candidate.find(vtx)!=candidate.end()){
                if(!used[vtx] && candidate.find(vtx)!=candidate.end()){
                    set<int> bufset;
                    set_intersection(candidate.begin(), candidate.end(), graph.neighbor[vtx].begin(), graph.neighbor[vtx].end(), inserter(bufset,bufset.end()));
                    candidate = bufset;
                    clique.push_back(vtx);
                    // used.insert(vtx);
                    used[vtx] = true;
                    if(candidate.empty()) break;
                }
            }
            cliques.push_back(clique);
        }
        if(cliques.size()<result.size()) result = cliques;
    }
    return result;
}

vector< vector<int> > first_random(Graph graph, int repetition, int seed){
    vector< pair<int, int> > degree;
    for(auto itr = graph.nodes.begin(); itr != graph.nodes.end(); ++itr) degree.push_back(make_pair(-1*graph.neighbor[*itr].size(),*itr));

    sort(degree.begin(),degree.end());

    vector< pair<int,int> > ranges;
    int d_head = 0;
    int d_value = degree[0].first;
    for(int i=0;i<degree.size()-1;++i){
        if(d_value!=degree[i+1].first){
            if(d_head!=i) ranges.push_back(make_pair(d_head,i));
            d_head = i+1;
            d_value = degree[d_head].first;
        }
    }
    if(d_head!=degree.size()-1) ranges.push_back(make_pair(d_head,degree.size()-1));

    srand(seed);

    vector< vector<int> > result(graph.nodes.size());
    for(int rep=0; rep<repetition; ++rep){
        // degree = random_sort(degree, ranges, rep);
        if(rep>0) degree = random_sort(degree, ranges, rep);
        // set<int> used;
        map<int, bool> used;
        for(auto itr = graph.nodes.begin(); itr != graph.nodes.end(); ++itr){
            int v = *itr;
            used[v] = false;
        }
        vector<int> accum(degree.size(), 0);
        int remain = degree.size();
        vector< vector<int> > cliques;
        while(remain>0){
            int v = rand()%remain;/////////////////////////////////////////////////////////
            if(used[v]) continue;
            vector<int> clique;
            set<int> candidate = graph.neighbor[v];
            clique.push_back(v);
            used[v] = true;
            for(int j=0; j<degree.size(); ++j){
                int vtx = degree[j].second;
                if(!used[vtx] && candidate.find(vtx)!=candidate.end()){
                    set<int> bufset;
                    set_intersection(candidate.begin(), candidate.end(), graph.neighbor[vtx].begin(), graph.neighbor[vtx].end(), inserter(bufset,bufset.end()));
                    candidate = bufset;
                    clique.push_back(vtx);
                    used[vtx] = true;
                    if(candidate.empty()) break;
                }
            }
            cliques.push_back(clique);
        }
        if(cliques.size()<result.size()) result = cliques;
    }
    return result;
}

vector< vector<int> > first_ascending(Graph graph, int repetition, int seed){
    vector< pair<int, int> > degree;
    for(auto itr = graph.nodes.begin(); itr != graph.nodes.end(); ++itr) degree.push_back(make_pair(-1*graph.neighbor[*itr].size(),*itr));

    sort(degree.begin(),degree.end());

    vector< pair<int,int> > ranges;
    int d_head = 0;
    int d_value = degree[0].first;
    for(int i=0;i<degree.size()-1;++i){
        if(d_value!=degree[i+1].first){
            if(d_head!=i) ranges.push_back(make_pair(d_head,i));
            d_head = i+1;
            d_value = degree[d_head].first;
        }
    }
    if(d_head!=degree.size()-1) ranges.push_back(make_pair(d_head,degree.size()-1));

    vector< vector<int> > result(graph.nodes.size());
    for(int rep=0; rep<repetition; ++rep){
        if(rep>0) degree = random_sort(degree, ranges, seed + rep);
        map<int, bool> used;
        for(auto itr = graph.nodes.begin(); itr != graph.nodes.end(); ++itr){
            int v = *itr;
            used[v] = false;
        }
        vector< vector<int> > cliques;
        for(int i=degree.size()-1; i>=0; --i){
            if(used[degree[i].second]) continue;
            vector<int> clique;
            set<int> candidate = graph.neighbor[degree[i].second];
            clique.push_back(degree[i].second);
            used[degree[i].second] = true;
            for(int j=0; j<degree.size(); ++j){
                int vtx = degree[j].second;
                if(!used[vtx] && candidate.find(vtx)!=candidate.end()){
                    set<int> bufset;
                    set_intersection(candidate.begin(), candidate.end(), graph.neighbor[vtx].begin(), graph.neighbor[vtx].end(), inserter(bufset,bufset.end()));
                    candidate = bufset;
                    clique.push_back(vtx);
                    used[vtx] = true;
                    if(candidate.empty()) break;
                }
            }
            cliques.push_back(clique);
        }
        if(cliques.size()<result.size()) result = cliques;
    }
    return result;
}

void output_to_file(vector< vector<int> > clique_cover, string file_name){
    ofstream file(file_name);
    for(int i=0;i<clique_cover.size();++i){
        for(int j=0;j<clique_cover[i].size()-1;++j){
            file<<clique_cover[i][j]+1<<',';
        }
        file<<clique_cover[i].back()+1<<endl;
    }
    file.close();
}

void output_to_std(vector< vector<int> > clique_cover){
    for(int i=0;i<clique_cover.size();++i){
        for(int j=0;j<clique_cover[i].size()-1;++j){
            cout<<clique_cover[i][j]<<',';
        }
        cout<<clique_cover[i].back()<<endl;
    }
}
