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

#ifndef PRODUCCION_H
#define PRODUCCION_H

#include <vector>
#include <set>

#include "gram/simbolo.h"
#include "gram/no_terminal.h"
#include "gram/utilidades_simbolo.h"

/*
    Definición de la clase Produccion para representar
    una producción de la Gramática.

    Consideramos una ligera variación de las gramáticas de libre
    contexto (tipo 2) al permitir un sólo símbolo No Terminal en
    la parte izquierda. Sin embargo la parte derecha puede contener
    tanto símbolos Terminales como No Terminales (funcionalidades
    adicionales brindadas por la estructura de datos ListaSimbolos
    hecha para este programa).

    La construcción de esta clase permite asignar los componentes
    de la parte izquierda y derecha de la gramática directamente.

    Aparte de los métodos de acceso a los miembros privados de la
    clase, se definen métodos para informar sobre el tamaño de la
    parte derecha de la gramática (usado en otros procedimientos),
    un método para añadir un Símbolo y dos funciones de generación
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
