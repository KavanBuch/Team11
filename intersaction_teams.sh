#!/usr/bin/env bash

path_of_dir=$(pwd)
echo "${path_of_dir}"

path_of_playing_team="${path_of_dir}/${1}"
echo "${path_of_playing_team}"

path_of_chosen_team="${path_of_dir}/${2}"
echo "${path_of_chosen_team}"

# while read -r player1; do
#      found=0;
#      while read -r player2; do
#           echo ${player1}
#           echo ${player2}
#           if [ "${player1}" == "${player2}" ]; then
#                found=1;
#           fi
#      done < ${path_of_playing_team}
#      # echo "${found}"     
#      if [ "${found}" -eq 1 ]; then
#           echo "$player1" >> ./intersection_team.txt
#      fi   
# done < ${path_of_chosen_team}

while read -r line; do
     echo "${line}"
done < "${path_of_chosen_team}"

while read -r line; do
     echo "${line}"
done < "${path_of_playing_team}"
