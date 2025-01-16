#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <error.h>
#include <sys/time.h>
 
std::string message = ":method:GET,:path:tap/";
//std::string message = "HelloStart012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789HelloEnd";
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
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <Server IP Address>" << std::endl;
        return EXIT_FAILURE;
    }
 
    const char* serverIpAddress = argv[1];
 
    // 检查IP地址的合法性
    if (isValidIpAddress(serverIpAddress) == IPVersion::IPV_NONE) {
        std::cout << "Invalid IP address: " << serverIpAddress << std::endl;
        return EXIT_FAILURE;
    }
 
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(server_addr);
 
    // 创建 socketd
    struct timeval start_t, end_t;
    gettimeofday(&start_t, NULL);
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cout << "Socket creation failed" << std::endl;
        return EXIT_FAILURE;
    }
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
    if (sendto(sockfd, message.c_str(), message.length(), 0, 
               (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cout << "\tsent to server FAILURE: " << errno << ">:errString:(" << strerror(errno) << ")" << std::endl;
        if (errno == EWOULDBLOCK) {
            std::cout << "Send would block, try again later, errno=" << errno << ">:errString:(" << strerror(errno) << ")" << std::endl;
        } else {
            std::cout << "Send to server failed" << std::endl;
            close(sockfd);
            return EXIT_FAILURE;
        }
    } else {
        std::cout << "\tsent to server SUCC: " << errno << ">:errString:(" << strerror(errno) << ")" << std::endl;
        std::cout << "Message sent to server: " << message << std::endl;
    }
 
    // 接收来自服务器的响应
    int cnt = 1000;
    while (true) {
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, 
                     (struct sockaddr*)&server_addr, &addr_len);
    if (n < 0) {
        if (errno == EWOULDBLOCK) {
            //std::cout << "Receive would block, try again later, cnt=" << cnt << " , errno=" << errno << ">:errString:(" << strerror(errno) << ")" << std::endl;
            if ( cnt > 0) {
                cnt--;
            }
            else
            {
                continue;
            }
        } else {
            std::cout << "Receive from server failed" << std::endl;
            close(sockfd);
            return EXIT_FAILURE;
        }
    } else {
        buffer[n] = '\0';
        std::cout << "Server response: " << buffer << std::endl;
        break;
    }
    }
 
    // 关闭 socket
    gettimeofday(&start_t, NULL);
    close(sockfd);
    gettimeofday(&end_t, NULL);
    duration_t = (end_t.tv_sec - start_t.tv_sec) * 1000 * 1000 + end_t.tv_usec - start_t.tv_usec;
    std::cout << " the close duration_t:" << duration_t << std::endl;
    return EXIT_SUCCESS;
}
