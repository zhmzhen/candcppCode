#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
//#include <functional>
#include <unistd.h>
 
class TapUdpServer {
public:
  bool initUDPServer(void);
  void startUDPServer(void);
  void stopUDPServer(void) { isExitUDPServerThread_ = true; }
  bool isUDPServerStopped(void) { return isExitUDPServerThread_; }
  bool isUDPServerRcvMatchedUDPMsg(void) { return isRcvMatchedUDPMsg_; }
private:
  bool isExitUDPServerThread_ = false;
  const int UDP_PORT_ = 8089;
  const char* UDP_SERVER_IP_ = "127.0.0.1";
  const char* MATCHED_TAP_STR_ = "tap";
  bool isRcvMatchedUDPMsg_ = false;
  const int UDP_SERVER_WAIT_INTERVAL_ = 100;
  //const int UDP_RCV_BUFFER_SIZE_ = 1024;
  //static const int UDP_RCV_BUFFER_SIZE_ = 1024;
  //#define UDP_RCV_BUFFER_SIZE_  1024
  int server_socket_ = -1;
}; 

bool TapUdpServer::initUDPServer() {
  server_socket_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_socket_ < 0) {
    return false;
  }
  int flags = fcntl(server_socket_, F_GETFL, 0);
  if (flags < 0 || fcntl(server_socket_, F_SETFL, flags | O_NONBLOCK) < 0) {
    close(server_socket_);
    return false;
  }
  sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  if (inet_pton(AF_INET, UDP_SERVER_IP_, &server_addr.sin_addr) <= 0) {
    close(server_socket_);
    return false;
  }
  server_addr.sin_port = htons(UDP_PORT_);
  if (bind(server_socket_, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    close(server_socket_);
    return false;
  }
  return true;
}

void TapUdpServer::startUDPServer() {
  const int UDP_RCV_BUFFER_SIZE_ = 1024;
  char buffer[UDP_RCV_BUFFER_SIZE_] = {0};
  sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);
  while (true) {
    memset(buffer, 0, UDP_RCV_BUFFER_SIZE_);
  //  ssize_t bytes_received = recvfrom(server_socket_, buffer, UDP_RCV_BUFFER_SIZE_, 0,
   //   (struct sockaddr*)&client_addr, &client_len);
   ssize_t bytes_received = 0;
    if (bytes_received <= 0) {
      //if (errno == EWOULDBLOCK || errno == EAGAIN) {
      if (true) {
        // Expected return value.
        if (isExitUDPServerThread_) {
std::cout << "\t\t CFXC exit because of stop " << std::endl;
  bytes_received = recvfrom(server_socket_, buffer, UDP_RCV_BUFFER_SIZE_, 0, (struct sockaddr*)&client_addr, &client_len);
    std::string rcv_msg {buffer};
std::cout << "\t\t CFX: exit got the expect messaage:" << buffer << std::endl;
          break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(UDP_SERVER_WAIT_INTERVAL_));
        continue;
      } else {
        // Exit because of other error
        break;
      }
    }
    std::string rcv_msg {buffer};
    if (rcv_msg.find(MATCHED_TAP_STR_) != std::string::npos) {
      isRcvMatchedUDPMsg_ = true;
std::cout << "\t\t CFX: exit got the expect messaage:" << buffer << std::endl;
    }
    // Only expect one UDP message and exit.
    isExitUDPServerThread_ = true;
    break;
  }
  close(server_socket_);
  server_socket_ = -1;
}

int main() {
 
//Create UDPserver
TapUdpServer tap_server;
if (!tap_server.initUDPServer()) {
  std::cout << "Failed to init UDP server" << std::endl;
  return -1;
}

//start server
//std::thread client_handler(std::bind(&tap_server.startUDPServer, &tap_server));
std::thread client_handler([&tap_server] () {
  tap_server.startUDPServer();
});
for (int i {0}; i < 30; i++) {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  if (tap_server.isUDPServerStopped()) {
    break;
  }
}
std::cout << "3 s passed and wait for thread " << std::endl;
// Wait for the client handler thread to finish (infinite loop until terminated)
if (!tap_server.isUDPServerStopped()) {
  std::cout << "UDP server isn't get the message and stop it" << std::endl;
  tap_server.stopUDPServer();
}
client_handler.join();
std::cout << "3 s passed and thread is exit " << std::endl;
return 0;
}
