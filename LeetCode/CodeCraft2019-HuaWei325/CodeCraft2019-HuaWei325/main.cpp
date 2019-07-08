#include <string>  
#include <iostream> 
#include <sstream>
#include <fstream>

#include <vector>
#include "element.h"

std::vector<road> roadVector;
std::vector<cross> crossVector;
std::vector<car> carVector;
std::vector<car> answerVector;
systemInfo System;

int firstRoadID = 9999;
int firstCrossID = 9999;
int firstCarID = 9999;
int firstAnswerID = 9999;


int StringSplit(std::vector<std::string> &dst, const std::string &src, const std::string &separator) {
	if (src.empty() || separator.empty())
		return 0;

	int nCount = 0;
	std::string temp;
	size_t pos = 0, offset = 0;

	// �ָ��1~n-1��
	while ((pos = src.find_first_of(separator, offset)) != std::string::npos) {
		temp = src.substr(offset, pos - offset);
		if (temp.length() > 0) {
			dst.push_back(temp);
			nCount++;
		}
		offset = pos + 1;
	}

	// �ָ��n��
	temp = src.substr(offset, src.length() - offset);
	if (temp.length() > 0) {
		dst.push_back(temp);
		nCount++;
	}

	return nCount;
}

int getMin(int a, int b) {
	return a < b ? a : b;
}

std::vector<nextMove> getNextPossibleMove(int thisRoadID, int thisRoadOri) {
	std::vector<nextMove> nextmove;

	int thisCrossID = roadVector[thisRoadID].getSimplexRoadEndCrossID(thisRoadOri);
	for (int i = 0; i < crossVector[thisCrossID].NumOfOutRoads; i++) {
		int nextRoadID = crossVector[thisCrossID].sortedOutRoadIDList[i];
		if (nextRoadID != thisRoadID) {
			nextMove tmp;
			tmp.roadID = nextRoadID;
			if (roadVector[nextRoadID].getStartCrossID() == thisCrossID) {
				tmp.crossID = roadVector[nextRoadID].getEndCrossID();
			}
			else {
				tmp.crossID = roadVector[nextRoadID].getStartCrossID();
			}
			nextmove.push_back(tmp);

		}
	}

	if (nextmove.size() == 0) {
		std::cout << "[INFO] No road to exit." << '\n';
	}

	return nextmove;

};

CarPlan getNextStepPlan(int thisRoadID, int thisRoadOri, nextMove move) {
	CarPlan plan;
	plan.roadID = thisRoadID;
	plan.orientation = thisRoadOri;
	if (roadVector[thisRoadID].getSimplexRoadNextRoadID(thisRoadOri, LEFT) == move.roadID) {
		plan.nextDirection = LEFT;
	}
	else if (roadVector[thisRoadID].getSimplexRoadNextRoadID(thisRoadOri, RIGHT) == move.roadID) {
		plan.nextDirection = RIGHT;
	}
	else if (roadVector[thisRoadID].getSimplexRoadNextRoadID(thisRoadOri, STRAIGHT) == move.roadID) {
		plan.nextDirection = STRAIGHT;
	}

	return plan;

}

int getRoadCarNum(int roadid, int ori) {
	int num = 0;
	for (int i = 0; i < roadVector[roadid].getLaneNum(); ++i) {
		for (int j = 0; j < roadVector[roadid].getRoadLength(); ++j) {
			if (roadVector[roadid].getGridState(ori, i, j) != -1) {
				num++;
			}
		}
	}
	return num;
}

void readRoadConfigFile(const std::string &path) {
	////////////////////////// �����·�ļ� road.txt //////////////////////////////

	std::ifstream configFileRoad(path);
	if (!configFileRoad.is_open()) {
		std::cout << "Fail to open files." << std::endl;
	}
	else {

		int lineNum = 0;
		std::string temp;
		std::vector<std::string> element;
		std::string separator(", ");

		while (getline(configFileRoad, temp)) {
			if (lineNum == 0) {
				lineNum++;
				continue;
			}

			temp.erase(temp.begin());
			temp.pop_back();

			StringSplit(element, temp, separator);

			int roadID = atoi(element[0].c_str());
			int len = atoi(element[1].c_str());
			int maxSpeed = atoi(element[2].c_str());
			int lane = atoi(element[3].c_str());
			int startpoint = atoi(element[4].c_str());
			int endpoint = atoi(element[5].c_str());
			int isDuplex = atoi(element[6].c_str());

			// ��¼�׸�·�ڵ�ID
			if (lineNum == 1) {
				firstRoadID = roadID;
			}

			element.clear();

			lineNum++;

			road tmp(roadID, isDuplex, len, lane, startpoint, endpoint, maxSpeed);
			roadVector.push_back(tmp);
		}

		configFileRoad.close();
	}

	std::cout << "Size of RoadVector: " << roadVector.size() << '\n';
}

void readCrossConfigFile(const std::string &path) {
	std::ifstream configFileCross(path);
	if (!configFileCross.is_open()) {
		std::cout << "Fail to open files." << std::endl;
	}
	else {

		int lineNum = 0;
		std::string temp;
		std::vector<std::string> element;
		std::string separator(", ");

		while (getline(configFileCross, temp)) {
			if (lineNum == 0) {
				lineNum++;
				continue;
			}

			temp.erase(temp.begin());
			temp.pop_back();

			StringSplit(element, temp, separator);

			int crossID = atoi(element[0].c_str());
			int r1 = atoi(element[1].c_str());
			int r2 = atoi(element[2].c_str());
			int r3 = atoi(element[3].c_str());
			int r4 = atoi(element[4].c_str());

			if (lineNum == 1) {
				firstCrossID = crossID;
			}

			element.clear();

			cross tmp(crossID, r1, r2, r3, r4);
			crossVector.push_back(tmp);

			lineNum++;
		}

		configFileCross.close();
	}

	std::cout << "Size of CrossVector: " << crossVector.size() << '\n';
}

void readCarConfigFile(const std::string &path) {

	std::ifstream configFileCar(path);
	if (!configFileCar.is_open()) {
		std::cout << "Fail to open files." << std::endl;
	}
	else {

		int lineNum = 0;
		std::string temp;
		std::vector<std::string> element;
		std::string separator(", ");

		while (getline(configFileCar, temp)) {
			if (lineNum == 0) {
				lineNum++;
				continue;
			}

			temp.erase(temp.begin());
			temp.pop_back();

			StringSplit(element, temp, separator);

			int carID = atoi(element[0].c_str());
			int startpoint = atoi(element[1].c_str());
			int endpoint = atoi(element[2].c_str());
			int maxSpeed = atoi(element[3].c_str());
			int planTime = atoi(element[4].c_str());

			if (lineNum == 1) {
				firstCarID = carID;
			}

			element.clear();

			car tmp(carID, maxSpeed, startpoint, endpoint, planTime);
			carVector.push_back(tmp);

			lineNum++;
		}

		configFileCar.close();
	}

	std::cout << "Size of CarVector: " << carVector.size() << '\n';
}

