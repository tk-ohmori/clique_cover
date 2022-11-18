#include <bits/stdc++.h>

using namespace std;

vector<string> split(const string &s, char delim){
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

void deleteNl2(string &targetStr){
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