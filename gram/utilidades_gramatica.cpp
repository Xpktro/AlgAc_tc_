/*
 *               _                    ___ _      ___
 *         /\   | |         /\       |  _| |    |_  |
 *        /  \  | | __ _   /  \   ___| | | |_ ___ | |
 *       / /\ \ | |/ _` | / /\ \ / __| | | __/ __|| |
 *      / ____ \| | (_| |/ ____ \ (__| | | || (__ | |
 *     /_/    \_\_|\__, /_/    \_\___| |_ \__\___|| |
 *                  __/ |            |___|      |___|
 *                 |___/
 *
 *           (c) 2012 - Mois�s Cachay Tello
 *   Este c�digo se entrega s�lo con fines de estudio.
 */

#include "utilidades_gramatica.h"
#include <iostream>

UtilidadesGramatica::UtilidadesGramatica() {
}

//Mini-Parser de gram�ticas. Debe de recibir un std::string conteniendo
//una lista de producciones separadas por saltos de l�neas en el
//siguiente formato:
//  NOTERMINAL -> Simbolos

//Las l�neas que contengan ; o est�n vac�as no ser�n procesadas, siendo
//consideradas como comentarios. N�tese que aunque partes cr�ticas de
//esta funci�n est�n apoyadas en las librer�as de Strings de Qt, son
//f�ciles de adaptar a cualquier otra implementaci�n con estructuras
//de datos an�logas (que son muy comunes en este y otros lenguajes).
Gramatica UtilidadesGramatica::parsearGramatica(std::string entrada) {
    //Inicializamos y definimos los punteros que usaremos
    //para el resto del proceso.
    Gramatica* gram = new Gramatica();
    Produccion* prod = NULL;
    Terminal* term = NULL;
    NoTerminal* noterm = NULL;

    //Se requiere de un StringStream para el proceso de extracci�n
    //de l�neas de la en�trada. Puede que no sea el m�todo m�s
    //eficiente, pero es limpio y elegante.
    std::stringstream ss(entrada);
    std::string linea;
    QString qLinea;
    QStringList partes;

    while(std::getline(ss, linea)) {
        //Ya que getLine no soporta QStrings, utilizamos los est�ndar
        //y convertimos para cada nueva l�nea.
        qLinea = QString::fromStdString(linea);

        //Obviamos las l�neas vac�as y los comentarios (que empiezan con ;)
        if(!qLinea.startsWith(";") && !qLinea.isEmpty()) {

            //Dividimos la l�nea actual utilizando la flecha y los espacios
            //como puntos de corte, adicionalmente se le indica a la funci�n
            //que no produzca elementos vac�os.
            partes = qLinea.split(QRegExp("(->| |\\t)+"), QString::SkipEmptyParts);

            //La funci�n debe de partir la l�nea en dos mitades, una
            //conteniendo la parte izquierda con un no terminal, y
            //la segunda con una lista de s�mbolos.
            noterm = new NoTerminal(partes.at(0).toStdString());
            prod = new Produccion();
            prod->setIzquierda(*noterm);

            //Luego, por cada caracter que se encuentre en la parte
            //derecha de cada producci�n:
            for(int i = 0; i < partes.at(1).size(); ++i) {

                //Verificamos que no estemos ante un comentario al final de
                //la producci�n, esto permite insertar comentarios en las
                //producciones sin afectar el reconocimiento de la entrada.
                if(partes.at(1).at(i)==';') break;

                //Para todos los dem�s caracteres, reconocemos si son Terminales
                //o no para agregarlos a la parte derecha de la producci�n actual.
                if(partes.at(1).at(i).isUpper()) {
                    noterm = new NoTerminal(QString(partes.at(1).at(i)).toStdString());
                    prod->agregarSimbolo(*noterm);
                }
                else if(partes.at(1).at(i).isLower()) {
                    term = new Terminal(QString(partes.at(1).at(i)).toStdString());
                    prod->agregarSimbolo(*term);
                }
            }

            //Y al final a�adir la producci�n actual a la gram�tica.
            gram->agregarProduccion(*prod);
        }
    }
    return *gram;
}

