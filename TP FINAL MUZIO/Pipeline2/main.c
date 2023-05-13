//Francisco Ignacio Muzio
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 600

typedef struct
{
    char nombre[20]; //"Biblia", "Copa de vino", "Doll"
    int falla; //puede tener 0...2 fallas
    float costo;
    char calidad; //según la calidad de la materia, será la calidad del producto
} Componente;

typedef struct
{
    float costo;
    char calidad;
} PlayMobil;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

int CargarA(Componente [], float [],int*);
void CargarComponentes (Componente [],Componente [],Componente [], Componente [],int,int *, int *, int*);
void CargarB (Componente[],Componente[],int,int*);
void CargarC (Componente[],Componente[],int,int*);
void CargarD (Componente[],Componente[],int,int*);
int Ensamble (Componente[],Componente [],Componente[],PlayMobil[],int,int,int,int);
void CargaFinales (PlayMobil [],int);
void CargaPerdidas (float [],int);


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    Componente a[MAX];
    Componente b[MAX];
    Componente c[MAX];
    Componente d[MAX];
    float Fallas[MAX];
    PlayMobil e[MAX];
    int valFal=0;
    int validos;
    int validosB=0;
    int validosC=0;
    int validosD=0;
    int validosE;
    validos= CargarA(a,Fallas,&valFal);
    CargarComponentes(a,b,c,d,validos,&validosB,&validosC,&validosD);
    validosE=Ensamble(b,c,d,e,validos,validosB,validosC,validosD);
    CargaFinales(e,validosE);
    CargaPerdidas(Fallas,valFal);

    return 0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

int CargarA(Componente x[],float Fal[],int *valF)
{
    FILE* arch=fopen("Componentes.bin","rb");
    Componente t;
    int i=0;
    if (arch!=NULL)
    {
        while (fread(&t,sizeof(Componente),1,arch)>0)
        {
            if(t.falla<2)
            {
                x[i]=t;
                i++;
            }
            else
            {
                Fal[*valF]=t.costo;
                (*valF)++;
            }
        }
        fclose(arch);
        return i;
    }
}

void CargarComponentes (Componente Aa[],Componente Ab[],Componente Ac[], Componente Ad[],int val,int* valb, int* valc, int* vald)
{
    CargarB(Aa,Ab,val,valb);
    CargarC(Aa,Ac,val,valc);
    CargarD(Aa,Ad,val,vald);
}

void CargarB (Componente Aa[],Componente Ab[],int val, int *valb)
{
    for(int i=0; i<val; i++)
    {
        if (strcmp(Aa[i].nombre,"Biblia")==0)
        {
            Ab[*valb]=Aa[i];
            (*valb)++;
        }
    }
}

void CargarC (Componente Aa[],Componente Ac[],int val, int *valc)
{
    for(int i=0; i<val; i++)
    {
        if (strcmp(Aa[i].nombre,"Copa de vino")==0)
        {
            Ac[*valc]=Aa[i];
            (*valc)++;
        }
    }
}

void CargarD (Componente Aa[],Componente Ad[],int val, int *vald)
{
    for(int i=0; i<val; i++)
    {
        if (strcmp(Aa[i].nombre,"Doll")==0)
        {
            Ad[*vald]=Aa[i];
            (*vald)++;
        }
    }
}

int Ensamble (Componente Ab[],Componente Ac[],Componente Ad[],PlayMobil Ae[],int val, int valb,int valc, int vald)
{
    float costComp;
    float costEn;
    int j=0;
    int y=0;
    for (int i=0; i<valb; i++)
    {
        j=0;
        while(Ac[j].calidad!=Ab[i].calidad && Ac[j].falla<2 && j<valc)
        {
            j++;
        }
        if (j<valc)
        {
            costComp=Ab[i].costo+Ac[j].costo;
            Ac[j].falla=2;
            j=0;
            while(Ad[j].calidad!=Ab[i].calidad && Ad[j].falla<2 && j<vald)
            {
                j++;
            }
            if (j<vald)
            {
                costComp=costComp+Ad[j].costo;
                Ad[j].falla=2;
                if(Ab[i].calidad=='a')
                {
                    costEn=costComp+14;
                    Ae[y].calidad='a';
                    Ae[y].costo=costEn;
                    y++;
                }
                else if (Ab[i].calidad=='b')
                {
                    costEn=costComp+12;
                    Ae[y].calidad='b';
                    Ae[y].costo=costEn;
                    y++;
                }
                else
                {
                    costEn=costComp+10;
                    Ae[y].calidad='c';
                    Ae[y].costo=costEn;
                    y++;
                }
            }
        }
    }
    return y;
}

void CargaFinales (PlayMobil e[],int val)
{
    FILE* arch= fopen("ProductosFinales.bin","wb");
    int i=0;
    if(arch!=NULL)
    {
        while(i<val)
        {
            fwrite(&e[i],sizeof(PlayMobil),1,arch);
            i++;
        }
        fclose(arch);
    }
}

void CargaPerdidas (float f[],int val)
{
    FILE* arch= fopen("Perdidas.bin","wb");
    int i=0;
    if(arch!=NULL)
    {
        while(i<val)
        {
            fwrite(&f[i],sizeof(float),1,arch);
            i++;
        }
        fclose(arch);
    }
}


