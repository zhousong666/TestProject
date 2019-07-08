#pragma once
#include "road.h"
#include <vector>

using namespace std;

class road {
public:
	road(short id,
		short length,
		short speed,
		short channel,
		short fromId,
		short toId,
		bool isDuplex) {
		roadId = id;
		roadLength = length;
		roadSpeed = speed;
		roadChannel = channel;
		roadFromId = fromId;
		roadToId = toId;
		roadIsDuplex = isDuplex;
		roadState = 0;

		//初始化道路空间  车道数与车道长度
		roadInfo.resize(channel);
		for (int k = 0; k < channel; ++k) {
			for (int i = 0; i < roadLength; ++i) {
				roadInfo[k].push_back(-1);   //初始化所有车位的内容全为-1，代表空闲，之后这里将填充carId
			}
		}
		//初始化道路开始的等待区
		for (int k = 0; k < channel; ++k) {
			roadWaitingArea.push_back(-1);
		}
			

	};
	void updateRoadInfo(short carId) {
		for (int i = 0; i < roadChannel; ++i) {
			if (roadInfo[i][0] == -1) {
				roadInfo[i][0] = carId;
				if (i == roadChannel - 1) 
					roadState = -1;
				break;
			}
		}
	}
	void updateRoadWaitingArea(short carId) {
		for (int i = 0; i < roadChannel; ++i) {
			if (roadWaitingArea[i] == -1) {
				roadWaitingArea[i] = carId;
				if (i == roadChannel - 1) 
					roadState = -1;
				break;
			}
		}
	}

public:
	short roadId;
	short roadLength;
	short roadSpeed;
	short roadChannel;
	short roadFromId;
	short roadToId;
	bool roadIsDuplex;
	short roadState;   // 0表示空闲， 1代表有车但并未拥堵， -1代表拥堵

	vector<vector<short>> roadInfo;
	vector<short> roadWaitingArea;
};
