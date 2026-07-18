# Shadow Project
==============

Description
-----------
Shadow is a remote administration tool consisting of a C-based client and a Python-based server component. The project includes the shadow executable (compiled from shadow.c) and server.py for handling connections.

Components
----------
- shadow.c: C source code for the client agent
- shadow: Compiled executable of the client agent
- server.py: Python server for managing client connections

Usage
-----
1. Build the client:
   make

2. Start the server:
   make serve

3. Run the client to connect to the server:
   make run ARGS="<server_ip> <port>" 

Alternatively, you can run the client directly:
   ./shadow <server_ip> <port>

Configuration
-------------
Edit server.py to configure:
- Listening port
- Allowed connections
- Logging preferences

Edit shadow.c to configure:
- Default server address
- Default port
- Connection timeout
- Encryption keys (if implemented)

Building
--------
The Makefile provides the following targets:
- `make` or `make all`: compile the client
- `make serve`: run the Python server
- `make run ARGS="..."`: run the client with arguments
- `make clean`: remove the compiled binary

To rebuild the client from source:
   make

Or manually:
   gcc shadow.c -o shadow

License
-------
This project is provided for educational and authorized testing purposes only.

Author
------
grisun0 of LazyOwn RedTeam

![Python](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54) ![Shell Script](https://img.shields.io/badge/shell_script-%23121011.svg?style=for-the-badge&logo=gnu-bash&logoColor=white) ![Flask](https://img.shields.io/badge/flask-%23000.svg?style=for-the-badge&logo=flask&logoColor=white) [![License: AGPL v3](https://img.shields.io/badge/License-AGPLv3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/Y8Y2Z73AV)
