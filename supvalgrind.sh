#!/bin/bash

# --- Configuration ---
# Path to your header file (adjust if necessary)
HEADER_FILE="include/fdf.h"
# Path to your Valgrind suppression file (adjust if necessary)
# Assuming 'valgrind.supp' is your Valgrind suppression file based on our previous conversation
SUPPRESSION_FILE="valgrind.supp"
# Temporary file to store extracted function names
TEMP_FUNCTION_LIST="fdf_function_list_$(date +%s).txt"

# --- Script Logic ---

echo "--- Starting Function Search Automation ---"
echo "Header File: $HEADER_FILE"
echo "Suppression File: $SUPPRESSION_FILE"

# 1. Check if the header file exists
if [ ! -f "$HEADER_FILE" ]; then
    echo "Error: Header file '$HEADER_FILE' not found."
    echo "Please ensure the path is correct and the file exists."
    exit 1
fi

# 2. Check if the suppression file exists
if [ ! -f "$SUPPRESSION_FILE" ]; then
    echo "Error: Suppression file '$SUPPRESSION_FILE' not found."
    echo "Please ensure the file is in the current directory or provide its full path."
    exit 1
fi

echo -e "\nExtracting function names from '$HEADER_FILE'..."

# Extract function names from the header file
# This command looks for sequences of word characters followed by an opening parenthesis
# and outputs them, one per line, to the temporary file.
grep -oP '[a-zA-Z_][a-zA-Z0-9_]*(?=\()' "$HEADER_FILE" > "$TEMP_FUNCTION_LIST"

if [ ! -s "$TEMP_FUNCTION_LIST" ]; then
    echo "No function names extracted. Please check the header file format or the grep pattern."
    rm -f "$TEMP_FUNCTION_LIST" # Clean up temp file
    exit 0
fi

echo "$(wc -l < "$TEMP_FUNCTION_LIST") function names extracted."
echo "List saved to: $TEMP_FUNCTION_LIST"

echo -e "\nSearching for extracted function names in '$SUPPRESSION_FILE'..."
echo "--- Matching Suppressions ---"

# Use the extracted function names to search in the suppression file
# The -f option tells grep to get patterns from a file.
# The -w option ensures whole word matching (e.g., 'init' won't match 'initialise').
# The -i option makes the search case-insensitive.
# You might want to add '-C N' (where N is a number) to see N lines of context around each match.
grep -wi -f "$TEMP_FUNCTION_LIST" "$SUPPRESSION_FILE"

echo "--- End of Matching Suppressions ---"

# Clean up the temporary file
rm -f "$TEMP_FUNCTION_LIST"

echo -e "\nAutomation complete."
