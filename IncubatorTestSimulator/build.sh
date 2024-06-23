#!/bin/bash
export build_type=DEBUG
if [ $# -gt 0 ]
then
    if [ "$1" = "ALL" ] 
    then
        build_type=ALL
    fi;
    if [ "$1" = "RELEASE" ] 
    then
        build_type=RELEASE
    fi;
fi;

cd ..
if [ "$build_type" = "DEBUG" ]
then
    ninja -C IncubatorTestSimulator/BuildDirDebug
fi;
if [ "$build_type" = "RELEASE" ]
then
    ninja -C IncubatorTestSimulator/BuildDirRelease
fi;
if [ "$build_type" = "ALL" ]
then
    ninja -C IncubatorTestSimulator/BuildDirDebug
    ninja -C IncubatorTestSimulator/BuildDirRelease
fi;

cd IncubatorTestSimulator