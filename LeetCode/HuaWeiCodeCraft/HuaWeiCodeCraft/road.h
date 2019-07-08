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

		//��ʼ����·�ռ�  �������복������
		roadInfo.resize(channel);
		for (int k = 0; k < channel; ++k) {
			for (int i = 0; i < roadLength; ++i) {
				roadInfo[k].push_back(-1);   //��ʼ�����г�λ������ȫΪ-1��������У�֮�����ｫ���carId
			}
		}
		//��ʼ����·��ʼ�ĵȴ���
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
	short roadState;   // 0��ʾ���У� 1�����г�����δӵ�£� -1����ӵ��

	vector<vector<short>> roadInfo;
	vector<short> roadWaitingArea;
};
