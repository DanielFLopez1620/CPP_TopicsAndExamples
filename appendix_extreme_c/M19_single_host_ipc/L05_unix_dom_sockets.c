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
 *   (where you need public adresses).
 *   Ther ei s a basic tool to guarantee connection, and it is the 'ping', it sends a number of ICMP
 *   (Internet Control Messages Protocol) packets and if it is replayed then it is connected.
 * 
 *      ping 8.8.8.8 # Check ping if you are connected with internet (Public IP of Google DNS Service).
 * 
 * - Transport Layer: Having just the connection is pretty general, and you would want different distinct 
 *   connections for several processes, which has its own identifiers known as 'ports'.
 *   It can be understood as a telephone system, when a person uses a telephone, the phone is the transport
 *   connection, and the call is only possible if the infrastructure allows it. If you want to communicate
 *   with others, they need a phone (or a NIC for nodes) and they will get notifies (ring) when someone is 
 *   trying to communicate with them. For communicating with someones you need his/her number (IP) and the 
 *   language must (in most cases) be the same, or at least a protocol you know.
 *   
 *  For the transport, we can talk about 'connection-oriented communication'  (a dedicated channel is created
 *  for a connector). Here, as said before, the messages are sent in fragments, if they are received in a
 *  different order, then they are re-arranged. Moreover, if one packet get lost, the receiver can request
 *  a resend of it. One of the most famous protocols that supports this is the Transport Control Protocol
 *  (TCP). On the other hand, the communcation can be 'connection-less' which doesn't guarantee the
 *  individual delivery and the sequence of them, one example is the User Datagram Protocol (UDP).
 * 
 *  Another important concept in this layer is the 'stream' a sequence of bytes that is transmited over
 *  a 'connection-oriented' channel, and another one is 'datagram' which is related with 'connection-
 *  less' communication.
 * 
 *  Now, let's answer the question about 'How the transport sequence is initializated?', it is different
 *  for both communications mentioned, but they have in common that the 'listener' always bind an endpoint
 *  (IP + Port(number of two bytes)):
 * 
 *  * Connection-less initialization sequences:
 *    1) Listener bind a port of the NICs, which will end in a redirection of the packets targeted to it.
 *    2) Process waits to read messages.
 *    3) The listener IP adress should be known for the connector to make the connection.
 *    4) If it is established, the connector can write to the channel and read from it.
 * 
 *  * Connection-oriented initialization sequences:
 *    1) Listener bind a port of the NICs.
 *    2) Listener configures the size of the backlog (queue of pending connections)
 *    3) After being set the backlock, the listener enters to listening mode.
 *    4) Listener accepts incomming connections
 * 
 * 
 * NOTE: You can use 'tracereoute' to see the routers between your computer and another computer.
*/