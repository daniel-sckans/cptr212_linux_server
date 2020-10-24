#include <stdio.h>
#include <string.h>
#include "server.h"

void skyler(FILE* socket_stream, char uri[128]){
    char* createpage;
    createpage = "<html><body>skylers_page</body></html>";
    return createpage;
}
