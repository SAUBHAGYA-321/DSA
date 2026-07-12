class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> temp = arr;

        // Sort the copied array
        sort(temp.begin(), temp.end());

        unordered_map<int, int> rank;
        int r = 1;

        // Assign ranks to unique elements
        for (int x : temp) {
            if (rank.find(x) == rank.end()) {
                rank[x] = r++;
            }
        }

        // Create answer array
        vector<int> ans;
        for (int x : arr) {
            ans.push_back(rank[x]);
        }

        return ans;
    }
};