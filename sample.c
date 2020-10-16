#include <stdio.h>
#include <string.h>
#include "server.h"

void sample(FILE* socket_stream, char uri[128]) {

    printf("URI: %s\n", uri); 

    if(strstr(uri, "bb.jpg") != NULL) {
        printf("Image request: \n"); 

        FILE* img_file = fopen("assets/bb.jpg", "r"); 
        fseek(img_file, 0, SEEK_END); 
        int img_file_length = ftell(img_file); 
        fseek(img_file, 0, SEEK_SET); 

        fprintf(socket_stream, "HTTP/1.1 200 OK"); 
        fprintf(socket_stream, "Content-length: %lu\n", img_file_length); 
        fprintf(socket_stream, "\n"); 

        while(!feof(img_file)) {
            fputc(fgetc(img_file), socket_stream); 
        }
        fflush(socket_stream); 

        return; 
    }    

    char* response_payload = "<!DOCTYPE html><html><head><title>Test Server</title></head><body><style>* { background-color: #0f0; }</style><h1>Sample hello</h1><img src='sample/bb.jpg' width='500'></body></html>"; 
    fprintf(socket_stream, "HTTP/1.1 200 OK"); 
    fprintf(socket_stream, "Content-length: %lu\n", strlen(response_payload)); 
    fprintf(socket_stream, "\n"); 

    // This is the body of our response.  
    fprintf(socket_stream, "%s", response_payload); 
    fflush(socket_stream); 

}