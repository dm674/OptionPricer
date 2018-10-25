#include"PathGeneration/ParkMiller.h"
#include<iostream>
using namespace std;
#include"Statistics/MCStatistics.h"
#include"Statistics/ConvergenceTable.h"
#include"PathGeneration/AntiThetic.h"
#include"PathDependentAsian.h"
#include"ExoticBSEngine.h"

int main() {
    double Expiry;
    double Strike;
    double Spot;
    double Vol;
    double r;
    double d;
    unsigned long NumberOfPaths;
    unsigned NumberOfDates;

    cout << "\nEnter expiry\n";
    cin >> Expiry;

    cout << "\nStrike\n";
    cin >> Strike;

    cout << "\nEnter spot\n";
    cin >> Spot;

    cout << "\nEnter vol\n";
    cin >> Vol;

    cout << "\nEnter riskless interest rate r\n";
    cin >> r;

    cout << "\nEnter drift d\n";
    cin >> d;

    cout << "\nNumber of dates\n";
    cin >> NumberOfDates;

    cout << "\nNumber of Monte Carlo paths\n";
    cin >> NumberOfPaths;

    // Create payoff object for generic call option
    PayOffCall thePayOff(Strike);

    // Create array of times for cashflow computation
    // i.e. number of points on each Monte Carlo path
    MJArray times(NumberOfDates);
    for (unsigned long i=0; i < NumberOfDates; i++)
        times[i] = (i+1.0)*Expiry/NumberOfDates;

    // Use inputs to define (constant) parameters
    ParametersConstant VolParam(Vol);
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);

    // Create option object according to user input
    PathDependent* theOption;
    int AsianOptType;
    cout << "\nChoose between Asian Options: (1) Arithmetic, (2) Geometric\n";
    cin >> AsianOptType;
    if (AsianOptType == 1) {
        theOption = new PathDependentArithmeticAsian(times, Expiry, thePayOff);
    } else if (AsianOptType== 2){
        theOption = new PathDependentGeometricAsian(times, Expiry, thePayOff);
    } else {
        cout << "Wrong option type";
        return 1;
    }

    // Create convergence table for mean over M.C. simulations
    StatisticsMean gatherer;
    ConvergenceTable gathererTwo(gatherer);

    // Create anti-thetic linear congruential generator (using Park-Miller method)
    RandomParkMiller generator(NumberOfDates);
    AntiThetic GenTwo(generator);

    // Create Black-Scholes engine for exotic option
    ExoticBSEngine theEngine(*theOption, rParam, dParam,
                             VolParam, GenTwo, Spot);
    theEngine.DoSimulation(gathererTwo, NumberOfPaths);

    // Obtain and output results from convergence table
    vector<vector<double> > results =
            gathererTwo.GetResultsSoFar();
    cout <<"\nFor the Asian call price the results are \n";
    {
        for (unsigned long i=0; i < results.size(); i++)
        {
            for (unsigned long j=0; j < results[i].size(); j++)
                cout << results[i][j] << " ";
            cout << "\n";
        }
    }

//    double tmp;
//    cin >> tmp;

    return 0;
}