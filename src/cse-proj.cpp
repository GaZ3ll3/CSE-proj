//============================================================================
// Name        : cse-proj.cpp
// Author      : 
// Version     :
// Copyright   : Copyright@lurker 2014
// Description : CSE PROJECT in C++, Ansi-style
//============================================================================

#include "WENO.h"
using namespace std;

int test_PWENO1D() {
	// test program
	std::cout<< std::setw(8) << "N" << std::setw(10) << "steps" << std::setw(15)
	<< "delta_t" << std::setw(20) << "ORDER3" << std::setw(12) << "ORDER5" <<
	std::setw(15) << "ORDER7" << std::setw(15)<< "ORDER9" << '\n';
	int N = 5;
	int time_step = 3;
	double delta_t = 1./3;
	for (int k = 1;k < 6; k++){
		N *=2;
		Grid_1D grid(.0,1.0, N); // 11 nodes
		VECTOR init_state(N+1);
//		time_step *= 2;
//		delta_t /= 2.0;
		for (int i = 0 ; i < N + 1; i++){
			init_state(i) = sin(2*PI*i/(N));
		}
		// periodic boundary
		WENO SOLVER;
		std::cout<< std::setw(8) << N << std::setw(10) << time_step <<
				std::setw(15) << delta_t << std::setw(20);
		SOLVER.PWENO_1D(0,ORDER3, init_state,grid,time_step, delta_t);
		std::cout << '\t';
		SOLVER.PWENO_1D(0,ORDER5, init_state,grid,time_step, delta_t);
		std::cout << '\t';
		SOLVER.PWENO_1D(0,ORDER7, init_state,grid,time_step, delta_t);
		std::cout << '\t';
		SOLVER.PWENO_1D(0,ORDER9, init_state,grid,time_step, delta_t);
		std::cout << '\n';
	}

	return 0;
}

int test_PWENO2D() {
	// test program
	std::cout<< std::setw(8) << "N" << std::setw(10) << "steps" << std::setw(15)
	<< "delta_t" << std::setw(20) << "ORDER3" << std::setw(12) << "ORDER5" <<
	std::setw(15) << "ORDER7" << std::setw(15)<< "ORDER9" << '\n';
	int N = 5;
	int time_step = 3;
	double delta_t = 1./3;
	for (int k = 1;k < 6; k++){
		N *=2;
		Grid_2D grid(.0,1.0, N, .0, 1.0 ,N); // 11 nodes
		MATRIX init_state(N+1,N+1);
//		time_step *= 2;
//		delta_t /= 2.0;
		for (int i = 0 ; i < N + 1; i++){
			for (int j = 0; j < N+1; j++){
				init_state(i,j) = sin(2*PI*i/(N))*sin(2*PI*j/(N));
			}
		}
		// periodic boundary
		WENO SOLVER;
		std::cout<< std::setw(8) << N << std::setw(10) << time_step <<
				std::setw(15) << delta_t << std::setw(20);
		SOLVER.PWENO_2D(0,ORDER3, init_state,grid,time_step, delta_t);
		std::cout << '\t';
		SOLVER.PWENO_2D(0,ORDER5, init_state,grid,time_step, delta_t);
		std::cout << '\t';
		SOLVER.PWENO_2D(0,ORDER7, init_state,grid,time_step, delta_t);
		std::cout << '\t';
		SOLVER.PWENO_2D(0,ORDER9, init_state,grid,time_step, delta_t);
		std::cout << '\n';
	}

	return 0;
}

int main(){
	test_PWENO1D();
	test_PWENO2D();
}
