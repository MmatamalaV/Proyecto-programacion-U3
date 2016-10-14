//mario matamala
//algunas de las funciones son cortesia de nuestro profesor Federio Meza
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//###########################################################################################################################################################
#define MAX_NOM 50
//###########################################################################################################################################################
typedef struct nodo1{
	char n_p_e[50+1];//nombre del programa a ejecutar
	int memoria;//cantidad de memoria que requiere el "programa"
	int inicio;
	int fin;
	struct nodo1 *sgte;//puntero que muestra donde esta el siguiente programa qie se está ejecutando	
}programa;
//###########################################################################################################################################################
typedef struct nodo2{
	int c_m_l;//cantidad de memoria libre
	int inicio;
	int fin;
	struct nodo2 *sgte;
}memlibre;
//###########################################################################################################################################################
int menu(int a){// esta funcion se encarga de mostrar las opciones del menu y retornar una opcion que sera ingresada por el usuario
	printf("\n\n   MENU\n\n\n\n");
	printf("  1)Solicitar memoria para un nuevo programa.\n\n");
	printf("  2)Liberar memoria y terminar un programa.\n\n");
	printf("  3)Mostrar programas en ejecucion.\n\n");
	printf("  4)Mostrar memoria libre.\n\n");
	printf("  0)salir\n\n");
	printf("  ingrese su opcion: ");
	scanf("%d", &a);
	return a;
}
//###########################################################################################################################################################
int sino(int a){//esta funcion se encarga de preguntale al usuario si quiere retirnar al menu
	printf("\n\n\n\n\n\n");
	printf("                Desea volver al MENU\n\n\n\n");     
	printf("	       1)Si              2)No\n\n\n\n\n");
	printf("  ingrese su opcion: ");	
	scanf("%d",&a);
	if (a==2)
		return 0;
	return 1;
}
//###########################################################################################################################################################
void imprimir_programa(programa *i) {//esta funcion se encarga de imprimir todos los programas que es encuentran en ejecucion
	programa *p;

	p = i;
	printf("\n\n\n\n");

	while (p != NULL) {
		printf("####################################################################################\n");
		printf("nombre del programa: %s\n\n", p->n_p_e);
		printf("tamano del programa: %d\n\n", p->memoria);
		printf("el programa esta ocupando el inervalo [%d,%d] en la memoria\n", p->inicio,p->fin);
		printf("####################################################################################\n\n");
		
		p = (*p).sgte;
	}
	printf("\n");
}
//###########################################################################################################################################################
void imprimir_memoria(memlibre *i){//esta funcion se encarga de imprimir todos los espacios de memorias que se encuentran disponibles
   memlibre *p;

   printf("memoria libre: ");
   p = i;
   printf("\n\n");
   while (p != NULL) {
   		printf("####################################################################################\n");
		printf("memoria= %d\n\n", p->c_m_l);
		printf("ubucada en el intervalo[%d,%d]\n\n", p->inicio,p->fin);
		printf("####################################################################################\n");
		p = (*p).sgte;
   }
   printf("\n\n\n\n");
}
//###########################################################################################################################################################
memlibre *trabajo_memoria(memlibre *i, int a){
	memlibre *n;
	n=malloc(sizeof(memlibre));
	n->c_m_l=a;
	n->inicio=0;
	n->fin=a-1;
	n->sgte=i;
	i=n;
	return n;
}
//###########################################################################################################################################################
memlibre *trabajo_memoria3(memlibre *i, programa*j){
	memlibre *nuevo, *p, *q;
   
   	nuevo = malloc(sizeof(memlibre));
   	nuevo->c_m_l= j->memoria;
   	nuevo->inicio=j->inicio;
   	nuevo->fin=j->fin;
   
   	// La lista esta vacia o se inserta al inicio
   	if (i==NULL || j->inicio < i->inicio) {
		nuevo->sgte = i;
      	return nuevo;
   	}

   	// Encuentra el lugar donde hay que insertar
   	// El puntero p se detiene en el nodo anterior a la insercion
   	p = i;
   	q = p->sgte;
   	while (q!=NULL && q->inicio < j->inicio) {
		p = q;
		q = p->sgte;
	}
	nuevo->sgte = p->sgte;
	p->sgte = nuevo;

	return i;
}
//###########################################################################################################################################################
memlibre *trabajo_memoria2(memlibre *i1, programa *i2){
	memlibre *n;
	n=i1;
	n->c_m_l=(n->c_m_l)-(i2->memoria);
	n->inicio+=i2->memoria;

	return n;
}
//###########################################################################################################################################################
int comprovar_espacio(int a, memlibre *i){
	memlibre *p;
   
	p = i;

	while (p!=NULL && p->c_m_l < a) {
		p = p->sgte;
	}
	if (p== NULL){
		return 0;
	}	

	if(p->c_m_l>= a){
		return 1;
	}
}
//###########################################################################################################################################################
programa *insertar_al_inicio(programa *i1, memlibre *i2, int pos) {
	int a,b,c;
	programa *n,*p;
	p=i1;
	n=malloc(sizeof(programa));
	printf("ingrese el nombre de su programa: ");
	scanf("%s",n->n_p_e);//por el momento los nombres no pueden estar separados por espacios
	if (i1!=NULL){
		while(strcmp(p->n_p_e,n->n_p_e)!=0 && p->sgte!=NULL){
		p=p->sgte;
		}
		if(strcmp(p->n_p_e,n->n_p_e)==0){
		printf("\n\n\nEL NOMBRE ESTA REPETIDO\n\n\n");
		system("sleep 1");
		return NULL;
		}
	}
	printf("ingrse el tamaño de su programa: ");
	scanf("%d", &n->memoria);
	n->inicio=pos+1;
	n->fin=pos+n->memoria;
	b=n->memoria;
	
	a=comprovar_espacio(b, i2);

	if(a==1){
		n->sgte=i1;
		i1=n;
		return n; 
	}

	if (a==0){
		printf("no hay espacio suficiente para ejecutar su programa\n");		
		return NULL;
	}
}
//###########################################################################################################################################################

