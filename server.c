//https://github.com/pranavdheer/Real-time-chat-application-in-c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include "helper.h"
#include "communication.h"
#include "paillier.h"

//********************GLOBAL DATA_STRUCTURES & CONSTANTS****************************
#define bufsize 1000

// mutex lock for global data access
pthread_mutex_t mutex;

struct client{
    char *name;
    int confd;
    struct client *next;
	  struct paillier_pubkey *pubkey; // ajout de la structure de cle publique.
};

struct client *header=NULL;

int* database = NULL;
int eteint = 0;

//**********************************************************************************

/*
 * @brief-: add user to the global user DATA_STRUCTURES
 * INSERTION AN HEAD -> O(1) complexity
*/

void add_user(struct client *user){

   if(header == NULL){
     header=user;
     user->next=NULL;
   }
   else{
      user->next=header;

      header=user;
   }
  // get current time
  time_t current_time;
  char* time_string;
  current_time = time(NULL);
  time_string = ctime(&current_time);
    
  // remove newline character from time string
  time_string[strlen(time_string) - 1] = '\0';
    
  printf("log : A new client \"%s\" is connected - %s\n", user->name, time_string);
}
/*
 * @brief-: delete client from thr global list
 *  O(n) complexity
 */
void delete_user(int confd){
   struct client *user=header;
   struct client *previous=NULL;
   // identify the user
   while(user->confd!=confd){
     previous=user;
     user=user->next;
   }

   if(previous == NULL)
      header=user->next;

   else
     previous->next=user->next;

   // free the resources
    printf("log : client \"%s\" is disconnected\n", user->name);
   free(user->name);
   free(user);

}

/*
* @brief-: assigns a listning socket at a given port number
* NOTE-: THE function traverses the list to find appropriate socket Connection
* for the server [ isrobust]
* @port-: port number
* @return -: listining file descriptor
*/
int connection(char * port){

   struct addrinfo *p, *listp, hints;
   int rc,listenfd,optval=1;

   //initialise to zero
   memset(&hints,0,sizeof(struct addrinfo));
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM; /* Connections only */
   hints.ai_flags =AI_ADDRCONFIG|AI_PASSIVE;
   hints.ai_flags |= AI_NUMERICSERV; //using fixed port number


   if ((rc = getaddrinfo(NULL, port, &hints, &listp)) != 0) {
     fprintf(stderr,"get_address info failed port number %s is invalid\n",port);
     return -1;
  }

   // traverse the list of available Connections
   for (p = listp; p; p = p->ai_next) {

       listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
       if (listenfd < 0) {
         continue; /* Socket failed, try the next */
       }

       /* Eliminates "Address already in use" error from bind */
      setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval,sizeof(int));
      //bind the socket, returns 0 on Success
      if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) {
          break; /* Success */
      }
      if (close(listenfd) < 0) { /* Bind failed, try the next */
            fprintf(stderr, "open_listenfd close failed: %s\n",
                    strerror(errno));
            return -1;
        }

    }

    // avoiding memory leak
    freeaddrinfo(listp);
    if (!p) { /* All connects failed */
        return -1;
    }

    // setting backlog to 1024 , desired value
    // set the socket to listen
    if (listen(listenfd, 1024) < 0) {
            close(listenfd);
            return -1;
        }

      return listenfd;
}

/*
 * send msg to all the clients
 */
void send_msg(int confd,char* msg, char* receiver, char* sender){

    char response[bufsize];
    struct client *user=header;
    if(receiver == NULL)
     while (user != NULL){
      if (user->confd == confd){
          strcpy(response,"msg sent\n\r\n");
          rio_writen(user->confd,response,strlen(response));
       }

      else{
          sprintf(response,"start\n%s : %s\n\r\n",sender,msg);
          rio_writen(user->confd,response,strlen(response));
      }
      user=user->next;
    }
   else{
       while (user != NULL){
         if(!strcmp(user->name,receiver)){
            sprintf(response,"start\n%s : %s\n\r\n",sender,msg);
            rio_writen(user->confd,response,strlen(response));
            strcpy(response,"msg sent\n\r\n");
            rio_writen(user->confd,response,strlen(response));

           return;
         }
         user=user->next;
       }
        strcpy(response,"user not found\n\r\n");
        rio_writen(confd,response,strlen(response));

   }

}

