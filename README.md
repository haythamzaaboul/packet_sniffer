Simple Linux Packet Sniffer

A basic network packet sniffer written in C for Linux systems. This utility uses raw sockets to capture all network traffic visible to the host interface and parses the Ethernet (Layer 2) and IP (Layer 3) headers.

Description

This program creates a raw socket (AF_PACKET, SOCK_RAW) to intercept all incoming and outgoing frames (ETH_P_ALL). It then manually parses the raw binary data by casting standard Linux protocol structures over the buffer.

It currently extracts and displays:

Ethernet Header: Source MAC, Destination MAC, and Protocol type.

IP Header: Version, IHL, TOS, Total Length, ID, TTL, Protocol (TCP/UDP/Other), Checksum, Source IP, and Destination IP.

Prerequisites

Operating System: Linux (relies on <linux/if_packet.h> and standard Linux kernel network structures).

Permissions: Root privileges (required to open a SOCK_RAW socket).

Compiler: GCC or Clang.

Compilation

Save the code to a file (e.g., sniffer.c) and compile it using gcc:

gcc -o sniffer sniffer.c


Usage

Because raw sockets require elevated privileges to access the network interface directly, you must run the resulting executable with sudo:

sudo ./sniffer


To stop the sniffer, use Ctrl+C.

Output Example

$$$$$$$$$$$$$$$$$$$$$PACKET RECEIVBED$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

Ethernet Header
	|-Source Address : 00-0C-29-XX-XX-XX
	|-Destination Address : 00-50-56-XX-XX-XX
	|-Protocol : 8
	|-Version : 4

IP Header
	|-Internet Header Length : 20 Bytes
	|-Type Of Service : 0
	|-Total Length : 84 Bytes
	|-Identification : 54321
	|-Time To Live : 64
	|-Protocol : 1 (ICMP)
	|-Header Checksum : 12345
	|-Source IP : 192.168.1.5
	|-Destination IP : 8.8.8.8


Disclaimer

This tool is intended for educational and testing purposes only. Ensure you have permission to capture traffic on the network you are testing.
