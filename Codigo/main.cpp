#include <iostream>
#include <cstdlib>
#define MAX_USUARIOS 50
#define MAX_AMIGOS 60
#define MAX_SOLICITUDES 20
#define MAX_LISTAS 10
#define MAX 3

using namespace std;

struct fecha
{
    int diaNacimiento;
    int mesNacimiento;
    int anioNacimiento;
};

struct solicitudes
{
    string nombre;
    string apellido;
    string correo;
    fecha fecha;
};

struct amigosEnComun
{
    string nombre;
    string apellido;
};

struct amigos
{
    string nombre;
    string apellido;
    string correo;
    fecha fecha;
};

struct listasAmigos
{
    string nombreLista;
    amigosEnComun amigos[MAX_AMIGOS];
    int posicionAmigo;
};

struct usuario
{
    string nombre;
    char infoNombre = 's';
    string apellido;
    char infoApellido = 's';
    string contrasenia;
    string correoElectronico;
    char infoCorreo;
    fecha fechaNacimiento;
    char infoFecha;
    solicitudes solicitudAmistad[  MAX_SOLICITUDES ];
    int cantidadSolicitudes;
    amigos amigosAceptados[ MAX_AMIGOS ];
    int cantidadAmigos;
    int estadisticaJuego[ MAX_AMIGOS ];
    int infojuego;
    listasAmigos listas[MAX_LISTAS];
    int cantidadListas;
    amigosEnComun amigosMutuos[ MAX_AMIGOS ];
    int cantidadAmigosEnComun;
};

int menuPrincipal();
char menuInscribirse( usuario [ MAX_USUARIOS ] );
void menuIngresar( usuario [ MAX_USUARIOS ] );
int menuUsuario();
void menuEditarPerfil( usuario [ MAX_USUARIOS], int );
void menuAmigos( usuario [ MAX_USUARIOS], int );
void menuTriqui( usuario [ MAX_USUARIOS], int );
bool buscarCorreoElectronico( usuario [ MAX_USUARIOS ], string );
bool buscarNombreLista ( usuario [ MAX_USUARIOS ], string, int );
int jugarTriqui();
bool verificarGanador1(int matriz[][MAX]);
bool verificarGanador2(int matriz[][MAX]);

int numeroUsuarios = 0;
int solicitudesAmistad = 0;

int main()
{
    int opcionMenuPrincipal;
    int opcionMenuIngresar;
    char opcionMenuInscrbirse;
    char continuar;
    usuario cliente[ MAX_USUARIOS ];

    do
    {
        opcionMenuPrincipal = menuPrincipal();
        switch (opcionMenuPrincipal)
        {
        case 1:

            do
            {
                opcionMenuInscrbirse = menuInscribirse( cliente );
            }
            while(opcionMenuInscrbirse == 's' || opcionMenuInscrbirse == 'S');


            break;
        case 2:
            menuIngresar( cliente );

            break;
        case 3:
            cout << "Muchas gracias, vuelva pronto" << endl;
            exit(0);

            break;
        default:
            cout << "Error" << endl;
            break;
        }
    }
    while (opcionMenuPrincipal != 3);


    return 0;
}

int menuPrincipal()
{
    int opcion;

    cout << " _______________MyBook______________ " << "\n";
    cout << "|___________________________________|" << "\n";
    cout << "|                                   |" << "\n";
    cout << "|          1. Inscribirse           |" << "\n";
    cout << "|          2. Sign-in               |" << "\n";
    cout << "|          3. Salir                 |" << "\n";
    cout << "|___________________________________|" << "\n";
    cout << "|___________________________________|" << "\n";
    cin >> opcion;

    return opcion;
}