//Los resultados que retornar�n los algoritmos Activo y Accesible
//son del tipo Gramatica. Adicionalmente se requiere de una lista
//de s�mbolos para insertar las sublistas de los pasos intermedios.
Gramatica UtilidadesGramatica::algoritmoActivo(Gramatica entrada, std::vector<UtilidadesSimbolo::SetSimbolos> &w) {
    //Iniciamos los valores de devoluci�n:
    //La gram�tica resultante:
    Gramatica gram = Gramatica();

    //Y una lista de s�mbolos que se a�adir� en cada iteraci�n para
    //el registro de los pasos intermedios y la condici�n de finalizaci�n
    //del algoritmo:
    UtilidadesSimbolo::SetSimbolos* wx = new UtilidadesSimbolo::SetSimbolos();

    //Se sabe que tambi�n el algoritmo no debe de hacer m�s iteraciones
    //que el n�mero de terminales que tiene la gram�tica.
    int nt = (int)entrada.getNoTerminales().size();

    //Se empieza teniendo un W0 que contiene todos los no terminales de
    //los lados izquierdos de las gram�ticas cuando sus lados derechos
    //contienen s�lo terminales.
    std::vector<Produccion>::size_type tProduccion = entrada.getProducciones().size();
    UtilidadesSimbolo::SetSimbolos* w0 = new UtilidadesSimbolo::SetSimbolos();

    for(unsigned int i = 0; i < tProduccion; i++) {
        if(QRegExp("[a-z]+").exactMatch(QString::fromStdString(entrada.getProduccion(i).getDerecha().listaStr()))) {
            w0->agregarElemento(entrada.getProduccion(i).getIzquierda());
        }
    }
    w.push_back(*w0);

    //Empezamos la serie de iteraciones principal:
    do {
        //Reiniciamos nuestro W temporal y le damos los valores
        //del �ltimo W insertado a w:
        wx = new UtilidadesSimbolo::SetSimbolos();
        wx->agregar(*(--w.end()));

        //Recogemos un w temporal con los �ltimos datos insertados para evitar resultados
        //apresurados al momento de la evaluaci�n de las expresiones regulares.
        UtilidadesSimbolo::SetSimbolos wTemp = UtilidadesSimbolo::SetSimbolos();
        wTemp.agregar(*wx);
        //Para cada una de las producciones de la gram�tica de entrada:
        for(unsigned int i = 0; i < tProduccion; i++) {
            //Verificamos si el lado derecho contiene s�lamente uno o todos los
            //s�mbolos de Wx. Para esto comparamos el lado derecho de la producci�n
            //con la expresi�n regular "^[(simbolos)a-z]+$" que s�lo coincidir� con
            //la condici�n anteriormente mencionada.
            QRegExp regexp = QRegExp(QString("[")+QString::fromStdString(wTemp.setStr())+QString("a-z]+"));
            if(regexp.exactMatch(QString::fromStdString(entrada.getProduccion(i).getDerecha().listaStr()))) {
                //En cuyo caso agregamos el s�mbolo de la izquierda
                //a W y a�adimos la producci�n en cuesti�n a nuestra
                //gram�tica resultante:
                wx->agregarElemento(entrada.getProduccion(i).getIzquierda());
                gram.agregarProduccion(entrada.getProduccion(i));
            }
        }

        //Al final guardamos nuestro Wx en la lista para guardar
        //el registro de los s�mbolos encontrados en la iteraci�n
        //actual:
        w.push_back(*wx);

    //Este proceso se repetir� hasta que la lista de resultados
    //actuales sea igual a la anterior o hasta que terminemos
    //con el n�mero de iteraciones posibles.
    }while(wx->getSet()!= (*(++w.rbegin())).getSet() && --nt);

    return gram;
}

Gramatica UtilidadesGramatica::algoritmoAccesible(Gramatica entrada, std::vector<UtilidadesSimbolo::SetSimbolos> &w) {
    //Iniciamos los valores de devoluci�n:
    //La gram�tica resultante:
    Gramatica gram = Gramatica();

    //Y una lista de s�mbolos que se a�adir� en cada iteraci�n para
    //el registro de los pasos intermedios y la condici�n de finalizaci�n
    //del algoritmo:
    UtilidadesSimbolo::SetSimbolos* wx = new UtilidadesSimbolo::SetSimbolos();

    //Se empieza teniendo un W0 que contiene el axioma de la gram�tica.
    //Sabi�ndose que es el s�mbolo no terminal de la izquierda en la
    //primera producci�n::
    wx->agregarElemento(entrada.getAxioma().getIzquierda());
    w.push_back(*wx);

    //Se sabe que tambi�n el algoritmo no debe de hacer m�s iteraciones
    //que el n�mero de terminales que tiene la gram�tica.
    int nt = (int)entrada.getNoTerminales().size();

    std::vector<Produccion>::size_type tProduccion = entrada.getProducciones().size();

    //Empezamos la serie de iteraciones principal:
    do {
        //Reiniciamos nuestro W temporal y le damos los valores
        //del �ltimo W insertado a w:
        wx = new UtilidadesSimbolo::SetSimbolos();
        wx->agregar(*(w.rbegin()));

        //Recogemos un w temporal con los �ltimos datos insertados para evitar resultados
        //apresurados al momento de la evaluaci�n de las expresiones regulares.
        UtilidadesSimbolo::SetSimbolos wTemp = UtilidadesSimbolo::SetSimbolos();
        wTemp.agregar(*wx);
        //Para cada una de las producciones de la gram�tica de entrada:
        for(unsigned int i = 0; i < tProduccion; i++) {
            //Verifivamos si el lado izquierdo contiene los s�mbolos terminales
            //de Wx. Para esto comparamos el lado izquierdo de la producci�n
            //con la expresi�n regular "[(simbolos)]" que s�lo coincidir� con
            //la condici�n anteriormente mencionada.
            QRegExp regexp = QRegExp(QString("[")+QString::fromStdString(wTemp.setStr())+QString("]"));
            if(regexp.exactMatch(QString::fromStdString(entrada.getProduccion(i).getIzquierda().getSimbolo()))) {
                //En cuyo caso agregamos la parte derecha de la producci�n
                //a W y a�adimos la producci�n en cuesti�n a nuestra
                //gram�tica resultante:
                wx->agregar(entrada.getProduccion(i).getDerecha());
                gram.agregarProduccion(entrada.getProduccion(i));
            }
        }

        //Al final guardamos nuestro Wx en la lista para guardar
        //el registro de los s�mbolos encontrados en la iteraci�n
        //actual:
        w.push_back(*wx);

    //Este proceso se repetir� hasta que la lista de resultados
    //actuales sea igual a la anterior o hasta que terminemos
    //con el n�mero de iteraciones posibles.
    }while(wx->getSet()!= (*(++w.rbegin())).getSet() && --nt);

    return gram;
}
