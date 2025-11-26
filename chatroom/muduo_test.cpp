#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Logging.h>
#include <iostream>

using namespace muduo;
using namespace muduo::net;

// 客户端连接回调
void onConnection(const TcpConnectionPtr& conn) {
    LOG_INFO << "Connection " << conn->peerAddress().toIpPort() 
             << " -> " << conn->localAddress().toIpPort() 
             << " is " << (conn->connected() ? "UP" : "DOWN");
}

// 客户端数据回调（回显数据）
void onMessage(const TcpConnectionPtr& conn,
               Buffer* buf,
               Timestamp time) {
    // 读取客户端数据
    std::string msg(buf->retrieveAllAsString());
    LOG_INFO << conn->peerAddress().toIpPort() << " send: " << msg;
    // 回显给客户端
    conn->send(msg);
}

int main() {
    LOG_INFO << "Server start...";
    
    // 事件循环（Reactor 核心）
    EventLoop loop;
    // 监听 0.0.0.0:8888
    InetAddress listenAddr(8888);
    TcpServer server(&loop, listenAddr, "EchoServer");
    
    // 设置回调函数
    server.setConnectionCallback(onConnection);
    server.setMessageCallback(onMessage);
    // 启动服务器（监听并接受连接）
    server.start();
    // 运行事件循环
    loop.loop();
    
    return 0;
}