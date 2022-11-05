#!/bin/bash

# logging

logging=0

log() {
  if [ $logging -eq 1 ]
  then
    echo $@
  fi
}

# initialization

declare -a bitstring

init() {
  local x=$1
  for (( i=0 ; i < ${#x} ; i++ ))
  do
    if [ ${x:i:1} -eq 0 ] || [ ${x:i:1} -eq 1 ]
    then
      bitstring+=(${x:i:1})
    fi
  done
}

if [ ${#@} -eq 1 ]
then
  logging=1
  init $1
else
  init "00011110000"
fi

log "Bitstring to decode: " ${bitstring[@]}

# decode

errindex=0
bitpos=0

for (( i=1; i<=${#bitstring[@]}; i++ ));
do
  if [ $((i & ((i - 1)))) -eq 0 ]
  then
    val=0
    for (( j=i; j <=${#bitstring[@]}; j++ ));
    do
      if [ $((((j >> bitpos)) & 1)) -eq 1 ]
      then
        val=$((val + bitstring[((j - 1))]))
      fi
    done
    val=$((val % 2))
    errindex=$((errindex + ((val * i))))
    ((bitpos++))
  fi
done
if [ $errindex -gt 0 ]
then
  log "Error detected at: " $errindex
  ((errindex--))
  bitstring[errindex]=$((((${bitstring[errindex]} + 1)) % 2))
else
  log "No error was detected"
fi
for (( i=1; i<=${#bitstring[@]}; i++ ));
do
  if [ $((i & ((i - 1)))) -ne 0 ]
  then
    result+=(${bitstring[((i - 1))]})
  fi
done

echo "Result: ${result[@]}"

exit 0
