-module(ej_2).
-export([wait/1,cronometro/3,crono_loop/3]).
%a)
wait(MS)->
    receive
        after MS -> ok
    end.
     % Al poner el receive completamente vacío (sin ningún patrón para hacer match antes del after), es imposible que el proceso agarre algún mensaje. 
     %Entonces, se queda bloqueado esperando, el tiempo se agota indefectiblemente, y termina ejecutando el ok.

%b)

crono_loop(Fun, Hasta, Periodo) ->

    if 
        (Hasta < Periodo) ->
            ok;
        true-> 
            wait(Periodo),
            Fun(),
            crono_loop(Fun,Hasta-Periodo,Periodo)
    end.

cronometro(Fun,Hasta,Periodo) ->
    spawn(ej_2,crono_loop,[Fun,Hasta,Periodo]).
