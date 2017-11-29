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

using std::string;
using std::vector;
using namespace std;

class Node {
public:
    Node();
    ~Node() {}
    string content() { return mContent; }
    void setContent(string str) { mContent.assign(str); }
    int getNumOfChildren() { return numOfChildren;}
    bool getMarker() {return mMarker;}
    void setMarker() { mMarker = true; }
    void setWeight(int w) { weight = w;}
    int getWeight() { return weight;}
    void setLevel(int level) { mLevel = level; }
    int getLevel() { return mLevel;  }
    void incrNumOfChildren() { numOfChildren++;}
    Node* findChild(string str);
    void appendChild(Node* child) { mChildren.push_back(child); }
    vector<Node*> children() { return mChildren; }

private:
    string mContent;
    bool mMarker;
    vector<Node*> mChildren;
    int numOfChildren;
    int weight;
    int mLevel;
};

class Trie {
public:
    Trie();
    ~Trie();
    Node* getRoot() { return root;}
    void addSentence(string s);
    int searchSentence(string s);
    void deleteSentence(string s);
private:
    Node* root;
};


vector<string> parse_line(const string& target, const string& delimiter);
void outputTrieTreeSortByWeight(Trie *trie, vector<int> weights, vector<string> lines, string word);
void selectionSort(vector<int> & toSort);
