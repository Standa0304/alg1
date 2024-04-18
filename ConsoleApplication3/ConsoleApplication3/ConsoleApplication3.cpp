#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

vector<vector < vector<int>>> getNext(vector<vector<int>> zac) {
   vector< vector < vector<int>>> next(4);
    
    for (int i = 0; i < zac.size(); ++i) {
        for (int j = 0; j < zac[i].size(); ++j) {
            if (zac[i][j] == 0) {
                int r = i;
                int s = j;

                const int dx[] = { -1, 1, 0, 0 };
                const int dy[] = { 0, 0, -1, 1 };

                for (int k = 0; k < 4; ++k) {
                    int newRow = r + dx[k];
                    int newCol = s + dy[k];
                    if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
                        swap(zac[r][s], zac[newRow][newCol]);
                        next[k] = zac;
                    }
                }

                return next;
            }
        }
    }

bool depthsearch(vector<vector<int>> zac) {
    stack<vector<vector<int>>> stack;
    unordered_set<vector<vector<int>>, hash<vector<vector<int>>>> visited;
    vector<vector<int>> cil = { {0, 2, 3}, {4, 5, 6}, {7, 8, 9} };

    stack.push(zac);
    visited.insert(zac);

    if (stack.empty()) {
        printf("Není řešení");
        return false;
    }
    else {
        if (zac == cil) {
            for (int i = 0; i < cil.size(); i++) {
                for (int j = 0; j < cil[1].size(); j++) {
                    cout << zac[i][j];
                }
                cout << "\n";
            }
        }
        else {
            vector<vector<int>> next = getNext(zac);


            stack.push(next);
            visited.insert(next);
        }
    }


}

int main()
{
    vector<vector<int>> zac = { {2, 3, 4}, {0, 5, 7}, {8, 6, 9}};



    int del = zac.size();
    int del2 = zac[1].size();

    depthsearch(zac);
  


}
