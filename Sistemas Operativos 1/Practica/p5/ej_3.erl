bal(Servs) ->
    receive
        {req, Arg, Pid} ->
            Proc = lists:nth(rand:uniform(length(Servs)), Servs),
            Proc ! { req, Arg, self() },
                receive
                    Reply -> Pid ! Reply
                end
    end,
    bal(Servs).

