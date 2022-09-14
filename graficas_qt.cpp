#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/errno.h>
#include<pthread.h>
#include <unistd.h>
#define MAX_LINE 120
     extern int errno;
     struct sockaddr_in lsock,fsock,sname;
     int s,ss;
     char buf[MAX_LINE];
bool procesar_respuesta();
bool definir_socket(){

     if(( s=socket(AF_INET,SOCK_STREAM,0))< 0){
	     perror("SOCKET:");
 	     exit(0);
     }
     lsock.sin_family = AF_INET;
     lsock.sin_port =htons(4400);
     lsock.sin_addr.s_addr=0;
     printf("SOCKET CREADO EXITOSAMENTE");
     if(bind(s,(struct sockaddr *)&lsock, sizeof(struct sockaddr_in)) < 0 ){
          perror("BIND: ");
          exit(1);
     }
     if(listen(s,3)<0){
          perror("LISTEN: ");
          exit(1);
     }
     procesar_respuesta();
}

bool procesar_respuesta(){
     unsigned int len=0,i=0;
     while(1){
          len = sizeof(struct sockaddr_in); /* &len: entra y sale el tamano del socket esperado */
          if((ss=accept(s,(struct sockaddr *)&fsock, &len)) < 0){
               perror("ACCEPT: ");
               continue;
          }
          printf("Conexion en el socket %d (antes %d)\n",ss, s);
          if (fork() == 0) {
          /* Aqui se ejecuta el proceso hijo */
          /* Cierra el socket incompleto */
          /* se dedica a atender la conexion con el socket completo */
          close(s);
          while(1){
               if((len=recv(ss,buf,MAX_LINE-1,0))<=0){
                    perror("RECV: "); /* Si len==0 entonces el cliente cerro la conexion */
                    exit(1);
          }
               for(i=0; i<len; i++) { /* Despliega y transforma a Mayusculas */
                    putchar(buf[i]);
               if(buf[i] >= 'a' && buf[i] <= 'z')
                    buf[i] = 'A' + (buf[i] - 'a');
               }
          putchar('\n');
          if(buf[0] == 'Q' || buf[0] == 'q'){
               printf("Termina el servicio por decision del Cliente\n");
               close(ss);
               exit(0); /* el proceso hijo se mata */
          }
          if(send(ss,buf,len,0) < len) /* responde al cliente */
               perror("SEND: ");
          } /*while */
          } /* if fork */
          else /* Aqui continua el proceso vigia para aceptar otra conexion */
               close(ss); /* el padre cierra el socket completo que dejo al hijo */
     } /*while*/
}

int main(){
		definir_socket();  
  return 0;
}