char menuInscribirse( usuario user[ MAX_USUARIOS ] )
{

    char continuar;
    bool encontro;
    cout << endl << endl;
    cout << "...Bienvenido a MyBok..." << endl;

    cout << "Digite su nombre: ";
    cin >> user[ numeroUsuarios ].nombre;

    cout << "Digite su apellido: ";
    cin >> user[ numeroUsuarios ].apellido;

    do
    {
        cout << "Digite su Correo electronico: ";
        cin >> user[numeroUsuarios].correoElectronico;

        encontro = buscarCorreoElectronico( user, user[numeroUsuarios].correoElectronico );
        if( encontro == true)
        {
            cout << "Vuelva a escribir un correo valido" << endl;
        }
        else
        {
            encontro = false;
        }
    }
    while (encontro == true);

    cout << "Desea que su correo sea publico (s/n): ";
    cin >> user[numeroUsuarios].infoCorreo;


    cout << "Digite su contrase" << char (164) <<"a: ";
    cin >> user[numeroUsuarios].contrasenia;

    cout << "Digite su fecha de nacimiento" << endl;
    cout << "Dia: ";
    cin >> user[numeroUsuarios].fechaNacimiento.diaNacimiento;
    cout << "Mes: ";
    cin >> user[numeroUsuarios].fechaNacimiento.mesNacimiento;
    cout << "A" << char (164) <<"o: ";
    cin >> user[numeroUsuarios].fechaNacimiento.anioNacimiento;
    cout << "Desea que su fecha de nacimiento sea publica (s/n): ";
    cin >> user[numeroUsuarios].infoFecha;

    cout << "Se ha registrado exitosamente en MyBook" << endl;

    user[numeroUsuarios].cantidadAmigos = 0;
    user[numeroUsuarios].cantidadSolicitudes = 0;
    user[numeroUsuarios].listas[0].nombreLista = "AMIGOS";
    user[numeroUsuarios].cantidadListas = 1;
    user[numeroUsuarios].infojuego = 0;
    user[numeroUsuarios].cantidadAmigosEnComun = 0;
    numeroUsuarios++;

    cout << endl;
    cout << "Desea inscribir otro usuario (s/n): ";
    cin >> continuar;

    return continuar;
}

void  menuIngresar( usuario user[ MAX_USUARIOS ] )
{

    string correoElectronico;
    string contrasenia;
    int opcionUsuario;
    int opcionEditarPerfil;
    int opcionAmigos;
    int opcionTriqui;
    bool encontro = false;
    int posicion = 0;

    cout << endl << endl;

    cout << "... Bienvenid@ Usuario..." << endl;

    do
    {
        cout << "Digite su correo electronico: ";
        cin >> correoElectronico;

        cout << "Digite su contrase" << char (164) <<"a: ";
        cin >> contrasenia;

        for( int i = 0; i < numeroUsuarios; i++ )
        {
            if( correoElectronico == user[i].correoElectronico && contrasenia == user[i].contrasenia)
            {
                encontro = true;
                do
                {
                    cout << endl << endl;
                    cout << "...Bienvenido a MyBok " << user[i].nombre << endl << endl;
                    opcionUsuario = menuUsuario();
                    switch (opcionUsuario)
                    {
                    case 1:
                        menuEditarPerfil( user, i );
                        break;

                    case 2:
                        menuAmigos( user, i );
                        break;

                    case 3:
                        menuTriqui( user, i );
                        break;

                    case 4:
                        cout << "Muchas gracias, vuelva pronto" << endl;
                        break;

                    default:
                        cout << "Error" << endl;
                        break;
                    }
                }
                while (opcionUsuario != 4);

            }
        }
    }
    while (encontro == false);

}

int menuUsuario()
{
    int opcion;

    cout << " ______________Usuario______________ " << "\n";
    cout << "|___________________________________|" << "\n";
    cout << "|                                   |" << "\n";
    cout << "|          1. Editar perfil         |" << "\n";
    cout << "|          2. Amigos                |" << "\n";
    cout << "|          3. Jugar triqui          |" << "\n";
    cout << "|          4. Salir                 |" << "\n";
    cout << "|___________________________________|" << "\n";
    cout << "|___________________________________|" << "\n";
    cin >> opcion;

    return opcion;

}

