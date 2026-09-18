-module(ej_1).
-export([nombre/1,apellido/1]).
-export([init/0,string_test/0,match_test/0,tuple_test/2,filtrar_por_apellido/2]).

match_test () ->
    {A,B} = {5,4},%Es valido, si asigna A= 5 y B = 4
    %{C,C} = {5,4}, No es valido, se asigna C=5, pero despues se quiere reasignar C=4, cuando C ya es igual a 5
    {B,A} = {4,5}.%es valido, se mantiene la asignación
    %{D,D} = {5,5}. no es valido por las mismas razones que {C,C}


string_test() -> [
    helloworld == 'helloworld', %verdadero, ambos son atomos
    "helloworld" < 'helloworld',%falso atomo<lista
    helloworld == "helloworld",%falso atomo<lista
    % c)
    % number < atom < reference < fun < port < pid < tuple < map < list < bitstring
    [$h,$e,$l,$l,$o,$w,$o,$r,$l,$d] == "helloworld",% verdadero, ambos son listas de caracteres y ademas son las mismas
    [104,101,108,108,111,119,111,114,108,100] < {104,101,108,108,111,119,111,114,108,100},%falso, tupla < listas
    [104,101,108,108,111,119,111,114,108,100] > 1,% verdadero listas>number
    [104,101,108,108,111,119,111,114,108,100] == "helloworld"]. %verdadero, ambas son listasd de caracteres


    
apellido ({persona,_,{apellido, Apellido}}) ->
    Apellido.
nombre ({persona,{nombre, Nombre},_}) ->
    Nombre.

tuple_test (P1, P2) ->
    io:fwrite("El nombre de P1 es ~p y el apellido de P2 es ~p~n", [nombre(P1), apellido(P2)]).

filtrar_por_apellido([], _) -> 
    [];
filtrar_por_apellido([P | Ps], Apellido)->
    case apellido(P) == Apellido of
        true -> 
            [nombre(P) | filtrar_por_apellido(Ps,Apellido)];
        false->
            filtrar_por_apellido(Ps,Apellido)
    end.



init () ->
    P1 = {persona, {nombre, "Juan"}, {apellido, "Gomez"}},
    P2 = {persona, {nombre, "Carlos"}, {apellido, "Garcia"}},
    P3 = {persona, {nombre, "Javier"}, {apellido, "Garcia"}},
    P4 = {persona, {nombre, "Rolando"}, {apellido, "Garcia"}},
    match_test(),
    tuple_test(P1, P2),
    Test= string_test(),
    io:write("test= ~p ~n",Test),
    Garcias = filtrar_por_apellido([P4, P3, P2, P1], "Garcia"),
    io:fwrite("Garcias: ~p ~n",[Garcias]).