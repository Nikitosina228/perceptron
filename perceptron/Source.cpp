#include <iostream>
#include <fstream>
#include <math.h> 
#include <cmath>
#include <stdlib.h> 
#include <iomanip> 

using namespace std;

double ActivationFunction(double x) { // activation function
	return 1 / (1 + exp(-x));
}

//double MSE(double Houtput, const int arrResponse[], int n) { // Error
//	return (arrResponse[n] - Houtput) * (arrResponse[n] - Houtput) / (n + 1);
//}

double Derivative¿unction(double x, string Function) { //derivative of activation function <:sigmoid ËÎË tangh:>
	if (Function == "sigmoid") {
		return (1 - x) * x;
	}
	if (Function == "tangh") {
		return 1 - (x * x);
	}
	return x;
}

double GRAD(double delta, double OUT) { //gradient for outgoing synapse
	return delta * OUT;
}

double MORValueOutputNeuron(double OUTresponse, double OUTactual) { //backpropagation <: algorithm for output neuron :>
	return (OUTresponse - OUTactual) * Derivative¿unction(OUTactual, "sigmoid");
}

//double WeightUpdate(const double E, double grad) { // Without a moment
//
//	return E * grad;
//}

double WeightUpdate(const double E, double grad, double a, double W, int i) { // With a moment
	if (i == 0) {
		return E * grad;
	}
	return E * grad + a * W;
}

//Customization<-------------------------------->Customization<-------------------------------------->Customization

//Training set <--------------------------> Training set
const int arrTraining[100][100] = {
						{1, 0, 1},
						{0, 0, 0},
						{1, 1, 0},
						{0, 1, 1},
};
//Training set <--------------------------> Training set

const int arrResponse[10000] = { 1, 0, 1, 0}; // Training Set Answers

const int arrTest[10000] = { 1, 0, 0 }; // Test set

const int NumberInputs = 3; // Number of inputs 
const int NumberTrainings = 5000; // Number of trainings
const int NumberTrainingSets = 4;  //Number of training sets


const double speed = 0.9; //Learning speed
const double moment = 0.01; // Moment

//Customization<-------------------------------->Customization<-------------------------------------->Customization



double Syn[10]; // synapse weights
double Hinput = 0, Houtput = 0, W[10000], err = 0, delta, Delta; // Variable initialization

int main() {

	cout << "wesa do" << endl;
	for (int i = 0; i <= NumberInputs; i++) { // set weights
		Syn[i] = (rand() % 100000) / 10000.0;
		cout << Syn[i] << endl;
	}
	cout << endl;


	for (int k = 0; k < NumberTrainings; k++) { // training--------------------------------------training
		Hinput = 0;
		for (int i = 0; i < NumberTrainingSets; i++) {
			Hinput = 0;
			for (int j = 0; j <= NumberInputs; j++) {
				if (j == NumberInputs) {
					Hinput += 1 * Syn[j];
				}
				else {
					Hinput += arrTraining[i][j] * Syn[j];
				}
			}
			Houtput = ActivationFunction(Hinput);
			delta = MORValueOutputNeuron(arrResponse[i], Houtput);

			for (int j = 0; j <= NumberInputs; j++) {
				if (j == NumberInputs) {
					Delta = GRAD(delta, 1);
				}
				else {
					Delta = GRAD(delta, arrTraining[i][j]);
				}
				W[j] = WeightUpdate(speed, Delta, moment, W[j - 1], j);
				Syn[j] += W[j];
			}
		}
	}

	Hinput = 0;

	cout << endl << "wesa posle" << endl;
	for (int i = 0; i <= NumberInputs; i++) {
		cout << Syn[i] << endl;
	}

	cout << endl;
	for (int j = 0; j <= NumberInputs; j++) { // check--------------------------------------check
		if (j == NumberInputs) {
			Hinput += 1 * Syn[j];
		}
		else {
			Hinput += arrTest[j] * Syn[j];
		}
	}
	Houtput = ActivationFunction(Hinput);
	cout << fixed << setprecision(5) << Houtput << endl;
	Hinput = 0;

	system("pause");
	return 0;
}