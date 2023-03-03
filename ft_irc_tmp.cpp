#include "Client.hpp"
#include "Server.hpp"

int main(int argc, char **argv) {

    if (argc != 2)
    {
        std::cout << "Port number needed." << std::endl;
        return (-1);
    }

    Client  client;
    Server  server;

    //server socket

    server._name = argv[0];
    client._port = std::strtol(argv[1], NULL, 10);

    server._socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server._socket == -1)
    {
        std::cerr << "Can't create socket." << std::endl;
        return (-2);
    }

    server._sockaddr.sin_family = AF_INET;
    server._sockaddr.sin_port = htons(client._port);
    server._sockaddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server._socket, (sockaddr*)&server._sockaddr, sizeof(server._sockaddr)) == -1)
    {
        std::cerr << "Can't bind to IP/port." << std::endl;
        return (-3);
    }

    if (listen(server._socket, SOMAXCONN) == -1)
    {
        std::cerr << "Can't listen." << std::endl;
        return (-4);
    }



    //client socket
    
    client._socklen = sizeof(client._sockaddr);

    client._socket = accept(server._socket, (sockaddr*)&client._sockaddr, &client._socklen);

    if (client._socket == -1)
    {
        std::cerr << "Problem connecting client to server." << std::endl;
        return (-5);
    }

    close(server._socket);

    memset(client._host, 0, NI_MAXHOST);
    memset(server._svc, 0, NI_MAXSERV);

    int info = getnameinfo((sockaddr*)&client._sockaddr, client._socklen, client._host, NI_MAXHOST, server._svc, NI_MAXSERV, 0);

    if (info)
        std::cout << client._host << " connected on " << server._svc << std::endl;
    else
        std::cout << inet_ntoa(client._sockaddr.sin_addr) << " connected on " << ntohs(client._sockaddr.sin_port) << std::endl;

    char    buf[4096];

    std::string welcome1(":server 001 <nick> :Welcome to the <network> Network, ");

    std::string welcome2("<nick>[!<user>@<host>]");

    std::string welcome_final = welcome1 + welcome2 + "\n";

    send(client._socket, welcome_final.data(), 79, 0);
    // send(client_socket, ":server 001 <nick> :Welcome to the <network> Network, <nick>[!<user>@<host>]\n", 79, 0);
    // send(client_socket, ":server 002 <nick> :Your host is <servername>, running version <version>\n", 75, 0);
    // send(client_socket, ":server 003 <nick> :This server was created <datetime>\n", 57, 0);
    // send(client25_socket, ":server 004 <nick> <servername> <version> <available umodes> <available cmodes> [<cmodes with param>]\n", 104, 0);
    // send(client_socket, ":server 372 <nick> <line>\n", 28, 0);
    // send(client_socket, ":server 375 <nick> <info>\n", 28, 0);
    // send(client_socket, ":server 376 <nick> :End of /MOTD command\n", 43, 0);
    // send(client_socket, ":server 422 <nick> :MOTD File is missing\n", 43, 0);

    while (true)
    {
        memset(buf, 0, 4096);

        int bytes_read = recv(client._socket, buf, 4096, 0);
        
        if (bytes_read == -1)
        {
            std::cerr << "Problem with recv()." << std::endl;
            break;
        }
        if (bytes_read == 0)
        {
            std::cerr << "Client disconnected." << std::endl;
            break;
        }
    
        if (bytes_read > 0)
            std::cout << std::string(buf, 0, bytes_read) << std::endl;

        // send(client_socket, buf, bytes_read + 1, 0);
    }

    close(client._socket);

    return (0);
}