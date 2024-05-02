#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>


using namespace std;

struct cisla {
    int hodnota;
    int smer;
};

vector<cisla> generate(int n) {
    vector<cisla> cis;
    for (int i = 1; i <= n; i++) {
        cis.push_back({ i, -1 });
    }
    return cis;
}

int find(vector<cisla> cis) {
    int mob = 0;
    int mobB = -1;
    for (int i = 0; i < cis.size(); i++) {
        if ((cis[i].smer == -1 && i != 0 && cis[i-1].hodnota < cis[i].hodnota )||( cis[i].smer == 1 && i != cis.size() -1 && cis[i].hodnota > cis[i+1].hodnota)) {
            if (cis[i].hodnota > mob) {
                mob = cis[i].hodnota;
                mobB = i;
            }
        }
    }
    return mobB;
}

void swapC(vector<cisla>& cis, int mobB) {
    if (cis[mobB].smer == -1) {
        for (int i = 0; i < cis.size(); i++) {
            if (cis[i].hodnota > cis[mobB].hodnota) {
                cis[i].smer *= -1;
            }
        }
        swap(cis[mobB].hodnota, cis[mobB-1].hodnota);
        swap(cis[mobB].smer, cis[mobB - 1].smer);
    }else if (cis[mobB].smer == 1) {
        for (int i = 0; i < cis.size(); i++) {
            if (cis[i].hodnota > cis[mobB].hodnota) {
                cis[i].smer *= -1;
            }
        }
        swap(cis[mobB].hodnota, cis[mobB + 1].hodnota);
        swap(cis[mobB].smer, cis[mobB + 1].smer);
    }
}

vector<vector<cisla>> alg(vector<cisla>cis) {
    
    vector<vector<cisla>> vys;
    vys.push_back(cis);
    int mobB = 10000;
    while (true) {
        mobB = find(cis);
        if (mobB == -1) {
            break;
        }
        swapC(cis, mobB);
        vys.push_back(cis); 
    }

    return vys;
}


int main()
{
    int n = 9;
    vector<cisla> cis = generate(n);



    auto star = std::chrono::high_resolution_clock::now();
    vector<vector<cisla>> vys = alg(cis);


    for (int i = 0; i < vys.size(); i++) {
        for (int j = 0; j < vys[i].size(); j++) {
            cout << vys[i][j].hodnota << "\t" << vys[i][j].smer << endl;
        }
        cout << endl;
    }

    auto en = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duratio = en - star;
    cout << "Time: " << duratio.count() << " sec" << endl;


    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = i + 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    do {
        for (int num : v) {
            cout << num << " ";
        }
        cout << endl;
    } while (next_permutation(v.begin(), v.end()));
    auto endd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endd - start;
    cout << "Time: " << duration.count() << " sec\n";

}


