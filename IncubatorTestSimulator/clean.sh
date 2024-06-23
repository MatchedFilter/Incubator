#!/bin/bash
export clean_type=DEBUG
if [ $# -gt 0 ]
then
    if [ "$1" = "ALL" ] 
    then
        clean_type=ALL
    fi;
    if [ "$1" = "RELEASE" ] 
    then
        clean_type=RELEASE
    fi;
fi;

cd ..
if [ "$clean_type" = "DEBUG" ]
then
    IncubatorTestSimulator/bin/Debug 2>/dev/null
    rm -rf IncubatorTestSimulator/BuildDirDebug 2>/dev/null
fi;
if [ "$clean_type" = "RELEASE" ]
then
    IncubatorTestSimulator/bin/Release
    rm -rf IncubatorTestSimulator/BuildDirRelease 2>/dev/null
fi;
if [ "$clean_type" = "ALL" ]
then
    rm -rf IncubatorTestSimulator/bin/Debug 2>/dev/null
    rm -rf IncubatorTestSimulator/bin/Release 2>/dev/null
    rm -rf IncubatorTestSimulator/BuildDirDebug 2>/dev/null
    rm -rf IncubatorTestSimulator/BuildDirRelease 2>/dev/null
fi;

cd IncubatorTestSimulator