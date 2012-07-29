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

#ifndef SIMBOLO_H
#define SIMBOLO_H

#include <string>

/*
    Definición de la clase Simbolo, para representar a cada
    tipo de símbolo presente en una Gramática.

    De esta clase se heredarán dos correspondientes a los tipos
    de símbolos, diferenciados por una constante entera y estática.

    Para efectos de análisis y facilidad de procesamiento, sólo
    se consideran como símbolos a las letras del alfabeto, tanto
    mayúsculas (para los No Terminales) como minúsculas (para
    los Terminales).

    Además de los métodos de acceso y constructores para esta
    clase, se implementan dos operadores: el de igualdad y el
    de desigualdad por un sentido, para facilitar operaciones
    sencillas que necesitan algunas estructuras de datos
    de la STL como std::vector y std::set.
*/

class Simbolo {
    private:
        std::string simbolo;
        int tipo;

    public:
        static const int TIPO_TERMINAL = 1;
        static const int TIPO_NO_TERMINAL = 2;

        void setSimbolo(std::string);
        std::string getSimbolo() const;

        void setTipo(int);
        int getTipo();

        Simbolo();
        Simbolo(std::string, int);

        friend bool operator < (Simbolo a, Simbolo b);
        friend bool operator == (Simbolo a, Simbolo b);

};

#endif // SIMBOLO_H
