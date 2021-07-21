#include <stdio.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>

int main(){

int lfd=socket(AF_INET,SOCK_STREAM,0);

struct sockaddr_in svr,cli;
socklen_t clilen=sizeof(cli);
memset(&svr,0x00,sizeof(svr));
svr.sin_family=AF_INET;
svr.sin_port=htons(8888);
svr.sin_addr.s_addr=0;

int opt=1;
setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

bind(lfd,(struct sockaddr*)&svr,sizeof(svr));

listen(lfd,128);

//Build a tree
int epfd=epoll_create(1);

//Hang the tree
struct epoll_event ev,evs[128];
ev.data.fd=lfd;
ev.events=EPOLLIN;
epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ev);

// loop waiting
while(1){
    
    int s=epoll_wait(epfd,evs,1024,-1);
    
    for(int i=0;i<s;i++){
    //Connection event
        if(evs[i].events & EPOLLIN){
            if(evs[i].data.fd==lfd){
                int cfd=accept(lfd,(struct sockaddr *)&cli,&clilen);
                // If successful, send the read event to the tree
                if(cfd>0){
                    ev.data.fd=cfd;
                    ev.events=EPOLLIN;
                    epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&ev);
                }
            }
            //Read event
            else{
                char buf[256]={0};
                int ret=read(evs[i].data.fd,buf,sizeof(buf));
                if(ret>0){
                    write(evs[i].data.fd,buf,sizeof(buf));
                    write(STDOUT_FILENO,buf,ret);
                }
                else if(ret<=0){
                    ev.data.fd=evs[i].data.fd;
                    ev.events=EPOLLIN;
                    epoll_ctl(epfd,EPOLL_CTL_DEL,ev.data.fd,&ev);
                    close(ev.data.fd);
                    printf("exit successful!!!");
                }
            }
        }
    }
	}
close(epfd);
close(lfd);
return 0;
}

