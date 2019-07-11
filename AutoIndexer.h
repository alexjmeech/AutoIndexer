#ifndef AUTOINDEXER_H_
#define AUTOINDEXER_H_

#include <map>
#include <fstream>
#include "String.h"
#include "ArrayList.h"
using namespace std;

class AutoIndexer
{
private:
	map<String, ArrayList<int>> indexEntries;
public:
	AutoIndexer(ifstream&, ofstream&);
private:
	void processLine(int, String&);
	void loadData(ifstream&);
	void outputData(ofstream&);
};

#endif /* AUTOINDEXER_H_ */
