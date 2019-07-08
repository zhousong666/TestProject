#pragma once

#include "systemInfo.h"

class systemInfo {
public:
	systemInfo(int time) {
		systmeTime = time;
	}

public:
	int systmeTime;
	int onLineCars;
	int offLineCars;

};
