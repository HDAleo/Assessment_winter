#include <iostream>  
#include <vector>  
#include <algorithm>  
using namespace std;  
  
class LongestIncreasingSubsequence {  
public:  
    static pair<int, vector<int>> findLongestIncreasingSubsequence(vector<int>& nums) {  
        int n = nums.size();  
        if (n == 0) return {0, {}};  
  
        vector<int> lengths(n, 1); 
        vector<int> parents(n, -1);
  
        int maxLengthIndex = 0;
        for (int i = 1; i < n; ++i) {  
            for (int j = 0; j < i; ++j) {  
                if (nums[i] > nums[j] && lengths[i] < lengths[j] + 1) {  
                    lengths[i] = lengths[j] + 1;  
                    parents[i] = j;  
                }  
            }  
            if (lengths[i] > lengths[maxLengthIndex]) {  
                maxLengthIndex = i;  
            }  
        }  
  
        vector<int> longestSubsequence;  
        for (int i = maxLengthIndex; i != -1; i = parents[i]) {  
            longestSubsequence.push_back(nums[i]);  
        }  
        reverse(longestSubsequence.begin(), longestSubsequence.end());
  
        return {lengths[maxLengthIndex], longestSubsequence};  
    }  
};  
  
int main() {  
    vector<int> input = {10, 22, 9, 33, 21, 50, 41, 60, 80};  
  
    auto result = LongestIncreasingSubsequence::findLongestIncreasingSubsequence(input);  
  
    cout << "Longest Increasing Subsequence: ";  
    for (int num : result.second) {  
        cout << num << ", ";  
    }  
    cout << endl;  
  
    cout << "Length of Longest Increasing Subsequence: " << result.first << endl;  
  
    return 0;  
}