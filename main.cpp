// lab1 stable matching
#include <iostream>
#include<map>
#include<queue>

using namespace std;

int main() {
    int n;
    cin >> n;
    int *wife = new int[n];
    int *husband = new int[n];
    int *proposal_time = new int[n];
    string *man = new string[n];
    string *woman = new string[n];
    int man_list[n][n];
    int woman_list[n][n];
    int woman_inverse[n][n];
    map<string, int> woman_map;
    map<string, int> man_map;
    queue<int> single_dog;
    string temp;
    for (int i = 0; i < n; ++i) {             //read in man
        cin >> temp;
        man_map.insert(pair<string, int>(temp, i));
        wife[i] = -1;
        proposal_time[i] = 0;
        man[i] = temp;
        single_dog.push(i);
    }
    for (int j = 0; j < n; ++j) {           //read in woman
        cin >> temp;
        woman_map.insert(pair<string, int>(temp, j));
        husband[j] = -1;
        woman[j] = temp;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> temp;
            man_list[i][j] = woman_map[temp];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> temp;
            woman_list[i][j] = man_map[temp];
        }
        for (int k = 0; k < n; ++k) {             //for inverse
            woman_inverse[i][woman_list[i][k]] = k;
        }
    }

    //matching process
    int proposed;
    int waiting_woman;
    int last_husband;
    while (!single_dog.empty()) {
        proposed = single_dog.front();
        single_dog.pop();
        waiting_woman = man_list[proposed][proposal_time[proposed]];
        if (husband[waiting_woman] == -1) {
            husband[waiting_woman] = proposed;
            wife[proposed] = waiting_woman;
        } else if (woman_inverse[waiting_woman][husband[waiting_woman]] > woman_inverse[waiting_woman][proposed]) {
            last_husband = husband[waiting_woman];
            husband[waiting_woman] = proposed;
            wife[proposed] = waiting_woman;
            single_dog.push(last_husband);
        } else {
            single_dog.push(proposed);
        }
        proposal_time[proposed]++;
    }

    for (int l = 0; l < n; ++l) {
        cout << man[l] << " " << woman[wife[l]] << "\n";
    }

}
