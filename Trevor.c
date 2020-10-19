#include <stdio.h>
#include <string.h>
#include "server.h"

void Trevor(FILE* socket_stream, char uri[128])
{
    //char* response_payload = "<!DOCTYPE html><html><head><title>Trevor's Page</title></head><body><style>* { background-color: #00f; }</style><h1>Headline!</h1><script>document.querySelector('h1').innerText = 'Hello from Trevor!';</script></body></html>"; 
    char* response_payload = "<h1>THIS IS TREVOR</h1>";
    char* response_payload = "\n";
    char* response_payload = "<h2>Quick Things About him</h2>";
    char* response_payload = "<ul><li>Is from Texas</li><li>Plays soccer for SouthWestern</li><li>Is a junior</li><li>likes pizza</li><li>likes dark colors</li></ul>" 

    fprintf(socket_stream, "HTTP/1.1 200 OK"); 
    fprintf(socket_stream, "Content-length: %lu\n", strlen(response_payload)); 
    fprintf(socket_stream, "\n"); 

    // This is the body of our response.  
    fprintf(socket_stream, "%s", response_payload); 
    fflush(socket_stream); 
}
