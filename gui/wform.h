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

#ifndef WFORM_H
#define WFORM_H

#include <QWidget>

#include "gram/utilidades_simbolo.h"

/*
    Definición de la clase que representa la Vista de los
    conjuntos intermedios producto de la ejecución de los
    algoritmos Activo y Accesible.

    Sólo contiene un ListWidget que se rellena al momento
    de construir el objeto con los contenidos del Set de
    Símbolos que tenga como argumento.
*/

namespace Ui {
class WForm;
}

class WForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit WForm(QWidget *parent = 0, std::vector<UtilidadesSimbolo::SetSimbolos> *w = 0);
    ~WForm();

    void refreshSize();
    
private:
    Ui::WForm *ui;
};

#endif // WFORM_H
