cmake_minimum_required(VERSION 3.12)
project(OptionPricer)

set(CMAKE_CXX_STANDARD 14)

add_executable(OptionPricer
        Arrays.h Arrays.cpp
        Options&Payoffs/PathDependent.h Options&Payoffs/PathDependent.cpp
        Wrapper.h
        Statistics/MCStatistics.h Statistics/MCStatistics.cpp
        Statistics/MCTermination.h Statistics/MCTermination.cpp
        Options&Payoffs/Parameters.h Options&Payoffs/Parameters.cpp
        Options&Payoffs/Vanilla3.h Options&Payoffs/Vanilla3.cpp
        Options&Payoffs/Digital.h Options&Payoffs/Digital.cpp
        Options&Payoffs/PayOffDiff.h Options&Payoffs/PayOffDiff.cpp
        Statistics/ConvergenceTable.h Statistics/ConvergenceTable.cpp
        PathGeneration/Random2.h PathGeneration/Random2.cpp
        PathGeneration/Normals.h PathGeneration/Normals.cpp
        ExoticEngine.h ExoticEngine.cpp
        ExoticBSEngine.h ExoticBSEngine.cpp
        Options&Payoffs/PayOffBridge.h Options&Payoffs/PayOffBridge.cpp
        Options&Payoffs/PayOff3.h Options&Payoffs/PayOff3.cpp
        Options&Payoffs/PathDependentAsian.h Options&Payoffs/PathDependentAsian.cpp
        PathGeneration/ParkMiller.h PathGeneration/ParkMiller.cpp
        PathGeneration/AntiThetic.h PathGeneration/AntiThetic.cpp
        Options&Payoffs/European.h Options&Payoffs/European.cpp
        Options&Payoffs/Lookback.h Options&Payoffs/Lookback.cpp
        BlackScholesFormulas.h BlackScholesFormulas.cpp
        EquityFXMain.cpp)