void menuEditarPerfil( usuario user[MAX_USUARIOS], int posicion )
{
    int opcion;
    string nombreTemporal;
    string apellidoTemporal;
    int diaTemporal;
    int mesTemporal;
    int anioTemporal;
    char infoNombre;
    char infoApellido;
    char infoCorreo;
    char infoFecha;

    do
    {
        cout << " ______________________Editar Perfil__________________" << "\n";
        cout << "|_____________________________________________________|" << "\n";
        cout << "|                                                     |" << "\n";
        cout << "|          1. Cambiar informacion basica              |" << "\n";
        cout << "|          2. Cambiar / ingresar fecha de nacimiento  |" << "\n";
        cout << "|          3. Administracion de seguridad             |" << "\n";
        cout << "|          4. Deshabilitar perfil                     |" << "\n";
        cout << "|          5. Salir                                   |" << "\n";
        cout << "|_____________________________________________________|" << "\n";
        cout << "|_____________________________________________________|" << "\n";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Digite su nuevo nombre: ";
            cin >> nombreTemporal;
            user[posicion].nombre = nombreTemporal;

            cout << "Digite su nuevo apellido: ";
            cin >> apellidoTemporal;
            user[posicion].apellido = apellidoTemporal;

            cout << "Informacion actualizada" << endl;
            break;

        case 2:
            cout << "Digite su nuevo dia de nacimiento: ";
            cin >> diaTemporal;
            user[posicion].fechaNacimiento.diaNacimiento = diaTemporal;

            cout << "Digite su nuevo mes de nacimiento: ";
            cin >> mesTemporal;
            user[posicion].fechaNacimiento.mesNacimiento = mesTemporal;

            cout << "Digite su nuevo anio de nacimiento: ";
            cin >> anioTemporal;
            user[posicion].fechaNacimiento.anioNacimiento = anioTemporal;

            cout << "Informacion actualizada" << endl;
            break;

        case 3:
            cout << "Desea que su nombre sea publico (s/n): ";
            cin >> infoNombre;
            user[posicion].infoNombre = infoNombre;

            cout << "Desea que su apellido sea publico (s/n): ";
            cin >> infoApellido;
            user[posicion].infoApellido = infoApellido;

            cout << "Desea que su correo sea publico (s/n): ";
            cin >> infoCorreo;
            user[posicion].infoCorreo = infoCorreo;

            cout << "Desea que su fecha de nacimiento sea publica (s/n): ";
            cin >> infoFecha;
            user[posicion].infoFecha = infoFecha;
            break;

        case 4:
            user[posicion].infoNombre = 's';
            user[posicion].infoApellido = 'n';
            user[posicion].infoCorreo = 'n';
            user[posicion].infoFecha = 'n';
            user[posicion].nombre = "Usuario MyBook";

            cout << "Perfil desactivado" << endl;
            break;

        case 5:
            cout << "Gracias";
            break;

        default:
            cout << "Error";
            break;
        }
    }
    while ( opcion != 5 );

}

