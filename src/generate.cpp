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


double distance_squared(double x1, double y1, double x2, double y2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}


double distance2d(double x1, double y1, double x2, double y2) {
    return sqrt(distance_squared(x1,y1,x2,y2));
}



double Green(double x1, double y1, double x2, double y2){
    double r2 = distance_squared(x1,y1,x2,y2);
    return exp(-r2*10);
}



double weight_hub(double x, double y){
    double r2 = distance_squared(x,y,0.0,0.0);
    
    // return r^(-4)
    return 1.0/r2/r2;
}




double score2d(double xi, double yi, double xj,double yj, double *X_hub, double *Y_hub, int N_hub){
    /*
    input: 
        xi,yi,xj,yj: coordinates of two nodes
        X_hub, Y_hub: pointer to the array of hub coordinates
        N_hub: number of hubs        
    */

    double x,y;
    double score = 0;
    // Loop over all hubs
    for (int counter_hub = 0; counter_hub < N_hub; counter_hub ++ ){
        x = X_hub[counter_hub];
        y = Y_hub[counter_hub];
        score += Green(xi,yi,x,y) * Green(xj,yj,x,y) * weight_hub(x,y);        
    }
    return score;
}


/*double score2d(double d, double alpha) {
	return (exp(-alpha * d * d));
}*/

double norm(double x, double y) {
	return (sqrt(x * x * +y * y));
}

double func_gaussian(double x, double mu, double sigma) {
	return (exp(-(x - mu) * (x - mu) / sigma / sigma));
}

void get_point(double &x, double &y) {
	double r = 1.0 * rand() / RAND_MAX;
	double q = 1.0 * rand() / RAND_MAX;

	x = r  - 0.5;
	y = q  - 0.5;
//	while (q > func_gaussian(r,0,1)){
////		cout<<q<<" "<<r<<"  "<<"trying\n";
//		r = 1.0 * rand() / RAND_MAX;
//		q = 1.0 * rand() / RAND_MAX;
//	}
//
//	double phi = 2.0*M_PI* rand() / RAND_MAX;
//	x = cos(phi)*r;
//	y = sin(phi)*r;
}


void generate_hubs(double* X, double* Y, int N_hub){
    for (int i = 0 ; i < N_hub; i++)
        get_point(X[i],Y[i]);    
}


double weight2d(double x1, double y1, double x2, double y2) {
	double d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	double w = exp(-10.0 * d);
	return w;

}

void simulate2d(int id, int N, int N_hub) {
    /*
    Input:
        id: the integer id of the current batch
        N: number of nodes
        alpha: blah blah
        N_hub: number of hubs
    */


    // X coordinates of the nodes
	double X[N];

    // y coordinates of the nodes
	double Y[N];

	double degree[N];

    
    // X coordinates of the hubs
    double X_hub[N_hub];

    // y coordinates of the hubs
    double Y_hub[N_hub];
 
    
    // generate hubs
    generate_hubs(X_hub, Y_hub, N_hub);


	ofstream f;


	stringstream filename;
	filename << "degrees-" <<  N << "-" << N_hub << ".txt";


//	const char* filename = "degrees.txt";
	cout << filename.str().c_str();
	if (id == 0)
		f.open(filename.str().c_str());
	else
		f.open(filename.str().c_str(), std::fstream::app);

	for (int i = 0; i < N; i++)
		degree[i] = 0;

	for (int i = 0; i < N; i++) {
		get_point(X[i], Y[i]);
	}


    


	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			double s = score2d(X[i],Y[i],X[j],Y[j], X_hub, Y_hub, N_hub);
			degree[i] = degree[i] + s ;
			degree[j] = degree[j] + s ;
		}
	}

	for (int i = 0; i < N; i++) {
//		cout << degree[i] << '\n';

//		if ((X[i] > 1.0 / alpha) && (X[i] < 1.0 - 1.0 / alpha)
//				&& (Y[i] > 1.0 / alpha) && (Y[i] > 1.0 - 1.0 / alpha))

		if (X[i] * X[i] + Y[i] * Y[i] < 0.1)
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

void runBatch2D(int num_repeats, int N, int N_hub) {
	for (int i = 0; i < num_repeats; i++){
        cout<< "Simulating batch no "<< i << "\n";
		simulate2d(i, N,  N_hub);
    }
        

}

int main(int argc, char *argv[]) {
	/* default values */
	int N = 1200;
    int N_hub = 100;

	/* process commandline arguments */
	if (argc == 3) {
		N = atoi(argv[1]);
		//alpha = atoi(argv[2]);
	}

	runBatch2D(10, N, N_hub);

	/*	alpha = 20;
	 for (double B = 20.0; B < 5000; B *= 1.4) {
	 N = int(alpha * B);
	 cout << N << "\n";
	 runBatch2D(100, N, alpha);
	 */

//	for (int i=0;i<1000;i++)
//		simulate1d(i,argc, argv);
}

