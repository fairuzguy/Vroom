#!/bin/bash

source ../shared-scripts.sh

# Dependencies
fetch_brew_dependency "wget"
fetch_brew_dependency "cmake"

# Third party libs
fetch_third_party_lib_sdl
fetch_third_party_lib_glm

# Downloading the emscripten SDK
pushd ../third-party
	if [ ! -d "emscripten" ]; then
		echo "Fetching Emscripten SDK ..."
		wget https://github.com/emscripten-core/emsdk/archive/master.zip
		unzip -q master.zip
		mv emsdk-master emscripten
		rm master.zip
		pushd emscripten
			echo "Updating Emscripten SDK ..."
			./emsdk update
			echo "Installing latest Emscripten SDK ..."
			./emsdk install latest
			echo "Activating latest Emscripten SDK ..."
			./emsdk activate latest
		popd
	fi
popd
