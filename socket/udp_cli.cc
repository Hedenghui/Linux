#include<iostream>
#include<string>
#include"udpsocket.hpp"

#define CHECK_RET(q) if((q)==false){return -1;}

int main(int argc,char *argv[])
{
  if(argc!=3)
  {
    std::cout<<"Usage: ./udp_cli ip port\n";
    return -1;
  }
  std::string srv_ip=argv[1];
  uint16_t srv_port=std::stoi(argv[2]);
  UdpSocket cli_sock;
  CHECK_RET(cli_sock.Socket());
  while(1)
  {
    std::cout<<"client say:";
    std::string buf;
    std::cin>>buf;
    CHECK_RET(cli_sock.Send(buf,srv_ip,srv_port));
    buf.clear();
    CHECK_RET(cli_sock.Recv(&buf,&srv_ip,&srv_port));
    std::cout<<"server say:"<<buf<<std::endl;
  }
  cli_sock.Close();
}
