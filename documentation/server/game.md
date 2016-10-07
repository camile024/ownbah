#Game state
##Network
The server proceeds to respond to various client requests regarding synchronisation, actions, joining, detecting clients that 
timed out (simple pinging from time to time?)
##Engine
Keep track of the time, give action points every N (value set when hosting the server) to every player, considering upgrades as well. 
Functions like: Attacking, Buying upgrades, Elimination of a player, updating statistics
Random events - TBA  
If victory conditions are met - proceed to [victory state](victory.md)
