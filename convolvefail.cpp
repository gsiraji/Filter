#include <iostream>
#include <vector>

std::pair<std::vector<int>, std::vector<int> > SplitAt(const std::vector<int>& vec, int n) {
    std::pair<std::vector<int>, std::vector<int> > result;
    result.first.reserve(n);
    result.second.reserve(vec.size() - n);
    for (int i = 0; i < n; ++i) {
        result.first.push_back(vec[i]);
    }
    for (int i = n; i < vec.size(); ++i) {
        result.second.push_back(vec[i]);
    }
    return result;
}

std::vector<int> Convolve(const std::vector<int>& x, const std::vector<int>& h) {
    int n = h.size();
    int m = x.size();

    if (n > m) {
        return Convolve(h, x);
    }

    if (n == 1) {
        std::vector<int> result(m);
        for (int i = 0; i < m; ++i) {
            result[i] = h[0] * x[i];
        }
        return result;
    }

    int bn = 2 * n;
    int c = 1;
    std::pair<std::vector<int>, std::vector<int> > x_split = SplitAt(x, bn / (2 * c));
    std::pair<std::vector<int>, std::vector<int> > h_split = SplitAt(h, bn / (2 * c));

    std::vector<int> x0 = x_split.first;
    std::vector<int> x1 = x_split.second;
    std::vector<int> h0 = h_split.first;
    std::vector<int> h1 = h_split.second;

    std::vector<int> z0 = Convolve(x0, h0);
    std::vector<int> z1(x0.size());
    for (int i = 0; i < x0.size(); ++i) {
        z1[i] = x0[i] - x1[i];
    }
    for (int i = 0; i < h1.size(); ++i) {
        z1[i] += h1[i] - h0[i];
    }
    std::vector<int> z2 = Convolve(x1, h1);

    std::vector<int> result(m + bn);
    for (int i = 0; i < z2.size(); ++i) {
        result[i] = z2[i];
    }
    for (int i = 0; i < z1.size(); ++i) {
        result[i + bn / (2 * c)] += z1[i];
    }
    for (int i = 0; i < z0.size(); ++i) {
        result[i + bn] += z0[i];
    }

    return result;
}

int main() {
    int x_arr[] = {1, 2, 3, 4, 5};
    int h_arr[] = {1, 2, 1};
    std::vector<int> x(x_arr, x_arr + sizeof(x_arr) / sizeof(x_arr[0]));
    std::vector<int> h(h_arr, h_arr + sizeof(h_arr) / sizeof(h_arr[0]));

    std::vector<int> result = Convolve(x, h);

    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}