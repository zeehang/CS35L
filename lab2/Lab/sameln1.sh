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

let iter=0
let cap=counter-1
for((i=0; i<$cap; i++))
do
    for((j=$i; j<$cap; j++))
    do
	if [ ${files[$i]} != ${files[$j]} ]
	   then
	   cmp -s "${files[$i]}" "${files[$j]}"
        if [ $? -eq "0" ]
	then
	   # echo ${files[$i]} and ${files[$j]} are the same!
	    rm ${files[$j]}
	    ln ${files[$i]} ${files[$j]}
#	else
#	    echo $checkItem and $nextItem are not the same!
	   fi 
	fi
    done
done

#for f in preprocess;
#	 echo "hello"
