### Codechef October Solution

----

#### Chef and Ground (**CHEFGR**)

Cakewalk. One trick: the final height may be higher than the highest.

#### DevuLand, Dinosaurs and Laddus (**PRLADDU**)

Greedy. Swipe the dinosaurs from the left to right, find the leftest people to match.

#### Remy paints the fence (**FATCHEF**)

Simple Combinatorics. For any gap of adjacent different bucket, if the length is `len`, there are `len+1` ways to add a divide line. So the result is mutiply all the number of ways.

#### Magical Girl and Colored Liquid Potions (**PRPOTION**)

Greedy. Only the maximum number in a colored set matters. And one greedy though is just applying magic trick on the maximum number.

Though I didn't prove the correctness of greedy, it did Accepted.

#### Chef and Square (**CHEFSQUA**)

Simple Geometry. Enumerate the bottom point of the square, calculate all vectors of differenece, for a possible edge `(x, y)`, check if `(-y, x)` and `(x - y, x + y)` exists. The complexity is `O(N^2log(N)`.

#### Sereja and two strings (**SEATSR**)

Dynamic Programming. As `K <= 100`, so the maximal difference between match index of the two strings is `[-k, k]`, so use `dp[the_index_in_first_string][diff_between_them]` to do a LCS DP. And it's `O(Len * K)`.

Before noticing the fact `K <= 100`, I wasted a lot of time wondering whether there is an `O(NlogN)` algorithm for LCS puzzles. The Google shows some result (for example, [An Efficient Algorithm for the LCS Problem](http://www.cs.ucf.edu/courses/cap5510/fall2009/SeqAlign/LCS.efficient.pdf)) to transform LCS to LIS, which has an `O(NlogN)` solution. But actually, it is useless as the length of transformed array could be `O(len^2)`.

#### Stringology is Magic (**QSTRING**)

Data Structure. This problem is almost the same with [HDU 5008 Boring String Problem](http://acm.hdu.edu.cn/showproblem.php?pid=5008).

The basic idea is using suffix array to calculate the `sa` and `height` array, then a ith-ranked prefix will generate `len - sa[i] - height[i]` distinct substrings. So for the `"Select"` queries with a given K (first rank), we can easily find the minimal-ranked prefix position `Pos_begin` and the length of the substring `len_substring`, but we need the k2-indexed prefix position.

To solve that, using binary search to find the interval [l, r] which show a common prefix with at least a length of `len_substring`, then get the k-th number in the interval. Persist Segment Tree can solve this.

For the `"Rank"` queries, also using binary search  to find the interval [l, r] which show a common prefix with at least a length of `len_substring`, but there is a small difference between the two search, the previous one only need search the bigger number, but this one requies both direction. Then we can still use the presist tree to find the rank of the given `Pos_begin` in this interval.

#### Chef and Painting (**CHEFPNT**)

Challenge. I simply use greedy algorithm, find the maximum empty gap and paint them, random choice in there seems useless.

And it's a good alternative choice to only use Row operation or Column operation. But forget it, my solution is just *naive*.