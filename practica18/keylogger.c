#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	struct input_event ev;
	int fdr,rd; //declaracion de un descriptor de archivos.
	char *teclas ="  1234567890'   qwertyuiop +  asdfghjklñ{} zxcvbnm,.-    "; //caracteres correspondientes a cada tecla
	char *entrada="/dev/input/event1\0"; // se declara la ruta del archivo
	fdr=open(entrada,O_RDONLY); // se abre el archivo, solo lectura 
	if(fdr!=-1){ // validamos si se puede leer eel archivo
		while(1) {
			// se lee del archivo event1 estructuras de tipo input_event y se guardan en ev
			rd = read(fdr,(void*)&ev,sizeof(struct input_event));
			 //si la tecla ha sido presionada y se leyó algo del archivo event1, y el valor del evento corresponde a EV_KEY, es decir ,0
			if(rd>0 && ev.value==0 && ev.type==1)
				printf("%c\n",teclas[ev.code]); //imprime el caracter de la tecla de acuerdo al campo code de la estructura
		}
		if(close(fdr)==-1) fprintf(stderr,"No se pudo cerrar el descriptor de archivo"); //se cierra el descriptor de archivo
	} 
	else fprintf(stderr,"No se pudo abrir o crear el archivo");
}