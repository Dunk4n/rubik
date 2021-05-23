/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:27:51 by niduches          #+#    #+#             */
/*   Updated: 2021/05/23 01:37:00 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include "Rubik.hpp"

Rubik::vec3	pos[20] =
{
	{0, 1, -1},
	{1, 1, 0},
	{0, 1, 1},
	{-1, 1, 0},

	{0, -1, -1},
	{1, -1, 0},
	{0, -1, 1},
	{-1, -1, 0},

	{1, 0, -1},
	{-1, 0, -1},

	{1, 0, 1},
	{-1, 0, 1},

	{1, 1, -1},
	{1, 1, 1},
	{-1, 1, 1},
	{-1, 1, -1},

	{1, -1, -1},
	{-1, -1, -1},
	{-1, -1, 1},
	{1, -1, 1},
};

void		Rubik::set_id(Rubik::vec3 pos, int *id, int *dir)
{
	uint	i = 0;

	while (i < this->nb_cube)
	{
		if (this->cubes[i].pos == pos)
		{
			*id = this->cubes[i].id;
			*dir = this->cubes[i].dir % (this->cubes[i].id < 12 ? 2 : 3);
			return ;
		}
		++i;
	}
	return ;
}


int applicableMoves[] = {0, 262143, 259263, 74943, 74898};

int affectedCubies[][8] =
{
	{0, 1, 2, 3, 0, 1, 2, 3},	// U
	{4, 7, 6, 5, 4, 5, 6, 7},	// D
	{0, 9, 4, 8, 0, 3, 5, 4},	// F
	{2, 10, 6, 11, 2, 1, 7, 6},	// B
	{3, 11, 7, 9, 3, 2, 6, 5},	// L
	{1, 8, 5, 10, 1, 0, 4, 7},	// R
};

std::vector<int> applyMove(int move, std::vector<int> state)
{
	int turns = move % 3 + 1;
	int face = move / 3;

	while (turns--)
	{
		std::vector<int> oldState = state;
		for (int i = 0; i < 8; i++)
		{
			int isCorner = i > 3;
			int target = affectedCubies[face][i] + isCorner * 12;
			int killer = affectedCubies[face][(i & 3) == 3 ? i - 3 : i + 1] + isCorner * 12;
			int orientationDelta = (i < 4) ? (face > 1 && face < 4) : (face < 2) ? 0 : 2 - (i & 1);
			state[target] = oldState[killer];
			state[target + 20] = oldState[killer + 20] + orientationDelta;
			if(!turns)
				state[target + 20] %= 2 + isCorner;
		}
	}
	return state;
}

int		inverse(int move)
{
	return (move + 2 - 2 * (move % 3));
}


std::vector<int> id(std::vector<int> state, int phase)
{
	if (phase < 2)
		return (std::vector<int>(state.begin() + 20, state.begin() + 32));
	if (phase < 3)
	{
		std::vector<int>	result(state.begin() + 31, state.begin() + 40);
		for (int i = 0; i < 12; i++)
			result[0] |= (state[i] / 8) << i;
		return (result);
	}
	if (phase < 4){
		std::vector<int> result(3);
		for (int i = 0; i < 12; ++i)
			result[0] |= ((state[i] > 7) ? 2 : (state[i] & 1)) << (2 * i);
		for (int i = 0; i < 8; ++i)
			result[1] |= ((state[i + 12] - 12) & 5) << (3 * i);
		for (int i = 12; i < 20; ++i)
			for (int j = i + 1; j < 20; ++j)
				result[2] ^= state[i] > state[j];
		return (result);
	}
	return (state);
}

void	display_move(class Rubik *ru, std::vector<int> &algorithm, std::vector<int> &currentState, std::string &sol)
{
	std::string new_instruction = "";
	std::string direction[6] = {"up", "down", "front", "back", "left", "right"};

	for (int i = 0; i < (int)algorithm.size(); i++)
	{
		new_instruction.clear();
		new_instruction = "UDFBLR"[(algorithm[i] / 3) % 6];

		if (algorithm[i] % 3 + 1 == 2)
			new_instruction += '2';
		else if (algorithm[i] % 3 + 1 == 3)
			new_instruction += '\'';
		if (ru->get_human_readable() == true)
		{
			std::cout << new_instruction << ':' << std::endl;
			std::cout << "Rotate the " << direction[(algorithm[i] / 3) % 6] << " face ";
			if (algorithm[i] % 3 + 1 == 2)
				std::cout << "two times ";
			else
				std::cout << "one time ";
			if (algorithm[i] % 3 + 1 == 3)
				std::cout << "cunter";
			std::cout << "clockwise." << std::endl;
			std::cout << std::endl;
		}
		sol += new_instruction;
		sol += ' ';
		currentState = applyMove(algorithm[i], currentState);
	}
}

void	make_phase(class Rubik *ru, int phase, std::vector<int> &currentState, std::vector<int> &goalState, std::string &sol)
{
	std::vector<int> currentId = id(currentState, phase);
	std::vector<int> goalId = id(goalState, phase);

	if(currentId == goalId)
		return ;
	std::queue<std::vector<int>> q;
	q.push(currentState);
	q.push(goalState);
	std::map<std::vector<int>, std::vector<int>> predecessor;
	std::map<std::vector<int>, int> direction;
	std::map<std::vector<int>, int> lastMove;
	direction[currentId] = 1;
	direction[goalId] = 2;
	while (1)
	{
		std::vector<int> oldState = q.front();
		q.pop();
		std::vector<int> oldId = id(oldState, phase);
		int &oldDir = direction[oldId];

		for (int move = 0; move < 18; ++move)
		{
			if (!(applicableMoves[phase] & (1 << move)))
				continue ;
			std::vector<int> newState = applyMove(move, oldState);
			std::vector<int> newId = id(newState, phase);
			int &newDir = direction[newId];
			if (newDir && newDir != oldDir)
			{
				if (oldDir > 1)
				{
					swap(newId, oldId);
					move = inverse(move);
				}
				std::vector<int> algorithm(1, move);
				while (oldId != currentId)
				{
					algorithm.insert(algorithm.begin(), lastMove[oldId]);
					oldId = predecessor[oldId];
				}
				while (newId != goalId)
				{
					algorithm.push_back(inverse(lastMove[newId]));
					newId = predecessor[newId];
				}
				display_move(ru, algorithm, currentState, sol);
				return ;
			}
			if(!newDir)
			{
				q.push(newState);
				newDir = oldDir;
				lastMove[newId] = move;
				predecessor[newId] = oldId;
			}
		}
	}
}

int		thistlethwaite(class Rubik *ru, std::vector<int> &currentState, std::string &sol)
{
	int					phase;
	std::vector<int>	goalState(40);
  
	for (int i = 0; i < 20; i++)
		goalState[i] = i;
	phase = 0;
	while (phase < 5)
		make_phase(ru, ++phase, currentState, goalState, sol);
	return (0);
}

void		Rubik::format(void)
{
	std::vector<int> currentState(40);
	int	i = 0;

	while (i < 20)
	{
		set_id(pos[i], &currentState[i], &currentState[i + 20]);
		++i;
	}
	thistlethwaite(this, currentState, this->solution);
}
