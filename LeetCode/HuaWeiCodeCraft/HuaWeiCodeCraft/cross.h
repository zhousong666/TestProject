#pragma once
#include "cross.h"
#include <vector>
using namespace std;

class cross {
public:
	cross(short id,
		short id1,
		short id2,
		short id3,
		short id4) {
		crossId = id;
		fourRoadAtCross[0] = id1;
		fourRoadAtCross[1] = id2;
		fourRoadAtCross[2] = id3;
		fourRoadAtCross[3] = id4;
	};

public:
	short crossId;
	vector<short> fourRoadAtCross = {-1, -1, -1, -1};
};