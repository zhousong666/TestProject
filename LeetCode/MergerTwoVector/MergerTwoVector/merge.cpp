#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		if (m == 0 && n == 0) return;
		if (m == 0) {
			nums1 = nums2;
			return;
		}
		else if (n == 0) return;
		int currIndex1 = 0;
		int currIndex2 = 0;
		vector<int> nums3;
		for (int i = 0; i < (m + n); i++) {
			if ((nums1[currIndex1] < nums2[currIndex2]) && currIndex1 != m) {
				nums3.push_back(nums1[currIndex1++]);
				if (currIndex1 == m) {
					for (int j = currIndex2; j < n; j++)
						nums3.push_back(nums2[j]);
					break;
				}
			}
			else if ((nums1[currIndex1] > nums2[currIndex2]) && currIndex1 != m) {
				nums3.push_back(nums2[currIndex2++]);
				if (currIndex2 == n) {
					for (int j = currIndex1; j < m; j++)
						nums3.push_back(nums1[j]);
					break;
				}
			}
			else if ((nums1[currIndex1] == nums2[currIndex2])) {
				if (i == (m + n - 1)) nums3.push_back(nums2[currIndex2]);
				else {
					nums3.push_back(nums1[currIndex1]);
					nums3.push_back(nums2[currIndex2]);
				}
				currIndex1++;
				currIndex2++;
				if (currIndex1 == m) {
					for (int j = currIndex2; j < n; j++)
						nums3.push_back(nums2[j]);
					break;
				}
				if (currIndex2 == n) {
					for (int j = currIndex1; j < m; j++)
						nums3.push_back(nums1[j]);
					break;
				}
				i++;
			}
		}
		nums1 = nums3;
	}
};


int main() {
	vector<int> vec1 = { 0,2,0,0,0,0,0,0};
	vector<int> vec2 = { -1,1,1,2,2,3};
	Solution s1;
	s1.merge(vec1, 2, vec2, 6);
	return 0;
}