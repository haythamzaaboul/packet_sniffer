# simple_sniffer — Minimal Raw Socket Packet Capturer (C)

A basic, educational packet sniffer for Linux using raw sockets.
Design goals: **simplicity**, **no dependencies**, **direct kernel interaction**—uses standard Linux headers (`<linux/if_packet.h>`, `<netinet/ip.h>`) instead of libpcap.

---

## Features

- **Raw Capture**: Uses `PF_PACKET` / `SOCK_RAW` to see all Ethernet frames (promiscuous mode).
- **Ethernet (L2)**: Extracts destination/source MAC addresses and EtherType.
- **IPv4 (L3)**: Extracts Version, IHL, Total Length, TTL, Protocol, and src/dst IP addresses.
- **Protocol Identification**: Identifies basic L4 protocols (TCP, UDP) via generic helper.
- **Loud Output**: Immediate console printing of captured header details.

---

## Why this sniffer?

Typical packet capture tools rely on heavy libraries like `libpcap`.

This project demonstrates:
- **Direct Socket Access**: How to open `AF_PACKET` sockets in standard C.
- **Manual Parsing**: How to overlay standard Linux structs (`struct ethhdr`, `struct iphdr`) onto raw memory buffers.
- **Kernel Structures**: Direct usage of standard Linux networking headers.

---




## Project Layout

```text
.
├── sniffer.c           # Complete implementation
└── README.md           # This documentation
```

## Build

```text
gcc sniffer.c -o sniffer
sudo ./sniffer

```


## Expected output

```text


$$$$$$$$$$$$$$$$$$$$$PACKET RECEIVBED$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

Ethernet Header
    |-Source Address : 00-0C-29-4F-8E-35
    |-Destination Address : 00-50-56-C0-00-08
    |-Protocol : 8
    |-Version : 4

IP Header
    |-Internet Header Length : 20 Bytes
    |-Type Of Service : 0
    |-Total Length : 84 Bytes
    |-Identification : 29403



    |-Time To Live : 64
    |-Protocol : 1 (ICMP)
    |-Header Checksum : 45779
    |-Source IP : 192.168.1.20
    |-Destination IP : 8.8.8.8
```

## EDesign Notes & Limitations


- **Linux Only**: Relies on Linux-specific <linux/if_packet.h> and raw socket behavior.

- **IPv4 Assumption**: Currently assumes incoming frames are IPv4 for simplicity; does not yet filter for ARP or IPv6 before casting the IP header.

- **Blocking I/O**: Uses a simple recvfrom loop; will block until traffic arrives.

- **Buffer Size**: Uses a static 65536 byte buffer to ensure capture of full MTU frames (including loopback).


