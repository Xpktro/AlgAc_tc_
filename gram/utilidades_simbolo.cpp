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

#include "utilidades_simbolo.h"

UtilidadesSimbolo::ListaSimbolos::ListaSimbolos() {
    std::vector<Simbolo>* s = new std::vector<Simbolo>();
    setLista(*s);
}

UtilidadesSimbolo::ListaSimbolos::ListaSimbolos(QString entrada) {
    std::vector<Simbolo>* s = new std::vector<Simbolo>();
    setLista(*s);

    //Para cuando el string de entrada es mayor que cero:
    if(entrada.size()) {
        for(int i=0; i<entrada.size(); i++) {

            //Se detecta la capitalidad de cada símbolo para agregarlo a
            //la lista.
            if(entrada.at(i).isUpper()) {
                NoTerminal* n = new NoTerminal(QString(entrada.at(i)).toStdString());
                agregarElemento(*n);
            }
            else if(entrada.at(i).isLower()) {
                Terminal* t = new Terminal(QString(entrada.at(i)).toStdString());
                agregarElemento(*t);
            }
        }
    }
}

std::vector<Simbolo> UtilidadesSimbolo::ListaSimbolos::getLista() {
    return simbolos;
}

void UtilidadesSimbolo::ListaSimbolos::setLista(std::vector<Simbolo> lista) {
    simbolos = lista;
}

void UtilidadesSimbolo::ListaSimbolos::agregarElemento(Simbolo simb) {
    simbolos.push_back(simb);
}

void UtilidadesSimbolo::ListaSimbolos::limpiar() {
    simbolos.clear();
}

std::string UtilidadesSimbolo::ListaSimbolos::listaCSV() {
    std::string resultado;

    //Para todos los símbolos de la lista:
    typedef std::vector<Simbolo>::iterator ListaIter;
    for(ListaIter i = simbolos.begin(); i != simbolos.end(); i++) {

        //Si estamos en una iteración distinta a la primera
        //se agrega una coma y un espacio al resultado.
        if(i != simbolos.begin()) resultado += ", ";
        resultado += (*i).getSimbolo();
    }
    return resultado;
}

std::string UtilidadesSimbolo::ListaSimbolos::listaStr() {
    std::string resultado;

    typedef std::vector<Simbolo>::iterator ListaIter;
    for(ListaIter i = simbolos.begin(); i != simbolos.end(); i++) {
        resultado += (*i).getSimbolo();
    }
    return resultado;
}

std::vector<Simbolo>::size_type UtilidadesSimbolo::ListaSimbolos::size() {
    return simbolos.size();
}

Simbolo UtilidadesSimbolo::ListaSimbolos::at(unsigned int i) {
    return simbolos.at(i);
}

std::vector<Simbolo>::iterator UtilidadesSimbolo::ListaSimbolos::getBegin() {
    return simbolos.begin();
}

std::vector<Simbolo>::iterator UtilidadesSimbolo::ListaSimbolos::getEnd() {
    return simbolos.end();
}

UtilidadesSimbolo::SetSimbolos::SetSimbolos() {
    std::set<Simbolo>* s = new std::set<Simbolo>();
    setSet(*s);
}

std::set<Simbolo> UtilidadesSimbolo::SetSimbolos::getSet() {
    return simbolos;
}

void UtilidadesSimbolo::SetSimbolos::setSet(std::set<Simbolo> s) {
    simbolos = s;
}

void UtilidadesSimbolo::SetSimbolos::agregarElemento(Simbolo simb) {
    simbolos.insert(simb);
}

void UtilidadesSimbolo::SetSimbolos::limpiar() {
    simbolos.clear();
}

std::string UtilidadesSimbolo::SetSimbolos::setCSV() {
    std::string resultado;

    //Para todos los símbolos del set:
    typedef std::set<Simbolo>::iterator SetIter;
    for(SetIter i = simbolos.begin(); i != simbolos.end(); i++) {

        //Si estamos en una iteración distinta a la primera
        //se agrega una coma y un espacio al resultado.
        if(i != simbolos.begin()) resultado += ", ";
        resultado += (*i).getSimbolo();
    }
    return resultado;
}

std::string UtilidadesSimbolo::SetSimbolos::setStr() {
    std::string resultado;

    typedef std::set<Simbolo>::iterator SetIter;
    for(SetIter i = simbolos.begin(); i != simbolos.end(); i++) {
        resultado += (*i).getSimbolo();
    }
    return resultado;
}

void UtilidadesSimbolo::SetSimbolos::agregar(UtilidadesSimbolo::SetSimbolos set) {
    simbolos.insert(set.getBegin(), set.getEnd());
}

void UtilidadesSimbolo::SetSimbolos::agregar(std::set<Terminal> set) {
    simbolos.insert(set.begin(), set.end());
}

void UtilidadesSimbolo::SetSimbolos::agregar(UtilidadesSimbolo::ListaSimbolos lista) {
    std::vector<Simbolo>::size_type tLista = lista.size();
    for(unsigned int i = 0; i < tLista; i++) {
        simbolos.insert(lista.at(i));
    }
}

std::set<Simbolo>::size_type UtilidadesSimbolo::SetSimbolos::size() {
    return simbolos.size();
}

std::set<Simbolo>::iterator UtilidadesSimbolo::SetSimbolos::getBegin() {
    return simbolos.begin();
}

std::set<Simbolo>::iterator UtilidadesSimbolo::SetSimbolos::getEnd() {
    return simbolos.end();
}
