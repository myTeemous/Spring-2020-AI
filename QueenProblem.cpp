/*
Kenneth Ratliff
Artificial Intelligence
Spring 2020
Final Project 2 - 7

Solve the 8 x 8 Queen problem using backtracking

Description: Make sure each queen on the board is not in the attack path of another queen.
*/

#include<iostream>
#include<vector>
#include<cmath>

void solveQueenProblem(int, int, std::vector<int>&, std::vector<std::vector<int>>&);
bool placementsValid(std::vector<int>&);
void printSolutions(std::vector<std::vector<int>>&);

int main() {

	//An array that will store all of the 
	std::vector<int> placements;

	//An array of arrays. Each array is a different solution that contains the valid queen positions for that specific solution 
	std::vector<std::vector<int>> solutions;

	solveQueenProblem(0, 8, placements, solutions);

	std::cout << "Number of solutions: " << solutions.size() << "\n\n";

	printSolutions(solutions);

	system("pause");

	return 0;
}

//To solve the 8 x 8 Queen Problem I use recursion and backtracking
void solveQueenProblem(int currentRow, int numberOfQueens, std::vector<int>& queenPlacements, std::vector<std::vector<int>>& solutions) {
	
	//Base case: When the current row is equal to the total number of queens that need to be placed, 
	//we know that we have found a valid queen placement on every row.
	if (currentRow == numberOfQueens) {
		solutions.push_back(queenPlacements);
	}
	else {
		//Iterate through each column position at the current row and 
		//check if the current position is a valid queen placement
		for (int col = 0; col < numberOfQueens; col++) {
			queenPlacements.push_back(col);

			if (placementsValid(queenPlacements)) {
				//If the placement is valid, move to the next row and repeat the process
				solveQueenProblem(currentRow + 1, numberOfQueens, queenPlacements, solutions);
			}
			//Backtrack. Remove the position that was just checked and try the next one
			queenPlacements.pop_back();
		}
	}
}

//Check to see if the most recent queen placement conflicts 
//with any other queen placements that have already been validated.
bool placementsValid(std::vector<int>& queenPlacements) {
	
	int rowID = queenPlacements.size() - 1;

	for (int i = 0; i < rowID; i++) {
		int difference = std::abs(queenPlacements[i] - queenPlacements[rowID]);
		
		if (difference == 0 || difference == rowID - i) {
			return false;
		}
	}
	return true;
}

//Display each solution
void printSolutions(std::vector<std::vector<int>>& solutions) {

	//Dimensions of the chess board
	const int ROW = 8;
	const int COLUMN = 8;
	int solutionCount = 1;

	for (const auto& solution : solutions) {
		//Make an empty chess board. A zero represents an empty position
		std::vector<std::vector<int>> board(ROW, std::vector<int>(COLUMN, 0));

		for (int row = 0; row < solution.size(); row++) {
			//Place the queens on the board. A one represents a queen
			board[solution[row]][row] = 1;
		}

		std::cout << "Solution " << solutionCount << ":\n\n";

		//Print the board for the current solution
		for (int i = 0; i < ROW; i++) {
			for (int k = 0; k < COLUMN; k++) {
				std::cout << board[i][k] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";

		solutionCount++;
	}
}