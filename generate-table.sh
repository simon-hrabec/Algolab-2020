#!/bin/bash

REPO_PATH="${1:-https://github.com/simon-hrabec/Algolab2020/tree/main/}"

echo_link() {
	PROBLEM_PATH="${REPO_PATH}$(echo "$1" | sed 's| |%20|g')"
	PROBLEM_PDF_PATH="${PROBLEM_PATH}/description.pdf"
	PROBLEM_NAME="$(echo "$1" | sed 's|^.*[[:digit:]][[:digit:]]\( PotW\)\? - ||g')"
	echo -n "<a href=\"${PROBLEM_PDF_PATH}\"><img src=\"https://i2.wp.com/www.uei.com/wp-content/uploads/2017/10/pdf-icon.png\" height=\"18\"></a>"
	echo -n "[${PROBLEM_NAME}](${PROBLEM_PATH})"
}

echo "## Featured solutions"
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
			fi
			echo -n " | "
		done
		printf "\n"
	fi
done

printf "\n"