#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <cmath>
#include <tgmath.h> 
#include <bits/stdc++.h> 

#define PRECISION 0.0000000000000001

// Biblioteca necessária para imprimir a precisão dos long double
#include <limits>

bool isChannel(std::vector< std::vector< long double > > matrix);
bool isDistribution( std::vector< long double >  numberVector);
void printDistribution(std::vector< long double >  numberVector);
void printChannel(std::vector< std::vector< long double > > matrix);
void jointProbability( std::vector< long double > prior, std::vector< std::vector< long double > > matrix, std::vector< std::vector< long double > > *joint);
void hyperDistribution(std::vector< long double > prior, std::vector< std::vector< long double > > matrix, std::vector< std::vector< long double > > *posterior, std::vector< long double > *outer);
long double ratio(long double total, long double part);
long double shannonEntropy(std::vector< long double > prior);
long double guessingEntropy(std::vector< long double > prior);
long double bayesVulnerability(std::vector< long double > prior);
long double ktriesVulnerability(std::vector< long double > prior, int n);
long double g_Vulnerability(std::vector< long double > prior, std::vector< std::vector< long double > > gainFunction);
std::vector< std::vector < long double > > innerRefactorate(std::vector< std::vector < long double > > matrix);
std::vector < long double > outerRefactorate(std::vector< std::vector < long double > > matrix, std::vector < long double > outer);
int positionWanted(std::vector<int> columns, int wanted);
int sizeColumns(std::vector<int> columns);
std::vector<int> equalColumns(std::vector< std::vector < long double > > matrix);
long double PosteriorShannonEntropy(std::vector< long double > prior, std::vector< std::vector < long double > > matrix);
long double PosteriorGuessingEntropy(std::vector< long double > prior, std::vector< std::vector < long double > > matrix);
long double PosteriorBayesVulnerability(std::vector< long double > prior, std::vector< std::vector < long double > > matrix);
long double PosteriorKtriesVulnerability(std::vector< long double > prior, int n, std::vector< std::vector < long double > > matrix);
long double PosteriorG_Vulnerability(std::vector< long double > prior, std::vector< std::vector< long double > > gainFunction, std::vector< std::vector < long double > > matrix);





// Given a vector of numbers, verify whether it constitutes a valid probability distribution.
bool isDistribution( std::vector< long double >  numberVector){
    long double totalSum = 0;
    for (size_t i = 0; i < numberVector.size(); i++){
        if(numberVector[i] < 0) return false;
        totalSum += numberVector[i];
    } 
    if (totalSum <= (long double) (1 + PRECISION) and totalSum >= (long double) (1 - PRECISION)){
        return true;
    } else {
        return false;
    }
}

// Given a matrix of number, verify whether it constitutes a valid channel matrix.
bool isChannel(std::vector< std::vector< long double > > matrix){
    int rows = 0;
    for(size_t i = 0; i < matrix.size(); i++){
        if(isDistribution(matrix[i]))
            rows += 1;
    }
    if(rows == matrix.size())
        return true;
}

// Print beautifully a prior on the screen.
void printDistribution(std::vector< long double >  numberVector){
    if(isDistribution(numberVector)){
        for(size_t i = 0; i < numberVector.size(); i++){
            std::cout  << "\t" <<  numberVector[i];
        }   
        std::cout << std::endl;
    }
}

// Print beautifully a channel matrix on the screen.
void printChannel(std::vector< std::vector< long double > > matrix){
    for(size_t i = 0; i < matrix.size(); i++){
        printDistribution(matrix[i]);   
    }
}

// Given a prior and a channel matrix, compute the corresponding joint probability distribution.
void jointProbability( std::vector< long double > prior, std::vector< std::vector< long double > > matrix, std::vector< std::vector< long double > > *joint){
    // std::vector< std::vector< long double > > joint(  prior.size() , std::vector< long double >(matrix[0].size(), 0));
    for(size_t i = 0; i < prior.size(); i++){
        for(size_t j = 0; j < matrix[0].size(); j++){
            (*joint)[i][j] = prior[i] * matrix[i][j];
        }
    }
}

