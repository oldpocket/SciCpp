#ifndef CSVDATALOADER_H_
#define CSVDATALOADER_H_

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class CSVDataLoader
{
public:
	CSVDataLoader(const string filename);
	~CSVDataLoader() { dataFile_.close(); }
	bool isEOF(void) { return dataFile_.eof(); }
	// Returns the number of input values read from the file, read a full row
	unsigned getInput(vector<double> &input_vals);

private:
	ifstream dataFile_;
};

#endif /* CSVDATALOADER_H_ */
