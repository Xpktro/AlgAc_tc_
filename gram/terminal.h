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

#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>

#include "gram/simbolo.h"

/*
    Definición de la clase Terminal.

    Hereda de Simbolo, con la única variación de la asignación
    de una constante especial de identificación durante su
    construcción.
*/

class Terminal : public Simbolo {
    public:
        Terminal();
        Terminal(std::string);
};

#endif // TERMINAL_H