// Given a prior and a channel matrix, compute the corresponding hyper-distribution (i.e., the set of posterior distributions and the outer distribution on them).
void hyperDistribution(std::vector< long double > prior, std::vector< std::vector< long double > > matrix, std::vector< std::vector< long double > > *posterior, std::vector< long double > *outer){
    std::vector< std::vector< long double > > joint(  prior.size() , std::vector< long double >(matrix[0].size(), 0));
    jointProbability(prior, matrix, &joint);
    
    long double totalSum;
    std::vector< int > columns(matrix[0].size(), -1);
    for(size_t j = 0; j < matrix[0].size(); j++){
        totalSum = 0;
        for(size_t i = 0; i < prior.size(); i++){
            totalSum += joint[i][j]; 
        }
        if(totalSum > 0) columns[j] = totalSum;
    }
    
    
}
long double ratio(long double total, long double part){
    return part/total;
}

// Given a prior distribution, compute its Shannon entropy.
long double shannonEntropy(std::vector< long double > prior){
    long double shannon = 0;
    for(size_t i = 0; i < prior.size(); i++){
        shannon += prior[i] * (log2l(prior[i]));
    }
    return shannon*(-1);
}

// Given a prior distribution, compute its Guessing entropy.
long double guessingEntropy(std::vector< long double > prior){
    std::sort(prior.begin(), prior.end(), std::greater<long double>());
    long double guessing = 0;
    for(size_t i = 0; i < prior.size(); i++){
        guessing += i * prior[i];
    }
    return guessing;
}

//  Given a prior distribution, compute its Bayes vulnerability.
long double bayesVulnerability(std::vector< long double > prior){
    std::sort(prior.begin(), prior.end(), std::greater<long double>());
    return prior[0];
}

// Given a prior distribution and a value n>=1, compute the probability of guessing correctly within n tries. (Note that when n = 1 this function coincides with Bayes vulnerability).
long double ktriesVulnerability(std::vector< long double > prior, int n){
    std::sort(prior.begin(), prior.end(), std::greater<long double>());
    long double vulnerability = 0;
    for(size_t i = 0; i < n; i++){
        vulnerability += prior[i];
    }
    return vulnerability;
}

// Given a prior distribution and a gain function, compute the g-vulnerability. 
long double g_Vulnerability(std::vector< long double > prior, std::vector< std::vector< long double > > gainFunction){
    long double vulnerability = 0;
    long double value = -1000000;
    for(size_t i = 0; i < gainFunction.size(); i++){
        for(size_t j = 0; j < prior.size(); j++){
            vulnerability += gainFunction[i][j]*prior[j];
        }
        if(vulnerability >= value) value = vulnerability;
    }
    return value;
}

std::vector< std::vector < long double > > innerRefactorate(std::vector< std::vector < long double > > matrix){
	std::vector<int> columns = equalColumns(matrix);
	std::vector< std::vector < long double > >  refactorated(matrix.size(), std::vector < long double >(sizeColumns(columns), 0) );
	int index = 0;
	for (size_t i = 0; i < matrix[0].size(); i++) {
		if(positionWanted(columns, i) != -1){
			for (size_t j = 0; j <  matrix.size(); j++) {
				refactorated[index][j] = matrix[positionWanted(columns, i)][j];
				index++;
			}
		}
	}
}

std::vector < long double > outerRefactorate(std::vector< std::vector < long double > > matrix, std::vector < long double > outer){
	std::vector<int> columns = equalColumns(matrix);
    std::vector < long double > outerRefactorated(sizeColumns(columns), 0);
    int index = 0;
    for (size_t i = 0; i < outer.size(); i++) {
		if(positionWanted(columns, i) != -1){
				outerRefactorated[index] = outer[positionWanted(columns, i)];
				index++;
		}
	}
}

