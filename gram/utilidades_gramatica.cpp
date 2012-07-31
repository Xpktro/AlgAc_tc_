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
 *           (c) 2012 - Moisés Cachay Tello
 *   Este código se entrega sólo con fines de estudio.
 */

#include "utilidades_gramatica.h"
#include <iostream>

UtilidadesGramatica::UtilidadesGramatica() {
}

//Mini-Parser de gramáticas. Debe de recibir un std::string conteniendo
//una lista de producciones separadas por saltos de líneas en el
//siguiente formato:
//  NOTERMINAL -> Simbolos

//Las líneas que contengan ; o estén vacías no serán procesadas, siendo
//consideradas como comentarios. Nótese que aunque partes críticas de
//esta función están apoyadas en las librerías de Strings de Qt, son
//fáciles de adaptar a cualquier otra implementación con estructuras
//de datos análogas (que son muy comunes en este y otros lenguajes).
Gramatica UtilidadesGramatica::parsearGramatica(std::string entrada) {
    //Inicializamos y definimos los punteros que usaremos
    //para el resto del proceso.
    Gramatica* gram = new Gramatica();
    Produccion* prod = NULL;
    Terminal* term = NULL;
    NoTerminal* noterm = NULL;

    //Se requiere de un StringStream para el proceso de extracción
    //de líneas de la enºtrada. Puede que no sea el método más
    //eficiente, pero es limpio y elegante.
    std::stringstream ss(entrada);
    std::string linea;
    QString qLinea;
    QStringList partes;

    while(std::getline(ss, linea)) {
        //Ya que getLine no soporta QStrings, utilizamos los estándar
        //y convertimos para cada nueva línea.
        qLinea = QString::fromStdString(linea);

        //Obviamos las líneas vacías y los comentarios (que empiezan con ;)
        if(!qLinea.startsWith(";") && !qLinea.isEmpty()) {

            //Dividimos la línea actual utilizando la flecha y los espacios
            //como puntos de corte, adicionalmente se le indica a la función
            //que no produzca elementos vacíos.
            partes = qLinea.split(QRegExp("(->| |\\t)+"), QString::SkipEmptyParts);

            //La función debe de partir la línea en dos mitades, una
            //conteniendo la parte izquierda con un no terminal, y
            //la segunda con una lista de símbolos.
            noterm = new NoTerminal(partes.at(0).toStdString());
            prod = new Produccion();
            prod->setIzquierda(*noterm);

            //Luego, por cada caracter que se encuentre en la parte
            //derecha de cada producción:
            for(int i = 0; i < partes.at(1).size(); ++i) {

                //Verificamos que no estemos ante un comentario al final de
                //la producción, esto permite insertar comentarios en las
                //producciones sin afectar el reconocimiento de la entrada.
                if(partes.at(1).at(i)==';') break;

                //Para todos los demás caracteres, reconocemos si son Terminales
                //o no para agregarlos a la parte derecha de la producción actual.
                if(partes.at(1).at(i).isUpper()) {
                    noterm = new NoTerminal(QString(partes.at(1).at(i)).toStdString());
                    prod->agregarSimbolo(*noterm);
                }
                else if(partes.at(1).at(i).isLower()) {
                    term = new Terminal(QString(partes.at(1).at(i)).toStdString());
                    prod->agregarSimbolo(*term);
                }
            }

            //Y al final añadir la producción actual a la gramática.
            gram->agregarProduccion(*prod);
        }
    }
    return *gram;
}

