# Sudoku Solver

This repository contains a simple Sudoku solver implemented in C++.
It aims to solve only the simplest Sudoku puzzles—those where a unique number can be determined for a cell by checking the available candidates in its row, column, and section.

## How It Works

The program solves Sudoku puzzles using a process of elimination, based on the following rules:

* A cell is considered solved if there's only one possible number that can fit based on the current state of its row, column, and 3x3 section.
* The solver iterates over the board repeatedly, attempting to solve each empty cell (represented by 0) by finding the candidates that can be placed in the row, column, and section. If there's a unique candidate, the cell is filled.
* This solver is limited to puzzles where such unique matches exist for every empty cell.

## Limitations

This solver only works for simple Sudoku puzzles where each empty cell has a unique candidate that can be determined by checking its row, column, and section.
It cannot solve more complex puzzles that require advanced techniques like guessing, backtracking, or naked pairs.

## Getting Started

Load the example board and print the output to the console:  
`ss --board ./example_board.csv --print`

## Command-Line Arguments

The program accepts the following command-line arguments:

| Argument            | Description                                                                |
|---------------------|----------------------------------------------------------------------------|
| `--board <path>`    | Specifies the path to the Sudoku puzzle file (required).                   |
| `--print`           | Prints the loaded and solved board to the console.                         |
| `--write <path>`    | Writes the solved board to the specified file.                             |


## Setting Log Level

You can set the logging level for the application by defining the LOG_LEVEL environment variable before running the program. The supported log levels are:

* debug
* info (default)
* warn
* error
* critical
* off
