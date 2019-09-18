## small script to run the analysis
analysis="main_TTbarAnalysis"
## for now, turn off Proof
parallel=0


##OPTION
echo Which option should I run?
read varname
echo Option is $varname

option=$varname


## execute and run ROOT
echo "starting ROOT"
##
root -l -b << EOF
.L $analysis.C
$analysis($parallel,$option)
EOF
##
echo "end of ROOT execution"
