# mapfinder
A tool to assist in finding game maps in a game binary.

Or more formally, a frequency search.

To explain what it does:

Say you have a game map. You don't know the code for a floor tile, or a wall tile.

Well, say you look at the map and it has 3 floor tiles, and 4 wall tiles, consecutive.

We want to find the map location in memory, but all we know is how many times the tiles occur in sequence.

Assuming the binary to search within is called game.bin, you say:

    mapfinder game.bin 3 4

It then says the matches it found.

There is a good chance that if there is only 1 match, it will be the position of the game map in memory.

That's pretty much it!

