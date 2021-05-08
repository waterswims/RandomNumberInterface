#pragma once

#include "catch2/catch.hpp";
#include "../includes/stdrand.hpp";
#include <vector>;
#include <cmath>;
#include <iostream>;

///////////////////////////////////////////////////////
// Non-test functions
///////////////////////////////////////////////////////

const double pi = 3.141592653589793;

double chi2(std::vector<int>& count, std::vector<double>& expect)
{
    double ans = 0;
    int skip = 0;
    for(int i=0; i < count.size(); i++)
    {
        if(count[i] == 0)
        {
            skip++;
            continue;
        }
        ans += pow((count[i] - expect[i]), 2) / expect[i];
    }
    return ans / (double)((int)count.size() - 1 - skip);
}

double beta(int a, int b)
{
    return tgamma(a)*tgamma(b)/(tgamma(a+b));
}

double binomial(int n, int k)
{
    return 1 / (k * beta(k, n-k+1));
}

void printResult(std::vector<int>& count, std::vector<double>& expect)
{
    for (int i = 0; i < count.size(); i++)
    {
        std::cout << count[i] << " " << expect[i] << std::endl;
    }
}

///////////////////////////////////////////////////////
// Random Number Tests
///////////////////////////////////////////////////////

TEST_CASE("StdRand, Integer_Test", "[std_int]")
{
    watersoft::random::StdRand myRng = watersoft::random::StdRand();

    int N_atts = 1e6, N_toss = 100;
    std::vector<int> bins(N_toss/2, 0);

    for(int i=0; i < N_atts; i++)
    {
        int N_zero = 0;
        for (int j=0; j < N_toss; j++)
        {
            if(myRng.generateBool() == 0) {N_zero++;}
        }
        bins[abs(N_zero - N_toss/2)]++;
    }

    std::vector<double> expect(N_toss/2);
    for(int i = 0; i < N_toss/2; i++)
    {
        expect[i] = binomial(N_toss, (N_toss/2)-i) * N_atts /
            float(pow(2, (N_toss - 1)));
    }
    expect[0] = expect[0] / 2;
    double chi2_test = chi2(bins, expect);

    REQUIRE(chi2_test > 0.9);
    REQUIRE(chi2_test < 1.8);
}

TEST_CASE("StdRand, Double_Test", "[std_double]")
{
    watersoft::random::StdRand myRng = watersoft::random::StdRand();

    int N_bins = 100, N_atts = 1e8;
    std::vector<int> bins(N_bins, 0);

    std::vector<double> expect(N_bins, (N_atts / N_bins));
    for(int i = 0; i < N_atts; i++)
    {
        bins[int(myRng.generateUniform() * N_bins)]++;
    }
    double chi2_test = chi2(bins, expect);
    //printResult(bins, expect);

    REQUIRE(chi2_test > 0.7);
    REQUIRE(chi2_test < 1.3);
}

TEST_CASE("StdRand, Lognormal_Test", "[std_ln]")
{
    watersoft::random::StdRand myRng = watersoft::random::StdRand();

    int N_bins = 100, N_atts = 1e6;
    std::vector<int> bins(N_bins, 0);

    double b_num;
    for(int i = 0; i < N_atts; i++)
    {
        b_num = int(myRng.generateLognormal() * N_bins);
        if (b_num >= N_bins) {i--; continue;}
        bins[(int)b_num]++;
    }

    std::vector<double> expect(N_bins);
    double overRoot2 = 1 / pow(2, 0.5);
    for(int i=0; i < N_bins; i++)
    {
        double x_min = (double)i / double(N_bins);
        double x_max = double(i + 1) / double(N_bins);

        double cumulativeDiff = erf(log(x_max) * overRoot2) - erf(log(x_min) * overRoot2);
        expect[i] = N_atts * cumulativeDiff;
    }
    double chi2_test = chi2(bins, expect);
    //printResult(bins, expect);

    REQUIRE(chi2_test > 0.7);
    REQUIRE(chi2_test < 1.3);
}

TEST_CASE("StdRand, Sphere_Test", "[std_sphere]")
{
    watersoft::random::StdRand myRng = watersoft::random::StdRand();

    double a, b, c;

    for(int i=0; i < 1e6; i++)
    {
        myRng.generateVector(&a, &b, &c);

        double norm = a * a + b * b + c * c;

        REQUIRE(1 - 1e-6 < norm);
        REQUIRE(1 + 1e-6 > norm);
    }
}
