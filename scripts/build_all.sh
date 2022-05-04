#!/bin/bash

for app in ./applications/*;
do
	cd ${app}
	echo "in ${app}"
	make clean
	echo "Building..."
	make
	retval=$?	
	if [ $retval -ne 0 ]; then
		echo "Build error"
		exit $retval
	fi
	echo "Building done."
	cd ../..
done
