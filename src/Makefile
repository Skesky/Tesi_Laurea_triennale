all: main

main:
	touch coherent_states.csv
	g++  *.cpp -Wall -O3 -o simulazione

.PHONY: clean

clean: 
	rm -f simulazione *.csv
