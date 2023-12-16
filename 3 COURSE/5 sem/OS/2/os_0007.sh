#!/bin/bash
if [ "$1" = "" ];
then
	echo parameter not found
	exit
else
	if ! [[ $1 =~ ^[0-9]+$ ]];
	then
   		echo pid = $1 not a number
		exit
	else if ps -p $1 > /dev/null
	then
		echo -n Name:
		ps -p $1 -o comm=
		echo Pid: $1
		echo -n PPid:
		ps -o ppid= -p $1

		if [ "$2" = "fd" ]; then
			ls -1 /proc/$1/fd
		fi
	else
		echo pid = $1 not found
		exit
		fi
	fi
fi				