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
	if (( s=socket(AF_INET,SOCK_STREAM,0))<0)
{
             perror("socket:");
		exit (0);
	}
     /* QUE SIGNIFICA EL CODIGO ANTEIROR
      * AQUI DEFINIMOS EL SOCKET DE LA FAMILIA INET
      * DEL TIPO SOCKET STREAM LE ESTAMOS DICIENDO QUE NOS CREE UN SOCKET  ORIENTADO A CONECION
      * OSEA LE ESTAMOS DICIENDO QUE NOS CREE UN SOCKET QUE SEA DEL TIPO TCP YA QUE COMO SABEMOS EL PROTOCOLO TCP
      * ES ORIENTADO A CONEXION
      * QUE QUIERE DECIR ESO?
      * SIMPLRE LO QUE NOS DICE ES QUE EL OTRO EXTREMO DE LA CONEXION NOS  TIENE QUE ENVIAR UNA RESPUESTA QUE CONFIRME QUE REALEMTE
      * LE HEMOS ENVIADO ALGO A ESE EXTREMO ES ALGO PUEDE SER UN MENSAJE , UN ARCHIVO  HASTA UN AUDIO SI AUNQUE NO LO CREAS PERO NOLIMITAREMOS
      * A CREAR PRIMERO CON PUROS MENSAJES
      * DESPUES LE DAMOS LA OPCION 0 QUE SEGUN DICE SAN GOOGLE XD QUE EL SOCKET TENDRA QUE SER SOCKET DEL TIPO TCP PERO ESO LO DETERMINA EL SISTEMA OPERATIVOCON
      * ESTA OPCION EL SISTEMA ELEGIRA CUAL ES EL QUE NOS CONVIENE MAS SIEMPRE DEBERIA DE SER CERO EL TERCER PARAMETRO DE LA FUCNON SOCKET EXCEPTO EN CIRUNTANCIAS EXCEPCIONALES Y RARAS CON 0 ES PRECISAMENTE PARA TCP
      * ESTA FUNCION SOCKET DEVUELVE UN DESCRIPTOR MOMENTO QUE DEMONIOS ES ESO???
      * PUES BIEN UN DESCRIPTOR COMO SE CONOCE COMUNMENTE COMO DESCRIPTOR DE ARCHIVO ES UN NUMERO PEQUENO ENTERO Y TU TE PREGUNTARAS PARA QUE QUIERO ESA MIERDA DE NUMERO JAJA
      * PUES ESE NUMERO ES UNA REFERENCIA AL SOCKET EN CUESTION PARA USOS POSTERIORES EN EL PROGRAMA
      * ESTA FUNCION SOCKET COMO DIJIMOS DEVULEVE UN DESCRIPTOR DE ARCHIVO OSEA EL NUMERO PEQUENO EN CASO DE SER ESE NUMERO PEQUENO EL NUMERO -1 QUIERE DECIR QUE NUESTRO SOCKET A FALLADO AL MOMENTO DE CREARSE Y POR ENDE NO PODEMOS CREAR ESE SOCKET.
      POR ESO LA COMPARACION DE socket (AF_INET,SOCK_STREAM,0)<0 YA QUE CASO DE SER MENOR A O PUES QUIERE DECIR QUE NUESTRO SOCKET NOS E CREO COMO LO MENCIONAMOS ANTERIORMENTE
      */
     lsock.sin_family=AF_INET;
     lsock.sin_port=htons(4400);
   	 lsock.sin_addr.s_addr=0;
     
     /*
        AHORA QUE CHUCHAS ES TODOS ESTO  DE SIN FAMILY   SIN PORT NO SE QUE TANTO???? WHAT !!!
        NO OS ASUSTEIS PARA ESO ESTOY AQUI JAJAJA
        PUES BIEN LA ESTRUCTURA EN SI DEFINIDA EN LA LIBRERIA include<netinet/in.h> NOS DICE QUE CONTIENE DETRO DE SU CODIGO DE ESA LIBRERIA
        UNA ESTRCUTURA QUE CONTIENE LA SIGUIENTE INFORMACION
        struct sockaddr_in   ESTE ES EL NOMBRE DE LA ESTRCTURA EN SI
          Y PARA QUE QUEREMOS UNA ESTRCTURA ASI?
          PUES PARA ALMACENAR LAS INFORMACION DE LAS DIRECCIONES IP
          {
          short sin_family; ESTE EL EL TIPO DE FAMILIA DEL PROTOCOLO POR CONVENCION COMO EN LA FUNCION SOCKET QUE HEMOS VISTO SE USA LA FAMILIA AF_INET
          u_short sin_port; ESTE ES EL PUERTO QUE QUEREMOS USAR EN EL SOCKET CREADO ANTERIORMENTE EN ESTE EJEMPLO COMO MENCIONAMOS SE USA  EL PUERTO 4440
          struct in_addr sin_addr; ESTE CAMPO HACE REFERENCIA A UNA ESTRCUTRA ANIDADA QUE ES ESO?
          UNA ESTRCUTRA ANIDADA NO ES MAS QUE UNA ESTRCUTRA DENTRO DE OTRA ESTRUCTURA SUENA DE LOCOS VERDAD ? PERO ES ASI DE HECHO EN C Y C++ HAY INFINIDAD DE
          COMBINACIONES QUE SE PUEDEN HACER ESTO TE LO DIGO POR EXPERIENCIA CON ESTE LEGUAJE PERO ESTO DIVAGANDO  JEJE
          VOLVIENDO A LO NUESTRO  ESTE CAMPO SIMPLEMENTE ES NUESTRA DIRECCION IP  QUE LE QUEREMOS PASAR AL SOCKET
          char sin_cero[8]; ESTE CAMPO SIN CERO SE USA PARA FORMATEAR EL CONTENIDO DEL CAMPO ANTERIOR OSEA  LA DIRECCION IP
          };
      */
     
     printf("SOCKET CREADO EXITOSAMENTE");
     if(bind(s,(struct sockaddr *)&lsock, sizeof(struct sockaddr_in)) < 0 ){
     /*la funcion bind que es eso?
      * PUES BIEN EL SOCKET  SERVIDOR QUE YA HEMOS CREADO DE ALGUNA MANERA TIENE QUE ASOCIAR AL CLIENTE POR MEDIO DE UN PUERTO Y UNA DIRECCION DE INTERFAZ DE RED  PARA QUE ESE CLIENTE PUEDEA ACCEDE 
      * A ESE CLIENTE PUES BIEN ESO SE CONSIGUE GRACIAS  A ESTA FUNCION BIND LA CUAL RECIBE
      * 3 PARAMETROS EL DESCRIPTOR DEL SOCKET NOMBRADO EN ESTE CASO s  
      * EL SEGUNDO PARAMETRO ES EL TIPO DE SOCKET QUE ES YA SEA AF_INET  O  AF_UNIX 
      * EL TERCERO Y ULTIMO ES LA LOGITUD DE LA ESTRUCTURA VISTA ENTERIORMENTE LA QUE TIENE EL NOMBRE DE sockaddr_in */
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
     while(1){ /*DEBEMOS DE TENR UN CICLO INFITO YA QUE NOSOTROS OCMO CLEINTE DEBEMOS DE ESTA ALA ESCUCHA DE LA INFORMACION QUE PODAS RECIBIR POR PARTE DEL SERVIDOR */
          len = sizeof(struct sockaddr_in); /* NOS DA EL TAMANO DEL SOCKET EN CUESTION TAL Y COMO HICIMOS ANTERIORMENTE*/
          if((ss=accept(s,(struct sockaddr *)&fsock, &len)) < 0){
          /*
	   *  ESTA FUNCION accept TAL Y COMO SU NOMBRE LO DICE SE USA PARA CONMUNICARSE CON EL CLIENTE QUE FUE ACEPTADO POR PARTE DE LA CONEXION
	   *  ES NECESARIA DEBIDO A QUE SI NO NO TENDRIAMOS UNA FORMA DE SABER SI EL OTRO EXTEMO DE LA CONEXION OSEA EL SERVIDOR NOS HA ACEPTADO PARA
	   *  DE ESA MANERA ENVIAR INFORMACION HACIA EL SERVIDOR
	   *  ESTA FUNCION DEVUELVE UN NUEVO DESCRIPTOR DE FICHERO PARA ESE PROPOSITO
	   *  ADMEAS RECIBE TRES PARAMETROS EL PRIMERO YA SABEN ES UN DESCRIPTOS DEL SOCKET 
	   *  EL SEGUNDO LA NUEVA REFERENCIA PARA PODER CREAR EL NUEVO DESCRIPTOR UNA VEZ ACCEPTADA ESA CONEXION POR PARTE DEL SERVIDOR ;W
	   * EL TERCERO ES LA LONGITUD DEL SOCKET  EN CUESTION :w
	   *
	   * */    
	        perror("ACCEPT: ");
               continue;
          }
          printf("Conexion en el socket %d (antes %d)\n",ss, s);
          if (fork() == 0) {
          /*AQUI SE EJECUTA EL PROCESO HIJO*/
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
