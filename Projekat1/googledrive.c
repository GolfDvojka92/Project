#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "googledrive.h"

char simboli[]=", ./<>?;':[]{}-=_+`~!@#$%^&*()";
FILE *fp;
int ulogovan=0;

int meni(account n)
{
    int a;
    if(ulogovan==0)
    {
        printf("|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*| \n");
        printf("|               Google drive                  | \n");
        printf("|                                             | \n");
        printf("| Dobrodosli!                                 | \n");
        printf("|                                             | \n");
        printf("| 1.Registracija                              | \n");
        printf("| 2.Login                                     | \n");
        printf("| 3.Izlaz                                     | \n");
        printf("|                                             | \n");
        printf("|                                             | \n");
        printf("|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*| \n");
        do
        {
            printf("Unesite komandu:");
            scanf("%d",&a);
            if(a==1)
            {
                registracija();
            }
            else if(a==2)
            {
                login();
            }
            else if(a==3)
            {
                return 0;
            }
            else
            {
                printf("Uneli ste nepostojecu komandu!\n");
            }
        }
        while(a<1 || a>3);
    }
    else
    {
        printf("|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*| \n");
        printf("|               Google drive                  | \n");
        printf("|                                             | \n");
        printf("| Dobrodosli!                                 | \n");
        printf("|                                             | \n");
        printf("| 1.Izmena naloga                             | \n");
        printf("| 2.Brisanje naloga                           | \n");
        printf("| 3.Logout                                    | \n");
        printf("| 4.Izlaz                                     | \n");
        printf("|                                             | \n");
        printf("|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*| \n");
        printf("Unesite komandu:");
        do
        {
            scanf("%d",&a);
            if(a==1)
            {
                editAccount(n);
            }
            else if(a==2)
            {
                removeAccount(n);
            }
            else if(a==3)
            {
                logout(n);
            }
            else if(a==4)
            {
                return 0;
            }
            else
            {
                printf("Uneli ste nepostojecu komandu! Pokusajte ponovo:");
            }
        }
        while(a<1 && a>4);
    }
}

