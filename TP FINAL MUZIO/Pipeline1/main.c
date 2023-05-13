//Francisco Ignacio Muzio
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX 600
#define DOLL 25
#define BIBLIA 2
#define COPA 3

typedef struct
{
    int cantMateria; //gramos
    char calidad; // "a", "b", "c"
    float costo; //cada bloque posee distintos costos en base a los gramos
} PaqueteMateriaPrima;

typedef struct
{
    char nombre[20]; //"Biblia", "Copa de vino", "Doll"
    int falla; //puede tener 0...2 fallas
    float costo;
    char calidad; //según la calidad de la materia, será la calidad del producto
} Componente;

//-------------------------------------------------------------------------
int CargarArr(PaqueteMateriaPrima []);
int Fabricar (PaqueteMateriaPrima [],int, Componente []);
void CargarArch (Componente[],int );
//-------------------------------------------------------------------------

int main()
{
    PaqueteMateriaPrima a[MAX];
    Componente b [MAX];
    int validos=CargarArr(a);
    int valComp=Fabricar(a,validos,b);
    int i=0;
    CargarArch(b,valComp);

    return 0;
}

//-------------------------------------------------------------------------

int CargarArr (PaqueteMateriaPrima m[])
{
    FILE *arch=fopen("Paquetes.bin","rb");
    PaqueteMateriaPrima p;
    int i=0;
    if(arch!=NULL)
    {
        while(fread(&p,sizeof(PaqueteMateriaPrima),1,arch)>0)
        {
            m[i]=p;
            i++;
        }
        fclose(arch);
    }
    return i;
}

int Fabricar (PaqueteMateriaPrima m[],int val, Componente c[])
{
    float g;
    int i=0;
    int j=0;
    int flag=0;
    g=m[i].cantMateria/m[i].costo;
    while(flag==0)
    {

        if(m[i].cantMateria<DOLL && i<val-1)
        {
            i++;
            g=m[i].cantMateria/m[i].costo;
        }
        if(m[i].cantMateria>=DOLL && flag==0)
        {
        m[i].cantMateria=(m[i].cantMateria)-25;
        c[j].calidad=m[i].calidad;
        c[j].falla=rand()%3;
        c[j].costo=g*25+6;
        strcpy(c[j].nombre,"Doll");
        j++;
        }
        else if (flag==0)
        {
            flag=1;
        }

        if(m[i].cantMateria<COPA && i<val-1)
        {
            i++;
            g=m[i].cantMateria/m[i].costo;
        }
        if(m[i].cantMateria>=COPA && flag==0)
        {
        m[i].cantMateria=(m[i].cantMateria)-3;
        c[j].calidad=m[i].calidad;
        c[j].falla=rand()%3;
        c[j].costo=g*3+0.75;
        strcpy(c[j].nombre,"Copa de vino");
        j++;
        }
        else if (flag==0)
        {
            flag=1;
        }

        if (m[i].cantMateria<BIBLIA && i<val-1)
        {
            i++;
            g=m[i].cantMateria/m[i].costo;
        }
        if(m[i].cantMateria>=BIBLIA && flag==0)
        {
        m[i].cantMateria=(m[i].cantMateria)-2;
        c[j].calidad=m[i].calidad;
        c[j].falla=rand()%3;
        c[j].costo=g*2+0.5;
        strcpy(c[j].nombre,"Biblia");
        j++;
        }
        else if (flag==0)
        {
            flag=1;
        }

    }
    return j;
}

void CargarArch(Componente c[],int val)
{
    FILE *arch=fopen("Componentes.bin","wb");
    int i=0;
    if(arch!=NULL)
    {
        while(i<val)
        {
            fwrite(&c[i],sizeof(Componente),1,arch);
            i++;
        }
        fclose(arch);
    }
}

