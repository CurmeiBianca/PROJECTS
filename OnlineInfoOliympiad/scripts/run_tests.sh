#!/bin/bash

if [ "$#" -ne 3 ]; then
    exit 1
fi

EXEC_FILE="$1"
INPUT_FILE="$2"
TEMP_OUT="$3"

if [ ! -f "$EXEC_FILE" ] || [ ! -f "$INPUT_FILE" ]; then
    exit 1
fi

timeout ls "$EXEC_FILE" < "$INPUT_FILE" > "$TEMP_OUT" 2>/dev/null
exit $?
