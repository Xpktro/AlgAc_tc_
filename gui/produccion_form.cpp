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

#include "produccion_form.h"
#include "ui_produccion_form.h"

ProduccionForm::ProduccionForm(QWidget *parent, Produccion *prod, bool enableClose, unsigned int pos) :
    QWidget(parent),
    ui(new Ui::ProduccionForm)
{
    ui->setupUi(this);
    actualizarNumero(pos);

    //Sólo se deshabilita el botón de cierre a la primera Producción
    ui->btnCerrar->setEnabled(enableClose);
    if(prod) {
        ui->txtIzquierda->setText(QString::fromStdString(prod->getIzquierda().getSimbolo()));
        ui->txtDerecha->setText(QString::fromStdString(prod->getDerecha().listaStr()));
    }
    connect(ui->txtIzquierda, SIGNAL(textChanged(QString)),
            this, SLOT(verificaIzquierda(QString)));
    connect(ui->txtDerecha, SIGNAL(textChanged(QString)),
            this, SLOT(verificaDerecha(QString)));
}

bool ProduccionForm::validarProduccion() {
    return !ui->txtIzquierda->text().isEmpty() && !ui->txtDerecha->text().isEmpty();
}

void ProduccionForm::actualizarNumero(int num) {
    posicion = num;

    //En cada acción de 'refresco' (como adicionar o eliminar una
    //producción) se deben de actualizar los números de cada producción.
    ui->lblNumero->setText(QString::number(num) + QString("."));
}

Produccion* ProduccionForm::getProduccion() {

    //Las Producciones se generan dinámicamente a pedido.
    Produccion* resultado = new Produccion();
    resultado->setDerecha(UtilidadesSimbolo::ListaSimbolos(ui->txtDerecha->text()));
    resultado->setIzquierda(NoTerminal(ui->txtIzquierda->text().toStdString()));
    return resultado;
}

QPushButton* ProduccionForm::getBtnCerrar() {
    return ui->btnCerrar;
}

ProduccionForm::~ProduccionForm() {
    delete ui;
}

void ProduccionForm::verificaIzquierda(QString texto) {

    //Por seguridad, se cortan los caracteres adicionales del lado izquierdo.
    if(texto.length()>1) {
        ui->txtIzquierda->setText(texto.at(0));
    }

    //Advertimos sobre la presencia de caracteres que no sean letras mayúsculas.
    if(!texto.isEmpty() && texto.contains(QRegExp("^[^A-Z]+$"))) {
        QMessageBox::information(this, "Información",
                 "<h2>Producción " + QString::number(posicion) + ":</h2>"
                 "El lado izquierdo de una producción debe de tener un símbolo <strong>No Terminal</strong> "
                 "y no debe de estar vacío.");
    }
}

void ProduccionForm::verificaDerecha(QString texto) {

    //Advertimos sobre la presencia de caracteres que no sean letras del alfabeto.
    if(!texto.isEmpty() && !texto.contains(QRegExp("^[A-Za-z]+$"))) {
        QMessageBox::information(this, "Información",
                 "<h2>Producción " + QString::number(posicion) + ":</h2>"
                 "El lado derecho de una producción debe de tener símbolos <strong>Terminales y "
                 "No Terminales</strong> únicamente y no debe de estar vacío.");
    }
}
