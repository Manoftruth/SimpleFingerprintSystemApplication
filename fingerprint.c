#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <ifaddrs.h>
int main()
{
        int i;               //opens the socket
        struct ifaddrs *ifap, *ifa;
        struct sockaddr_in *addri;
        int j;
        char *IPaddr;
        char *eth0="eth0";
        struct ifreq macBuff;
        unsigned char fingerprint;
        j=getifaddrs(&ifap);
        i = socket(PF_INET, SOCK_DGRAM, 0);
        memset(&macBuff, 0x00, sizeof(macBuff));//sets the mac address to macBuff
        strcpy(macBuff.ifr_name, "eth0");
        ioctl(i, SIOCGIFHWADDR,&macBuff);//reads the mac address
        close(i);
        for (i=0;i<6;i++){
                 fingerprint =((macBuff.ifr_hwaddr.sa_data[i]<<2)+0x40); //sets fingerprint
                for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
                        addri =(struct sockaddr_in *) ifa->ifa_addr;//grabs ip
                        if( strcmp(ifa->ifa_name,eth0)==0){
                                if(ifa->ifa_next!=NULL){
                                        IPaddr =inet_ntoa(addri->sin_addr);//sets ip address 
                                        fingerprint= fingerprint +(unsigned char)IPaddr; //adds them
                                        printf("%x", fingerprint); //prints unique id
                                }
                        }
                }
        }
        freeifaddrs(ifap);
        printf("\n");
        return 0;
}