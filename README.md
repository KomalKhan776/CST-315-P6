# CST-315-P6
# Project 6: File System Manager

## Description
The project implements simple file system manager as part of custom Linux shell. 
It allows users to create directories, navigate between them, create files, 
and delete files and directories using some Linux commands. (mentioned below)

The file system uses a hierarchical tree structure.

## Features
- Create directories (mkdir)
- Navigate directories (cd ..)
- List contents (ls)
- Create files (touch)
- Delete files (rm)
- Delete empty directories (rmdir)
- Show current directory (pwd)

## Requirements
- Linux / Ubuntu
- g++ compiler

## Compile
g++ Project6.cpp -o Project6

## Run
./Project6

## Commands to run
- ls
- mkdir temp
- cd temp
- touch file1
- touch file2
- mkdir temp1
- ls
- cd temp1
- touch fileA
- ls
- rm fileA
- cd ..
- rmdir temp1
- cd ..
- ls

## Notes
- The directory must be empty before using rmdir
- Commands must be typed exactly as they are
- This is a simulated file system
