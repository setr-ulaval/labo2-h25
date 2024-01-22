#!/bin/bash
set -e

bn=$(basename $1)

# Ensure the folder exists
ssh pi@$2 "mkdir -p /home/pi/projects/laboratoire2/pointdemontage"

# Sync executable
rsync -az $1/build/tp2client pi@$2:/home/pi/projects/laboratoire2/tp2client

# Execute GDB
ssh pi@$2 "rm -f /home/pi/capture-stdout-fuse; rm -f /home/pi/capture-stderr-fuse; nohup gdbserver :4568 /home/pi/projects/laboratoire2/tp2client -f -s /home/pi/projects/laboratoire2/pointdemontage > /home/pi/capture-stdout-fuse 2> /home/pi/capture-stderr-fuse < /dev/null &"
sleep 1