void menuAmigos( usuario user[ MAX_USUARIOS], int posicion )
{
    int opcion;
    string datosUsuario;
    string correoAmigo;
    bool encontro = false;
    bool esta = false;
    char aceptarSolicitud;
    int opcionLista;
    string nombreLista;
    string nombreListaEliminar;
    int numeroLista;
    string listaNuevoAmigo;
    string correoEliminar;
    string nombreAmigo;
    string nombreListaCambiar;
    bool encontrar;
    int posAmigo;

    do
    {
        cout << " ______________________Amigos___________________" << "\n";
        cout << "|_______________________________________________|" << "\n";
        cout << "|                                               |" << "\n";
        cout << "|          1. Ver amigos                        |" << "\n";
        cout << "|          2. Buscar amigos                     |" << "\n";
        cout << "|          3. Aceptar o rechazar amigos         |" << "\n";
        cout << "|          4. Eliminar amigos                   |" << "\n";
        cout << "|          5. Mover un amigo a una lista        |" << "\n";
        cout << "|          6. Administrar listas de amigos      |" << "\n";
        cout << "|          7. Hacer solicitudes de amistad      |" << "\n";
        cout << "|          8. Salir                             |" << "\n";
        cout << "|_______________________________________________|" << "\n";
        cout << "|_______________________________________________|" << "\n";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            if ( user[posicion].cantidadAmigos == 0 )
            {
                cout << "Aun no tienes amigos" << endl;
            }
            else
            {
                for (int i =0; i < user[posicion].cantidadAmigos; i++ )
                {
                    cout << "Amigo: " << i+1 << endl;
                    cout << "Nombre: " << user[posicion].amigosAceptados[i].nombre << endl;
                    cout << "Apellido: " << user[posicion].amigosAceptados[i].apellido << endl;
                    cout << "Correo: " << user[posicion].amigosAceptados[i].correo << endl;
                }
            }

            break;

        case 2:
            cout << "Digite el nombre o el apellido del usuario que quiere que sea su amigo: ";
            cin >> datosUsuario;

            for ( int i = 0; i < numeroUsuarios ; i ++)
            {
                if ( user[i].nombre == datosUsuario || user[i].apellido == datosUsuario )
                {
                    cout << "Nombre: " << user[i].nombre << endl;
                    cout << "Apellido: " << user[i].apellido << endl;

                    if ( user[i].infoCorreo == 's' )
                    {
                        cout << "Correo electronico: " << user[i].correoElectronico << endl;
                    }
                    if ( user[i].infoFecha == 's' )
                    {
                        cout << "Fecha nacimiento" << endl;
                        cout << "Dia: " << user[i].fechaNacimiento.diaNacimiento << endl;
                        cout << "Mes: " << user[i].fechaNacimiento.mesNacimiento << endl;
                        cout << "Anio: " << user[i].fechaNacimiento.anioNacimiento << endl;
                    }
                }
                cout << endl << endl;
            }
            break;

        case 3:
            for ( int i =  0; i < user[posicion].cantidadSolicitudes; i++)
            {
                cout << " Solicitud " << i + 1 << endl;
                cout << "Nombre: " << user[posicion].solicitudAmistad[i].nombre << endl;
                cout << "Apellido: " << user[posicion].solicitudAmistad[i].apellido << endl;
                cout << "Correo: " << user[posicion].solicitudAmistad[i].correo << endl;

                if ( user[posicion].cantidadAmigosEnComun == 0)
                {
                    cout << "No tienen amigos en comun" << endl;
                }
                else
                {
                    cout << user[posicion].amigosMutuos[i].nombre << endl;
                    cout << user[posicion].amigosMutuos[i].apellido << endl;
                }

                cout << "Desea aceptar la solicitud " << i+1 << " (s/n): ";
                cin >> aceptarSolicitud;

                if (aceptarSolicitud == 's')
                {
                    user[posicion].amigosAceptados[user[posicion].cantidadAmigos].nombre = user[posicion].solicitudAmistad[i].nombre;
                    user[posicion].amigosAceptados[user[posicion].cantidadAmigos].apellido = user[posicion].solicitudAmistad[i].apellido;
                    user[posicion].amigosAceptados[user[posicion].cantidadAmigos].correo = user[posicion].solicitudAmistad[i].correo;
                    user[posicion].cantidadAmigos++;

                    user[i].amigosAceptados[user[i].cantidadAmigos].nombre = user[posicion].nombre;
                    user[i].amigosAceptados[user[i].cantidadAmigos].apellido = user[posicion].apellido;
                    user[i].amigosAceptados[user[i].cantidadAmigos].correo = user[posicion].correoElectronico;
                    user[i].cantidadAmigos++;
                    cout << user[posicion].solicitudAmistad[i].nombre << " ahora es tu amigo" << endl;

                    cout << "Digite en que lista desea guardar a su nuevo amigo: ";
                    cin >> listaNuevoAmigo;

                    for ( int j = 0; j < user[posicion].cantidadListas; j++)
                    {
                        if ( user[posicion].listas[j].nombreLista == listaNuevoAmigo)
                        {
                            //Guardo a mi amigo en la lista que se haya deseado
                            user[posicion].listas[j].amigos[user[posicion].listas[j].posicionAmigo].nombre = user[posicion].solicitudAmistad[i].nombre;
                            user[posicion].listas[j].amigos[user[posicion].listas[j].posicionAmigo].apellido = user[posicion].solicitudAmistad[i].apellido;
                        }
                    }
                }

                //Eliminar solicitud del arreglo de solucitudAmistad
                user[posicion].solicitudAmistad[i].nombre =  user[posicion].solicitudAmistad[i+1].nombre;
                user[posicion].solicitudAmistad[i].apellido =  user[posicion].solicitudAmistad[i+1].apellido;
                user[posicion].solicitudAmistad[i].correo =  user[posicion].solicitudAmistad[i+1].correo;
                user[posicion].cantidadSolicitudes--;
            }
            break;

        case 4:
            cout << "Digite el correo del amigo desea eliminar: ";
            cin >> correoEliminar;

            if ( user[posicion].cantidadAmigos == 1)
            {
                user[posicion].cantidadAmigos = 0;
                cout << correoEliminar << " se ha eliminado de su lista de amigos" << endl;
            }
            else
            {
                for ( int i = 0; i < user[posicion].cantidadAmigos-1; i++)
                {
                    if ( user[posicion].amigosAceptados[i].correo == correoEliminar )
                    {
                        for ( int j = i; j < user[posicion].cantidadAmigos-1; j++)
                        {
                            user[posicion].amigosAceptados[j].nombre = user[posicion].amigosAceptados[j+1].nombre;
                            user[posicion].amigosAceptados[j].apellido = user[posicion].amigosAceptados[j+1].apellido;
                            user[posicion].amigosAceptados[j].correo = user[posicion].amigosAceptados[j+1].correo;
                            user[posicion].amigosAceptados[j].fecha.diaNacimiento = user[posicion].amigosAceptados[j+1].fecha.diaNacimiento;
                            user[posicion].amigosAceptados[j].fecha.mesNacimiento = user[posicion].amigosAceptados[j+1].fecha.mesNacimiento;
                            user[posicion].amigosAceptados[j].fecha.anioNacimiento = user[posicion].amigosAceptados[j+1].fecha.mesNacimiento;
                        }
                        user[posicion].cantidadAmigos--;
                        break;
                        cout << "Se ha eliminado " << correoEliminar << " de la lista de amigos" << endl;
                    }
                }
            }
            break;

        case 5:
            cout << "Digite el nombre de su amigo: ";
            cin >> nombreAmigo;

            for ( int j = 0; j < user[posicion].cantidadAmigos ; j++)
            {
                if ( user[posicion].amigosAceptados[j].nombre == nombreAmigo )
                {
                    posAmigo = j;
                }
            }

            cout << "Digite el nombre de la lista a la que desea cambiar su amigo: ";
            cin >> nombreListaCambiar;

            for ( int j = 0; j < user[posicion].cantidadListas; j++)
            {
                if ( user[posicion].listas[j].nombreLista == nombreListaCambiar)
                {
                    user[posicion].listas[j].amigos[user[posicion].listas[j].posicionAmigo].nombre = user[posAmigo].nombre;
                    user[posicion].listas[j].amigos[user[posicion].listas[j].posicionAmigo].apellido = user[posAmigo].apellido;
                    user[posicion].listas[j].posicionAmigo++;
                }
            }
            break;

        case 6:
            cout << "1. Crear lista" << endl;
            cout << "2. Eliminar lista" << endl;
            cout << "3. Ver amigos de una lista" << endl;
            cin >> opcionLista;

            if( opcionLista == 1 )
            {
                do
                {
                    cout << "Digite el nombre de la lista: ";
                    cin >> nombreLista;

                    encontrar = buscarNombreLista( user, nombreLista, posicion);
                    if( encontrar == true)
                    {
                        cout << "Vuelva a escribir un nombre valido" << endl;
                    }
                    else
                    {
                        encontrar = false;
                    }
                }
                while (encontrar == true);

                user[posicion].listas[user[posicion].cantidadListas].nombreLista = nombreLista;
                user[posicion].cantidadListas++;
                cout << "La lista " << nombreLista << " ha sido creada con exito" << endl;
            }
            else if ( opcionLista == 2)
            {
                cout << "Digite el nombre de la lista que desea eliminar: ";
                cin >> nombreListaEliminar;

                if (nombreListaEliminar == "AMIGOS")
                {
                    cout << "No podemos eliminar esta lista :( " << endl;
                }
                else
                {
                    for( int i = 1; i < user[posicion].cantidadListas - 1; i++)
                    {
                        if ( user[posicion].listas[i].nombreLista == nombreListaEliminar)
                        {
                            user[posicion].listas[i].nombreLista = user[posicion].listas[i+1].nombreLista;
                        }
                    }
                    user[posicion].cantidadListas--;
                }
            }
            else  if (opcionLista == 3)
            {
                for ( int i = 0; i < user[posicion].cantidadListas; i++)
                {
                    cout  << i+1 << " "<< user[posicion].listas[i].nombreLista << endl;
                }
                cout << "Que numero de lista desea ver: ";
                cin >> numeroLista;

                if ( numeroLista == 1 )
                {
                    for (int i = 0; i < user[posicion].cantidadAmigos; i++)
                    {
                        cout << user[posicion].amigosAceptados[i].nombre << endl;
                        cout << user[posicion].amigosAceptados[i].apellido << endl;
                    }

                }
                else
                {
                    for ( int i= 0; i < user[posicion].cantidadAmigos; i++)
                    {
                        cout << user[posicion].listas[numeroLista].amigos[i].nombre << endl;
                        cout << user[posicion].listas[numeroLista].amigos[i].apellido << endl;
                    }
                }

            }
            break;

        case 7:
            for ( int i = 0; i < numeroUsuarios; i++ )
            {
                if ( i == posicion)
                {
                    cout << " " << endl;
                }
                else
                {
                    if ( user[i].infoNombre == 's' )
                    {
                        cout << "Nombre: " << user[i].nombre << endl;
                    }
                    if ( user[i].infoApellido == 's' )
                    {
                        cout << "Apellido: " << user[i].apellido << endl;
                    }
                    if ( user[i].infoCorreo == 's' )
                    {
                        cout << "Correo: " << user[i].correoElectronico << endl;
                    }
                    if ( user[i].infoFecha == 's')
                    {
                        cout << "Fecha de nacimiento" << endl;
                        cout << "Dia: " << user[i].fechaNacimiento.diaNacimiento << endl;
                        cout << "Mes: " << user[i].fechaNacimiento.mesNacimiento << endl;
                        cout << "Anio: " << user[i].fechaNacimiento.anioNacimiento << endl;
                    }
                    cout << endl;
                }
            }

            cout << "Digite el correo del usuario que desea enviar la solicitud: ";
            cin >> correoAmigo;

            for ( int i =  0; i < numeroUsuarios ; i++ )
            {
                if ( user[i].correoElectronico == correoAmigo)
                {
                    user[i].solicitudAmistad[ user[i].cantidadSolicitudes].nombre  = user[ posicion ].nombre;
                    user[i].solicitudAmistad[user[i].cantidadSolicitudes].apellido = user[ posicion ].apellido;
                    user[i].solicitudAmistad[user[i].cantidadSolicitudes].correo = user[posicion].correoElectronico;
                    user[i].solicitudAmistad[user[i].cantidadSolicitudes].fecha.diaNacimiento = user[posicion].fechaNacimiento.diaNacimiento;
                    user[i].solicitudAmistad[user[i].cantidadSolicitudes].fecha.mesNacimiento = user[posicion].fechaNacimiento.mesNacimiento;
                    user[i].solicitudAmistad[user[i].cantidadSolicitudes].fecha.anioNacimiento = user[posicion].fechaNacimiento.anioNacimiento;
                    user[i].cantidadSolicitudes = user[i].cantidadSolicitudes + 1;

                    cout << "Ya se envio la solicitud a: " << user[i].nombre << endl;
                }

                for ( int j = 0; j < user[posicion].cantidadAmigos; j++)
                {
                    // Verifica si los usuarios tienen amigos en comun, y los manda a la lista de amigos en comun
                    if( user[posicion].amigosAceptados[j].nombre == user[i].amigosAceptados[j].nombre)
                    {
                        user[i].amigosMutuos[user[i].cantidadAmigosEnComun].nombre = user[posicion].amigosAceptados[j].nombre;
                        user[i].amigosMutuos[user[i].cantidadAmigosEnComun].apellido = user[posicion].amigosAceptados[j].apellido;
                    }
                }

            }


            break;

        case 8:
            break;
        }
    }
    while (opcion != 8);

}

