#!/bin/bash
# generic cleaning of unnecessary files
rm -rf gmon.out
rm -f *~;
rm -rf *_ACLiC_*
rm -rf *.d
rm -rf *.pcm
rm -rf *.so

# and what is inside histograms/
rm -rf histograms/*
