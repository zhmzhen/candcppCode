#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
 
const int PORT = 8080;
const int BUFFER_SIZE = 1024;
 
std::mutex output_mutex;
 
bool isExitUDPServerThread = false;
void handle_client(int server_socket) {
    char buffer[BUFFER_SIZE];
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
 
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
 
        // Receive data from the client
        ssize_t bytes_received = recvfrom(server_socket, buffer, BUFFER_SIZE, 0, 
                                          (struct sockaddr*)&client_addr, &client_len);
 
        if (bytes_received < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                // Non-blocking mode - no data available
                if (isExitUDPServerThread) {
                	std::lock_guard<std::mutex> lock(output_mutex);
                	std::cout << "handle_client: isExitUDPServerThread is true and exit now" << std::endl;
			break;
		}
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            } else {
                // An actual error occurred
                std::lock_guard<std::mutex> lock(output_mutex);
                std::cerr << "Error receiving data: " << strerror(errno) << std::endl;
                break;
            }
        }
 
        {
            // Lock output to prevent mixed console output
            std::lock_guard<std::mutex> lock(output_mutex);
            std::cout << "Received: " << buffer << std::endl;
        }
 
        // Send a response back to the client
        const char* response = "Message received!";
        sendto(server_socket, response, strlen(response), 0, (struct sockaddr*)&client_addr, client_len);
    }
}
 
int main() {
    // Create a socket
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        std::cerr << "Failed to create socket: " << strerror(errno) << std::endl;
        return 1;
    }
 
    // Set the socket to non-blocking mode
    int flags = fcntl(server_socket, F_GETFL, 0);
    if (flags < 0 || fcntl(server_socket, F_SETFL, flags | O_NONBLOCK) < 0) {
        std::cerr << "Failed to set non-blocking mode: " << strerror(errno) << std::endl;
        close(server_socket);
        return 1;
    }
 
    // Bind the socket to a port
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
 
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket: " << strerror(errno) << std::endl;
        close(server_socket);
        return 1;
    }
 
    std::cout << "Server is running on port " << PORT << std::endl;
 
    // Create a thread to handle incoming messages
    std::thread client_handler(handle_client, server_socket);
    for (int i {0}; i < 3; i++) {
    	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "3 s passed and wait for thread " << PORT << std::endl;
    isExitUDPServerThread = true;
    // Wait for the client handler thread to finish (infinite loop until terminated)
    client_handler.join();
    std::cout << "3 s passed and thread is exit " << PORT << std::endl;
 
    // Close the socket
    close(server_socket);
 
    return 0;
}
