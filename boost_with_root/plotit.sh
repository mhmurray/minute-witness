#!/bin/bash

gnuplot --persist -e "plot 'lorenz_example.dat' using 3:4 w lp" &
