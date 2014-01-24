/*
 * generate.cppx
 *
 *  Created on: Dec 12, 2013
 *      Author: navid
 */

#include <iostream>
#include <cstdio>
#include "string.h"
#include <stdlib.h>
#include <cmath>
#include <fstream>

#include <sstream>

using namespace std;

double distance2d(double x1, double y1, double x2, double y2) {
//	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
//	return sqrt(abs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));

	return sqrt(x1 * x1 + y1 * y1 + x2 * x2 + y2 * y2);

}

double score2d(double d, double alpha) {
//	if (d < 0.1)
//		return (exp(-alpha * d * d));
////		return (0);
//	else
	return (exp(-alpha * d * d));
//	return (exp(-alpha * d )/d);
}

void simulate2d(int id, int N, double alpha) {
	double X[N];
	double Y[N];
	double degree[N];

	ofstream f;

	cout << "The lambda/alpha^2 ratio is: " << 1.0 * N / (alpha) << "\n";

	stringstream filename;
	filename << "degrees-" << int(1.0 * N / (alpha)) << ".txt";

//	fprintf(filename,"%d",alpha);
//	filename << ".txt";

//	const char* filename = "degrees.txt";
	cout << filename.str().c_str();
	if (id == 0)
		f.open(filename.str().c_str());
	else
		f.open(filename.str().c_str(), std::fstream::app);

	for (int i = 0; i < N; i++)
		degree[i] = 0;

	for (int i = 0; i < N; i++) {
		X[i] = 1.0 * rand() / RAND_MAX;
		Y[i] = 1.0 * rand() / RAND_MAX;
//		cout << X[i] << " " << Y[i] << "\n";
	}

	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			double d = distance2d(X[i], Y[i], X[j], Y[j]);
			double s = score2d(d, alpha);
			degree[i] = degree[i] + s;
			degree[j] = degree[j] + s;
		}
	}

	for (int i = 0; i < N; i++) {
//		cout << degree[i] << '\n';

//		if ((X[i] > 1.0 / alpha) && (X[i] < 1.0 - 1.0 / alpha)
//				&& (Y[i] > 1.0 / alpha) && (Y[i] > 1.0 - 1.0 / alpha))

		if (X[i] * X[i] + Y[i] * Y[i] < 1)
			f << degree[i] << " " << X[i] << " " << Y[i] << '\n';
	}

	f.close();
}
//

double distance1d(double x1, double x2) {
	return sqrt((x1 - x2) * (x1 - x2));
//	return sqrt(x1 * x1 + x2 * x2);

}

double score1d(double d, double alpha) {
//	return (exp(-alpha * d));
	return (exp(-alpha * d) / d);
}

void simulate1d(int id, int N, double alpha) {

	double X[N];
	double degree[N];
	ofstream f;

	// There has to be 4 arguments: a string option, and am integer time_total

	cout << "The lambda/alpha^2 ratio is: " << 1.0 * N / (alpha) << "\n";

	stringstream filename;
	filename << "degrees-" << int(1.0 * N / (alpha)) << ".txt";

//	fprintf(filename,"%d",alpha);
//	filename << ".txt";

//	const char* filename = "degrees.txt";
	cout << filename.str().c_str();

	if (id == 0)
		f.open(filename.str().c_str());
	else
		f.open(filename.str().c_str(), std::fstream::app);

	for (int i = 0; i < N; i++)
		degree[i] = 0;

	for (int i = 0; i < N; i++) {
		X[i] = 1.0 * rand() / RAND_MAX;
//		cout << X[i] << " " << Y[i] << "\n";
	}

	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			double d = distance1d(X[i], X[j]);
			double s = score1d(d, alpha);
			degree[i] = degree[i] + s;
			degree[j] = degree[j] + s;
		}
	}

	for (int i = 0; i < N; i++) {
//		cout << degree[i] << '\n';

//		if ((X[i] > 1.0 / alpha) && (X[i] < 1.0 - 1.0 / alpha)
//				&& (Y[i] > 1.0 / alpha) && (Y[i] > 1.0 - 1.0 / alpha))
		f << degree[i] << " " << X[i] << '\n';
	}

	f.close();
}

void runBatch2D(int num_repeats, int N, double alpha) {
	for (int i = 0; i < num_repeats; i++)
		simulate2d(i, N, alpha);

}

int main(int argc, char *argv[]) {
	/* default values */
	int N = 4000;
	double alpha = 20;

	/* process commandline arguments */
	if (argc == 3) {
		N = atoi(argv[1]);
		alpha = atoi(argv[2]);
	}

	alpha = 20;
	for (double B = 20.0; B < 5000; B *= 1.5) {
		N = int(alpha * B);
		cout << N << "\n";
		runBatch2D(100, N, alpha);
	}

//	for (int i=0;i<1000;i++)
//		simulate1d(i,argc, argv);

}

