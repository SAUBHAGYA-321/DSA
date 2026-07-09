class Solution {
public:
   int minSubArrayLen(int tar, vector<int>& a) {
        int n = a.size();
        int left = 0;
        int sum = 0;
        int minLen = INT_MAX;

        for (int right = 0; right < n; ++right) {
            sum += a[right];

            // shrink window while valid
            while (sum >= tar) {
                minLen = min(minLen, right - left + 1);
                sum -= a[left];
                ++left;
            }
        }

         return (minLen == INT_MAX) ? 0 : minLen;

    }
};

