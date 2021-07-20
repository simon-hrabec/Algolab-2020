# Dominoes - solution
Dominos is quite simple problem that requires iteration over the input and a few conditions.
- Failing case
- Iterative solution

## Failing case
We are told how many domino pieces will fall if we push the first one. First question to ask is why should not fall all of them and what would be the case. The only way to prevent a domino piece from falling is it is preceded by domino piece of height 1. Actually this is not a sufficient condition. If the domino pieces 2 places behind would be of height 3 it would topple it anyway (as an example). So we need to take into consideration all preceeding pieces.

## Iterative solution
The observation above delineates the expected solution. As we go we remember the furthers place that the current or any preceding piece will hit. Once we go over a domino piece that is out of reach we have found the answer. Note that even though we know the answer already, we still need to read the rest of the input due to the following cases.

# Running time
    Test set 1 (30 pts / 5 s) - 0.013s
    Test set 2 (30 pts / 5 s) - 0.93s
    Test set 3 (40 pts / 5 s) - 0.895s
