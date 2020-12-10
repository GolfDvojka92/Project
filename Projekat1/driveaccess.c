#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "googledrive.h"

void driveAccess(account n)
{
    int a;

    printf("|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*| \n");
    printf("|               Google drive                  | \n");
    printf("|                                             | \n");
    printf("| 1.Kreiranje foldera                         | \n");
    printf("| 2.Izmena foldera                            | \n");
    printf("| 3.Deljenje foldera                          | \n");
    printf("| 4.Pretraga foldera                          | \n");
    printf("| 5.Uklanjanje foldera                        | \n");
    printf("| 6.Podesavanje naloga                        | \n");
    printf("|                                             | \n");
    printf("|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*| \n");
    printf("Izaberite komandu:");
    do
    {
        fflush(stdin);
        scanf("%d", &a);
        switch(a)
        {
            case 1:
                createFolder(n);
            case 2:
                editFolder(n);
            case 3:
                shareFolder(n);
            case 4:
                searchFolder(n);
            case 5:
                removeFolder(n);
            case 6:
                meni(n);
            default:
                printf("Uneli ste nepostojecu komandu!Pokusajte ponovo:");
        }
    }
    while(a<1 || a>5);
}

void createFolder(account n)
{
    int i,brFoldera;
    FILE *fp;
    fp=fopen("folderi.txt","r+");

    ///NIZ SVIH FOLDERA

    folder niz[40];
    nizFoldera(fp,niz,&brFoldera);

    folder k;
    int random;
    time_t t;

    ///IME FOLDERA

    printf("Unesite ime foldera:");
    naziv:
    scanf("%s", k.naziv);

    for(i=0;i<brFoldera;i++)
    {
        if(strcmp(k.naziv,niz[i].naziv)==0)
        {
            printf("Uneli ste postojece ime foldera! Pokusajte ponovo:");
            goto naziv;
        }
    }

    fprintf(fp,"%s\n",k.naziv);

    ///LINK FOLDERA

    srand((char)time(&t));

    for(i=0;i<5;i++)
    {
        random=(rand()%75)+48;
        while((random>90&&random<97) || (random>57&&random<65))
        {
            random=(rand()%75)+48;
        }
        k.link[i]=random;
    }
    fprintf(fp,"%s\n",k.link);

    ///VLASNIK FOLDERA

    fprintf(fp,"%s\n",n.nickname);

    ///PRISTUP

    fprintf(fp,"0\n\n");

    ///ISPIS I KRAJ

    system("cls");
    printf("Uspesno ste kreirali folder!\n");

    fclose(fp);
    driveAccess(n);
}

