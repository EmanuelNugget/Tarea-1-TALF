#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <string>

using namespace std;

#define EstadoInicial 0
#define limit 1000            //limite multi-aplicado

void inicializar();

int imatriz;       //Cantidad de estados del AFD
int jmatriz;       //Cantidad de letras del alfabeto del AFD

int F[limit];      //Arreglo de estados finales
int long_F;        //Tamaño del arreglo de estados finales

char alfabeto[limit];     //Alfabeto del AFD

int T[limit][limit];      //Matriz de transiciones de un AFD

string mR0[limit][limit];  // Matriz R0 para expresion regular

string expRegular(int eInicial,int eFinal,int cEstados)            // retorna la expresion regular en un string
{
    if(cEstados == 0){
        return mR0[eInicial-1][eFinal-1];
    }
    else{
        if(eInicial == cEstados){
            char aux1[10];
            strcpy(aux1,expRegular(cEstados,eFinal,cEstados-1).c_str());
            if(strcmp(aux1,"V") == 0){
                return "V";
            }
            char aux2[10];
            strcpy(aux2,expRegular(cEstados,cEstados,cEstados-1).c_str());
            if(strcmp(aux2,"V") == 0){
                return "L";
            }
            else{
                return "("+expRegular(cEstados,cEstados,cEstados-1)+")*"+expRegular(cEstados,eFinal,cEstados-1);
            }
        }
        if(eFinal == cEstados){
            char aux3[10];
            strcpy(aux3,expRegular(eInicial,cEstados,cEstados-1).c_str());
            if(strcmp(aux3,"V") == 0){
                return "V";
            }
            char aux4[10];
            strcpy(aux4,expRegular(cEstados,cEstados,cEstados-1).c_str());
            if(strcmp(aux4,"V") == 0){
                return "L";
            }
            else{
                return expRegular(eInicial,cEstados,cEstados-1)+"("+expRegular(cEstados,cEstados,cEstados-1)+")*";
            }
        }
        if(eFinal == cEstados && eInicial == cEstados && eFinal == eInicial){
            char aux5[10];
            strcpy(aux5,expRegular(cEstados,cEstados,cEstados-1).c_str());
            if(strcmp(aux5,"V") == 0){
                return "V";
            }
            else{
                return "("+expRegular(cEstados,cEstados,cEstados-1)+")^+";
            }
        }
        else{
            char aux6[10];
            char aux7[10];
            strcpy(aux6,expRegular(eInicial,cEstados,cEstados-1).c_str());
            strcpy(aux7,expRegular(cEstados,eFinal,cEstados-1).c_str());
            if(strcmp(aux6,"V") == 0 || strcmp(aux7,"V") == 0){
                return expRegular(eInicial,eFinal,cEstados-1);
            }
            else{
                char aux8[10];
                strcpy(aux8,expRegular(cEstados,cEstados,cEstados-1).c_str());
                if(strcmp(aux8,"(L)*") == 0){
                    return expRegular(eInicial,eFinal,cEstados-1)+"+"+expRegular(eInicial,cEstados,cEstados-1)+expRegular(cEstados,eFinal,cEstados-1);
                }
                else{
                    return expRegular(eInicial,eFinal,cEstados-1)+"+"+expRegular(eInicial,cEstados,cEstados-1)+"("+expRegular(cEstados,cEstados,cEstados-1)+")*"+expRegular(cEstados,eFinal,cEstados-1);
                }
            }
        }
    }
}

void mostrarGramatica()    //Muestra la Gramatica regular de un AFD
{
    char estados[26]={'S','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','T','U','V','W','X','Y','Z'};
    string espacios;
    cout << "\nE = {";
    for(int i=0;i<jmatriz;i++){
        cout << alfabeto[i];
        espacios+=" ";
        if(i+1 < jmatriz)
            cout << ",";
    }
    cout << "}\nN = {";
    for(int i=0;i<imatriz;i++){
        cout << estados[i];
        if(i+1 < imatriz)
            cout << ",";
    }
    cout << "}\nS = {" << estados[0] << "}\nP = {";
    for(int i=0;i<imatriz;i++){
        cout << "\n      " << estados[i] << " -------> ";
        for(int j=0;j<jmatriz;j++){
            cout << alfabeto[j] << estados[T[i][j]];
            if(j+1 < jmatriz){
                cout << " | ";
            }
        }
        for(int k=0;k<long_F;k++){
            if(i == F[k]){
                cout << " | lambda ";
                espacios+="         ";
            }
        }
    }
    cout << espacios << "}\n\n";
}

bool comprobarPalabra(char word[],int n)      //Comprueba si una palabra ingresada por teclado pertenece al lenguaje
{
    int wint[1000];

    for(int i=0;i<n;i++){
        for(int j=0;j<imatriz;j++){
            if(word[i] == alfabeto[j])
                wint[i] = j;
        }
    }

    int i=0;
    int q=0;
    while(i < n){
        q = T[q][wint[i]];
        i++;
    }

    for(int j=0;j<long_F;j++){
        if(q == F[j])
            return true;
    }
    return false;
}

