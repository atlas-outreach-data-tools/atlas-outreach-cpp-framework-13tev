#!/bin/bash
## small script to run the analysis
analysis="main_SingleTopAnalysis"

##OPTION
echo Which option should I run? 
echo Options are:
echo 0 = run all data and MC one after another
echo 11,12,13,14 = run data only \(can be run in parallel\)
echo 2,3,41,42,43,44 = run MC samples only \(can be run in parallel\)
read varname
echo Option is $varname
option=$varname

if (( ($option == 11) || ($option == 12) || ($option == 13) || ($option == 14) || ($option == 0)  )) ; then
        echo 'WARNING! After running, you need to add the samples using: hadd data.root dataA.root dataB.root dataC.root dataD.root'
fi

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
