#include "httplib.h"
#include "GenericApi.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    std::string webRoot = argc > 1 ? argv[1] : "web";
    int port = argc > 2 ? std::stoi(argv[2]) : 8080;

    httplib::Server server;
    if (!server.set_mount_point("/", webRoot))
    {
        std::cerr << "Web folder not found: " << webRoot << std::endl;
        return 1;
    }

    registerGenericApi(server);

    std::cout << "TIVIDY running at http://localhost:" << port << std::endl;
    if (!server.listen("0.0.0.0", port))
    {
        std::cerr << "Could not start on port " << port << " (is it already in use?)" << std::endl;
        return 1;
    }
    return 0;
}
