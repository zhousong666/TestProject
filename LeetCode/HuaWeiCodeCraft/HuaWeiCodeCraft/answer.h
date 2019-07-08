#pragma once
#include "answer.h"
#include <vector>
using namespace std;

const short LEFT = 0;
const short STRAIGHT = 1;
const short RIGHT = 2;
const short ENDPOINT = 3;

class answer {
public:
	answer(short & carId, vector<short>  & carRoadLine) {
		answerCarId = carId;
		roadLine.insert(roadLine.begin(), carRoadLine.begin(), carRoadLine.end());
	}
	void setStartTime(short time) {
		startTime = time;
	}
public:
	short startTime;
	short answerCarId;
	short actualTime;
	short finishTime;
	short carState; // -1:未出发(等待状态)；0:已完成调度(终止状态)；1:正在调度
	short carOnWhichRoad;
	short currPriority; 
	short currCarSpeed;
	short nextCrossDirection;
	vector<short> roadLine;//存储路线信息
};
