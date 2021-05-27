#!/bin/bash
## small script to run the analysis
analysis="main_WBosonAnalysis"

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
root -l -b << EOF // El comando "-b" significa que correrá en modo bash, sin gráficas. y le comando "-l" hace que no aparezca el banner ROOT
.L $analysis.C+ //Compila el archivo analysis.C (main_WBosonAnalysis.C) y genera una librería compartida $analysis
$analysis($parallel,$option) // parallel = 1, option = 0
EOF // End of Comand (EOF), es un delimitador. El << se interpreta como una instrucción para leer la entrada has que finalice.
##
echo "end of ROOT execution"
