#include <iostream>
#include <tuple>
#include <queue>
#include <algorithm>

using namespace std;

int board[102][102][102];
int vis[102][102][102];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M, H;
    cin >> M >> N >> H;

    int dh[6] = {0, 0, 0, 0, 1, -1};
    int dn[6] = {1, -1, 0, 0, 0, 0};
    int dm[6] = {0, 0, 1, -1, 0, 0};

    queue<tuple<int, int, int>> Q;

    for(int h = 0; h < H; h++) {
        for(int n = 0; n < N; n++) {
            for(int m = 0; m < M; m++) {
                cin >> board[h][n][m];
                if(board[h][n][m] == 1) {
                    Q.push({h, n, m});
                    vis[h][n][m] = 0;
                } else {
                    vis[h][n][m] = -1;
                }
            }
        }
    }

    while(!Q.empty()) {
        auto cur = Q.front(); Q.pop();
        int curH, curN, curM;
        tie(curH, curN, curM) = cur;

        for(int dir = 0; dir < 6; dir++) {
            int nh = curH + dh[dir];
            int nn = curN + dn[dir];
            int nm = curM + dm[dir];

            if (nh < 0 || nh >= H || nn < 0 || nn >= N || nm < 0 || nm >= M) continue;
            if (vis[nh][nn][nm] >= 0) continue;
            if (board[nh][nn][nm] == -1) continue;

            vis[nh][nn][nm] = vis[curH][curN][curM] + 1;
            Q.push({nh, nn, nm});
        }
    }

    int ans = 0;
    for(int h = 0; h < H; h++) {
        for(int n = 0; n < N; n++) {
            for(int m = 0; m < M; m++) {
                if(board[h][n][m] == 0 && vis[h][n][m] == -1) {
                    cout << -1;
                    return 0;
                }
                ans = max(ans, vis[h][n][m]);
            }
        }
    }

    cout << ans;
    return 0;
}