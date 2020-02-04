#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include<windows.h>
#include<time.h>
#define tam 15
#define lar 30
#define list 20
#define p 200

//using namespace std;

//------------------------------------ESTRUCTURAS DE DATOS-----------------------------------------------
struct direccion
{
	char colonia[lar];
	char ciudad[lar];
	char departamento[lar];
	char telefono[8];
};
typedef struct direccion info_Dir;

struct producto
{
	int cod_prod;
	int cod_provee;
	int cantidad;
	char nom_prod[lar];
	double precio;
};

struct orden{
	int cod_prod;
	char nom_prod[lar];
	int cantidad;
	double precio;
};

struct proveedores
{
	int cod_provee;
	char nom_provee[lar];
	info_Dir direccion;
};

struct usuario
{
	int cod_user;
	char nom_user[lar];
	char ape_user[lar];
	char usuario[tam];
	char clave[tam];
	char rol_empleado[lar];
	info_Dir direccion;
};

typedef struct detalle_factura{
	int codigo;
	char nom_prod[lar];
	int cantidad;
	double precio;
	double total;
	struct detalle_factura* siguiente;
}detalle_factura;

struct det_factura{
	int codigo;
	char nom_prod[lar];
	int cantidad;
	double precio;
	double total;
};
typedef struct det_factura lista_factura;

struct factura
{
	int cod_factura;
	char nom_fac[lar];
	char fecha[128];
	char hora[128];
	double subtotal;
	double isv;
	double grantotal;
	lista_factura lista[list];
};

struct cierre{
	char fecha[128];
	char hora_final[128];
	int total_fac;
	double total_dia;
};


//**************************************************************************************************


typedef struct usuario datos_usuario;
typedef struct proveedores datos_provee;
typedef struct producto datos_produc;
typedef struct factura datos_fac;
typedef struct cierre datos_caja;

datos_produc info_produc;
datos_usuario info_user;
datos_provee info_pro;
datos_fac info_fac;
datos_caja info_caja;
detalle_factura* inicio = NULL;
FILE *datUsuario;
FILE *datosSM;
char resp = 'S';
int smenu =0;

//--------------------------------------POSICION EN LA PANTALLA------------------------------------
void gatoxy(int x, int y)
{
	HANDLE acomodador;
	COORD cordenada;
	acomodador = GetStdHandle(STD_OUTPUT_HANDLE);
	cordenada.X= x;
	cordenada.Y= y;
	SetConsoleCursorPosition(acomodador, cordenada);
}
//*************************************************************************************************
//------------------------------------VALIDACION MAYORES A 0---------------------------------------
bool entero_cero(int num){
	bool salida = false;
	if(num < 0){
		printf("\nERROR. Dato no puede ser negativo.");
		Sleep(1500);
		return true;	
	}
		else
			return false;
}
//*************************************************************************************************
//-----------------------------------VALIDACION ENTEROS--------------------------------------------
int validar_entero(char numero[])
{
    int i=0, num=0, j, salida;
	
	j=strlen(numero);
	
	while(i<j && num==0)
	{
		if(isdigit(numero[i])!=0)
		{
			i++;
		}
		else
		{
			num=1;
		}
	}
	if(num!=0)
				{
					printf("\nERROR. Solo se permiten numeros.\n");
					Sleep(1000);
					salida=0;
				}
				else
					salida=atoi(numero);
	return salida;
}

//*************************************************************************************************

//-----------------------------VALIDACION RESPUESTA DE SALIDA--------------------------------------
char validacion_respuesta(){
	do{
	system("cls");
	  printf("\n\n\tDESEA INGRESAR OTRO DATO? [S o N]: ");
	  scanf("%s", &resp);
	  
	  resp=toupper(resp);
	  
	  if(resp!='S' && resp!='N')
	  {
	    printf("\nERROR. **>>Ingrese una opcion valida<<\n");
	    system("pause");
      }
	  
	}while((resp!='S')&& (resp!='N'));
	return resp;
}
//********************************************************************************************************

//-----------------------------------VALIDACION DE RESPUESTA---------------------------------------------
char vali_resp(char valor){
	  valor=toupper(valor);
	  
	  if(valor!='S' && valor!='N')
	  {
	    printf("\nERROR. >>Ingrese una opcion valida<<\n");
	    system("pause");
      }
	return valor;
}
//*******************************************************************************************************
//-----------------------------------TIEMPO DEL SISTEMA--------------------------------------------------
void fecha_tiempo(char fecha[128]){
	time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        strftime(fecha,128,"%d/%m/%y",tlocal);
        
}
void hora_tiempo(char hora[128]){
	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	strftime(hora,128,"%H:%M:%S",tlocal);
}
//*******************************************************************************************************
//-----------------------------------VALIDACION DE MENUS-------------------------------------------------
void vali_menu(int in, int min, int max){
			if(in < min || in > max){
			printf("\nERROR. >>Opcion No Validad. Ingrese [%d hasta %d]<<\n", min, max);
			system("pause");
		}
}
//*******************************************************************************************************
//-----------------------------------------VALIDACION DE NUMEROS-----------------------------------------
int validar_numero(char numero[])
{
    int i=0, num=0, j;
	
	j=strlen(numero);
		while(i<j && num==0)
		{
			if(isdigit(numero[i])!=0)
				i++;
			else
				num=1;
		}
		if(num!=0){
			printf("\nERROR. Ingrese solo numeros\n");
			return num;	
		}
		else if(j!=8){
				printf("\nERROR. Ingrese 8 digitos del numero de telefono\n");
				num=1;
				return num;
			}
}
//**********************************************************************************************************
//---------------------------------------VALIDACION DE LETRAS-----------------------------------------------
int validar_letras(char cadena[lar])
{
	int i=0, let=0, j;
	
	j=strlen(cadena);
	
	while(i<j && let==0)
	{
		if(isalpha(cadena[i])!=0)
			i++;
		else
			let=1;
	}
	if(let!=0)
		printf("\n\t[ERROR:] Ingrese solo letras\n");			
	return let;
}
//********************************************************************************************************
//------------------------------------VALIDACION DE ENTERO------------------------------------------------
int validar_num(int numero){
	
	if(isdigit(numero) != 0)
		return numero;
		else{
			printf("\nnumero");
			system("pause");
			numero = 0;
			return numero;
		}
			
}
//---------------------------------CUENTA DE REGISTROS----------------------------------------------------
int cuenta(FILE *datUsuario){
	
	int cont=0;
  
       datUsuario = fopen("empleado.dat","r+b");
       fseek(datUsuario,0,0);
       while(!(feof(datUsuario)))
       {fread (&info_user,sizeof(info_user),1, datUsuario);        
                 cont++;      
       }        
       fclose(datUsuario);
       
       return cont;
}
int cuenta2(FILE *datosSM){
	
	int cont=0;
  
       datosSM = fopen("proveedores.dat","r+b");
       fseek(datosSM,0,0);
       while(!(feof(datosSM)))
       {fread (&info_pro,sizeof(info_pro),1, datosSM);        
                 cont++;      
       }        
       fclose(datosSM);
       
       return cont;
}
int cuenta3(FILE *datosSM){
	
	int cont=0;
  
       datosSM = fopen("productos.dat","r+b");
       fseek(datosSM,0,0);
       while(!(feof(datosSM)))
       {fread (&info_produc,sizeof(info_produc),1, datosSM);        
                 cont++;      
       }        
       fclose(datosSM);
       
       return cont;
}
int cuenta4(FILE *datosSM){
	
	int cont=0;
  
       datosSM = fopen("facturas.dat","r+b");
       fseek(datosSM,0,0);
       while(!(feof(datosSM)))
       {fread (&info_fac,sizeof(info_fac),1, datosSM);        
                 cont++;      
       }        
       fclose(datosSM);
       
       return cont;
}
int cuenta5(FILE *datosSM){
	int cont=0;
  
       datosSM = fopen("cierre_caja.dat","r+b");
       fseek(datosSM,0,0);
       while(!(feof(datosSM)))
       {fread (&info_caja,sizeof(info_caja),1, datosSM);        
                 cont++;      
       }        
       fclose(datosSM);
       
       return cont;
}

