#!/bin/bash

REPO_PATH="${1:-https://github.com/simon-hrabec/Algolab2020/tree/main/}"

echo_link() {
	echo -n "[$(echo "$1" | sed 's|^.*[[:digit:]][[:digit:]]\( PotW\)\? - ||g')](${REPO_PATH}$(echo "$1" | sed 's| |%20|g'))"
}

echo "| Week | Problem of the Week | 1st problem | 2nd problem | 3rd problem | 4th problem |"
echo "| --- | --- | --- | --- | --- | --- |"

for i in $(seq -w 01 14); do 
	if ls -1 | grep "$i" > /dev/null; then
		#First handle POTW
		echo -n "| $(echo $i | sed 's|^0*||') | "
		if ls -1 | grep "$i PotW" > /dev/null; then
			echo_link "$(ls -1 | grep "$i PotW" | head -1)"
		fi
		echo -n " | "

		# Handle problem 1-4
		for j in $(seq 1 4); do
			PROBLEM="$(ls -1 | grep "$i - " | sed "${j}q;d")"
			if [ ! -z "$PROBLEM" ]; then
				echo_link "$PROBLEM"
				echo -n " | "
			fi
		done
		printf "\n"
	fi
done

printf "\n"