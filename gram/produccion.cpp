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

#include "produccion.h"

Produccion::Produccion(){
    UtilidadesSimbolo::ListaSimbolos* l = new UtilidadesSimbolo::ListaSimbolos();
    derecha = *l;
}

Produccion::Produccion(NoTerminal izquierda, UtilidadesSimbolo::ListaSimbolos derecha){
    setIzquierda(izquierda);
    setDerecha(derecha);
}

NoTerminal Produccion::getIzquierda() {
    return izquierda;
}

void Produccion::setIzquierda(NoTerminal noterm) {
    izquierda = noterm;
}

UtilidadesSimbolo::ListaSimbolos Produccion::getDerecha() {
    return derecha;
}

void Produccion::setDerecha(UtilidadesSimbolo::ListaSimbolos simb) {
    derecha = simb;
}

std::vector<Simbolo>::size_type Produccion::getTamanoDerecha() {
    return derecha.size();
}

void Produccion::agregarSimbolo(Simbolo simb) {
    derecha.agregarElemento(simb);
}

std::string Produccion::produccionCSV() {
    return izquierda.getSimbolo() + " -> " + derecha.listaCSV();
}

std::string Produccion::produccionStr() {
    return izquierda.getSimbolo() + " -> " + derecha.listaStr();
}