void readAnswerFiles(const std::string &path) {
	std::ifstream configFileAnswer(path);
	if (!configFileAnswer.is_open()) {
		std::cout << "Fail to open files." << std::endl;
	}
	else {

		int lineNum = 0;
		std::string temp;
		std::vector<std::string> element;
		std::string separator(", ");
		while (getline(configFileAnswer, temp)) {
			if (lineNum == 0) {
				lineNum++;
				continue;
			}

			temp.erase(temp.begin());
			temp.pop_back();

			StringSplit(element, temp, separator);

			if (lineNum == 1) {
				firstAnswerID = atoi(element[0].c_str());
			}

			int carID = -1;
			int i = 0;

			while (i < element.size()) {
				if (i == 0) {
					carID = atoi(element[i].c_str()) - firstAnswerID;
				}
				else if (i == 1) {
					carVector[lineNum - 1].PlannedTime = atoi(element[i].c_str());
				}
				else {
					if (carID == carVector[lineNum - 1].ID) {
						CarPlan tmpcarplan;
						tmpcarplan.roadID = atoi(element[i].c_str()) - firstRoadID;
						tmpcarplan.orientation = -1;
						tmpcarplan.nextDirection = -1;
						carVector[lineNum - 1].pushCarPlan(tmpcarplan); // push plan.
					}
					else {
						std::cout << "[Error] CarID conflicts." << std::endl;
						exit(14);
					}
				}

				++i;
			}

			lineNum++;

			element.clear();
		}

		configFileAnswer.close();

		if (lineNum != carVector.size() + 1) {
			std::cout << "[ERROR] Unplanned Car" << std::endl;
			exit(13);
		}
	}

	// ���³����滮����
	for (int i = 0; i < carVector.size(); ++i) {
		int sp = carVector[i].StartPoint;
		int planSize = carVector[i].Plan.size();
		if (planSize < 1) {
			std::cout << "[WARNING] CAR " << carVector[i].ID << " doesn't need to be planned?" << '\n';
			continue;
		}

		// �����ʼ·��
		int firstRoadid = carVector[i].Plan[0].roadID;
		if (sp == roadVector[firstRoadid].getStartCrossID()) {
			carVector[i].Plan[0].orientation = 0;
		}
		else if (sp == roadVector[firstRoadid].getEndCrossID()) {
			carVector[i].Plan[0].orientation = 1;
		}
		else {
			std::cout << "[ERROR] CAR " << carVector[i].ID << " & cross unmatched1." << '\n';
			exit(12);
		}

		// �������·��
		int iter = 1;
		while (iter < planSize) {
			int thisRoadID = carVector[i].Plan[iter].roadID;
			int lastRoadID = carVector[i].Plan[iter - 1].roadID;
			int lastRoadOrientation = carVector[i].Plan[iter - 1].orientation;
			if (thisRoadID == roadVector[lastRoadID].getSimplexRoadNextRoadID(lastRoadOrientation, LEFT)) {
				carVector[i].Plan[iter - 1].nextDirection = LEFT;
			}
			else if (thisRoadID == roadVector[lastRoadID].getSimplexRoadNextRoadID(lastRoadOrientation, STRAIGHT)) {
				carVector[i].Plan[iter - 1].nextDirection = STRAIGHT;
			}
			else if (thisRoadID == roadVector[lastRoadID].getSimplexRoadNextRoadID(lastRoadOrientation, RIGHT)) {
				carVector[i].Plan[iter - 1].nextDirection = RIGHT;
			}
			else {
				std::cout << "[ERROR] CAR " << carVector[i].ID << " & cross unmatched2." << '\t' << lastRoadID << '\n';
				exit(12);
			}

			int thisCrossID = roadVector[lastRoadID].getSimplexRoadEndCrossID(lastRoadOrientation); //�൱��sp
			if (thisCrossID == roadVector[thisRoadID].getStartCrossID()) {
				carVector[i].Plan[iter].orientation = 0;
			}
			else if (thisCrossID == roadVector[thisRoadID].getEndCrossID()) {
				carVector[i].Plan[iter].orientation = 1;
			}
			else {
				std::cout << "[ERROR] CAR " << carVector[i].ID << " & cross unmatched3." << '\n';
				exit(12);
			}

			iter++;
		}
	}
}

void updateMapIDInfo() {
	/////// ��ȥ�� ID,�õ��µ���0��ʼ��ID��Ϊ���� ////////////////
	for (int i = 0; i < roadVector.size(); ++i) {
		roadVector[i].updateRoadID(firstRoadID);
		roadVector[i].updateCrossID(firstCrossID);
	}
	for (int i = 0; i < crossVector.size(); ++i) {
		crossVector[i].updateRoadID(firstRoadID);
		crossVector[i].updateCrossID(firstCrossID);
	}
	for (int i = 0; i < carVector.size(); ++i) {
		carVector[i].updateCarID(firstCarID);
		carVector[i].updateCrossID(firstCrossID);
	}

	/////// ����cross�ļ��е������ĳһ·�ڵĽ����·�ڵĵ�·id������ ////////////////

	for (int i = 0; i < crossVector.size(); ++i) {
		crossVector[i].sortRoadID();
		for (int k = 0; k < crossVector[i].getNumOfRoads(); ++k) {
			int eachRoadID = crossVector[i].sortedRoadIDList[k];
			if (roadVector[eachRoadID].isDuplex()) {
				crossVector[i].sortedInRoadIDList.push_back(eachRoadID);
				crossVector[i].NumOfInRoads++;
				crossVector[i].sortedOutRoadIDList.push_back(eachRoadID);
				crossVector[i].NumOfOutRoads++;
			}
			else {
				if (roadVector[eachRoadID].getEndCrossID() == crossVector[i].getCrossID()) {
					crossVector[i].sortedInRoadIDList.push_back(eachRoadID);
					crossVector[i].NumOfInRoads++;
				}
				else if (roadVector[eachRoadID].getStartCrossID() == crossVector[i].getCrossID()) {
					crossVector[i].sortedOutRoadIDList.push_back(eachRoadID);
					crossVector[i].NumOfOutRoads++;
				}
			}
		}

		///// Display /////////////////////
		for (int k = 0; k < 4; ++k) {
			std::cout << crossVector[i].getRoadIDSet(k) << '\t';
		}
		std::cout << '\t';
		for (int k = 0; k < crossVector[i].getNumOfRoads(); ++k) {
			int eachRoadID = crossVector[i].sortedRoadIDList[k];
			std::cout << eachRoadID << '\t';
		}
		std::cout << '\t' << '\t' << '\t';
		for (int k = 0; k < crossVector[i].NumOfInRoads; ++k) {
			int eachRoadID = crossVector[i].sortedInRoadIDList[k];
			std::cout << eachRoadID << '\t';
		}
		std::cout << '\n';
		/////////////////////////////////////
	}
}