void registracija()
{
    account n;
    int i,j;

    fp=fopen("nalozi.txt","r+");
    account nalozi[100];
    int brNaloga=0;
    char c;
    for(i=0;;i++)
    {
        fscanf(fp,"%s",nalozi[i].ime);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%s",nalozi[i].prezime);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%s",nalozi[i].nickname);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%s",nalozi[i].mail);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%s",nalozi[i].password);
        c=fgetc(fp);
        if(c==EOF)
        {
            break;
        }
        else
        {
            brNaloga++;
        }
    }
    fseek(fp,0,SEEK_END);

    ///IME

    printf("Ime:");
    IME:
    scanf("%s", n.ime);
    for(i=0;i<strlen(n.ime);i++)
    {
        for(j=0;j<strlen(simboli);j++)
        {
            if(n.ime[i]==simboli[j])
            {
                printf("Uneli ste ilegalan karakter! Molimo ponovo unesite ime:");
                goto IME;
            }
        }
    }

    fputs(n.ime,fp);
    fprintf(fp,"\n");

    ///PREZIME

    printf("Prezime:");
    PREZIME:
    scanf("%s", n.prezime);
    for(i=0;i<strlen(n.prezime);i++)
    {
        for(j=0;j<strlen(simboli);j++)
        {
            if(n.prezime[i]==simboli[j])
            {
                printf("Uneli ste ilegalan karakter! Molimo ponovo unesite ime:");
                goto PREZIME;
            }
        }
    }

    fputs(n.prezime,fp);
    fprintf(fp,"\n");

    ///NADIMAK

    printf("Nadimak:");
    NADIMAK:
    scanf("%s", n.nickname);
    for(i=0;i<strlen(n.nickname);i++)
    {
        for(j=0;j<strlen(simboli);j++)
        {
            if(n.nickname[i]==simboli[j])
            {
                printf("Uneli ste ilegalan karakter! Molimo ponovo unesite ime:");
                goto NADIMAK;
            }
        }
    }
    for(i=0;i<brNaloga;i++)
    {
        if(strcmp(nalozi[i].nickname,n.nickname)==0)
        {
            printf("Uneli ste postojeci nadimak! Molimo pokusajte ponovo:");
            goto NADIMAK;
        }
    }

    fputs(n.nickname,fp);
    fprintf(fp,"\n");

    ///MAIL

    char mailPr[]="@gmail.com";

    printf("Mail adresa(primer@gmail.com):");
    MAIL:
    scanf("%s",n.mail);
    if(strlen(n.mail)<10)
    {
        printf("Uneli ste neispravan mail! Molimo unesite ponovo:");
        goto MAIL;
    }
    if(strstr(n.mail,mailPr)==NULL)
    {
        printf("Uneli ste neispravan mail! Molimo unesite ponovo:");
        goto MAIL;
    }

    for(i=0;i<brNaloga;i++)
    {
        if(strcmp(nalozi[i].mail,n.mail)==0)
        {
            printf("Uneli ste postojecu mail adresu! Molimo pokusajte ponovo:");
            goto MAIL;
        }
    }

    fputs(n.mail,fp);
    fprintf(fp,"\n");

    ///SIFRA

    char confirmPass[100];
    SIFRA:
    printf("Sifra:");
    scanf("%s",n.password);
    if(strlen(n.password)<8)
    {
        printf("Uneli ste prekratku sifru:");
        goto SIFRA;
    }
    for(i=0;i<strlen(n.password);i++)
    {
        if(n.password[i]==' ')
        {
            printf("Uneli ste razmak u vasoj sifri! Pokusajte ponovo.\n");
            goto SIFRA;
        }
    }
    printf("Potvrdite sifru:");
    scanf("%s",confirmPass);
    if(strcmp(n.password,confirmPass)!=0)
    {
        printf("Unesene sifre nisu jednake! Molimo unesite sifru ponovo.\n");
        goto SIFRA;
    }

    fputs(n.password,fp);
    fprintf(fp,"\n\n");

    ///KRAJ

    printf("Uspesno ste se registrovali!\n\n");
    ulogovan=1;
    fclose(fp);
    meni(n);
}

void login()
{
    char temp[100];
    int i;
    fp=fopen("nalozi.txt", "r+");

    account nalozi[100];
    int brNaloga=0;
    char c;
    for(i=0;;i++)
    {
        fscanf(fp,"%s",nalozi[i].ime);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%s",nalozi[i].prezime);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%s",nalozi[i].nickname);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%s",nalozi[i].mail);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%s",nalozi[i].password);
        c=fgetc(fp);
        if(c==EOF)
        {
            fseek(fp,0,SEEK_SET);
            break;
        }
        else
        {
            brNaloga++;
        }
    }

    printf("Unesite nadimak ili mail adresu:");
    int redBr;
    NALOG:
    scanf("%s", temp);
    for(i=0;;i++)
    {
        if(strcmp(temp,nalozi[i].nickname)==0)
        {
            redBr=i;
            break;
        }
        if(strcmp(temp,nalozi[i].mail)==0)
        {
            redBr=i;
            break;
        }
        if(i==brNaloga)
        {
            printf("Uneli ste nepostojeci nalog! Pokusajte ponovo:");
            goto NALOG;
        }
    }
    char pass[100];
    printf("Sifra:");
    SIFRA:
    scanf("%s", pass);
    if(strcmp(pass,nalozi[redBr].password)!=0)
    {
        printf("Pogresna sifra! Pokusajte ponovo:");
        goto SIFRA;
    }
    printf("Uspesno ste se ulogovali!\n");
    ulogovan=1;
    fclose(fp);
    meni(nalozi[redBr]);
}

void logout(account n)
{
    printf("Izlogovali ste se.\n\n");
    ulogovan=0;
    meni(n);
}

