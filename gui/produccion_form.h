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

#ifndef PRODUCCIONFORM_H
#define PRODUCCIONFORM_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QToolTip>

#include "gram/produccion.h"

/*
    Definición de clase del Form que alberga una Producción.

    La clase ProduccionForm hereda de un QWidget, contiene un
    label con el número de producción, dos casilleros para las
    partes derecha e izquierda, y un botón para cerrar la producción
    actual.

    Además se conectan las señales que se lanzan al editar alguna
    de las dos partes de la producción con slots que apuntan a
    métodos de validación en vivo para despejar errores.
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