void menuTriqui(  usuario user[MAX_USUARIOS], int posicion )
{
    int opcion;
    int posicionAmigo;
    string correoAmigo;
    string contraseniaAmigo;
    int triqui;

    do
    {
        cout << " _______________Triqui_______________ " << "\n";
        cout << "|____________________________________|" << "\n";
        cout << "|                                    |" << "\n";
        cout << "|          1. Jugar Triqui           |" << "\n";
        cout << "|          2. Ver estadisticas       |" << "\n";
        cout << "|          3. Salir                  |" << "\n";
        cout << "|____________________________________|" << "\n";
        cout << "|____________________________________|" << "\n";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Digite el correo de su amigo: ";
            cin >> correoAmigo;
            cout << "Digite la contrasenia de su amigo: ";
            cin >> contraseniaAmigo;

            for ( int j = 0; j < numeroUsuarios ; j++)
            {
                if ( user[j].correoElectronico == correoAmigo && user[j].contrasenia == contraseniaAmigo)
                {
                    posicionAmigo = j;
                }
            }

            for ( int i = 0; i < user[posicion].cantidadAmigos; i++)
            {
                if ( user[posicion].amigosAceptados[i].correo == correoAmigo && user[posicionAmigo].contrasenia == contraseniaAmigo )
                {
                    triqui = jugarTriqui();

                    if ( triqui == 3)
                    {
                        user[posicion].estadisticaJuego[user[posicion].infojuego] = 3;
                        user[posicion].infojuego++;

                        user[posicionAmigo].estadisticaJuego[user[posicionAmigo].infojuego] = 3;
                        user[posicionAmigo].infojuego++;
                    }
                    else
                    {
                        if ( triqui == 2)
                        {
                            user[posicion].estadisticaJuego[user[posicion].infojuego] = 2;
                            user[posicion].infojuego++;

                            user[posicionAmigo].estadisticaJuego[user[posicionAmigo].infojuego] = 1;
                            user[posicionAmigo].infojuego++;
                        }
                        else
                        {
                            if ( triqui == 1)
                            {
                                user[posicion].estadisticaJuego[user[posicion].infojuego] = 1;
                                user[posicion].infojuego++;

                                user[posicionAmigo].estadisticaJuego[user[posicionAmigo].infojuego] = 2;
                                user[posicionAmigo].infojuego++;
                            }
                        }
                    }
                }
                else
                {
                    cout << "Correo o contrasenia invalida " << endl;
                }
            }
            break;

        case 2:

            for (int i = 0; i<user[posicion].infojuego; i++)
            {
                if (user[posicion].estadisticaJuego[i] == 1)
                {
                    cout << "Partida " << i + 1 << " ganada" << endl;
                }
                else
                {
                    if (user[posicion].estadisticaJuego[i] == 2)
                    {
                        cout << "Partida " << i + 1 <<" perdida" << endl;
                    }
                    else
                    {
                        if (user[ posicion ].estadisticaJuego[i] == 3)
                        {
                            cout << "Partida " << i + 1 << " empatada" << endl;
                        }
                    }
                }
            }
            break;
        case 3:
            break;
        default:
            cout << "Error" << endl;
            break;
        }
    }
    while (opcion != 3);
}

