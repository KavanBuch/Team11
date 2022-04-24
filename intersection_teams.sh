#!/usr/bin/env bash

path_of_dir=$(pwd)

path_of_playing_team="${path_of_dir}/${1}"

path_of_chosen_team="${path_of_dir}/${2}"

# if already exists then remove it because we will append the content inside it.

if [ -f "${path_of_dir}"/intersection_team.txt ]; then
     rm intersection_team.txt
fi

while read -r player1; do
     found=0;
     while read -r player2; do
          if [ "${player1}" == "${player2}" ]; then
               found=1;
          fi
     done < ${path_of_playing_team}    
     if [ "${found}" -eq 1 ]; then
          echo "$player1" >> ./intersection_team.txt
     fi   
done < ${path_of_chosen_team}
