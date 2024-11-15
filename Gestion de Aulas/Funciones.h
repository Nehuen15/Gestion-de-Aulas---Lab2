#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

void mostrarDepCompleto(int codigo), verAulas(), verComisiones(int CodDep), verComisiones(const char *nombre);
void verInfoDep(int CodDep), PedirCambios(int CodDep);
Departamento buscarDep(int Cod);

///Admin
void allComisiones(), darBaja(int legajo), darAlta(int dni);
int verificarUsuario(int dni);

void darAlta(const char *rol="Becado"), darBaja(int cod, int legajo, const char *rol);

void allComisiones()    //  SOLO COMISIONES ACTIVAS
{
    ArchComision arch;
    arch.listarRegistros();
}

int verificarUsuario(int dni)
{
    Usuario obj;
    ArchUsuario arch;

    int tam = arch.contarRegistros();
    for(int i=0; i<tam; i++)
    {
        obj = arch.leerRegistro(i);
        if(obj.getDni() == dni)
        {
            return i;
        }
    }
    return -8;
}

void darAlta()          //  Buscar por Dni
{
    cout << "Ingrese el Dni de la persona: ";
    cin >> dni;
    cout << endl;

    int verificacion = verificarUsuario(dni);

    if(verificacion >= 0)
    {
        //Modificar estado y registro
        Usuario obj;
        ArchUsuario arch;

        obj = arch.leerRegistro(verificacion);
        obj.setEstado(true);
        arch.modificarRegistro(obj, verificacion);
        obj.Mostrar();
        cout << endl << obj.getNombre() << " " << obj.getApellido() << " Existe en el sistema y fue dado de Alta exitosamente" << endl;

    }
    else{Alta_Usuarios(dni);}
}

void darBaja() //buscar por Legajo
{
    Usuario obj;
    ArchUsuario arch;

    cout << "Ingrese el legajo de la persona: ";
    cin >> legajo;

    int tam = arch.contarRegistros();
    for(int i=0; i<tam; i++)
    {
        obj = arch.leerRegistro(i);
        if(obj.getLegajo() == legajo)
        {
            obj.setEstado(false);
            arch.modificarRegistro(obj, i);
            cout << "Dado de Baja Correctamente" << endl;
            system("pause");
            return;
        }
    }
    cout << "No se encontro el usuario" << endl;
    system("pause");
}


void darBaja(int cod, const char *rol) //buscar por Legajo
{
    Usuario obj;
    ArchUsuario arch;

    cout << "Ingrese el legajo de la persona: ";
    cin >> legajo;

    int tam = arch.contarRegistros();
    for(int i=0; i<tam; i++)
    {
        obj = arch.leerRegistro(i);
        if(obj.getLegajo() == legajo && obj.getRol() == rol && obj.getCodDep() == cod)
        {
            obj.setCodDep(0);
            arch.modificarRegistro(obj, i);
            cout << "Eliminado del Departamento Correctamente" << endl;
            system("pause");
            return;
        }
    }
    cout << "No se encontro el becado" << endl;
    system("pause");
}

void darAlta(int CodDep,const char *rol)          //  Buscar por Dni
{
    int dni;

    cout << "Ingrese el Dni de la persona: ";
    cin >> dni;
    cout << endl;

    int verificacion = verificarUsuario(dni);

    if(verificacion >= 0)
    {
        //Modificar estado y registro
        Usuario obj;
        ArchUsuario arch;

        obj = arch.leerRegistro(verificacion);
        obj.setEstado(true);
        arch.modificarRegistro(obj, verificacion);
        obj.Mostrar();
        cout << endl << obj.getNombre() << " " << obj.getApellido() << " Existe en el sistema y fue dado de Alta exitosamente" << endl;

    }
    else{Alta_Usuarios(CodDep, dni, rol);}
}


Departamento buscarDep(int Cod)
{
    Departamento obj, aux;
    ArchDep arch;

    int tam = arch.contarRegistros();
    for(int i=0; i<tam; i++)
    {
        obj = arch.leerRegistro(i);
        if(obj.getCodigo() == Cod)
        {
            aux = obj;
            return aux;
        }
    }
    obj.setCodigo(-1);
    return obj;
}

void verInfoDep(int CodDep)
{
    Departamento obj;

    obj = buscarDep(CodDep);
    if(obj.getCodigo() != -1)
    {
        obj.MostrarTodo();
    }
    else{cout << "no se encontro";}
}

void mostrarDepCompleto(int codigo)
{
    Usuario obj;
    ArchUsuario arch;
    Comision com;
    ArchComision archC;

    int tam = arch.contarRegistros();
    for(int i=0; i<tam; i++)
    {
        obj = arch.leerRegistro(i);
        if(obj.getCodDep() == codigo)
        {
            cout << obj.getRol() << ": " << obj.getNombre() <<endl;
        }
    }

    tam = archC.contarRegistros();
    for(int i=0; i<tam; i++)
    {
        com = archC.leerRegistro(i);
        if(com.getCodDep() == codigo)
        {
            cout << "A cargo de la Comision: " << com.getCodComision() << endl;
        }
    }
}

void verAulas()
{
    Aula obj;
    ArchAula archA;

    system("cls");
    int tam = archA.contarRegistros();
    //Crear un vector de objAula para pedir aulas
    //Usar dos variables para localizar el mostrar()
    for(int i=0; i<tam; i++)
    {
        obj = archA.leerRegistro(i);
        obj.Mostrar_Peticion();
    }
}

void verComisiones(int CodDep)
{
    Comision comi;
    ArchComision arch;

    system("cls");
    int tam = arch.contarRegistros();
    for(int i=0; i<tam; i++)
    {
        comi = arch.leerRegistro(i);
        if(comi.getCodDep() == CodDep)
        {
            comi.Mostrar_Becado();
            cout << endl;
        }
    }

}

void verComisiones(const char *nombre)
{
    Comision comi;
    ArchComision arch;

    system("cls");
    int tam = arch.contarRegistros();
    for(int i=0; i<tam; i++)
    {
        comi = arch.leerRegistro(i);
        if(strcmp(comi.getProfe(), nombre)==0)
        {
            comi.Mostrar_Docente();
            cout << endl;
        }
    }

}

void PedirCambios(int CodDep) /// Vector Dinamico, ingresar el nombre del aula y cantidad de alumnos. GRABAR ARCH Cambios.dat
{
    Aula obj;
    ArchAula arch;

    int tam = arch.contarRegistros();
    for(int i=0; i<tam; i++)
    {
        obj = arch.leerRegistro(i);
        if(strcmp(obj.getNombre(), "A4") == 0)
        {
            cout << obj.getNombre() <<": " << obj.getDisponibilidad() << endl;
        }
    }
}


#endif // FUNCIONES_H_INCLUDED
