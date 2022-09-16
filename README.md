# Hacktr0n_ports
Herramienta de automatizacion de puertos usando nmap  Estamos!?
<br> #Forma de ejecutar el script extraccion.sh <br>
1.-Primeramente necesitara ejecutar la herramienta de extracion de la siguiente manera
sudo sh extraccion.sh  <br>
2.-En caso de no poder ejecutarse o realizarse alguna operacion simplemente cambie los permisos <br>
Eso lo puede conseguir con el comando   <br>
sudo chmod 755 extraccion.sh  <br>
3.-Al ejecutarlo podra realiar la siguiente acciones <br>
  *Ingresar una direccion ip por ejemplo 192.168.100.36   <br>
  *Obtener informacion de los puertos de esa direccion ip <br>
  *Obtener las direcciones de las interfaces de red de tu sistema <br>
  *Obtener tu direccion ip de tu sistema  <br>
  *Obtener la direccion del router (gateway) de tu sistema por lo general es la 192.168.0.1 pero puede variar dependiendo  <br>
  de commpania  de proovedor de internet (ISP) hayas contratado o donde estes conctado nino rata mmmmmmm jaja XD  <br>
#Forma de uso del chat tcp <br> 
El chat contiene dos archivos los cuales son graficas_cliente_qt.cpp <br>
 *El primero llamado cliente_tcp.cpp
 *El segundo llamado servidor_tcp.cpp
Los cuales pueden pueden compilarse de la siguiente manera
<br> Para cliente_tcp.cpp
 <br> sudo g++ -DTEST --debug cliente_tcp.cpp -o client
<br> Para servidor_tcp.cpp
 <br> sudo g++ -DTEST --debug servidor_tcp.cpp -o server
Para ejecutar el cliente 
  ./client
  
Para ejecutar el servidor 
  ./server
  
 Nota Importante : El cliente no funcionara a menos de que el servidor este corriendo antes en tu maquina 
