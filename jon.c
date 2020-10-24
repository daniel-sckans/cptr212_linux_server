#include <stdio.h>
#include <string.h>
#include "server.h"

void jon(FILE* socket_stream, char uri[128]){
 
    char* response_payload = "<!DOCTYPE html><html><head><title>Test Server</title></head><body><style>* { background-color: #00f; }</style><h1>Headline!</h1><script>document.querySelector('h1').innerText = 'Hello Welcome to Jon's Webpage !';</script></body></html>"; 
    fprintf(socket_stream, "HTTP/1.1 200 OK"); 
    fprintf(socket_stream, "Content-length: %lu\n", strlen(response_payload)); 
    fprintf(socket_stream, "\n"); 

    // This is the body of our response.  
    fprintf(socket_stream, "%s", response_payload); 
    fflush(socket_stream); 

}
