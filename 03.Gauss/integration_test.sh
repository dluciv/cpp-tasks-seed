#!/bin/bash

status=true

# ---------------------------------------------------

./gauss AB.csv > X.actual.csv
cmp X.csv X.actual.csv || status=false
rm -f X.actual.csv

$status
