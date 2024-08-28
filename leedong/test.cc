#include <bits/stdc++.h>

using namespace std;

// 写一个模板函数，实现不同类型的相加

// template<typename T, typename U>
// auto add(const T& t, const U& u) -> decltype(t+u){
//     return t+u;
// }

// int main(){
//     int x = 1;
//     int y = 2;
//     std ::cout << "add result: " << add(x, y) << std::endl;

//     std::string s1 = "abc";
//     std::string s2 = "def";

//     std::cout << "add result: " << add(s1, s2) << std::endl;
//     return 0;
// }

// void quickSort(vector<int>& data, int left, int right){
//     if(left >= right) return ;

//     // 选取基准元素
//     int pivot = data[(left + right) / 2];
//     int i = left;
//     int j = right;
//     while(i <= j){
//         // 找到从左往右第一个大于基准元素的下标
//         while(data[i] < pivot){
//             i++;
//         }
//         // 从右到左找第一个小于基准元素的下标
//         while(data[j] > pivot){
//             j--;
//         }
//         if(i <= j){
//             // 交换
//             swap(data[i], data[j]);
//             i++;
//             j--;
//         }
//     }
//     // 分治
//     quickSort(data, left, j);
//     quickSort(data, i, right);
// }

// int main(){
//     vector<int> data={5, 5, 4, 3, 2, 1};

//     quickSort(data, 0, data.size()-1);

//     for(auto& it : data){
//         cout << it << " ";
//     }
//     cout << endl;
// }


// 直方图 接水量

int getWater(vector<int>& nums){
    int ans = 0;
    // 单调栈
    stack<int> st;
    int n = nums.size();
    for(int i=0; i<n; i++){
        // 单调栈不为空 并且当前遍历元素大于栈顶元素（有空间接水）
        while(st.empty()==false && nums[i]>= nums[st.top()]){
            // 保存栈顶元素
            int top = st.top();
            st.pop();
            if(st.empty() == true) break;
            // 栈顶的下一个元素
            int l = st.top();
            int curW = i - l - 1;
            int curH = min(nums[l], nums[i]) - nums[top];
            ans += curH * curW;
        }
        // 当前下标入栈
        st.push(i);
    }
    return ans;
}

int main(){
    vector<int> nums={3, 2, 1, 2, 3};

    int ans = getWater(nums);
    cout << ans << endl;
}

/**

    1       1
    1 1   1 1
    1 1 1 1 1

 */