Filesystem Simulator
====================

This project is a simple filesystem simulator written in C. It allows users to create, delete, read, and write files within a simulated filesystem. The project also supports saving the filesystem state to a file and loading it from a saved state.

Table of Contents
-----------------
- Features
- File Structure
- Installation
- Usage
- Commands
- Contributing
- License

Features
--------
- Create Files: Add new files to the simulated filesystem.
- Delete Files: Remove existing files from the filesystem.
- Read Files: Access the contents of files within the filesystem.
- Write Files: Store data in files.
- Persistent Storage: Save the state of the filesystem to disk and reload it later.

File Structure
--------------
- core.h: Contains utility functions, including a function to get the current time.
- coreop.c: Implements the core operations of the filesystem, such as creating, deleting, reading, and writing files.
- filesys.h: Defines the structure of the filesystem, including inodes and data blocks, and declares the functions for interacting with the filesystem.
- filesystem.c: Initializes the filesystem and manages the free blocks.
- main.c: Provides a command-line interface for interacting with the filesystem.

Installation
------------
To compile and run the filesystem simulator:

1. Clone this repository:
   git clone https://github.com/raharezaie/filesystem-simulator.git
   cd filesystem-simulator

2. Compile the code using `gcc`:
   gcc -o filesystem main.c coreop.c filesystem.c

3. Run the compiled program:
   ./filesystem

Usage
-----
After starting the program, you can interact with the filesystem using various commands. The program runs in an interactive mode where you can enter commands to manipulate files.

Commands
--------
- create `<filename>`: Create a new file with the specified name.
- delete `<filename>`: Delete the file with the specified name.
- read `<filename>`: Read the contents of the file and display it.
- write `<filename>` `<data>`: Write the specified data to the file.
- ls: List all files in the filesystem.
- help: Display the help message with all available commands.

Contributing
------------
Contributions are welcome! If you'd like to contribute, please fork the repository, create a new branch for your feature or bug fix, and submit a pull request.

