#!/bin/bash

source ../shared-scripts.sh

# Grabbing dependencies
fetch_brew_dependency "wget"
fetch_brew_dependency "cmake"
fetch_brew_dependency "ninja"

# Downloading third-party libraries
fetch_third_party_lib_sdl

# Downloading frameworks
fetch_framework_sdl2
