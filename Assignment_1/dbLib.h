/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DBLIB_H
#define DBLIB_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

struct TCity {
	int		id;
	string	name;

	TCity(int id, const string& name): id(id),name(name)
	{
	}
};

struct TLine {
	int		id;
	int		cityId;

	TLine(int id, int city_id)
		: id(id),
		  cityId(city_id)
	{
	}
};

struct TTrack {
	int		id;
	string	lineString;
	int		cityId;

	TTrack(int id, const string& line_string, int city_id)
		: id(id),
		  lineString(line_string),
		  cityId(city_id)
	{
	}
};

struct TStation
{
	int			id;
	string		name;
	string		point;
	int			cityId;
	
	TStation(int id, const string& name, const string& point, int cityId)
		: id(id),
		  name(name),
		  point(point), cityId(cityId)
	{
	}
};

struct Station_Line
{
	int		lineId;
	int		stationId;

	Station_Line(int station_id, int line_id)
		: stationId(station_id), lineId(line_id)
	{
	}
};

class TDataset {
public:
	L1List<TCity>*			city;
	L1List<TLine>*			line;
	L1List<TTrack>*			track;
	L1List<TStation>*		station;
	L1List<Station_Line>*	station_Line;
	
	~TDataset()
	{
		delete city;
		delete line;
		delete track;
		delete station;
		delete station_Line;
	}

	TDataset()
	{
		city = new L1List<TCity>;
		line = new L1List<TLine>;
		track = new L1List<TTrack>;
		station = new L1List<TStation>;
		station_Line = new L1List<Station_Line>;
	}
};

// Please add more or modify as needed
string frontToNextComma(string &);

void LoadFlinesCSV(L1List<TLine>*& lineData);
void LoadFcitiesCSV(L1List<TCity>*& cityData);
void LoadFstationsCSV(L1List<TStation>*& stationData);
void LoadFstation_LinesCSV(L1List<Station_Line>*& sLinesData);

void LoadData(void* &);
void ReleaseData(void* &);

#endif //DSA191_A1_DBLIB_H
