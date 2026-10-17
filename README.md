# WordleCli

Wordle for the command line, written in C. Each game picks a random word from a list of 14,855 five-letter words, so you get a new puzzle every time you run it.

## How to play

You have **6 guesses** to find the hidden five-letter word. After each guess, every letter is coloured:

| Colour | Meaning |
| --- | --- |
| 🟩 Green | Right letter, right spot |
| 🟨 Yellow | The letter is in the word, but somewhere else |
| 🟥 Red | The letter is not in the word |

The board is redrawn after every guess, so you can see all your earlier guesses. Guess the word to win. If you run out of guesses, the game shows you the answer.

## Building

You need a C compiler. The code uses the GCC `\e` escape, so use GCC (on Windows, [MSYS2](https://www.msys2.org/) or MinGW).

```bash
gcc WordleCli.c -o Wordle.exe
```

## Running

Run the game from the repository folder, because it loads `words.txt` from the current directory:

```bash
./Wordle.exe
```

Type a guess and press Enter. When the game ends, press any key to exit.


## Files

- `WordleCli.c`: the game
- `words.txt`: the word list, one word per line
