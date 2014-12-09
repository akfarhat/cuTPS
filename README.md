cuTPS
=====

COMP 3004 Project: Carleton University Textbook Publishing System

Contributors:
-------------

- Abdul-Karim Farhat
- Kirill Kravinskiy
- Ahmad Masoud
- Zach Renaud


Project Configuration:
----------------------

The main Qt project contains 3 subprojects:

1. cuTPS-client: the client application. Outputs: cuTPS-client executable
2. cuTPS-server: the server. Outputs: cutpsd executable
3. cuTPS-common: common shared library. Outputs: libcutps.1.so dynamic library.

Project build path configuration:
---------------------------------

Within the project's build path, following items exist:

* cuTPS-server:
	+ /db/cutpsd.db: sqlite database used by the server
	+ cutps.conf: configuration file. Path to the database can be changed in this file.

Build instructions:
-------------------
Using QtCreator:
* import project to QTCreator
* once asked, setup build kits (providing paths to debug and release build output directories)
* run the build
* in case of issues while building, 'Build -> Clean all' then 'Build -> run qmake' then 'Build -> Build all'
* following files will be produced by build:
	/build/cuTPS-client/cuTPS-client -- the client executable
	/build/cuTPS-server/cutpsd -- the server executable.

Using command-line:
* In project directory, run 'qmake -unix cuTPS-KernelPanic.pro'
* Run 'make' (some error messages about file copying are possible -- this is normal)
* After the build, run 'sudo make install' in order to properly install libcutps.so library under /usr/lib.


Run instructions:
-----------------

* run the cutpsd server daemon. Ensure that the server is started and proper database file is used. (look in the standard output)
* run the cuTPS-client


Credentials:
------------
Student user: johnsmith/alamepassword
CM user: cm/pass
