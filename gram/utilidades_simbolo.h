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

#ifndef UTILIDADESSIMBOLO_H
#define UTILIDADESSIMBOLO_H

#include <vector>
#include <set>

#include <QString>

#include "gram/simbolo.h"
#include "gram/no_terminal.h"
#include "gram/terminal.h"

/*
    Definici�n del Espacio de Nombres de Utilidades de S�mbolo
    conteniendo las clases de Lista y Set de S�mbolos.

    ListaSimbolos es una clase que envuelve a un std::vector
    de objetos Simbolo con implementaciones espec�ficas de
    m�todos de acceso y procesamiento para su uso con AlgAc[tc].

    SetSimbolos es una clase que envuelve a un std::set
    de objetos Simbolo con implementaciones espec�ficas de
    algunos constructores, m�todos de acceso y procesamiento
    para su uso con AlgAc[tc].
*/

namespace UtilidadesSimbolo {
    class ListaSimbolos {
        private:
            std::vector<Simbolo> simbolos;

        public:
            ListaSimbolos();
            ListaSimbolos(QString);

            std::vector<Simbolo> getLista();
            void setLista(std::vector<Simbolo>);
            void agregarElemento(Simbolo);

            void limpiar();

            std::string listaCSV();
            std::string listaStr();

            std::vector<Simbolo>::size_type size();
            Simbolo at(unsigned int);

            std::vector<Simbolo>::iterator getBegin();
            std::vector<Simbolo>::iterator getEnd();
    };

    class SetSimbolos {
        private:
            std::set<Simbolo> simbolos;

        public:
            SetSimbolos();

            std::set<Simbolo> getSet();
            void setSet(std::set<Simbolo>);
            void agregarElemento(Simbolo);
            void agregar(UtilidadesSimbolo::SetSimbolos);
            void agregar(std::set<Terminal>);
            void agregar(UtilidadesSimbolo::ListaSimbolos);

            void limpiar();

            std::string setCSV();
            std::string setStr();

            std::set<Simbolo>::size_type size();

            std::set<Simbolo>::iterator getBegin();
            std::set<Simbolo>::iterator getEnd();
    };
}

#endif // UTILIDADESSIMBOLO_H
