#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
using namespace std;

void error(const char * message){
    perror(message);
    exit(EXIT_FAILURE);
}
//helper function
void Get(int& clientSocket){
    string filename;
    cout << "Please enter the name of the file: " << endl;
    cin >> filename;
    const char * message = filename.c_str();
    ssize_t n = send(clientSocket, message, strlen(message), 0);
    char buffer[4096] = {0};
    n = recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << "File content: " << buffer << endl;
}

int main(){
    //creating socket and address
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8000);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    //connectingto server
    connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    //layout
    cout << endl;
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
    char option;
    //main loop
    do {
        cout << endl;
        cout << "Assignment 2 - Pick a opition" << endl;
        cout << "option 1 - Get file" << endl;
        cout << "option 2 - Exit" << endl;
        cout << "Pick option: " << endl;
        cin >> option;
        switch(option) {
            case '1':
                Get(clientSocket);
                break;
            case '2':
                cout << "You terminated the program" << endl;
                close(clientSocket);
                break; 
            default:
            cout << "Pick option: " << endl;
        }
        } while(option != '2');
        close(clientSocket);
        return 0; 
    }