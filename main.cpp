#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <cctype>
#include <iomanip>
#include "trie.hpp"

using namespace std;

void traverse_tree_print(Trie::node* p);

void print_final(map<int, string> m); 

void traverse_trie(Trie::node* p, string value, map<int, string> &m);

vector<string> parser(string input);

int main(int argc, const char * argv[]) {
    string word;
    
    ifstream fin;
    ofstream out;
    out.open("inputfile.txt");

    for(string line; getline(cin, line) && line.compare(""); ) {
      out << line <<endl;
      
    }
    // out << endl;
    string query;
    getline(cin, query);
    //out << query << endl;
    out.close(); 

      
    fin.open("inputfile.txt");
    
    // check for error
    if (fin.fail()) {
        cerr << "Error opening file" <<endl;
        exit(1);
    }
    Trie my_trie;
    bool first_word = true;
    int weight;
    
    while(true) {
        fin>>word;
        if (fin.eof())
            break;
    
        //******Using STOI need to modify make, see piazza
        if (first_word) {
            weight = stoi(word);
            first_word = false;
            continue;
        }
        
        my_trie.search_node(word);
        
        //im at the end of the line, need to set weight, reset bool
        if (fin.peek() == '\n' || fin.peek() == '\r') {
            Trie::node* p = my_trie.getCurr();
            p->weight = weight;
            my_trie.setCurr(my_trie.getRoot()); //set curr equal to root
            first_word = true;
        }
        
        
        
    }
    //test the structure
    //traverse_tree_print(my_trie.getRoot());
    my_trie.setCurr(my_trie.getRoot()); //reset currr just in case
    
    string input = query;
    //getline(cin, input);
    
    vector<string> in_words;
    in_words = parser(input);
    
    string value = "";
    bool found = true;
    //found = my_trie.find_node(input);
    
    
    for (int i = 0; i < in_words.size(); i++){
        found = my_trie.find_node(in_words[i]);
        if (found == false) break; 
    }

    if (found) {
        map<int, string> m;
        traverse_trie(my_trie.getCurr(), value, m);
        print_final(m);
        cout << my_trie.getMax()->word + " " << my_trie.getMax()->ref.size() << endl;
    }
    else if(found == false)
        cout << "No valid completion" << endl;
    
    return 0;
}

vector<string> parser(string input) {
    vector<string> o;
    string word = "";
    for (int i = 0; i < input.length(); i++) {
        if(input[i] == 32) {
            o.push_back(word);
            word = "";
        }
        else
            word = word + input[i];
    }
    o.push_back(word);
    return o;
}

void traverse_trie(Trie::node* p, string value, map<int, string> &m) {
    //base case
    if (p->ref.empty()) {
        //value = value + p->word;
        m[p->weight] = value;
        return;
    }
    else {
        for (map<string, Trie::node*>::iterator it =p->ref.begin(); it!=p->ref.end(); ++it){
//            value = value + it->first;
            traverse_trie(it->second, value  + it->first + " ", m);
        }
    }
}


void print_final(map<int, string> m) {
    for (map<int, string>::reverse_iterator it =m.rbegin(); it!=m.rend(); ++it){

        cout << it->second << " " << endl;
    }
}


void traverse_tree_print(Trie::node* p) {
    //base case
    if (p->ref.empty()) {
        cout << p->word << " ";
        cout << " " << p->weight << endl;
        return;
    }
    else {
        for (map<string, Trie::node*>::iterator it =p->ref.begin(); it!=p->ref.end(); ++it){
            cout << p->word << " ";
            traverse_tree_print(p->ref[it->first]);
        }
    }
}

