//============================================================================
// Name        : WENO.cpp
// Author      : lurker
// Version     : 0.0.1
// Copyright   : Copyright@nlmd_group 2014
// Description : WENO in C++, Ansi-style
//============================================================================

//#include <iostream>
#include "Util.hpp"
#include "WENO.hpp"
#include "Interpolation.hpp"
using namespace std;

long timer()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

int test1D_Const_Delta_t_Const_Vel() {
	std::cout<< std::setw(8) << "N" << std::setw(10) << "steps" << std::setw(15)
		<< "delta_t" << std::setw(16) << "ORDER3" << std::setw(16) << "ORDER5" <<
		std::setw(16) << "ORDER7" << std::setw(16)<< "ORDER9" << '\n';
		int N = 5;
		int time_step = 3;
		double delta_t = 1./3;
		for (int k = 1;k < 6; k++){
			N *=2;
//			time_step *= 2;
//			delta_t /= 2.;
			Grid_1D grid(.0,1.0, N);
			Vector<double> init_state(N);
			for (int i = 0 ; i < N ; i++){
				init_state(i) = sin(2*PI*i/(N));
			}
			// periodic boundary
			WENO SOLVER;
			std::cout.unsetf(ios::fixed | ios::scientific);
			std::cout<< std::setw(8) << N << std::setw(10) << time_step <<
					std::setw(15) << delta_t << std::scientific;
			SOLVER.CWENO1D(init_state,grid,3,time_step,delta_t,1.0);
			SOLVER.CWENO1D(init_state,grid,5,time_step,delta_t,1.0);
			SOLVER.CWENO1D(init_state,grid,7,time_step,delta_t,1.0);
			SOLVER.CWENO1D(init_state,grid,9,time_step,delta_t,1.0);
			std::cout << '\n';
		}

		return 0;
}

int test2D_Const_Delta_t_Const_Vel() {
	std::cout<< std::setw(8) << "N" << std::setw(10) << "steps" << std::setw(15)
		<< "delta_t" << std::setw(16) << "ORDER3" << std::setw(16) << "ORDER5" <<
		std::setw(16) << "ORDER7" << std::setw(16)<< "ORDER9" << '\n';
		int N = 5;
		int time_step = 3;
		double delta_t = 1./3;
		for (int k = 1;k < 6; k++){
			N *=2;
//			time_step *= 2;
//			delta_t /= 2.;
			Grid_2D grid(.0,1.0, N,0.,1.,N);
			Matrix<double> init_state(N,N);
			for (int i = 0 ; i < N ; i++){
				for(int j=0; j<N;j++){
					init_state(i,j) = sin(2*PI*i/(N))*sin(2*PI*j/(N));
				}

			}
			// periodic boundary
			WENO SOLVER;
			std::cout.unsetf(ios::fixed | ios::scientific);
			std::cout<< std::setw(8) << N << std::setw(10) << time_step <<
					std::setw(15) << delta_t << std::scientific;
			SOLVER.CWENO2D(init_state,grid,3,time_step,delta_t,1.0,1.0);
			SOLVER.CWENO2D(init_state,grid,5,time_step,delta_t,1.0,1.0);
			SOLVER.CWENO2D(init_state,grid,7,time_step,delta_t,1.0,1.0);
			SOLVER.CWENO2D(init_state,grid,9,time_step,delta_t,1.0,1.0);
			std::cout << '\n';
		}

		return 0;
}

int test3D_Const_Delta_t_Const_Vel() {
	std::cout<< std::setw(8) << "N" << std::setw(10) << "steps" << std::setw(15)
		<< "delta_t" << std::setw(16) << "ORDER3" << std::setw(16) << "ORDER5" <<
		std::setw(16) << "ORDER7" << std::setw(16)<< "ORDER9" << '\n';
		int N = 5;
		int time_step = 3;
		double delta_t = 1./3;
		for (int k = 1;k < 5; k++){
			N *=2;
//			time_step *= 2;
//			delta_t /= 2.;
			Grid_3D grid(.0,1.0, N,0.,1.,N , 0., 1., N);
			Tensor<double> init_state(N,N, N);
			for (int i = 0 ; i < N ; i++){
				for(int j=0; j<N;j++){
					for (int k = 0; k<N; k++){
						init_state(i,j,k) = sin(2*PI*i/(N))*sin(2*PI*j/(N))*sin(2*PI*k/(N));
					}
				}

			}
			// periodic boundary
			WENO SOLVER;
			std::cout.unsetf(ios::fixed | ios::scientific);
			std::cout<< std::setw(8) << N << std::setw(10) << time_step <<
					std::setw(15) << delta_t << std::scientific;
			SOLVER.CWENO3D(init_state,grid,3,time_step,delta_t,1.0,1.0,1.0);
			SOLVER.CWENO3D(init_state,grid,5,time_step,delta_t,1.0,1.0,1.0);
			SOLVER.CWENO3D(init_state,grid,7,time_step,delta_t,1.0,1.0,1.0);
			SOLVER.CWENO3D(init_state,grid,9,time_step,delta_t,1.0,1.0,1.0);
			std::cout << '\n';
		}

		return 0;
}

