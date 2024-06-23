#!/bin/bash
chmod +x build.sh install.sh clean.sh
export configuration_type=DEBUG
if [ $# -gt 0 ]
then
    if [ "$1" = "ALL" ] 
    then
        configuration_type=ALL
    fi;
    if [ "$1" = "RELEASE" ] 
    then
        configuration_type=RELEASE
    fi;
fi;

cd ..
if [ "$configuration_type" = "DEBUG" ]
then
    cmake -S . -B IncubatorTestSimulator/BuildDirDebug -G"Ninja" -DCMAKE_BUILD_TYPE=Debug 
fi;
if [ "$configuration_type" = "RELEASE" ]
then
    cmake -S . -B IncubatorTestSimulator/BuildDirRelease -G"Ninja" -DCMAKE_BUILD_TYPE=Release 
fi;
if [ "$configuration_type" = "ALL" ]
then
    cmake -S . -B IncubatorTestSimulator/BuildDirDebug -G"Ninja" -DCMAKE_BUILD_TYPE=Debug 
    cmake -S . -B IncubatorTestSimulator/BuildDirRelease -G"Ninja" -DCMAKE_BUILD_TYPE=Release 
fi;

cd IncubatorTestSimulator