void evaluate(char *buf ,int confd ,char *username){

  char response[bufsize];
  char msg[bufsize];
  char receiver[bufsize];
  char keyword[bufsize];
  // clear the buffer
  msg[0]='\0';
  receiver[0]='\0';
  keyword[0]='\0';
  struct client *user=header;


  if(!strcmp(buf,"help")){
      sprintf(response,"msg \"text\" : send the msg to all the clients online.\n");
      sprintf(response,"%smsg \"text\" user :send the msg to a particular client.\n",response);
      sprintf(response,"%s/a text : send to all client.\n",response);
      sprintf(response,"%sonline : get the username of all the clients online.\n",response);
      sprintf(response,"%skeys : generate all the keys for Paillier encryption communication.\n",response);
      sprintf(response,"%squit : exit the chatroom.\n\r\n",response);
      rio_writen(confd,response,strlen(response));
      return;
   }

   // get the online user name
   if (!strcmp(buf,"online")){
      // empty the buffer
      response[0]='\0';
      //global access should be exclusive
      pthread_mutex_lock(&mutex);
      while(user!=NULL){
          sprintf(response,"%s%s\n",response,user->name);
          user=user->next;
      }
      sprintf(response,"%s\r\n",response);
      //global access should be exclusive
      pthread_mutex_unlock(&mutex);
      rio_writen(confd,response,strlen(response));
      return;
   }
/*
  //set keys
  if (!strcmp(buf,"keys")){
      response[0]='\0';
      strcpy(response,"keys\n\r\n");
      rio_writen(confd,response,strlen(response));
      return;
   }
*/
  //close the connexion
  if (!strcmp(buf,"quit")){
      pthread_mutex_lock(&mutex);
      delete_user(confd);
      pthread_mutex_unlock(&mutex);
      strcpy(response,"exit");
      rio_writen(confd,response,strlen(response));
      close(confd);
      eteint++;
      return;
   }

  //send to all
  if (!strncmp(buf, "/a", strlen("/a")) == 0) {
        sscanf(buf,"%s %[^\"]",keyword,msg);
        pthread_mutex_lock(&mutex);
        struct client *receiver=header;
        while(receiver!=NULL){
          send_msg(confd,msg,receiver->name,username);
          receiver = receiver->next;
        }
        free(receiver);
        pthread_mutex_unlock(&mutex);
    return;
   }


  //send to specific
  sscanf(buf,"%s \" %[^\"] \"%s",keyword,msg,receiver);
   if (!strcmp(keyword,"msg")){
      pthread_mutex_lock(&mutex);
      send_msg(confd,msg,receiver,username);
      pthread_mutex_unlock(&mutex);
      return;
  }
  
  //error
  else {
     strcpy(response," - Invalid command\n\r\n");
     rio_writen(confd,response,strlen(response));

  }

  return;
}


/*
* @brief-: the function handles incoming clients concurrently
* @vargp-: poiner to the connection file descriptor
*/
void* client_handler(void *vargp ){

  char username[bufsize];
  rio_t rio;
  struct client *user;
  long byte_size;
  char buf[bufsize];
  // detaching the thread from peers
  // so it no longer needs to be
  // terminated in the main thread
   pthread_detach(pthread_self());

   // saving the connection fd on function stack
   int confd = *((int *)vargp);
   rio_readinitb(&rio, confd);

    // read the user name as a single line , -1 is for error handling
    if( (byte_size=rio_readlineb(&rio,username,bufsize)) == -1){
         close(confd);
         free(vargp);
         return NULL;
    }
    //strip the newline from the string
    username[byte_size-1]='\0';
    // assign space in the global structure
    user=malloc(sizeof(struct client));
    // error handling
    if (user == NULL){
      perror("memory can't be assigned");
      close(confd);
      free(vargp);
      return NULL;
    }
    // user->name=username is not safe
    // as the local stack can be accessed by peer threads
    // assign space in heap
    user->name=malloc(sizeof(username));
    memcpy(user->name,username,strlen(username)+1);
    user->confd=confd;

    //lock
    pthread_mutex_lock(&mutex);
    add_user(user);
    //unlock
    pthread_mutex_unlock(&mutex);

    // read client response
    while((byte_size=rio_readlineb(&rio,buf,bufsize)) >0){

        //strip the newline from the string
        buf[byte_size-1]='\0';
        // take appropriate action
        evaluate(buf,confd,username);

    }

    return NULL;
}

