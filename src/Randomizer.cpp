#include "Randomizer.h"


float Randomizer::RandomNumber()
{
	m_random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	if (m_random == 1.0f)
	{
		RandomNumber();
	}

	return m_random;
}
