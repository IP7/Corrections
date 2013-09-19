fact(0, 1).
fact(N, R) :- N > 0, M is N-1, fact(M, T), R is N*T.