//Los resultados que retornarán los algoritmos Activo y Accesible
//son del tipo Gramatica. Adicionalmente se requiere de una lista
//de símbolos para insertar las sublistas de los pasos intermedios.
Gramatica UtilidadesGramatica::algoritmoActivo(Gramatica entrada, std::vector<UtilidadesSimbolo::SetSimbolos> &w) {
    //Iniciamos los valores de devolución:
    //La gramática resultante:
    Gramatica gram = Gramatica();

    //Y una lista de símbolos que se añadirá en cada iteración para
    //el registro de los pasos intermedios y la condición de finalización
    //del algoritmo:
    UtilidadesSimbolo::SetSimbolos* wx = new UtilidadesSimbolo::SetSimbolos();

    //Se sabe que también el algoritmo no debe de hacer más iteraciones
    //que el número de terminales que tiene la gramática.
    int nt = (int)entrada.getNoTerminales().size();

    //Se empieza teniendo un W0 que contiene todos los no terminales de
    //los lados izquierdos de las gramáticas cuando sus lados derechos
    //contienen sólo terminales.
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
        //del último W insertado a w:
        wx = new UtilidadesSimbolo::SetSimbolos();
        wx->agregar(*(--w.end()));

        //Recogemos un w temporal con los últimos datos insertados para evitar resultados
        //apresurados al momento de la evaluación de las expresiones regulares.
        UtilidadesSimbolo::SetSimbolos wTemp = UtilidadesSimbolo::SetSimbolos();
        wTemp.agregar(*wx);
        //Para cada una de las producciones de la gramática de entrada:
        for(unsigned int i = 0; i < tProduccion; i++) {
            //Verificamos si el lado derecho contiene sólamente uno o todos los
            //símbolos de Wx. Para esto comparamos el lado derecho de la producción
            //con la expresión regular "^[(simbolos)a-z]+$" que sólo coincidirá con
            //la condición anteriormente mencionada.
            QRegExp regexp = QRegExp(QString("[")+QString::fromStdString(wTemp.setStr())+QString("a-z]+"));
            if(regexp.exactMatch(QString::fromStdString(entrada.getProduccion(i).getDerecha().listaStr()))) {
                //En cuyo caso agregamos el símbolo de la izquierda
                //a W y añadimos la producción en cuestión a nuestra
                //gramática resultante:
                wx->agregarElemento(entrada.getProduccion(i).getIzquierda());
                gram.agregarProduccion(entrada.getProduccion(i));
            }
        }

        //Al final guardamos nuestro Wx en la lista para guardar
        //el registro de los símbolos encontrados en la iteración
        //actual:
        w.push_back(*wx);

    //Este proceso se repetirá hasta que la lista de resultados
    //actuales sea igual a la anterior o hasta que terminemos
    //con el número de iteraciones posibles.
    }while(wx->getSet()!= (*(++w.rbegin())).getSet() && --nt);

    return gram;
}

Gramatica UtilidadesGramatica::algoritmoAccesible(Gramatica entrada, std::vector<UtilidadesSimbolo::SetSimbolos> &w) {
    //Iniciamos los valores de devolución:
    //La gramática resultante:
    Gramatica gram = Gramatica();

    //Y una lista de símbolos que se añadirá en cada iteración para
    //el registro de los pasos intermedios y la condición de finalización
    //del algoritmo:
    UtilidadesSimbolo::SetSimbolos* wx = new UtilidadesSimbolo::SetSimbolos();

    //Se empieza teniendo un W0 que contiene el axioma de la gramática.
    //Sabiéndose que es el símbolo no terminal de la izquierda en la
    //primera producción::
    wx->agregarElemento(entrada.getAxioma().getIzquierda());
    w.push_back(*wx);

    //Se sabe que también el algoritmo no debe de hacer más iteraciones
    //que el número de terminales que tiene la gramática.
    int nt = (int)entrada.getNoTerminales().size();

    std::vector<Produccion>::size_type tProduccion = entrada.getProducciones().size();

    //Empezamos la serie de iteraciones principal:
    do {
        //Reiniciamos nuestro W temporal y le damos los valores
        //del último W insertado a w:
        wx = new UtilidadesSimbolo::SetSimbolos();
        wx->agregar(*(w.rbegin()));

        //Recogemos un w temporal con los últimos datos insertados para evitar resultados
        //apresurados al momento de la evaluación de las expresiones regulares.
        UtilidadesSimbolo::SetSimbolos wTemp = UtilidadesSimbolo::SetSimbolos();
        wTemp.agregar(*wx);
        //Para cada una de las producciones de la gramática de entrada:
        for(unsigned int i = 0; i < tProduccion; i++) {
            //Verifivamos si el lado izquierdo contiene los símbolos terminales
            //de Wx. Para esto comparamos el lado izquierdo de la producción
            //con la expresión regular "[(simbolos)]" que sólo coincidirá con
            //la condición anteriormente mencionada.
            QRegExp regexp = QRegExp(QString("[")+QString::fromStdString(wTemp.setStr())+QString("]"));
            if(regexp.exactMatch(QString::fromStdString(entrada.getProduccion(i).getIzquierda().getSimbolo()))) {
                //En cuyo caso agregamos la parte derecha de la producción
                //a W y añadimos la producción en cuestión a nuestra
                //gramática resultante:
                wx->agregar(entrada.getProduccion(i).getDerecha());
                gram.agregarProduccion(entrada.getProduccion(i));
            }
        }

        //Al final guardamos nuestro Wx en la lista para guardar
        //el registro de los símbolos encontrados en la iteración
        //actual:
        w.push_back(*wx);

    //Este proceso se repetirá hasta que la lista de resultados
    //actuales sea igual a la anterior o hasta que terminemos
    //con el número de iteraciones posibles.
    }while(wx->getSet()!= (*(++w.rbegin())).getSet() && --nt);

    return gram;
}
