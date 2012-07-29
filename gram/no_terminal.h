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

#ifndef NOTERMINAL_H
#define NOTERMINAL_H

#include <string>

#include "gram/simbolo.h"

/*
    Definici�n de la clase NoTerminal.

    Hereda de Simbolo, con la �nica variaci�n de la asignaci�n
    de una constante especial de identificaci�n durante su
    construcci�n.
*/

class NoTerminal : public Simbolo {
    public:
        NoTerminal();
        NoTerminal(std::string);
};

#endif // NOTERMINAL_H
