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
	string	cityName;

	TLine(int id, int city_id, const string& city_name)
		: id(id),
		  cityId(city_id),
		  cityName(city_name)
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

	TStation(int id, const string& name, const string& point)
		: id(id),
		  name(name),
		  point(point)
	{
	}
};

struct StationLine
{
	int		lineId;
	int		stationId;

	StationLine(int line_id, int station_id)
		: lineId(line_id),
		  stationId(station_id)
	{
	}
};

class TDataset {
public:
	L1List<TCity>*		city;
	L1List<TLine>*		line;
	L1List<TTrack>*		track;
	L1List<TStation>*	station;
	
	~TDataset()
	{
		delete city;
		delete line;
		delete track;
		delete station;
	}

	TDataset()
	{
		city = new L1List<TCity>;
		line = new L1List<TLine>;
		track = new L1List<TTrack>;
		station = new L1List<TStation>;
	}
};

// Please add more or modify as needed
string frontToNextComma(string &);

void LoadLinesInCSV(L1List<TLine>*& lineData);
void LoadCities(L1List<TCity>*& cityData);
void LoadStations(L1List<TStation>*& stationData);

void LoadData(void* &);
void ReleaseData(void* &);

#endif //DSA191_A1_DBLIB_H
