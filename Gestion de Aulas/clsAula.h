#ifndef CLSAULA_H_INCLUDED
#define CLSAULA_H_INCLUDED

class Aula{
private:
    char nombre[5], deparLlave[10];
    int capacidad, numero;
    bool llave, disponibilidad, estado;

public:
    Aula(const char *n="ABC", const char *de="T", int c=0, bool l=true, bool d=true, bool e=false, int num=1)
    {
        strcpy(deparLlave, de);
        disponibilidad = d;
        strcpy(nombre, n);
        capacidad = c;
        numero = num;
        estado = e;
        llave = l;
    }
    void setDeparLlave(const char *d){strcpy(deparLlave, d);}
    void setDisponibilidad(bool d){disponibilidad = d;}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setCapacidad(int c){capacidad = c;}
    void setEstado(bool e){estado = e;}
    void setNumero(int n){numero = n;}
    void setLlave(bool l){llave = l;}
    bool getDisponibilidad(){return disponibilidad;}
    const char *getDeparLlave(){return deparLlave;}
    const char *getNombre(){return nombre;}
    int getCapacidad(){return capacidad;}
    bool getEstado(){return estado;}
    int getNumero(){return numero;}
    bool getLlave(){return llave;}
    void Cargar()
    {
        cout << "Ingrese el nombre: ";
        cargarCadena(nombre, 4);
        cout << "Ingrese la capacidad: ";
        cin >> capacidad;
        cout << "Se cierra con llave? 1 = si // 0 = no: ";
        cin >> llave;
        if(llave)
        {
            cout << "Ingrese el nombre del departamento encargado: ";
            cargarCadena(deparLlave, 9);
        }
        estado = true;
    }
    void Mostrar()
    {
        if(!estado){cout << "NO SE PUEDE UTILIZAR, AULA DADA DE BAJA" << endl;}

        cout << "El aula es: " << nombre << endl;
        cout << "Cuenta con una capacidad de: " << capacidad << " bancos" << endl;

        if(llave){cout << "Hay que pedir la llave a " << deparLlave << endl;}

        if(disponibilidad){cout << "Esta disponible" << endl;}
        else{cout << "Esta ocupada" << endl;}
    }
    void Mostrar_Peticion()
    {
        cout << "El aula " << nombre << " tiene " << capacidad << " bancos. ";
        if(disponibilidad){cout << "Esta disponible" << endl;}
        else{cout << "No esta disponible" << endl;}
    }
};

class ArchAula{
    private:
        char nombre[30];
    public:
        ArchAula(const char *n="aulas.dat"){strcpy(nombre, n);}
        Aula leerRegistro(int pos);
        void grabarRegistro(Aula obj);
        void modificarRegistro(Aula obj, int pos);
        void listarRegistros();
        int buscarRegistro(int num);
        int contarRegistros();
};


Aula ArchAula::leerRegistro(int pos){
    Aula obj;
    obj.setNumero(-1);
    FILE *p;
    p=fopen(nombre,"rb");
    if(p==nullptr){
        cout<<"ERROR DE ARCHIVO"<<endl;
        obj.setNumero(-2);
        return obj;
    }
    fseek(p, pos * sizeof obj, 0);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

void ArchAula::grabarRegistro(Aula obj){
    FILE *p;
    p=fopen(nombre,"ab");
    if(p==nullptr){
        cout<<"ERROR DE ARCHIVO"<<endl;
        return;
    }
    fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
}

void ArchAula::modificarRegistro(Aula obj, int pos){
    FILE *p;
    p=fopen(nombre,"rb+");
    if(p==nullptr){
        return;
    }
    fseek(p, pos * sizeof obj , 0);
    fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
}

void ArchAula::listarRegistros(){
    Aula obj;
    int cant = contarRegistros();
    for(int i=0; i<cant; i++){
        obj = leerRegistro(i);
        obj.Mostrar();
        if(obj.getEstado()) cout<<endl;
    }
}

int ArchAula::buscarRegistro(int num){
    Aula obj;
    int cant=contarRegistros();
    for(int i=0; i<cant; i++){
        obj = leerRegistro(i);
        if(obj.getNumero()==num){
            return i;
        }
    }
    return -1;
}

int ArchAula::contarRegistros(){
    FILE *p=fopen(nombre,"rb");
    if(p==nullptr){
        cout<<"ERROR DE ARCHIVO"<<endl;
        return -1;
    }
    fseek(p, 0, 2);
    int cant=ftell(p);
    fclose(p);
    return cant/sizeof(Aula);
}

#endif // CLSAULA_H_INCLUDED
