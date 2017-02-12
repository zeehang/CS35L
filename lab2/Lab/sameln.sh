#!/bin/bash
directory=$1

declare -a files
preprocess=`ls $directory | sort`
preprocessHidden=`ls -a $directory | grep "^\." | sort`
counter=0

#first add hidden files
for f in $preprocessHidden
do
    if [ -f $directory/$f ]
    then
	files[$counter]="$directory/$f"
        counter=$((counter+1))
    fi
done

#add the rest of the files
for f in $preprocess
do
    if [ -f $directory/$f ]
    then
      	files[$counter]="$directory/$f"
      	counter=$((counter+1))
    fi
done

for a in "${files[@]}"
do
    echo $a
done

let iter=0
let cap=counter-1
for checkItem in "${files[@]}"
do
    nextItem=$checkItem
    for nextItem in "${files[@]}"
    do
	if [ $checkItem != $nextItem ]
	   then
	   cmp -s "$checkItem" "$nextItem"
        if [ $? -eq "0" ]
	then
	    echo $checkItem and $nextItem are the same!
	    rm $nextItem
	    ln $checkItem $nextItem
#	else
#	    echo $checkItem and $nextItem are not the same!
	   fi 
	fi
    done
done

#for f in preprocess;
#	 echo "hello"
