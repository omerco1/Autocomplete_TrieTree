#include <iostream>
#include "trie.hpp"
#include <map>
#include <string>

using namespace std;

Trie::Trie() {
    root = new node;
    //root->word = "root";
    curr = root;
    max = NULL; 
}

Trie::~Trie(){}

Trie::node* Trie::getCurr() {
    return this->curr;
}

void Trie::setCurr(node* temp) {
    this->curr = temp;
}
Trie::node* Trie::getRoot() {
    return this->root;
}

Trie::node* Trie::getMax() {
    return this->max;
}

void Trie::setMax(node* new_max) {
    this->max = new_max;
}

void Trie::search_node(string key) {
    //check if your starting word exists
    if (curr->ref.find(key) != curr->ref.end()){
        //points the cursor pointer to the next node
        setCurr(curr->ref[key]);
    }
    else
        build_trie_node(key);
}

void Trie::build_trie_node(string key) {
    node* new_node = new node;
    new_node->word = key;
    new_node->weight = -1; //*****STUB********
    curr->ref[key] = new_node;
    //c = c->ref[key];
    if (curr != root) {
        if (max == NULL || max->ref.size() < curr->ref.size()) {
            setMax(curr);
        }
    }
    setCurr(new_node); // point c to that new node
    return;
}

bool Trie::find_node(string key) {
    if (curr->ref.find(key) != curr->ref.end()){
        setCurr(curr->ref[key]);
        return true;
    }
    return false;
}


