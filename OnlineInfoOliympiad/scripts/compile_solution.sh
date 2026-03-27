#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "[ERROR] Numar invalid de argumente. Usage: $0 source_file output_file"
    exit 1
fi

SOURCE_FILE="$1"
OUTPUT_EXE="$2"

sync

echo "[DEBUG] Compile solution.sh ruleaza:"
echo "          SOURCE_FILE=$SOURCE_FILE"
echo "          OUTPUT_EXE=$OUTPUT_EXE"

if [ ! -f "$SOURCE_FILE" ]; then
    echo "[ERROR] Fisier sursa nu exista: $SOURCE_FILE"
    exit 1
fi

gcc "$SOURCE_FILE" -o "$OUTPUT_EXE" -std=c99 -O2 -lm

if [ $? -eq 0 ] && [ -f "$OUTPUT_EXE" ]; then
    chmod +x "$OUTPUT_EXE"
    echo "[DEBUG] Compilare reusita: $OUTPUT_EXE"
    exit 0
else
    echo "[ERROR] Compilare esuata!"
    exit 1
fi 
