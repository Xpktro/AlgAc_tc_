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

#include "simbolo.h"

Simbolo::Simbolo() {
}

Simbolo::Simbolo(std::string simb, int tip) {
    this->setSimbolo(simb);
    this->setTipo(tip);
}

std::string Simbolo::getSimbolo() const {
    return this->simbolo;
}

void Simbolo::setSimbolo(std::string simb) {
    this->simbolo = simb;
}

int Simbolo::getTipo() {
    return tipo;
}

void Simbolo::setTipo(int tip) {
    tipo = tip;
}

bool operator < (Simbolo a, Simbolo b) {

    //Se considera que un s�mbolo es menor que otro
    //cuando es 'alfab�ticamente menor'
    return a.getSimbolo() < b.getSimbolo();
}

bool operator == (Simbolo a, Simbolo b) {
  return a.getSimbolo() == b.getSimbolo();
}
