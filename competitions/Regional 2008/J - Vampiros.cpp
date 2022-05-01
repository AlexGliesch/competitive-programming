/* 
 * I'm thinking of the recursive formula:
 * 
 * p(H1, H2) = (AT / 6) * p(H1+D, H2-D) + ((6-AT/6) * p(H1-D, H2+D)
 * p(0, H2) = 0
 * p(H1, 0) = 1
 * 
 * that is, the probability of 1 winning with healths H1 and H2 is the prob.
 * of the dice running in his favour and him sucking 2's health, or the prob.
 * of the dice running in 2's favour and 2 sucking 1's health.
 * 
 * However, this recursive formula is too complicated and I couldn't find 
 * a solution for it.
 * */