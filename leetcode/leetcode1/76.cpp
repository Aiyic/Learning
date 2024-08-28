#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int cs['z'-'A'+1]={0}; 
        int ct['z'-'A'+1]={0};
        set<char> ss; 
        for(char &c : t){
            ct[c-'A']++;
            ss.insert(c);
        }

        int i=0,j=0;
        while(ct[s[i]-'A']==0){
            i++;
            if(i>=s.length()) return string("");
        } 
        j=i;
        while(1) {
            if(j>=s.length()) return string("");
            char c = s[j]; 
            cs[c-'A']++; j++;
            if(cs[c-'A'] >= ct[c-'A']) ss.erase(c);
            if(ss.empty()) break;
        }
        while(i<=j){
            char c = s[i];
            if(cs[c-'A'] > ct[c-'A']){
                cs[c-'A']--;
                i++;
            }
            else break;
        }
        int minLength=j-i;
        int mini=i;

        while(j<s.length()){
            // ++
            while(j<s.length()){
                char c = s[j];
                cs[c-'A']++; j++;
                // break
                if(c == s[i]) break;
            }
            if(j>=s.length() && s[i]!=s[j-1]) break;
            // --
            while(i<=j){
                char c = s[i];
                if(cs[c-'A'] > ct[c-'A']){
                    cs[c-'A']--; i++;
                }
                else break;
            }
            // update
            if(j-i<minLength){
                minLength=j-i;
                mini=i;
            }
        }
        return string(s,mini,minLength);
    }
};


int main() {
    Solution solution;
    // string s = "bqztnkmwaonpyfqaunplbtwarwwmjvznnagdkuznimeiuxiokzaltwmmuiyefzrtzzwmtvzbjdldavsluuynskcmvasaajvbkrndomgyqtdqoxdlrcyjocwldomfajgkbuqrgyrysvrisutmyuvpwtabkmgmynyzjosrpkqhhhpbdlnefltbetdqilcgabhjrzbgltpscfwhsjlxueabafriruorxxdoygvkzkebraijmwigajjaobkhxabuxeiwkfilsmolpyvbufjxotzfukorkpnktvifdqqveegvddwxjiwzbwgvgvoskbeeyojdecalgjilmflxnhzqdfnlcbgnektezekfgksptbaiilhxvgnyoakqdqfjcypddzjlkdafednoqxllfakvcwohotqssiwxhhitklzroofgntstveoacchsyakqigprpzlakmtaaahovbjrhxtjccbaclsmuhejirltdgvfhetchevoeqxgtyivmckilorthfmklkpuqlzypumtlkbgkjbwnneybysifeuqqknhvmfmgrgtdhzotdkgqrfupxeudzmwlzdglkuubaphkpvfuhlkysgprljxkytvzwdlixhlawsklnpfvcstxylolulvuesucxhkxoyxkqjyeyfbcxwzyhojcbhygzskzbxwpvtaleyredsgdpidwymazvzhxtswvrsmmnmxtmrxsjdxanaxlozlkauhuodrfxfrmsrfgicathxuvxtgmstwtqdpeiikfnbthuyoeaoyjoselnnzfixyycpdkxprlsksnkirmxpwljcywpaeaxeyaudmrugcnsxadf";
    // string t = "rpejlru";
    // string s = "ADOBECODEBANC";
    // string t = "ABC";
    string s = "bbaac";
    string t = "aba";
    auto a = solution.minWindow(s,t) ;
    cout << a;
    return 0;
}