// simulate.cpp
#include "simulate.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <numeric>
#include <fstream>
#include <algorithm>

using namespace std;

// Tree Node Structure
struct Node {
    string name;
    int value;
    vector<Node*> children;
};

bool allNonNegative(const std::vector<double>& v) {
    return all_of(v.begin(), v.end(), [](double x) {
        return x >= 0;
        });
}

vector<double> Probabilities_1d(float D2) {
    vector<double> P(2);
    double RR = pow(0.5, D2);
    P[0] = 0.5 * (1.0 + sqrt(1 - 2.0 * (1 - RR)));
    P[1] = 1.0 - P[0];
    return P;
}

vector<double> Probabilities_2d(float D2) {
    vector<double> P(4), F(4);
    double sum, RR = pow(0.5, D2), r = sqrt(RR - 0.25);
    bool flag = true;

    while (flag) {

        sum = 0.0;
        for (int i = 0; i < 4; ++i) {
            F[i] = (double)rand() / RAND_MAX;
            sum += F[i];
        }
        for (int i = 0; i < 4; ++i) {
            F[i] /= sum;
        }
        sum = 0.0;
        for (int i = 0; i < 4; ++i) {
            sum += pow((F[i] - 0.25), 2);
        }
        sum = sqrt(sum);
        for (int i = 0; i < 4; ++i) {
            P[i] = 0.25 + (F[i] - 0.25) * r / sum;
        }
        if (allNonNegative(P)) flag = false;
    }
    return P;
}

vector<double> Probabilities_3d(float D2) {
    vector<double> P(8), F(8);
    double sum, RR = pow(0.5, D2), r = sqrt(RR - 0.125);
    bool flag = true;

    while (flag) {

        sum = 0.0;
        for (int i = 0; i < 8; ++i) {
            F[i] = (double)rand() / RAND_MAX;
            sum += F[i];
        }
        for (int i = 0; i < 8; ++i) {
            F[i] /= sum;
        }
        sum = 0.0;
        for (int i = 0; i < 8; ++i) {
            sum += pow((F[i] - 0.125), 2);
        }
        sum = sqrt(sum);
        for (int i = 0; i < 8; ++i) {
            P[i] = 0.125 + (F[i] - 0.125) * r / sum;
        }
        if (allNonNegative(P)) flag = false;
    }
    return P;
}

// Recursively construct a binary tree of depth K
Node* build_tree(int depth, int n, const string& name, mt19937& gen) {
    Node* node = new Node{ name, -1, {} };
    int num_children = 1 << n; // 2^n

    if (depth == 0) return node;

    // Use unique random values in the range [1, ..., 2^K] as node values
    vector<int> values(num_children);
    iota(values.begin(), values.end(), 1);
    shuffle(values.begin(), values.end(), gen);

    for (int i = 0; i < num_children; ++i) {
        string child_name = name + "-" + to_string(i);
        Node* child = build_tree(depth - 1, n, child_name, gen);
        child->value = values[i];
        node->children.push_back(child);
    }

    return node;
}

// Single traverse the tree
vector<float> walk_tree(Node* root, int K, int n, const vector<double>& P, mt19937& gen) {
    Node* current = root;
    discrete_distribution<> dist(P.begin(), P.end());
    vector<int> coords(n);
    vector<float> X1(n), X2(n), X(n);
    uniform_real_distribution<double> uniform_dist(0.0, 1.0);

    for (int d = 0; d < n; ++d) {
        X1[d] = 0.0; X2[d] = 1.0;
    }

    for (int level = 0; level < K; ++level) {
        int idx = dist(gen);
        if (idx >= current->children.size()) break;
        current = current->children[idx];

        for (int d = 0; d < n; ++d) {
            coords[d] = (current->value >> d) & 1;  // d-th bit of number i
            if (coords[d] == 0)
                X1[d] = 0.5 * (X1[d] + X2[d]);
            else
                X2[d] = 0.5 * (X1[d] + X2[d]);
        }
    }

    for (int d = 0; d < n; ++d) {
        X[d] = X1[d] + uniform_dist(gen) * (X2[d] - X1[d]);
    }

    return X;
}


template<int D>
void simulate(PointCloud<D>& cloud, float D2, int K, int n_points) {

    auto sizes = cloud.getSizes();
     vector<double> P;// probabilities

    if (D == 1)
        P = Probabilities_1d(D2);
    else if (D == 2)
        P = Probabilities_2d(D2);
    else if (D == 3)
        P = Probabilities_3d(D2);

    int num_children = 1 << D;
    vector<float> X(D);
    typename PointCloud<D>::Point pt;

    random_device rd;
    mt19937 gen(rd());

    // Build the tree recursively
    Node* root = build_tree(K, D, "root", gen);

    for (int i = 0; i < n_points; ++i) {
        X = walk_tree(root, K, D, P, gen);
        for (int j = 0;j < D;++j) pt[j] = X[j]*sizes[j];
        cloud.addPoint(pt);
    }

}

// Provide explicit template instantiation
template void simulate<1>(PointCloud<1>&, float, int, int);
template void simulate<2>(PointCloud<2>&, float, int, int);
template void simulate<3>(PointCloud<3>&, float, int, int);
