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

#include "gramatica.h"

Gramatica::Gramatica() {
}

std::vector<Produccion> Gramatica::getProducciones() {
    return producciones;
}

Produccion Gramatica::getProduccion(unsigned int i) {
    return producciones.at(i);
}

Produccion Gramatica::getAxioma() {
    //Considerándose al Axioma de toda Gramática en la
    //primera producción.
    return producciones.at(0);
}

std::set<Terminal> Gramatica::getTerminales() {
    return terminales;
}

std::set<NoTerminal> Gramatica::getNoTerminales() {
    return noTerminales;
}

void Gramatica::agregarProduccion(Produccion pro) {

    // Cada producción debe de ser única en toda la Gramática

    std::vector<Produccion>::size_type tProd = producciones.size();
    for(unsigned int i = 0; i < tProd; i++) {
        if(producciones[i].produccionStr() == pro.produccionStr()) return;
    }

    // Una vez terminada la comprobación, se inserta el lado izquierdo
    // en la Gramática
    noTerminales.insert(pro.getIzquierda());

    // Para el lado derecho se comprueba la naturaleza de cada uno de los Símbolos
    // y se insertan a cada uno de sus conjuntos.
    std::vector<Simbolo>::size_type tDer = pro.getTamanoDerecha();
    for(unsigned int i = 0; i < tDer; i++) {
        if(pro.getDerecha().at(i).getTipo()==Simbolo::TIPO_NO_TERMINAL) {
            NoTerminal* n = new NoTerminal(pro.getDerecha().at(i).getSimbolo());
            noTerminales.insert(*n);
        }
        else if(pro.getDerecha().at(i).getTipo()==Simbolo::TIPO_TERMINAL) {
            Terminal* t = new Terminal(pro.getDerecha().at(i).getSimbolo());
            terminales.insert(*t);
        }
    }

    producciones.push_back(pro);
}

std::string Gramatica::gramaticaStr() {

    // Función de autogeneración de Gramática en formato de texto plano
    // para ser exportado a un fichero.

    std::string resultado =
            ";Definición de Gramática Autogenerada de AlgAc[tc]\n\n"
            ";Terminales: ";

    typedef std::set<Terminal>::iterator TermIter;
    for(TermIter i = terminales.begin(); i != terminales.end(); i++) {
        if(i != terminales.begin()) resultado += ", ";
        resultado += (*i).getSimbolo();
    }

    resultado += "\n"
            ";No Terminales: ";

    typedef std::set<NoTerminal>::iterator NTermIter;
    for(NTermIter i = noTerminales.begin(); i != noTerminales.end(); i++) {
        if(i != noTerminales.begin()) resultado += ", ";
        resultado += (*i).getSimbolo();
    }

    resultado += "\n\n"
            ";Producciones:\n";

    typedef std::vector<Produccion>::iterator ListaIter;
    for(ListaIter i = producciones.begin(); i != producciones.end(); i++) {
        if(i != producciones.begin()) resultado += "\n";
        resultado += (*i).produccionStr();
    }
    return resultado;
}

std::string Gramatica::alfabetoCSV() {

    // Función de autogeneración del alfabeto de una Gramática en
    // formato de texto plano. Actualmente no usado por AlgAc[tc]

    UtilidadesSimbolo::ListaSimbolos alfabeto;

    alfabeto.getLista().insert(alfabeto.getLista().end(),
                               terminales.begin(),
                               terminales.end());

    alfabeto.getLista().insert(alfabeto.getLista().end(),
                               noTerminales.begin(),
                               noTerminales.end());

    return alfabeto.listaCSV();
}
