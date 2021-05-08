#include "../includes/stdrand.hpp";

#include <cmath>

namespace watersoft
{
namespace random
{
	void StdRand::change_seed(int seed)
	{
		generator.seed(seed);
	}

	double StdRand::generateUniform()
	{
		return uniformDistribution(generator);
	}

	int StdRand::generateBool()
	{
		return uniformIntDistribution(generator);
	}

	double StdRand::generateNormal()
	{
		return normalDistribution(generator);
	}

	double StdRand::generateLognormal()
	{
		return lognormalDistribution(generator);
	}

	void StdRand::generateVector(double* a, double* b, double* c)
	{
		double x = generateNormal();
		double y = generateNormal();
		double z = generateNormal();

		double x2 = x * x;
		double y2 = y * y;
		double z2 = z * z;

		double scaleFactor = 1.0 / pow(x2 + y2 + z2, 0.5);

		*a = x * scaleFactor;
		*b = y * scaleFactor;
		*c = z * scaleFactor;
	}
}
}