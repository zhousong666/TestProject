#pragma once
#include "car.h"

class car {
public:
	car(short id,
		short from,
		short to,
		short speed,
		short planTime) {
		carId = id;
		carFrom = from;
		carTo = to;
		carSpeed = speed;
		carPlanTime = planTime;
	};

public:
	short carId;
	short carFrom;
	short carTo;
	short carSpeed;
	short carPlanTime;
};