main(int argc, char *argv[]){

	programa *inicio_p, *inicio_p1, *p, *n, *q;
	memlibre *inicio_m;
	int a=0,b;
	int pos=-1;
	char c[MAX_NOM];


	
	if (argc!=2) {
		system("clear");
		printf("\nFaltan componentes en la ejecucion del programa\n\nEl uso correcto es: %s (inserte el tamaño de la memoria)\n\n", argv[0]);
   		system("sleep 2");
   		system("clear");
   		exit(EXIT_FAILURE);
	}

	

	b=atoi(argv[1]);
	inicio_p=NULL;
	inicio_m=NULL;

	
	inicio_m=trabajo_memoria(inicio_m,b);
	system("clear");
	printf("\n\n\n              BIENVENIDO A ESTE PROGRAMA\n\n\n");
	system("sleep 2");
	system("clear");
	do{
		system("clear");
		a=menu(a);
		if (a>0){
			system("clear");
			switch(a){
				case 1:
					printf("Solicitar memoria para un nuevo programa.\n\n\n");
					inicio_p1=insertar_al_inicio(inicio_p, inicio_m,pos);
					if(inicio_p1!=NULL){
						inicio_p=inicio_p1;
						inicio_m=trabajo_memoria2(inicio_m,inicio_p);
						pos+=inicio_p1->memoria;
					}
					a=sino(a);
					break;
				
				case 2:
					printf("Liberar memoria y terminar un programa.\n\n\n");
					if(inicio_p!=NULL){
						printf("Ingrese el nombre del programa que desea terminar: ");
						scanf("%s",c);
						
						p=inicio_p;
						n=p->sgte;
						
						if (strcmp(p->n_p_e,c)==0){
							inicio_m=trabajo_memoria3(inicio_m,p);		
							inicio_p=p->sgte;
						}

						if(p->sgte!=NULL){
							while(strcmp(n->n_p_e,c)!=0 && n->sgte!=NULL){
							p=p->sgte;
							n=p->sgte;
							}
							if(strcmp(n->n_p_e,c)==0){
								inicio_m=trabajo_memoria3(inicio_m,n);
								p->sgte=n->sgte;
							}	
						}
						else{
							printf("\n\n\n   No se ha encontrado un programa con ese nombre\n");
						}
					}
					else{
						printf(".\n\n\n   No hay programas en ejecucion\n");
					}
					a= sino(a);
					break;
				
				case 3:
					printf("Programas en ejecucion.\n\n\n");
					if (inicio_p!=NULL){
						imprimir_programa(inicio_p);
					}
					else{
						printf("no hay programas en ejecucion\n");
					}
					a= sino(a);
					break;
				
				case 4:
					printf("Memoria libre.\n\n\n");
						imprimir_memoria(inicio_m);
						a= sino(a);
				break;
			}
		}
	}while (a>0);
	
	system("clear");
	printf("\n\n\n                GRACIAS POR SU PREFERENCIA\n\n\n");
	system("sleep 1");
	system("clear");
	printf("\n\n\n                     HASTA PRONTO\n\n\n");
	system("sleep 1");
	system("clear");
}
//###########################################################################################################################################################
