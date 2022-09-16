function banner(){
echo "##### #    # #### #    # #   # #     # ##### #   # ####\n" 
echo "#   # ##   # #  # ##   #  # #  ##   ## #   # #   # #   \n"
echo "##### # #  # #  # # #  #   #   # # # # #   # #   # ####\n"
echo "#   # #  # # #  # #  # #   #   #  #  # #   # #   #    #\n"
echo "#   # #   ## #  # #   ##   #   #     # #   # #   #    #\n "
echo "#   # #    # #### #    #   #   #     # ##### ##### ####\n"
echo "Autor:Aldair Martinez Alias H4ctr0n731"
printf "\n"
}
function extraccionx(){	
	ports=$( sudo find "/home/$USER" -name "extraccion.tmp" -type f -print0 | cd /home/$USER && cat extraccion.tmp | grep -oP '\d{1,9}/tcp' | awk '{print $0}' FS='/' | tr ' ' '/' | column -t)
	ip_address=$( cat /home/$USER/extraccion.tmp | grep -oP '\d{1,3}\.\d{1,3}\.\d{0,3}\.\d{1,3}' | sort -u | head -n 1)
	echo -e "\n[*] Extracting information...\n" > info.tmp
	echo -e "\nt[*] IP Address: $ip_address"  > info.tmp
	echo -e "\n[*] Open ports: $ports\n"  > info.tmp
	echo $ports | tr -d '\n' | xclip -sel clip
	echo -e "[*] Ports copied to clipboard\n"  > info.tmp
	
}
function escanear_direcciones(){
      host_ip=$1
      echo "Escanenaod red porfavor espere  maximo 30 segundos "
      nmap -p- --open -T5 -v -n -sS  $host_ip  --oG allports > extraccion.tmp
      echo "Escaner terminado" 
}
function info_fichero(){
	if [ -z $1 ]; then
   		error "Se debe de pasar el nombre del fichero"  	
	fi
	printf "Analizando  la informacion mas relevante del fichero"
        fichero=$1
	echo -n "$fichero"
	if [ -d $fichero ]; then
		printf "Es un directorio"
	elif [ -f  $fichero ]; then
		printf "Es un fichero estandar"
	else:
		printf "es otro tipo de fichero"
	fi
       permisos=$(ls -lhd $fichero | tr -s " " | cut -d " " -f1)
       propietario=$(ls -lhd $fichero  | tr -s " " | cut -d " " -f3)
       grupo=$(ls -lhd $fichero | tr -s " " | cut -d " " -f4 )
       tam=$(ls -lhd $fichero | tr -s " "  | cut -d " " -f5 )      
       echo "\n Los permisos de $fichero son $permisos"
       echo "\n El propietario de $fichero es $propietario"
       echo "\n El grupo de $fichero es $propietario"
       echo "\n Tam de $fichero es $tam"
}
function error(){
	echo "[ERROR] - $1" 
	exit 1
}

function extraer_direcciones_de_interfaces(){
     echo "Extraayendo direcciones de interfaces de red"
	 direccion_ip=$( /bin/ip -4 -f inet address | grep -v 127.0.0.1 | awk 'match($0, /([0-9]+\.[0-9]+\.[0-9]+\.[0-9]+)/) {print substr($0,RSTART,RLENGTH)}' )
	 direcciones_ip=$( /bin/ip -4 -f inet address | grep -oE "\b([0-9]{1,3}\.){3}[0-9]{1,3}\b" )
	 echo "Las direcciones de red de red son ---> ${direcciones_ip[@]} "
     echo "Tu direccion ip es---> $direccion_ip"
}
banner
printf "Eliga una opcion";
printf "\n 1.-Ingresar direccion ip"
printf "\n 2.-Extraer la informacion de los puertos de la direccion ip anterior"
printf "\n 3.-Ver informacion de un fichero"
printf "\n 4.-Ver informacion de las direccion interfaces de red de tu sistema"
printf "\n 5.-Extraer la direccion ip del router"
printf "\n 6.-Extraer la direccion ip de tu sistema"
read opcion
if [ $opcion == 1 ]; then
	printf "Ingrese una sola direccion ip"	
	read direccion_user
	escanear_direcciones $direccion_user 
	sleep 0.8s
elif [ $opcion == 2 ]; then
	prinf "Extrayendo informacion de los puertos..."
	extraccionx 
	sleep 0.8s
elif [ $opcion == 3 ]; then
	printf "Ingrese nombre del fichero"	
	read fichero
	sleep 0.8s
	info_fichero $fichero
elif [ $opcion == 4 ]; then
	printf "?"
elif [ $opcion == 5 ]; then
	extraer_direcciones_de_interfaces
else:
	echo "opcion incorrecta"
fi
