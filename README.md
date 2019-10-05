# TheHashRacer
## Introduction
Hi and welcome to the Race. This is a benchmark designed for VU MIF ISI students to race their hash generators in speed and reliability.
This program expects you to have created a C++ program that respects the requirements of [1-oji užduotis: Hash generatorius](https://github.com/blockchain-group/Blockchain-technologijos/blob/master/pratybos/1uzduotis-Hashavimas.md). Without further ado, LET'S GET RACING!
![Meme](https://funnymemes.co/memes/Slow_and_Steady_Funny_Meme.jpg)

## Getting started
You can get the binary from the [releases tab](https://github.com/AugustinasMK/TheHashRacer/releases) here on Github. The binary is standalone and only requires you to pass the path to your generator executable. You can also build the binary yourself (see below for instructions).

The code in this repository has been written in C++ and will thus require [`CMAKE`](https://cmake.org/) and `MAKE`(comes with either GNU or MinGW) to work correctly.
These are the steps to get the racer up and running:
```bash
git clone https://github.com/AugustinasMK/TheHashRacer.git
cd TheHashRacer/
mkdir build
cd build/
cmake .. -G "MinGW Makefiles"
```
If you get an error please run ```cmake ..``` Otherwise, move on to the next command.
```bash
mingw32-make
./TheHashRacer.exe <the full path to your hash generator exe>
```
### Warning
Please note that all `\` in your path should be `\\` for C++ to understand it. I also recommend  not having spaces in the path as it can and most likely will cause problems.

## Requirements for your Hash Generator
- Your hash generator should accept a single command-line argument in the form of a string and return a single console line that contains your hash.
- Your hash function has to accept inputs that are 1000 characters long.
## About posting your results
There are 3 ways to get your results onto the board:
1. Reach me at amakevicius98@gmail.com or [Augustinas Makevičius on Facebook](https://www.facebook.com/augustinasmkvs) and send me your executable. I will run the racer on my machine and update the board with your results myself.
2. Run the program yourself by using the steps in `Getting Started` and use the aforementioned methods of reaching me and I'll update the board.
3. Run the code yourself and post a pull request here on Github that contains your addition to the board.
## The Board

 - A - Checks the first case: if m1 and m2 are two different one character long strings the hashes should be of the same length.
 - B - Checks the second case: if m1 and m2 are two different 1000 characters long strings the hashes should be of the same length.
 - C - The time it takes to hash konstitucija.txt. 
 - D - The number of collisions when hashing 10000 pairs of random strings.
 - E - The maximum percentage of letter-wise difference when hashing 10000 pairs of random strings that differ by one character.
 - F - The minimum percentage of letter-wise difference when hashing 10000 pairs of random strings that differ by one character.
 - G - The average percentage of letter-wise difference when hashing 10000 pairs of random strings that differ by one character.
 
 |Author|Year|A|B|C|D|E|F|G|
 |------|----|-|-|-|-|-|-|-|
 |AugustinasMK|2017|PASS|PASS| 0.988009 s (Linux)|0|100%|58%|87%|
 |gitguuddd|2018|PASS|PASS| 0.8305 s (Linux)|0|100%|0%|92%|
 |Rytisgit|2017|PASS|PASS| 1.00654 s (Linux)|0|75%|45%|72%|
 |BlackDude22|2017|PASS|PASS| 1.16189 s (Linux)|0|98%|76%|92%|

 
 ## Credits
This racer has been created by me - [Augustinas Makevičius](https://github.com/AugustinasMK). You can find more of my work here on Github by pressing on my name or contacting me at amakevicius98@gmail.com
