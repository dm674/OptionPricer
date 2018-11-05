#include"PathGeneration/ParkMiller.h"
#include<iostream>
using namespace std;
#include"Statistics/MCStatistics.h"
#include"Statistics/ConvergenceTable.h"
#include"PathGeneration/AntiThetic.h"
#include"PathDependentAsian.h"
#include"ExoticBSEngine.h"
#include"Statistics/MCTermination.h"
#include"Options&Payoffs/DoubleDigital2.h"

int main() {
    double Expiry;
    double Strike;
    double Spot;
    double Vol;
    double r;
    double d;
    unsigned NumberOfDates;

    cout << "\nEnter expiry\n";
    cin >> Expiry;

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

    // Use inputs to define (constant) parameters
    ParametersConstant VolParam(Vol);
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);

    // Create user-defined payoff object
    PayOff* thePayOff;
    int in_PayOffType;
    cout << "\nChoose between payoffs: (1) Call option, (2) Put option, (3) Double-digital option\n";
    cin >> in_PayOffType;
    cout << "\nStrike\n";
    cin >> Strike;
    switch(in_PayOffType) {
        case 1:
            thePayOff = new PayOffCall(Strike); break;
        case 2:
            thePayOff = new PayOffPut(Strike); break;
        case 3:
            double Strike2;
            cout << "\nUpper strikc\n";
            cin >> Strike2;
            thePayOff = new PayOffDoubleDigital(Strike,Strike2); break;
        default:
            cout << "Wrong payoff type";
            return 1;
    }
    //PayOff* thePayOff = new PayOffCall(Strike);

    // Create array of times for cashflow computation
    // i.e. number of points on each Monte Carlo path
    MJArray times(NumberOfDates);
    for (unsigned long i=0; i < NumberOfDates; i++)
        times[i] = (i+1.0)*Expiry/NumberOfDates;

    // Create option object according to user input
    PathDependent* theOption;
    int in_AsianOptType;
    cout << "\nChoose between Asian Options: (1) Arithmetic, (2) Geometric\n";
    cin >> in_AsianOptType;
    if (in_AsianOptType == 1) {
        theOption = new PathDependentArithmeticAsian(times, Expiry, *thePayOff);
    } else if (in_AsianOptType== 2){
        theOption = new PathDependentGeometricAsian(times, Expiry, *thePayOff);
    } else {
        cout << "Wrong option type";
        return 1;
    }

    // Create user-defined set of statistics to gather throughout MC simulation
    vector<StatisticsMC*> stat_tmp;
    int in_StatType;
    do {
        cout << "\nSimple statistics: (1) Mean, (2) Variance, (3) Moments, (4) VaR, or (0) done\n";
        cout << "Convergence table: (11) Mean, (12) Variance, (13) Moments, (14) VaR or (0) done\n";
        cin >> in_StatType;
        switch (in_StatType) {
            case 1:
                stat_tmp.push_back(new StatisticsMean); break;
            case 2:
                stat_tmp.push_back(new StatisticsVariance); break;
            case 3:
                stat_tmp.push_back(new StatisticsMoments); break;
            case 4:
                stat_tmp.push_back(new StatisticsVaR); break;
            case 11:
                stat_tmp.push_back(new ConvergenceTable(*(new StatisticsMean))); break;
            case 12:
                stat_tmp.push_back(new ConvergenceTable(*(new StatisticsVariance))); break;
            case 13:
                stat_tmp.push_back(new ConvergenceTable(*(new StatisticsMoments))); break;
            case 14:
                stat_tmp.push_back(new ConvergenceTable(*(new StatisticsVaR))); break;
        }
    } while(in_StatType != 0 || stat_tmp.empty());
    //StatisticsMean gathererInit;
    //ConvergenceTable gatherer(gathererInit);
    StatisticsMulti gatherer(stat_tmp);

    // Create anti-thetic linear congruential generator (using Park-Miller method)
    RandomParkMiller generator(NumberOfDates);
    AntiThetic GenTwo(generator);

    // Create user-defined set of termination conditions
    vector<TerminationMC*> term_tmp;
    int in_TermType;
    do {
        cout << "\nTermination: (1) Paths, (2) Time, (3) Variance, (4) Convergence, or (0) done\n";
        cin >> in_TermType;
        switch (in_TermType) {
            case 1:
                unsigned long NumberOfPaths;
                cout << "Number of Monte Carlo paths\n";
                cin >> NumberOfPaths;
                term_tmp.push_back(new TerminationPaths(NumberOfPaths)); break;
            case 2:
                double maxtime;
                cout << "Maximum time (in seconds)\n";
                cin >> maxtime;
                term_tmp.push_back(new TerminationTime(maxtime)); break;
            case 3:
                double maxvariance;
                cout << "Maximum variance accepted\n";
                cin >> maxtime;
                term_tmp.push_back(new TerminationVariance(maxvariance)); break;
            case 4:
                double epsilon;
                cout << "Absolute threshold\n";
                cin >> epsilon;
                term_tmp.push_back(new TerminationConv(epsilon)); break;
        }
    } while(in_TermType != 0 || term_tmp.empty());
    TerminationMC* termination;
    if (term_tmp.size() > 1){
        int in_TermMultiType;
        do {
            cout << "\nStop when (1) all, (2) any, of these conditions are satisfied \n";
            cin >> in_TermMultiType;
            switch (in_TermMultiType) {
                case 1:
                    termination = new TerminationMultiOR(term_tmp); break;
                case 2:
                    termination = new TerminationMultiAND(term_tmp); break;
            }
        } while(in_TermMultiType != 1 || in_TermMultiType !=2);
    } else {
        termination = new TerminationMultiOR(term_tmp);
    }
//    termination = new TerminationMultiOR(term_tmp);

    // Create Black-Scholes engine for exotic option
    ExoticBSEngine theEngine(*theOption, rParam, dParam,
                             VolParam, GenTwo, Spot);
    theEngine.DoSimulation(gatherer, *termination);

    // Obtain and output results from convergence table
    vector<vector<double> > results =
            gatherer.GetResultsSoFar();
    gatherer.PrintResults(); // Prints the same results as GetResultsSoFar()

//    double tmp;
//    cin >> tmp;

    return 0;
}