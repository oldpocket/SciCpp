#ifndef NEURON_H_
#define NEURON_H_

#include "Type.h"

using namespace std;

class Neuron
{
public:
	Neuron(unsigned num_outputs, unsigned my_index);
	~Neuron() { output_weights_.clear(); }

	void feedForward(const vector<Neuron> &prev_layer);
	void feedForwardOutput(const vector<Neuron> &prev_layer, bool classification);

	void compOutputGradients(double target_val, bool classification);
	void compHiddenGradients(const vector<Neuron> &next_layer);

	void updateInputWeights(vector<Neuron> &prev_layer, double eta, double alpha, double lambda);
	void resetOutputWeights();
	Weights getOutputWeights();

	void setOutputWeights(Weights weights);
	void setOutputVal(double val) { output_val_ = val; }
	double getOutputVal(void) const { return output_val_; }

	double sumSquaredWeights();
	double sumWeights();
	// void reset_full_gradient(){ full_gradient_ = 0; }
	// double squaredGradient(){ return full_gradient_*full_gradient_; }
private:
	double sigmoid(double x);
	double sigmoidDerivative(double x);

	double randomWeight(void);
	double output_val_; // output value of the unit
	vector<Connection> output_weights_;

	unsigned my_index_; // In the current layer
	double gradient_;
	// double full_gradient_; // cumulator for the gradiends values during one epoch training
};

#endif /* NEURON_H_ */
