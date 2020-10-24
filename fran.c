#include <stdio.h>
#include <string.h>
#include "server.h"

void fran(FILE* socket_stream, char uri[148]) {
    char* response_payload = "<!DOCTYPE html><html><head><title>Server</title></head><body><h1><i>About ZORO</i></h1><p>Zoro is the greatest swore man to ever grace the anime world.</p></body></html>";

    fprintf(socket_stream, "HTTP/1.1 200 OK"); 
    fprintf(socket_stream, "Content-length: %lu\n", strlen(response_payload)); 
    fprintf(socket_stream, "\n"); 

    // This is the body of our response.  
    fprintf(socket_stream, "%s", response_payload); 
    fflush(socket_stream);

}
