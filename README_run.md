# Food Ordering CLI App

A terminal-based food ordering and delivery system built in C++.

## Features
- Interactive menu: `menu`, `add`, `order`, `exit`
- Command-line support: `--order`, `--history`, `--list`, `--help`
- CSV order history
- Pizza customization (size, toppings, sauces)

## Usage
```
foodapp.exe
foodapp.exe --list
foodapp.exe --history
foodapp.exe --order --item "Pizza Diavola" --qty 2 --custom "extra cheese" --name "Name" --address "City" --phone "0723123123"
```

## Build
```
make     # compiles foodapp.exe
    or use the following command to compile: 
        g++ -std=c++17 main.cpp cli.cpp cart.cpp fileio.cpp -o foodapp.exe
make clean
    or use the following command to delete:
        del foodapp.exe
```