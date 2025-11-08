#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>   
#include <net/ethernet.h>
#include <linux/if_packet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static const char* ip_proto_name(uint8_t p) {
    switch (p) {
        case IPPROTO_TCP: return "TCP";
        case IPPROTO_UDP: return "UDP";
        default: return "OTHER";
    }
}


int main(void) {
    //creating the RAW socket to accept all packets
	int sock_r = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sock_r < 0) {
		perror("socket");
		return -1;
	};

    //reaceiving these packets in the socket
    unsigned char *buffer = (unsigned char *)malloc(65536);

    while (1){
        memset(buffer, 0, 65536);
        struct sockaddr saddr; 
        int saddr_len = sizeof(saddr);
        int buflen = recvfrom(sock_r, buffer, 65536, 0, &saddr, &saddr_len);
        if(buflen < 0) {
            perror("Recvfrom Error");
            exit(1);
        }

        struct ethhdr *eth = ( struct ethhdr *)(buffer);
        unsigned int iplen; 
        struct iphdr *ip = ( struct iphdr * )(buffer + sizeof(struct ethhdr));
        struct sockaddr_in source, dest;
        memset(&source, 0, sizeof(source));
        source.sin_addr.s_addr = ip->saddr;
        memset(&dest, 0, sizeof(dest));
        dest.sin_addr.s_addr = ip->daddr;



        printf("\n$$$$$$$$$$$$$$$$$$$$$ PACKET RECEIVBED $$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
        printf("\nEthernet Header\n");
        printf("\t|-Source Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",eth->h_source[0],eth->h_source[1],eth->h_source[2],eth->h_source[3],eth->h_source[4],eth->h_source[5]);
        printf("\t|-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5]);
        printf("\t|-Protocol : %d\n", ntohs(eth->h_proto));
        printf("\t|-Version : %d\n",(unsigned int)ip->version);
 
        printf("\nIP Header\n");
        printf("\t|-Internet Header Length : %d Bytes\n",((unsigned int)(ip->ihl))*4);
        printf("\t|-Type Of Service : %d\n",(unsigned int)ip->tos);
        printf("\t|-Total Length : %d Bytes\n",ntohs(ip->tot_len));
        printf("\t|-Identification : %d\n",ntohs(ip->id));
        printf("\t|-Time To Live : %d\n",(unsigned int)ip->ttl);
        printf("\t|-Protocol : %u (%s)\n", ip->protocol, ip_proto_name(ip->protocol));
        printf("\t|-Header Checksum : %d\n",ntohs(ip->check));
        printf("\t|-Source IP : %s\n", inet_ntoa(source.sin_addr));
        printf("\t|-Destination IP : %s\n",inet_ntoa(dest.sin_addr));

    }
    

    close(sock_r);
    return 0;

    
    
}