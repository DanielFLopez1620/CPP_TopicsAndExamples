// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * UNIX DOMAIN SOCKETS: They are sockets that can operate within the same machine, and they can be
 * biderectional (so one can read/write over the same channel), and they are more flexible because
 * they are 'session-aware' and 'message-aware'.
 * 
 * Sockets can be single or multi host and they use more or less the same API  and share concepts,
 * and one is related with how computers networks works. We cnan talk of it in terms of:
 * 
 * - Physical layer: A computer in a network can be considered as a mchine, host, node or system. If
 *   two computers are connected they need a wired or wireless setup and it makes possible to
 *   transfer data.
 * 
 * - Link layer: Even if the channel exist we should know what will pass or use it and the way it 
 *   will, so it is mandatory to have some regulations and protocols. Messaes should be broken in
 *   parts callled 'frames' (segments) and each one of them should be independent from other frames.
 *   Also you will need standards to understand what is being recieved and how to send info, some
 *   well-known protocol are Ehternet, IEEE 802.11 (wireless networks), LAN (Local Area Network), NIC
 *   (Network Interface Controller, which attached to LAN). This standards provide the access, adapters
 *   needed to exchange information. In the case of IEEE 802.11, it provides the MAC (Media Access
 *   Control) whihc si needed to be unique for connecting with WIFI.
 * 
 * - Network Layer: The MAC adresses are needed for using networks, but what if two computers from 
 *   different LANs try to connect? (Moreover, if one is wireless and the other one uses wire/fiber), so
 *   it is needed an overall protocol to the links layers. So we have 'packets' which are broken
 *   fragments of messages (frames encapsulate packets). Also, we have a 'network protocol' which 
 *   connects different link layer standards, one of the most famous is IP (Internet Protocol), and it
 *   can be IPv4 (four segments from 0.0.0.0 to 255.255.255.255 or 32 bits) and IPv6 (up to 16 bytes),
 *   which have a private and public adresses. The connection itself is achieved with a 'router node' 
 *   which decides which packets to transfer and how they are transferred, and the way to be connected 
 *   is provided by the Operating System they are in.
 *   When using a LAn adrress, each node has a MAC Adress (used for link layer protocols to trasmit to the
 *   LAN ) and an IP Adress (used to make connections within the same LAN or other LANs). So, we can say
 *   that this layer connects two or more LANs which generates a mesh of networks, for example, the internet
 * 
 * 
 * NOTE: You can use 'tracereoute' to see the routers between your computer and another computer.
*/