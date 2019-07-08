#include <iostream>
#include <vector>

using namespace std;
void BubbleSort(vector<int> & vec) {
	for (int i = 0; i < vec.size() - 1; ++i) {
		for (int j = 0; j < vec.size() - i - 1; ++j) {
			if (vec[j] > vec[j + 1]) {
				int tmp = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = tmp;
			}
		}
	}
}

void SelectSort(vector<int> & vec) {
	int minIndex = 0, tmp = 0;
	for (int i = 0; i < vec.size() - 1; ++i) {
		minIndex = i;
		for (int j = i + 1; j < vec.size(); ++j) {
			if (vec[j] < vec[minIndex]) minIndex = j;
		}
		tmp = vec[i];
		vec[i] = vec[minIndex];
		vec[minIndex] = tmp;
	}
}

void InsertSort(vector<int> & vec) {
	int current = 0;
	int preIndex = 0;
	for (int i = 1; i < vec.size(); ++i) {
		preIndex = i - 1;
		current = vec[i];
		while (preIndex >= 0 && vec[preIndex] > current) {
			vec[preIndex + 1] = vec[preIndex];
			--preIndex;
		}
		vec[preIndex + 1] = current;
	}
}

void QuickSort(vector<int> &vec, int l, int r) {
	if (l < r) {
		int x = vec[l];
		int i = l;
		int j = r;
		while (i < j) {
			while (i < j && x <= vec[j]) --j;
			if ( i< j) vec[i++] = vec[j];
			while (i < j && x >= vec[i]) ++i;
			if (i < j) vec[j--] = vec[i];
		}
		vec[i] = x;
		QuickSort(vec, l, i - 1);
		QuickSort(vec, i + 1, r);
	}
}

void Heapify(vector<int> &vec, int i) {
	int left = i * 2 + 1;
	int right = i * 2 + 2;
	if (left < vec.size() && vec[left] > vec[i]) {
		swap(vec[left], vec[i]);
	}
	if (right < vec.size() && vec[right] > vec[i]) {
		swap(vec[right], vec[i]);
	}
}
void BuildMaxHeap(vector<int> &vec, int size) {
	for (int i = size - 1; i >= 0; --i) {
		Heapify(vec, i);
	}
}

void HeapSort(vector<int> & vec) {
	int len = vec.size();

	for (int i = 0; i < len - 1; ++i) {
		BuildMaxHeap(vec, len);
		--len;
		swap(vec[0], vec[len]);

	}
}
int main() {
	vector<int> testVec = { 3,5,2,9,4 };
	//BubbleSort(testVec);
	//SelectSort(testVec);
	//InsertSort(testVec);
	//QuickSort(testVec, 0, testVec.size() - 1);
	HeapSort(testVec);
	return 0;
}