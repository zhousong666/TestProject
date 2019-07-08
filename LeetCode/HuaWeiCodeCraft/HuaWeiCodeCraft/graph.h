#pragma once
#include "graph.h"

#include < cstring > 


// 常量定义： 
const   int  maxV = 250;
const   double  Inf = 1e100;
// const int Inf=2000000000;

// Graph类定义： 
class  GraphMatrix {
private:
	int  v;     // 顶点数 
	int  e;     // 边数 
	short roadID[maxV][maxV];     // 邻接矩阵
	short length[maxV][maxV];     // 邻接矩阵 
	short speed[maxV][maxV];      // 邻接矩阵 
	short channel[maxV][maxV];
	bool isDuplex[maxV][maxV];

public:
	GraphMatrix(int a, int b) {
		v = a;
		e = b;
	}
	void  init() {
		memset(length, 0, sizeof(length));
		memset(speed, 0, sizeof(length));
		memset(channel, 0, sizeof(channel));
	}
	void  clear() {
		int  i, j;
		for (i = 0; i < maxV; ++i) {
			for (j = 0; j < maxV; ++j){
				length[i][j] = 0;
				speed[i][j] = 0;
				channel[i][j] = 0;
				roadID[i][j] = 0;
			}
				
		}
	}

	void  v_increment() {
		++v;
	}

	int  get_v() {
		return v;
	}

	int  get_e() {
		e = v * 4 - e;
		return e;
	}

	void  e_increment() {
		++e;
	}

	void  e_decrement() {
		--e;
	}

	void setLength(short& value, short& x, short& y) {
		length[x][y] = value;
	}

	short getLength(short& x, short& y) {
		return length[x][y];
	}

	void setSpeed(short& value, short& x, short& y) {
		speed[x][y] = value;
	}

	short getSpeed(short& x, short& y) {
		return speed[x][y];
	}

	void setChannel(short& value, short& x, short& y) {
		channel[x][y] = value;
	}
	void setIsDuplex(bool& value, short& x, short& y) {
		isDuplex[x][y] = value;
	}

	void setRoadID(short& value, short& fromCrodssID, short& toCrodssID) {
		roadID[fromCrodssID][toCrodssID] = value;
	}

	short getRoadID(short& fromCrodssID, short& toCrodssID) {
		return roadID[fromCrodssID][toCrodssID];
	}
};
