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

#include <QListWidget>

#include "tab_gramatica.h"
#include "ui_tab_gramatica.h"
#include "produccion_form.h"

TabGramatica::TabGramatica(QWidget *parent, Gramatica *gram, std::vector<UtilidadesSimbolo::SetSimbolos> *w, QString *nom) :
    QWidget(parent),
    ui(new Ui::TabGramatica)
{
    ui->setupUi(this);

    //El nombre de la pesta�a se guarda para usarlo al aplicar un
    //algoritmo o al exportar la Gram�tica a un fichero de texto.
    nombre = *nom;

    //Si la pesta�a es nueva:
    if(!gram) {
        //Se crea una nueva y se agrega:
        Produccion* prod = new Produccion();
        ProduccionForm* p = new ProduccionForm(this, prod, false, 1);
        ui->layoutProducciones->addWidget(p);

        //Cada pesta�a tiene una lista de punteros a ProduccionForm
        //para gestionar la generaci�n y eliminaci�n de Producciones.
        producciones.push_back(p);

    //De otra forma:
    } else {

        //Si la pesta�a es producto de alg�n algoritmo y tiene una
        //lista de conjuntos de s�mbolos.
        if(w) {

            //Creamos una nueva vista y la agregamos, adem�s de
            //redefinir las proporciones de los elementos en
            //pantalla.
            WForm* wf = new WForm(this, w);
            ui->layoutV->addWidget(wf);
            ui->layoutV->setStretch(0, 10);
            ui->layoutV->setStretch(1, 4);
        }

        //Populamos la pesta�a con las producciones de la Gram�tica.
        unsigned int tprod = gram->getProducciones().size();
        for(unsigned int i = 0; i < tprod; i++) {
            QWidget* p;
            Produccion prod = gram->getProduccion(i);
            p = new ProduccionForm(this, &prod, i, producciones.size()+1);
            ui->layoutProducciones->addWidget(p);
            producciones.push_back(qobject_cast<ProduccionForm*>(p));
            connect(qobject_cast<ProduccionForm*>(p)->getBtnCerrar(), SIGNAL(clicked()),
                    this, SLOT(cerrarProduccion()));
        }
    }
}

TabGramatica::~TabGramatica() {
    delete ui;
}

QString TabGramatica::getNombre() {
    return nombre;
}

void TabGramatica::agregarProduccion() {
    Produccion* p = new Produccion();
    ProduccionForm *pForm = new ProduccionForm(this, p, true, producciones.size()+1);
    producciones.push_back(pForm);
    ui->layoutProducciones->addWidget(pForm);
    connect(pForm->getBtnCerrar(), SIGNAL(clicked()),
            this, SLOT(cerrarProduccion()));
}

void TabGramatica::cerrarProduccion() {
    //qobject_cast es una funci�n de casting especifica para transformar
    //QObjects. QObject::sender() es una funci�n especial que devuelve
    //un puntero al QObject que envi� la se�al al slot.
    QPushButton *b = qobject_cast<QPushButton*>(QObject::sender());

    //takeAt devuelve el objeto del QList en determinada posici�n y lo quita
    //de la lista.
    delete producciones.takeAt(producciones.indexOf(qobject_cast<ProduccionForm*>(b->parent())));
    unsigned int tProd = producciones.size();
    for(unsigned int i = 0; i < tProd; ++i) {
        producciones.at(i)->actualizarNumero(i+1);
    }
    this->update();
}

bool TabGramatica::validarProducciones() {
    unsigned int tProd = producciones.size();
    for(unsigned int i = 0; i < tProd; ++i) {
        if(!producciones.at(i)->validarProduccion()){
            return false;
        }
    }
    return true;
}

std::vector<Produccion*>* TabGramatica::getProducciones() {

    //La lista de Producciones se genera din�micamente a pedido.
    std::vector<Produccion*>* resultado = new std::vector<Produccion*>;
    unsigned int tProd = producciones.size();
    for(unsigned int i = 0; i < tProd; ++i) {
        resultado->push_back(producciones.at(i)->getProduccion());
    }
    return resultado;
}

QPushButton* TabGramatica::getBtnActivo() {
    return ui->btnAlgActivo;
}

QPushButton* TabGramatica::getBtnAccesible() {
    return ui->btnAlgAccesible;
}
