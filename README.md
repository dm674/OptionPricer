# Monte-Carlo Option Pricer


The basic infrastructure is based on Chapters 1-7 of [C++ Design Patterns and Derivatives Pricing](http://www.markjoshi.com/design/) by Mark S. Joshi.
For simplicity, notation conventions are kept wherever possible.

Object classes can be categorized by their actions
* Generating a stock price path (PathGeneration folder)
* Producing the cash-flows of the chosen option with the given payoff (Options&Payoffs folder)
* Accounting for the cash-flows and calling successive paths (main folder)
* Gathering the chosen statistics over all paths up to the chosen termination point (Statistics folder)

We can summarize the key steps of the main algorithm:
* The user defines all main parameters: expiry date, current spot price, option and payoff types, chosen statistics and termination conditions, etc.;
* A random path generator takes in an array of times, and uses its size to set its internal dimensionality;
* The engine computes all possible discount factors for the times at which the product (i.e. the option and its payoff) may provide a cash-flow;
* The engine creates a mutable vector to receive the produced cash-flows;
* For each path, the path generator passes an array of spot values for the engine;
* The product copies the cash-flow values for these spot values into the mutable vector;
* The engine sums the discounted cash-flows, and sends the total value to the statistics gatherer and terminator;
* The termination conditions are checked;
* Once the total termination condition is reached, the statistics gatherer obtains and prints the results.


For arithmetic Asian options, results can be compared to [The Value of an Asian Option](https://doi.org/10.2307/3215221) by L.C.G. Rogers & Z. Shi.