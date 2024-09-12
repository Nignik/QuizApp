#pragma once

#include <random>
#include <vector>

inline std::random_device rd;
inline std::mt19937 g{ rd() };

template<typename T>
inline void shuffleRandom(std::vector<T>& deck)
{
	std::shuffle(deck.begin(), deck.end(), g);
}
