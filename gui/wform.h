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

#ifndef WFORM_H
#define WFORM_H

#include <QWidget>

#include "gram/utilidades_simbolo.h"

/*
    Definici�n de la clase que representa la Vista de los
    conjuntos intermedios producto de la ejecuci�n de los
    algoritmos Activo y Accesible.

    S�lo contiene un ListWidget que se rellena al momento
    de construir el objeto con los contenidos del Set de
    S�mbolos que tenga como argumento.
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
