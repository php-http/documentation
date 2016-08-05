#!/usr/bin/env bash

while inotifywait -e modify -r --include ".+?\.rst" .; do
    make html
done
