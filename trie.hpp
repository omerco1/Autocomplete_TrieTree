#ifndef trie_hpp
#define trie_hpp

#include <map>
#include <stdio.h>
#include <string>


using namespace std;


class Trie {
    
public:
    struct node{
        int weight;
        string word;
        map<string, node*> ref;
    };
    Trie();
    ~Trie();
    node* getRoot();
    node* getCurr();
    node* getMax();
    void setCurr(node* temp);
    void setMax(node* max);
    
    bool find_node(string key);
    void build_trie_node(string key);
    void search_node(string key);
    
private:
    node* root;
    node* curr;
    node* max;
};
#endif /* trie_hpp */