void editFolder(account n)
{
    FILE *fp;

    ///NIZ NALOGA

    fp=fopen("nalozi.txt","r+");
    account nalozi[100];
    int brNaloga=0,i;
    char c;
    for(i=0;;i++)
    {
        if(c==EOF)
        {
            break;
        }
        fscanf(fp,"%s",nalozi[i].ime);
        fgetc(fp);
        fscanf(fp,"%s",nalozi[i].prezime);
        fgetc(fp);
        fscanf(fp,"%s",nalozi[i].nickname);
        fgetc(fp);
        fscanf(fp,"%s",nalozi[i].mail);
        fgetc(fp);
        fscanf(fp,"%s",nalozi[i].password);
        c=fgetc(fp);
    }
    brNaloga=i-1;
    fclose(fp);

    fp=fopen("folderi.txt","r+");

    ///NIZ SVIH FOLDERA

    folder niz[40];
    int brFoldera,a;
    nizFoldera(fp,niz,&brFoldera);

    for(i=0;i<brFoldera;i++)
    {
        printf("\t%d. %s\n",i+1,niz[i].naziv);
    }
    printf("Izaberite zeljeni folder za izmenu:");
    do
    {
        fflush(stdin);
        scanf("%d",&a);
        printf("%s\n",niz[i].kreator);
        if(strcmp(niz[a-1].kreator,n.nickname)!=0)
        {
            printf("Nemate pristup ovom folderu! Izaberite folder sa pristupom:");
        }
    }
    while(strcmp(niz[a-1].kreator,n.nickname)!=0);

    int k;
    char temp[100];
    printf("\t1.Naziv\n\t2.Pristup\nIzaberite sta zelite da izmenite:");
    scanf("%d",&k);
    switch(k)
    {
    case 1:
        {
            printf("Unesite novo ime foldera:");
            naziv:
            scanf("%s",temp);
            for(i=0;i<brFoldera;i++)
            {
                if(strcmp(temp,niz[i].naziv)==0)
                {
                    printf("Uneli ste postojece ime foldera! Pokusajte ponovo:");
                    goto naziv;
                }
            }
            strcpy(niz[a-1].naziv,temp);
        }
        break;
    case 2:
        {
            printf("Unesite mail adrese korisnika kojim dajete pristup (odvojene razmacima, max 10)\n");
            unos:
            fflush(stdin);
            gets(niz[a-1].access);

            int brRazmaka=0;
            if(strcmp(niz[a-1].access,"0")==0)
            {
                goto kraj;
            }
            for(i=0;i<strlen(niz[a-1].access);i++)
            {
                if(niz[a-1].access[i]==' ')
                {
                    brRazmaka++;
                }
            }

            int checker=0;

            for(i=0;i<brNaloga;i++)
            {
                if(strstr(niz[a].access,nalozi[i].mail)!=NULL)
                {
                    checker++;
                }
            }
            if(checker!=brRazmaka+1)
            {
                printf("Neispravan unos mejlova! Pokusajte ponovo:");
                goto unos;
            }
        }
    }
    kraj:

    fseek(fp,0,SEEK_SET);

    for(i=0;i<brFoldera;i++)
    {
        fprintf(fp,"%s\n",niz[i].naziv);
        fprintf(fp,"%s\n",niz[i].link);
        fprintf(fp,"%s\n",niz[i].kreator);
        fprintf(fp,"%s\n\n",niz[i].access);
    }
    system("cls");
    printf("Fajl uspesno izmenjen!\n");

    fclose(fp);
    driveAccess(n);
}

void removeFolder(account n)
{
    FILE *fp;
    fp=fopen("folderi.txt","r+");

    ///NIZ SVIH FOLDERA

    folder niz[40];
    int brFoldera,i,a;
    nizFoldera(fp,niz,&brFoldera);

    for(i=0;i<brFoldera;i++)
    {
        printf("\t%d. %s\n",i+1,niz[i].naziv);
    }
    printf("Izaberite zeljeni folder za brisanje:");
    do
    {
        fflush(stdin);
        scanf("%d",&a);
        printf("%s\n",niz[i].kreator);
        if(strcmp(niz[a-1].kreator,n.nickname)!=0)
        {
            printf("Nemate pristup ovom folderu! Izaberite folder sa pristupom:");
        }
    }
    while(strcmp(niz[a-1].kreator,n.nickname)!=0);
    char c;
    printf("Da li ste sigurni da zelite da obriste zeljeni folder?(Y/N)");
    do
    {
        fflush(stdin);
        scanf("%c",&c);
        switch(c)
        {
            case 'Y':
            case 'N':
            case 'y':
            case 'n':
            {
                break;
            }
            default:
            {
                printf("Nepostojeca komanda! Pokusajte ponovo:");
            }
        }
    }
    while(c!='Y' && c!='N' && c!='y' && c!='n');
    fclose(fp);
    fp=fopen("folderi.txt","w");
    for(i=0;i<brFoldera;i++)
    {
        if(a-1==i)
        {
            continue;
        }
        fprintf(fp,"%s\n",niz[i].naziv);
        fprintf(fp,"%s\n",niz[i].link);
        fprintf(fp,"%s\n",niz[i].kreator);
        fprintf(fp,"%s\n\n",niz[i].access);
    }
    fclose(fp);
    system("cls");
    printf("Uspesno ste obrisali folder!\n");
    driveAccess(n);
}

