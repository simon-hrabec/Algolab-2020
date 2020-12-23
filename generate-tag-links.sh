#!/bin/bash

REPO_PATH='https://github.com/simon-hrabec/Algolab2020/tree/main/'

cp README.source README.md
{
	find . -type f -name "tags" -exec cat {} \; | sort | uniq | while read -r tag; do
		echo -n "- $tag - "
		grep -rl "$tag" */tags | while read -r problem; do
			echo -n "[W$(echo "$problem" | sed 's/[^0-9]*//g' )/$(echo "$problem" | sed 's|.* - \(.*\)/tags|\1|g')]"
			echo -n "($REPO_PATH$(echo "$problem" | sed 's|/tags||g' | sed 's| |%20|g')) "
		done
		printf "\n"
	done
} >> README.md

