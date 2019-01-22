#!/bin/bash

FILE=$1

if [[ -f "$1" ]]; then
	sshpass -p 'raspberry' scp -P10022 $FILE pi@localhost:$FILE
else
	echo "Usage: copy_to_pi file_name"
fi

