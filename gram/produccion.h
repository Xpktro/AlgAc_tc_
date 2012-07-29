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

#ifndef PRODUCCION_H
#define PRODUCCION_H

#include <vector>
#include <set>

#include "gram/simbolo.h"
#include "gram/no_terminal.h"
#include "gram/utilidades_simbolo.h"

/*
    Definici�n de la clase Produccion para representar
    una producci�n de la Gram�tica.

    Consideramos una ligera variaci�n de las gram�ticas de libre
    contexto (tipo 2) al permitir un s�lo s�mbolo No Terminal en
    la parte izquierda. Sin embargo la parte derecha puede contener
    tanto s�mbolos Terminales como No Terminales (funcionalidades
    adicionales brindadas por la estructura de datos ListaSimbolos
    hecha para este programa).

    La construcci�n de esta clase permite asignar los componentes
    de la parte izquierda y derecha de la gram�tica directamente.

    Aparte de los m�todos de acceso a los miembros privados de la
    clase, se definen m�todos para informar sobre el tama�o de la
    parte derecha de la gram�tica (usado en otros procedimientos),
    un m�todo para a�adir un S�mbolo y dos funciones de generaci�n
    de texto plano.
*/

class Produccion {
        private:
        NoTerminal izquierda;
        UtilidadesSimbolo::ListaSimbolos derecha;

    public:
        NoTerminal getIzquierda();
        void setIzquierda(NoTerminal);

        UtilidadesSimbolo::ListaSimbolos getDerecha();
        void setDerecha(UtilidadesSimbolo::ListaSimbolos);

        std::vector<Simbolo>::size_type getTamanoDerecha();

        void agregarSimbolo(Simbolo);

        std::string produccionCSV();
        std::string produccionStr();

        Produccion();
        Produccion(NoTerminal, UtilidadesSimbolo::ListaSimbolos);
};

#endif // PRODUCCION_H
