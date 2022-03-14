#!/bin/bash

prog=`basename "$PWD"`
echo $prog

for ip in "$@"
do
echo './'$prog' 192.168.2.'$ip
gnome-terminal -e 'bash -c "./'$prog' 192.168.2.'$ip'; read"'
sleep 0.1   
done
