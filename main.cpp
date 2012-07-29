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

//Comentar las siguientes 2 líneas si no se compila en Windows:
#include <QtPlugin>
Q_IMPORT_PLUGIN(qico)

#include <QtGui/QApplication>
//#include <QPlastiqueStyle>
#include "gui/ventana_principal.h"
#include "gui/tab_gramatica.h"

/*
    Implementación del punto de entrada de AlgAc[tc].
*/

int main(int argc, char *argv[])
{
    //QApplication::setStyle(new QPlastiqueStyle);
    QApplication a(argc, argv);
    VentanaPrincipal w;
    w.show();
    
    return a.exec();
}
