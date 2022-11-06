#include <iostream>
#include <fstream>
#include "mlp/Net.h"
#include "util/DatasetManager.h"

using namespace std;

// initial parameters of the system
namespace
{
	const unsigned kFirstInputCol = 0; // column count sta
	const unsigned kNumFold = 5;	   // 1 = all data training
	const bool classification = false;
	const unsigned first_target_col = 5;
	double scale[] = {0.045906, 0.49896415}, translate[] = {-1.692065, -22.383271};
	const unsigned epoch_limit = 100000;
	double best_eta = 0.1, best_alpha = 0.1, best_lambda = 0.001, best_valid = 1000;
}

int main()
{
	cout << "Start!" << endl;
	{
		// Trainning and Validation dataset data
		DatasetManager *data_set_manager = new DatasetManager("data//input.txt", kFirstInputCol, first_target_col, kNumFold);
		data_set_manager->shuffleDataSet();
		data_set_manager->splitDataset(30); // between trainning and validation

		// TRAIN the best model on all the dataset
		Net *net1 = new Net("5 5 2", classification, first_target_col, scale, translate);
		net1->train(data_set_manager->getDataset(), best_eta, best_alpha, best_lambda, epoch_limit, true /*printout*/, true /*mee*/);

		// final TEST on the choosen model
		DatasetManager *test_set_manager = new DatasetManager("data//test.txt", kFirstInputCol, first_target_col, kNumFold);
		net1->blindTest(test_set_manager->getDataset());

		// Clean up
		delete data_set_manager;
		delete test_set_manager;
		delete net1;
	}
	std::cout << "Finish!" << endl;

	// End.
	std::cout << "Press enter to exit";
	std::cout << "\a";
	std::cin.get();
	return 0;
}