/*
* manage the uses of command on the server
*
*/
void usage_server(){
  printf(" > h           : print help\n");
  printf(" > quit        : close all conections and the server\n");
  printf(" > tableau X Y : set the database to size X with dimension Y\n");
  printf(" > liberer     : free the allocated memory of the database\n");
}


void* server_handler(void *arg) {
    socklen_t clientlen = *(socklen_t*)arg;
    char buffer[BUFSIZ];
    int n;


    while(1) {
        // read from stdin
        n = read(STDIN_FILENO, buffer, BUFSIZ);

        if (n > 0) {
            // process the input
            buffer[n-1] = '\0'; // replace the newline character with a null terminator
            printf("log: server command - %s\n", buffer);
        }

        //to close the server
        if (strcmp(buffer, "quit") == 0) {
                printf("log: server is shutting down...\n");

                //close the server
                if(header==NULL){
                  libererTab(database);
                  printf("log: server closed.\n");
                  close(clientlen);
                  exit(0);
                }
                  

                printf("log: server is closing connections...\n");
                // close all connections
                while(header!=NULL){
                  evaluate("quit",header->confd,header->name);
                }

                // exit the program
                libererTab(database);
                printf("log: server closed.\n");
                close(clientlen);
                exit(0);
        }

        //to active the database
        if (strncmp(buffer, "tableau", strlen("tableau")) == 0) {
            // extract the arguments from the buffer
            int size, dimension;
            int res = sscanf(buffer, "tableau %d %d", &size, &dimension);
            if (res != 2)
            {
                printf("log: Command Error: invalid arguments\n");
            } else if (size <= 0 || dimension <= 0) 
            {
                printf("log: Command Error: invalid size or dimension\n");
            } else 
            {
                // allocate the array
                genererTab(database, size, dimension);
            }
          }

        //liberate database
        if (strcmp(buffer, "liberer") == 0) {
          libererTab(database);
        }
        
        //print help
        if (strcmp(buffer, "h") == 0) {
          usage_server();
        }
/*
        //print public keys
        if (strcmp(buffer, "publicKeys") == 0) {
          printf("log: Display public keys\n");
          pthread_mutex_lock(&mutex);
          struct client *receiver=header;
          while(receiver!=NULL){
            printf("-----------------------\n");
            printf("%c :\n", receiver->name);
            gmp_printf("N : %Zd", receiver->pubkey->n);
            gmp_printf("N^2 : %Zd", receiver->pubkey->n2);
            printf("-----------------------\n");
            receiver = receiver->next;
          }
          free(receiver);
          pthread_mutex_unlock(&mutex);
        }
*/        


        
        
        if (strcmp(buffer, ""))
        {
            // TODO: process the server command here
        }
          
    }
}



int main(int argc,char **argv){
  struct sockaddr_storage clientaddr;
  socklen_t clientlen;
  int listen=-1;
  char host[1000];
  char *port="5555";		//a free port to play
  int *confd;
  pthread_t tid_server, tid_client;

  if (argc > 1)
    port=argv[1];

  // make a connection file descriptor
  listen= connection(port);

  //connection failed
  if(listen == -1){
   printf("connection failed\n");
   exit(1);
  }
  usage_server();
  printf("#######################################\n");
  printf("log: waiting at localhost and port '%s'\n",port);


  //set up the server to be able to be used
	// start a thread to handle server input
	pthread_create(&tid_server, NULL, server_handler, &clientlen);



  // loop to keep accepting clients
  while(!eteint){
    // assign space in the heap [prevents data race]
    confd=malloc(sizeof(int));
    *confd=accept(listen, (struct sockaddr *)&clientaddr, &clientlen);
    
    // assign a seperate thread to deal with the new client
    pthread_create(&tid_client,NULL,client_handler, confd);

  }
	return 0;
}
