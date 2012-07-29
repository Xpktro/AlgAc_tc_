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

#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QMessageBox>

#include "gram/utilidades_gramatica.h"
#include "gui/tab_gramatica.h"

/*
    Definici�n de la clase que representa la Ventana Principal
    de AlgAc[tc].

    La Ventana Principal se encarga de gestionar y agrupar a
    todas las producciones en pesta�as, adem�s de controlar la
    importaci�n y exportaci�n (a texto plano) de las Gram�ticas.

    Todas las acciones de la interfaz se implementan en los
    slots p�blicos de esta clase, adem�s de contener un contador
    interno usado para nombrar a las nuevas Gram�ticas.
*/

namespace Ui {
class VentanaPrincipal;
}

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit VentanaPrincipal(QWidget *parent = 0);
    ~VentanaPrincipal();
    
private slots:
    void on_actionCerrarGramatica_triggered();
    void on_actionSalir_triggered();
    void on_actionAnadirGramatica_triggered();
    void on_actionAbrirGramatica_triggered();
    void on_actionAcerca_de_triggered();
    void on_actionAcerca_de_Qt_triggered();
    void on_actionAplicarAlgoritmo_triggered();
    void on_actionGuardarGramatica_triggered();

public slots:
    void algAccesible();
    void algActivo();

private:
    Ui::VentanaPrincipal *ui;
    int num;
};

#endif // VENTANAPRINCIPAL_H
