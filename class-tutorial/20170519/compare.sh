#!/bin/sh

fact(){
    a=$1
	b=$2
	if [ $a -ge $b ]; then
        return $a
    else
        return $b
    fi
	
}

read -p "type a:" a
read -p "type b:" b

fact $a $b 
re=$?
echo "$re is the biggest"

exit 0
