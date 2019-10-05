#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <cctype>
#define FILENAME "q1_sol.cpp"
using namespace std;

/* Your code MUST NOT contain any words in the following list:
{"include", "while", "for", "goto"} even in the comments */

//----------------------------------------------
// Begin implementation
//----------------------------------------------

/// Student implement the recursive function here
int isEvenWord(string word) {
	static int F[300]{};
	static int count = 0;
	static int res = 0;

	if (word.length() == 0)
	{
		if (count > 0) return -1;
		return res;
	}
	else
	{
		F[word[0]]++;
		if (F[word[0]] == 1)
			count++;
		if (F[word[0]] == 2)
		{
			F[word[0]] = 0;
			count--;
			res++;
		}
		word.erase(0, 1);
		return isEvenWord(word);
	}
}

bool codeCheck() {
	const char* forbiddenKeyword[] = { "include", "while", "for", "goto" };
	fstream ifs;
	ifs.open("main.cpp", ios::in);
	if (ifs.fail()) ifs.open(FILENAME, ios::in);
	if (ifs.fail()) return true;
	ifs.seekg(0, ifs.end);
	int fileSize = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	char* fileContent = new char[fileSize];
	ifs.read(fileContent, fileSize);
	ifs.close();
	*strstr(fileContent, "bool codeCheck() {") = '\0';
	char* todoSegment = strstr(fileContent, "// Begin implementation");
	int numberOfForbiddenKeyword = sizeof(forbiddenKeyword) / sizeof(const char*);
	for (int i = 0; i < numberOfForbiddenKeyword; i++) { if (strstr(todoSegment, forbiddenKeyword[i])) return false; }
	delete[] fileContent;
	return true;
}


int main(int argc, char** argv) {

	ifstream ifs("inp.txt", ios::in);

	string word;
	getline(ifs, word);

	ifs.close();

	cout << isEvenWord(word);

	return 0;

}