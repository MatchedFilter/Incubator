#!/bin/bash
export install_type=DEBUG
if [ $# -gt 0 ]
then
    if [ "$1" = "ALL" ] 
    then
        install_type=ALL
    fi;
    if [ "$1" = "RELEASE" ] 
    then
        install_type=RELEASE
    fi;
fi;

./build.sh $install_type
cd ..
if [ "$install_type" = "DEBUG" ]
then
    cmake --install IncubatorTestSimulator/BuildDirDebug
fi;
if [ "$install_type" = "RELEASE" ]
then
    cmake --install IncubatorTestSimulator/BuildDirRelease
fi;
if [ "$install_type" = "ALL" ]
then
    cmake --install IncubatorTestSimulator/BuildDirDebug
    cmake --install IncubatorTestSimulator/BuildDirRelease
fi;

cd IncubatorTestSimulator