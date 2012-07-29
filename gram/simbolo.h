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

#ifndef SIMBOLO_H
#define SIMBOLO_H

#include <string>

/*
    Definici�n de la clase Simbolo, para representar a cada
    tipo de s�mbolo presente en una Gram�tica.

    De esta clase se heredar�n dos correspondientes a los tipos
    de s�mbolos, diferenciados por una constante entera y est�tica.

    Para efectos de an�lisis y facilidad de procesamiento, s�lo
    se consideran como s�mbolos a las letras del alfabeto, tanto
    may�sculas (para los No Terminales) como min�sculas (para
    los Terminales).

    Adem�s de los m�todos de acceso y constructores para esta
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
