#include "socket.hh"
#include "util.hh"

#include <cstdlib>
#include <iostream>

using namespace std;

void get_URL(const string &host, const string &path) {
    Address addr( host, "http" );                    // 从hostname和service构造Address，address即服务器描述
    TCPSocket socket;                                // 创建套接字
    socket.connect( addr );                          // 通过套接字连接到服务器
    socket.write( "GET " + path + " HTTP/1.1\r\n" ); // 通过套接字发送http请求
    socket.write( "HOST: " + host + "\r\n" );
    socket.write( "Connection: close\r\n" );
    socket.write( "\r\n" );
    while ( !socket.eof() ) { // 循环读取socket文件直到文件末尾
        string buffer;
        socket.read( buffer );
        cout << buffer;
    }

    cerr << "Function called: get_URL(" << host << ", " << path << ").\n";
    cerr << "Warning: get_URL() has not been implemented yet.\n";
}

int main(int argc, char *argv[]) {
    try {
        if (argc <= 0) {
            abort();  // For sticklers: don't try to access argv[0] if argc <= 0.
        }

        // The program takes two command-line arguments: the hostname and "path" part of the URL.
        // Print the usage message unless there are these two arguments (plus the program name
        // itself, so arg count = 3 in total).
        if (argc != 3) {
            cerr << "Usage: " << argv[0] << " HOST PATH\n";
            cerr << "\tExample: " << argv[0] << " stanford.edu /class/cs144\n";
            return EXIT_FAILURE;
        }

        // Get the command-line arguments.
        const string host = argv[1];
        const string path = argv[2];

        // Call the student-written function.
        get_URL(host, path);
    } catch (const exception &e) {
        cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
