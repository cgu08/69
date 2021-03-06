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

static int max_level = 0;
static string max_str = "";

Node::Node()
{    
    mContent = "";
    mMarker = false;
    numOfChildren = 0;
    weight = 0;
    mLevel = 0;
}

Node* Node::findChild(string str)
{
    for ( size_t i = 0; i < mChildren.size(); i++ )
    {
        Node* tmp = mChildren.at(i);
        if ( tmp->content() == str)
        {
            return tmp;
        }
    }

    return NULL;
}

Trie::Trie()
{
    root = new Node();
}

Trie::~Trie()
{
    delete root;
}

vector<string> parse_line(const string& target, const string& delimiter)
{
    vector<string> result;
    string::const_iterator substart = target.begin(), subend;

    while (true) {
        subend = search(substart, target.end(), delimiter.begin(), delimiter.end());
        string temp(substart, subend);
        if (!temp.empty()) {
	    result.push_back(temp);
        }
	if (subend == target.end()) {
	    break;
        }
	substart = subend + delimiter.size();
    }
    return result;
}

void Trie::addSentence(string s)
{
    vector<string> split_str = parse_line(s, " ");
    size_t size = split_str.size();

    Node* current = root;

    if ( size == 0 )
    {
        current->setMarker(); 
        return;
    }

    for ( size_t i = 1; i < size; i++ )
    {        
        Node* child = current->findChild(split_str[i]);
        if ( child != NULL )
        {
            current = child;
        }
        else
        {
            Node* tmp = new Node();
            tmp->setContent(split_str[i]);
   	    tmp->setLevel(i);
            current->appendChild(tmp);
            current->incrNumOfChildren();
            if (current->getNumOfChildren() > max_level) {
		max_level = current->getNumOfChildren();
		max_str = current->content();
 	    }
            current = tmp;
        }
        if ( i == size - 1 ) {
            current->setMarker();
	    current->setWeight(atoi(split_str[0].c_str()));
	}
    }
}


int Trie::searchSentence(string s)
{
    size_t i;
    Node* current = root;

    vector<string> split_str = parse_line(s, " ");
    size_t size = split_str.size();

    for (i = 0; i < size; i++) {
        Node* tmp = current->findChild(split_str[i]);
        if ( tmp == NULL ) {
            return 0;
        } else {
	    current = tmp;
	}
    }

    if ( current->getMarker())
        return current->getWeight();
    else
        return 0;
}

void outputTrieTreeSortByWeight(Trie *trie, vector<int> weights, vector<string> lines, string word)
{
    size_t j, k, size_of_lines;
    vector<string> new_line_split_str;
    string new_line = "";
    string output_line = "";
    Node* child;
    bool notFound = false;
    int level;
    int w_size = weights.size();

    Node* current = trie->getRoot();
    if (current == NULL) {
    	cout << "No valid completion" << endl;
    } else {
	for (int i = w_size - 1; i >= 0; i--) {
	    current = trie->getRoot();
	    output_line = "";
	    child = current->findChild(word);
	    if (child != NULL) {
	    	level = child->getLevel();
	    } else {
	    	level = 0;
	    }
	    for (j = 0; j < lines.size(); j++) {
		new_line_split_str = parse_line(lines[j], " ");
		size_of_lines = new_line_split_str.size();
		if (atoi(new_line_split_str[0].c_str()) == weights[i])
		    break;
	    }
	    for (k = 1; k < size_of_lines; k++) {
		child = current->findChild(new_line_split_str[k]);
		if (child != NULL) {
		    current = child;
		    if (!current->getMarker()) {
			if (current->content() != word) {
			    if (current->getLevel() == level) {
			    	break;
			    } else if (current->getLevel() > level) {
				if (output_line == "") {
				    output_line = current->content();
				} else {
				    output_line = output_line + " " + current->content();
				}
			    }
			} 
		    } else if (current->getMarker()) {
			if (current->content() != word) {
			    if (output_line == "") {
				output_line = current->content();
			    } else {    
				output_line = output_line + " " + current->content();
			    }
			    cout << output_line << endl;
			    break;
			}
		    }
	 	} else {
		    notFound = true;
		    break;
		}
	    }
	}
	if (notFound == true) {
	    cout << "No valid completion" << endl;
	} else {
	    cout << max_str << " " << max_level << endl;
	    cout << endl;
	}
    }
}

void selectionSort(vector<int> & toSort)
{
    size_t pos, i, pos_min;
    int min;
    size_t size = toSort.size();
    for (pos = 0; pos < size; pos++) {
	min = toSort[pos];
	for (i = pos + 1; i < size; i++) {
	    if (toSort[i] < min) {
		min = toSort[i];
		pos_min = i;
	    }
	}
	if (min != toSort[pos]) {
	    std::swap(toSort.at(pos_min), toSort.at(pos));
	}
    }
}
