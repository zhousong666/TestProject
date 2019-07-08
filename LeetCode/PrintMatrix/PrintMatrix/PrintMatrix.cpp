// PrintMatrix.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
using namespace std;
class Solution {
public:
	vector<int> printMatrix(vector<vector<int> > matrix) {
		vector<int> result;
		//if (matrix.size() == 1) return matrix[0];
		int leftIndex = 0;
		int rightIndex = matrix[0].size() - 1;
		int topIndex = 0;
		int bottomIndex = matrix.size() - 1;
		char direction = 'r';
		int matrixSize = matrix.size()*matrix[0].size();
		while (matrixSize) {
			if (direction == 'r') {
				direction = 'd';
				for (int i = 0; i < (rightIndex - leftIndex + 1); i++){ 
					matrixSize--;
					result.push_back(matrix[topIndex][leftIndex + i]);
				}	
				topIndex++;

			}
			else if (direction == 'd') {
				direction = 'l';
				for (int i = 0; i < (bottomIndex - topIndex + 1); i++) {
					matrixSize--;
					result.push_back(matrix[topIndex + i][rightIndex]);
				}
				rightIndex--;
			}
			else if (direction == 'l') {
				direction = 'u';
				for (int i = 0; i < (rightIndex - leftIndex + 1); i++) {
					matrixSize--;
					result.push_back(matrix[bottomIndex][rightIndex - i]);
				}					
				bottomIndex--;
			}
			else if (direction == 'u') {
				direction = 'r';
				for (int i = 0; i < (bottomIndex - topIndex + 1); i++) {
					matrixSize--;
					result.push_back(matrix[bottomIndex - i][leftIndex]);
				}					
				leftIndex++;
			}
		}
		return result;
	}
};

int main()
{
	vector<vector<int>> testVec = { { 1,2,3,4,5 } };
	Solution s1;
	s1.printMatrix(testVec);
    return 0;
}