bool buscarCorreoElectronico( usuario user[ MAX_USUARIOS ], string correo )
{
    bool encontro = false;
    for ( int i = 0; i < numeroUsuarios && encontro == false ; i++ )
    {
        if ( user[i].correoElectronico == correo )
        {
            encontro = true;
        }
    }
    return encontro;
}

bool buscarNombreLista ( usuario user[ MAX_USUARIOS ], string nombreLista, int posicion)
{
    bool encontro = false;
    for ( int i = 0; i < user[posicion].cantidadListas && encontro == false ; i++ )
    {
        if ( user[posicion].listas[i].nombreLista == nombreLista )
        {
            encontro = true;
        }
    }
    return encontro;
}

int jugarTriqui()
{
    bool terminarJuego = false;
    int tablero[MAX][MAX];
    int fila, col, cont = 0;
    int gano = 0;
    bool a, b;
    cout << endl << endl;
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            tablero[i][j] = 3;
        }
    }
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            cout << tablero[i][j];
        }
        cout << endl;
    }
    do
    {
        cout << endl;
        cout << "Jugador 1" << endl;
        cout << "Digite la posicion fila de su jugada X: ";
        cin >> fila;
        cout << "Digite la posicion columna de su jugada X: ";
        cin >> col;
        tablero[fila][col] = 1;
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                if (tablero[i][j] == 2)
                {
                    cout << "O";
                }
                if (tablero[i][j] == 1)
                {
                    cout << "X";
                }
                if (tablero[i][j] != 1 && tablero[i][j] != 2)
                {
                    cout << tablero[i][j];
                }
            }
            cout << endl;
        }

        cont++;
        if ((terminarJuego = verificarGanador1(tablero)) == true)
        {
            cout << "Felicitaciones, jugador 1 ha ganado..." << endl;
            break;
        }
        cout << endl;
        cout << "Jugador 2" << endl;
        cout << "Digite la posicion fila de su jugada O: ";
        cin >> fila;
        cout << "Digite la posicion columna de su jugada O: ";
        cin >> col;
        tablero[fila][col] = 2;
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                if (tablero[i][j] == 2)
                {
                    cout << "O";
                }
                if (tablero[i][j] == 1)
                {
                    cout << "X";
                }
                if (tablero[i][j] != 1 && tablero[i][j] != 2)
                {
                    cout << tablero[i][j];
                }
            }
            cout << endl;
        }
        cont++;
        if ((terminarJuego = verificarGanador2(tablero)) == true)
        {
            cout << "Felicitaciones, jugador 2 ha ganado..." << endl;
            break;
        }


    }
    while (terminarJuego == false && cont<8);

    if ((a = verificarGanador1(tablero) == false) && (b = verificarGanador2(tablero) == false))
    {
        cout << "Ups, hubo un empate" << endl;
        gano = 3;
    }

    if ((terminarJuego = verificarGanador1(tablero)) == true)
    {
        gano = 1;
    }
    else
    {
        if ((terminarJuego = verificarGanador2(tablero)) == true)
        {
            gano = 2;
        }
    }
    return terminarJuego;
}

