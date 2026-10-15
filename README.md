# Battleships vs. the Aliens

This is a Battleships game I made in C. Earth is being attacked by aliens from Kepler, and
your mission is to sink their whole fleet before they sink yours. The aliens are controlled
by an enemy bot that I made smarter so the game is actually a challenge.

## How to play
- The alien board is on the left and your board is on the right.
- You attack by typing a row number and then a column letter, for example `5a`.
- `?` means a miss and `/` means a hit. Your ships are the `O`s.
- Each side has 5 ships: a carrier (5), a battleship (4), a cruiser (3), a submarine (3)
  and a destroyer (2). Whoever sinks all 17 ship squares first wins.

## How to build and run
**In VS Code** (with the CMake Tools extension): open the folder, build with **F7**, then run
it with the **▷** button in the status bar.

**From a terminal:**
```
cmake -S . -B build
cmake --build build
build\Debug\battleships.exe
```

---

## How I made the enemy smarter

### The first version
At first I made the game with my own enemy bot that hit my battleships at random spaces and
kept hitting until it had hit all of them and I lost. But this made the game too easy for the
player, because the bot I made was, in other words, stupid. Even after it hit one of my ships,
its next shot was random again, so it never finished off anything it found.

### The smart bot
So I made a smart bot that plays like a real human. It works in two modes:

- **Hunt mode (searching):** while it hasn't found anything, it only shoots at squares in a
  checkerboard pattern, like the black squares on a chess board. I can do this because the
  smallest ship is 2 squares long, so every ship has to cover at least one "black" square.
  This means the bot only has to search half of the board.
- **Target mode (finishing a ship):** after it hits something, it checks if it can shoot the
  square before or after the hit (left or right, because the ships are horizontal) and keeps
  going along that row until the ship sinks. Then it goes back to hunting.

The bot doesn't keep any memory of its own. Every turn it looks at its hits (`/`) and misses
(`?`) on the board, the same way a person would look at their notes.

To build it I wrote two helper functions:
- `canShoot` checks if a square is on my board and hasn't been shot yet. Target mode needs it
  so it doesn't shoot off the edge of the board or at the same square twice.
- `blackLeft` checks if there are any checkerboard squares left to search, so the bot doesn't
  get stuck looking for one that doesn't exist.

**It plays fair:** the bot only uses what it learned from its own shots. It never looks at
where my ships are to decide where to shoot.

### Fixing my old code
I wrote this game about 2 years ago, before I knew some of what I know now. Before adding the
smart bot, I went back and fixed the bugs in my original code: reading outside the arrays, a
ship that could sometimes be placed on a row that doesn't exist, shots on the same square
erasing earlier hits, and ship messages that named the wrong ship.

### Results
I used Claude to play-test the game with the same strategy in every game, 24 games against each bot:

| Enemy bot  | Games the bot won |
|------------|-------------------|
| Random bot | 0 / 24            |
| Smart bot  | 11 / 24           |

Against the random bot, it had usually found only about half of my ships by the time I won.
Against the smart bot, the games were close every time.

## What I would improve next
- Tell the bot when a ship has sunk, so it stops wasting a shot after finishing one
- A probability-map bot that shoots where ships are most likely to be
- Ships that can also be placed vertically

## Built with
C and CMake. I used AI tools as a learning aid while fixing the old code and building the
smart bot, and I can explain how every part of it works.
