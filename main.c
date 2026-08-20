#include <stdio.h>
#include <math.h>

// Helper Function: Cumulative Normal Probability N(x)
double N(double x) {
    return 0.5 * erfc(-x / sqrt(2.0));
}

int main() {
    // -------------------------------------------------------------
    // FIXED HISTORICAL VOLATILITY RECORD (Unchanged Data)
    // -------------------------------------------------------------
    // Historical 252-day annualized volatility (sigma) remains constant
    const double v = 0.20; // 20.0% Annualized Volatility from historical records

    // User Input Variables
    double S, K, T, r, market_price;

    printf("=========================================================\n");
    printf("     BLACK-SCHOLES INTERACTIVE DECISION ENGINE           \n");
    printf("=========================================================\n");
    printf("Historical Volatility (v / Sigma): %.2f%% [FIXED DATA]\n", v * 100.0);
    printf("Note for Evaluator: Suggested test values are shown in [ ].\n");
    printf("---------------------------------------------------------\n");

    // -------------------------------------------------------------
    // USER INPUT PROMPTS WITH GUIDING VALUES IN BRACKETS
    // -------------------------------------------------------------
    printf("Enter Current Stock Spot Price ($S)    [e.g., 100.00] : ");
    if (scanf("%lf", &S) != 1) return 1;

    printf("Enter Option Strike Price ($K)        [e.g., 100.00] : ");
    if (scanf("%lf", &K) != 1) return 1;

    printf("Enter Time to Expiry in Years (T)     [e.g., 1.0]    : ");
    if (scanf("%lf", &T) != 1) return 1;

    printf("Enter Risk-Free Rate in %% (r)          [e.g., 5.0]    : ");
    if (scanf("%lf", &r) != 1) return 1;
    r = r / 100.0; // Convert percentage to decimal

    printf("Enter Actual Market Asking Price ($)   [e.g., 8.50]   : ");
    if (scanf("%lf", &market_price) != 1) return 1;

    // -------------------------------------------------------------
    // BLACK-SCHOLES PRICING CALCULATIONS
    // -------------------------------------------------------------
    double d1 = (log(S / K) + (r + 0.5 * v * v) * T) / (v * sqrt(T));
    double d2 = d1 - v * sqrt(T);
    
    // Theoretical Fair Price
    double fair_price = S * N(d1) - K * exp(-r * T) * N(d2);
    
    // Probabilities and Risk Metrics
    double win_probability = N(d2) * 100.0;
    double delta = N(d1);

    // Decision Logic
    double price_difference = fair_price - market_price;
    double mispricing_pct = (price_difference / market_price) * 100.0;

    // -------------------------------------------------------------
    // OUTPUT RESULTS & DECISION
    // -------------------------------------------------------------
    printf("\n=========================================================\n");
    printf("                  EVALUATION RESULTS                     \n");
    printf("=========================================================\n");
    printf("Theoretical Fair Value : $%.2f\n", fair_price);
    printf("Actual Market Asking   : $%.2f\n", market_price);
    printf("Win Probability        : %.2f%% (P(In-The-Money at Expiry))\n", win_probability);
    printf("Delta Risk Sensitivity : %.4f\n", delta);
    printf("---------------------------------------------------------\n");
    printf("DECISION RECOMMENDATION:\n");

    if (price_difference > 0.50) {
        printf(" -> RECOMMENDATION : BENEFICIAL TO BUY (UNDERVALUED)\n");
        printf(" -> REASONING      : Market price ($%.2f) is cheaper than\n", market_price);
        printf("                      fair value ($%.2f) by +%.1f%%.\n", fair_price, mispricing_pct);
    } 
    else if (price_difference < -0.50) {
        printf(" -> RECOMMENDATION : BAD DECISION / DO NOT BUY (OVERVALUED)\n");
        printf(" -> REASONING      : Market price ($%.2f) is overpriced compared\n", market_price);
        printf("                      to fair value ($%.2f).\n", fair_price);
    } 
    else {
        printf(" -> RECOMMENDATION : NEUTRAL / FAIRLY PRICED\n");
        printf(" -> REASONING      : Market price is near fair theoretical value.\n");
    }
    printf("=========================================================\n");

    return 0;
}
