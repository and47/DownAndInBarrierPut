#include"BarrierOption.h"
#include<cmath>
#include<iostream>
#include"Random1.h"
#include<algorithm>
#include<vector>
#include<fstream>

using std::cout;
using std::cin;
using namespace std;

//definition of constructor
BarrierOption::BarrierOption(
	int nInt_,
	double strike_,
	double spot_,
	double vol_,
	double r_,
	double expiry_,
	double barrier_){
		nInt = nInt_;
		strike = strike_;
		spot = spot_;
		vol = vol_;
		r = r_;
		expiry = expiry_;
		barrier = barrier_;
		generatePath();
} 

//method definition
void BarrierOption::generatePath(){
	double thisDrift = (r * expiry - 0.5 * vol * vol * expiry) / double(nInt);
	double cumShocks = 0;
	thisPath.clear();
	
	for(int i = 0; i < nInt; i++){
		cumShocks += (thisDrift + vol * sqrt(expiry / double(nInt)) * GetOneGaussianByBoxMuller());
		thisPath.push_back(spot * exp(cumShocks));
	}
	
}

//method definition
bool BarrierOption::checkIfBarrierCrossed(){
	double lowestUnderlyingPrice = 0.0;
	lowestUnderlyingPrice = *std::min_element(std::begin(thisPath), std::end(thisPath));
	if (lowestUnderlyingPrice < barrier) return true;
	else return false;
}


//method definition
double BarrierOption::getLastPrice(){

	double price = 0.0;

	price = thisPath.back();

	return price;
}

//method definition
void BarrierOption::printPath(){

	for(int i = 0;  i < nInt; i++){
	
		std::cout << thisPath[i] << "\n";

	}

}

//method definition
double BarrierOption::MonteCarloThisBarrierPutSeveralTimes(int nReps){

	double rollingSum = 0.0;
	double thisLast = 0.0;
	bool barrierCrossed = false;

	for(int i = 0; i < nReps; i++){
		generatePath();
		thisLast=getLastPrice();
		barrierCrossed = checkIfBarrierCrossed();
		if (barrierCrossed) {
			rollingSum += (thisLast < strike)? (strike - thisLast) : 0; }
		if (nReps < 5){
			printPath();
			cout << "Last price of underlying in this generated path = " << thisPath.back() << "\n";}
	}
	
	  ofstream myfile;
	  myfile.open ("simulation.txt", std::ios_base::app);
      myfile << (rollingSum/double(nReps))/exp(r*expiry) << "\n";
      myfile.close();

	return (rollingSum/double(nReps))/exp(r*expiry);

}

//overloaded operator ();
double BarrierOption::operator()(char char1, char char2, int nReps){
	if ((char1 == 'I') & (char2 =='P')) return MonteCarloThisBarrierPutSeveralTimes(nReps);
//	else if ((char1 == 'O') & (char2 =='P')) return downAndOutBarrierPut(nReps);
	else return -99;
}