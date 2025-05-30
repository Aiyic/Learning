/*
 * @lc app=leetcode.cn id=69 lang=cpp
 *
 * [69] x 的平方根 
 *
 * https://leetcode.cn/problems/sqrtx/description/
 *
 * algorithms
 * Easy (38.41%)
 * Likes:    1441
 * Dislikes: 0
 * Total Accepted:    789.5K
 * Total Submissions: 2.1M
 * Testcase Example:  '4'
 *
 * 给你一个非负整数 x ，计算并返回 x 的 算术平方根 。
 * 
 * 由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。
 * 
 * 注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：x = 4
 * 输出：2
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：x = 8
 * 输出：2
 * 解释：8 的算术平方根是 2.82842..., 由于返回类型是整数，小数部分将被舍去。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 <= x <= 2^31 - 1
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int mySqrt(int x) {
        if(x==0 || x==1) return x;
        int l=1,r=x,mid;
        while(l<r){     // =
            mid=l+(r-l)/2;  //local

            int t=x/mid;
            int c=x%mid;

            if(mid==t && c==0) break;

            if(t>=mid) l=mid+1;    //+1
            else r=mid;             //-1
        }
        if(x/mid<mid) mid--;
        return mid;
    }
};
// @lc code=end
// x           mid*mid
// t*mid+c     mid*mid
// t+c/mid     mid


int main() {
    Solution solution;
    
    int s = solution.mySqrt(2147483647) ;

    return 0;
}