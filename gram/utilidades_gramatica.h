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
    Definici�n de la clase de Utilidades de procesamiento de Gram�tica.

    Se definen m�todos est�ticos para procesar una entrada de texto plano
    en una estructura de tipo Gramatica, adem�s de los dos algoritmos de
    reducci�n bajo los criterios de s�mbolos Activos y Accesibles.

*/

class UtilidadesGramatica {
    public:
        UtilidadesGramatica();

        static Gramatica parsearGramatica(std::string entrada);
        static Gramatica algoritmoActivo(Gramatica entrada, std::vector<UtilidadesSimbolo::SetSimbolos> &w);
        static Gramatica algoritmoAccesible(Gramatica entrada, std::vector<UtilidadesSimbolo::SetSimbolos> &w);
};

#endif // UTILIDADESGRAMATICA_H
