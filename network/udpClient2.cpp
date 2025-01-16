#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <error.h>
#include <sys/time.h>
#include <sys/poll.h>
 
//
std::string message = ":method:GET,:path:tap/";
#define SERVER_PORT 8089
#define BUFFER_SIZE 1024
enum class IPVersion {
	IPV_NONE,
	IPV_4,
	IPV_6,
};
 
//bool isValidIpAddress(const char* ipAddress) {
IPVersion isValidIpAddress(const char* ipAddress) {
    struct sockaddr_in sa;
    std::cout << "isValidIpAddress: " << ipAddress << std::endl;
    // 尝试将字符串形式的IP地址转换为二进制形式
    //try IPv4 firstly
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    if (result > 0) {
        std::cout << "isValidIpAddress: ipv4" << std::endl;
        return IPVersion::IPV_4;
    }
    result = inet_pton(AF_INET6, ipAddress, &(sa.sin_addr));
    if (result > 0) {
        std::cout << "isValidIpAddress: ipv6" << std::endl;
        return IPVersion::IPV_6;
    }
    return IPVersion::IPV_NONE;
}
 
int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <Server IP Address, sleep sec, send cnt>" << std::endl;
        return EXIT_FAILURE;
    }
 
   std::cout << "Usage: argc =" << argc << std::endl;
   std::cout << "Usage: arg2 =" << argv[2] << std::endl;
   std::cout << "Usage: arg3 =" << argv[3] << std::endl;
    const char* serverIpAddress = argv[1];
 
    // 检查IP地址的合法性
    if (isValidIpAddress(serverIpAddress) == IPVersion::IPV_NONE) {
        std::cout << "Invalid IP address: " << serverIpAddress << std::endl;
        return EXIT_FAILURE;
    }
 
    int sockfd;
    struct sockaddr_in server_addr;
    //char buffer[BUFFER_SIZE];
    //socklen_t addr_len = sizeof(server_addr);
 
    // 创建 socketd
    struct timeval start_t, end_t;
    gettimeofday(&start_t, NULL);
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cout << "Socket creation failed" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Socket creation fd:"<< sockfd << std::endl;
    gettimeofday(&end_t, NULL);
    long duration_t = (end_t.tv_sec - start_t.tv_sec) * 1000 * 1000 + end_t.tv_usec - start_t.tv_usec;
    std::cout << " the socket duration_t:" << duration_t << std::endl;
 
    // 设置 socket 为非阻塞模式
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags < 0) {
        std::cout << "fcntl F_GETFL failed" << std::endl;
        close(sockfd);
        return EXIT_FAILURE;
    }
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) < 0) {
        std::cout << "fcntl F_SETFL failed" << std::endl;
        close(sockfd);
        return EXIT_FAILURE;
    }
 
   //send buff
   int sendbuffsize =128;
   if (setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sendbuffsize, sizeof(sendbuffsize)) < 0)
   {
      std::cout << " failed to set sendbufsize " << std::endl;
   }
   socklen_t optlen = sizeof(sendbuffsize);
   if (getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sendbuffsize, &optlen) < 0)
   {
      std::cout << " failed to get sendbufsize " << std::endl;
   }
  std::cout << " the send buff size: " << sendbuffsize << std::endl;
  std::cout << " the send buff size: " << sendbuffsize/1024 << "K" << std::endl;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, serverIpAddress, &server_addr.sin_addr) <= 0) {
        std::cout << "Invalid address/ Address not supported" << std::endl;
        close(sockfd);
        return EXIT_FAILURE;
    }
 
    // 发送消息到服务器
    //std::string message = "Hello, Server!";
    int sc = atoi(argv[2]);
    if (sc == 0) sc = 1;
    for (int i=0; i < sc ; i++) {
    int ret = sendto(sockfd, message.c_str(), message.length(), 0,
      (const struct sockaddr*)&server_addr, sizeof(server_addr));
    if ( ret < 0) {
        std::cout << "\tsent to server FAILURE: ret =" << ret <<"errno=" << errno << ">:errString:(" << strerror(errno) << ")" << std::endl;
        if (errno == EWOULDBLOCK) {
            std::cout << "ERROR: EWOULDBLOCK, Send would block, try again later, errno=" << errno << ">:errString:(" << strerror(errno) << ")" << std::endl;
        } else {
            std::cout << "ERROR: other, Send failed, errno=" << errno << ">:errString:(" << strerror(errno) << ")" << std::endl;
            close(sockfd);
            return EXIT_FAILURE;
        }
    } else {
        std::cout << "\tsent to server SUCC: ret=" << ret <<" errno=" << errno << ">:errString:(" << strerror(errno) << ")" << std::endl;
        //std::cout << "Message sent to server: " << message << std::endl;
    }
    }
 
   std::cout << "Main: sleep a while" << std::endl;
   //ms, 0m, 20s
   int ss = atoi(argv[3]);
   if (ss == 0) ss = 1;
   poll(NULL,0,ss*1000);
    // 关闭 socket
    gettimeofday(&start_t, NULL);
    close(sockfd);
    gettimeofday(&end_t, NULL);
    duration_t = (end_t.tv_sec - start_t.tv_sec) * 1000 * 1000 + end_t.tv_usec - start_t.tv_usec;
    std::cout << " the close duration_t:" << duration_t << std::endl;
    return EXIT_SUCCESS;
}
