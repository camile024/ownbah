#Intro
When a server starts, it gets all data from two files:  
-server.cfg  
-server_rules.cfg  
Client will be responsible for changing these files regarding user preferences  
In the early stages feel free to hardcode all the settings into variables and work on them.
#Set-up
Server loads settings like turn-time and whatever we come up with later on.  
Server should then set up the game world with pre-defined regions (we'll get to the amount of them and how they're distinguished).
We'll probably make a 'Region' class and create many instances of it, assigning X and Y to each one of them (coords will be
hardcoded/stored in a file. People responsible for the map have to generate them when they set up the map).  
After creating the world (setting up the regions), the server runs the game-loop function for the first time, that turns
on the [warm-up phase](warmup.md)
