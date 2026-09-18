-module(factorial).
-export([fact/1]).

%Funcion factorial por pattern matching

fact(0) -> 1;
fact(N) -> N*fact(N-1).

