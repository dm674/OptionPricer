#include"PathGeneration/ParkMiller.h"
#include<iostream>
#include"Statistics/MCStatistics.h"
#include"Statistics/ConvergenceTable.h"
#include"PathGeneration/AntiThetic.h"
#include"Options&Payoffs/PathDependentAsian.h"
#include"Options&Payoffs/European.h"
#include"Options&Payoffs/Lookback.h"
#include"ExoticBSEngine.h"
#include"Statistics/MCTermination.h"
#include"Options&Payoffs/PayOffDiff.h"
#include"BlackScholesFormulas.h"

using namespace std;

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

    // Use inputs to define (constant) parameters
    ParametersConstant VolParam(Vol);
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);


    // Create user-defined payoff object
    PayOff* thePayOff;
    int in_PayOffType;
    cout << "\nChoose between payoffs: (1) Call option, (2) Put option, "
            "(3) Digital call option, (4) Digital put option, "
            "(5) Double-digital option \n";
    cin >> in_PayOffType;
    cout << "\nStrike\n";
    cin >> Strike;
    switch(in_PayOffType) {
        case 1:
            thePayOff = new PayOffCall(Strike); break;
        case 2:
            thePayOff = new PayOffPut(Strike); break;
        case 3:
            thePayOff = new PayOffDigitalCall(Strike); break;
        case 4:
            thePayOff = new PayOffDigitalPut(Strike); break;
        case 5:
            double Strike2;
            cout << "\nUpper strike\n";
            cin >> Strike2;
            thePayOff = new PayOffDoubleDigital(Strike,Strike2); break;
        default:
            cout << "Wrong payoff type";
            return 1;
    }
    //PayOff* thePayOff = new PayOffCall(Strike);



    // Create option object according to user input
    PathDependent* theOption;
    int in_OptType;
    cout << "\nChoose between Options: (1) European, (2) Arithmetic Asian, (3) Geometric Asian, (4) Lookback\n";
    cin >> in_OptType;
    if (in_OptType == 1) {
        NumberOfDates = 1;
        MJArray times(NumberOfDates);
        times[0] = Expiry;
        theOption = new European(times, Expiry, *thePayOff);
    } else if ((in_OptType == 2) || (in_OptType == 3) || (in_OptType == 4)) {
        // Create array of times for cashflow computation, i.e. number of points on each Monte Carlo path
        cout << "\nNumber of dates\n";
        cin >> NumberOfDates;
        MJArray times(NumberOfDates);
        for (unsigned long i=0; i < NumberOfDates; i++)
            times[i] = (i+1.0)*Expiry/NumberOfDates;
        if (in_OptType == 2)
            theOption = new PathDependentArithmeticAsian(times, Expiry, *thePayOff);
        if (in_OptType == 3)
            theOption = new PathDependentGeometricAsian(times, Expiry, *thePayOff);
        if (in_OptType == 4)
            theOption = new Lookback(times, Expiry, *thePayOff);
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
                stat_tmp.push_back(new ConvergenceTable(StatisticsMean())); break;
            case 12:
                stat_tmp.push_back(new ConvergenceTable(StatisticsVariance())); break;
            case 13:
                stat_tmp.push_back(new ConvergenceTable(StatisticsMoments())); break;
            case 14:
                stat_tmp.push_back(new ConvergenceTable(StatisticsVaR())); break;
            case 0:
                break;
            default:
                cout << "Wrong statistics type; try again!";
        }
    } while(in_StatType != 0 || stat_tmp.empty());
    //StatisticsMean gathererInit;
    //ConvergenceTable gatherer(gathererInit);
    StatisticsMulti gatherer(stat_tmp);


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
                cin >> maxvariance;
                // Need MultiAND termination with minimum path number to avoid 0 variance at first few paths
                term_tmp.push_back(new TerminationMultiAND({ new TerminationVariance(maxvariance),
                                                             new TerminationPaths(50) }));
                break;
            case 4:
                double epsilon;
                cout << "Absolute threshold\n";
                cin >> epsilon;
                term_tmp.push_back(new TerminationConv(epsilon)); break;
            case 0:
                break;
            default:
                cout << "Wrong termination type; try again!";
        }
    } while(in_TermType != 0 || term_tmp.empty());
    TerminationMC* termination;
    if (term_tmp.size() > 1){
        int in_TermMultiType = 0;
        do {
            cout << "\nStop when (1) any, (2) all, of these conditions are satisfied \n";
            cin >> in_TermMultiType;
            switch (in_TermMultiType) {
                case 1:
                    termination = new TerminationMultiOR(term_tmp); break;
                case 2:
                    termination = new TerminationMultiAND(term_tmp); break;
                default:
                    cout << "Wrong termination multi-type; try again!";
            }
        } while(in_TermMultiType != 1 && in_TermMultiType !=2);
    } else {
        termination = new TerminationMultiOR(term_tmp);
    }
    //TerminationMC* termination = new TerminationVariance(100000.0);


    // Create anti-thetic linear congruential generator (using Park-Miller method)
    RandomParkMiller generator(NumberOfDates);
    AntiThetic GenTwo(generator);

    // Create Black-Scholes engine for exotic option
    ExoticBSEngine theEngine(*theOption, rParam, dParam,
                             VolParam, GenTwo, Spot);
    theEngine.DoSimulation(gatherer, *termination);

    // Obtain and output results from convergence table
    vector<vector<double> > results = gatherer.GetResultsSoFar();
    gatherer.PrintResults(); // Prints the same results as GetResultsSoFar()

    // Print exact Black-Scholes result where possible
    if (in_OptType == 1){
        switch (in_PayOffType) {
            case 1:
                cout << "Black-Scholes price for European call is : " << BlackScholesCall(Spot,Strike,r,d,Vol,Expiry);
                break;
            case 2:
                cout << "Black-Scholes price for European put is : " << BlackScholesPut(Spot,Strike,r,d,Vol,Expiry);
                break;
            case 3:
                cout << "Black-Scholes price for digital call is : " << BlackScholesDigitalCall(Spot,Strike,r,d,Vol,Expiry);
                break;
            case 4:
                cout << "Black-Scholes price for digital put is : " << BlackScholesDigitalPut(Spot,Strike,r,d,Vol,Expiry);
                break;
        }
    }

    //    double tmp;
    //    cin >> tmp;

    return 0;
}