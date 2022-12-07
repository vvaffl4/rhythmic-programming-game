# Rhythmicity
This is the code repository for the Rhythmicity game.

# Project structure
 * app -> Contains the android application
 * util -> Contains all utility applications
	 * level-conv -> Converts levels from json to binary
	 * level-gen -> Generates test levels
	 * protobeat-composer -> Level editor

The folder src/app/main/glm is a git submodule, this contains the sources for the glm library.

# Requirements
Rhythmicity:
* Android Studio (version 3.0.1 or greater)
* Android device with at least Android 6

Protobeat composer:
* IntelliJ IDEA
* Maven

Level converter:
* CMake (version 3.6 or greater)
* A compatible C++ compiler (gcc/clang/msvc/mingw)

# Reading and running the code
To properly read and run the project, Android Studio is **required**. Upon opening Android Studio for the first time, you'll have to **import** the project. After opening the project, Android Studio will prompt to install all the required dependencies. It is important to **decline the gradle upgrade**. Following through with the upgrade will almost always break the project in some way or shape.

After the project has been successfully imported into Android Studio, it is just a matter of pressing run or debug in the toolbar at the top of the screen

# Installing
To install the game on an Android device without building the code you can install the apk. 
To install this apk unkown sources has to be turned on to allow the installation of apps from sources other then the play store.