void buildMap() {
	////////////////////////// ����ȫ�ֵ�ͼ��ϵ //////////////////////////////

	DynamicArray roadConnectionInfo(crossVector.size(), crossVector.size());
	for (int i = 0; i < roadVector.size(); ++i) {
		int tmpx = roadVector[i].getStartCrossID();
		int tmpy = roadVector[i].getEndCrossID();
		if (roadVector[i].isDuplex()) {
			roadConnectionInfo.setValue(tmpx, tmpy, roadVector[i].getRoadID());
			roadConnectionInfo.setValue(tmpy, tmpx, roadVector[i].getRoadID());
		}
		else {
			roadConnectionInfo.setValue(tmpx, tmpy, roadVector[i].getRoadID());
		}
	}

	//    roadConnectionInfo.displayArray();

	// ��д��һ·�ڵĸ���·����Է���
	for (int i = 0; i < roadVector.size(); ++i) { //60
		if (roadVector[i].isDuplex()) {
			// road0  roadEnd dirction
			int tmpCrossID = roadVector[i].getEndCrossID();
			for (int j = 0; j < crossVector.size(); ++j) { // 36
				int tmpNextRoadID = roadConnectionInfo.getValue((tmpCrossID), j);
				//				int tmpNextRoadID;
				if (tmpNextRoadID < 0) { //û��·
					continue;
				}
				else {
					int ptr_self = 999;
					int ptr_next = 999;
					for (int k = 0; k < 4; ++k) {   //tmpSetID Ϊ endCross���ĸ�����ĵ�·
						int tmpSetID = crossVector[tmpCrossID].getRoadIDSet(k);
						if (tmpSetID == roadVector[i].getRoadID()) {
							ptr_self = k;
						}
						else if (tmpSetID == tmpNextRoadID) {
							ptr_next = k;
						}
					}

					if ((ptr_next - ptr_self) == -1 || (ptr_next - ptr_self) == 3) {
						roadVector[i].setSimplexRoadNextRoadID(0, RIGHT, tmpNextRoadID);
					}
					else if ((ptr_next - ptr_self) == -2 || (ptr_next - ptr_self) == 2) {
						roadVector[i].setSimplexRoadNextRoadID(0, STRAIGHT, tmpNextRoadID);
					}
					else if ((ptr_next - ptr_self) == -3 || (ptr_next - ptr_self) == 1) {
						roadVector[i].setSimplexRoadNextRoadID(0, LEFT, tmpNextRoadID);
					}
				}
			}

			//road1
			tmpCrossID = roadVector[i].getStartCrossID();
			for (int j = 0; j < crossVector.size(); ++j) { // 36
				int tmpNextRoadID = roadConnectionInfo.getValue((tmpCrossID), j);
				if (tmpNextRoadID < 0) { //û��·
					continue;
				}
				else {
					int ptr_self = 999;
					int ptr_next = 999;
					for (int k = 0; k < 4; ++k) {
						int tmpSetID = crossVector[tmpCrossID].getRoadIDSet(k);
						if (tmpSetID == roadVector[i].getRoadID()) {
							ptr_self = k;
						}
						else if (tmpSetID == tmpNextRoadID) {
							ptr_next = k;
						}
					}

					/// ˳ʱ��
					if ((ptr_next - ptr_self) == -1 || (ptr_next - ptr_self) == 3) {
						roadVector[i].setSimplexRoadNextRoadID(1, RIGHT, tmpNextRoadID);
					}
					else if ((ptr_next - ptr_self) == -2 || (ptr_next - ptr_self) == 2) {
						roadVector[i].setSimplexRoadNextRoadID(1, STRAIGHT, tmpNextRoadID);
					}
					else if ((ptr_next - ptr_self) == -3 || (ptr_next - ptr_self) == 1) {
						roadVector[i].setSimplexRoadNextRoadID(1, LEFT, tmpNextRoadID);
					}
				}
			}
		}
		else {
			int tmpCrossID = roadVector[i].getEndCrossID();
			for (int j = 0; j < crossVector.size(); ++j) { // 36
				int tmpNextRoadID = roadConnectionInfo.getValue((tmpCrossID), j);
				if (tmpNextRoadID < 0) { //û��·
					continue;
				}
				else {
					int ptr_self = 999;
					int ptr_next = 999;
					for (int k = 0; k < 4; ++k) {
						int tmpSetID = crossVector[tmpCrossID].getRoadIDSet(k);
						if (tmpSetID == roadVector[i].getRoadID()) {
							ptr_self = k;
						}
						else if (tmpSetID == tmpNextRoadID) {
							ptr_next = k;
						}
					}

					if ((ptr_next - ptr_self) == -1 || (ptr_next - ptr_self) == 3) {
						roadVector[i].setSimplexRoadNextRoadID(0, RIGHT, tmpNextRoadID);
					}
					else if ((ptr_next - ptr_self) == -2 || (ptr_next - ptr_self) == 2) {
						roadVector[i].setSimplexRoadNextRoadID(0, STRAIGHT, tmpNextRoadID);
					}
					else if ((ptr_next - ptr_self) == -3 || (ptr_next - ptr_self) == 1) {
						roadVector[i].setSimplexRoadNextRoadID(0, LEFT, tmpNextRoadID);
					}
				}
			}
		}
	}
}

