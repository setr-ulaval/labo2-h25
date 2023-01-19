#!/bin/bash
set -e

# Sync executable
bn=$(basename $1)
rsync -az $1/build/tp2serveur pi@$2:/home/pi/projects/laboratoire2/tp2serveur

# Execute GDB
ssh pi@$2 "rm -f /home/pi/capture-stdout-curl; rm -f /home/pi/capture-stderr-curl; nohup gdbserver :4567 /home/pi/projects/laboratoire2/tp2serveur > /home/pi/capture-stdout-curl 2> /home/pi/capture-stderr-curl < /dev/null &"
sleep 1
