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

void LoadFlinesCSV(L1List<TLine>*& lineData)
{
	ifstream ifs("lines.csv", ios::in);
	string s;
	getline(ifs, s);//delete 1st line
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
	getline(ifs, s);//delete 1st line
	int id;string name;
	while (getline(ifs, s)) {
		id = stoi(frontToNextComma(s));
		name = frontToNextComma(s);
		TCity temp(id, name);
		cityData->push_back(temp);
	}
	ifs.close();
}

void LoadData(void*& pManager)
{
	TDataset* pDataset = new TDataset;
	LoadFlinesCSV(pDataset->line);
	LoadFcitiesCSV(pDataset->city);
	
	pManager = pDataset;
}

void ReleaseData(void*& pManager)
{
	delete pManager;
}
