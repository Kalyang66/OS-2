#include <iostream>
#include <fstream>
using namespace std;
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <netinet/in.h>
#include <sys/stat.h>
#include <filesystem>

void error(const char * message){
    perror(message);
    exit(EXIT_FAILURE);
}
//helper function
string Read(const string& filename){
    string path = "Repository/" + filename;
    ifstream file(path);
    if (file.is_open()) {
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        cout << "Found the file: " << filename << endl; 
        return content;
    } else {
        cout << "Could not find the file: " << filename + '\n';
        return "File not found " + filename + '\n';
    }
}

int main(){
    //layout same as client
    cout << "Kalyan Gautam PID: 2134209" << endl;
    cout << "OS Assignment 2" << endl; 
    cout << "********************************" << endl;
    cout << "How to run: (p.s I am on mac so I just opened two terminal but you can use VS code)" << endl;
    cout << "1: Open two differnt terminals after downlaoding the .cpp files" << endl;
    cout << "2: first complie the server using g++ Kalyan_Gautam_Server -o server in one of the terminals" << endl;
    cout << "3: complie the client using g++ Kalyan_Gautam_Client -o client in the other terminals" << endl;
    cout << "4: run ./server in the first terminal you used for server" << endl;
    cout << "5: run ./client in the second ternimal" << endl;
    cout << "6: You can go from there and ask for as many files you want as long as you want. It will return the content or say is does not exist." << endl;
    cout << "********************************" << endl;
    cout << endl; 
    //socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0){
        error("error opening socket");
    }

    //address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8000);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // bind and listen
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, 5);
    //connect by accepting client
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    //recvie
    while(true){
        char fileName[256];
        ssize_t n = recv(clientSocket, fileName, sizeof(fileName), 0);
        //error handle 
        if (n < 0){
            error("error reading from sockot");
        } 

        //process file
        string fileCont = Read(fileName);
        n = send(clientSocket, fileCont.c_str(), fileCont.length(), 0);
        }
        close(serverSocket);

        return 0; 
}