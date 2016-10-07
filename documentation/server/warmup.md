#Warm-up
Server accepts connections and tells clients that it's the warmup phase. During that phase if it receives a register
query, it checks if it's valid and proceeds to register players (add player to the world with data received from the client,
then set up the territory, action points etc. for that player). When the time runs out, the server enters the [game state](game.md)
and doesn't accept new players anymore.
