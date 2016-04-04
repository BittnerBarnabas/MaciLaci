#!/bin/bash
echo "Installing MaciLaci game in `pwd`/bin"
echo "Running qmake EVA_Bead_2.pro"
qmake EVA_Bead_2.pro
echo "Running make..."
make
./bin/MaciLaci
