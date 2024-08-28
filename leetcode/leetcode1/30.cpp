#include<iostream>
#include<vector>
#include<functional>

using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        hash<string> myhash;
        int wsize = words.size();
        int slength = s.length();
        int wlength = words[0].length();
        int subs_length = wsize*wlength;
        vector<int> wordshash;
        for(string x : words)
            wordshash.push_back(myhash(x));
        
        vector<int> results;

        for(int idx=0; idx<=slength-subs_length; idx++ ){
            string subs = string(s,idx,subs_length);
            int flag = 1;
            int record[5000]={0};
            for(int i=0;i<wsize;i++){
                string sub_word = string(subs,i*wlength,wlength);
                int sub_word_h = myhash(sub_word);
                int wordidx;
                for(wordidx=0; wordidx<wsize; wordidx++){
                    if(wordshash[wordidx] == sub_word_h && record[wordidx]==0) {
                        if(words[wordidx] == sub_word){
                            record[wordidx]=1;
                            break;
                        }
                    }
                }
                if(wordidx==wsize){
                    flag=0;
                    break;
                }
            }

            if(!flag) continue;

            for(int wordidx=0; wordidx<wsize; wordidx++){
                if(record[wordidx]==0) {
                    flag=0;
                }
            }

            if(flag){
                results.push_back(idx);
            }
        }
        return results;
    }
};

int main() {
    Solution x;
    string s = "barfoofoobarthefoobarman";
    vector<string> words;
    words.push_back("bar");
    words.push_back("foo");
    words.push_back("the");
    vector<int> a = x.findSubstring(s,words);
    return 0;
}
