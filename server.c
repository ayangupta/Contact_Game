#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <fcntl.h>

struct info
{
    int socketvalue;
    char name[20];
    int points;
    int corr;
};

struct val
{
    int score;
};

/*void handle(int sig){
    printf(" ------- \t\t\t\t ----------------------------\n  %s  \t\t\t\t %s\t%s\t%s\t%s  \n    %d    \t\t\t\t   %d\t  %d\t  %d\t  %d   \n ------- \t\t\t\t ----------------------------\n",timer,buffo[0],buffo[1],buffo[2],buffo[3],tim,scores[0],scores[1],scores[2],scores[3]);
    //printf("|\t\t\t\t\t\t\t\t\t| \n");
    //printf("  %s  ",timer);printf("\t\t\t\t %s\t%s\t%s\t%s  \n",buffo[0],buffo[1],buffo[2],buffo[3]);
    //printf("    %d    ",time);printf("\t\t\t\t   %d\t  %d\t  %d\t  %d   \n",scores[0],scores[1],scores[2],scores[3]);
    //printf(" ------- \t\t\t\t ----------------------------\n");
    //printf("|\t\t\t\t\t\t\t\t\t| \n");
    //printf("|\t%s\t\t%s\t\t%s\t\t%s\t\t| \n",buffo[0],buffo[1],buffo[2],buffo[3]);
    //printf("|\t%d\t\t%d\t\t%d\t\t%d\t\t| \n",scores[0],scores[1],scores[2],scores[3]);
    //printf("|\t\t\t\t\t\t\t\t\t| \n");
    //printf("\t\t\t%s\t \n",hint);
    //printf("\t\t%s\n",notice);
    //printf("|\t\t\t\t\t\t\t\t\t| \n");
    //printf("|\t\t\t\t\t\t\t\t\t| \n");
    //printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| \n");
    printf("\033[6A");
    //scanf("%d",&scores[2]);
    tim++;
    alarm(1);
}*/


