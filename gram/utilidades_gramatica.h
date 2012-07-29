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

#ifndef UTILIDADESGRAMATICA_H
#define UTILIDADESGRAMATICA_H

#include <string>
#include <sstream>
#include <vector>

#include <QString>
#include <QStringList>

#include "gram/gramatica.h"
#include "gram/utilidades_simbolo.h"

/*
    Definición de la clase de Utilidades de procesamiento de Gramática.

    Se definen métodos estáticos para procesar una entrada de texto plano
    en una estructura de tipo Gramatica, además de los dos algoritmos de
    reducción bajo los criterios de símbolos Activos y Accesibles.

*/

class UtilidadesGramatica {
    public:
        UtilidadesGramatica();

        static Gramatica parsearGramatica(std::string entrada);
        static Gramatica algoritmoActivo(Gramatica entrada, std::vector<UtilidadesSimbolo::SetSimbolos> &w);
        static Gramatica algoritmoAccesible(Gramatica entrada, std::vector<UtilidadesSimbolo::SetSimbolos> &w);
};

#endif // UTILIDADESGRAMATICA_H
