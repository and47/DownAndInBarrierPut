#include<iostream>
#include<vector>
#include"BarrierOption.h"
#include<ctime>
#include<cstdlib>
#include"functions.h"

using std::vector;
using std::cout;
using std::cin;

int main(){
	// Variables that user is expected to enter

	double Expiry;
	double workingDays;
	double Strike; 
	double Spot; 
	double Volat; 
	double r;
	double Barrier;
	unsigned long NumberOfPaths;

	cout << "\nEnter expiry (e.g. 0.5 for half of year, 0 for default!):\n";
	cin >> Expiry;

	// set the seed
	srand( time(NULL) );

	if(Expiry)	// If expiry = 0 is entered, the program runs monte carlo simulation with default characteristics of option, see below
		{
			cout << "\nNumber of working days (daily price changes, e.g. 126 for half a year):\n";
			cin >> workingDays;

			cout << "\nEnter strike (e.g. 200):\n";
			cin >> Strike;
	
			cout << "\nEnter the barrier (makes sense if barrier < strike price for Down-And-In Barrier Put ):\n";
			cin >> Barrier;

			cout << "\nEnter spot price of underlying asset (e.g. 195):\n";
			cin >> Spot;

			cout << "\nEnter volatility (e.g. 0.2):\n";
			cin >> Volat;

			cout << "\nEnter risk-free rate (e.g. 0.06):\n";
			cin >> r;

			cout << "\nNumber of paths (if less than 5, each path will be printed):\n";
			cin >> NumberOfPaths;

			// create a new instance of class
			// BarrierOption myOption(126, 200, 195, 0.2, 0.06, 0.5, 200);	// for now Strike = Barrier meaning vanilla Put
			BarrierOption myOption(workingDays, Strike, Spot, Volat, r, Expiry, Barrier);

			//run Monte Carlo to obtain theoretical price of barrier put
			cout << "The Price of Down-And-In Barrier Put = "  << myOption.MonteCarloThisBarrierPutSeveralTimes(NumberOfPaths)  << "\n";


			//call Monte Carlo via overloaded () operator
			cout << "\n Calling functions via operator() \n";
			cout << "Price of Down-And-In Barrier Put = " <<  myOption('I', 'P', NumberOfPaths) << "\n";

			//check whether data generating process runs correctly 
			//(is the expected price and volatility of underlying close to option parameters?)
			vector<double> myVec2;
			for(int i = 0; i < 1000; i++){
				myOption.generatePath();
				myVec2.push_back(myOption.thisPath.back());
			}

			cout << "\n\nSome technical info:\nmean of myVec is " << mean(myVec2) << "\n";
			cout << "stddev of myVec is " << stdDev(myVec2) << "\n";

	}
	
	// If no characteristics were defined, run monte carlo with default characteristics of option
	
	else{

		NumberOfPaths = 20000;
		BarrierOption myOption(126, 200, 195, 0.2, 0.06, 0.5, 175);
		cout << "\nDefault characteristics run:\n\nExpiration = Half a Year with 126 working days (price changes)\n\n Strike = $200\nBarrier = $175\n Meaning DEFAULT project simulation! \nStarting price of underlying asset at $195\n\nVolatility = 20% and Risk-free Rate set to 6%\n\n20000 random paths will be generated, shouldn't take long...\n\n Loop is underway, 100 simulations performed! \n\n The results will be written (append) in simulation.txt file\n\n Note: Standard deviation of simulations results in project is based on this file \n";

		//run Monte Carlo to obtain theoretical price of barrier put
		for(int i = 0; i < 50; i++){	// two simulation one called by overloading operator, 50 times x 2 = 100 simulations. 100 results will be written to file
		cout << "The Price of Down-And-In Barrier Put = "  << myOption.MonteCarloThisBarrierPutSeveralTimes(NumberOfPaths)  << "\n";
		cout << "Price of Down-And-In Barrier Put = " <<  myOption('I', 'P', NumberOfPaths) << "\n";}
		//check whether data generating process runs correctly 
		//(is the expected price and volatility of underlying close to option parameters?)
		vector<double> myVec2;
		for(int i = 0; i < 1000; i++){
			myOption.generatePath();
			myVec2.push_back(myOption.thisPath.back());
		}

		cout << "\n\nSome technical info:\nmean of myVec is " << mean(myVec2) << "\n";
		cout << "stddev of myVec is " << stdDev(myVec2) << "\n";
	}


	// To make sure the window doesn't close
	double tmp;
    cin >> tmp;

	return 0;
}