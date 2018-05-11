#!/bin/sh
(gcc -Wall -o drivers/ACCEL piloteACCEL.c -lm && echo "Nouveau pilote 'ACCEL' dans ./drivers") || echo "Echec."