//********************************************************************************************************
//-----------------------------AGREGAR NUEVO USUARIO------------------------------------------------------
void agregar_Nuevouser(FILE *datUsuario, datos_usuario info_user)
{
	do{
		int codigo=0, let;
		char cod[6];
		bool llave = false;
	
		   system("cls");
		   do{
		   	system("cls");
		   printf("\n\t----CREAR NUEVO USUARIO----");
		   printf("\nIngrese el codido del empleado: ");
		   scanf("%s", &cod);
		   codigo = validar_entero(cod);
			}while(codigo == 0);
			llave=false;
		       datUsuario = fopen("empleado.dat","r+b");
		       fseek(datUsuario,0,0);
		       while(!(feof(datUsuario)))
		       {fread (&info_user,sizeof(info_user),1,datUsuario);         
		          if(info_user.cod_user==codigo){
		             llave=true;     
		          }   
		       }        
		       fclose(datUsuario);
		       
		       if (llave==false){  
		       printf("\n\t----INFORMACION DEL USUARIO----");
		       info_user.cod_user = codigo;
		       do
						{
							printf("\nIngrese el nombre del usuario: ");
		                    scanf("%s", &info_user.nom_user);
							let = validar_letras(info_user.nom_user);
						}while(let==1);	
		      
		                do
						{
							 printf("\nIngrese el apellido del usuario: ");
		                     scanf("%s", &info_user.ape_user);
							 let = validar_letras(info_user.ape_user);
						}while(let==1);	
		               do
						{
							 printf("\nIngrese un usuario: ");
		                     scanf("%s", &info_user.usuario);
						     let = validar_letras(info_user.usuario);
						}while(let==1);	
							 printf("\nIngrese una clave: ");
		                     scanf("%s", &info_user.clave);
		                do
						{
							 printf("\nIngrese el rol del empleado: ");
		                     scanf("%s", &info_user.rol_empleado);
							let = validar_letras(info_user.rol_empleado);
						}while(let==1);	
		       printf("\n\t---INFORMACION DE DIRECCION---");
			            do
						{
							 printf("\nIngrese la colonia: ");
			                 scanf("%s", &info_user.direccion.colonia);
							let = validar_letras(info_user.direccion.colonia);
						}while(let==1);	
		                do
						{
							 printf("\nIngrese la ciudad: ");
		                     scanf("%s", &info_user.direccion.ciudad);
							let = validar_letras(info_user.direccion.ciudad);
						}while(let==1);	
		                do
						{
							 printf("\nIngrese el departamento: ");
		                     scanf("%s", &info_user.direccion.departamento);
							 let = validar_letras(info_user.direccion.departamento);	
						}while(let==1);	
						do{
							printf("\nIngrese el numero de telefono: ");
		       				scanf("%s", &info_user.direccion.telefono);
		       				let = validar_numero(info_user.direccion.telefono);
						}while(let==1);
		            datUsuario = fopen("empleado.dat","r+b");
		            fseek (datUsuario,0,SEEK_END);
		            fwrite(&info_user, sizeof(info_user),1,datUsuario);
		            fclose(datUsuario);
		      
		      }else{
		          system("cls");
		          printf("\nADVERTENCIA. >>La informacion ingresada ya existe.<<\n");
		          system("pause");
		      }
		    validacion_respuesta();
	  }while(resp=='S');
}
//********************************************************************************************************
//---------------------------------REPORTE USUARIO--------------------------------------------------------
void reporte_usuario(FILE *datUsuario)
{

   int cont=1;
   int contar=cuenta(datUsuario);
   system("cls");
   printf("\n\t-----REPORTE DE EMPLEADOS----");
       
       datUsuario = fopen("empleado.dat","r+b");
       fseek(datUsuario,0,0);
       while((!(feof(datUsuario)))&&(cont<contar))
       {
	   fread (&info_user,sizeof(info_user),1,datUsuario);        
                       
          printf("\nEMPLEADO #%d", cont);
          printf("\nCodigo del empleado: %d", info_user.cod_user);
          printf("\nNombre del empleado: %s %s", info_user.nom_user, info_user.ape_user);
          printf("\nRol del usuario: %s", info_user.rol_empleado);
          printf("\n---------DIRECCION--------------\n");
          printf("Direccion: %s; %s - %s", info_user.direccion.colonia, info_user.direccion.ciudad, info_user.direccion.departamento);
          printf("\nTelefono: %s", info_user.direccion.telefono);
          printf("\n******************************************************************************\n");
          cont++;
       }  
	   printf("\n***************************   FIN DE REPORTE *********************************\n\n"); 
       fclose(datUsuario);  
       system("pause");

}
//********************************************************************************************************
//----------------------------------------BUSCADOR DE USUARIO---------------------------------------------
void buscar_user(FILE *datUsuario, datos_usuario info_user){
	do{
		bool alerta = false;
		int cod_emple = 0;
		char cod_veri[6];
		char nom[lar];
		char ape[lar];
		char usuario[tam];
		char clave[tam];
		char rol_empleado[lar];	
		char colonia[lar];
		char ciudad[lar];
		char departamento[lar];
		char telefono[8];
		int cont=1;
		int contar=cuenta(datUsuario);

	   system("cls");
	   printf("\n\t-----BUSCAR EMPLEADO-----");
	   printf("\nIndique el codigo del empleado: ");
	   scanf("%s", &cod_veri);
	   cod_emple = validar_entero(cod_veri);
	     
	       datUsuario = fopen("empleado.dat","r+b");
	       fseek(datUsuario,0,0);
	       while((!(feof(datUsuario)))&&(cont<contar))
	       {fread (&info_user,sizeof(info_user),1,datUsuario);       
	          if(info_user.cod_user ==cod_emple){
              alerta=true;  
			  strcpy(nom, info_user.nom_user);   
              strcpy(ape, info_user.ape_user);
              strcpy(usuario, info_user.usuario);
              strcpy(clave, info_user.clave);
              strcpy(rol_empleado, info_user.rol_empleado);
              strcpy(colonia, info_user.direccion.colonia);
              strcpy(ciudad, info_user.direccion.ciudad);
              strcpy(departamento, info_user.direccion.departamento);
              strcpy(telefono, info_user.direccion.telefono);
          	}  
          	cont++;
	       }        
	       fclose(datUsuario); 
	       
	       if(alerta==false){
	       system("cls");
	       printf("\n\tERROR.  >>No se encontro el empleado<<\n");
	       }else{
	              printf("\nRESULTADO DE EMPLEADO");
		          printf("\nCodigo del empleado: %d", cod_emple);
		          printf("\nNombre del empleado: %s %s", nom, ape);
		          printf("\nRol del usuario: %s", rol_empleado);
		          printf("\n---------DIRECCION--------------\n");
		          printf("Direccion: %s; %s - %s", colonia, ciudad, departamento);
		          printf("\nTelefono: %s", telefono);
	       }
	    printf("\n**************************** FIN DE BUSQUEDA ***********************************\n");
		system("pause"); 
		validacion_respuesta();
	}while(resp=='S');
}
//********************************************************************************************************
//---------------------------AGREGAR NUEVO PROVEEDOR------------------------------------------------------
void agregar_NuevoProvee(FILE *datosSM, datos_provee info_pro)
{
	
	do{
		int codigo=0, let;
		char cod_valid[6];
		bool llave = false;
	   system("cls");
	   do{
	   printf("\n\t----CREAR NUEVO PROVEEDOR----");
	   printf("\nIngrese el codido del Proveedor: ");
	   scanf("%s", &cod_valid);
	   codigo = validar_entero(cod_valid);
		}while(codigo == 0);
		llave=false;
	       datosSM = fopen("proveedores.dat","r+b");
	       fseek(datosSM,0,0);
	       while(!(feof(datosSM)))
	       {
		   	fread (&info_pro,sizeof(info_pro),1,datosSM);         
	    	if(info_pro.cod_provee==codigo)
	             llave=true;     
	       }        
	       fclose(datosSM);
	       
	       if (llave==false){  
	       printf("\n\t----INFORMACION DEL PROVEEDOR----");
	       info_pro.cod_provee = codigo;
	       do{
		    	printf("\nIngrese el nombre del proveedor: ");
		       	scanf("%s", &info_pro.nom_provee);
		       	let = validar_letras(info_pro.nom_provee);
	       }while(let==1);
	       printf("\n\t---INFORMACION DE DIRECCION---");
	       do{
	       		printf("\nIngrese el lugar: ");
		   		scanf("%s", &info_pro.direccion.colonia);
		   		let = validar_letras(info_pro.direccion.colonia);
	       }while(let==1);
	       do{
	       		printf("\nIngrese la ciudad: ");
	       		scanf("%s", &info_pro.direccion.ciudad);
	       		let = validar_letras(info_pro.direccion.ciudad);
	       }while(let==1);
	       do{
	       		printf("\nIngrese el departamento: ");
	       		scanf("%s", &info_pro.direccion.departamento);
	       		let = validar_letras(info_pro.direccion.departamento);
	       }while(let==1);
	       do{
	       		printf("\nIngrese el numero de telefono: ");
	       		scanf("%s", &info_pro.direccion.telefono);
	       		let = validar_numero(info_pro.direccion.telefono);
	       }while(let==1);
	            datosSM = fopen("proveedores.dat","r+b");
	            fseek (datosSM,0,SEEK_END);
	            fwrite(&info_pro, sizeof(info_pro),1,datosSM);
	            fclose(datosSM);
	      
	      }else{
	          system("cls");
	          printf("\nADVERTENCIA. >>La informacion ingresada ya existe.<<\n");
	          system("pause");
	      }
			validacion_respuesta();
	}while(resp=='S');
}
//********************************************************************************************************
//-------------------------------REPORTE DE PROVEEDORES---------------------------------------------------
void reporte_provee(FILE *datosSM)
{

   int cont=1;
   int contar=cuenta2(datosSM);
   system("cls");
   printf("\n\t-----REPORTE DE PROVEEDORES----");
       
       printf("\n\tCODIGO\t | NOMBRE\t | DIRECCION\t\t | TELEFONO\t |");
       datosSM = fopen("proveedores.dat","r+b");
       fseek(datosSM,0,0);
       while((!(feof(datosSM)))&&(cont<contar))
       {
	   fread (&info_pro,sizeof(info_pro),1,datosSM);        
          printf("\n\t%d\t | %s\t | %s - %s\t | %s", info_pro.cod_provee, info_pro.nom_provee, info_pro.direccion.colonia, info_pro.direccion.ciudad, info_pro.direccion.telefono); 
		  char colonia[lar];
	char ciudad[lar];
	char departamento[lar];
	char telefono[8];            
          cont++;
       }  
	   printf("\n***************************   FIN DE REPORTE *********************************\n\n"); 
	      
       fclose(datosSM);  
       system("pause");

}
//********************************************************************************************************
//-------------------------------------BUSCADOR DE PROVEEDOR----------------------------------------------
void buscar_provee(FILE *datosSM, datos_provee info_pro){
	
	
	do{
		int cod_provee = 0;
		char cod_valid[6];
		char nom[lar];
		char colonia[lar];
		char ciudad[lar];
		char departamento[lar];
		char telefono[8];
		bool alerta = false;
		int cont=1;
		int contar=cuenta2(datosSM);
	   system("cls");
	   printf("\n\t-----BUSCAR PROVEEDOR-----");
	   printf("\nIndique el codigo del Proveedor: ");
	   scanf("%s", &cod_valid);
	     cod_provee = validar_entero(cod_valid);
	     
	       datosSM = fopen("proveedores.dat","r+b");
	       fseek(datosSM,0,0);
	       while((!(feof(datosSM)))&&(cont<contar))
	       {fread (&info_pro,sizeof(info_pro),1,datosSM);       
	          if(info_pro.cod_provee ==cod_provee){
              alerta=true;  
			  strcpy(nom, info_pro.nom_provee);   
              strcpy(colonia, info_pro.direccion.colonia);
              strcpy(ciudad, info_pro.direccion.ciudad);
              strcpy(departamento, info_pro.direccion.departamento);
              strcpy(telefono, info_pro.direccion.telefono);
          	}  
          	cont++;
	       }        
	       fclose(datosSM); 
	       
	       if(alerta==false){
	       system("cls");
	       printf("\n\tERROR.  >>No se encontro el Proveedor<<\n");
	       }else{
	              printf("\nRESULTADO DE PROVEEDOR");
		          printf("\nCodigo del proveedor: %d", cod_provee);
		          printf("\nNombre del proveedor: %s", nom);
		          printf("\nTelefono: %s", telefono);
		          printf("\n---------DIRECCION--------------\n");
		          printf("Direccion: %s; %s - %s", colonia, ciudad, departamento);
	       }
	    printf("\n**************************** FIN DE BUSQUEDA ***********************************\n");
		system("pause"); 
		validacion_respuesta();
	}while(resp=='S');
}
//********************************************************************************************************
//-----------------------------------AGREGAR NUEVO PRODUCTO-----------------------------------------------
void agregar_NuevoProduc(FILE *datosSM, datos_produc info_produc, datos_provee info_pro)
{
	
	do{
		int codigo = 0, codigopro = 0, let, cant = 0;
		char cod_valid[6], cod_valid2[6], scant[5];
		bool llave = false, llave2 = false;
	   system("cls");
	   printf("\n\t----INGRESAR NUEVO PRODUCTO----");
	   do{
	   printf("\nIngrese el codigo del producto: ");
	   scanf("%s", &cod_valid);
	   codigo = validar_entero(cod_valid);
		}while(codigo == 0);
		llave=false;
	       datosSM = fopen("productos.dat","r+b");
	       fseek(datosSM,0,0);
	       while(!(feof(datosSM)))
	       {
		   fread (&info_produc,sizeof(info_produc),1,datosSM);         
	          if(info_produc.cod_prod==codigo)
	             llave=true;     
	       }        
	       fclose(datosSM);
	    do{
	   printf("\nIngrese el codigo del Proveedor: ");
	   scanf("%s", &cod_valid2);
	   codigopro = validar_entero(cod_valid2);
		}while(codigopro == 0);
		llave2=false;
	       datosSM = fopen("proveedores.dat","r+b");
	       fseek(datosSM,0,0);
	       while(!(feof(datosSM)))
	       {
		   fread (&info_pro,sizeof(info_pro),1,datosSM);         
	          if(info_pro.cod_provee==codigopro)
	             llave2=true;       
	       }        
	       fclose(datosSM);
	       
	       if (llave==false && llave2 == true){  
	       printf("\n\t----INFORMACION DEL PRODUCTO----");
	       info_produc.cod_prod = codigo;
	       info_produc.cod_provee = codigopro;
	       do{
			    printf("\nIngrese el nombre del producto: ");
			    scanf("%s", &info_produc.nom_prod);
	       		let = validar_letras(info_produc.nom_prod);
	       }while(let==1);
	       do{
	       printf("\nIngrese la cantidad: ");
	       scanf("%s", &scant);
	       cant = validar_entero(scant);
	   		}while(cant == false);
	   		info_produc.cantidad = cant;
	       
	       do{
	       		printf("\nIngrese el precio: ");
	       		scanf("%lf", &info_produc.precio);
	       		if(info_produc.precio < 0)
	       			printf("\nERROR. >>Precio no puede ser negativo.<<");
	       }while(info_produc.precio < 0);
	       
	            datosSM = fopen("productos.dat","r+b");
	            fseek (datosSM,0,SEEK_END);
	            fwrite(&info_produc, sizeof(info_produc),1,datosSM);
	            fclose(datosSM);
	      
	      }else{
	          system("cls");
	          printf("\nADVERTENCIA. >>La informacion ingresada ya existe o el proveedor no se encontro.<<\n");
	          system("pause");
	      }
			validacion_respuesta();
	}while(resp=='S');
}
//********************************************************************************************************
//-------------------------------BUSCAR PRODUCTO----------------------------------------------------------
void buscar_producto(FILE *datosSM, datos_produc info_produc, datos_provee info_pro){

	do{
		bool alerta = false, alerta2 = false;
		int cod_prod = 0;
		int cod_provee = 0;
		int cantidad = 0;
		char cod_valid[6];
		char nom_prod[lar];
		char nom_provee[lar];
		double precio = 0;
		int cont=1, cont2 = 1;
		int contar=cuenta3(datosSM);
		int contar2=cuenta2(datosSM);
	   system("cls");
	   printf("\n\t-----BUSCAR PRODUCTO-----");
	   printf("\nIndique el codigo del PRODUCTO: ");
	   scanf("%s", &cod_valid);
	   cod_prod = validar_entero(cod_valid);
	     
	       datosSM = fopen("productos.dat","r+b");
	       fseek(datosSM,0,0);
	       while((!(feof(datosSM)))&&(cont<contar))
	       {fread (&info_produc,sizeof(info_produc),1,datosSM);       
	          if(info_produc.cod_prod ==cod_prod){
              alerta=true; 
              cod_prod = info_produc.cod_prod;
              cantidad = info_produc.cantidad;
              precio = info_produc.precio;
              strcpy(nom_prod, info_produc.nom_prod);
              cod_provee = info_produc.cod_provee;
          	}  
          	cont++;
	       }        
	       fclose(datosSM);
		   
		   datosSM = fopen("proveedores.dat","r+b");
	       fseek(datosSM,0,0);
	       while((!(feof(datosSM)))&&(cont2<contar2))
	       {fread (&info_pro,sizeof(info_pro),1,datosSM);       
	          if(info_pro.cod_provee ==cod_provee){
              alerta2=true; 
              strcpy(nom_provee, info_pro.nom_provee);
          	}  
          	cont2++;
	       }        
	       fclose(datosSM);  
	       
	       if(alerta==false || alerta2 == false){
	       system("cls");
	       printf("\n\tERROR.  >>No se encontro el producto<<\n");
	       }else{
	              printf("\nRESULTADO DEL PRODUCTO");
		          printf("\nCodigo del producto: %d", cod_prod);
		          printf("\nNombre del Producto: %s", nom_prod);
		          printf("\nNombre del Proveedor: %s", nom_provee);
		          printf("\n\t------DETALLE DEL PRODUCTO-------");
		          printf("\nCantidad en almacen: %d", cantidad);
		          printf("\nPrecio por unidad: %.2lf", precio);
	       }
	    printf("\n**************************** FIN DE BUSQUEDA ***********************************\n");
		system("pause");
		validacion_respuesta();
	}while(resp=='S');
}
//********************************************************************************************************
//----------------------------ORDENAR LOS PRODUCTOS-------------------------------------------------------
void orden_producto(orden lista[], int posicion)
{
	int cod = 0, can = 0;
	char nom[lar];
	double pre;
	
	for(int i=0; i<posicion; i++)
	{
		for(int j=0; j<posicion-1; j++)
		{
			if(lista[i].cantidad > lista[j].cantidad)
			{
				can=lista[j].cantidad;
				cod=lista[j].cod_prod;
				pre=lista[j].precio;
				strcpy(nom, lista[j].nom_prod);
				lista[j].cantidad = lista[i].cantidad;
				lista[j].cod_prod = lista[i].cod_prod;
				lista[j].precio = lista[i].precio;
				strcpy(lista[j].nom_prod, lista[i].nom_prod);
				lista[i].cantidad = can;
				lista[i].cod_prod = cod;
				lista[i].precio = pre;
				strcpy(lista[i].nom_prod,nom);
			}
		}
	}
}
//********************************************************************************************************
//------------------------------------REPORTE DE PRODUCTOS------------------------------------------------
void reporte_Produc(FILE *datosSM, datos_produc info_produc)
{
	int cont=0, i = 0;
   int contar=cuenta3(datosSM);
	struct orden ordenamiento[p];   
	     system("cls"); 
	       printf("\n\t---LISTA DE PRODUCTOS SIN EXISTENCIAS---");
	        printf("\n\tCODIGO\t | NOMBRE\t | PRECIO\t | CANTIDAD\t ");
	       datosSM = fopen("productos.dat","r+b");
	       fseek(datosSM,0,0);
	       while((!(feof(datosSM)))&&(cont<contar))
	       {fread (&info_produc,sizeof(info_produc),1,datosSM);       
	          if(0 == info_produc.cantidad){
	          	
	            printf("\n\t%d\t | %s\t | %.2lf\t | %d\t |", info_produc.cod_prod, info_produc.nom_prod, info_produc.precio, info_produc.cantidad);
          	} 
			ordenamiento[i].cod_prod = info_produc.cod_prod;
			ordenamiento[i].cantidad = info_produc.cantidad;
			ordenamiento[i].precio = info_produc.precio;
			strcpy(ordenamiento[i].nom_prod, info_produc.nom_prod);
			i++;
          	cont++;
	       }       
	       fclose(datosSM); 
	       
	       printf("\n\t\t\t************************");
   		printf("\n\t-----REPORTE DE PRODUCTOS----");
       printf("\n\tCODIGO\t | NOMBRE\t | PRECIO\t | CANTIDAD\t ");
       orden_producto(ordenamiento, cont);
       for(int i = 0; i < cont-1; i++){
       	printf("\n\t%d\t | %s\t | %.2lf\t | %d\t |", ordenamiento[i].cod_prod, ordenamiento[i].nom_prod, ordenamiento[i].precio, ordenamiento[i].cantidad);
       }
	   printf("\n***************************   FIN DE REPORTE *********************************\n\n"); 
       system("pause");
}
//********************************************************************************************************
//-----------------------------------------INSERTAR DETALLE DE FACTURA------------------------------------
void insertar_detalle(int cod, char nom[lar], double precio, int cantidad, double total){
	
	detalle_factura* nuevo = (detalle_factura*) malloc(sizeof(detalle_factura));
	nuevo->codigo =cod;
	strcpy(nuevo->nom_prod, nom);
	nuevo->precio = precio;
	nuevo->cantidad = cantidad;
	nuevo->total = total;
	nuevo-> siguiente = inicio;
	inicio = nuevo;
}
//********************************************************************************************************
//-------------------------------------MOSTRAR LISTA DE DETALLE DE FACTURA--------------------------------
void mostra_lista(){
	detalle_factura* actual = (detalle_factura*) malloc(sizeof(detalle_factura));
	actual = inicio;
	if(inicio != NULL){
		while(actual != NULL){
			printf("%d\t\t | %s\t\t | %.2lf\t | %d\t\t | %.2lf \n", actual->codigo, actual->nom_prod, actual->precio, actual->cantidad, actual->total);
			actual = actual->siguiente;
		}
	}
}
//********************************************************************************************************
//--------------------------------------ELIMINAR DATO DE LA LISTA-----------------------------------------
void eliminar_datolista(detalle_factura *&inicio, int &cod, char *nombre, double &precio, int &cantidad, double &total){
	detalle_factura *aux = inicio;
	cod = aux->codigo;
	strcpy(aux->nom_prod, nombre);
	precio = aux->precio;
	cantidad = aux->cantidad;
	total = aux->total;
	inicio = aux->siguiente;
	delete aux;
}
//********************************************************************************************************
//---------------------------------NUEVA FACTURA----------------------------------------------------------
void agregar_factura(FILE *datosSM, datos_produc info_produc,  datos_fac info_fac){
		do{
			bool llave = false, vali_cantidad = false, llave2 = false;
			int codigo = 1, cod_prod = 0, i =0,  let, cantidad = 0, cant_cliente = 0, salida = 0;
			double precio = 0, total = 0, subtotal = 0, isv, grantotal = 0;
			char nom, name[lar], nom_prod[lar], agregar, eliminar, fecha[128], hora[128], cod[6], cant[6];
			   datosSM = fopen("facturas.dat","r+b");
		       fseek(datosSM,0,0);
		       while(!(feof(datosSM)))
		       {
			   fread (&info_fac,sizeof(info_fac),1,datosSM);         
		          if(info_fac.cod_factura==codigo)
		             codigo++;    
		       }        
		       fclose(datosSM);
		       do{
		       		system("cls");
		       		printf("\n\n\t\t----NUEVA FACTURA-----\n");
		       		printf("\tDesea con nombre la factura. (Ingrese [S o N]): ");
		       		scanf("%s", &nom);
		       		nom = vali_resp(nom);
		       }while(nom!='S' && nom!='N');
		    	
		    	if(nom == 'S'){
		    		do{
		    			printf("\nIngrese su Nombre: ");
		    			scanf("%s", &name);
		    			let = validar_letras(name);
		    			strupr(name);
		    		}while(let == 1);
		    	}
		    	else 
		    		strcpy(name, "CONSUMIDOR_FINAL");
		    do{		
		    	vali_cantidad = false;
		    	llave = false;
		    	do{
		    		do{
		    		system("cls");
			    	printf("\n\t\t------LISTA DE PRODUCTOS------");
			    	printf("\nCOD. PRODUCTO\t | NOMBRE PRODUCTO\t | PRECIO\t | CANTIDAD\t | TOTAL\n");
			    	mostra_lista();
			    	scanf("%s", &cod);
			    	cod_prod = validar_entero(cod);
			    	}while(cod_prod == 0);
			    	datosSM = fopen("productos.dat","r+b");
			       fseek(datosSM,0,0);
			       while(!(feof(datosSM)))
			       {
				   fread (&info_produc,sizeof(info_produc),1,datosSM);         
			          if(info_produc.cod_prod==cod_prod){
			          	cantidad = info_produc.cantidad;
			          	llave = true;
			             if(cantidad > 0){
			             	vali_cantidad = true; 
			             	strcpy(nom_prod, info_produc.nom_prod); 
						 	precio = info_produc.precio;
			             }
			          }
			       }        
			       fclose(datosSM);
			       system("cls");
		    	if(llave == true && vali_cantidad == true){
		    		do{
		    			do{
		    			system("cls");
			    		printf("\n\t\t------LISTA DE PRODUCTOS------");
			    	   	printf("\nCOD. PRODUCTO\t | NOMBRE PRODUCTO\t | PRECIO\t | CANTIDAD\t | TOTAL\n");
			    	   	mostra_lista();
		    			printf("%d\t\t | %s\t\t | %.2lf\t | ", cod_prod, nom_prod, precio);
		    			scanf("%s", &cant);
		    			cant_cliente = validar_entero(cant);
		    			}while(cant_cliente == 0);
		    			if(cant_cliente<= cantidad && cant_cliente > 0){
		    				llave2 =  true;
		    				system("cls");
		    				total = cant_cliente * precio;
		    				subtotal = subtotal + total;
		    				printf("\n\t\t------LISTA DE PRODUCTOS------");
		    	   			printf("\nCOD. PRODUCTO\t | NOMBRE PRODUCTO\t | PRECIO\t | CANTIDAD\t | TOTAL\n");
		    	   			mostra_lista();
		    				printf("%d\t\t | %s\t\t | %.2lf\t | %d\t\t | %.2lf \n", cod_prod, nom_prod, precio, cant_cliente, total);
		    				
		    			}
		    			else{
		    				llave2 = false;
		    				printf("\nERROR. >>Cantidad de producto no aceptada.<<\n");
		    				system("pause");
		    				system("cls");
		    				printf("\n\t\t------LISTA DE PRODUCTOS------");
		    	   			printf("\nCOD. PRODUCTO\t | NOMBRE PRODUCTO\t | PRECIO\t | CANTIDAD\t | TOTAL\n");
		    	   			mostra_lista();
		    			}
		    		}while(llave2 == false);
		    	}
		    	else if(vali_cantidad == false && llave == true){
		    		printf("\nERROR. >>No esta disponible este producto en almacen.<<\n");
		    		system("pause");
		    		system("cls");
					printf("\n\t\t------LISTA DE PRODUCTOS------");
		    	   	printf("\nCOD. PRODUCTO\t | NOMBRE PRODUCTO\t | PRECIO\t | CANTIDAD\t | TOTAL\n");
		    	   	mostra_lista();
		    	}
		    	else if(llave == false){
		    		printf("\nERROR. >>El Producto ingresado no se encontro<<\n");
		    		salida++;
		    		system("pause");
		    		system("cls");
					printf("\n\t\t------LISTA DE PRODUCTOS------");
		    	   	printf("\nCOD. PRODUCTO\t | NOMBRE PRODUCTO\t | PRECIO\t | CANTIDAD\t | TOTAL\n");
		    	   	mostra_lista();
		    	   	if(salida > 3)
		    	   		break;
		    	}
		    	}while(llave == false || vali_cantidad == false);
		    	if(salida < 3){
		    	insertar_detalle(cod_prod, nom_prod, precio, cant_cliente, total);
		    	do{
		    	system("cls");
		    	printf("\n\t\t------LISTA DE PRODUCTOS------");
		    	printf("\nCOD. PRODUCTO\t | NOMBRE PRODUCTO\t | PRECIO\t | CANTIDAD\t | TOTAL\n");
		    	mostra_lista();
		    	printf("\n\t\t---OPCION---\n");
		    	printf("\n\tS - Agregar otro producto a la lista.");
		    	printf("\n\tE - Eliminar ultimo producto.");
		    	printf("\n\tF - Facturar.");
		    	printf("\n\tOpcion: ");
		    	scanf("%s", &agregar);
				agregar=toupper(agregar);
					 if(agregar!='S' && agregar!='E' && agregar != 'F')
						{
						printf("\nERROR. >>Ingrese una opcion valida<<\n");
					    system("pause");
						}
				}while((agregar!='S')&& (agregar!='E') && (agregar != 'F'));  
				if(agregar == 'E'){
					if(inicio != NULL){
						subtotal = subtotal - total;
						printf("\nEl producto [%s] se elimino.\n", inicio->nom_prod);
						eliminar_datolista(inicio, cod_prod, nom_prod, precio, cant_cliente, total);
						system("pause");
					} 
						else
							printf("\nNo se encontraron datos en la lista.\n");
					do{
			    		printf("\n\tDesea agregar otro producto [S / N]: ");
			    		scanf("%s", &agregar);
			    		system("cls");
						 agregar = vali_resp(agregar);
						 if(inicio == NULL){
						 	printf("\nERROR. No se encontraron detalle en la factura.");
						 	printf("\nIngrese un articulo a la factura.\n");
						 	system("pause");
						 	agregar = 'S';
						 }
					}while((agregar!='S')&& (agregar!='N')); 
				}
				}
				else
					agregar = 'N';
			}while(agregar == 'S');
			
			if(salida < 3){
			fecha_tiempo(fecha);
			hora_tiempo(hora);
			isv = subtotal * 0.15;
			grantotal = subtotal + isv;
			system("cls");
			printf("\n\t\t---FACTURA---");
			printf("\n\t\t*************");
			printf("\n\t     SUPER MERCADITO");
			printf("\n     FRENTE AL AEROPUERTO, TEGUCIGALPA");
			printf("\n\tTEL.(504) 2223-5050");
			printf("\n\tSUPER_MERCADITO@GMAIL.COM");
			printf("\n\nC.A.I:");
			printf("\nBBEE724-C905D4-174E9A-449C6E-2F994A-81");
			printf("\n\nFecha: %s %s ", fecha, hora);
			printf("\n\nFACTURA #: %d", codigo);
			printf("\nNombre Cliente: %s", name);
			printf("\n\t\t------------------");
			printf("\n\t\tDETALLE DE FACTURA");
			printf("\n***************************************************************");
			printf("\nCOD. PRODUCTO\t | NOMBRE PRODUCTO\t | PRECIO\t | CANTIDAD\t | TOTAL\n");
		    mostra_lista();
			printf("\n\n\t\t\t\tSUBTOTAL: %.2lf", subtotal);
			printf("\n\t\t\t\t   I.S.V: %.2lf", isv);
			printf("\n\t\t\t\t   TOTAL: %.2lf", grantotal);
			printf("\n********************FIN DE FACTURA*****************************\n");
			system("pause");
			info_fac.cod_factura = codigo;
			strcpy(info_fac.fecha, fecha);
			strcpy(info_fac.hora, hora);
			strcpy(info_fac.nom_fac, name);
			info_fac.subtotal = subtotal;
			info_fac.isv =  isv;
			info_fac.grantotal = grantotal;
			detalle_factura* actual = (detalle_factura*) malloc(sizeof(detalle_factura));
			actual = inicio;
			if(inicio != NULL){
				while(actual != NULL){
					info_fac.lista[i].codigo = actual->codigo;
					strcpy(info_fac.lista[i].nom_prod, actual->nom_prod);
					info_fac.lista[i].precio = actual->precio;
					info_fac.lista[i].cantidad = actual->cantidad;
					info_fac.lista[i].total = actual->total;
					actual = actual->siguiente; 
					i++;
				}
			}
	            datosSM = fopen("facturas.dat","r+b");
	            fseek (datosSM,0,SEEK_END);
	            fwrite(&info_fac, sizeof(info_fac),1,datosSM);
	            fclose(datosSM);
	            while(inicio!=NULL){
	            	eliminar_datolista(inicio, cod_prod, nom_prod, precio, cant_cliente, total);
	            }
	            validacion_respuesta();
	    	}	
	    	else 
	    		break;
				
		}while(resp=='S');
}
//********************************************************************************************************
//--------------------------------SUMA DE TOTAL-----------------------------------------------------------
double suma_total(double totales[], int cant){
	if(cant == 0)
		return 1;
		else
			return totales[cant] + suma_total(totales, cant-1);
}
//********************************************************************************************************
//----------------------------LISTAR FACTURAS-------------------------------------------------------------
void mostrar_factura(){
	int cont=1;
   int contar=cuenta4(datosSM);
   double totales[p];
   system("cls");
   printf("\n\t-----REPORTE DE FACTURAS----");
       
       datosSM = fopen("facturas.dat","r+b");
       fseek(datosSM,0,0);
       while((!(feof(datosSM)))&&(cont<contar))
       {
	   fread (&info_fac,sizeof(info_fac),1,datosSM);                 
          printf("\n\t\t---FACTURA---");
			printf("\n\t\t*************");
			printf("\n\t     SUPER MERCADITO");
			printf("\n     FRENTE AL AEROPUERTO, TEGUCIGALPA");
			printf("\n\tTEL.(504) 2223-5050");
			printf("\n\tSUPER_MERCADITO@GMAIL.COM");
			printf("\n\nC.A.I:");
			printf("\nBBEE724-C905D4-174E9A-449C6E-2F994A-81");
			printf("\n\nFecha: %s %s", info_fac.fecha, info_fac.hora);
			printf("\n\nFACTURA #: %d", info_fac.cod_factura);
			printf("\nNombre Cliente: %s", info_fac.nom_fac);
			printf("\n\t\t------------------");
			printf("\n\t\tDETALLE DE FACTURA");
			printf("\n***************************************************************");
			printf("\nCOD. PRODUCTO\t | NOMBRE PRODUCTO\t | PRECIO\t | CANTIDAD\t | TOTAL\n");
		    for(int i=0; i < list; i++){
		    	if(info_fac.lista[i].codigo != 0)
		    		printf("%d\t\t | %s\t\t | %.2lf\t | %d\t\t | %.2lf \n", info_fac.lista[i].codigo, info_fac.lista[i].nom_prod, info_fac.lista[i].precio, info_fac.lista[i].cantidad, info_fac.lista[i].total);
		    	else
		    		i = list;
		    }
			printf("\n\n\t\t\t\tSUBTOTAL: %.2lf", info_fac.subtotal);
			printf("\n\t\t\t\t   I.S.V: %.2lf", info_fac.isv);
			printf("\n\t\t\t\t   TOTAL: %.2lf", info_fac.grantotal);
			printf("\n****************************************************************\n");
			totales[cont] = info_fac.grantotal;
          cont++;
       }  
	   printf("\n***************************   FIN DE REPORTE *********************************\n\n"); 
       fclose(datosSM);
       printf("\n\t\t----TOTAL DE EFECTIVO EN CAJA-----");
	   printf("\n\t\tSUMA DE CAJA: %.2lf\n", suma_total(totales, cont)-1);  
       system("pause");
}
//********************************************************************************************************
//--------------------------------BUSCAR FACTURA----------------------------------------------------------
void buscar_factura(FILE *datosSM, datos_fac info_fac){

	do{
		bool alerta = false;
		char cod_veri[6];
		int cod_fact;
		int cont=1;
		int contar=cuenta4(datosSM);

	   system("cls");
	   printf("\n\t-----BUSCAR FACTURA-----");
	   printf("\nIndique el codigo de Factura: ");
	   scanf("%s", &cod_veri);
	   cod_fact = validar_entero(cod_veri);
	     
	       datosSM = fopen("facturas.dat","r+b");
	       fseek(datosSM,0,0);
	       while((!(feof(datosSM)))&&(cont<contar))
	       {fread (&info_fac,sizeof(info_fac),1,datosSM);       
	          if(info_fac.cod_factura ==cod_fact){
              alerta=true;  
			  printf("\n\t\t---FACTURA---");
			  printf("\n\t\t*************");
			  printf("\n\t     SUPER MERCADITO");
			  printf("\n     FRENTE AL AEROPUERTO, TEGUCIGALPA");
			  printf("\n\tTEL.(504) 2223-5050");
			  printf("\n\tSUPER_MERCADITO@GMAIL.COM");
			  printf("\n\nC.A.I:");
			  printf("\nBBEE724-C905D4-174E9A-449C6E-2F994A-81");
			  printf("\n\nFecha: %s %s", info_fac.fecha, info_fac.hora);
			  printf("\n\nFACTURA #: %d", info_fac.cod_factura);
			  printf("\nNombre Cliente: %s", info_fac.nom_fac);
			  printf("\n\t\t------------------");
			  printf("\n\t\tDETALLE DE FACTURA");
			  printf("\n***************************************************************");
			  printf("\nCOD. PRODUCTO\t | NOMBRE PRODUCTO\t | PRECIO\t | CANTIDAD\t | TOTAL\n");
		      for(int i=0; i < list; i++){
		    	if(info_fac.lista[i].codigo != 0)
		    		printf("%d\t\t | %s\t\t | %.2lf\t | %d\t\t | %.2lf \n", info_fac.lista[i].codigo, info_fac.lista[i].nom_prod, info_fac.lista[i].precio, info_fac.lista[i].cantidad, info_fac.lista[i].total);
		    	else
		    		i = list;
		    	}
			printf("\n\n\t\t\t\tSUBTOTAL: %.2lf", info_fac.subtotal);
			printf("\n\t\t\t\t   I.S.V: %.2lf", info_fac.isv);
			printf("\n\t\t\t\t   TOTAL: %.2lf", info_fac.grantotal);
			printf("\n****************************************************************\n");
			  } 
          	cont++;
	       }        
	       fclose(datosSM); 
	       
	       if(alerta==false){
	       system("cls");
	       printf("\n\tERROR.  >>No se encontro la Factura<<\n");
	   		}
	    printf("\n**************************** FIN DE BUSQUEDA ***********************************\n");
		system("pause"); 
		validacion_respuesta();
	}while(resp=='S');
}
//********************************************************************************************************
//-------------------------------CIERRE DE CAJA-----------------------------------------------------------
void cierre_caja(FILE *datosSM, datos_caja info_caja, datos_fac info_fac){
	char hora_final[128], fecha[128];
	int cont = 1, cont2 = 0;
	int contar = cuenta4(datosSM);
	int contar2 = cuenta5(datosSM);
	bool llave = false;
	double total_caja[p];
	    
	    fecha_tiempo(fecha);
	    datosSM = fopen("cierre_caja.dat","r+b");
	       fseek(datosSM,0,0);
	       while((!(feof(datosSM)))&&(cont2<contar2))
	       {fread (&info_caja,sizeof(info_caja),1,datosSM);       
	          if(strcmp(info_caja.fecha, fecha)==0)
            	llave = true;
             cont2++;
       		}        
	       fclose(datosSM); 
	       cont2=0;
	       
	       if(llave == false){
	       	datosSM = fopen("facturas.dat","r+b");
	       fseek(datosSM,0,0);
	       while((!(feof(datosSM)))&&(cont<contar))
	       {fread (&info_fac,sizeof(info_fac),1,datosSM);       
	          if(strcmp(info_fac.fecha, fecha))
            	total_caja[cont] = info_fac.grantotal;
             cont++;
       		}        
	       fclose(datosSM); 
	       info_caja.total_dia = suma_total(total_caja, cont)-1;
	       hora_tiempo(hora_final);
	       info_caja.total_fac = cont;
	       strcpy(info_caja.hora_final, hora_final);
	       strcpy(info_caja.fecha, fecha);

		datosSM = fopen("cierre_caja.dat","r+b");
	    fseek (datosSM,0,SEEK_END);
	    fwrite(&info_caja, sizeof(info_caja),1,datosSM);
	    fclose(datosSM);
	    
		system("cls");
	       }
	       else{
		       	system("cls");
		       	printf("\n\tADVERTENCIA. Lo sentimos ya hubo cierre de caja.");
		       	printf("\n\tSe habilita hasta el siguiente dia.");
	       }
	       datosSM = fopen("cierre_caja.dat","r+b");
		       fseek(datosSM,0,0);
		       while((!(feof(datosSM)))&&(cont2<contar2))
		       {fread (&info_caja,sizeof(info_caja),1,datosSM);       
		          if(strcmp(info_caja.fecha, fecha) == 0){
	              	printf("\n\t\t----CIERRE DE CAJA----");
	              	printf("\n\tFECHA: %s", info_caja.fecha);
	              	printf("\n\tHORA DE CIERRE: %s", info_caja.hora_final);
	              	printf("\n\tNUMERO DE FACTURAS DEL DIA: %d", info_caja.total_fac-1);
	              	printf("\n\tTOTAL DE CIERRE EN EFECTIVO: LPS. %.2lf\n", info_caja.total_dia);
				  } 
	          	cont2++;
		       }        
		       fclose(datosSM);
		       system("pause");
	       
}
//********************************************************************************************************
//--------------------------ARCHIVOS DE RESPALDOS---------------------------------------------------------
void archivo(){
	if((datUsuario = fopen("empleado.dat", "r+")) == NULL || (datosSM = fopen("proveedores.dat", "r+")) == NULL
	|| (datosSM = fopen("productos.dat", "r+")) == NULL || (datosSM = fopen("facturas.dat", "r+")) == NULL 
	|| (datosSM = fopen("cierre_caja.dat", "r+")) == NULL){
		if((datUsuario = fopen("empleado.dat", "r+")) == NULL)
			datUsuario = fopen("empleado.dat", "w+");
		fclose(datUsuario);
		if((datosSM = fopen("proveedores.dat", "r+")) == NULL)
			datosSM = fopen("proveedores.dat", "w+");
		fclose(datUsuario);
		if((datosSM = fopen("productos.dat", "r+")) == NULL)
			datosSM = fopen("productos.dat", "w+");
		fclose(datUsuario);
		if((datosSM = fopen("facturas.dat", "r+")) == NULL)
			datosSM = fopen("facturas.dat", "w+");
		fclose(datUsuario);
		if((datosSM = fopen("cierre_caja.dat", "r+")) == NULL)
			datosSM = fopen("cierre_caja.dat", "w+");
		fclose(datUsuario);
		printf("---------------------------------------------");
		printf("\nNo se encontraron algunos Archivos");
		printf("\nSe crearon nuevos archivos de respaldo");
		printf("\n---------------------------------------------\n");
		system("pause");
	}
}
//********************************************************************************************************
//---------------------------------MENU PRINCIPAL----------------------------------------------------------
int menu(){
	archivo();
	char opc[2];
	int salida;
	
	do{
	system("cls");
	gatoxy(50,5);
	printf("-----MENU PRINCIPAL-----");
	gatoxy(40,6);
	printf("1)- Facturacion");
	gatoxy(40,7);
	printf("2)- Agregar Informacion");
	gatoxy(40,8);
	printf("3)- Buscar Datos");
	gatoxy(40,9);
	printf("4)- Mostrar listados de informacion");
	gatoxy(40,10);
	printf("5)- Mantenimiento(proximamente)");
	gatoxy(40,11);
	printf("6)- Salir");
	gatoxy(40,12);
	printf("Ingrese su opcion: ");
	scanf("%s", &opc);
	salida = validar_entero(opc);
	vali_menu(salida, 1, 6);
	}
	while(salida < 1 || salida > 6);
	return salida;
}
//*******************************************************************************************************
//-------------------------------------SUB-MENU----------------------------------------------------------
void sub_menu(int opc, int smenu){
	if(opc == 1){
		switch(smenu){
					case 1:
							agregar_factura(datosSM, info_produc, info_fac);
							break;
					case 2:
							buscar_factura(datosSM, info_fac);
							break;
					case 3:
							mostrar_factura();
							break;
					case 4:
							cierre_caja(datosSM, info_caja, info_fac);
							break;
		}
	}
	else if(opc==2){
		switch(smenu){
					case 1:
							agregar_NuevoProvee(datosSM, info_pro);
							break;
					case 2:
							agregar_NuevoProduc(datosSM, info_produc, info_pro);
							break;
					case 3:
							agregar_Nuevouser(datUsuario, info_user);
							break;
					}
	}
	else if(opc==3){
		switch(smenu){
					case 1:
							buscar_provee(datosSM, info_pro);
							break;
					case 2:
							buscar_producto(datosSM, info_produc, info_pro);
							break;
					case 3:
							buscar_user(datUsuario, info_user);
							break;
			}
	}
	else if(opc==4){
		switch(smenu){
					case 1:
							reporte_provee(datosSM);
							break;
					case 2:
							reporte_Produc(datosSM, info_produc);
							break;
					case 3:
							reporte_usuario(datUsuario);
							break;
			}
	}
	else if(opc==5){
		switch(smenu){
					case 1:
							break;
					case 2:
							break;
					case 3:
							break;
					case 4:
							break;
		}
	}
}
//*******************************************************************************************************
int main()
{
	system("color F0");
	int opc; 
	char opc2[20];
	int contp=0;
	char resp2='N';
	
	 while(resp2=='N')
	 {
	 	smenu = 0;
	 	opc = menu();
	 	switch(opc){
				case 1:
					while(smenu!=5){
							do{
								system("cls");
								gatoxy(40,8);printf("-----Modulo Facturacion-----");
								gatoxy(41,10);printf("1)- Nueva Factura");
								gatoxy(42,11);printf("2)- Buscar factura");
								gatoxy(43,12);printf("3)- Mostrar facturas");
								gatoxy(44,13);printf("4)- Cierre de caja");
								gatoxy(45,14);printf("5)- Regresar al menu principal");
								gatoxy(46,15);printf("Opcion: ");
								scanf("%s", &opc2);
								smenu = validar_entero(opc2);
									vali_menu(smenu, 1, 5);
								}while(smenu < 1 || smenu > 5);
								sub_menu(opc, smenu);
						}
							break;
				case 2:
						while(smenu!=4){
							do{
								system("cls");
								gatoxy(40,8);printf("-----Modulo Agregar Informacion-----");
								gatoxy(41,10);printf("1)- Agregar nuevo proveedor");
								gatoxy(42,11);printf("2)- Agregar nuevo producto");
								gatoxy(43,12);printf("3)- Agregar nuevo usuario");
								gatoxy(44,13);printf("4)- Regresar al menu principal");
								gatoxy(45,14);printf("Opcion: ");
								scanf("%s", &opc2);
									smenu = validar_entero(opc2);
									vali_menu(smenu, 1, 5);
								}while(smenu < 1 || smenu > 4);
								sub_menu(opc, smenu);
							}
							break;
				case 3:
						while(smenu!=4){
							do{
								system("cls");
								gatoxy(40,8);printf("-----Modulo Buscar Datos-----");
								gatoxy(41,10);printf("1)- Buscar proveedor");
								gatoxy(42,11);printf("2)- Buscar producto");
								gatoxy(43,12);printf("3)- Buscar usuario");
								gatoxy(44,13);printf("4)- Regresar al menu principal");
								gatoxy(45,14);printf("Opcion: ");
								scanf("%s", &opc2);
									smenu = validar_entero(opc2);
									vali_menu(smenu, 1, 5);
								}while(smenu < 1 || smenu > 4);
								sub_menu(opc, smenu);
						}
							break;
				case 4:
						while(smenu!=4){
							do{
								system("cls");
								gatoxy(40,8);printf("-----Modulo listar Informacion-----");
								gatoxy(41,10);printf("1- Lista de los proveedores");
								gatoxy(42,11);printf("2- Lista de los productos");
								gatoxy(43,12);printf("3- Lista de los usuarios");
								gatoxy(44,13);printf("4- Regresar al menu principal");
								gatoxy(45,14);printf("Opcion: ");
								scanf("%s", &opc2);
									smenu = validar_entero(opc2);
									vali_menu(smenu, 1, 5);
								}while(smenu < 1 || smenu > 4);
								sub_menu(opc, smenu);
						}
							break;
				case 5:
							break;
				case 6:
							do{
								system("cls");
								  printf("\n\n\tDESEA REALMENTE SALIR DEL SISTEMA? [S o N]: ");
								  scanf("%s", &resp2);
								  
								  resp2=toupper(resp2);
								  
								  if(resp2!='S' && resp2!='N')
								  {
								    printf("\nERROR. >>Ingrese una opcion valida<<\n");
								    system("pause");
							      }
								  
								}while((resp2!='S')&& (resp2!='N'));
								if(resp2=='S')
									return 0;
							break;
				default:
						printf("\nERROR. No se encontraron los datos\n");
						return 1;
						break;
		}

	 }
}
