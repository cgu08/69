#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <iomanip>

#include "trie.hpp"

using std::string;
using std::vector;
using namespace std;

// Test program
int main()
{
    std::vector<std::string> lines;
    std::vector<int> weights;
    std::string line;
    std::string word_to_search;
    std::vector<string> split_str;
    
    Trie* trie = new Trie();
    int line_cnt = 0;

    do {
	getline(std::cin, line);
    	lines.push_back(line);
	trie->addSentence(line);
	line_cnt++;
    } while (!line.empty());

    getline(std::cin, word_to_search);

    cout << endl;

    vector<string> new_line_split_str;
    for (int i = 0; i < line_cnt - 1; i++) {
	new_line_split_str = parse_line(lines[i], " ");
    	weights.push_back(atoi(new_line_split_str[0].c_str()));	
    }

    selectionSort(weights);

    outputTrieTreeSortByWeight(trie, weights, lines, word_to_search);
    delete trie;
    return 0;
}
