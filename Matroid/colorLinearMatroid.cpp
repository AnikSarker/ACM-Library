/*
source : https://codeforces.com/blog/entry/69287 
         [Tutorial] Matroid intersection in simple words by ATSTNG
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long int Z2Vector;

struct GroundSetElement {
    int color;
    Z2Vector vector;
    bool in_independent_set;
    int independent_set_position;
    int bfs_parent;
};

struct Z2Basis {
    vector<Z2Vector> vectors;

    void add_vector(Z2Vector new_vector) {
        vectors.push_back(new_vector);
    }

    void reset() {
        vectors.clear();
    }

    int size() {
        return vectors.size();
    }

    void gaussian_elimination() {
        for (int i = 0; i < size(); i++) {
            for (int j = i; j < size(); j++) {
                if (vectors[i] < vectors[j]) swap(vectors[i], vectors[j]);
            }

            for (int j = i+1; j < size(); j++) {
                vectors[j] = min(vectors[j], vectors[j] ^ vectors[i]);
            }
        }
    }

    bool independent_with(Z2Vector new_vector) {
        for (auto v : vectors) new_vector = min(new_vector, new_vector ^ v);

        return new_vector > 0;
    }
};

int n;
int m;

int color_count;
bool color_used[60+60];

vector<GroundSetElement> ground_set;
vector<int> independent_set; /// as indexes of ground set
Z2Basis basis; /// of independent set
Z2Basis basis_without[60+60];

bool linear_oracle(int inserted) {
    return basis.independent_with(ground_set[inserted].vector);
}

bool linear_oracle(int inserted, int removed) {
    int wi = ground_set[removed].independent_set_position;

    return basis_without[wi].independent_with(ground_set[inserted].vector);
}

void prepare_linear_oracle() {
    basis.reset();

    for (int i = 0; i < independent_set.size(); i++) {
        basis_without[i].reset();
    }

    for (int i = 0; i < independent_set.size(); i++) {
        basis.add_vector(ground_set[independent_set[i]].vector);
        for (int  j = 0; j < independent_set.size(); j++) {
            if (i != j) basis_without[j].add_vector(ground_set[independent_set[i]].vector);
        }
    }

    basis.gaussian_elimination();
    for (int i = 0; i < independent_set.size(); i++) {
        basis_without[i].gaussian_elimination();
    }
}

bool colorful_oracle(int inserted) {
    int inserted_color = ground_set[inserted].color;

    return !color_used[inserted_color];
}

bool colorful_oracle(int inserted, int removed) {
    int inserted_color = ground_set[inserted].color;
    int removed_color = ground_set[removed].color;

    if (!color_used[inserted_color]) return true;

    return inserted_color == removed_color;
}

void prepare_colorful_oracle() {
    for (int c = 0; c < color_count; c++) {
        color_used[c] = false;
    }

    for (auto idx : independent_set) {
        color_used[ground_set[idx].color] = true;
    }
}

bool augment() {
    prepare_linear_oracle();
    prepare_colorful_oracle();

    const int SOURCE = -1;
    const int NOT_VISITED = -2;
    const int NOT_FOUND = -3;

    for (int i = 0; i < ground_set.size(); i++) {
        ground_set[i].bfs_parent = NOT_VISITED;
    }

    int endpoint = NOT_FOUND;

    queue<int> q;

    for (int i = 0; i < ground_set.size(); i++) {
        if (colorful_oracle(i)) {
            ground_set[i].bfs_parent = SOURCE;
            q.push(i);
        }
    }

    while (q.size()) {
        int cur = q.front();
        q.pop();

        if (ground_set[cur].in_independent_set) {
            for (int to = 0; to < ground_set.size(); to++) {
                if (ground_set[to].bfs_parent != NOT_VISITED) continue;
                if (!colorful_oracle(to, cur)) continue;

                ground_set[to].bfs_parent = cur;
                q.push(to);
            }
        } else {
            if (linear_oracle(cur)) {
                endpoint = cur;
                break;
            }

            for (auto to : independent_set) {
                if (ground_set[to].bfs_parent != NOT_VISITED) continue;
                if (!linear_oracle(cur, to)) continue;

                ground_set[to].bfs_parent = cur;
                q.push(to);
            }
        }
    }

    if (endpoint == NOT_FOUND) return false;

    do {
        ground_set[endpoint].in_independent_set ^= true;
        endpoint = ground_set[endpoint].bfs_parent;
    } while (endpoint != SOURCE);

    independent_set.clear();
    for (int i = 0; i < ground_set.size(); i++) {
        if (ground_set[i].in_independent_set) {
            ground_set[i].independent_set_position = independent_set.size();
            independent_set.push_back(i);
        }
    }

    return true;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        ground_set.emplace_back();
        ground_set.back().color = i;
        ground_set.back().in_independent_set = false;

        cin >> ground_set.back().vector;
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        while (k--) {
            ground_set.emplace_back();
            ground_set.back().color = n+i;
            ground_set.back().in_independent_set = false;

            cin >> ground_set.back().vector;
        }
    }

    color_count = n+m;

    while (augment()) ;

    if (independent_set.size() < color_count) {
        cout << "-1\n";
        return;
    }

    for (int i = n; i < ground_set.size(); i++) {
        if (ground_set[i].in_independent_set) cout << ground_set[i].vector << "\n";
    }
}

int main() {
    solve();
}
