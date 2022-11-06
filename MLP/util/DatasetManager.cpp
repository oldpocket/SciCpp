#include "DatasetManager.h"

// initialize the data matrixes reading all the file
// in the csv training file each row contains also the target val
DatasetManager::DatasetManager(const string file_name,
							   unsigned input_start_col, unsigned target_start_col, unsigned num_of_fold)
	: CSVDataLoader(file_name)
{
	input_start_col_ = input_start_col;
	target_start_col_ = target_start_col;
	num_fold_ = num_of_fold;
	actual_fold_num_ = -1;

	vector<double> trainingVals;
	while (!CSVDataLoader::isEOF())
	{
		if (CSVDataLoader::getInput(trainingVals) != 0)
		{
			data_set_.push_back(trainingVals);
		}
	}
}

// until nextFold is called the training set and the dataset are not initialized
void DatasetManager::nextFold(void)
{
	actual_fold_num_++;
	initKthFold(actual_fold_num_);
}

void DatasetManager::shuffleTrainingSet(void)
{
	std::srand(unsigned(std::time(0)));
	// using built-in random generator:
	std::random_shuffle(training_set_.begin(), training_set_.end());
}
void DatasetManager::shuffleDataSet(void)
{
	std::srand(unsigned(std::time(0)));
	// using built-in random generator:
	std::random_shuffle(data_set_.begin(), data_set_.end());
}

// The actual fold number k is the index of the partition used as test
// build the new training and validation sets
void DatasetManager::initKthFold(unsigned k)
{
	validation_set_.clear();
	training_set_.clear();
	for (unsigned i = 0; i < data_set_.size(); i++)
	{
		if ((i % num_fold_) == k)
		{
			validation_set_.push_back(data_set_[i]);
		}
		else
		{
			training_set_.push_back(data_set_[i]);
		}
	}
}
// form the data build the training set and use the remaining p% for the validation set
void DatasetManager::splitDataset(int p)
{
	vector<double> row;
	unsigned size = (unsigned)data_set_.size() * p / 100;
	validation_set_.clear();
	for (unsigned row_n = 0; row_n < size; row_n++)
	{
		for (unsigned k = 0; k < data_set_[row_n].size(); k++)
		{
			row.push_back(data_set_[row_n][k]);
		}
		validation_set_.push_back(row);
		row.clear();
	}
	training_set_.clear();
	for (unsigned row_n = size; row_n < data_set_.size(); row_n++)
	{
		for (unsigned k = 0; k < data_set_[row_n].size(); k++)
		{
			row.push_back(data_set_[row_n][k]);
		}
		training_set_.push_back(row);
		row.clear();
	}
}
