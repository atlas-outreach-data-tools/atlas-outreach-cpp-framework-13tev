#!/bin/bash
## small script to run the analysis using the web configuration
analysis="main_HyyAnalysis_web"

##OPTION
echo Will always run all data and MC one after another!
varname=2
echo Option is $varname
option=$varname

echo Will always set PROOF to false for now!
proofvarname=0
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
