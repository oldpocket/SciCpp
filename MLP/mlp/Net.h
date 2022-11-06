#ifndef NET_H_
#define NET_H_
#include <vector> // per vector
#include "Type.h"
#include "Neuron.h"

using namespace std;

class Net
{
public:
	Net(const vector<unsigned> &topology, bool classification, unsigned first_target_col, double *scale, double *translate);
	Net(string topology, bool classification, unsigned first_target_col, double *scale, double *translate);
	~Net() { layers_.clear(); }

	// compute the units output value
	void feedForward(const vector<double> &inputVals);
	//  for a single pattern
	void backProp(const vector<double> &target_vals, double eta, double alpha, double lambda);
	// one epoch of backprop alg throught the training set
	double trainEpoch(vector<vector<double>> d_train, double eta, double alpha, double lambda, bool mee);
	double train(vector<vector<double>> data, double eta, double alpha, double lambda,
				 unsigned epoch_max, bool printout, bool mee);

	void getOutputs(vector<double> &output_vals) const;
	vector<unsigned> getTopology() { return topology_; }

	void resetNetWeights();
	vector<vector<Weights>> getNetWeights(void);
	void setNetWeights(vector<vector<Weights>> w);

	double computeError(const vector<double> &target_vals, const vector<double> &output_vals, bool mee);

	double test(const vector<vector<double>> d_test, bool print_output, bool mee);
	void printResults(ofstream &out_file, const vector<double> input_vals, const vector<double> output_vals, const vector<double> target_vals) const;
	void blindTest(const vector<vector<double>> d_test);
	double sumWeights();
	void resetFullGradients();

private:
	void denormalize(vector<double> &data, double *scale, double *translate);

	double sumSquaredWeights();
	double sumSquaredGradients();
	vector<unsigned> getTopology(string t);
	void split(const vector<vector<double>> data, vector<vector<double>> &d_train, vector<vector<double>> &d_valid, int p);
	vector<vector<Neuron>> layers_; // m_layers[layerNum][neuronNum]
	vector<unsigned> topology_;
	bool classification_;
	unsigned first_target_col_;
	double *scale_ = NULL, *translate_ = NULL;
};

#endif /* NET_H_ */
