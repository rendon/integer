#!/bin/bash

for i in {1..50}
do
    echo "Test #$i: "
    ./generator.rb;

    TMP_FILE="/tmp/$(basename $0).$RANDOM.txt"
    cd ..
    ./integer 2> $TMP_FILE
    echo

    if [[ $? != 0 ]]
    then
        echo
        cat $TMP_FILE
        rm $TMP_FILE
        exit $? 
    fi

    rm $TMP_FILE
    cd - &> /dev/null
done

