#!/bin/bash

#Author: Isaiah Vogt
#Author email: ivogt@csu.fullerton.edu
#CPSC 223C-01
#Due Date: 02/21/2024 11:59pm

#OS developed on: 11.1.0ubuntu4
#OS developed on: 11.1.04ubuntu4

#Program Name: Array Search for Character Frequency in a File:

rm *.o
rm *.out

gcc -c -Wall -m64 -no-pie -fno-pie -o search.o array_search.c -std=c2x

gcc -m64 -no-pie -fno-pie -o search.out search.o -std=c2x

chmod u+x search.out

./search.out
