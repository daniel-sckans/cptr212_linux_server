#include <stdio.h>
#include <string.h>
#include "server.h"

void sample(FILE* socket_stream, char uri[128]) {

    printf("URI: %s\n", uri); 

    char* response_payload = "<!DOCTYPE html><html><head><title>Fran server</title></head><body><style>* { background-color: #FFFF000; }</style><h1><i>Hello World</i></h1></body></html>"; 
    fprintf(socket_stream, "HTTP/1.1 200 OK"); 
    fprintf(socket_stream, "Content-length: %lu\n", strlen(response_payload)); 
    fprintf(socket_stream, "\n"); 

    // This is the body of our response.  
    fprintf(socket_stream, "%s", response_payload); 
    fflush(socket_stream); 

}
