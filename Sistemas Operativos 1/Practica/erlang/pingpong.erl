-module(pingpong).
-export([ping/0, pong/0, play/0]).


pong() -> 
    receive 
        {0, Pidping} -> io:fwrite("Pong recv: ~p ~n", [Pidping]),
            Pidping ! {fin,self()},
            okPong;
        {N, Pidping} -> io:fwrite("Pong recv de ~p: ~p ~n",[Pidping, N]),
            Pidping ! {N-1, self()},
            pong()
    end.

ping() -> 
    receive
        {fin,Pidpong} -> io:fwrite("Se termino el juego ~p ~n",[Pidpong]),
            okPing;
        {N,Pidpong} -> io:fwrite("Ping recv de ~p:  ~p ~n", [Pidpong, N]),
            Pidpong ! {N-1,self()}, 
            ping()
    end.


play()->    
    Pidping = spawn(pingpong, ping, []),
    Pidpong = spawn(pingpong, pong, []),
    Pidpong ! {10, Pidping},
    playok.

