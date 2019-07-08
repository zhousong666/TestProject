// MergeTwoList.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
	val(x), next(NULL) {
	}
};
class Solution {
public:
	ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
	{
		if (pHead1 == NULL) return pHead2;
		if (pHead2 == NULL) return pHead1;
		ListNode* currList = NULL;
		if (pHead1->val > pHead2->val) {
			currList = pHead2;
			pHead2 = pHead2->next;
		}
		if (pHead2->val >= pHead1->val) {
			currList = pHead1;
			pHead1 = pHead1->next;
		}
		ListNode* pHead3 = currList;
		while (pHead2 != NULL && pHead1 != NULL) {
			if (pHead1->val > pHead2->val) {
				pHead3->next = pHead2;
				pHead3 = pHead3->next;
				pHead2 = pHead2->next;
			}
			if (pHead2->val >= pHead1->val) {
				pHead3->next = pHead1;
				pHead3 = pHead3->next;
				pHead1 = pHead1->next;
			}
		}
		if (pHead2 == NULL) pHead3->next = pHead1;
		else if (pHead1 == NULL) pHead3->next = pHead2;

		return currList;

	}
};

int main()
{
    return 0;
}

