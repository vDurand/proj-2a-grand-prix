#!/bin/sh
(gcc -Wall -o drivers/Random piloteRandom.c -lm && echo "Nouveau pilote 'Random' dans ./drivers") || echo "Echec."
