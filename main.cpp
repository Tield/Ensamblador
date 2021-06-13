#include <conio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
using namespace std;

//DECLARACION DE FUNCIONES
int menu();
void abrirArchivo();
void mostrarInf();
void numerarLineas();

void analisis();
void aLexico();
void msnPalabra();
void msnNumero();
void comparadorLexico();
void valorEsam();
void valorhexa();


//VARIEBLES GLOBALES
int 	opcMenu;
char 	verificar [] ="prueba.txt";

char 	datos[500];
int 	contLinea = 1;
char 	linea[500];
int 	i=0;
int      p=0;
char    hexadecimal[250];
char    binario[250];
char 	tempPalabra[20];
char 	tempNumero[50];
int 	x=0,y;
//La variable AUX es para comparar las palabra reservadas
char 	aux[20];
char 	temSimb[3];

//Banderas globales
int indicadorN = 0;
int banderaNum=0;
int banderaLet=0;

//BUFFER


//Structura de identificadores
struct indentificador{

    char nom[20];
    char valor[50];
    char tipo[10];
    char use[3];
    //char iden[20];

}ident;
struct indentReser{

    char reser[20];

}reserver;

//Variables del valor del esamblador
int mov,add,ax,bx,cx,dx,Ax,Bx,Cx,Dx;
int special,ro,and2,cmp,sub,AX,BX,CX,DX;

char mov1[20],add1[20],ax1[20],bx1[20],cx1[20],dx1[20],special1[20],or1[20],and1[20],cmp1[20],sub1[20],AX1[20],BX1[20],CX1[20],DX1[20],Ax1[20],Bx1[20],Cx1[20],Dx1[20];
//PROGRAMA PRINCIPAL
int main()
{
    remove("Enumerado.txt");
    remove("tablaSimbolos.txt");
    remove("tablaReservadas.txt");
    remove("hexadecimal.txt");
    remove("binario.txt");
	do
	{
		opcMenu=menu();
		switch(opcMenu){
			case 1:
			abrirArchivo();
			//analisis();
			break;

		    case 2:
               mostrarInf();
            break;

			case 3:
			numerarLineas();
            cout<<"\n\nChecar:[Enumerado.txt]...\n";
            system("pause");
			break;

            case 4:
			analisis();
            system("pause");
			break;

			case 5:
		    	cout<<"\n\nLas tablas se han creado verificar tablaSimbolos.txt y tablaReservadas.txt]...\n";
		    	system("pause");
			break;

			default:
			break;
         	case 6:
        //    fclose(table2);
            //fclose(lectura);
			//fclose(escritura);
		//	fclose(table);
			break;
		}
	}while (opcMenu!=6);

return EXIT_SUCCESS;
}

FILE *lectura = fopen("prueba.txt", "r");
FILE *escritura = fopen("Enumerado.txt", "w+");
FILE *table = fopen("tablaSimbolos.txt","w+");
FILE *table2 = fopen("tablaReservadas.txt","w+");
FILE *hexa=fopen("hexadecimal.txt","w+");
FILE *bina=fopen("binario.txt","w+");


//FUNCIONES
int menu()
{
	system("cls");//clrscr();
	cout<<"\n\tANALIZADOR LEXICO\n\n";
    cout<<"\n\t1. Abrir txt";
	cout<<"\n\t2. Mostrar el codigo ";
	cout<<"\n\t3. enumerar lineas";
	cout<<"\n\t4. Analisis lexico ";
	cout<<"\n\t5. Tabla de simbolos ";
	cout<<"\n\t6. Salir\n";
	cout<<"\n\n\t elige una opcion: ";
	cin>>opcMenu;
	return(opcMenu);
}

