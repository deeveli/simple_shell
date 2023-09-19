#!/bin/bash

# Get the list of contributors from the Git log
contributors=$(git log --format='%aN' | sort -uf)

echo "# List of contributors for the SHELL PROJECT" > AUTHORS

while read -r contributor; do
 first_name=$(echo "$contributor" | awk '{print $1}')
 last_name=$(echo "$contributor" | awk '{print $NF}')

  echo "$first_name $last_name" >> AUTHORS
done <<< "$contributors"

echo "Authors list generated and saved in AUTHORS file."