//char timer[]={"timer"};

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {

    time_t endwait;
    time_t start;
    time_t seconds;
    
    //signal(SIGALRM, handle);
    //alarm(1);
    int tim = 1;

    struct val* sc;    
    struct info idname[5];
    int sockfd, newsocketfd[5], newsockfd, portno;
    socklen_t clilen;
    char buffer[500];
    struct sockaddr_in serv_addr, cli_addr[5];
    int n;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
         error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 9001;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd, 5);
    clilen = sizeof(cli_addr[0]);
    fcntl(sockfd, F_SETFL, fcntl(sockfd,F_GETFL, 0) | O_NONBLOCK);

    //Below code is modified to handle multiple clients using fork
    //------------------------------------------------------------------
    int i=0,qwe;
    start = time(NULL);
    seconds = 10;
    endwait = start + seconds;
    do{

         newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr[i], &clilen);

         if (newsockfd != -1)
            {     
            //printf(\r) 
            //fcntl(newsockfd, F_SETFL, fcntl(newsockfd,F_GETFL, 0) | O_NONBLOCK);   
            newsocketfd[i++] = newsockfd;
            //do whatever you want
            
          } 
    }while((start = time(NULL)) < endwait);
    int j;
    sc = calloc(i,sizeof(struct val));
    for(j=0;j<i;j++)
    {
        n = write(newsocketfd[j], "Enter you Name", 15);
        if (n < 0)
             error("ERROR writing to socket");
         idname[j].corr=0;
         idname[j].points=0;

            //error("ERROR reading from socket");
            
    }
    for(j=0;j<i;j++)
    {
        bzero(buffer, 256);
        n = read(newsocketfd[j], buffer, 499);
        idname[j].socketvalue = newsocketfd[j];
        strcpy(idname[j].name,buffer);
        if (n >= 0)
            printf("The name of the player is: %s from %d\n", idname[j].name,idname[j].socketvalue);       
    }

    while(1)
    {
    for(j=0;j<i;j++)
    {
        n = write(newsocketfd[j], "Do you want to be a leader", 26);
        if (n < 0)
             error("ERROR writing to socket");
            //error("ERROR reading from socket");
    }
    int oi=1;
    int leader;
    char leadername[20];
    start = time(NULL);
    seconds = 10;
    endwait = start + seconds;
    for(j=0;j<i;j++)
    {
        //do
        {
            bzero(buffer, 499);
            n = read(newsocketfd[j], buffer, 499);
            //if (n > 0)
            {
                printf("Answer: %s from %d\n", buffer,idname[j].socketvalue);
                if((strcmp(buffer,"yes")==0)&& oi==1)
                {
                    write(newsocketfd[j],"Enter the word",255);oi=-91;
                    leader=newsocketfd[j];
                    printf("(leader =%d)\n",leader );
                    strcpy(leadername,idname[j].name);
                   }                                     
                //break;
            }
        }// while ((start = time(NULL)) < endwait);
    }
    bzero(buffer, 499);
    read(leader,buffer,499);
    char word[35];
    strcpy( word,buffer);
    int length=strlen(word);
    char hint[length];
    hint[0]=word[0];
    int fo=1;
            int hindex=1;
    for(fo=1;fo<length;fo++)
    {
        hint[fo]='_';
    }
    while(strcmp(hint,word)!=0)
        {
            bzero(buffer, 499);
            strcpy(buffer,hint);
            strcat(buffer,"(");
            char stri[3];
            sprintf(stri,"%d",length);
            strcat(buffer,stri);
            strcat(buffer,")");
            strcat(buffer,"and the leader is ");
            strcat(buffer,leadername);

            
            j=0;
            for(j=0;j<i;j++)
            {   printf(" %s \n",buffer);
                write(newsocketfd[j],buffer,499);
                if (n < 0)
                     error("ERROR writing to socket");
                    //error("ERROR reading from socket");
            }

    
            j=0;
            for(j=0;j<i;j++){
                if(newsocketfd[j]==leader)write(newsocketfd[j],"Other people are typing hints now",499);
               else{ write(newsocketfd[j],"You can now type the hints else type PASS",499);
                if (n < 0)
                     error("ERROR writing to socket");  
            }}
            j=0;
            char hhint[200];
            char hword[30];
            int hinter;
            int bk=0;
            for(j=0;j<i;j++)
            {
                if(newsocketfd[j]==leader){printf("\n");}
                else
                    {
                        bzero(buffer,499);
                        read(newsocketfd[j], buffer, 499);
                        
                        

                        //printf("%s\n",buffer );
                        if(strcmp(buffer,"PASS")!=0&&bk!=1)
                            {   
                                strcpy(hhint,buffer);
                                bk=1;
                                write(newsocketfd[j],"Your hint is selected. Enter the word",499);
                                bzero(buffer,499);
                                hinter=newsocketfd[j];
                                read(newsocketfd[j],buffer,499);
                                strcpy(hword,buffer);
                                
                            }
                    }

                //printf("%s\n",buffer);

            }
            printf("HINT-%s\n",hhint);
            //printf("%s\n",hword );
            j=0;
            bzero(buffer,499);
            strcpy(buffer,hhint);
            for(j=0;j<i;j++)
            {
                write(newsocketfd[j],buffer,499);
            }
            j=0;
            int guesses=3;
            int noofcontacts=0;
            int lcorrect=0;

            for(j=0;j<i;j++)
            {   if(newsocketfd[j]==leader)
                {   bzero(buffer,499);
                        read(leader,buffer,499);
                        printf(" NEW TRY%s\n",buffer );
                        printf("Type guess number %d", guesses);
                        
                    while(guesses!=0)
                    {   
                        printf("Type guess number %d\n", guesses);
                        bzero(buffer,499);
                        read(leader,buffer,499);

                        printf(" output of read %s\n",buffer );
                        if(strcmp(buffer,"PASS")==0)
                        {
                            write(leader,"PASS",499);
                            guesses=0;

                        }
                        else
                        {   
                            if(strcmp(buffer,hword)==0)
                            {   write(leader,"CONGRATS .YOU ARE CORRECT",499);
                                printf("Leader guessed correctly\n");      
                                guesses=0;
                                lcorrect=1;       
                                sc[j].score++; 
                                idname[j].points+=2;
                                printf("points- %d  name- %s\n",idname[j].points,idname[j].name );

                            }
                            else{
                                write(leader,"Wrong",499);
                                printf("Wrong, guesses left = %d   %s\n",(guesses-1),buffer);
                                bzero(buffer,499);
                                //read(leader,buffer,499);
                                
                                
                                guesses--;
                            }
                            //bzero(buffer,499);
                            //read(leader,buffer,499);

                        }
                    }
                }
                else
                {
                    if(newsocketfd[j]==hinter)
                        {
                            write(hinter,"Wait for people to contact",499);
                        }
                    else
                    {   
                        read(newsocketfd[j],buffer,499);
                        printf("%s\n",buffer );

                        //j=0;
                        if(strcmp(buffer,hword)==0)
                            {   write(newsocketfd[j],"CONGRATS .YOU ARE CORRECT",499);
                                //printf("leader guessed correctly\n");      
                                //guesses=0;            
                                //idname[j].points+=5;      
                                noofcontacts++;
                                sc[j].score++;  sc[hinter].score++;
                            }
                        else
                        {

                            write(newsocketfd[j],"You are wrong",499);
                        }
                    }
                } 
                



                //bzero(buffer,499);
                //ead(newsocketfd[j],buffer,499);
                //bzero(buffer,499);
                
            }

            if(noofcontacts!=0&&lcorrect==0){
                    hint[hindex]=word[hindex];
                    printf("Modified hint %s\n",hint );
                    hindex++;
                 //noofcontacts=0;
                }
                        
             j=0;
                for(j=0;j<i;j++)

                  { 
                    if(lcorrect==0&&noofcontacts!=0){
                        //hint[hindex]=word[hindex];
                        //printf("modified hint %s\n",hint );
                        //hindex++;
                         
                        if(newsocketfd[j]!=leader){
                            //printf("points kyu nahi badh rahe\n");
                            //printf("newsocketfd[j] - %d hinter %d\n",newsocketfd[j],hinter );
                        if(newsocketfd[j]==hinter)
                        {
                            idname[j].points+=5;
                            printf("points -  %d name - %s\n",idname[j].points,idname[j].name );
                        }
                        else{
                            if(idname[j].corr=1)
                                {
                                idname[j].points+=5;
                                idname[j].corr=0;
                                printf("points -  %d name - %s\n",idname[j].points,idname[j].name );
                                }
                                else{
                                    //printf("bakchodi MAX\n");
                                }
                           
                            }     
                        }
                        //else{printf("leader hi hoon bhai\n");}

                    }
                        //else{printf("bas ye hi bacha tha\n");}
                }
                noofcontacts=0;
               /*if(i==4)
                sprintf(buffer," ------- \t\t\t\t ----------------------------\n  %s  \t\t\t\t\t %s\t%s\t%s  \n    %d    \t\t\t\t   %d\t  %d\t  %d\t     \n ------- \t\t\t\t ----------------------------\n",timer,idname[0].name,idname[1].name,idname[2].name,tim,sc[0].score,sc[1].score,sc[2].score);
                else if(i==5)
                sprintf(buffer," ------- \t\t\t\t ----------------------------\n  %s  \t\t\t\t %s\t%s\t%s\t%s  \n    %d    \t\t\t\t   %d\t  %d\t  %d\t  %d   \n ------- \t\t\t\t ----------------------------\n",timer,idname[0].name,idname[1].name,idname[2].name,idname[3].name,tim,sc[0].score,sc[1].score,sc[2].score,sc[3].score);
                
            for(j=0;j<i;j++)
            {write(newsocketfd[j],buffer,499);
            }*/
            
}
 
  for(j=0;j<i;j++)
    {
                write(newsocketfd[j],"NEW",499);
                
                    
               
            
    }   //fflush(stdout);
    //printf("Out\rINn");
    //fflush(stdout);
}    //-------------------------------------------------------------------
   return 0;
}
