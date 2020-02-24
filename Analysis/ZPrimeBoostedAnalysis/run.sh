#!/bin/bash
## small script to run the analysis
analysis="main_ZPrimeBoostedAnalysis"

##OPTION
echo Which option should I run? 
echo Options are:
echo 0 = run all data and MC one after another
echo 1 = run data only 
echo 2,3 = run MC samples only 
read varname
echo Option is $varname
option=$varname

echo Should I use PROOF? \(will make things faster\)
echo Options are:
echo 0 = NO
echo 1 = YES
read proofvarname
echo PROOF option is $proofvarname
parallel=$proofvarname


## execute and run ROOT
echo "starting ROOT"
##
root -l -b << EOF
.L $analysis.C+
$analysis($parallel,$option)
EOF
##
echo "end of ROOT execution"
