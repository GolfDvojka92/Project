#ifndef GOOGLEDRIVE_H_INCLUDED
#define GOOGLEDRIVE_H_INCLUDED

typedef struct
{
    char ime[20];
    char prezime[20];
    char nickname[100];
    char mail[100];
    char password[100];
}account;

typedef struct
{
    char naziv[20];
    char link[5];
    char fajlovi[50][20];
    char kreator[20];
    char access[100];
}folder;

void nizFoldera();

void meni();
void registracija();
void login();
void logout();
void editAccount();
void removeAccount();

void createFolder();
void editFolder();
void shareFolder();
void searchFolder();
void driveAccess();
void removeFolder();



#endif // GOOGLEDRIVE_H_INCLUDED
