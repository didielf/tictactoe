// TicTacToeLab.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <time.h>
#include <list>
#include <vector>
#include <cstdlib>

enum Player { Human = 0, Computer = 1 };

struct aiMove
{
	aiMove() {};
	aiMove(int score) {};
	int index;
	int score;
};

class Tictactoe
{
public:
	Player player;
	char matrix[9] = { ' ',' ', ' ',' ', ' ', ' ', ' ', ' ', ' ' };


	Tictactoe()
	{
		int n = rand() % 2 + 1;
		n == 1 ? player = Human : player = Computer;

	}

	void Play()
	{
		Draw();
		do
		{
			if (player == Human)
			{
				PlayHuman();
				player = Computer;
			}
			else {
				if (emptySpaces(matrix).size() == 9) {
					matrix[0] = '0';
					Draw();
				}
				else
					PlayComputer();
				player = Human;
			}
		} while (winner(matrix, Computer) == false && winner(matrix, Human) == false && emptySpaces(matrix).size() != 0);
		if(winner(matrix, Computer) == true)
			cout << endl << "	You lost the game." << endl << endl;
		else if (winner(matrix, Human) == true)
			cout << endl << "	You won the game." << endl << endl;
		else
			cout << endl
			<< "	A draw." << endl << endl;

	}

	void PlayHuman()
	{
		int n = -1;
		do
		{
			cout << endl << "	Enter a number: ";
			cin >> n;
			if (matrix[n - 1] == ' ')
			{
				matrix[n - 1] = 'X';
				Draw();
				break;
			}
			else
				cout << "	<<Not a valid move>>";

		} while (matrix[n - 1] != ' ');
	}

	void PlayComputer()
	{
		aiMove bmove = minimax(matrix, Computer);
		matrix[bmove.index] = '0';
		Draw();
	}

	char getPlayerChar(Player player)
	{
		return player == Human ? 'X' : '0';
	}

	std::vector<int> emptySpaces(char newMatrix[9])
	{
		std::vector<int> temp;
		for (int i = 0; i < 9; i++)
		{
			if (newMatrix[i] == ' ')
				temp.push_back(i);
		}
		return temp;
	}

	aiMove minimax(char *newMatrix, Player player)
	{
		std::vector<int> empSpaces = emptySpaces(newMatrix);
		if (winner(newMatrix, Computer))
		{
			aiMove m;
			m.score = 10;
			return aiMove(m);
		}
		else if (winner(newMatrix, Human))
		{
			aiMove m;
			m.score = -10;
			return aiMove(m);
		}
		else if (empSpaces.size() == 0)
		{
			aiMove m;
			m.score = 0;
			return aiMove(m);
		}

		std::vector<aiMove> moves;
		for (int i = 0; i < empSpaces.size(); i++)
		{
			aiMove move;
			move.index = empSpaces[i];
			newMatrix[empSpaces[i]] = getPlayerChar(player);
			if (player == Computer)
				move.score = minimax(newMatrix, Human).score;
			else
				move.score = minimax(newMatrix, Computer).score;

			newMatrix[empSpaces[i]] = ' ';
			moves.push_back(move);
		}

		int bestmove;

		if (player == Computer)
		{
			int thebestScore = -10000;
			for (int i = 0; i < moves.size(); i++)
			{
				if (moves[i].score > thebestScore)
				{
					thebestScore = moves[i].score;
					bestmove = i;
				}
			}
		}
		else
		{
			int thebestScore = 10000;
			for (int i = 0; i < moves.size(); i++)
			{
				if (moves[i].score < thebestScore)
				{
					thebestScore = moves[i].score;
					bestmove = i;
				}
			}
		}

		return moves[bestmove];
	}


	bool winner(char newMatrix[9], Player player)
	{
		char pchar = getPlayerChar(player);
		if (
			(newMatrix[0] == pchar && newMatrix[1] == pchar && newMatrix[2] == pchar) ||
			(newMatrix[3] == pchar && newMatrix[4] == pchar && newMatrix[5] == pchar) ||
			(newMatrix[6] == pchar && newMatrix[7] == pchar && newMatrix[8] == pchar) ||
			(newMatrix[0] == pchar && newMatrix[3] == pchar && newMatrix[6] == pchar) ||
			(newMatrix[1] == pchar && newMatrix[4] == pchar && newMatrix[7] == pchar) ||
			(newMatrix[2] == pchar && newMatrix[5] == pchar && newMatrix[8] == pchar) ||
			(newMatrix[0] == pchar && newMatrix[4] == pchar && newMatrix[8] == pchar) ||
			(newMatrix[2] == pchar && newMatrix[4] == pchar && newMatrix[6] == pchar)) {
			return true;
		}
		else
			return false;
	}

	void Draw()
	{
		system("@cls||clear");
		cout << endl << "		   Tic Tac Toe" << endl;
		cout << "	(Instructions) Select a number from 1-9" << endl << endl;

		cout << "	     |     |     " << endl;
		cout << "	  1  |  2  |  3 " << endl;
		cout << "	_____|_____|_____" << endl;
		cout << "	     |     |     " << endl;
		cout << "	  4  |  5  |  6 " << endl;
		cout << "	_____|_____|_____" << endl;
		cout << "	     |     |     " << endl;
		cout << "	  7  |  8  |  9" << endl;
		cout << "	     |     |     " << endl << endl;


		cout << "	Human Player (X) - AI Player (0)" << endl << endl;
		cout << "	     |     |     " << endl;
		cout << "	  " << matrix[0] << "  |  " << matrix[1] << "  |  " << matrix[2] << endl;
		cout << "	_____|_____|_____" << endl;
		cout << "	     |     |     " << endl;
		cout << "	  " << matrix[3] << "  |  " << matrix[4] << "  |  " << matrix[5] << endl;
		cout << "	_____|_____|_____" << endl;
		cout << "	     |     |     " << endl;
		cout << "	  " << matrix[6] << "  |  " << matrix[7] << "  |  " << matrix[8] << endl;
		cout << "	     |     |     " << endl;

	}
};

int main()
{
	srand(time(NULL));
	Player p = Human;
	Tictactoe game;
	game.Play();
	system("pause");
    return 0;
}

