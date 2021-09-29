#!/bin/bash

echo "Adding Frameworks @rpath to binary ..."
install_name_tool -add_rpath @loader_path/../Frameworks out/Template

pushd out
    if [ ! -d "assets" ]; then
        echo "Linking 'assets' path to '../../assets'"
        ln -s ../../assets assets
    fi
popd
