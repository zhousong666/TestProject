#include <string>  
#include <iostream> 
#include <sstream>
#include <stack>
#include <vector>
#include <fstream>  //ofstream类的头文件

#include "systemInfo.h"
#include "graph.h"
#include "road.h"
#include "cross.h"
#include "car.h"
#include "answer.h"
using namespace std;

vector<road> roadVec;
vector<cross> crossVec;
vector<car> carVec;
vector<answer> answerVec;

const int MAX_V = 100;
const int MAX = 100000;
bool S[MAX_V];		//记录从源点V0到终点Vi是否已经确定为最短路径，确定了记true，否则记false
short Path[MAX_V];	//记录从源点V0到终点Vi的当前最短路径上终点Vi的直接前驱顶点序号，若V0到Vi之间有边前驱为V0否则为-1 
short D[MAX_V];		//记录源点到终点之间最短路径的长度，存在记V0到Vi的边的权值，否则记为MAX 
stack<int> pathVec;	//因为路线是从终点往回倒推的，所以此处使用栈来保存路线
void ShortestPath_DIJ(GraphMatrix & G, short id, short v0, short endV, short speed)
{
	memset(S, 0, sizeof(S));
	memset(Path, 0, sizeof(Path));
	memset(D, 0, sizeof(D));
	for (short i = 0; i < G.get_v(); i++) {
		S[i] = false;				//S初始化为空集
		D[i] = G.getLength(v0, i);	//将v0到各个终点的最短路径长度初始化为边上的权值
		if	(D[i] > 0) Path[i] = v0;	//如果v0和v之间有边，则将v的前驱初始化为v0
		else	Path[i] = -1;		//如果v0和v之间无边，则将v的前驱初始化为-1
	}
	S[v0] = true;	//将v0加入s
	D[v0] = 0;		//源点到源点的权值为0
	
	//---------初始化结束，开始主循环，每次求得v0到某个顶点的最短路径，将v加到S数组
	for (short i = 1; i < G.get_v() + 1; i++) {

		int min = MAX;
		short v = v0;
		for (short w = 0; w < G.get_v() + 1; w++)
		{
			if (!S[w] && (D[w] > 0 && D[w] <min))
			{//选择一条当前最短路径，终点为v
				v = w;
				min = D[w];
			}
		}
		S[v] = true;//将v加到s集合中
		v0 = v;
		//cout << v0 << "---" << endV << endl;
		if (v0 == endV) {
			pathVec.push(endV);
			while (Path[endV] > 0) {
				pathVec.push(Path[endV]);
				endV = Path[endV];
			}
		}
		
		for (short w = 0; w < G.get_v() + 1; w++)
		{//更新从v0出发到集合V-S上所有顶点的最短路径长度
			if (!S[w] && (G.getLength(v,w) > 0))
			{
				D[w] = D[v] + G.getLength(v, w);//更新D[w]
				Path[w] = v0;//更改w的前驱为v0

			}
		}		
	}
}

