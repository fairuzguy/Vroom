#!/bin/bash

source ../shared-scripts.sh

# Grabbing dependencies
fetch_brew_dependency "wget"
fetch_brew_dependency "xcodegen"

# Downloading SDL2
fetch_third_party_lib_sdl

# Framework for macOS
fetch_framework_sdl2

# Existing folder for macOS application
if [ ! -d "Source" ]; then
	echo "Linking 'Source' path to '../src'"
	ln -s ../src Source
fi

# Using xcodegen to make the xcode project for us (really helps with lag on old machines too)
echo "Generating XCode project ..."
xcodegen generate

