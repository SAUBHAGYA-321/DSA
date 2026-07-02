class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        // Sort by descending (minimum - actual), i.e., descending slack
        sort(tasks.begin(), tasks.end(), [](const vector<int>& a, const vector<int>& b) {
            return (a[1] - a[0]) > (b[1] - b[0]);
        });
        
        long long energyNeeded = 0;
        
        // Process in reverse: compute minimum energy needed at the start
        // of this task to finish it and everything after it.
        for (int i = tasks.size() - 1; i >= 0; i--) {
            int actual = tasks[i][0];
            int minimum = tasks[i][1];
            energyNeeded = max((long long)minimum, energyNeeded + actual);
        }
        
        return (int)energyNeeded;
    }
};