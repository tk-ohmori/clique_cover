#include <graph.hpp>

vector< vector<int> > clique_cover(Graph graph, int repetition);
vector< vector<int> > clique_cover(Graph graph, int repetition, int seed);
vector< vector< vector<int> > > multi_clique_cover(Graph graph, int repetition, int seed, int cc_num);

vector< pair<int,int> > random_sort(vector< pair<int,int> > degree, vector< pair<int,int> > ranges, int seed);

vector< vector<int> > greedy(Graph graph, int repetition, int seed);
vector< vector<int> > same_degree_random(Graph graph, int repetition, int seed);
vector< vector<int> > first_random(Graph graph, int repetition, int seed);
vector< vector<int> > first_ascending(Graph graph, int repetition, int seed);

void output_to_file(vector< vector<int> > clique_cover, string file_name);
void output_to_std(vector< vector<int> > clique_cover);
