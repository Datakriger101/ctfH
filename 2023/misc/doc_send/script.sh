#!/bin/bash

# I think this only on the server, do manuely when testing 
while [ 1 -gt 0 ]
do
	cat doc_info.txt | nc -q 0 -l 3001
done
