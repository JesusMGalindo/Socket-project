*******************************************************
*  **Name      :**  Jesus Galindo       
*  **Student ID:**  108568522             
*  **Class     :**  CSCI 3761 Section 001        
*  **Project # :**  2             
*  **Due Date  :**  Nov, 7, 2022
*******************************************************
   
# Read Me  

## Instructions

* User will have two terminals with the directories of the server and client files pulled up. The user will type "make" to create objects and executable files for the client side to create an executable shortcut to run the code. "./client". The server is an executable provided by instructor and can be called the same way as client. The client must enter an IP and port number "./client <ipaddr> <port>". the server must enter a port number "./server <portNumber>". To get rid of all objects and executables for the client type "make clean" in the terminal in the directory of the file desired. 

##  Description of the programs

1. client.c: 
The client is implementing an RDT and a sliding window protocol. The user will be prompted to input a string preferably a long string. The data portion of the segment set will be 2 bytes maximum. The MSS is 17 bytes, which means 15 bytes of ‘header’ and 2 bytes of ‘data’ (max).  We will be using UDP to send the segment. The window size is 10 and the message will be sent to the server via the protocol.  


##  Source files

* *** client.c ***
   **Main program** This is the driver program for the client that takes command arguments as input in the form of the IP of the server and the port number of the server and asks user to input a string to send.
      

##  Circumstances of programs

   * The program runs successfully.  
          

##  Program Output

**client**

Enter a string: Hello world, how are you today? I am fine, thanks for asking me
Sending: Hello world, how are you today? I am fine, thanks for asking me

Size of message: 63
Final packet: 62
Sending packet: 0 -Data: He -Length of packet in bytes: 17
Sending packet: 2 -Data: ll -Length of packet in bytes: 17
Sending packet: 4 -Data: o  -Length of packet in bytes: 17
Sending packet: 6 -Data: wo -Length of packet in bytes: 17
Sending packet: 8 -Data: rl -Length of packet in bytes: 17
Waiting for ack...
Received ack of: 0
Sending packet: 10 -Data: d, -Length of packet in bytes: 17
Received ack of: 2
Sending packet: 12 -Data:  h -Length of packet in bytes: 17
Received ack of: 4
Sending packet: 14 -Data: ow -Length of packet in bytes: 17
Received ack of: 6
Sending packet: 16 -Data:  a -Length of packet in bytes: 17
Received ack of: 8
Sending packet: 18 -Data: re -Length of packet in bytes: 17
Received ack of: 10
Sending packet: 20 -Data:  y -Length of packet in bytes: 17
Received ack of: 12
Sending packet: 22 -Data: ou -Length of packet in bytes: 17
Received ack of: 14
Sending packet: 24 -Data:  t -Length of packet in bytes: 17
Received ack of: 16
Sending packet: 26 -Data: od -Length of packet in bytes: 17
Received ack of: 18
Sending packet: 28 -Data: ay -Length of packet in bytes: 17
Received ack of: 20
Sending packet: 30 -Data: ?  -Length of packet in bytes: 17
Received ack of: 22
Sending packet: 32 -Data: I  -Length of packet in bytes: 17
TIMEOUT...
Sending packet: 24 -Data:  t -Length of packet in bytes: 17
Sending packet: 26 -Data: od -Length of packet in bytes: 17
Sending packet: 28 -Data: ay -Length of packet in bytes: 17
Sending packet: 30 -Data: ?  -Length of packet in bytes: 17
Sending packet: 32 -Data: I  -Length of packet in bytes: 17
Waiting for ack...
Received ack of: 24
Sending packet: 34 -Data: am -Length of packet in bytes: 17
Received ack of: 26
Sending packet: 36 -Data:  f -Length of packet in bytes: 17
Received ack of: 28
Sending packet: 38 -Data: in -Length of packet in bytes: 17
TIMEOUT...
Sending packet: 30 -Data: ?  -Length of packet in bytes: 17
Sending packet: 32 -Data: I  -Length of packet in bytes: 17
Sending packet: 34 -Data: am -Length of packet in bytes: 17
Sending packet: 36 -Data:  f -Length of packet in bytes: 17
Sending packet: 38 -Data: in -Length of packet in bytes: 17
Waiting for ack...
Received ack of: 30
Sending packet: 40 -Data: e, -Length of packet in bytes: 17
Received ack of: 32
Sending packet: 42 -Data:  t -Length of packet in bytes: 17
Received ack of: 34
Sending packet: 44 -Data: ha -Length of packet in bytes: 17
Received ack of: 36
Sending packet: 46 -Data: nk -Length of packet in bytes: 17
Received ack of: 38
Sending packet: 48 -Data: s  -Length of packet in bytes: 17
Received ack of: 40
Sending packet: 50 -Data: fo -Length of packet in bytes: 17
Received ack of: 42
Sending packet: 52 -Data: r  -Length of packet in bytes: 17
Received ack of: 44
Sending packet: 54 -Data: as -Length of packet in bytes: 17
TIMEOUT...
Sending packet: 46 -Data: nk -Length of packet in bytes: 17
Sending packet: 48 -Data: s  -Length of packet in bytes: 17
Sending packet: 50 -Data: fo -Length of packet in bytes: 17
Sending packet: 52 -Data: r  -Length of packet in bytes: 17
Sending packet: 54 -Data: as -Length of packet in bytes: 17
Waiting for ack...
Received ack of: 46
Sending packet: 56 -Data: ki -Length of packet in bytes: 17
Received ack of: 48
Sending packet: 58 -Data: ng -Length of packet in bytes: 17
Received ack of: 50
Sending packet: 60 -Data:  m -Length of packet in bytes: 17
Received ack of: 52
Sending packet: 62 -Data: e -Length of packet in bytes: 16
Received ack of: 54
Received ack of: 56
Received ack of: 58
Received ack of: 60
Received ack of: 62
Finished

