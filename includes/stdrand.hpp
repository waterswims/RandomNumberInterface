#pragma once

#include "randbase.hpp";
#include <random>;

namespace watersoft
{
namespace random
{
    ///////////////////////////////////////////////////////////////////////////
    /// Random number generators which uses the STD library
    ///////////////////////////////////////////////////////////////////////////
    class StdRand : public RandBase
    {
    private:
        std::mt19937 generator = std::mt19937();
        std::uniform_real_distribution<double> uniformDistribution =    
            std::uniform_real_distribution<double>(0, 1);
        std::uniform_int_distribution<int> uniformIntDistribution =
            std::uniform_int_distribution<int>(0, 1);
        std::normal_distribution<double> normalDistribution =
            std::normal_distribution<double>(0, 1);
        std::lognormal_distribution<double> lognormalDistribution =
            std::lognormal_distribution<double>(0, 1);

        const unsigned int GEN_MIN = std::mt19937::min();
        const unsigned int GEN_MAX = std::mt19937::max();
    public:
        ///////////////////////////////////////////////////////////////////////
        /// \brief Change the current random seed.
        ///
        /// \param seed The new seed.
        ///////////////////////////////////////////////////////////////////////
        void change_seed(int seed) override;
        ///////////////////////////////////////////////////////////////////////
        /// Return a single random number between 0 and 1.
        ///////////////////////////////////////////////////////////////////////
        double generateUniform() override;
        ///////////////////////////////////////////////////////////////////////
        /// Return an integer which can be either 0 or 1.
        ///////////////////////////////////////////////////////////////////////
        int generateBool() override;
        ///////////////////////////////////////////////////////////////////////
        /// Return a random number from a normal distribution.
        ///////////////////////////////////////////////////////////////////////
        double generateNormal() override;
        ///////////////////////////////////////////////////////////////////////
        /// Return a random number from a lognormal distribution.
        ///////////////////////////////////////////////////////////////////////
        double generateLognormal() override;
        ///////////////////////////////////////////////////////////////////////
        /// Return a random vector on the surface of a sphere.
        ///////////////////////////////////////////////////////////////////////
        void generateVector(double* a, double* b, double* c) override;
    };
}
}