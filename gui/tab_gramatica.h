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

#ifndef TABGRAMATICA_H
#define TABGRAMATICA_H

#include <QWidget>
#include <QList>
#include <QString>

#include "gram/gramatica.h"
#include "gram/utilidades_simbolo.h"
#include "gui/produccion_form.h"
#include "gui/wform.h"

/*
    Definición de clase del TabWidget que alberga una Gramática.

    TabGramatica alberga a todas sus producciones y contiene
    además tres botones: uno para añadir una producción a la
    gramática, y dos atajos para aplicar los algoritmos Activo
    y Accesible.
*/

namespace Ui {
class TabGramatica;
}

class TabGramatica : public QWidget
{
    Q_OBJECT
    
public:
    explicit TabGramatica(QWidget *parent = 0, Gramatica *gram = 0, std::vector<UtilidadesSimbolo::SetSimbolos> *w = 0, QString *nom = 0);
    Gramatica generaGramatica();
    ~TabGramatica();

    bool validarProducciones();
    std::vector<Produccion*>* getProducciones();
    QPushButton* getBtnActivo();
    QPushButton* getBtnAccesible();
    QString getNombre();

public slots:
    void agregarProduccion();
    void cerrarProduccion();
    
private:
    Ui::TabGramatica *ui;
    QString nombre;
    QList<ProduccionForm*> producciones;
};

#endif // TABGRAMATICA_H