void updateState(systemInfo *&system) {

	system->updateTime();
	std::cout << "/------- SystemTime: " << system->getTime() << " Start -------\\" << '\n';


	if (system->getOnlineCarNum() > 0) {
		/// ��һ�������ȵ�����·�ϵĳ��� ///////////
		for (int i = 0; i < roadVector.size(); ++i) // ��·id����
		{
			int thisRoadSpeedLimit = roadVector[i].getRoadMaxSpeed();

			//////// ���򳵵� & ˫�򳵵���road0
			for (int j = 0; j < roadVector[i].getRoadLength(); ++j) //��һ(0)�ŵ����һ��
			{
				for (int k = 0; k < roadVector[i].getLaneNum(); ++k) //��һ(0)��������󳵵�
				{
					int thisCarID = roadVector[i].getGridState(0, k, j);
					int thisCarSpeedLimit = carVector[thisCarID].MaxCarSpeed;
					if (thisCarID != -1) //�жϵ�ǰ��������û�г�
					{
						// ��ȡ��������Ϣ��������һ�����򣬵�ǰ���ó��٣�����λ��
						// int planStep=carVector[thisCarID].PlanStep;
						// int ori=carVector[thisCarID].Plan[planStep].orientation;
						// int nextDir=carVector[thisCarID].Plan[planStep].nextDirection;
						// int speedlimit=carVector[thisCarID].Plan[planStep].thisRoadSpeedLimit;
						int speedlimit =
							thisCarSpeedLimit < thisRoadSpeedLimit ? thisCarSpeedLimit : thisRoadSpeedLimit;

						//�ж��ܷ��·�ڣ�
						bool exitRoadFlag = false;
						if (j - speedlimit < 0) {
							exitRoadFlag = true;
						}

						// �ж�ǰ���Ƿ����赲��
						bool blockFlag = false;
						int distToFrontCar = -1; // ��ǰ������
						int stopCarID = -1;
						for (int p = j - 1; p >= 0; --p) //�Ӻ���ǰѰ�ұ����������ǰ��λ��
						{
							if (roadVector[i].getGridState(0, k, p) != -1) {
								distToFrontCar = j - p;
								if (distToFrontCar <= speedlimit) //���赲��������������������������Attention
								{
									stopCarID = roadVector[i].getGridState(0, k, j - distToFrontCar);
									blockFlag = true;
								}
								break;
							}
						}


						if (!blockFlag) //û���赲
						{

							if (exitRoadFlag) //���Գ�·��
							{
								//���Ϊ�ȴ�����
								carVector[thisCarID].CarState = 1;
							}
							else //���ܳ�·��
							{
								//���Ϊ��ֹ״̬��ȷ����ֹλ��
								carVector[thisCarID].CarState = 0;
								// ���³����б��е���Ϣ
								carVector[thisCarID].presentPosition.laneID = k;
								carVector[thisCarID].presentPosition.orientation = 0;
								carVector[thisCarID].presentPosition.positionID = j - speedlimit;
								carVector[thisCarID].presentPosition.roadID = roadVector[i].getRoadID();
								// ���µ�·��ͼ�б��е���Ϣ
								roadVector[i].changeGridState(0, k, j, -1);
								roadVector[i].changeGridState(0, k, j - speedlimit, thisCarID);
							}
						}
						else //���赲
						{
							if (carVector[stopCarID].CarState == 1) //�赲�ĳ��ǵȴ�����
							{
								//���Ϊ�ȴ�����
								carVector[thisCarID].CarState = 1;
							}
							else //�赲�ĳ�����ֹ״̬����
							{
								//���Ϊ��ֹ״̬��ȷ����ֹλ��
								carVector[thisCarID].CarState = 0;
								// ���³����б��е���Ϣ
								carVector[thisCarID].presentPosition.laneID = k;
								carVector[thisCarID].presentPosition.orientation = 0;
								carVector[thisCarID].presentPosition.positionID =
									j - distToFrontCar + 1; // Attention!!!!!!!!!!!!!!!!!!!!!
								carVector[thisCarID].presentPosition.roadID = roadVector[i].getRoadID();
								// ���µ�·��ͼ�б��е���Ϣ
								roadVector[i].changeGridState(0, k, j, -1);
								roadVector[i].changeGridState(0, k, j - distToFrontCar + 1, thisCarID);
							}
						}
					}
				} // lane1 �� lane n
			}     // ��һ�ŵ����һ��

				  // �ж��Ƿ���˫�򳵵���
			if (roadVector[i].isDuplex()) {
				////////// road1
				for (int j = 0; j < roadVector[i].getRoadLength(); ++j) //��һ(0)�ŵ����һ��
				{
					for (int k = 0; k < roadVector[i].getLaneNum(); ++k) //��һ(0)��������󳵵�
					{
						int thisCarID = roadVector[i].getGridState(1, k, j);
						int thisCarSpeedLimit = carVector[thisCarID].MaxCarSpeed;
						if (thisCarID != -1) //�жϵ�ǰ��������û�г�
						{
							// ��ȡ��������Ϣ��������һ�����򣬵�ǰ���ó��٣�����λ��
							// int planStep=carVector[thisCarID].PlanStep;
							// int ori=carVector[thisCarID].Plan[planStep].orientation;
							// int nextDir=carVector[thisCarID].Plan[planStep].nextDirection;
							// int speedlimit=carVector[thisCarID].Plan[planStep].thisRoadSpeedLimit;
							int speedlimit =
								thisCarSpeedLimit < thisRoadSpeedLimit ? thisCarSpeedLimit : thisRoadSpeedLimit;

							//�ж��ܷ��·�ڣ�
							bool exitRoadFlag = false;
							if (j - speedlimit < 0) {
								exitRoadFlag = true;
							}


							// �ж�ǰ���Ƿ����赲��
							// �ӱ������ĵ�һ�ſ�ʼ���Լ��������ҵ�����ĳ�
							bool blockFlag = false;
							int distToFrontCar = 1;
							int stopCarID = -1;
							for (int p = j - 1; p >= 0; --p) //�Ӻ���ǰѰ�ұ����������ǰ��λ��
							{
								if (roadVector[i].getGridState(1, k, p) != -1) {
									distToFrontCar = j - p;
									if (distToFrontCar <= speedlimit) //���赲��������������������������
									{
										stopCarID = roadVector[i].getGridState(1, k, j - distToFrontCar);
										blockFlag = true;
									}
									break;
								}
							}


							if (!blockFlag) //û���赲
							{
								if (exitRoadFlag) //���Գ�·��
								{
									//���Ϊ�ȴ�����
									carVector[thisCarID].CarState = 1;
								}
								else //���ܳ�·��
								{
									//���Ϊ��ֹ״̬��ȷ����ֹλ��
									carVector[thisCarID].CarState = 0;
									// ���³����б��е���Ϣ
									carVector[thisCarID].presentPosition.laneID = k;
									carVector[thisCarID].presentPosition.orientation = 1;
									carVector[thisCarID].presentPosition.positionID = j - speedlimit;
									carVector[thisCarID].presentPosition.roadID = roadVector[i].getRoadID();
									// ���µ�·��ͼ�б��е���Ϣ
									roadVector[i].changeGridState(1, k, j, -1);
									roadVector[i].changeGridState(1, k, j - speedlimit, thisCarID);
								}
							}
							else //���赲
							{
								if (carVector[stopCarID].CarState == 1) //�赲�ĳ��ǵȴ�����
								{
									//���Ϊ�ȴ�����
									carVector[thisCarID].CarState = 1;
								}
								else //�赲�ĳ�����ֹ״̬����
								{
									//���Ϊ��ֹ״̬��ȷ����ֹλ��
									carVector[thisCarID].CarState = 0;
									// ���³����б��е���Ϣ
									carVector[thisCarID].presentPosition.laneID = k;
									carVector[thisCarID].presentPosition.orientation = 1;
									carVector[thisCarID].presentPosition.positionID = j - distToFrontCar + 1;
									carVector[thisCarID].presentPosition.roadID = roadVector[i].getRoadID();
									// ���µ�·��ͼ�б��е���Ϣ
									roadVector[i].changeGridState(1, k, j, -1);
									roadVector[i].changeGridState(1, k, j - distToFrontCar + 1, thisCarID);
								}
							}
						}
					} // lane1 �� lane n
				}     // ��һ�ŵ����һ��
			}

		} //��һ��

		  /// �ڶ���������·�ڡ���·�д��ڵȴ�״̬�ĳ�����
		system->carNumInWaiting = 0;
		for (int i = 0; i < carVector.size(); ++i) {
			if (carVector[i].CarState == 1) {
				system->carNumInWaiting++;
			}
		}

		while (system->carNumInWaiting > 0) //���г���û����,���ڵȴ�״̬
		{

			for (int i = 0; i < crossVector.size(); ++i) // ��crossID����ѭ��ÿһ·��
			{
				int lastWaitingNum_cross = crossVector[i].carNumInWaiting;
				crossVector[i].carNumInWaiting = 0;
				for (int iter = 0; iter < carVector.size(); ++iter) {
					if (carVector[iter].CarState == 1) {
						int tmpRoadid = carVector[iter].presentPosition.roadID;
						int tmpRoadori = carVector[iter].presentPosition.orientation;
						if (roadVector[tmpRoadid].getSimplexRoadEndCrossID(tmpRoadori) ==
							crossVector[i].getCrossID()) {
							crossVector[i].carNumInWaiting++;
						}
					}
				}

				while (crossVector[i].carNumInWaiting > 0) {

					for (int j = 0; j < crossVector[i].NumOfInRoads; ++j) //������ѭ����·�ڵĵ�·
					{
						int thisRoadID = crossVector[i].sortedInRoadIDList[j];
						// �жϱ���·�����·��id�ķ���
						int thisRoadOri = 0;
						if (roadVector[thisRoadID].getStartCrossID() == crossVector[i].getCrossID()) {
							thisRoadOri = 1;
						}
						int thisRoadSpeedLimit = roadVector[thisRoadID].getRoadMaxSpeed();


						// ��road�����ȼ�˳��
						bool thisRoadBreakFlag = false;
						for (int k = 0; k < roadVector[thisRoadID].getRoadLength(); ++k) //����ѭ��
						{
							for (int m = 0; m < roadVector[thisRoadID].getLaneNum(); ++m) //������˳��ѭ��
							{
								int thisGridID = roadVector[thisRoadID].getGridState(thisRoadOri, m, k);
								if (thisGridID != -1 && carVector[thisGridID].CarState == 1) // ������ǰ��Ҫ���ȵĳ�
								{

									int thisCarSpeedLimit = carVector[thisGridID].MaxCarSpeed;
									int speedLimit = thisCarSpeedLimit < thisRoadSpeedLimit ? thisCarSpeedLimit
										: thisRoadSpeedLimit;

									// �жϱ�road��ǰ���������Ƿ����赲
									bool blockFlag = false;
									int distToFrontCar = 1; // ��ǰ������
									int stopCarID = -1;
									for (int q = k - 1; q >= 0; --q) {
										if (roadVector[thisRoadID].getGridState(thisRoadOri, m, q) != -1) {
											distToFrontCar = k - q;
											if (distToFrontCar <= speedLimit) //���赲����������������������������Attention
											{
												stopCarID = roadVector[thisRoadID].getGridState(thisRoadOri, m,
													k - distToFrontCar);
												blockFlag = true;
											}
											break;
										}
									}


									if (blockFlag) //���赲��������ζ��޷���·�ڣ��������۳�ͻ���⡣��ת��Ϊ��һ����(d)
									{

										//���Ϊ��ֹ״̬��ȷ����ֹλ��
										carVector[thisGridID].CarState = 0;
										// ���³����б��е���Ϣ
										carVector[thisGridID].presentPosition.laneID = m;
										carVector[thisGridID].presentPosition.orientation = thisRoadOri;
										carVector[thisGridID].presentPosition.positionID =
											k - distToFrontCar + 1; // Attention!!!!!!!!!!!!!!!!!!!!!
										carVector[thisGridID].presentPosition.roadID = thisRoadID;
										// ���µ�·��ͼ�б��е���Ϣ
										roadVector[thisRoadID].changeGridState(thisRoadOri, m, k, -1);
										roadVector[thisRoadID].changeGridState(thisRoadOri, m,
											k - distToFrontCar + 1, thisGridID);
									}
									else //���赲
									{

										// �ж��Ƿ���г��·�ڵ�Ǳ����
										if (speedLimit <= k) // �����ٶ����ޣ��޷����·�ڡ���ת��Ϊ��һ����(b)
										{
											//���Ϊ��ֹ״̬��ȷ����ֹλ��
											carVector[thisGridID].CarState = 0;
											// ���³����б��е���Ϣ
											carVector[thisGridID].presentPosition.laneID = m;
											carVector[thisGridID].presentPosition.orientation = thisRoadOri;
											carVector[thisGridID].presentPosition.positionID = k - speedLimit;
											carVector[thisGridID].presentPosition.roadID = thisRoadID;
											// ���µ�·��ͼ�б��е���Ϣ
											roadVector[thisRoadID].changeGridState(thisRoadOri, m, k, -1);
											roadVector[thisRoadID].changeGridState(thisRoadOri, m, k - speedLimit,
												thisGridID);
										}
										else //��ϣ�����·��
										{
											// Ѱ����һ��Ҫȥ��·��roadID������
											int thisPlanStep = carVector[thisGridID].PlanStep;
											int nextPlanStep = thisPlanStep + 1;

											if (nextPlanStep == carVector[thisGridID].Plan.size()) //û��ʣ��Ĺ滮���ѵ����յ�
											{
												if (roadVector[carVector[thisGridID].presentPosition.roadID].getSimplexRoadEndCrossID(
													carVector[thisGridID].presentPosition.orientation) ==
													carVector[thisGridID].EndPoint) {
													////////// �����յ��һϵ�в��� //////////////////////
													//���Ϊ��ֹ״̬��ȷ����ֹλ��
													carVector[thisGridID].CarState = 0;
													// ���³����б��е���Ϣ
													carVector[thisGridID].presentPosition.laneID = -2;
													carVector[thisGridID].presentPosition.orientation = -2;
													carVector[thisGridID].presentPosition.positionID = -2;
													carVector[thisGridID].presentPosition.roadID = -2;
													carVector[thisGridID].FinishedTime = system->getTime();
													carVector[thisGridID].PlanStep = -2;
													// ���µ�·��ͼ�б��е���Ϣ
													roadVector[thisRoadID].changeGridState(thisRoadOri, m, k, -1);
													// ϵͳ��Ϣ
													system->finishOneCar(thisGridID);
													std::cout << "[CAR INFO] Car " << thisGridID + 1
														<< " has reached the end." << '\n';
												}
												else {
													std::cout << "[ERROR] Car " << thisGridID + 1
														<< " has no next plan input." << '\n';
													exit(9);
												}
											}
											else {

												int nextRoadID = carVector[thisGridID].Plan[nextPlanStep].roadID;
												if (nextRoadID == carVector[thisGridID].Plan[thisPlanStep].roadID) {
													std::cout << "[ERROR] Car " << thisGridID + 1
														<< " has repeated plan input." << '\n';
													exit(8);
												}
												int nextRoadOri = 0;
												if (roadVector[nextRoadID].getEndCrossID() ==
													crossVector[i].getCrossID()) {
													nextRoadOri = 1;
												}

												int nextRoadSpeedLimit =
													thisCarSpeedLimit < roadVector[nextRoadID].getRoadMaxSpeed()
													? thisCarSpeedLimit
													: roadVector[nextRoadID].getRoadMaxSpeed();
												// speedLimit: ����·�ϵ��ۺ����٣�nextRoadSpeedLimit: ����·�ϵ��ۺ�����
												int restDist = k;
												//������·���ߵľ���
												int nextRoadExpectedDist =
													(getMin(speedLimit, nextRoadSpeedLimit) - restDist) > 0 ? (
														getMin(speedLimit, nextRoadSpeedLimit) - restDist)
													: 0;

												if (nextRoadExpectedDist == 0) //��������·�����٣���·��ʧ�ܣ�ͣ���˱���·��·�ڱ�Ե��
												{
													//���Ϊ��ֹ״̬��ȷ����ֹλ��
													carVector[thisGridID].CarState = 0;
													// ���³����б��е���Ϣ
													carVector[thisGridID].presentPosition.laneID = m;
													carVector[thisGridID].presentPosition.orientation = thisRoadOri;
													carVector[thisGridID].presentPosition.positionID = 0;
													carVector[thisGridID].presentPosition.roadID = thisRoadID;
													// ���µ�·��ͼ�б��е���Ϣ
													roadVector[thisRoadID].changeGridState(thisRoadOri, m, k, -1);
													roadVector[thisRoadID].changeGridState(thisRoadOri, m, 0,
														thisGridID);
												}
												else // ������Ϊ����·�����ٶ��޷����·��
												{
													//////////////// ׼��ͨ��·�ڣ���ʼ�жϳ�ͻ��//////////////////
													bool conflictFlag = false;

													if (carVector[thisGridID].Plan[thisPlanStep].nextDirection ==
														STRAIGHT) {
														conflictFlag = false;
													}
													else if (
														carVector[thisGridID].Plan[thisPlanStep].nextDirection ==
														LEFT) {
														int rightRoadID = roadVector[thisRoadID].getSimplexRoadNextRoadID(
															thisRoadOri, RIGHT);
														int rightRoadOri = 0;
														if (roadVector[rightRoadID].getStartCrossID() ==
															crossVector[i].getCrossID()) {
															rightRoadOri = 1;
														}
														// ����ұߵ�·�ϵĵ�һ���ȼ��ĳ��Ƿ�Ҫֱ�С�
														// �ұߵ�·�����ȼ�����
														bool rBreakFlag = false;
														for (int rk = 0; rk <
															roadVector[rightRoadID].getRoadLength();
															++rk) //����ѭ��
														{
															for (int rm = 0; rm <
																roadVector[rightRoadID].getLaneNum();
																++rm) //������˳��ѭ��
															{
																int rightGridID = roadVector[rightRoadID].getGridState(
																	rightRoadOri, rm, rk);
																if (rightGridID != -1 &&
																	carVector[rightGridID].CarState == 1) {
																	int rightCarThisPlanStep = carVector[rightGridID].PlanStep;
																	int rightCarNextPlanStep =
																		rightCarThisPlanStep + 1;
																	if (carVector[rightGridID].Plan[rightCarNextPlanStep].nextDirection ==
																		STRAIGHT) // !!!!!!!!!!
																	{
																		conflictFlag = true;
																		rBreakFlag = true;
																		break;
																	}
																	else {
																		conflictFlag = false;
																		rBreakFlag = true;
																		break;
																	}
																}
															}

															if (rBreakFlag) {
																break;
															}
														}
													}
													else if (
														carVector[thisGridID].Plan[thisPlanStep].nextDirection ==
														RIGHT) {
														// ���ֱ�г�ͻ���ڱ���������߳���
														int leftRoadID = roadVector[thisRoadID].getSimplexRoadNextRoadID(
															thisRoadOri, LEFT);
														int leftRoadOri = 0;
														if (roadVector[leftRoadID].getStartCrossID() ==
															crossVector[i].getCrossID()) {
															leftRoadOri = 1;
														}
														// �����ߵ�·�ϵĵ�һ���ȼ��ĳ��Ƿ�Ҫֱ�С�
														// ��ߵ�·�����ȼ�����
														bool lBreakFlag = false;
														for (int lk = 0; lk <
															roadVector[leftRoadID].getRoadLength();
															++lk) //����ѭ��
														{
															for (int lm = 0; lm <
																roadVector[leftRoadID].getLaneNum();
																++lm) //������˳��ѭ��
															{
																int leftGridID = roadVector[leftRoadID].getGridState(
																	leftRoadOri, lm, lk);
																if (leftGridID != -1 &&
																	carVector[leftGridID].CarState == 1) {
																	int leftCarThisPlanStep = carVector[leftGridID].PlanStep;
																	int leftCarNextPlanStep =
																		leftCarThisPlanStep + 1;

																	conflictFlag =
																		(carVector[leftGridID].Plan[leftCarNextPlanStep].nextDirection ==
																			STRAIGHT);
																	lBreakFlag = true;
																	break;
																}
															}

															if (lBreakFlag) {
																break;
															}
														}

														if (!conflictFlag) //ֱ���޳�ͻ���ټ����ת��ͻ��
														{
															// �����ת��ͻ���ڱ������Ķ��泵��
															int frontRoadID = roadVector[thisRoadID].getSimplexRoadNextRoadID(
																thisRoadOri, STRAIGHT);
															int frontRoadOri = 0;
															if (roadVector[frontRoadID].getStartCrossID() ==
																crossVector[i].getCrossID()) {
																frontRoadOri = 1;
															}

															// �������·�ϵĵ�һ���ȼ��ĳ��Ƿ�Ҫ��ת��
															// �����·�����ȼ�����
															bool fBreakFlag = false;
															for (int fk = 0; fk <
																roadVector[frontRoadID].getRoadLength();
																++fk) //����ѭ��
															{
																for (int fm = 0; fm <
																	roadVector[frontRoadID].getLaneNum();
																	++fm) //������˳��ѭ��
																{
																	int frontGridID = roadVector[frontRoadID].getGridState(
																		frontRoadOri, fm, fk);
																	if (frontGridID != -1 &&
																		carVector[frontGridID].CarState == 1) {
																		int frontCarThisPlanStep = carVector[frontGridID].PlanStep;
																		int frontCarNextPlanStep =
																			frontCarThisPlanStep + 1;

																		conflictFlag =
																			(carVector[frontGridID].Plan[frontCarNextPlanStep].nextDirection ==
																				LEFT);
																		fBreakFlag = true;
																		break;
																	}
																}

																if (fBreakFlag) {
																	break;
																}
															}
														}
													}
													////////////// ��ͻ��� /////////////////

													if (conflictFlag) //����г�ͻ
													{
														// ������road��ѭ����
														thisRoadBreakFlag = true;
														break;
													}
													else //����޳�ͻ
													{
														// ���Ԥ��·�����Ƿ��г����赲������У��жϸ��赲�᲻���ñ����޷��ƶ�
														bool canMoveFlag = false;
														int possibleX = -1;
														int possibleY = -1;
														for (int x = 0;
															x < roadVector[nextRoadID].getLaneNum(); ++x) {
															for (int y = roadVector[nextRoadID].getRoadLength() - 1;
																y >= roadVector[nextRoadID].getRoadLength() -
																nextRoadExpectedDist;
																--y) {
																if (roadVector[nextRoadID].getGridState(nextRoadOri,
																	x,
																	y) == -1) {
																	// ���¿���λ��
																	possibleX = x;
																	possibleY = y;
																	canMoveFlag = true;
																}
																else {
																	break;
																}
															}
															if (canMoveFlag) //�Ƿ��Ѿ��ҵ�����λ��
															{
																break;
															}
														}

														if (canMoveFlag) {
															//���Ϊ��ֹ״̬��ȷ����ֹλ��
															carVector[thisGridID].CarState = 0;
															// ���³����б��е���Ϣ
															carVector[thisGridID].presentPosition.laneID = possibleX;
															carVector[thisGridID].presentPosition.orientation = nextRoadOri;
															carVector[thisGridID].presentPosition.positionID = possibleY;
															carVector[thisGridID].presentPosition.roadID = nextRoadID;
															// ���µ�·��ͼ�б��е���Ϣ
															roadVector[thisRoadID].changeGridState(thisRoadOri, m,
																k,
																-1);
															roadVector[nextRoadID].changeGridState(nextRoadOri,
																possibleX,
																possibleY,
																thisGridID);
															// ����plan
															carVector[thisGridID].PlanStep++;
														}
														else // �赲�ñ����޷��ƶ�,���ֵȴ�״̬
														{
															// ����roadѭ����
															thisRoadBreakFlag = true;
															break;
														}
													}
												}
											}
										}
									}
								}
							}

							if (thisRoadBreakFlag) {
								break;
							}

						} //����·
					}     //��·��

						  // ���·���Ƿ���ʱ����
					crossVector[i].carNumInWaiting = 0;
					for (int iter = 0; iter < carVector.size(); ++iter) {
						if (carVector[iter].CarState == 1) {
							int tmpRoadid = carVector[iter].presentPosition.roadID;
							int tmpRoadori = carVector[iter].presentPosition.orientation;
							if (roadVector[tmpRoadid].getSimplexRoadEndCrossID(tmpRoadori) ==
								crossVector[i].getCrossID()) {
								crossVector[i].carNumInWaiting++;
							}
						}
					}

					if (crossVector[i].carNumInWaiting == 0) //ѭ��һ��·�ڵ�road����,û�еȴ�״̬�ĳ����ˡ�
					{
						break;
					}
					if (lastWaitingNum_cross == crossVector[i].carNumInWaiting) //ѭ��һ��·�ڵ�road����û���κ�״̬�ı�
					{
						std::cout << "[INFO] Cross " << crossVector[i].getCrossID() << " unchanged with "
							<< lastWaitingNum_cross << " waiting cars." << std::endl;
						break;
					}

				}
			}

			// ���ϵͳ�Ƿ�����
			int lastWaitingNum_system = system->carNumInWaiting;
			system->carNumInWaiting = 0;
			for (int i = 0; i < carVector.size(); ++i) {
				if (carVector[i].CarState == 1) {
					system->carNumInWaiting++;
				}
			}
			if (lastWaitingNum_system == system->carNumInWaiting && lastWaitingNum_system != 0) //ѭ��һ��cross����û���κ�״̬�ı�
			{
				std::cout << "[ERROR] System Locked." << std::endl;
				break;
			}

		} //�ڶ���

	} // �������ߵĳ�

	if (system->getOfflineCarNum() > 0) {
		for (int i = 0; i < carVector.size(); ++i) {
			if (carVector[i].CarState == -1) //��δ����
			{
				if (carVector[i].PlannedTime <= system->getTime()) //�Ѿ��ﵽ�ɳ���ʱ��
				{
					// �жϳ�����·���Ƿ����赲
					bool canStartFlag = false;
					int possibleX = -1;
					int possibleY = -1;
					if (carVector[i].Plan.size() > 0) {
						int nextRoadID = carVector[i].Plan[0].roadID;
						int nextRoadOri = carVector[i].Plan[0].orientation;
						int nextRoadExpectedDist = carVector[i].MaxCarSpeed < roadVector[nextRoadID].getRoadMaxSpeed()
							? carVector[i].MaxCarSpeed
							: roadVector[nextRoadID].getRoadMaxSpeed();
						for (int x = 0; x < roadVector[nextRoadID].getLaneNum(); ++x) {
							for (int y = roadVector[nextRoadID].getRoadLength() - 1;
								y >= roadVector[nextRoadID].getRoadLength() -
								nextRoadExpectedDist;
								--y) {
								if (roadVector[nextRoadID].getGridState(nextRoadOri, x,
									y) == -1) {
									// ���¿���λ��
									possibleX = x;
									possibleY = y;
									canStartFlag = true;
								}
								else {
									break;
								}
							}
							if (canStartFlag) //�Ƿ��Ѿ��ҵ�����λ��
							{
								break;
							}
						}

						if (canStartFlag) {
							//���Ϊ��ֹ״̬��ȷ����ֹλ��
							carVector[i].CarState = 0;
							// ���³����б��е���Ϣ
							carVector[i].presentPosition.laneID = possibleX;
							carVector[i].presentPosition.orientation = nextRoadOri;
							carVector[i].presentPosition.positionID = possibleY;
							carVector[i].presentPosition.roadID = nextRoadID;
							// ���µ�·��ͼ�б��е���Ϣ
							roadVector[nextRoadID].changeGridState(nextRoadOri,
								possibleX, possibleY,
								i);
							// ����plan
							carVector[i].PlanStep = 0;
							// ����ʵ�ʳ���ʱ��
							carVector[i].ActualTime = system->getTime();
							//����ϵͳ��Ϣ
							system->startOneCar(i);
							std::cout << "[CAR INFO] Car " << i << " starts." << '\n';
						}
						else // �赲�ñ����޷��ƶ�,���ֵȴ�״̬
						{
							// ����carѭ����
							break;
						}
					}
					else {
						std::cout << "[ERROR] Car " << carVector[i].ID << " has no plan input." << '\n';
						exit(9);
					}
				}
			}
		}
	} // ���λ�δ�����ĳ�

	std::cout << "\\_______ SystemTime: " << system->getTime() << " End _________/" << '\n' << '\n' << '\n';


}

