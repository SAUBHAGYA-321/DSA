class Solution {
public:
    vector<int> parent;
    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
    void unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra != rb) parent[ra] = rb;
    }
    
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
        
        // Since nums is sorted non-decreasing, only need to check adjacent elements
        for (int i = 0; i + 1 < n; i++) {
            if (nums[i+1] - nums[i] <= maxDiff) {
                unite(i, i+1);
            }
        }
        
        vector<bool> answer;
        for (auto& q : queries) {
            int u = q[0], v = q[1];
            answer.push_back(find(u) == find(v));
        }
        
        return answer;
    }
};