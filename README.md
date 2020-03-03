# C Server Test
The purpose of this repository is to experiment with using C for backend web development. This repo currently has two separate tests.
1. Setup with live TCP server and client. The test was designed for use in a Windows environment, but (hopefully :pray:) should work on Linux and Mac environments too.
2. Setup with basic HTML webpage and live local server. The local server is designed to serve a web page to the client in a browser when requested, and to stop the client from requesting any more data when finished.

# Requirements
* C Compiler (GNU C Compiler, MinGW, etc.)
* Terminal (Command Line Interface, Powershell, etc.)
* Web Browser

# Usage
### TCP Server and Client
This is a simple test consisting of a TCP server and client designed to interact with each other. The socket address has been configured to the localhost IP and is running on port 9002.
1. Compile tcp_server.c and tcp_client.c
2. In the terminal, execute the compiled tcp_server
3. In a separate terminal, execute the compiled tcp_client
4. A successful response should show "Connection established" in the server terminal, and the string "Heya. I got your request, but now I gotta go." in the client terminal.
5. tcp_server will remain open after successfully completing the client's connection request. Close the server with Ctrl+C

### Local Web Server
This is a simple test which consists only of a TCP web server and an html page. The socket address has been configured to listen to any available interface on port 8080.
1. Compile http_server.c
2. In the terminal, execute the compiled http_server to start the server
3. In your web browser of choice, navigate to "localhost:8080"
4. A simple (read: a really bad) webpage should render in the browser