void editAccount(account n)
{
    fp=fopen("nalozi.txt","r+");
    int a,i,j;

    char ceoFile[1000];
    char c;
    for(i=0;;i++)
    {
        c=fgetc(fp);
        ceoFile[i]=c;
        if(c==EOF)
        {
            break;
        }
    }
    fseek(fp,0,SEEK_SET);

    account nalozi[100];
    int brNaloga=0;
    for(i=0;;i++)
    {
        fscanf(fp,"%s",nalozi[i].ime);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%s",nalozi[i].prezime);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%s",nalozi[i].nickname);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%s",nalozi[i].mail);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%s",nalozi[i].password);
        c=fgetc(fp);
        if(c==EOF)
        {
            fseek(fp,0,SEEK_SET);
            break;
        }
        else
        {
            brNaloga++;
        }
    }

    int redBr;
    for(i=0;i<brNaloga;i++)
    {
        if(strcmp(n.nickname,nalozi[i].nickname)==0)
        {
            redBr=i;
            break;
        }
    }

    ///MENI

    {
    printf("|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*| \n");
    printf("|               Izmena naloga                 | \n");
    printf("|                                             | \n");
    printf("|  1.Ime i prezime                            | \n");
    printf("|  2.Nadimak                                  | \n");
    printf("|  3.Mail adresa                              | \n");
    printf("|  4.Sifra                                    | \n");
    printf("|                                             | \n");
    printf("|                                             | \n");
    printf("|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*| \n");
    }

    char confirmPass[100];
    do
    {
        printf("Izaberite izmenu:");
        scanf("%d",&a);

        ///IME I PREZIME

        if(a==1)
        {
            IME:
            printf("Unesite novo ime:");
            scanf("%s",n.ime);
            for(i=0;i<strlen(n.ime);i++)
            {
                for(j=0;j<strlen(simboli);j++)
                {
                    if(n.ime[i]==simboli[j])
                    {
                        printf("Uneli ste ilegalan karakter! Molimo ponovo unesite ime:");
                        goto IME;
                    }
                }
            }
            printf("Unesite novo prezime:");
            PREZIME:
            scanf("%s",n.prezime);
            for(i=0;i<strlen(n.prezime);i++)
            {
                for(j=0;j<strlen(simboli);j++)
                {
                    if(n.prezime[i]==simboli[j])
                    {
                        printf("Uneli ste ilegalan karakter! Molimo ponovo unesite ime:");
                        goto PREZIME;
                    }
                }
            }
            printf("Uspesno ste promenili ime i prezime!\n");
        }

        ///NADIMAK

        else if(a==2)
        {
            printf("Unesite novi nadimak:");
            NADIMAK:
            scanf("%s",n.nickname);
            for(i=0;i<strlen(n.nickname);i++)
            {
                for(j=0;j<strlen(simboli);j++)
                {
                    if(n.nickname[i]==simboli[j])
                    {
                        printf("Uneli ste ilegalan karakter! Molimo ponovo unesite ime:");
                        goto NADIMAK;
                    }
                }
            }
            if(strstr(ceoFile,n.nickname)!=NULL)
            {
                printf("Uneli ste postojeci nadimak! Molimo unesite ponovo:");
                goto NADIMAK;
            }
            printf("Uspesno ste promenili nadimak!\n");
        }

        ///MAIL

        else if(a==3)
        {
            printf("Unesite novi mail:");
            MAIL:
            scanf("%s",n.mail);
            if(strlen(n.mail)<10)
            {
                printf("Uneli ste neispravan mail! Molimo unesite ponovo:");
                goto MAIL;
            }
            if(strstr(n.mail,"@gmail.com")==NULL)
            {
                printf("Uneli ste neispravan mail! Molimo unesite ponovo:");
                goto MAIL;
            }
            if(strstr(ceoFile,n.mail)!=NULL)
            {
                printf("Uneli ste postojeci mail! Molimo unesite ponovo:");
                goto MAIL;
            }
            printf("Uspesno ste promenili mail!\n");
        }

        ///SIFRA

        else if(a==4)
        {
            SIFRA:
            printf("Unesite novu sifru:");
            scanf("%s",n.password);
            if(strlen(n.password)<8)
            {
                printf("Uneli ste prekratku sifru! Pokusajte ponovo.\n");
                goto SIFRA;
            }
            for(i=0;i<strlen(n.password);i++)
            {
                if(n.password[i]==' ')
                {
                    printf("Uneli ste razmak u vasoj sifri! Pokusajte ponovo.\n");
                    goto SIFRA;
                }
            }
            printf("Potvrdite sifru:");
            scanf("%s",confirmPass);
            if(strcmp(n.password,confirmPass)!=0)
            {
                printf("Unesene sifre nisu jednake! Molimo unesite sifru ponovo.\n");
                goto SIFRA;
            }
            printf("Uspesno ste promenili sifru!\n");
        }

        ///INVALIDNI UNOS

        else
        {
            printf("Uneli ste nepostojecu komandu!\n");
        }
    }
    while(a<1 || a>4);

    ///UPIS U FAJL

    strcpy(nalozi[redBr].ime,n.ime);
    strcpy(nalozi[redBr].prezime,n.prezime);
    strcpy(nalozi[redBr].nickname,n.nickname);
    strcpy(nalozi[redBr].mail,n.mail);
    strcpy(nalozi[redBr].password,n.password);

    for(i=0;i<brNaloga;i++)
    {
        fputs(nalozi[i].ime,fp);
        fprintf(fp,"\n");
        fputs(nalozi[i].prezime,fp);
        fprintf(fp,"\n");
        fputs(nalozi[i].nickname,fp);
        fprintf(fp,"\n");
        fputs(nalozi[i].mail,fp);
        fprintf(fp,"\n");
        fputs(nalozi[i].password,fp);
        fprintf(fp,"\n");
    }
    printf("Restartujte aplikaciju da uvaze promene.\n");
    meni(n);
}

