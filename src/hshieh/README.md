# "Efficient Computation of the Kauffman Bracket"

This code uses the algorithm from "Efficient Computation of the Kauffman Bracket" by Ellenberg et al., found at https://arxiv.org/abs/1303.7179. The algorithm takes a cutting of
the knot, where each crossing is introduced one by one. After each crossing is added, the expression for the Kauffman bracket polynomial is simplified to a linear combination of
laurent polynomials in a single variable times a basis tangle (with no crossings). The worst-case run time for the algorithm is O(n2^{C * sqrt(n)}), where C = 6 * sqrt(2) + 
5 * sqrt(3).
