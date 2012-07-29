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

#ifndef GRAMATICA_H
#define GRAMATICA_H

#include <vector>
#include <set>
#include <string>

#include "gram/produccion.h"
#include "gram/terminal.h"
#include "gram/utilidades_simbolo.h"

/*
    Definición de la clase Gramatica para la representación de
    una gramática de contexto libre (tipo 2) que sólo acepta
    un símbolo no terminal en la parte izquierda de sus producciones.

    Posee como miebros a las mismas producciones y dos estructuras
    de datos de tipo std::set para albergar a todos los símbolos
    terminales y no terminales que la componen, usadas para generar
    un texto plano que puede guardarse en un fichero.

    Los métodos de clase permiten tener acceso a los miembros de
    la clase, además de permitir obtener la primera producción (que
    se considera como la que contiene el Axioma), asi como también
    la administración básica de las producciones y la generación
    de la gramática en un formato comprensible por humanos.
*/

class Gramatica {
    private:
        std::vector<Produccion> producciones;
        std::set<Terminal> terminales;
        std::set<NoTerminal> noTerminales;

    public:
        Gramatica();

        std::vector<Produccion> getProducciones();
        Produccion getProduccion(unsigned int);
        Produccion getAxioma();

        std::set<Terminal> getTerminales();
        std::set<NoTerminal> getNoTerminales();

        void agregarProduccion(Produccion);
        void limpiarProducciones();

        std::string gramaticaStr();
        std::string alfabetoCSV();
};

#endif // GRAMATICA_H