double Vel_2D_X(double x,double y,  double t){
	return -y;
}

double Vel_2D_Y(double x, double y, double t){
	return x;
}
int test2D_Const_CFL_Variable_Vel() {
	std::cout<< std::setw(8) << "N" << std::setw(10) << "steps" << std::setw(15)
		<< "delta_t"<< std::setw(16) << "ORDER3" << std::setw(16) << "ORDER5" <<
		std::setw(16) << "ORDER7" << std::setw(16)<< "ORDER9" << std::setw(16) << "Elapse" <<  '\n';
		int N = 50;
		int time_step = 30;
		double delta_t =2*PI/30;
		FuncVel_2D Vel_X, Vel_Y;
		Vel_X = Vel_2D_X;
		Vel_Y = Vel_2D_Y;
		for (int k = 0;k < 5; k++){
			N = floor(N*1.25992104989); // cubic root of 2, should see halving effect
			//time_step = 2 * N;
			//delta_t = 2*PI/time_step;
			Grid_2D grid(-1.,1., N,-1.,1.,N);
			Matrix<double> init_state(N,N);
			for (int i = 0; i < grid.size_x; i++){
				for (int j = 0; j < grid.size_y; j++){
						if (pow(grid.start_x + i *grid.delta_x,2) + pow(grid.start_y + j *grid.delta_y,2) < 0.64)
							init_state(i,j) = 1.0 + cos(sqrt(pow(grid.start_x + i *grid.delta_x,2) + pow(grid.start_y + j *grid.delta_y,2))*PI/2.0/0.4);
				}
			}

			WENO SOLVER;
			std::cout.unsetf(ios::fixed | ios::scientific);
			std::cout << std::setw(8) << N << std::setw(10) <<time_step <<
					std::setw(15) << delta_t << std::scientific;
			long start = timer();
			SOLVER.VWENO2D(init_state,grid,3,time_step,delta_t,Vel_X,Vel_Y);
			SOLVER.VWENO2D(init_state,grid,5,time_step,delta_t,Vel_X,Vel_Y);
			SOLVER.VWENO2D(init_state,grid,7,time_step,delta_t,Vel_X,Vel_Y);
			SOLVER.VWENO2D(init_state,grid,9,time_step,delta_t,Vel_X,Vel_Y);
			long elapse = timer() - start;
			std::cout.unsetf(ios::fixed | ios::scientific);
			std::cout << setw(16) << elapse/1000000.0 << std::endl;
			std::cout << '\n';


		}

		return 0;
}

int testTensor(){
	Tensor<int> A(3,3,3);
	Tensor<int> B(3,3,3);
	Vector<int> C(3);
	A(0,0,0) = 1;
	A(1,1,1) = 2;

	A += 1;

	cout << A(0,0,0) << A(1,1,1);

	B += 1;

	A += B;

	cout << A(0,0,0) << A(1,1,1);

	C = A.slicerc(1,1);

	cout << C(0) << C(1) << C(2) ;

	cout << A.sqnorm() << endl;
	return 0;
}

int testVector(){
	Vector<int> A(3);
	Vector<int> B(3);
	A(0) = 1; A(1) = 2;A(2) = 3;
	cout << A(0) << A(3) << endl;
	A += 1;

	cout << A(0) << endl;
	B = A;

	A += B;

	cout << A(0) << A(-5) << endl;

	cout << A.sqnorm() << endl;
	return 0;
}
int main(){
//	testVector();
//	testTensor();
//	test1D_Const_Delta_t_Const_Vel();
	test2D_Const_CFL_Variable_Vel();
//	test2D_Const_Delta_t_Const_Vel();
//	test3D_Const_Delta_t_Const_Vel();
}
