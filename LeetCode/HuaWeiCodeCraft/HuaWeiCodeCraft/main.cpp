#include <string>  
#include <iostream> 
#include <sstream>
#include <stack>
#include <vector>
#include <fstream>  //ofstream���ͷ�ļ�

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
bool S[MAX_V];		//��¼��Դ��V0���յ�Vi�Ƿ��Ѿ�ȷ��Ϊ���·����ȷ���˼�true�������false
short Path[MAX_V];	//��¼��Դ��V0���յ�Vi�ĵ�ǰ���·�����յ�Vi��ֱ��ǰ��������ţ���V0��Vi֮���б�ǰ��ΪV0����Ϊ-1 
short D[MAX_V];		//��¼Դ�㵽�յ�֮�����·���ĳ��ȣ����ڼ�V0��Vi�ıߵ�Ȩֵ�������ΪMAX 
stack<int> pathVec;	//��Ϊ·���Ǵ��յ����ص��Ƶģ����Դ˴�ʹ��ջ������·��
void ShortestPath_DIJ(GraphMatrix & G, short id, short v0, short endV, short speed)
{
	memset(S, 0, sizeof(S));
	memset(Path, 0, sizeof(Path));
	memset(D, 0, sizeof(D));
	for (short i = 0; i < G.get_v(); i++) {
		S[i] = false;				//S��ʼ��Ϊ�ռ�
		D[i] = G.getLength(v0, i);	//��v0�������յ�����·�����ȳ�ʼ��Ϊ���ϵ�Ȩֵ
		if	(D[i] > 0) Path[i] = v0;	//���v0��v֮���бߣ���v��ǰ����ʼ��Ϊv0
		else	Path[i] = -1;		//���v0��v֮���ޱߣ���v��ǰ����ʼ��Ϊ-1
	}
	S[v0] = true;	//��v0����s
	D[v0] = 0;		//Դ�㵽Դ���ȨֵΪ0
	
	//---------��ʼ����������ʼ��ѭ����ÿ�����v0��ĳ����������·������v�ӵ�S����
	for (short i = 1; i < G.get_v() + 1; i++) {

		int min = MAX;
		short v = v0;
		for (short w = 0; w < G.get_v() + 1; w++)
		{
			if (!S[w] && (D[w] > 0 && D[w] <min))
			{//ѡ��һ����ǰ���·�����յ�Ϊv
				v = w;
				min = D[w];
			}
		}
		S[v] = true;//��v�ӵ�s������
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
		{//���´�v0����������V-S�����ж�������·������
			if (!S[w] && (G.getLength(v,w) > 0))
			{
				D[w] = D[v] + G.getLength(v, w);//����D[w]
				Path[w] = v0;//����w��ǰ��Ϊv0

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
	

	if (in_cross) // ��cross�ļ�  
	{
		string line;
		while (getline(in_cross, line)) // line�в�����ÿ�еĻ��з�  
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

	if (in_road) // ��road�ļ�  
	{
		string line;
		while (getline(in_road, line)) // line�в�����ÿ�еĻ��з�   cout << line << endl;
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
				else if (elementIndex == 2) {   //  ����" 15"    int 15�ļ���,�˴�����length
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
			}//������ͼ
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

	if (in_car) // ��cross�ļ�  
	{
		string line;
		short tmpCarId = 0;
		short tmpCarSpeed = 0;
		short tmpCarFrom = 0;
		short tmpCarTo = 0;
		short tmpPlanTime = 0;
		while (getline(in_car, line)) // line�в�����ÿ�еĻ��з�  
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
					for (int i = 1; i < elementSize - 1; i++) {   //ע��������elementSize - 1����Ϊ������������
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

	systemInfo systemInformation(0);				//��ʼ��ϵͳʱ��Ϊ 0
	systemInformation.offLineCars = carVec.size();  //��ʼʱΪ��·�ĳ���Ϊ���г���
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
		trueRoadID = G.getRoadID(roadFromId, roadToId);//��·��IDת��Ϊ��·ID
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
			trueRoadID = G.getRoadID(roadFromId, roadToId);//��·��IDת��Ϊ��·ID
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

	//��car,road,cross,answer�����id����
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
	//mycout.close();	//�ر�answer.txt�ĵ�
	//0ʱ�̣������г�����ʼ���������·�ĵȴ��������½���ȴ����ĵĳ����Ŀ�ʼʱ��
	for (int i = 0; i < answerVec.size(); ++i) {
		short carCurrRoadId = answerVec[i].roadLine[0];
		if (roadVec[carCurrRoadId].roadState != -1) {
			answerVec[i].carOnWhichRoad = carCurrRoadId;
			roadVec[carCurrRoadId].updateRoadWaitingArea(carVec[i].carId);//0ʱ�̣�����id��С����������������������Ӧ�ĳ�����ȱ�����
			answerVec[i].startTime = carVec[i].carPlanTime;	//������ʼ��ʱ,��ʱ��㲻�����ڳ����ļƻ�����ʱ��
			if(answerVec[i].startTime > 0) 
				answerVec[i].carState = -1;  //��������ȴ�״̬����ʱ��δ����
			else 
				answerVec[i].carState = 1;  //���������planTimeδ0������Ϊ��ʼ����
			//������ʻ������ٶ�
			if (carVec[i].carSpeed <= roadVec[carCurrRoadId].roadSpeed)
				answerVec[i].currCarSpeed = carVec[i].carSpeed;
			else
				answerVec[i].currCarSpeed = roadVec[carCurrRoadId].roadSpeed;
			//��������¸�·�ھ����յ�
			if (answerVec[i].roadLine.size() == 1) {
				answerVec[i].nextCrossDirection = ENDPOINT;
				continue;
			}
			//�¸�·�ڲ����յ�
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
		//������һ��·id���ó���������һ·�ڵķ��� 
	}

	while (++systemInformation.systmeTime) {
		//�������е�·��Ӧ�ĳ���,���³�����λ�ü�״̬
		for (int i = 0; i < roadVec.size(); ++i) {
			//���������г�����ǰ�ƶ�
			for (int j = 0; j < roadVec[i].roadChannel; ++j) {
				for 
					(int k = 0; k < roadVec[i].roadInfo.size(); ++k) {
					roadVec[i].roadInfo.front();//�����е�ͷ��
				}

			}
		}
	}
	return 0;

}