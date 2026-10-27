#include "httplib.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    std::string webRoot = argc > 1 ? argv[1] : "web";
    int port = 8080;

    httplib::Server server;
    if (!server.set_mount_point("/", webRoot))
    {
        std::cerr << "Web folder not found: " << webRoot << std::endl;
        return 1;
    }

    std::cout << "TIVIDY running at http://localhost:" << port << std::endl;
    server.listen("0.0.0.0", port);
    return 0;
}
