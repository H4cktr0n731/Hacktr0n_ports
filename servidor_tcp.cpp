#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 120
extern int errno;
int main(int argc,char *argv[])
{
    char buf[MAX_LINE];
    struct sockaddr_in fsock, sname;
    struct hostent *hent; /* estructura que guarda el llamado a gethostbyname */
    int s, len;
    if (argc!=2){
printf("USO: cliente nombreMaquina_del_Servidor\n");
exit(1);
}
if(!(hent = gethostbyname(argv[1])) ){
perror("GETHOSTBYNAME: ");
exit(0);
}
if((s=socket(AF_INET,SOCK_STREAM,0)) < 0) {
perror("SOCKET: ");
exit(0);
}
    fsock.sin_family = AF_INET;
    fsock.sin_addr.s_addr = *(long *) hent->h_addr; /* direccion IP de Maq. Remota */
    fsock.sin_port = htons(4400); /* puerto de la maq. remota en formato BIGENDIAN */
    if(connect(s,(struct sockaddr *)&fsock, sizeof(struct sockaddr_in)) == -1){
        perror("CONNECT: ");
        close(s);
        exit(0);
    }
        printf("Arranca el Programa Cliente !!!... Pulse q para salir\n");
    while(1){
        printf("Dame una cadena.: ");
        fgets(buf,MAX_LINE,stdin);
        if( send(s,buf,strlen(buf),0) < strlen(buf) ){
            perror("SEND: ");
            break;
        }
if( buf[0]=='q' || buf[0] == 'Q'){
printf("Terminamos....\n");
close(s);
exit(0);
}
printf("Me detengo a recibir la respuesta del servidor...\n");
if( (len=recv(s,buf,MAX_LINE-1,0))<= 0 ){
perror("RECV: ");
close(s);
exit(0);
}
buf[len] = '\0';
printf("Respuesta..: %s\n\n",buf);
}
}
