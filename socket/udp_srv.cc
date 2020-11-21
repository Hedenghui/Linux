#include<iostream>
#include<string>
#include"udpsocket.hpp"

#define CHECK_RET(q) if((q)==false){return false;}
int main(int argc,char *argv[])
{
  if(argc!=3)
  {
    std::cout<<"Usage: ./udp_srv ip port\n";
    return -1;
  }
  uint16_t port =std::stoi(argv[2]);
  std::string ip=argv[1];

  UdpSocket srv_sock;

  //创建
 // if(srv_sock.Socket()==false)
 // {
 //   return false;
 // }
  CHECK_RET(srv_sock.Socket());
  CHECK_RET(srv_sock.Bind(ip,port));
  while(1)
  {
    std::string buf;
    std::string peer_ip;
    uint16_t peer_port;
    CHECK_RET(srv_sock.Recv(&buf,&peer_ip,&peer_port));
    std::cout<<"client["<<peer_ip<<":"<<peer_port<<"] say:"<<buf<<std::endl;
    //发送
    buf.clear();
    std::cout<<"server say: ";
    std::cin>>buf;
    CHECK_RET(srv_sock.Send(buf,peer_ip,peer_port));

  }
  srv_sock.Close();
}
