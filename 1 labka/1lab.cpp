#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

enum class NumOfRoots{Zero, One, Two};

double* solver(double a, double b, double c, NumOfRoots& n) {
	double d{ b * b - (4 * a * c) };
	if (d > 0) {
		double* x{ new double[2] };
		x[0] = (-b + sqrt(d)) / (2 * a);
		x[1] = (-b - sqrt(d)) / (2 * a);
		n = NumOfRoots::Two;
		return x;
	}
	else if (d == 0) {
		double* x{ new double(-b / (2 * a)) };
		n = NumOfRoots::One;
		return x;
	}
	else {
		n = NumOfRoots::Zero;
		return nullptr;
	}
}

double* solverInput(void) {
	double* coef{ new double[3] };
	cout << "Enter coefficient a: " << endl;
	cin >> coef[0];
	cout << "Enter coefficient b: " << endl;
	cin >> coef[1];
	cout << "Enter coefficient c: " << endl;
	cin >> coef[2];
	cout << "Your equation is " << coef[0] << "x^2 + " << coef[1] << "x + " << coef[2] << endl;

	return coef;
}

void solverOutput(double* roots, NumOfRoots n) {
	if (n == NumOfRoots::Zero) { cout << "\nEquation has no roots!\n" << endl; }
	if (n == NumOfRoots::One) { cout << "\nEquation has one root: " << roots[0] << endl; }
	if (n == NumOfRoots::Two) { cout << "\nEquation has two roots: " << roots[0] << " and " << roots[1] << endl; }
}

bool isNumerical(const string& str) {
	for (char c : str) {
		if (!isdigit(c) && c != '.' && c != '-') {
			return false;
		}
	}
	return true;
}

void readFile(double* coef) {
	ifstream inputFile("coefficients.txt");
	if (!inputFile.is_open()) {
		cerr << "Error: Unable to open the input file." << endl;
		return;
	}

	string line;
	int coefficientIndex = 0;

	while (coefficientIndex < 3 && getline(inputFile, line)) {
		stringstream ss(line);
		if (ss >> coef[coefficientIndex] && isNumerical(line)) {
			coefficientIndex++;
		}
		else {
			cerr << "Error: Invalid input for coefficient " << coefficientIndex + 1 << "." << endl;
			return;
		}
	}

	inputFile.close();

	if (coefficientIndex < 3) {
		cerr << "Error: Input file does not contain enough coefficients." << endl;
		return;
	}

	cout << "The coefficients read from the file are: ";
	for (int i = 0; i < 3; i++) {
		cout << coef[i];
		if (i < 2) {
			cout << ", ";
		}
	}
	cout << endl;
}
void saveRootsToFile(double* roots, NumOfRoots numRoots) {
	ofstream outputFile("roots.txt");
	if (outputFile.is_open()) {
		switch (numRoots) {
		case NumOfRoots::Zero:
			outputFile << "The quadratic equation has no real roots." << endl;
			break;
		case NumOfRoots::One:
			outputFile << roots[0] << endl;
			break;
		case NumOfRoots::Two:
			outputFile << roots[0] << " " << roots[1] << endl;
			break;
		}
		cout << "Roots have been saved to roots.txt" << endl;
		outputFile.close();
	}
	else {
		cerr << "Error: Unable to open the output file." << endl;
	}
}
int main(void) {

	NumOfRoots n{};
	double coef[3];
	readFile(coef);
	double* roots{ solver(coef[0], coef[1], coef[2], n) };
	solverOutput(roots, n);
	saveRootsToFile(roots, n);
	return 0;

	delete[] roots;
}