void shareFolder(account n)
{
    int a,i,brFoldera;
    FILE *fp;

    ///NIZ NALOGA

    fp=fopen("nalozi.txt","r+");
    account nalozi[100];
    int brNaloga=0;
    char c;
    for(i=0;;i++)
    {
        if(c==EOF)
        {
            break;
        }
        fscanf(fp,"%s",nalozi[i].ime);
        fgetc(fp);
        fscanf(fp,"%s",nalozi[i].prezime);
        fgetc(fp);
        fscanf(fp,"%s",nalozi[i].nickname);
        fgetc(fp);
        fscanf(fp,"%s",nalozi[i].mail);
        fgetc(fp);
        fscanf(fp,"%s",nalozi[i].password);
        c=fgetc(fp);
    }
    brNaloga=i-1;
    fclose(fp);

    ///NIZ SVIH FOLDERA

    fp=fopen("folderi.txt","r+");

    folder niz[40];
    nizFoldera(fp,niz,&brFoldera);

    ///ISPIS SVIH FOLDERA

    for(i=0;i<brFoldera;i++)
    {
        printf("\t%d. %s\n",i+1,niz[i].naziv);
    }
    printf("Izaberite zeljeni folder za deljenje:");
    fflush(stdin);
    scanf("%d",&a);
    a--;

    printf("Unesite mail adrese korisnika kojim dajete pristup (odvojene razmacima, max 10)\n");
    unos:
    fflush(stdin);
    gets(niz[a].access);

    int brRazmaka=0;
    for(i=0;i<strlen(niz[a].access);i++)
    {
        if(niz[a].access[i]==' ')
        {
            brRazmaka++;
        }
    }

    int checker=0;

    for(i=0;i<brNaloga;i++)
    {
        if(strstr(niz[a].access,nalozi[i].mail)!=NULL)
        {
            checker++;
        }
    }
    if(checker!=brRazmaka+1)
    {
        printf("Neispravan unos mejlova! Pokusajte ponovo:");
        goto unos;
    }

    ///UPIS U FAJL

    fseek(fp,0,SEEK_SET);

    for(i=0;i<brFoldera;i++)
    {
        fprintf(fp,"%s\n",niz[i].naziv);
        fprintf(fp,"%s\n",niz[i].link);
        fprintf(fp,"%s\n",niz[i].kreator);
        fprintf(fp,"%s\n\n",niz[i].access);
    }
    system("cls");
    printf("Fajl uspesno podeljen!\n");

    fclose(fp);
    driveAccess(n);
}

void searchFolder(account n)
{
    FILE *fp;
    fp=fopen("folderi.txt","r+");

    ///NIZ SVIH FOLDERA

    folder niz[40];
    int brFoldera,i;
    nizFoldera(fp,niz,&brFoldera);

    char temp[100];
    printf("Pretraga:");
    scanf("%s",temp);

    int brojac=1;
    for(i=0;i<brFoldera;i++)
    {
        if(strstr(niz[i].naziv,temp)!=NULL)
        {
            printf("\t%d.%s\n",brojac,niz[i].naziv);
            brojac++;
        }
    }
    printf("\n");
    int k;
    printf("1.Drive\n2.Meni\nUnesite komandu:");
    scanf("%d",&k);
    switch(k)
    {
    case 1:
        {
            driveAccess(n);
        }
    case 2:
        {
            meni();
        }
    }
}

void nizFoldera(FILE *fp,folder *niz,int *brFoldera)
{
    char c;
    int i;
    for(i=0;;i++)
    {
        if(c==EOF)
        {
            break;
        }
        fscanf(fp,"%s", niz[i].naziv);
        fgetc(fp);
        fscanf(fp,"%s", niz[i].link);
        fgetc(fp);
        fscanf(fp,"%s", niz[i].kreator);
        fgetc(fp);
        fscanf(fp,"%s", niz[i].access);
        c=fgetc(fp);
    }
    *brFoldera=i-1;
    fseek(fp,0,SEEK_END);

}
