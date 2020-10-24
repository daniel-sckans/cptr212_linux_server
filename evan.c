#include <stdio.h>
#include <string.h>
#include "server.h"

void evan(FILE* socket_stream, char uri[128]) {
    char* response_payload = "<!DOCTYPE html><html><head><title>Evan's not-default page</title></head><body><style>* { background-color: #00f; }</style><h1>Headline!</h1><p>I'm creating a link to<a href=\"https://www.mozilla.org/en-US/\">the Mozilla homepage</a>.</p><script>document.querySelector('h1').innerText = 'Hello from JavaScript!';</script></body></html>"; 
    fprintf(socket_stream, "HTTP/1.1 200 OK"); 
    fprintf(socket_stream, "Content-length: %lu\n", strlen(response_payload)); 
    fprintf(socket_stream, "\n"); 

    fprintf(socket_stream, "%s", response_payload); 
    fflush(socket_stream); 
}