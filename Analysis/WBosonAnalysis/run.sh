## small script to run the analysis
analysis="main_WBosonAnalysis"
## for now, turn off Proof
parallel=0
## execute and run ROOT
echo "starting ROOT"
##
root -l -b << EOF
.L $analysis.C
$analysis($parallel)
EOF
##
echo "end of ROOT execution"
