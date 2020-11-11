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

int meni();
void registracija();
void login();
void logout();
void editAccount();
void removeAccount();


#endif // GOOGLEDRIVE_H_INCLUDED
