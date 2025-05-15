#!/bin/bash

start_time=$(date +%s)

## small script to run the analysis
analysis="main_TTbarAnalysis"

##OPTION
echo Which option should I run? 
echo Options are:
echo 0 = run all data and MC one after another
echo 1 = run data only
echo 2,3,4,5 = run MC samples only
read varname
echo Option is $varname
option=$varname

#PROOF is currently desactivated 
parallel=0

## execute and run ROOT
echo "starting ROOT"
##
root -l -b << EOF
.L $analysis.C+
$analysis($parallel,$option)
EOF
##
echo "end of ROOT execution"

end_time=$(date +%s)
execution_time=$((end_time - start_time))

# Calculate hours, minutes, and seconds
hours=$((execution_time / 3600))
minutes=$(((execution_time % 3600) / 60))
seconds=$((execution_time % 60))

echo "Execution time: ${hours}h ${minutes}m ${seconds}s"
