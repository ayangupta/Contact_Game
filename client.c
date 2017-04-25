/*
 *  Author: Sandeeep Kumar Mittal
 *  Special Thanks to Prabodh Agarwal
 *  Description: Client side file to guess a number over TCP/IP sockets.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <time.h>
#include <fcntl.h>
 //#include <conio.h>

int main()
{
    // Important declaration
    int clientSocket;
    char *buffer;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    int leaderflag=0;
    int hinterflag=0;

    // User Input
    char *userInput;

    userInput = (char *)malloc(sizeof(char)*2000);
    buffer = (char *)malloc(sizeof(char)*2000);

    /*  Create the network socket.   */
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    /*  1) PR_INET Internet domain
        2) SOCK_STREAM represents Stream socket
        3) 0 represents Default protocol (TCP in this case)
        */

    // Configure settings of the server address
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;

    /* Set port number */
    serverAddr.sin_port = htons(9001);
    /*  In networking we prefer to use big-endian binary
        sequencing.  Since in our PC we use small endian binary
        scheme, we use htons to convert little endian to big
        endian.
        */

    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof
            serverAddr.sin_zero);

    /* Connect the socket to the server using the address*/
    addr_size = sizeof serverAddr;
    if ( connect( clientSocket, (struct sockaddr *) &serverAddr,
                addr_size) < 0 )
    {
        printf("[ERROR] Unable to connect to server.\n");
        close( clientSocket );
        exit(0);
    }

    int maxPoints = 1000;
    int counter = 0;
    unsigned int inputLength = 0;

    // User input to guess a number
    //printf("Attempt [%d] : ", ( counter + 1 ) );
    //printf("Enter the number between 1 to 100 to send: ");
    //while(1)
    {
        if ( recv ( clientSocket, buffer, 30, 0) < 0 )
        {
            printf("[ERROR] Connection closed prematurely.\n");
           // break;
        }

        else
        {
            printf("%s\n",buffer);
        }
        bzero(buffer, 31);
        scanf("%[^\n\t]s", userInput);

        inputLength = strlen(userInput);
        if ( send ( clientSocket, userInput, inputLength, 0) != inputLength )
            printf("[ERROR] Unable to send the data.\n");
        /* Read the message from the server into the buffer */
    }
   while(1){  {
        if ( recv ( clientSocket, buffer, 30, 0) < 0 )
        {
            printf("[ERROR] Connection closed prematurely.\n");
           // break;
        }

        else
        {
            printf("%s\n",buffer);
        }
        bzero(buffer, 31);
        scanf("%s", buffer);
        //printf("%s",buffer);

        inputLength = strlen(buffer);
        if ( send ( clientSocket, buffer, inputLength, 0) != inputLength )
            printf("[ERROR] Unable to send the data.\n");
        /* Read the message from the server into the buffer */
    }

  while(2>1){
    bzero(buffer,499);
    read(clientSocket,buffer,499);
    if(strcmp(buffer,"NEW")==0){printf("Round 1 Ends\n");bzero(buffer,499);break;}
    if(strcmp(buffer,"Enter the word")==0)
    {
        printf("%s\n",buffer);
        leaderflag=1;
        bzero(buffer, 31);
        scanf("%s", buffer);
        inputLength = strlen(buffer);
        if ( send ( clientSocket, buffer, inputLength, 0) != inputLength )
            printf("[ERROR] Unable to send the data.\n");
        bzero(buffer,499);
        read(clientSocket,buffer,499);


    }

        printf("%s\n",buffer);

	 bzero(buffer,499);
        read(clientSocket,buffer,499);
        printf("%s\n",buffer);


        //printf("ohd");

        bzero(buffer,499);
        //read(clientSocket,buffer,499);
        //printf("%s\n",buffer);
        //printf("here\n");
        bzero(buffer,499);
        if(leaderflag==0)
        scanf("%s", buffer);
        //bzero()
        //
        write(clientSocket,buffer,499);
        //printf("here is %s\n",buffer );
        bzero(buffer,499);
        //printf("here\n");
        read(clientSocket,buffer,499);
        //printf(" print this %s\n",buffer );
        if(strcmp(buffer,"Your hint is selected. Enter the word")==0)
        {   printf("(%s)\n",buffer );
            bzero(buffer,499);
            hinterflag=1;
            scanf("%s",buffer);
            write(clientSocket,buffer,499);
            bzero(buffer,499);
            read(clientSocket,buffer,499);


        }

      //while(1)
        //{
           // read(clientSocket,buffer,499);
                    printf("Hint is %s\n",buffer );
      if(leaderflag==0)
        {
            if(hinterflag==0)

                {
                    printf("Guess the word else type PASS\n");
                    bzero(buffer,499);
                    scanf("%s",buffer);
                    write(clientSocket,buffer,499);
                    //printf("yeh bheja");
                    bzero(buffer,499);
                    read(clientSocket,buffer,499);
                    printf("%s\n",buffer );
                }
                else
                {
                    bzero(buffer,499);
                    read(clientSocket,buffer,499);
                    printf("%s\n",buffer );
                    hinterflag=0;
                }

        }
        if(leaderflag==1)
        {
            printf("You have three guesses\n");
            printf("You can type PASS if you dont want to guess\n");

            //bzero(buffer,499);
            //read(clientSocket,buffer,499);
            //printf("first GUESSSSSSS %s\n",buffer );
            int pohs=1;
            int gu=3;
            while(gu!=0){
                printf("GUESS no %d\n",gu);
                bzero(buffer,499);
                scanf("%s",buffer);
                printf("%s\n",buffer );
                write(clientSocket,buffer,499);
                if(strcmp(buffer,"PASS")==0){gu=1;}
                bzero(buffer,499);
                read(clientSocket,buffer,499);
                printf("%s\n",buffer);

                if(strcmp(buffer,"CONGRATS .YOU ARE CORRECT")==0){gu=1;}
                gu--;
            }

           /* if(strcmp(buffer,"PASS")!=0)
            {
                printf("guess %d %s\n",pohs, buffer);
                //bzero(buffer,499);
                if(strcmp(buffer,"Wrong")==0){
                    bzero(buffer,499);
                    scanf("%s",buffer);pohs++;
                    write(clientSocket,buffer,499);
                    bzero(buffer,499);
                    read(clientSocket,buffer,499);
                    printf("guess is %d %s\n",pohs,buffer);
                    if(strcmp(buffer,"Wrong")==0)
                    {
                        bzero(buffer,499);
                        scanf("%s",buffer);pohs++;
                        write(clientSocket,buffer,499);
                        bzero(buffer,499);
                        read(clientSocket,buffer,499);
                        printf("guess is %d %s\n",pohs,buffer);
                    }
                    else{printf("%s\n", );}
                }
                else{

                }


            }*/

        }

}

leaderflag=0;
}



    /*int availablePoints = maxPoints;
    while ( buffer[0] == '2' )
    {
        ++counter;
        availablePoints = maxPoints - ( counter * 100 );
        if ( availablePoints > 0 )
        {
            // Send data to server
            printf("Attempt [%d] : ", ( counter + 1 ) );
            printf("Enter the number between 1 to 100 to send: ");
            scanf("%s", userInput);

            inputLength = strlen(userInput);
            if ( send ( clientSocket, userInput,
                        inputLength, 0) != inputLength )
                printf("[ERROR] Unable to send the data.\n");
            if ( recv ( clientSocket, buffer, 10, 0) < 0 )
                printf("[ERROR] Connection closed prematurely.\n");
        } else {
            userInput = "DONE\0";
            send ( clientSocket, userInput, 5, 0);
            break;
        }
    }
    availablePoints = maxPoints - (counter * 100 );
    */
    close( clientSocket );
    return 0;
}
