## small script to run the analysis
analysis="main_HZZAnalysis"

# local or PROOF?
echo Run local or on PROOF? Options are:
echo 0 = local
echo 1 = PROOF
read option
echo Option is $option
parallel=$option

# which files?
echo Which files should I run? Options are:
echo 0 = run all data and MC one by one
echo 1 = run data only, 2,3,4,5 = run MC samples only
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
