/* 
 * my idea was to put all X's and Y's of all lines in two sets, having the
 * X's and Y's of horizontal and vertical lines. 
 * 
 * then, given the fact that there are at most 100 lines, we can iterate over
 * every pair of X and Y lines, and check if the point (X, Y) is outside the
 * polygon (polygon containment test for that): if it is, then we can remove
 * lines X and Y using only one judge. 
 * 
 * in the end, add one judge for every non-paired X and Y line. 
 * 
 * it works for the sample tests, but i'm getting WA, although the algorithm 
 * makes a lot of sense to me.
 * 
 * */