void abrirArchivo()
{
     char veri[30];
     int yupi=0;
     cout<<"\nTeclea el nombre del archivo: ";
     cin>>veri;
        lectura = fopen(veri, "r");
		system("cls");//clrscr();
		//Verificamos que el archivo original exista, si no existe cerrar el programa
		if (lectura==NULL){
			cout<<"Error al abrir el archivo de TEXTO 'prueba'...";
			getch();
			//exit(-1);
			yupi=1;
		}
	if(yupi==0)	{
	   cout<<"\nDatos copiados";
	   getch();
    }
}
void mostrarInf()
{
	int x=1;
	system("cls");//clrscr();
	rewind(lectura);
		while (fgets(datos, 500, lectura) != NULL){
			printf("%d  ",x);
			puts(datos);
			x++;
		}
	getch();
}
void numerarLineas()
{
	if(indicadorN==0){
		//clrscr();
		rewind(lectura);
		//Escribimos datos en el nuevo archivo
		while (fgets(datos, 500, lectura) != NULL){
			fprintf(escritura,"%d |     ",contLinea);
			fputs(datos,escritura);
			contLinea++;
		}
		cout<<"\n\nLineas enumerados en nuevo documento TXT...";
		indicadorN=1;
	}
	else{
		system("cls");/*clrscr()*/;cout<<"\n\tLas lineas ya fueron numeradas...";}
	getch();
	fclose(escritura);
}

void analisis()
{
      fprintf(table,"\t\t\t\tTABLA DE SIMBOLOS\t\n");
      fprintf(table,"--------------------------------------------------------------------\n");
      fprintf(table,"TIPO\t");
      fprintf(table,"\tETIQUETA");
      fprintf(table,"\tUSO");
      fprintf(table,"\t\tDIRECCION");
      fprintf(table,"\tVALOR\n");
      fprintf(table2,"\t\t\tTABLA DE PALABRAS RESERVADAS\t\n");
      fprintf(table2,"------------------------------------------------------------------\n");
      fprintf(bina," BINARIOS DEL PROGRAMA \n");
      fprintf(hexa," HEXADECIMAL DEL PROGRAMA \n");
      system("cls");
	rewind(lectura); //Rebobina el archivo de lectura
		while (fgets(datos, 500, lectura) != NULL){
			aLexico();
			valorEsam();
			memset (mov1, 0, sizeof (mov1));
            memset (add1, 0, sizeof (add1));
            memset (ax1, 0, sizeof (ax1));
            memset (bx1, 0, sizeof (bx1));
            memset (cx1, 0, sizeof (cx1));
            memset (dx1, 0, sizeof (dx1));
           	memset (special1, 0, sizeof (special1));
            memset (or1, 0, sizeof (or1));
            memset (and1, 0, sizeof (and1));
            memset (cmp1, 0, sizeof (cmp1));
            memset (sub1, 0, sizeof (sub1));
            memset (AX1, 0, sizeof (AX1));
           	memset (BX1, 0, sizeof (BX1));
            memset (CX1, 0, sizeof (CX1));
            memset (DX1, 0, sizeof (DX1));
			cout<<"\n";
			getch();
				printf("\nBIN= %s",binario);
                    printf("\nHEX= %s \n",hexadecimal);
                    fprintf(bina,"%s \n",binario);
                    fprintf(hexa,"%s \n",hexadecimal);
                    memset(binario,0,250);
                    memset(hexadecimal,0,250);



		}
		//IMPRIMIR ANALISIS DE LA ULTIMA PALABRA DE LA ULTIMA LINEA DEL ARCHIVO
		if(banderaNum==1)	msnNumero();
		if(banderaLet==1)	msnPalabra();
		valorEsam();


	}

