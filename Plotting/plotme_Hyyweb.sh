#!/bin/bash
########################################
#
# General plotting script
#
########################################

    # run main command
    root -l -b << EOF
	.L Plotting.cxx+
    	Plotting *m=new Plotting();
	m->SetLumi(36000);
	m->SetOption("HyyAnalysis");
    	m->SetInputLocation("../Analysis/HyyAnalysis/Output_HyyAnalysis")
    	m->run()
    	.q
EOF

########################################
