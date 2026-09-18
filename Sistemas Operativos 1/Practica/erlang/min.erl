-module(min).
-export([min/1]).

min([X]) -> X;
min([X|Xs]) -> 
    Rest = min(Xs),
    if 
        X<Rest ->
            X;
        true -> 
            Rest
    end.