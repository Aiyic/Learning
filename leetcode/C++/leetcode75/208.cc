
#include<bits/stdc++.h>
using namespace std;

class Trie {
public:
    Trie(): isStrEnd(false){

    }
    
    void insert(string word) {
        char ch = word[0];
        if(word.size()>0) {
            if(!children[ch-'a']){
                children[ch-'a'] = new Trie();
            }
            children[ch-'a']->insert(string(word,1));
        }
        else {
            isStrEnd=true;
        }
    }
    
    bool search(string word) {
        char ch = word[0];
        if(word.size()>0) {
            if(children[ch-'a']){
                return children[ch-'a']->search(string(word,1));
            }
            else return false;
        }
        else {
            return isStrEnd;
        }
    }
    
    bool startsWith(string prefix) {
        char ch = prefix[0];
        if(prefix.size()>0) {
            if(children[ch-'a']){
                return children[ch-'a']->startsWith(string(prefix,1));
            }
            else return false;
        }
        else {
            return true;
        }
    }

private:
    Trie* children[26]={nullptr};
    bool isStrEnd;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int main() {
    Trie root;
    root.insert("apple");
    cout << root.search("apple") << ' ';
    cout << root.search("app") << ' ';
    cout << root.startsWith("app") << ' ';
    root.insert("app");
    cout << root.search("app") << ' ';
    cout << 1;
    return 0;
}
