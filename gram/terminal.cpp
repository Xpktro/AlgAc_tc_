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

#include "terminal.h"

Terminal::Terminal(): Simbolo() {
}

Terminal::Terminal(std::string simbolo): Simbolo(simbolo, Simbolo::TIPO_TERMINAL) {
}
