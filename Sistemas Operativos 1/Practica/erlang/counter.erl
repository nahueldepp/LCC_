-module (counter).
-export([init/0, bucle/1, incrementar/1, valor/1]).


init() -> spawn(counter, bucle, [0]).

incrementar(Contador) -> Contador ! inc,
                    ok.

valor(Contador) -> Contador ! val,
                    ok. 

bucle(N) -> 
    receive 
        inc -> bucle(N+1);
        val -> io:fwrite("Valor actual: ~p ~n",[N]),
            bucle(N)
    end.