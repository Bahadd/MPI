#!/bin/bash
# This is run by gnome-terminal.

# The command you actually want to run.
"$@"

# Remove the tmp file to show that the command has exited.
rm "${MY_MPIRUN_TMP_FILE}"
