#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define CHUNKSIZE 2 // define global variables of protocol
#define WINDOW 10
#define TIMEOUT (1/2)

int sendData(int sd, struct sockaddr_in server_address);
int main(int argc, char *argv[])
{  
int sd;
struct sockaddr_in server_address;
int portNumber;
char serverIP[29];

if(argc != 3)
{
    printf("For client use <IPaddr> <portNumber>\n");
    exit(1);
}

sd = socket(AF_INET, SOCK_DGRAM, 0);

portNumber = strtol(argv[2], NULL, 10);
strcpy(serverIP, argv[1]);

server_address.sin_family = AF_INET;
server_address.sin_port = htons(portNumber);
server_address.sin_addr.s_addr = inet_addr(serverIP);


sendData(sd, server_address);

return 0;  
}

int sendData(int sd, struct sockaddr_in server_address) // function to send message
{
    char dataBuffer[100], sendBuffer[17], bufferIn[100], seg_data[CHUNKSIZE]; // set up buffers for every data needed
    int ack = -1, count = 0, rc = 0, seqNumber = 0;      // iset up int variables for window, ack's, sequence number, and return code
    struct sockaddr_in from_address;  // get from address for revfrom
    socklen_t fromLength = sizeof(from_address); // unix unstable if not set 

    printf("Enter a string: ");     // prompt user for string
    fgets(dataBuffer, 100, stdin);

    int dataBufferSize = strlen(dataBuffer) - 1;    // get size of string and expected last sequence number/ final segement
    int finalSegment = (dataBufferSize / CHUNKSIZE); 
    if (dataBufferSize % CHUNKSIZE > 0)     // increment if the is a decimal remainder
    {
        finalSegment++;
    }
    finalSegment = (finalSegment * 2) - 2;

    printf("Sending: %s\n", dataBuffer);      // convert size to network order and send to server
    printf("Size of message: %d\n", dataBufferSize);
    printf("Final packet: %d\n", finalSegment);
    int convertedSize = ntohl(dataBufferSize);
    rc = sendto(sd, &convertedSize, sizeof(convertedSize), 0, (struct sockaddr *) &server_address, sizeof(server_address));

    while(1)  // loop for sending window
    {
        if(ack == (finalSegment) || ack > (finalSegment)) // check if current ack is last ack to finish
        {
                printf("Finished.\n");
                break;
        }
        for(int i = count/CHUNKSIZE; i < count/CHUNKSIZE + 5; i++) // send window by looping through starting point to 5 segments from starting point
        {
                memset(seg_data, 0, sizeof (seg_data));    // set buffers for use
                memset(sendBuffer, 0, sizeof (sendBuffer));
			    if(seqNumber == finalSegment) // check if sequence number/packet is last packet 
			    {
			        if(dataBufferSize % 2 != 0) // check if message is odd then only send 1 byte
			        {
                        strncpy(seg_data, (dataBuffer + i*CHUNKSIZE), 1); // copy string to correct position and copy 1 byte
                        sprintf(sendBuffer, "%11d%4d", seqNumber, 1); // format string
                        strcat(sendBuffer, seg_data); // append to sendbuffer to form full packet
                        printf("Sending packet: %d -Data: %s -Length of packet in bytes: %zu\n", seqNumber, seg_data, strlen(sendBuffer)); // send packet
                        rc = sendto(sd, &sendBuffer, strlen(sendBuffer), 0, (struct sockaddr *) &server_address, sizeof(server_address)); // send packet
                        if(rc < 0)
                        {
                            printf("Error sendto\n");
                            exit(1);
                        }
                        break;
			        }
                    else // else message is even send 2
                    {
                        strncpy(seg_data, (dataBuffer + i*CHUNKSIZE), CHUNKSIZE);  // copy string to correct position and copy 1 byte
                        sprintf(sendBuffer, "%11d%4d", seqNumber, CHUNKSIZE); // format string
                        strcat(sendBuffer, seg_data);  // append to sendbuffer to form full packet
                        printf("Sending packet: %d -Data: %s -Length of packet in bytes: %zu\n", seqNumber, seg_data, strlen(sendBuffer)); // send packet
                        rc = sendto(sd, &sendBuffer, strlen(sendBuffer), 0, (struct sockaddr *) &server_address, sizeof(server_address));
                        if(rc < 0)
                        {
                            printf("Error sendto\n");
                            exit(1);
                        }
                        break;
                    }

			    }
                strncpy(seg_data, (dataBuffer + i*CHUNKSIZE), CHUNKSIZE); // copy string to correct position and copy 1 byte
                sprintf(sendBuffer, "%11d%4d", seqNumber, CHUNKSIZE);  // format string
                strcat(sendBuffer, seg_data);  // append to sendbuffer to form full packet
                printf("Sending packet: %d -Data: %s -Length of packet in bytes: %zu\n", seqNumber, seg_data, strlen(sendBuffer)); // send packet
                rc = sendto(sd, &sendBuffer, strlen(sendBuffer), 0, (struct sockaddr *) &server_address, sizeof(server_address));
                if(rc < 0)
                {
                    printf("Error sendto\n");
                    exit(1);
                }
				seqNumber+=2;
        }
        printf("Waiting for ack...\n"); // check for acks
        time_t startTime = time(NULL);  // variable to check the beginning time
        time_t currentTime = 0; // variable to check timestamp during proccess
        while(ack != finalSegment)  // while not at end
        {
            sleep(1); // sleep to allow for ack to get there in time
            memset(bufferIn, 0, sizeof (bufferIn)); // set buffer for reading
            memset(seg_data, 0, sizeof (seg_data));    // set buffer for the degmented data
            memset(sendBuffer, 0, sizeof (sendBuffer)); // set buffer for the the send buffer
            rc = recvfrom(sd, &bufferIn, 11, MSG_DONTWAIT, (struct sockaddr *) &from_address, &fromLength);
            if(rc < 0) // if rc is negative check if timeout or error
            {
                currentTime = time(NULL);   // get time stamp of after sleeping and receiving
                if (currentTime - startTime > TIMEOUT)
                {
                    printf("TIMEOUT...\n");
                    break;
                }
                printf("Error recvfrom\n");
                exit(1);
            }
            rc = sscanf(bufferIn, "%11d", &ack); // assign ack from server to current ack
            printf("Received ack of: %d\n", ack);  // print recieved ack
            if((ack + WINDOW) > finalSegment && rc > 0)
            {
                continue;
            }
            if((ack + WINDOW) == finalSegment) // check if sequence number/packet is last packet 
            {
                if(dataBufferSize % 2 != 0) // check if message is odd then only send 1 byte
                {
                    strncpy(seg_data, (dataBuffer + (ack + WINDOW)), 1); // copy string to correct position and copy 1 byte
                    sprintf(sendBuffer, "%11d%4d", (ack + WINDOW), 1); // format string
                    strcat(sendBuffer, seg_data); // append to sendbuffer to form full packet
                    printf("Sending packet: %d -Data: %s -Length of packet in bytes: %zu\n", ack + WINDOW, seg_data, strlen(sendBuffer)); // send packet
                    rc = sendto(sd, &sendBuffer, strlen(sendBuffer), 0, (struct sockaddr *) &server_address, sizeof(server_address)); // send packet
                    if(rc < 0)
                    {
                        printf("Error sendto\n");
                        exit(1);
                    }
                    continue;
                }
                else // else message is even send 2
                {
                    strncpy(seg_data, (dataBuffer + (ack + WINDOW)), CHUNKSIZE);  // copy string to correct position and copy 1 byte
                    sprintf(sendBuffer, "%11d%4d", (ack + WINDOW), CHUNKSIZE); // format string
                    strcat(sendBuffer, seg_data);  // append to sendbuffer to form full packet
                    printf("Sending packet: %d -Data: %s -Length of packet in bytes: %zu\n", ack + WINDOW, seg_data, strlen(sendBuffer)); // send packet
                    rc = sendto(sd, &sendBuffer, strlen(sendBuffer), 0, (struct sockaddr *) &server_address, sizeof(server_address));
                    if(rc < 0)
                    {
                        printf("Error sendto\n");
                        exit(1);
                    }
                    continue;
                }
            }
            strncpy(seg_data, (dataBuffer + (ack + WINDOW)), CHUNKSIZE); // copy string to correct position and copy 1 byte
            sprintf(sendBuffer, "%11d%4d", (ack + WINDOW), CHUNKSIZE);  // format string
            strcat(sendBuffer, seg_data);  // append to sendbuffer to form full packet
            printf("Sending packet: %d -Data: %s -Length of packet in bytes: %zu\n", ack + WINDOW, seg_data, strlen(sendBuffer)); // send packet
            rc = sendto(sd, &sendBuffer, strlen(sendBuffer), 0, (struct sockaddr *) &server_address, sizeof(server_address));
            if(rc < 0)
            {
                printf("Error sendto\n");
                exit(1);
            }
            startTime = time(NULL);
        }
		seqNumber = ack + 2; // increment sequence and count by 2 to start 1 segment after recent ack and incread window
        count = ack + 2;
    }
    return 0;
}
