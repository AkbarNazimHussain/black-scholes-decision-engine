# Black-Scholes Interactive Decision Engine (`black-scholes-decision-engine`)

An interactive, high-performance quantitative decision engine written in C that evaluates option contract valuations using the **Black-Scholes-Merton model**. 

By comparing calculated theoretical fair values against live market asking prices, the system automatically detects market mispricings and generates actionable trade recommendations (**BENEFICIAL TO BUY** vs. **BAD DECISION / OVERVALUED**), along with probability metrics and risk sensitivities ($\Delta$).

---

## Key Features

* **Interactive Valuation Interface:** Accepts real-time market spot prices ($S$), strike prices ($K$), expiry time horizons ($T$), interest rates ($r$), and exchange asking prices via interactive CLI prompts with guided evaluator benchmarks.
* **Immutable Historical Volatility Parameter:** Enforces a protected, immutable 252-day historical annualized volatility variable (`const double v = 0.20`), preserving historical risk baselines.
* **Integrated Statistical Computation:** Computes standard cumulative normal probabilities $N(x)$ directly via C's native math library (`erfc()`), eliminating bulk lookup tables or low-accuracy polynomial approximations.
* **Risk & Probability Metrics:** Calculates both **Win Probability** ($N(d_2)$, the likelihood of expiring In-The-Money) and **Delta Risk Sensitivity** ($\Delta = N(d_1)$, hedging ratio).
* **Automated Decision Framework:** Employs margin-of-safety decision rules to flag undervalued arbitrage opportunities and prevent purchasing overpriced contracts.

---

## Mathematical Formulation

The engine solves the standard continuous-time Black-Scholes pricing equation for a European Call Option:

$$C(S, t) = S \cdot N(d_1) - K e^{-rT} \cdot N(d_2)$$

Where the standard probabilistic distance parameters $d_1$ and $d_2$ are given by:

$$d_1 = \frac{\ln\left(\frac{S}{K}\right) + \left(r + \frac{\sigma^2}{2}\right)T}{\sigma \sqrt{T}}$$

$$d_2 = d_1 - \sigma \sqrt{T}$$

### Financial Parameter Mapping

| Symbol | C Variable | Financial Parameter | Description / Standard Source |
| :---: | :---: | :--- | :--- |
| $S$ | `S` | Spot Price | Current stock market execution price |
| $K$ | `K` | Strike Price | Fixed contractual exercise price |
| $T$ | `T` | Time to Expiry | Time remaining until expiration (in annual fractions) |
| $r$ | `r` | Risk-Free Rate | Central bank / Treasury yield benchmark |
| $\sigma$ | `v` | Volatility | Fixed historical 252-day annualized return standard deviation |
| $N(d_1)$ | `delta` | Option Delta ($\Delta$) | Price sensitivity of the option relative to a $1 movement in $S$ |
| $N(d_2)$ | `win_probability` | Win Probability | Statistical probability that $S_T > K$ at expiration date |

---

## Compilation & Usage

### 1. Prerequisites
Ensure a standard C compiler (`gcc` or `clang`) with C99 support and math library linking options is installed.

### 2. Compilation
Compile `main.c` using standard flags:

```bash
gcc main.c -o decision_engine -lm
