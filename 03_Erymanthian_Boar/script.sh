#!/bin/sh

SCRIPT="task.sh"
DATE="8:42 AM 4/21/2020"
CMD="sh $SCRIPT"

echo "$CMD" | at $DATE
