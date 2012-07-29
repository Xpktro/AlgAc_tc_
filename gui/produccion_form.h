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

#ifndef PRODUCCIONFORM_H
#define PRODUCCIONFORM_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QToolTip>

#include "gram/produccion.h"

/*
    Definici�n de clase del Form que alberga una Producci�n.

    La clase ProduccionForm hereda de un QWidget, contiene un
    label con el n�mero de producci�n, dos casilleros para las
    partes derecha e izquierda, y un bot�n para cerrar la producci�n
    actual.

    Adem�s se conectan las se�ales que se lanzan al editar alguna
    de las dos partes de la producci�n con slots que apuntan a
    m�todos de validaci�n en vivo para despejar errores.
*/

namespace Ui {
    class ProduccionForm;
}

class ProduccionForm : public QWidget {
    Q_OBJECT
    
public:
    explicit ProduccionForm(QWidget *parent = 0, Produccion *prod = 0, bool enableClose = false, unsigned int pos = 0);
    void actualizarNumero(int);
    bool validarProduccion();
    Produccion* getProduccion();
    QPushButton* getBtnCerrar();
    ~ProduccionForm();
    unsigned int posicion;
    
public slots:
    void verificaDerecha(QString);
    void verificaIzquierda(QString);

private:
    Ui::ProduccionForm *ui;
};

#endif // PRODUCCIONFORM_H