void removeAccount(account n)
{
    fp=fopen("nalozi.txt","r+");
    account nalozi[100];
    char c;

    printf("Da li ste sigurni da zelite da obrisete nalog?(Y/N)");

    do
    {
        fflush(stdin);
        scanf("%c",&c);
        if(c=='y' || c=='Y')
        {
            break;
        }
        else if(c=='n' || c=='N')
        {
            meni(n);
        }
        else
        {
            printf("Uneli ste invalidan karakter! Pokusajte ponovo:");
        }
    }
    while(c!='y' || c!='Y' || c!='n' || c!='N');

    int brNaloga=0,i;
    for(i=0;;i++)
    {
        fscanf(fp,"%s",nalozi[i].ime);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%s",nalozi[i].prezime);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%s",nalozi[i].nickname);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%s",nalozi[i].mail);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%s",nalozi[i].password);
        c=fgetc(fp);
        if(c==EOF)
        {
            fseek(fp,0,SEEK_SET);
            break;
        }
        else
        {
            brNaloga++;
        }
    }
    fclose(fp);
    int index;
    for(i=0;i<brNaloga;i++)
    {
        if(strcmp(nalozi[i].nickname,n.nickname)==0)
        {
            index=i;
            printf("%d", index);
            break;
        }
    }

    fp=fopen("nalozi.txt","w");

    for(i=0;i<brNaloga;i++)
    {
        if(i!=index)
        {
            printf("%d",i);
            fputs(nalozi[i].ime,fp);
            fprintf(fp,"\n");
            fputs(nalozi[i].prezime,fp);
            fprintf(fp,"\n");
            fputs(nalozi[i].nickname,fp);
            fprintf(fp,"\n");
            fputs(nalozi[i].mail,fp);
            fprintf(fp,"\n");
            fputs(nalozi[i].password,fp);
            fprintf(fp,"\n");
        }
    }
    brNaloga--;
    fclose(fp);
    ulogovan=0;
    meni(n);
}
