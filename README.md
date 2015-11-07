# RouletteWinner
Calculates a winning strategy for given roulette odds. Does better with more iterations and more unlikely odds.

Strategy:

Given odds (ex: 2:1), determines a winning strategy. To get the idea behind this strategy consider the scenario
where we're playing with 2:1 odds. 

    Bet the minimum bet
    If we win
        Continue betting the minumum
    If we lose
        Double the existing bet

The logic behind this is that if we win with our doubled bet, we make back what we've lost (plus the minimum bet).
This strategy extends to any given odds.

Example:

    Starting - 500
    Odds - 2:1

    Bet: 5
        Lose 5
    Bet: 10
        Lose 10
    Bet: 20
        Win 40

    Running total: +5