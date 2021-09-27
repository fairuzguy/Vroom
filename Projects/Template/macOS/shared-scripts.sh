#!/bin/bash

# Installing dependencies from Homebrew
function fetch_brew_dependency() {
	FORMULA_NAME=$1
	echo "Fetching Brew dependency: '$FORMULA_NAME'."
	if brew ls --versions $FORMULA_NAME > /dev/null; then
		echo "Dependency '$FORMULA_NAME' is already installed, continuing ..."
	else
		echo "Dependency '$FORMULA_NAME' is not installed, installing via Homebrew ..."
		brew install $FORMULA_NAME
	fi
}

# Creating necessary folders just in case
function verify_third_party_folder_exists() {
	pushd ../
		if [ ! -d "third-party" ]; then
			mkdir third-party
		fi
	popd
}

# Downloading SDL library (note, windows uses SDL-windows, not the standard SDL)
function fetch_third_party_lib_sdl() {
	verify_third_party_folder_exists
	pushd ../third-party
		if [ ! -d "SDL" ]; then
			echo "Fetching SDL (SDL2: 2.0.9) ..."
			wget https://www.libsdl.org/release/SDL2-2.0.9.zip
			unzip -q SDL2-2.0.9.zip
			mv SDL2-2.0.9 SDL
			rm SDL2-2.0.9.zip
		else
			echo "SDL library already exists in third-party folder"
		fi
	popd
}

# Frameworks for macOS console application (folder)
function verify_frameworks_folder_exists() {
	if [ ! -d "Frameworks" ]; then
		mkdir Frameworks
	fi
}

# Downloading SDL2 framework for macOS
function fetch_framework_sdl2() {
	verify_frameworks_folder_exists
	pushd Frameworks
		if [ ! -d "SDL2.framework" ]; then
			wget https://www.libsdl.org/release/SDL2-2.0.9.dmg
			echo "Mounting DMG file ..."
			hdiutil attach SDL2-2.0.9.dmg
			echo "Copying SDL2.framework from DMG file into the current folder ..."
			cp -R /Volumes/SDL2/SDL2.framework .
			echo "Unmounting DMG file ..."
			hdiutil detach /Volumes/SDL2
			echo "Deleting DMG file ..."
			rm SDL2-2.0.9.dmg
			pushd SDL2.framework
				echo "Code signing SDL2.framework ..."
				codesign -f -s - SDL2
			popd
		else
			echo "SDL2.framework already exists"
		fi
	popd
}

# Build folder verification for cmake builds
function verify_build_folder_exists() {
	echo "Checking for build folder ..."
	if [ ! -d "build" ]; then
		mkdir build
	fi
}
