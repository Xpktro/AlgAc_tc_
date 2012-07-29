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

#include "wform.h"
#include "ui_wform.h"

WForm::WForm(QWidget *parent, std::vector<UtilidadesSimbolo::SetSimbolos> *w) :
    QWidget(parent),
    ui(new Ui::WForm)
{
    ui->setupUi(this);

    //Agregamos una cabecera a la vista de resultados:
    ui->listWidget->addItem("W[x] Resultantes:");

    //Y populamos la vista con los elementos del set que se pasó en el
    //constructor de la instancia.
    typedef std::vector<UtilidadesSimbolo::SetSimbolos>::iterator iter;
    int ind = 0;
    for(iter i = w->begin(); i != w->end(); i++){
        ui->listWidget->addItem(QString("   W[") + QString::number(ind++) + QString("]: ") + QString::fromStdString((*i).setCSV()));
    }
}

WForm::~WForm()
{
    delete ui;
}
