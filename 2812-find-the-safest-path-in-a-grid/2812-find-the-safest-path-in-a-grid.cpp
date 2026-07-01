class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<pair<int,int>> q;
        
        // Step 1: Multi-source BFS from all thief cells
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (grid[r][c] == 1) {
                    dist[r][c] = 0;
                    q.push({r, c});
                }
            }
        }
        
        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};
        
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
        
        // Step 2: Max-bottleneck Dijkstra (maximize the minimum safety value along path)
        vector<vector<int>> safety(n, vector<int>(n, -1));
        safety[0][0] = dist[0][0];
        
        // max-heap: (safety value, row, col)
        priority_queue<tuple<int,int,int>> pq;
        pq.push({dist[0][0], 0, 0});
        
        while (!pq.empty()) {
            auto [s, r, c] = pq.top();
            pq.pop();
            
            if (s < safety[r][c]) continue; // outdated entry
            
            if (r == n - 1 && c == n - 1) {
                return s;
            }
            
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                    int ns = min(s, dist[nr][nc]);
                    if (ns > safety[nr][nc]) {
                        safety[nr][nc] = ns;
                        pq.push({ns, nr, nc});
                    }
                }
            }
        }
        
        return safety[n-1][n-1];
    }
};