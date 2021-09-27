#!/bin/bash

source ../shared-scripts.sh

verify_build_folder_exists

pushd build
	echo "Configuring CMake with Ninja ..."
	cmake -G Ninja ..
	echo "Building project with Ninja ..."
	ninja
popd