void initializeSystem() {
	std::vector<int> carIDList;
	carIDList.reserve(carVector.size());
	for (int i = 0; i < carVector.size(); ++i) {
		carIDList.push_back(carVector[i].ID);
	}

	std::cout << System.getTime() << '\n';
	System.inputCarVector(carIDList);

	System.displayCarList();  //ϵͳ����ʱ��

	roadVector[0].display(); //����ӳ������д�ӡ
}

//int main(int argc, char *argv[])
int main() {
	std::cout << "Begin" << std::endl;

	//	if(argc < 5){
	//		std::cout << "please input args: carPath, roadPath, crossPath, answerPath" << std::endl;
	//		exit(1);
	//	}
	//
	//	std::string carPath(argv[1]);
	//	std::string roadPath(argv[2]);
	//	std::string crossPath(argv[3]);
	//	std::string answerPath(argv[4]);
	//
	//	std::cout << "carPath is " << carPath << std::endl;
	//	std::cout << "roadPath is " << roadPath << std::endl;
	//	std::cout << "crossPath is " << crossPath << std::endl;
	//	std::cout << "answerPath is " << answerPath << std::endl;

	std::string roadPath("../config/road.txt");
	std::string crossPath("../config/cross.txt");
	std::string carPath("../config/car.txt");
	std::string answerPath("../config/answer.txt");


	////////////////////////// �����·�ļ� road.txt /////////////////////////////
	readRoadConfigFile(roadPath);

	////////////////////////// ����·���ļ� cross.txt ////////////////////////////
	readCrossConfigFile(crossPath);

	////////////////////////// ���복���ļ� car.txt //////////////////////////////
	readCarConfigFile(carPath);

	////////////////////////// ����map�����е�ID��Ϣ //////////////////////////////
	updateMapIDInfo();

	////////////////////////// ����ȫ�ֵ�ͼ���˹�ϵ ////////////////////////////////
	buildMap();

	//    ////////////////// test //////////////////
	//    int test_para = 17;
	//    std::cout << '\n';
	//    std::cout << "Road " << roadVector[test_para].getRoadID() + 5000 << " Direction + " << '\n';
	//    std::cout << '\t' << " left:" << '\t' << roadVector[test_para].getSimplexRoadNextRoadID(0, LEFT) << '\n'
	//              << '\t' << " straight:" << '\t' << roadVector[test_para].getSimplexRoadNextRoadID(0, STRAIGHT) << '\n'
	//              << '\t' << " right:" << '\t' << roadVector[test_para].getSimplexRoadNextRoadID(0, RIGHT) << '\n';
	//    std::cout << "Road " << roadVector[test_para].getRoadID() + 5000 << " Direction - " << '\n';
	//    std::cout << '\t' << " left:" << '\t' << roadVector[test_para].getSimplexRoadNextRoadID(1, LEFT) << '\n'
	//              << '\t' << " straight:" << '\t' << roadVector[test_para].getSimplexRoadNextRoadID(1, STRAIGHT) << '\n'
	//              << '\t' << " right:" << '\t' << roadVector[test_para].getSimplexRoadNextRoadID(1, RIGHT) << '\n';
	//    ////////////////// test //////////////////


	////////////////////////// ����滮�ļ� answer.txt �����³����滮���� ///////////////////////////
	// readAnswerFiles(answerPath);

	////    carVector[4].displayPlan();

	////////////////////////////////////////////////////////////////////////////////////////////


	initializeSystem();

	systemInfo *p = &System;


	// TODO: ���м������������ĳ�ʼ�滮 ////////////////////////////////////////////////////////////

	//    ///////// test ///////////////
	//    CarPlan firstPlan;
	//    firstPlan.roadID = 0;
	//    firstPlan.orientation = 0;
	//    firstPlan.nextDirection = 0;
	//
	//    carVector[0].pushCarPlan(firstPlan);
	//    carVector[1].pushCarPlan(firstPlan);
	//    carVector[2].pushCarPlan(firstPlan);
	//    carVector[3].pushCarPlan(firstPlan);
	//    carVector[4].pushCarPlan(firstPlan);
	//    carVector[5].pushCarPlan(firstPlan);
	//    carVector[6].pushCarPlan(firstPlan);
	//    carVector[7].pushCarPlan(firstPlan);
	//    ///////// test ///////////////


	do {
		//////// ״̬���� //////////////////////////////////////////////////////////////////////
		updateState(p);

		// TODO: ///////// ��ȡ��ǰ��ͼ��Ϣ //////////////////////////////////////////////////////
		// ��ȡĳһ·�ϵĳ�����Ŀ�� getRoadCarNum(int roadid, int ori)

		// ��ȡĳһ������·�ϵĳ�����Ŀ��
		// roadID = carVector[carID].getPresnetRoadID();
		// roadOri = carVector[carID].getPresnetRoadOri();
		// ��ʹ�ú��� getRoadCarNum(roadID, roadOri)��


		// TODO: /////////// �����㷨 ///////////////////////////////////////////////////////////


		// TODO: //////// д�����г�����һ���滮 ///////////////////////////////////////////////////
		// ʹ�ú��� getNextPossibleMove() �õ������߳���һ·��ʱ���ܵ�����
		// ����Ϊ��roadID���Լ�����(0��1)����������� std::vector<nextMove> �
		// ���У�nextMove�ṹ���У�nextMove.crossID ������һ·�ڵ�ID��nextMove.roadID ������һ��·��ID��

		// ��ǰ�������� std::vector<nextMove> �У������㷨��Ҫ������ѡ��һ��ȥ�򣬼���Ϊ move_A (nextMove����)��
		// ѡ����ĳ��ȥ������ú��� getNextStepPlan() �� move_A ת��Ϊ plan_A (CarPlan ����)
		// ���磺plan_A = getNextStepPlan(·id��·����move_A)

		// �����ɵĵ��� plan_A ѹ�뵽ĳ������ PlanList ��
		// ���磺carVector[carID].pushCarPlan(plan_A)

		// �������ƣ�Ϊ�������ߵĳ���pushһ���滮��

		//        ////////// test /////////////////////////////////
		//        nextMove moveX;
		//        moveX.roadID = 1;
		//        moveX.crossID = 2;
		//
		//        CarPlan planX;
		//        planX = getNextStepPlan(1,0,moveX);
		//
		//        carVector[0].pushCarPlan(planX);
		//        carVector[1].pushCarPlan(planX);
		//        carVector[2].pushCarPlan(planX);
		//        carVector[3].pushCarPlan(planX);
		//        carVector[4].pushCarPlan(planX);
		//        carVector[5].pushCarPlan(planX);
		//        carVector[6].pushCarPlan(planX);
		//        carVector[7].pushCarPlan(planX);
		//        ////////// test /////////////////////////////////



		//    } while (System.getOnlineCarNum() > 0); // ���������г���
	} while (System.getTime() < 2); // ʱ�䵥��

									/////////////////////////////////////////////////////////////////////////////////////////////////

	roadVector[1].display();


	std::cout << "Finished within " << System.getTime() << " seconds";

	// TODO:read input filebuf
	// TODO:processs
	// TODO:write output file

	return 0;
}
