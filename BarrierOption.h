#include<vector>


class BarrierOption{
public:

	//constructor
	BarrierOption(
		int nInt_,
		double strike_,
		double spot_,
		double vol_,
		double r_,
		double expiry_,
		double barrier_
		);

	//destructor
	~BarrierOption(){};

	//methods
	void generatePath();
	bool checkIfBarrierCrossed();
	double getLastPrice();
	void printPath();
	double MonteCarloThisBarrierPutSeveralTimes(int nReps);

	//overloaded operator ()
	double operator()(char char1, char char2, int nReps);

	//members
	std::vector<double> thisPath;
	int nInt;
	double strike;
	double spot;
	double vol;
	double r;
	double expiry;
	double barrier;

};