# Rubik

_The goal of the project is to solve 3x3x3 [Rubik's Cubes](https://en.wikipedia.org/wiki/Rubik%27s_Cube) with minimum spins using Thistlethwaite's 52-move algorithm._

## Installation:

```sh
git clone https://github.com/Dunk4n/rubik.git
cd ./rubik
make
```

## Usage:
* `./rubik SEQUENCE [-h] [-d] [-s] [-g[0-100]] [-w]`

## Example:
* `./rubik "B' B F2 R' R R L2 L B'"`
* `./rubik "" -g100`
* `./rubik "B D' L' B2 U2 F F' F L' R2 U' B R2 F2" -w`

## Options:
* `-h --help   Display this help and exit`
* `-d          Display rubik`
* `-s          Change thistlethwaite to Belgian rubik solving algorithm`
* `-g[0-100]   generate instructions`
* `-w          display 3d rubik`

## Window command:
* `r`: to start to resolve the rubik
* `w` or `s`: to go forward or backward
* `d` or `a`: to go to the right or left
* `e` or `q`: to go up or down

![Rubik](https://github.com/Dunk4n/rubik/blob/master/rubik.gif)
