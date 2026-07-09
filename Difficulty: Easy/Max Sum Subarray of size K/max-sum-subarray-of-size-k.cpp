class Solution {
  public:
    int maxSubarraySum(vector<int>& arr, int k) {
        // code here
        int n =arr.size();
        if (n < k) return 0;
        
        int windowsum =0;
        int maxsum= INT_MIN;
        
        for (int i=0;i<k;i++){
         windowsum += arr[i];

        }
        maxsum=windowsum;
        for (int i=k; i<n; i++) {
         windowsum += arr[i]-arr[i-k];
        maxsum= max(maxsum ,windowsum);
        }
        
        return maxsum;
    }
};