//Francisco Ignacio Muzio
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define CAL 3

typedef struct{
    float costo;
    char calidad;
}PlayMobil;

typedef struct {     ///planilla final
    float gananciaBruta;
    float costoLote; //de todos los prod
    float costoPerdidas;
    int cantTotal;
}Contaduria;

typedef struct {
    float precioFinal;
    int cant;
    char calidad;
}DetalleLote;

//---------------------------------------------------------------------------
void CargarArr(PlayMobil [],int *);
float CargCont1 (Contaduria*, PlayMobil[],int);
float CargDet (DetalleLote [],PlayMobil[],int, float);
void Ganancia (Contaduria);
void CargarCon2 (Contaduria);
void CargarDet (DetalleLote []);
//---------------------------------------------------------------------------
int main()
{
    PlayMobil e[MAX];
    DetalleLote d[CAL];
    Contaduria c;
    int val=0;
    float prom;
    CargarArr (e,&val);
    prom=CargCont1 (&c,e,val);
    c.gananciaBruta=CargDet(d,e,val,prom);
    Ganancia(c);
    CargarCon2(c);
    CargarDet(d);
    return 0;
}

void CargarArr (PlayMobil a[],int *val)
{
    FILE *arch=fopen("ProductosFinales.bin","rb");
    PlayMobil f;
    if(arch!=NULL)
    {
        while(fread(&f,sizeof(PlayMobil),1,arch)>0)
        {
            a[*val]=f;
            (*val)++;
        }
        fclose(arch);
    }
}

float CargCont1(Contaduria* a, PlayMobil b[],int val)
{
    int i=0;
    float j;
    (*a).costoLote=0;
    (*a).cantTotal=0;
    (*a).costoPerdidas=0;
    while(i<val)
    {
        ((*a).cantTotal)++;
        (*a).costoLote=(*a).costoLote+(b[i].costo);
        i++;
    }
    FILE *arch=fopen("Perdidas.bin","rb");
    if (arch!=NULL)
    {
        while(fread(&j,sizeof(float),1,arch)>0)
        {
            (*a).costoPerdidas=(*a).costoPerdidas+j;
        }
        fclose(arch);
    }
    j=(*a).costoLote/(*a).cantTotal;
    return j;
}

 float CargDet(DetalleLote a[],PlayMobil b[],int val,float prom)
 {
     int i=0;
     float total=0;
     a[0].precioFinal=prom*2.25;
     a[0].calidad='a';
     a[0].cant=0;
     a[1].precioFinal=prom*2.23;
     a[1].calidad='b';
     a[1].cant=0;
     a[2].precioFinal=prom*2.20;
     a[2].calidad='c';
     a[2].cant=0;
     while (i<val)
     {
         if(b[i].calidad=='a')
         {
             (a[0].cant)++;
         }
         else if (b[i].calidad=='b')
         {
             (a[1].cant)++;
         }
         else
         {
            (a[2].cant)++;
         }
         i++;
     }
     for(int j=0;j<CAL;j++)
     {
         total=a[j].cant*a[j].precioFinal+total;
     }
     return total;
 }


 void Ganancia (Contaduria c)
 {
     float costTot;
     costTot=c.costoLote+c.costoPerdidas;
     if(c.gananciaBruta>costTot)
     {
         printf("\nEl lote consiguio ganancias por sobre el costo.\n");
     }
     else
     {
         printf("\nEl lote genero perdidas por coste.\n");
     }
 }

 void CargarCon2 (Contaduria c)
 {
     FILE *arch=fopen("Contaduria.bin","wb");
     if (arch!=NULL)
     {
         fwrite(&c,sizeof(Contaduria),1,arch);
         fclose(arch);
     }
 }

 void CargarDet (DetalleLote d[])
 {
     FILE *arch= fopen("DetalleLote.bin","wb");
     if(arch!=NULL)
     {
         for (int i=0;i<CAL;i++)
         {
             fwrite(&d[i],sizeof(DetalleLote),1,arch);
         }
         fclose(arch);
     }
 }
