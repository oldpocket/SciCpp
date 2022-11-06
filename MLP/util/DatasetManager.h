#ifndef DATASETMANAGER_H_
#define DATASETMANAGER_H_

#include <iostream>	 // per std::cout e std::endl
#include <vector>	 // per vector
#include <ctime>	 // std::time
#include <algorithm> // std::random_shuffle
#include "CSVDataLoader.h"

using namespace std;

class DatasetManager : public CSVDataLoader
{
public:
	DatasetManager(const string file_name, unsigned input_start_col, unsigned target_start_col, unsigned num_of_fold);
	~DatasetManager()
	{
		data_set_.clear();
		training_set_.clear();
		validation_set_.clear();
	}
	void shuffleTrainingSet(void);
	void shuffleDataSet(void);
	void nextFold(void);
	bool hasNextFold(void) { return actual_fold_num_ < num_fold_ - 1; }
	int getActualFoldNum() { return actual_fold_num_; }
	vector<vector<double>> getTrainingSet() { return training_set_; }
	vector<vector<double>> getValidationSet() { return validation_set_; }
	vector<vector<double>> getDataset() { return data_set_; }
	void splitDataset(int p);
	unsigned getNumOfFolds() { return num_fold_; }

private:
	void initKthFold(unsigned k);
	vector<vector<double>> data_set_;		// matrix containing the training data input + target
	vector<vector<double>> training_set_;	// training set
	vector<vector<double>> validation_set_; // validation set
	unsigned input_start_col_;				// col num start by 0
	unsigned target_start_col_;				// the col numb of the first target val
	int actual_fold_num_;
	int num_fold_;
};

#endif /* DATASETMANAGER_H_ */