void aLexico()
{
	strcpy(linea, datos);
	i=0;

	while (linea[i] != '\0'){
		//ACEPTAR LETRAS  && NUMEROS
		if(isalpha(linea[i]) ||isdigit(linea[i])){
			//Si comieza con NUMEROS:
			if(isdigit(linea[i]) && banderaLet==0){
			tempNumero[x]=linea[i];
			x++;
			banderaNum=1;
			}
				//Si comienza con LETRAS
				else{
					if(banderaNum==1)	msnNumero();
				tempPalabra[x]=linea[i];
				x++;
				banderaLet=1;
				}
		}

//Hacer corte de palabra y numero en CASO DE ESPACIO
		if(isspace(linea[i])){
			if(banderaNum==1)	msnNumero();
			if(banderaLet==1)	msnPalabra();
		}
//Hacer corte de palabra y numero en CASO DE SIMBOLO & imprimir SIMBOLO
		if (ispunct(linea[i])){
			temSimb[0]=linea[i];

			if(banderaNum==1)	msnNumero();
			if(banderaLet==1)	msnPalabra();
        //Imprimir SIMBOLO
				if (strcmp( temSimb, "!" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, admiracion)\n";
				else if (strcmp( temSimb, "�" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, admiracion)\n";
				else if (strcmp(temSimb, "\"" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, comilla doble)\n";
				else if (strcmp( temSimb, "\'" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, comilla simple)\n";
				else if (strcmp( temSimb, "#" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, numerico)\n";
				else if (strcmp( temSimb, "%" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, porcentaje)\n";
				else if (strcmp( temSimb, "&" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, ampersan)\n";
				else if (strcmp( temSimb, "(" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, parentesis izquierdo)\n";
				else if (strcmp( temSimb, ")" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, parentesis derecho)\n";
				else if (strcmp( temSimb, ";" ) == 0)
                {
                    cout<<linea[i]<<"\t\t(Simbolo, punto y coma)\n";

                }

				else if (strcmp( temSimb, ":" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, dos puntos)\n";
				else if (strcmp( temSimb, "." ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, punto)\n";
				else if (strcmp( temSimb, "," ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, coma)\n";
				else if (strcmp( temSimb, "<" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, menor que)\n";
				else if (strcmp( temSimb, ">" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, mayor que)\n";
				else if (strcmp( temSimb, "?" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, interrogacion)\n";
				else if (strcmp( temSimb, "�" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, interrogacion)\n";
				else if (strcmp( temSimb, "{" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, llave abrir)\n";
				else if (strcmp( temSimb, "}" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, llave cerrar)\n";
				else if (strcmp( temSimb, "[" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, corchete izquierdo)\n";
				else if (strcmp( temSimb, "]" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, corchete derecho)\n";
				else if (strcmp( temSimb, "@" ) == 0)
					cout<<linea[i]<<"\t\t(Simbolo, arroba)\n";
				else if (strcmp( temSimb, "+" ) == 0)
					cout<<linea[i]<<"\t\t(Operador, suma)\n";
				else if (strcmp( temSimb, "-" ) == 0)
					cout<<linea[i]<<"\t\t(Operador, resta)\n";
				else if (strcmp( temSimb, "*" ) == 0)
					cout<<linea[i]<<"\t\t(Operador, multiplicacion)\n";
				else if (strcmp( temSimb, "/" ) == 0)
					cout<<linea[i]<<"\t\t(Operador, division)\n";
				else if (strcmp( temSimb, "=" ) == 0)
					cout<<linea[i]<<"\t\t(Operador, igual)\n";
				else
					cout<<linea[i]<<"\t\t(Simbolo)\n";
		}

	i++;

	} //Termina WHILE e imprimimos salto de linea
	cout<<"\n";
}
void msnPalabra(){
	for(y=0; y<x; y++){
		cout<<tempPalabra[y];
	}

	comparadorLexico();
	memset (tempPalabra, 0, sizeof (tempPalabra));//Libera memoria te deja en cero el arreglo
	banderaLet=0;
	x=0;
	getch();

}
void msnNumero(){
	for(y=0; y<x; y++){
		cout<<tempNumero[y];
	}
	fprintf(table,"\n");
	cout<<"\t\t(Numero)\n";
	strcpy(ident.valor,tempNumero);
    fprintf(table,"\t%s",ident.valor);
//Libera memoria te deja en cero el arreglo
	memset (tempNumero, 0, sizeof (tempNumero));
	banderaNum=0;
	x=0;
	getch();
}
void comparadorLexico()
{
     int marca=0;
	strcpy(aux, tempPalabra);
	if  (strcmp( aux, "mov" ) == 0
		||strcmp(aux, "add" ) == 0
		||strcmp(aux, "ax" ) == 0
		||strcmp(aux, "bx" ) == 0
		||strcmp(aux, "cx" ) == 0
		||strcmp(aux, "dx" ) == 0
		||strcmp(aux, "special" ) == 0
		||(strcmp(aux, "org" ) == 0
		||strcmp(aux, "and" ) == 0
		||strcmp(aux, "cmp" ) == 0
		||strcmp(aux, "sub" ) == 0
		||strcmp(aux, "AX" ) == 0
		||strcmp(aux, "BX" ) == 0
		||strcmp(aux, "CX" ) == 0
		||strcmp(aux, "DX" ) == 0
        ||strcmp(aux, "Ax" ) == 0
		||strcmp(aux, "Bx" ) == 0
		||strcmp(aux, "Cx" ) == 0
		||strcmp(aux, "Dx" ) == 0
		||strcmp(aux, "[BX]" ) == 0))

{
cout<<"\t\t(Palabra reservada de ensamblador)\n";
	  if (strcmp( aux, "mov" ) == 0)
       {cout<<"\t\tBINARIO\n";
        cout<<linea[i]<<"\t\t(110)\n";
        strcpy(mov1, "110");
        strcat(binario, " 110");
        mov=110;
        cout<<"\t\tHEXADECIMAL\n";
        cout<<linea[i]<<"\t\t(6)\n";
        strcpy(mov1, "6");
        strcat(hexadecimal, " 6");
        mov=6;
        }
else if(strcmp( aux, "add" ) == 0)
        {cout<<"\t\tBINARIO\n";
        cout<<linea[i]<<"\t\t(010)\n";
        strcpy(add1, "010");
         strcat(binario, " 010");
        add=010;
        cout<<"\t\tHEXADECIMAL\n";
        cout<<linea[i]<<"\t\t(2)\n";
        strcpy(add1, "2");
         strcat(hexadecimal, " 6");
        add=2;
        }
else if (strcmp( aux, "ax" ) == 0)
        {cout<<"\t\tBINARIO\n";
        cout<<linea[i]<<"\t\t(00)\n";
        strcpy(ax1, "00");
         strcat(binario, " 00");
        ax=00;
        cout<<"\t\tHEXADECIMAL\n";
        cout<<linea[i]<<"\t\t(0)\n";
        strcpy(ax1, " 0");
         strcat(hexadecimal, " 0");
        ax=0;
        }
else if(strcmp( aux, "bx" ) == 0)
       {cout<<"\t\tBINARIO\n";
        cout<<linea[i]<<"\t\t(01)\n";
        strcpy(bx1, "01");
         strcat(binario, " 01");
        bx=01;
        cout<<"\t\tHEXADECIMAL\n";
        cout<<linea[i]<<"\t\t(1)\n";
        strcpy(bx1, "1");
         strcat(hexadecimal, " 1");
        bx=1;
        }

else if (strcmp( aux, "cx" ) == 0)
        {cout<<"\t\tBINARIO\n";
        cout<<linea[i]<<"\t\t(10)\n";
        strcpy(cx1, "10");
         strcat(binario, " 10");
        cx=10;
        cout<<"\t\tHEXADECIMAL\n";
        cout<<linea[i]<<"\t\t(2)\n";
        strcpy(cx1, "2");
         strcat(hexadecimal, " 2");
        cx=2;
        }

else if(strcmp( aux, "dx" ) == 0)
        {cout<<"\t\tBINARIO\n";
        cout<<linea[i]<<"\t\t(11)\n";
        strcpy(dx1, "11");
         strcat(binario, " 11");
        dx=11;
        cout<<"\t\tHEXADECIMAL\n";
        cout<<linea[i]<<"\t\t(3)\n";
        strcpy(dx1, "3");
         strcat(hexadecimal, " 3");
        dx=3;
        }

else if (strcmp( aux, "special" ) == 0)
       {cout<<"\t\tBINARIO\n";
        cout<<linea[i]<<"\t\t(000)\n";
        strcpy(special1, "000");
         strcat(binario, " 000");
        special=000;
        cout<<"\t\tHEXADECIMAL\n";
        cout<<linea[i]<<"\t\t(0)\n";
        strcpy(special1, "0");
         strcat(hexadecimal, " 0");
        special=0;
        }

else if(strcmp( aux, "org" ) == 0)
        {cout<<"\t\tBINARIO\n";
        cout<<linea[i]<<"\t\t(001)\n";
        strcpy(or1, "001");
         strcat(binario, " 001");
        ro=001;
        cout<<"\t\tHEXADECIMAL\n";
        cout<<linea[i]<<"\t\t(1)\n";
        strcpy(or1, "1");
         strcat(hexadecimal, " 1");
        ro=1;
        }

else if (strcmp( aux, "and" ) == 0)
       {cout<<"\t\tBINARIO\n";
        cout<<linea[i]<<"\t\t(010)\n";
        strcpy(and1, "010");
         strcat(binario, " 010");
        and2=010;
        cout<<"\t\tHEXADECIMAL\n";
        cout<<linea[i]<<"\t\t(2)\n";
        strcpy(and1, "2");
         strcat(hexadecimal, " 2");
        and2=2;
        }

else if(strcmp( aux, "cmp" ) == 0)
        {cout<<"\t\tBINARIO\n";
        cout<<linea[i]<<"\t\t(011)\n";
        strcpy(cmp1, "011");
         strcat(binario, " 011");
        cmp=011;
        cout<<"\t\tHEXADECIMAL\n";
        cout<<linea[i]<<"\t\t(3)\n";
        strcpy(cmp1, "3");
         strcat(hexadecimal, " 3");
        cmp=3;
        }
else if (strcmp( aux, "sub" ) == 0)
        {cout<<"\t\tBINARIO\n";
        cout<<linea[i]<<"\t\t(100)\n";
        strcpy(sub1, "100");
         strcat(binario, " 100");
        sub=100;
         cout<<"\t\tHEXADECIMAL\n";
        cout<<linea[i]<<"\t\t(4)\n";
        strcpy(sub1, "4");
         strcat(hexadecimal, " 4");
        sub=4;
        }

else if(strcmp( aux, "Ax" ) == 0)
    {cout<<"\t\tBINARIO\n";
	cout<<linea[i]<<"\t\t(000)\n";
	strcpy(Ax1, "000");
	 strcat(binario, " 000");
    Ax=000;
    cout<<"\t\tHEXADECIMAL\n";
    cout<<linea[i]<<"\t\t(0)\n";
	strcpy(Ax1, "0");
	 strcat(hexadecimal, " 0");
    Ax=0;}

    if (strcmp( aux, "Bx" ) == 0)
    {cout<<"\t\tBINARIO\n";
	cout<<linea[i]<<"\t\t(001)\n";
	strcpy(Bx1, "001");
	strcat(binario, " 001");
    Bx=001;
    cout<<"\t\tHEXADECIMAL\n";
   cout<<linea[i]<<"\t\t(1)\n";
	strcpy(Bx1, "1");
	strcat(hexadecimal, " 1");
    Bx=1;
    }

else if(strcmp( aux, "Cx" ) == 0)
    {cout<<"\t\tBINARIO\n";
	cout<<linea[i]<<"\t\t(010)\n";
	strcpy(Cx1, "010");
	strcat(binario, " 010");
    Cx=010;
    cout<<"\t\tHEXADECIMAL\n";
    cout<<linea[i]<<"\t\t(2)\n";
	strcpy(Cx1, "2");
	strcat(hexadecimal, " 2");
    Cx=2;
    }

if (strcmp( aux, "Dx" ) == 0)
   {cout<<"\t\tBINARIO\n";
	cout<<linea[i]<<"\t\t(011)\n";
	strcpy(Dx1, "011");
	strcat(binario, " 011");
    Dx=011;
    cout<<"\t\tHEXADECIMAL\n";
    cout<<linea[i]<<"\t\t(3)\n";
	strcpy(Dx1, "3");
	strcat(hexadecimal, " 3");
    Dx=3;
    }
 	   marca=1;
	    strcpy(reserver.reser,tempPalabra);
        fprintf(table2,"\t%s\n",reserver.reser);
	}
    else if (marca == 0){
        cout<<"\t\t(etiqueta)\n";
       fprintf(table,"\t\t");
        //fprintf(table,"\n");
        strcpy(ident.nom,tempPalabra);
        fprintf(table,"%s\t",ident.nom);
        fprintf(table,"\tVariable");
        fprintf(table,"\t%d\t",&tempPalabra);
    }
}

void valorEsam()
{

     cout<<"Valor en hexadecimal: \n";
     cout<<mov1<<add1<<special1<<or1<<and1<<cmp1<<sub1<<ax1<<bx1<<cx1<<dx1<<AX1<<BX1<<CX1<<DX1;
     cout<<"\n-----------------------------";

}
