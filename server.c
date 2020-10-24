
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

// Headers we'll use for networking.  
#include <netinet/in.h>
#include <sys/socket.h>

// Our local header.  
#include "server.h"

int main(int argc, char** argv) {

    // Step one: create a socket.  
    // In our case, a socket will be a lot like a stream.  
    // Just like stdin, stdout, and stderr are referred to by ints (1, 2, and 3), sockets are referred to by ints as well.  
    // Just like streams, we'll read and write from them; in this case, what we write can be made available over the internet.  
    char const*const socket_location = "/tmp/inet_sock"; 
    unlink(socket_location); 
    int server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0); 
    if(server_socket_descriptor == -1) {
        fprintf(stderr, "Unable to create socket descriptor: %s\n", strerror(errno)); 
        return 1; 
    }
    int socket_option_value = 1; 
    setsockopt(server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, (const void*)&socket_option_value, sizeof(int)); 
    
    // These are required options to set up our socket.  
    // Of note is the port: your server, when it's running locally, will be available in your internet browser at "http://localhost:8000", where 8000 is the "socket_address.sin_port". 
    struct sockaddr_in socket_address; 
    memset(&socket_address, 0, sizeof(socket_address)); 
    socket_address.sin_family = AF_INET; 
    socket_address.sin_addr.s_addr = INADDR_ANY; 
    socket_address.sin_port = htons((unsigned short int)8000); 
    int result = bind(server_socket_descriptor, (struct sockaddr*)&socket_address, sizeof(socket_address)); 
    if(result == -1) {
        close(server_socket_descriptor); 
        fprintf(stderr, "Error binding socket: %s\n", strerror(errno)); 
        return 2; 
    }

    // Set your server to listen for incoming connections.  
    // The number 10 refers to the number of waiting connections (people who have typed your web address into their browser).  
    result = listen(server_socket_descriptor, 10); 
    if(result == -1) {
        close(server_socket_descriptor); 
        fprintf(stderr, "Error listening to socket descriptor for connections: %s\n", strerror(errno)); 
        return 3; 
    }

    // Receive requests until error.  
    while(1) {
        fprintf(stdout, "\n"); 
        fprintf(stdout, "Ready to receive a new connection\n"); 

        // Got an incoming request.  
        // This is now the client's socket descriptor, but the same rules apply (we'll treat it as a stream).  
        int client_socket_descriptor = accept(server_socket_descriptor, NULL, NULL); 
        if(result == -1) {
            close(server_socket_descriptor); 
            fprintf(stderr, "Error accepting requests: %s\n", strerror(errno)); 
            return 4; 
        }

        // Here we'll set the request open for reading and writing to, much like a stream or file.  
        FILE* socket_stream = fdopen(client_socket_descriptor, "r+"); 
        if(!socket_stream) {
            close(server_socket_descriptor); 
            close(client_socket_descriptor); 
            fprintf(stderr, "Unable to open request as stream: %s\n", strerror(errno)); 
            return 5; 
        }

        // We'll read and print out the entire request.  
        // http requests (those from the internet) are always terminated by a new line ("\r\n").  
        char _method[32]; 
        char _uri[128]; 
        char _version[64]; 
        fscanf(socket_stream, "%s %s %s\n", _method, _uri, _version); 
        fprintf(stdout, "%s %s %s\n", _method, _uri, _version); 

        char buffer[256] = {0}; 
        do {
            fgets(buffer, 256, socket_stream); 
            fprintf(stdout, "REQ >> %s", buffer); 
        } while(buffer[0] != '\r'); 
        
        if(strstr(_uri + 1, "akito") == _uri + 1) {
            akito(socket_stream, _uri); 
        } else if(strstr(_uri + 1, "fran") == _uri + 1) {
            fran(socket_stream, _uri); 
        } else if(strstr(_uri + 1, "jon") == _uri + 1) {
            jon(socket_stream, _uri); 
        } else if(strstr(_uri + 1, "trevor") == _uri + 1) {
            Trevor(socket_stream, _uri); 
        } else {

            // Writing a default response; this is the response when no other page is matched.  
            // In this minimal response, we'll only include the basics.  
            char* default_response = "<!DOCTYPE html><html><head><title>Test Server</title></head>"
                "<body>"
                    "<style>* { background-color: #00f; }</style>"
                    "<h1>Welcome to the Webpage!</h1>"
                    "<script>document.querySelector('h1').innerText = 'Hello Welcome to Jon's Webpage!';</script>"
                "</body>"
            "</html>"; 
                       
            fprintf(socket_stream, "HTTP/1.1 200 OK"); 
            fprintf(socket_stream, "Content-length: %lu\n", strlen(default_response)); 
            fprintf(socket_stream, "\n"); 

            // This is the body of our response.  
            fprintf(socket_stream, "%s", default_response); 
            fflush(socket_stream); 
        } 

        close(client_socket_descriptor); 
    }

    return EXIT_SUCCESS; 
}