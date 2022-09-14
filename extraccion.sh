
function extraccionx(){	
	echo "ESTO ES SER ANONYMOUS"
	ports=$( sudo find "/home/aldair" -name "extraccion.tmp" -type f -print0 | cd /home/aldair && cat extraccion.tmp | grep -oP '\d{1,9}/tcp' | awk '{print $0}' FS='/' | tr ' ' '/' | column -t)
	ip_address=$( cat /home/aldair/extraccion.tmp | grep -oP '\d{1,3}\.\d{1,3}\.\d{0,3}\.\d{1,3}' | sort -u | head -n 1)
	echo -e "\n[*] Extracting information...\n" > info.tmp
	echo -e "\t[*] IP Address: $ip_address"  > info.tmp
	echo -e "\t[*] Open ports: $ports\n"  > info.tmp
	echo $ports | tr -d '\n' | xclip -sel clip
	echo -e "[*] Ports copied to clipboard\n"  > info.tmp
	cat extraccion.tmp;
	echo "Nombre fichero"
	read nombre_fichero
        info_usuario $nombre_fichero
}
function escanear_direcciones(){
      host_ip=$1
      echo "Escanenaod red porfavor espere  maximo 30 segundos "
      nmap -p- --open -T5 -v -n -sS  $host_ip  --oG allports > extraccion.tmp
      echo "Escaner terminado"
      extraccionx 

}
function info_usuario(){
	if [ -z $1 ]; then
   		error "se debe de pasar el nombre del usuario"  	
	fi
	printf "Analizando  la informacion mas relevante del ususario"
        fichero $1
	echo -n "$fichero"
	if [ -d $fichero ]; then
		printf "Es un directorio"
	elif [ -f  $fichero ]; then
		printf "Es un fichero estandar"
	else:
		printf "es otro tipo de fichero"
	fi
       permisos=$(ls -lhd $fichero | tr -s " " | cut -d " " -f1)
       propietario=$(ls -lhd $fichero  | tr -s " " | cut -d " " -f3)`
       grupo=$(ls -lhd $fichero | tr -s " " | cut -d " " -f4 )
       tam=$(ls -lhd $fichero | tr -s " "  | cut -d " " -f5 )      
       echo "Los permisos de $fichero son $permisos"
       echo "El propietario de $fichero es $propietario"
       echo "El grupo de $fichero es $propietario"
       echo "Tam de $fichero es $tam"
}
function error(){
	echo "[ERROR] - $1" 
	exit 1
}
printf "Inggrese direccion ip"
read direccion_user
escanear_direcciones $direccion_user 
