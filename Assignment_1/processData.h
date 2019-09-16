/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Declaration of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_PROCESSDATA_H
#define DSA191_A1_PROCESSDATA_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cassert>

#include "dbLib.h"

using namespace std;
/// Prototype declaration
void Initialization();
void Finalization();

void ProcessRequest(const char* pRequest, void*& pData, void* &pOutput, int &);

template <typename T>
void PrintReqOutput(const char* pRequest, T* pOutput, int N) {
    cout << pRequest << ":";
    if (pOutput == nullptr) {
        cout << " error\n";
        return;
    }
    for (int i = 0; i < N; ++i) {
        cout << ' ' << *pOutput++;
    }
    cout << '\n';
}

enum Options
{
	COUNT_LINE,COUNT_LINE_of_CITY,
	LIST_STATION_of_CITY, LIST_LINE_of_CITY, LIST_STATION_of_LINE,
	FIND_CITY, FIND_STATION, FIND_STATION_of_TRACK,
	INSERT_STATION, REMOVE_STATION, UPDATE_STATION,
	INSERT_STATION_to_LINE, REMOVE_STATION_from_LINE
};

Options resolveOptions(string& requestS, string& restS);

int getCityIdByName(TDataset*& pData, string nameS);

void countLine_1(TDataset*& pData, int*& pOutput, int& N);

void countLineofCity_2(TDataset*& pData, int*& outputData, int& N);

void ListStationOfCity_3(TDataset*& pData, int*& outputData, int& N);

void ListLinesOfCity_4(TDataset*& pData, int*& outputData, int& N);

void ListStationOfLines_5(TDataset*& pData, int*& outputData, int& N);

void FindCityIdbyName_6(TDataset*& pData, int*& outputData, int& N);

void FindStationIdbyName_7(TDataset*& pData, int*& outputData, int& N);

void FindStationinTrack_8(TDataset*& pData, int*& outputData, int& N);

#endif //DSA191_A1_PROCESSDATA_H