int positionWanted(std::vector<int> columns, int wanted){
	for (size_t i = 0; i < columns.size(); i++) {
		if(columns[i] == wanted) return i;
	}
	return -1;
}
int sizeColumns(std::vector<int> columns){
	int size = columns.size();
	for(int i = 0; i <  columns.size(); i++){
		for(int j = 0; j < columns.size(); j++){
			if(i != j){
				if(columns[i] == columns[j]) size--;
			}
		}
	}
	return size;
}
std::vector<int> equalColumns(std::vector< std::vector < long double > > matrix){
	std::vector<int> columns(matrix[0].size(), -1);
	int aux;
	for(int i = 0; i < matrix[0].size(); i++){
		for(int j = 0; j < matrix[0].size(); j++){
			aux = 0;
			if(columns[j] == -1){
				for(int k = 0; k < matrix.size(); k++){
					if(matrix[k][i] == matrix[k][j])	aux++;
				}
				if(aux == matrix.size()){
					columns[j] = i;
				}
			}
		}
	}
	return columns;
}

long double PosteriorShannonEntropy(std::vector< long double > prior, std::vector< std::vector < long double > > matrix){
    std::vector< long double > outer(matrix.size(), 0);
    std::vector< std::vector < long double > > posterior(matrix.size(), std::vector < long double >(matrix[0].size(), 0));
    long double posteriorShannon = 0;
    hyperDistribution(prior, matrix, &posterior, &outer);
    for(size_t i = 0; i < matrix.size(); i++){
        posteriorShannon += outer[i]*shannonEntropy(posterior[i]);
    }
    return posteriorShannon;
}
long double PosteriorGuessingEntropy(std::vector< long double > prior, std::vector< std::vector < long double > > matrix){
    std::vector< long double > outer(matrix.size(), 0);
    std::vector< std::vector < long double > > posterior(matrix.size(), std::vector < long double >(matrix[0].size(), 0));
    long double posteriorGuessing = 0; 
    hyperDistribution(prior, matrix, &posterior, &outer);
    for(size_t i = 0; i < matrix.size(); i++){
        posteriorGuessing += guessingEntropy(posterior[i]);
    }
    return posteriorGuessing;
}
long double PosteriorBayesVulnerability(std::vector< long double > prior, std::vector< std::vector < long double > > matrix){
    std::vector< long double > outer(matrix.size(), 0);
    std::vector< std::vector < long double > > posterior(matrix.size(), std::vector < long double >(matrix[0].size(), 0));
    long double posteriorBays = 0; 
    hyperDistribution(prior, matrix, &posterior, &outer);
    for(size_t i = 0; i < matrix.size(); i++){
        posteriorBays += bayesVulnerability(posterior[i]);
    }
    return posteriorBays;
}
long double PosteriorKtriesVulnerability(std::vector< long double > prior, int n, std::vector< std::vector < long double > > matrix){
    std::vector< long double > outer(matrix.size(), 0);
    std::vector< std::vector < long double > > posterior(matrix.size(), std::vector < long double >(matrix[0].size(), 0));
    long double posteriorKtries = 0;
    hyperDistribution(prior, matrix, &posterior, &outer);
    for(size_t i = 0; i < matrix.size(); i++){
        posteriorKtries += ktriesVulnerability(posterior[i], n);
    }
    return posteriorKtries;
}
long double PosteriorG_Vulnerability(std::vector< long double > prior, std::vector< std::vector< long double > > gainFunction, std::vector< std::vector < long double > > matrix){
    std::vector< long double > outer(matrix.size(), 0);
    std::vector< std::vector < long double > > posterior(matrix.size(), std::vector < long double >(matrix[0].size(), 0));
    long double posteriorG = 0; 
    hyperDistribution(prior, matrix, &posterior, &outer);
    for(size_t i = 0; i < matrix.size(); i++){
        posteriorG += g_Vulnerability(posterior[i], gainFunction);
    }
    return posteriorG;
}
long double additiveLeakage(long double prior, long double posterior){
    return posterior - prior;
}
long double multiplicativeLeakage(long double prior, long double posterior){
    return posterior/prior;
}