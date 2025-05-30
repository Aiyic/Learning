
#include<bits/stdc++.h>
using namespace std;

#if 0 // my
class Trie{
public:
    void insert(string word){
        char ch = word[0];
        if(word.size()>0) {
            if(!children[ch]){
                children[ch] = make_shared<Trie>(Trie()) ;
            }
            children[ch]->insert(string(word,1));
        }
        else {
            isStrEnd=true;
        }
    }

    Trie* startsWith(string prefix) {
        char ch = prefix[0];
        if(prefix.size()>0) {
            if(children[ch]){
                return children[ch]->startsWith(string(prefix,1));
            }
            else return nullptr;
        }
        else {
            return this;
        }
    }

    static void allstring(set<string>* res, string prefix, shared_ptr<Trie> node){
        if(node->isStrEnd) res->insert(prefix);
        for(auto& [i,j] : node->children){
            allstring(res, prefix + i, j);
        }
    }

    // ~Trie(){
    //     for(auto& [i,j] : children){
    //         j->~Trie();
    //     }
    //     // cout << "del" << endl;
    // }
private:
    // Trie* children[26]={nullptr};
    map<char, shared_ptr<Trie>> children;
    bool isStrEnd=false;
};

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        Trie root;
        for(string & x : products){
            root.insert(x);
        }
        vector<vector<string>> results;
        set<string> res;
        for(int i=1; i<=searchWord.length(); ++i){
            string prefix(searchWord,0,i);
            auto s = root.startsWith(prefix);
            if(s){
                res.clear();
                Trie::allstring(&res, prefix, make_shared<Trie>(*s));
                if(res.size()<=3)
                    results.emplace_back(res.begin(),res.end());
                else{
                    auto itend = res.begin();
                    ++itend;++itend;++itend;
                    results.emplace_back(res.begin(),itend);
                }
            }
            else results.emplace_back(vector<string>());
        }
        return results;
    }
};


#else // offical

struct Trie {
    unordered_map<char, Trie*> child;
    priority_queue<string> words;
};

class Solution {
private:
    void addWord(Trie* root, const string& word) {
        Trie* cur = root;
        for (const char& ch: word) {
            if (!cur->child.count(ch)) {
                cur->child[ch] = new Trie();
            }
            cur = cur->child[ch];
            cur->words.push(word);
            if (cur->words.size() > 3) {
                cur->words.pop();
            }
        }
    }
    
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        Trie* root = new Trie();
        for (const string& word: products) {
            addWord(root, word);
        }
        
        vector<vector<string>> ans;
        Trie* cur = root;
        bool flag = false;
        for (const char& ch: searchWord) {
            if (flag || !cur->child.count(ch)) {
                ans.emplace_back();
                flag = true;
            }
            else {
                cur = cur->child[ch];
                vector<string> selects;
                while (!cur->words.empty()) {
                    selects.push_back(cur->words.top());
                    cur->words.pop();
                }
                reverse(selects.begin(), selects.end());
                ans.push_back(move(selects));
            }
        }
        
        return ans;
    }
};

#endif

int main() {
    Solution s;
    vector<string> products = {"mobile","mouse","moneypot","monitor","mousepad"};
    string searchWord = "mouse";
    auto x = s.suggestedProducts(products,searchWord);
    cout << 1;
    return 0;
}
