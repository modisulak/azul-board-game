## AZUL - Command line edition

### The Aim
To create a base implementation of a 2 player, human only, command line version of the strategy board game - Azul.

---
## Repository structure
``` sh
.
├── bin                 # Executables are stored in the bin folder
├── include             # Contains all class header files (.h).
├── resources           # Contains text files that are read by the application, i.e. help, rules and credits
│   └── tests           # Contains a test overview and many subdirectories for black box testing.
│         └── <test>    # Each test subdirectory contains 2 files:
│                                  # <test>_player.txt - Commands to redirect as input into the application.
│                                  # <test>_expected.txt - The expected output of the test.
├── save_files          # All saved games are stored in this directory, including inputs to be loaded for testing.
│   └── save_tests      # All test outputs are saved in this subdirectory.
└── src                 # Contains all source code implementations (.cpp) for the game.
```

---
### The Team
**Name:** _Moditha Sulakshana_

**Student ID:** _s3756843_

**Email:** _s3756843@student.rmit.edu.au

**Name:** _Thomas Pfundt_

**Student ID:** _s3724447_

**Email:** _s3724447@student.rmit.edu.au_

**Name:** _Aiden Contini_

**Student ID:** _s3780445_

**Email:** _s3780445@student.rmit.edu.au_

---
### Testing
The project uses black box testing to run predefined tests on the application through I/O redirection of an series of
commands defined in a text file. In most test cases, games are loaded in a base state, the action being tested is 
executed, then the game is saved to an output file and compared against an expected output.

In cases where this is not possible - i.e. loading invalid saved files or testing end of game scoring where the game
cannot be saved after completion, tests are run in the same fashion, except outputs captured by redirecting the output
to an output file, instead of saving the game. These tests are more brittle / flaky, as they rely on consistent menu's,
load game lists etc, and therefore have been used only where there is no other option.

As this is a manual process, and there are multiple tests, to make testing easier, a test overview document is provided
in the resources folder. This document assigns each test an ID, a description of what is being tested, preconditions,
actions, expected results, associated files and a make command to run the test.

Additionally, all tests have been categorised, so that a single category of tests can be run independently, i.e. to 
run all Tile placement tests, the command ```make test-TP``` will run all the tile placement tests.

To run all tests, the command ```make tests``` will clean and compile the executable, and then proceed to run all tests
sequentially.

The description of each test is printed out before it runs. If a test fails, other tests will continue to run, but
the test will show a failed output, and depending on the cause of failure, either an error message, or the differences
between the actual output and the expected output will also be displayed.

Due to having multiple contributors, often file format issues with the test cases are experienced, which causes issues
with end of line characters being added unknowingly. Therefore, a shell script in the route of the directory - 
```./reformat_files.sh``` can be run to reformat all files in the resources and saved files directories, to aleviate 
this issues.

n.b. This script requires dos2unix to be installed on the users machine. This can be installed with the command 
```sudo apt-get install dos2unix```.

---
### Playing the game
The game is a two player strategy game. Players take turns selecting tiles from factories to put into storage rows.
Once a storage row is full, at the end of the round, completed storage rows will tile the mosaic wall, scoring points
for each player. If the player "breaks" any tiles during game play, points will be deducted from the players score.

The aim of the game is to be the player with the most points at the end of the game. The game ends after completion 
of a round in which at least one player has completed a horizontal line of 5 consecutive tiles on the mosaic wall.

Note: Just because a player finishes a row first, does not necessarily mean they will win!

Players can view the rules from within the game, by typing the keyword ```rules```.

Players can also receive help on game commands, by typing the keywor ```help```, although this command will not give
the player any move suggestions or specific help... yet...

Happy Gaming!