void UpdateSystemState() {

}
int main() {
	GraphMatrix G(0, 0);
	G.clear();
	ifstream in_road("road.txt");
	ifstream in_cross("cross.txt");
	ifstream in_car("car.txt");
	

	if (in_cross) // 有cross文件  
	{
		string line;
		while (getline(in_cross, line)) // line中不包括每行的换行符  
		{

			if (line[0] == '#')
				continue;
			for (int i = 0; i < line.size(); ++i) {
				if (line[i] == '-') G.e_increment();
			}
			G.v_increment();
			istringstream stream(line);
			string element;
			short elementIndex = 0;
			short crossId = 0;
			short id1 = 0;
			short id2 = 0;
			short id3 = 0;
			short id4 = 0;
			while (getline(stream, element, ',')) {
				++elementIndex;
				int tmp = 0;
				int elementSize = element.size();
				if (elementIndex == 1) {   //  id
					for (int i = 1; i < elementSize; i++) {
						crossId += short(element[i] - 48) *  pow(10, (elementSize - i - 1));
					}
				}
				else if (elementIndex == 2) {   // 
					if (element[1] == '-')  id1 = -1;
					else{
						for (int i = 1; i < elementSize; i++) {
							id1 += short(element[i] - 48) *  pow(10, (elementSize - i - 1));
						}
					}
				}
				else if (elementIndex == 3) {   //  
					if (element[1] == '-')  id2 = -1;
					else {
						for (int i = 1; i < elementSize; i++) {
							id2 += short(element[i] - 48) *  pow(10, (elementSize - i - 1));
						}
					}
				}
				else if (elementIndex == 4) {   //  
					if (element[1] == '-')  id3 = -1;
					else {
						for (int i = 1; i < elementSize; i++) {
							id3 += short(element[i] - 48) *  pow(10, (elementSize - i - 1));
						}
					}
				}
				else if (elementIndex == 5) {   //  
					if (element[1] == '-')  id4 = -1;
					else {
						for (int i = 1; i < elementSize - 1; i++) {
							id4 += short(element[i] - 48) *  pow(10, (elementSize - i - 2));
						}
					}
				}
			}
			cross tmpCross(crossId, id1, id2, id3, id4);
			crossVec.push_back(tmpCross);
		}
	}
	else cout << "no cross.txt file" << endl;

	in_cross.close();

	if (in_road) // 有road文件  
	{
		string line;
		while (getline(in_road, line)) // line中不包括每行的换行符   cout << line << endl;
		{
			if (line[0] == '#') 
				continue;
			istringstream stream(line);
			string element;
			short elementIndex = 0;
			short tmpRoadID = 0;
			short tmpLength = 0;
			short tmpSpeed = 0;
			short tmpChannel = 0;
			short tmpCrossFrom = 0;
			short tmpCrossTo = 0;
			bool tmpisDuplex = false;
			while (getline(stream, element, ',')) {
				++elementIndex;
				int tmp = 0;
				int elementSize = element.size();
				if (elementIndex == 1) {   //  id
					for (int i = 1; i < elementSize; i++) {
						tmpRoadID += short(element[i] - 48) *  pow(10, (elementSize - i - 1));
					}
				}
				else if (elementIndex == 2) {   //  例如" 15"    int 15的计算,此处计算length
					for (int i = 1; i < elementSize; i++) {
						tmpLength += short(element[i] - 48) *  pow(10, (elementSize - i - 1));
					}
				}else if (elementIndex == 3) {   //  speed
					for (int i = 1; i < elementSize; i++) {
						tmpSpeed += short(element[i] - 48) *  pow(10, (elementSize - i - 1));
					}
				}
				else if (elementIndex == 4) {   //  channel
					for (int i = 1; i < elementSize; i++) {
						tmpChannel += short(element[i] - 48) *  pow(10, (elementSize - i - 1));
					}
				}
				else if (elementIndex == 5) {   //  fromId
					for (int i = 1; i < elementSize; i++) {
						tmpCrossFrom += short(element[i] - 48) *  pow(10, (elementSize - i - 1));
					}
				}
				else if (elementIndex == 6) {   //  toId
					for (int i = 1; i < elementSize; i++) {
						tmpCrossTo += short(element[i] - 48) *  pow(10, (elementSize - i - 1));
					}
				}
				else if (elementIndex == 7) {   //  isDuplex
					for (int i = 1; i < elementSize - 1; i++) {
						tmpisDuplex += short(element[i] - 48) *  pow(10, (elementSize - i - 2));
					}
				}
			}//建立地图
			if (tmpisDuplex == true) {
				G.setLength(tmpLength, tmpCrossTo, tmpCrossFrom);
				G.setSpeed(tmpSpeed, tmpCrossTo, tmpCrossFrom);
				G.setChannel(tmpChannel, tmpCrossTo, tmpCrossFrom);
				G.setRoadID(tmpRoadID, tmpCrossTo,tmpCrossFrom);
				G.setIsDuplex(tmpisDuplex, tmpCrossTo, tmpCrossFrom);
			}
			else if(tmpisDuplex == false){
				short tmpFuYi = -1;
				G.setLength(tmpFuYi, tmpCrossTo, tmpCrossFrom);
			}
			G.setRoadID(tmpRoadID, tmpCrossFrom, tmpCrossTo);
			G.setLength(tmpLength, tmpCrossFrom, tmpCrossTo);
			G.setSpeed(tmpSpeed, tmpCrossFrom, tmpCrossTo);
			G.setChannel(tmpChannel, tmpCrossFrom, tmpCrossTo);
			G.setIsDuplex(tmpisDuplex, tmpCrossFrom, tmpCrossTo);
			road tmpRoad(tmpRoadID, tmpLength, tmpSpeed, tmpChannel, tmpCrossFrom, tmpCrossTo, tmpisDuplex);
			roadVec.push_back(tmpRoad);
		}
	}
	else cout << "no road.txt file" << endl;

	in_road.close();

	if (in_car) // 有cross文件  
	{
		string line;
		short tmpCarId = 0;
		short tmpCarSpeed = 0;
		short tmpCarFrom = 0;
		short tmpCarTo = 0;
		short tmpPlanTime = 0;
		while (getline(in_car, line)) // line中不包括每行的换行符  
		{
			tmpCarId = 0;
			tmpCarSpeed = 0;
			tmpCarFrom = 0;
			tmpCarTo = 0;
			tmpPlanTime = 0;
			//cout << line << endl;
			if (line[0] == '#')
				continue;
			istringstream stream(line);
			string element;
			short elementIndex = 0;
			while (getline(stream, element, ',')) {
				++elementIndex;
				int tmp = 0;
				int elementSize = element.size();
				if (elementIndex == 1) {   //  id
					for (int i = 1; i < elementSize; i++) {
						tmpCarId += short(element[i] - 48) *  pow(10, (elementSize - i - 1));
					}
				}else if (elementIndex == 2) {   //  from
					for (int i = 1; i < elementSize; i++) {
						tmpCarFrom += short(element[i] - 48) *  pow(10, (elementSize - i - 1));
					}
				}
				else if (elementIndex == 3) {   //  to
					for (int i = 1; i < elementSize; i++) {
						tmpCarTo += short(element[i] - 48) *  pow(10, (elementSize - i - 1));
					}
				}
				else if (elementIndex == 4) {   //  speed
					for (int i = 1; i < elementSize; i++) {
						tmpCarSpeed += short(element[i] - 48) *  pow(10, (elementSize - i - 1));
					}
				}
				else if (elementIndex == 5) {   //  planTime
					for (int i = 1; i < elementSize - 1; i++) {   //注意这里是elementSize - 1，因为后面有右括号
						tmpPlanTime += short(element[i] - 48) *  pow(10, (elementSize - i - 2));
					}
				}
			}

			car tmpCar(tmpCarId, tmpCarFrom, tmpCarTo, tmpCarSpeed, tmpPlanTime);
			carVec.push_back(tmpCar);
		}
	}
	else cout << "no cross.txt file" << endl;

	in_car.close();

	//ofstream mycout("answer.txt");
	//mycout << "#(carId,StartTime,RoadId...)" << endl;

	systemInfo systemInformation(0);				//初始化系统时间为 0
	systemInformation.offLineCars = carVec.size();  //开始时为上路的车辆为所有车辆
	long actualTime = carVec[0].carPlanTime;
	//short driveTime = actualTime;
	for (int carIndex = 0; carIndex < carVec.size(); ++carIndex) {
		ShortestPath_DIJ(G, carVec[carIndex].carId, carVec[carIndex].carFrom, carVec[carIndex].carTo, carVec[carIndex].carSpeed);
		short trueRoadID = 0;
		short roadSpeend = 0;
		short roadLength = 0;
		short roadFromId = 0;
		short roadToId = 0;
		vector<short> roadLine;
		roadFromId = pathVec.top();
		pathVec.pop();
		roadToId = pathVec.top();
		trueRoadID = G.getRoadID(roadFromId, roadToId);//将路口ID转换为道路ID
		roadLine.push_back(trueRoadID);
		//mycout << "(" << carVec[carIndex].carId << ", " << driveTime << ", " << trueRoadID << ", ";
		while (pathVec.size() > 1) {
			roadSpeend = G.getSpeed(roadFromId, roadToId);
			roadLength = G.getLength(roadFromId, roadToId);
			//if (carVec[carIndex].carId > roadSpeend)
			//	driveTime += ceil((roadLength / (roadSpeend * 1.0)));
			//else
			//	driveTime += ceil((roadLength / (carVec[carIndex].carSpeed * 1.0)));
			roadFromId = roadToId;
			pathVec.pop();
			roadToId = pathVec.top();
			trueRoadID = G.getRoadID(roadFromId, roadToId);//将路口ID转换为道路ID
			roadLine.push_back(trueRoadID);
			//if (pathVec.size() > 1)
			//	mycout << trueRoadID << ", ";
			//else
			//	mycout << trueRoadID << ")";

		}
		while (pathVec.size()) pathVec.pop();
		//mycout << endl;
		answer answerTmp(carVec[carIndex].carId, roadLine);
		answerVec.push_back(answerTmp);

	}	

	short firstRoadId = roadVec[0].roadId;
	short firstCarId = carVec[0].carId;
	short firstCrossId = crossVec[0].crossId;
	short firstAnswerId = answerVec[0].answerCarId;

	//将car,road,cross,answer的起点id归零
	for (int i = 0; i < roadVec.size(); ++i) {
		roadVec[i].roadId = roadVec[i].roadId - firstRoadId;
		roadVec[i].roadToId = roadVec[i].roadToId - firstCrossId;
		roadVec[i].roadFromId = roadVec[i].roadFromId - firstCrossId;
	}

	for (int i = 0; i < carVec.size(); ++i) {
		carVec[i].carId = carVec[i].carId - firstCarId;
		carVec[i].carFrom = carVec[i].carFrom - firstCrossId;
		carVec[i].carTo = carVec[i].carTo - firstCrossId;
	}

	for (int i = 0; i < crossVec.size(); ++i) {
		crossVec[i].crossId = crossVec[i].crossId - firstCrossId;
		if (crossVec[i].fourRoadAtCross[0] != -1) crossVec[i].fourRoadAtCross[0] = crossVec[i].fourRoadAtCross[0] - firstRoadId;
		if (crossVec[i].fourRoadAtCross[1] != -1) crossVec[i].fourRoadAtCross[1] = crossVec[i].fourRoadAtCross[1] - firstRoadId;
		if (crossVec[i].fourRoadAtCross[2] != -1) crossVec[i].fourRoadAtCross[2] = crossVec[i].fourRoadAtCross[2] - firstRoadId;
		if (crossVec[i].fourRoadAtCross[3] != -1) crossVec[i].fourRoadAtCross[3] = crossVec[i].fourRoadAtCross[3] - firstRoadId;
	}

	for (int i = 0; i < answerVec.size(); ++i) {
		answerVec[i].answerCarId = answerVec[i].answerCarId - firstAnswerId;
		for (int j = 0; j < answerVec[i].roadLine.size(); ++j)
			answerVec[i].roadLine[j] = answerVec[i].roadLine[j] - firstRoadId;
	}
	//mycout.close();	//关闭answer.txt文档
	//0时刻，将所有车辆初始化，进入道路的等待区，更新进入等待区的的车辆的开始时间
	for (int i = 0; i < answerVec.size(); ++i) {
		short carCurrRoadId = answerVec[i].roadLine[0];
		if (roadVec[carCurrRoadId].roadState != -1) {
			answerVec[i].carOnWhichRoad = carCurrRoadId;
			roadVec[carCurrRoadId].updateRoadWaitingArea(carVec[i].carId);//0时刻，车辆id从小到大遍历车辆，如果车辆对应的车道空缺则进入
			answerVec[i].startTime = carVec[i].carPlanTime;	//车辆开始计时,此时间点不得早于车辆的计划出发时间
			if(answerVec[i].startTime > 0) 
				answerVec[i].carState = -1;  //车辆进入等待状态，此时还未出发
			else 
				answerVec[i].carState = 1;  //如果车辆的planTime未0，则标记为开始调度
			//车辆行驶的最大速度
			if (carVec[i].carSpeed <= roadVec[carCurrRoadId].roadSpeed)
				answerVec[i].currCarSpeed = carVec[i].carSpeed;
			else
				answerVec[i].currCarSpeed = roadVec[carCurrRoadId].roadSpeed;
			//如果车辆下个路口就是终点
			if (answerVec[i].roadLine.size() == 1) {
				answerVec[i].nextCrossDirection = ENDPOINT;
				continue;
			}
			//下个路口不是终点
			for (int k = 0; k < 4; ++k) {
				for (int j = 0; j < 4; ++j) {
					if (crossVec[roadVec[carCurrRoadId].roadFromId].fourRoadAtCross[k] = crossVec[roadVec[carCurrRoadId].roadToId].fourRoadAtCross[j]) {
						if (k == j) answerVec[i].nextCrossDirection = STRAIGHT;
						else if((k -j)==-3 || (k - j) == 1) answerVec[i].nextCrossDirection = LEFT;
						else if ((k - j) == 3 || (k - j) == -1) answerVec[i].nextCrossDirection = RIGHT;
					}
				}

			}
		}
		//根据下一道路id，得出车辆在下一路口的方向 
	}

	while (++systemInformation.systmeTime) {
		//遍历所有道路对应的车道,更新车辆的位置及状态
		for (int i = 0; i < roadVec.size(); ++i) {
			//车道上所有车辆向前移动
			for (int j = 0; j < roadVec[i].roadChannel; ++j) {
				for 
					(int k = 0; k < roadVec[i].roadInfo.size(); ++k) {
					roadVec[i].roadInfo.front();//车道中的头车
				}

			}
		}
	}
	return 0;

}