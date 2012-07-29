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

#ifndef NOTERMINAL_H
#define NOTERMINAL_H

#include <string>

#include "gram/simbolo.h"

/*
    Definición de la clase NoTerminal.

    Hereda de Simbolo, con la única variación de la asignación
    de una constante especial de identificación durante su
    construcción.
*/

class NoTerminal : public Simbolo {
    public:
        NoTerminal();
        NoTerminal(std::string);
};

#endif // NOTERMINAL_H
