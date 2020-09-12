# string-matching-rabin-karp

String matching algorithm that performs well in practice

Worst case running time O((n - m + 1)m)

Main idea from number theory: two numbers are equivalent modula a third number.

Treat Pattern as a set of digits, mapping each character to a number. P has size m. To make sure th hash of P fits an integer variable, take its module q.

Treat Text similarly as a set of digits, where T has size n. n >= m

Calculate the value of P modulo q. Go through T with a sliding window, calculating the size of T of length m modulo q. If the two numbers modulo q match, check to see if the string matches.