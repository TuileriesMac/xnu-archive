#!/usr/bin/env bash
set -e
export PING_SLEEP=30s
export WORKDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export BUILD_OUTPUT=$WORKDIR/build.out
touch "$BUILD_OUTPUT"
dump_output() {
   echo "Printing 1000 lines of output: "
   tail -n 1000 "$BUILD_OUTPUT"
}
error_handler() {
  echo "ERROR: An error was encountered with the build."
  dump_output
  exit 1
}
trap 'error_handler' ERR
bash -c "while true; do echo \".\"; sleep \$PING_SLEEP; done" &
PING_LOOP_PID=$!
mkdir "BUILD.syskext"
make \
  DSTROOT="$PWD/BUILD.syskext" \
  install_config &> "$BUILD_OUTPUT"
dump_output
kill $PING_LOOP_PID