void mostrarPalabras()        //Muestra de 1 a 5 palabras que pertenecen al lenguaje
{
    int n=0,m=0,largo=0,cant_palabras=0,cont1=0,cont2=0,k = 0;
    char w[1000];
    cout << "\nIngrese Cantidad de Palabras: ";
    cin >> cant_palabras;
    cin.sync();
    system("CLS");

    cout << "\nMostrando " << cant_palabras << " Palabra|s";

    srand(time(0));

    while(cont1 < cant_palabras){
        largo=0;
        cont2=0;
        n = 0;
        for(int i=0;i<1000;i++){
            w[i] = '\0';
        }
        while(cont2 < jmatriz){
            n = rand()%20;
            for(int i=0;i<n;i++){
                k = rand()%jmatriz;
                w[i+largo] = alfabeto[k];
            }
            largo+=n;
            cont2++;
        }
        if(comprobarPalabra(w,largo)){
            cout << "\n\nPalabra " << cont1+1 << ":\n\n";
            for(int i=0;i<jmatriz;i++){
                m=0;
                for(int j=0;j<largo;j++){
                    if(alfabeto[i] == w[j]){
                        m++;
                    }
                }
                cout << "  |" << alfabeto[i] << "| = " << m;
            }
            cout << "  |w| = " << largo << "\n\n   w = ";
            for(int i=0;i<largo;i++)
                cout << w[i];
            cont1++;
        }
    }
    cout << "\n\n";
}

void menu()
{
    system("CLS");
    char palabra[1000];
    int long_p=0;
    char opt1;
    cout << "\n******************* MENU *******************\n\n1.- Mostrar Palabras que Pertenecen al Lenguaje.\n2.- Comprobar si una palabra pertenece al Lenguaje.\n3.- Mostrar Gramatica Regular.\n4.- Mostrar Expresion Regular.\n5.- Volver a Ingresar AFD.\n6.- Salir\n\nIngrese Opcion: ";
    cin >> opt1;
    int opt=0;
    if(opt1 < 49 || opt1 > 54){
        cout << "\nOpcion Ingresada no Valida, ";
        system("PAUSE");
        menu();
    }
    else{
        opt = opt1 - 48;
        switch (opt)
        {
        case 1:
            mostrarPalabras();
            system("PAUSE");
            menu();
            break;
        case 2:
            cout << "\nIngrese una Palabra: ";
            cin >> palabra;
            while(palabra[long_p] != '\0'){
                long_p++;
            }
            if(comprobarPalabra(palabra,long_p))
                cout << "\nLa Palabra Pertenece al Lenguaje.\n" << endl;
            else
                cout << "\nLa Palabra NO Pertenece al Lenguaje.\n" << endl;
            system("PAUSE");
            menu();
            break;
        case 3:
            mostrarGramatica();
            system("PAUSE");
            menu();
            break;
        case 4:
            cout << "\n Expresion Regular: \n\n";                     //usar cuando se pueda construir la matriz R0 a partir de la matriz de transiciones
            for(int i=0;i<long_F;i++){
                if(i > 0)
                    cout << "+";
                cout << " " << expRegular(EstadoInicial+1,F[i]+1,imatriz);
            }
            cout << "\n\n";
            system("PAUSE");
            menu();
            break;
        case 5:
            inicializar();
        case 6:
            exit(0);
        default:
            cout << "\nOpcion Ingresada no Valida, ";
            system("PAUSE");
            menu();
            break;
        }
    }
}

void inicializar()
{
    system("CLS");
    int tam_alf=0,estados=0,est_fnl=0;
    cout << "\nIngrese Cantidad de Letras del Alfabeto: ";
    cin >> tam_alf;

    jmatriz = tam_alf;

    cout << "\nIngrese las Letras del Alfabeto: \n";
    for(int i=0;i<tam_alf;i++){
        cout << "\nE (" << i << ") = ";
        cin >> alfabeto[i];
    }

    cout << "\nIngrese Cantidad de Estados del AFD: ";
    cin >> estados;

    imatriz = estados;

    cout << "\nIngrese Cantidad de Estados Finales del AFD: ";
    cin >> est_fnl;
    long_F = est_fnl;
    cout << "\nIngrese Estados Finales del AFD: \n";
    for(int i=0;i<est_fnl;i++){
        cout << "\nq (F" << i << ") = ";
        cin >> F[i];
    }

    for(int i=0;i<estados;i++){
        for(int j=0;j<tam_alf;j++){
            T[i][j] = 0;
        }
    }

    cout << "\nIngrese la Matriz de Transiciones del AFD: \n\n";
    for(int i=0;i<estados;i++){
        for(int j=0;j<tam_alf;j++){
            cout << "  q" << i << " -> " << alfabeto[j] << " = ";
            cin >> T[i][j];
        }
    }

    for(int i=0;i<imatriz;i++){
        for(int j=0;j<imatriz;j++){
            if(i == j)
                mR0[i][j] = "L";
            else
                mR0[i][j] = "\0";
        }
    }
    char aux[10];
    for(int i=0;i<imatriz;i++){
        for(int j=0;j<jmatriz;j++){
            strcpy(aux,mR0[i][T[i][j]].c_str());
            if(i == T[i][j] && strcmp(aux,"\0") != 0){
                mR0[i][T[i][j]] = mR0[i][T[i][j]]+"+"+alfabeto[j];
            }
            else{
                mR0[i][T[i][j]] = alfabeto[j];
            }
        }
    }

    char aux2[10];
    for(int i=0;i<imatriz;i++){
        for(int j=0;j<imatriz;j++){
            strcpy(aux2,mR0[i][j].c_str());
            if(strcmp(aux2,"\0") == 0)
                mR0[i][j] = "V";
        }
    }

    cout << "\n\n Datos Completados Correctamente. ";
    system("PAUSE");
    menu();
}

int main()
{
    inicializar();
    return 0;
}
