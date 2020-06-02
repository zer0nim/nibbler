# nibbler

_A snake implementation with multiples graphical interfaces_

## About

> The purpose of this project is to create our version of the game Snake, with at least 3 different GUIs. These GUIs being shared libraries.

### NCURSES
![ncurses](/imgs/ncurses.png "ncurses")

### SFML
![sfml](/imgs/sfml.png "sfml")

### SDL
![sdl](/imgs/sdl.png "sdl")

## Installation

Clone the project.

```bash
git clone https://github.com/ebaudet/abstract-vm.git
cd abstract-vm
make
```

## Usage

```bash
./nibbler --usage
usage: ./nibbler width height [-g gui] [-b gameboard] [-s snakeSpeed]

positional arguments
  width:  set the windows width
  <uint32 range=[200:7680]>

  height:  set the windows height
  <uint32 range=[200:4320]>

optional arguments
  gui:  -g, --gui  change the starting gui id
  <uint8 default=0 range=[:2]>

  gameboard:  -b, --gameboard  set the gameboard size
  <uint32 default=16 range=[10:1000]>

  snakeSpeed:  -s, --snakeSpeed  change the snake speed
  <float default=10.500 range=[0.000:100.000]>

description
  The purpose of this project is to create our version of the game Snake,
  with at least 3 different GUIs. These GUIs being shared libraries.
```
