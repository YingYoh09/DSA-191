/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "dbLib.h"

string frontToNextComma(string& s)
{
	int commaPosition = s.find_first_of(",");
	string temp = s.substr(0, commaPosition);
	s.erase(0, commaPosition + 1);
	return temp;
}

string frontToNextDoubleQuotes(string& s)
{
	string temp = "";
	for (int i = 1; s[i] != '\"';++i)
		temp += s[i];
	s.erase(0, temp.length() + 3);
	return temp;
}

void LoadFlinesCSV(L1List<TLine>*& lineData)
{
	ifstream ifs("lines.csv", ios::in);
	string s;
	getline(ifs, s);//ignore 1st line
	int id, cityId;
	while (getline(ifs, s)) {
		id = stoi(frontToNextComma(s));
		cityId = stoi(frontToNextComma(s));
		TLine tempTLine(id, cityId);
		lineData->push_back(tempTLine);
	}
	ifs.close();
}

void LoadFcitiesCSV(L1List<TCity>*& cityData)
{
	ifstream ifs("cities.csv", ios::in);
	string s;
	getline(ifs, s);//ignore 1st line
	int id;string name;
	while (getline(ifs, s)) {
		id = stoi(frontToNextComma(s));
		name = frontToNextComma(s);
		TCity temp(id, name);
		cityData->push_back(temp);
	}
	ifs.close();
}

void LoadFstationsCSV(L1List<TStation>*& stationData)
{
	ifstream ifs("stations.csv", ios::in);
	string s;
	getline(ifs, s);//ignore 1st line
	int id, cityId=0; string name, point;
	while (getline(ifs, s)) {
		id = stoi(frontToNextComma(s));
		if (s[0] == '\"')
			name = frontToNextDoubleQuotes(s);
		else name = frontToNextComma(s);
		point = frontToNextComma(s);
		//POINT() = 7
		point = point.substr(6, point.length() - 7);
		s.erase(0, s.find_last_of(",") + 1);
		cityId = stoi(s);
		TStation temp(id, name, point, cityId);
		stationData->push_back(temp);
	}
	ifs.close();
}

void LoadFstation_LinesCSV(L1List<Station_Line>*& sLinesData)
{
	ifstream ifs("station_lines.csv", ios::in);
	string s, buffer;
	getline(ifs, s);//ignore 1st line
	int stationId, lineId;
	while (getline(ifs, s)) {
		buffer = frontToNextComma(s);
		stationId = stoi(frontToNextComma(s));
		lineId = stoi(frontToNextComma(s));
		Station_Line temp(stationId,lineId);
		sLinesData->push_back(temp);
	}
	ifs.close();
}

void LoadFtracksCSV(L1List<TTrack>*& trackData)
{
	ifstream ifs("tracks.csv", ios::in);
	string s, lineString;
	getline(ifs, s);//ignore 1st line
	int id, cityId;
	while (getline(ifs, s)) {
		id = stoi(frontToNextComma(s));
		if (s[0] == '\"')
			lineString = frontToNextDoubleQuotes(s);
		else lineString = "";
		s = s.erase(0, s.find_last_of(",") + 1);
		cityId = stoi(s);
		TTrack temp(id, lineString, cityId);
		trackData->push_back(temp);
	}
	ifs.close();
}

void LoadData(void*& pManager)
{
	TDataset* pDataset = new TDataset;
	LoadFlinesCSV(pDataset->line);
	LoadFcitiesCSV(pDataset->city);
	LoadFstationsCSV(pDataset->station);
	LoadFstation_LinesCSV(pDataset->station_Line);
	LoadFtracksCSV(pDataset->track);
	
	pManager = pDataset;
}

void ReleaseData(void*& pManager)
{
	delete pManager;
}