bool verificarGanador1(int matriz[][MAX])
{
    bool terminarJuego = false;
    int vez = 0, cant = 0, b = 2;
    for (int i = 0; i<3; i++)
    {
        vez = 0;
        for (int j = 0; j<3; j++)
        {
            if (matriz[i][j] == 1)
            {
                vez++;
            }
        }
        if (vez == 3)
        {
            cant++;
        }
    }
    for (int i = 0; i<3; i++)
    {
        vez = 0;
        for (int j = 0; j<3; j++)
        {
            if (matriz[j][i] == 1)
            {
                vez++;
            }
        }
        if (vez == 3)
        {
            cant++;
        }
    }
    for (int i = 0; i<3; i++)
    {
        vez = 0;
        if (matriz[i][i] == 1)
        {
            vez++;
        }

    }
    if (vez == 3)
    {
        cant++;
    }

    for (int i = 0; i<3; i++)
    {

        vez = 0;
        if (matriz[i][b] == 1)
        {
            vez++;
        }
        b--;

    }
    if (vez == 3)
    {
        cant++;
    }
    if (cant>0)
    {
        terminarJuego = true;
    }
    return terminarJuego;
}

bool verificarGanador2(int matriz[][MAX])
{
    bool terminarJuego = false;
    int vez = 0, cant = 0, b = 2;
    for (int i = 0; i<3; i++)
    {
        vez = 0;
        for (int j = 0; j<3; j++)
        {
            if (matriz[i][j] == 2)
            {
                vez++;
            }
        }
        if (vez == 3)
        {
            cant++;
        }
    }
    for (int i = 0; i<3; i++)
    {
        vez = 0;
        for (int j = 0; j<3; j++)
        {
            if (matriz[j][i] == 2)
            {
                vez++;
            }
        }
        if (vez == 3)
        {
            cant++;
        }
    }
    for (int i = 0; i<3; i++)
    {
        vez = 0;
        if (matriz[i][i] == 2)
        {
            vez++;
        }

    }
    if (vez == 3)
    {
        cant++;
    }

    for (int i = 0; i<3; i++)
    {

        vez = 0;
        if (matriz[i][b] == 2)
        {
            vez++;
        }
        b--;

    }
    if (vez == 3)
    {
        cant++;
    }
    if (cant>0)
    {
        terminarJuego = true;
    }
    return terminarJuego;
}


