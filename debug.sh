#!/bin/bash
# This is run outside gnome-terminal by mpirun.

# Create a tmp file that we can wait on.
export MY_MPIRUN_TMP_FILE="$(mktemp)"

# Start the gnome-terminal. It will exit immediately.
# Call the wrapper script which removes the tmp file
# after the actual command has ended.
gnome-terminal -- ./helper.sh "$@"

# Wait for the file to disappear.
while [ -f "${MY_MPIRUN_TMP_FILE}" ] ; do
    sleep 1
done

# Now exit, so mpirun can destroy the MPI environment
# and exit itself.
