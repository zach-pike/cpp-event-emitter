#!/bin/bash

FILENAME=build.sh

mkdir build

for FILE in *; 
do
    if [ $FILE != $FILENAME ]; then
        g++ $FILE -o build/${FILE/.cpp/}
    fi

    echo "Done!"
done