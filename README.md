
# Basic Tool for QIF


Using your favorite programming language (Python, C, C++), implement a tool that has the following functions:

## Basic functions
1) Given a vector of numbers, verify whether it constitutes a valid probability distribution.
2) Given a matrix of number, verify whether it constitutes a valid channel matrix.
3) Print beautifully a prior on the screen.
4) Print beautifully a channel matrix on the screen.
## Update of knowledge using priors and channels
1) Given a prior and a channel matrix, compute the corresponding joint probability distribution.
2) Given a prior and a channel matrix, compute the corresponding hyper-distribution (i.e., the set of posterior distributions and the outer distribution on them). 
## Prior measures of information
1) Given a prior distribution, compute its Shannon entropy.
2) Given a prior distribution, compute its Guessing entropy.
3) Given a prior distribution, compute its Bayes vulnerability.
4) Given a prior distribution and a value n>=1, compute the probability of guessing correctly within n tries. (Note that when n = 1 this function coincides with Bayes vulnerability).
5) Given a prior distribution and a gain function, compute the g-vulnerability. 
(Note that when the g-function is gid, you recover Bayes vulnerability). 
## Posterior measures of information
1) create functions that, given a prior and a channel matrix, compute the corresponding posterior information measures as in the items (a)-(e) of item (3) above.

### Leakage measures
1) Given a prior, a channel matrix, and a information function, compute the corresponding additive leakage.
2) Given a prior, a channel matrix, and a information function, compute the corresponding multiplicative leakage.
