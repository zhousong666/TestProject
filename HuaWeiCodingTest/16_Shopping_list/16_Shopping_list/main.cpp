#include <iostream>
#include <vector>

using namespace std;

int main() {
	int m = 0, n = 0;
	
	while (cin >> m >> n) {
		vector<vector<int>> arr(n);
		for (int i = 0; i < n; ++i) {
			int v, p, q;
			cin >> v >> p >> q;
			arr[i].push_back(v);
			arr[i].push_back(p);
			arr[i].push_back(q);
			system("pause");
		}


	}
	return 0;
}