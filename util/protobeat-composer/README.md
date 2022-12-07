# Protobeat composer
This folder contains the protobeat composer. This is a tool for creating new beatmaps for the Rhythmicity game.

## Requirements
* Java 8
* IntelliJ IDEA
	* The Lombok plugin is required to generate the data classes in IntellIJ IDEA
* Maven (for generating artifacts only)

## Opening the project
Most of the import steps can be accomplished by simply clicking on next or finish, but take not of the following:

* Open IntelliJ IDEA
* Import the project from Maven
* Enable auto import for Maven modules

## Building with maven
This requires Maven to be installed on your system. Generating an artifact can be achieved by running `mvn package` in the protobeat composer project root. Sometimes the first build fails, most of the times this can be remedied by running `mvn package` for a second time or appending the -U flag.

Artifacts appear in the `target/` folder. The file ending with `-with-dependencies.jar` is universal and will run on any system without configuration.