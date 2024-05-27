#include<cmath>
#include<iostream>
#include<vector>

// general function for mean
double mean (std::vector<double> thisVec)	{

	double runningSum = 0.0;
	int thisSize = thisVec.size();

	for(int i = 0; i < thisSize; i++){
		runningSum += thisVec[i];
	}

	return runningSum/double(thisSize);
}


// general function for standard deviation
double stdDev (std::vector<double> thisVec)	{
	
	double runningSum = 0.0;
	int thisSize = thisVec.size();

	for ( int i = 0; i < thisSize; i++ ){
		runningSum += pow((thisVec[i]- mean(thisVec) ), 2);
	}
	
	return sqrt(runningSum/(thisSize - 1));	
}	
