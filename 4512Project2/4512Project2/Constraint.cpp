#include <vector>
#include <iostream>
#include "Constraint.h"

template <typename T>
std::ostream& operator <<
(std::ostream& os, const std::vector<std::vector<T>>
	& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.at(i).size(); j++)
		{
		os << matrix[i][j] << ", ";
		}
		os << std::endl;
	}
	os << std::endl;
	return os;
}

int Constraint::getM() { return m; }
int Constraint::getN() { return n; }
int Constraint::getNumCols() { return numCols; }
void Constraint::setVal(int i, int j, double n)
{
	cCoeff.at(i).at(j) = n;

	//return cCoeff.at(i).at(j);
}
std::vector<std::vector<double>> Constraint::getCoeff() { return cCoeff; }

double Constraint::at(int i, int j)
{
	return cCoeff.at(i).at(j);
}

std::vector<double> Constraint::at(int i)
{
	return cCoeff.at(i);
}


Constraint::Constraint(int m, int n, std::vector<std::vector<double>> coefficients)
{
	this->m = m;
	this->n = n;

	/* Add m for slacks, add 1 for z column, add 1 for RHS.*/
	numCols = n + m + 2;
	cCoeff = coefficients;
	
	/* A vector to temporarily store the RHS value of each constraint. Need
	this so the RHS appears at the rightmost side of the matrix after the
	slack variables have been added. */
	std::vector<double> rhs;

	for (int i = 0; i < m; i++)
	{
		/* Grab the last number in each row of the coefficients matrix. */
		rhs.push_back(coefficients.at(i).at(n));
	}

	for (int i = 0; i < m; i++)
	{
		cCoeff.at(i).pop_back(); // Remove the last value from coefficients matrix.
		
	}
	
	/* Resize constraints matrix to include 0s for slack variables. 
	Diagonal of 1's are added next. */
	for (int i = 0; i < m; i++)
	{
		cCoeff.push_back(std::vector<double>());

		for (int j = n; j < n+m; j++)
		{
			cCoeff.at(i).push_back(0);
		}
	}
	
	int j = n;
	/* Changing the diagonal of slacks to 1's. */
	for (int i = 0; i < m; i++) 
	{
		cCoeff.at(i).at(j) = 1;
		j++;
		
	}

	/* Pushing the RHS value to the end of the matrix.
	Also add a 0 to the front to represent z. */
	for (int i = 0; i < m; i++)
	{
		cCoeff[i].push_back(rhs[i]);

		cCoeff[i].insert(cCoeff[i].begin(), 0);
	}
}

void Constraint::printConstraint()
{
	std::cout << cCoeff;
}


		