## small script to run the analysis
analysis="main_WBosonAnalysis"

##OPTION
echo Which option should I run? Options are:
echo 0 = run all data and MC one by one
echo 11,12,13,14 = run data only, 2,3,4,5 = run MC samples only
read varname
echo Option is $varname

option=$varname


echo Should I use PROOF? Options are:
echo 0 = NO
echo 1 = YES
read proofvarname
echo PROOF option is $proofvarname
parallel=$proofvarname


echo WARNING! After running, you need to add the samples using: hadd data.root dataA.root dataB.root dataC.root dataD.root


## execute and run ROOT
echo "starting ROOT"
##
root -l -b << EOF
.L $analysis.C
$analysis($parallel,$option)
EOF
##
echo "end of ROOT execution"
