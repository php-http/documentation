#!/usr/bin/env bash

# Note: --include is not available in all versions of inotifywait
while inotifywait -e modify -r --include ".+?\.rst" .; do
    make html
done
