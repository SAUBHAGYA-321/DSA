class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                     vector<vector<int>>& queries) {

        vector<pair<int,int>> arr;
        for (int i = 0; i < n; ++i) {
            arr.push_back({nums[i], i});
        }
        sort(arr.begin(), arr.end());

        vector<int> vals(n), pos(n);
        for (int i = 0; i < n; ++i) {
            vals[i] = arr[i].first;
            pos[arr[i].second] = i;
        }

        // Connected components
        vector<int> comp(n, 0);
        for (int i = 1; i < n; ++i) {
            comp[i] = comp[i - 1];
            if (vals[i] - vals[i - 1] > maxDiff)
                comp[i]++;
        }

        // Farthest reachable in one step
        vector<int> nxt(n);
        int r = 0;
        for (int i = 0; i < n; ++i) {
            while (r + 1 < n && vals[r + 1] - vals[i] <= maxDiff)
                ++r;
            nxt[i] = r;
        }

        // Binary lifting
        int LOG = 1;
        while ((1 << LOG) <= n) ++LOG;

        vector<vector<int>> up(LOG, vector<int>(n));
        up[0] = nxt;

        for (int k = 1; k < LOG; ++k) {
            for (int i = 0; i < n; ++i) {
                up[k][i] = up[k - 1][ up[k - 1][i] ];
            }
        }

        auto getDist = [&](int u, int v) {
            int l = pos[u];
            int rr = pos[v];

            if (l == rr) return 0;
            if (comp[l] != comp[rr]) return -1;

            if (l > rr) swap(l, rr);

            int ans = 0;
            int cur = l;

            for (int k = LOG - 1; k >= 0; --k) {
                int nx = up[k][cur];
                if (nx < rr) {
                    cur = nx;
                    ans += (1 << k);
                }
            }

            return ans + 1;
        };

        vector<int> answer;
        for (auto &q : queries) {
            answer.push_back(getDist(q[0], q[1]));
        }

        return answer;
    }
};