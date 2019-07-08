#pragma once
#include "maxProductAfterCutting.h"


class maxProductAfterCutting {
public:
	int maxProductAfterCutting_solution(int length) {
		if (length < 2) return 0;
		if (length == 2) return 1;
		if (length == 3) return 2;

	}
};
