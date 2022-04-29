#include<bits/stdc++.h>
#include <unistd.h>
using namespace std;

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
    if (!item.empty()) {
            elems.push_back(item);
        }
    }
    return elems;
}

void deleteNl2(string &targetStr)
{
	const char CR = '\r';
	const char LF = '\n';
	string destStr;
	for (const auto c : targetStr) {
		if (c != CR && c != LF) {
			destStr += c;
		}
	}
	targetStr = move(destStr);
}

vector< pair<int,int> > random_sort(vector< pair<int,int> > degree, vector< pair<int,int> > ranges, int seed){
    mt19937_64 get_rand_mt(seed);
    for(pair<int,int> p: ranges){
        shuffle(degree.begin() + p.first, degree.begin() + p.second + 1, get_rand_mt);
    }
    return degree;
}

vector< vector<int> > get_clique(int repetition, string file_name){
    int v=-1;
    ifstream ifs(file_name);
    string str;
    smatch results;

    if(ifs.fail()){
        cerr<<"Failed to open file."<<endl;
        exit(-1);
    }

    while(getline(ifs,str)){
        if(str[0]=='p') {
            deleteNl2(str);
            regex_match(str,results,regex("p\\s+?(edges?\\s+?)?(\\d+)\\s+?\\d+.*"));
            v = stoi(results[2].str());
            break;
        }
    }

    if(v<0){
        cerr<<"Failed to read graph info."<<endl;
        exit(-1);
    }

    vector< set<int> > graph(v);
    vector< pair<int,int> > degree(v,make_pair(0,0));
    for(int i=0;i<v;++i) degree[i].second=i;

    while(getline(ifs,str)){
        if(str[0]=='e'){
            deleteNl2(str);
            vector<string> line = split(str,' ');
            int x = stoi(line[1])-1;
            int y = stoi(line[2])-1;
            graph[x].insert(y);
            graph[y].insert(x);
            --degree[x].first;
            --degree[y].first;
        }
    }
    sort(degree.begin(),degree.end());

    vector< pair<int,int> > ranges;
    int d_head = 0;
    int d_value = degree[0].first;
    for(int i=0;i<v-1;++i){
        if(d_value!=degree[i+1].first){
            if(d_head!=i) ranges.push_back(make_pair(d_head,i));
            d_head = i+1;
            d_value = degree[d_head].first;
        }
    }
    if(d_head!=v-1) ranges.push_back(make_pair(d_head,v-1));

    vector< vector<int> > result(v);
    for(int rep=0;rep<repetition;++rep){
        if(rep>0) degree = random_sort(degree, ranges, rep);
        vector<bool> used(v,false);
        vector< vector<int> > clique_cover;
        for(int i=0;i<v;++i){
            if(used[degree[i].second]) continue;
            vector<int> clique;
            set<int> candidate = graph[degree[i].second];
            clique.push_back(degree[i].second);
            used[degree[i].second] = true;
            for(int j=i+1;j<v;++j){
                int vtx = degree[j].second;
                if(!used[vtx] && candidate.find(vtx)!=candidate.end()){
                    set<int> bufset;
                    set_intersection(candidate.begin(),candidate.end(),graph[vtx].begin(),graph[vtx].end(),inserter(bufset,bufset.end()));
                    candidate = bufset;
                    clique.push_back(vtx);
                    used[vtx] = true;
                    if(candidate.empty()) break;
                }
            }
            clique_cover.push_back(clique);
        }
        if(clique_cover.size()<result.size()) result = clique_cover;
    }
    return result;
}

void output_to_std(vector< vector<int> > clique_cover){
    for(int i=0;i<clique_cover.size();++i){
        for(int j=0;j<clique_cover[i].size()-1;++j){
            cout<<clique_cover[i][j]<<',';
        }
        cout<<clique_cover[i].back()<<endl;
    }
}

void output_to_file(vector< vector<int> > clique_cover,string file_name){
    ofstream file(file_name);
    for(int i=0;i<clique_cover.size();++i){
        for(int j=0;j<clique_cover[i].size()-1;++j){
            file<<clique_cover[i][j]+1<<',';
        }
        file<<clique_cover[i].back()+1<<endl;
    }
    file.close();
}

int main(int argc,char *argv[]){
    int rep = 1;
    string output_file;
    string col_file;
    int opt;
    while((opt = getopt(argc, argv,"r:o:")) != -1){
        switch(opt){
            case 'r':
                rep = stoi(optarg);
                break;
            case 'o':
                output_file = optarg;
                break;
            default:
                cout<<"Option error"<<endl;
                exit(-1);
        }
    }
    if(optind != argc-1){
        cout<<"No col file."<<endl;
        exit(-1);
    }else col_file = argv[optind];

    vector< vector<int> > clique_cover = get_clique(rep, col_file);
    if(output_file.empty()) output_to_std(clique_cover);
    else output_to_file(clique_cover, output_file);
    return 0;
}
