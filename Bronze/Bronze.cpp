#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<pair<int, int>> points(N);

    for (int i = 0; i < N; i++) {
        cin >> points[i].first >> points[i].second;
    }

    // 정렬: x 오름차순, x가 같으면 y 오름차순
    sort(points.begin(), points.end());

    for (const auto& p : points) {
        cout << p.first << " " << p.second << "\n";
    }

    return 0;
}
