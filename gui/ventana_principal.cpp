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

#include "ventana_principal.h"
#include "ui_ventana_principal.h"

VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);

    //Reubicamos la Ventana Principal al centro de la pantalla.
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x, y);

    //Actualizamos el mensaje de la barra de estado.
    statusBar()->showMessage("Bienvenido a AlgAc[tc]");

    //Inicializamos el contador de Gram�ticas nuevas.
    num = 1;

    //A�adimos la Gram�tica.
    on_actionAnadirGramatica_triggered();
}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

void VentanaPrincipal::on_actionSalir_triggered()
{
    this->close();
}

void VentanaPrincipal::on_actionCerrarGramatica_triggered()
{
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
}

void VentanaPrincipal::on_actionAnadirGramatica_triggered()
{
    //Generamos un nuevo nombre para la Gram�tica Nueva:
    QString nombre = "Gramatica " + QString::number(num++);

    //Se a�ade la nueva pesta�a y se conectan las se�ales de los
    //botones de los algoritmos.
    TabGramatica *tab = new TabGramatica(this, NULL, NULL, &nombre);
    ui->tabWidget->addTab(qobject_cast<QWidget*>(tab), nombre);
    ui->tabWidget->setCurrentWidget(tab);
    connect(tab->getBtnAccesible(), SIGNAL(clicked()),
            this, SLOT(algAccesible()));
    connect(tab->getBtnActivo(), SIGNAL(clicked()),
            this, SLOT(algActivo()));
}

void VentanaPrincipal::on_actionAbrirGramatica_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Abrir Gram�tica",
                               QDir::currentPath(),
                               "Archivos de Gramatica (*.txt)");
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        //Creamos un objeto de tipo QFileInfo para obtener el nombre
        //del fichero abierto.
        QFileInfo fileInfo(file.fileName());

        //Creamos la nueva Gram�tica a partir del fichero de texto abierto.
        Gramatica gram = UtilidadesGramatica::parsearGramatica(QString::fromUtf8(file.readAll()).toStdString());

        //Creamos una nueva pesta�a con la Gram�tica obtenida y la agregamos.
        TabGramatica* tab = new TabGramatica(this, &gram, NULL, &fileInfo.baseName());
        ui->tabWidget->addTab(qobject_cast<QWidget*>(tab), fileInfo.baseName());
        ui->tabWidget->setCurrentWidget(tab);
        connect(tab->getBtnAccesible(), SIGNAL(clicked()),
                this, SLOT(algAccesible()));
        connect(tab->getBtnActivo(), SIGNAL(clicked()),
                this, SLOT(algActivo()));
        file.close();
    }
}

void VentanaPrincipal::algActivo() {

    //Reconocemos a la pesta�a activa para aplicarle el algoritmo:
    TabGramatica* tab = qobject_cast<TabGramatica*>(ui->tabWidget->currentWidget());

    //Advertimos de posibles errores de validaci�n antes de hacer nada:
    if(!tab->validarProducciones()){
        QMessageBox::warning(this, "Error de Validaci�n",
                             "Complete todas las producciones o elimine las que considere innecesarias.",
                             QMessageBox::Ok);
        return;
    }

    //Creamos un nuevo contenedor de los resultados intermedios:
    std::vector<UtilidadesSimbolo::SetSimbolos>* w = new std::vector<UtilidadesSimbolo::SetSimbolos>();

    //Recreamos la Gram�tica de la pesta�a:
    Gramatica* gram = new Gramatica();
    std::vector<Produccion*>* producciones = tab->getProducciones();
    Produccion* prod = NULL;
    unsigned int tProd = producciones->size();
    for(unsigned int i = 0; i < tProd; i++) {
        prod = producciones->at(i);
        gram->agregarProduccion(*prod);
    }

    //Aplicamos el Algoritmo:
    Gramatica resultado = UtilidadesGramatica::algoritmoActivo(*gram, *w);

    //Creamos una nueva pesta�a con el resultado y la a�adimos a la ventana:
    TabGramatica *nTab = new TabGramatica(this, &resultado, w, &tab->getNombre().append("_Act"));
    ui->tabWidget->addTab(qobject_cast<QWidget*>(nTab), tab->getNombre().append("_Act"));
    ui->tabWidget->setCurrentWidget(nTab);
    connect(nTab->getBtnAccesible(), SIGNAL(clicked()),
            this, SLOT(algAccesible()));
    connect(nTab->getBtnActivo(), SIGNAL(clicked()),
            this, SLOT(algActivo()));
}

void VentanaPrincipal::algAccesible() {

    //Reconocemos a la pesta�a activa para aplicarle el algoritmo:
    TabGramatica* tab = qobject_cast<TabGramatica*>(ui->tabWidget->currentWidget());

    //Advertimos de posibles errores de validaci�n antes de hacer nada:
    if(!tab->validarProducciones()){
        QMessageBox::warning(this, "Error de Validaci�n",
                             "Complete todas las producciones o elimine las que considere innecesarias.",
                             QMessageBox::Ok);
        return;
    }

    //Creamos un nuevo contenedor de los resultados intermedios:
    std::vector<UtilidadesSimbolo::SetSimbolos>* w = new std::vector<UtilidadesSimbolo::SetSimbolos>();

    //Recreamos la Gram�tica de la pesta�a:
    Gramatica* gram = new Gramatica();
    std::vector<Produccion*>* producciones = tab->getProducciones();
    Produccion* prod = NULL;
    unsigned int tProd = producciones->size();
    for(unsigned int i = 0; i < tProd; i++) {
        prod = producciones->at(i);
        gram->agregarProduccion(*prod);
    }

    //Aplicamos el Algoritmo:
    Gramatica resultado = UtilidadesGramatica::algoritmoAccesible(*gram, *w);

    //Creamos una nueva pesta�a con el resultado y la a�adimos a la ventana:
    TabGramatica *nTab = new TabGramatica(this, &resultado, w, &tab->getNombre().append("_Acc"));
    ui->tabWidget->addTab(qobject_cast<QWidget*>(nTab), tab->getNombre().append("_Acc"));
    ui->tabWidget->setCurrentWidget(nTab);
    connect(nTab->getBtnAccesible(), SIGNAL(clicked()),
            this, SLOT(algAccesible()));
    connect(nTab->getBtnActivo(), SIGNAL(clicked()),
            this, SLOT(algActivo()));
}

void VentanaPrincipal::on_actionAcerca_de_triggered()
{
    QMessageBox::about(this, "Acerca de...",
                "<center><h2 style=\"color: red\">Universidad Tecnol�gica del Per�</h2>"
                "<h2 style=\"margin-top: 0.2em\">AlgAc[tc]</h2></center>"
                "<p style=\"padding-bottom: 1em\"><ul>"
                "<li><strong>Desarrollado por: </strong> Mois�s Gabriel Cachay Tello </li>"
                "<li><strong>Curso: </strong> Matem�tica Discreta II</li>"
                "<li><strong>Profesor: </strong> Carlos An�bal De Souza Ferreyra Llaque</li>"
                "</ul></p>"
                "<center>&copy;2012 - Todos los Derechos Reservados<br />"
                "<small>El c�digo fuente de esta aplicaci�n se entrega, permiti�ndose su reproducci�n, con fines de estudio �nicamente.</small></center>");
}

void VentanaPrincipal::on_actionAcerca_de_Qt_triggered()
{
    //Muestra un mensaje con informaci�n relevante acerca de Qt.
    QMessageBox::aboutQt(this, "Acerca de Qt");
}

void VentanaPrincipal::on_actionAplicarAlgoritmo_triggered()
{
    switch(QMessageBox::question(this, "Pregunta", "�Qu� algoritmo desea aplicar a esta gram�tica?", "Activo", "Accesible", "Cancelar")) {
        case 0:
            algActivo();
            break;
        case 1:
            algAccesible();
            break;
        default: break;
    }
}

void VentanaPrincipal::on_actionGuardarGramatica_triggered()
{

    //Recogemos la referencia a la pesta�a actual:
    TabGramatica* tab = qobject_cast<TabGramatica*>(ui->tabWidget->currentWidget());

    //Verificamos la integridad de las producciones antes de guardar la
    //Gram�tica.
    if(!tab->validarProducciones()){
        QMessageBox::warning(this, "Error de Validaci�n",
                             "Complete todas las producciones o elimine las que considere innecesarias.",
                             QMessageBox::Ok);
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this,"Guardar Gramatica",
                                                    QDir::currentPath() + "/"+tab->getNombre()+".txt",
                                                    "Archivos de Gramatica (*.txt)");
    if(fileName.isEmpty())
        return;
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly|QIODevice::Text)) {

        //Recreamos la Gram�tica de la pesta�a actual:
        Gramatica gram = Gramatica();
        std::vector<Produccion*>* producciones = tab->getProducciones();
        Produccion* prod = NULL;
        unsigned int tProd = producciones->size();
        for(unsigned int i = 0; i < tProd; i++) {
            prod = producciones->at(i);
            gram.agregarProduccion(*prod);
        }

        //La volcamos en el fichero de texto:
        file.write(QString::fromStdString(gram.gramaticaStr()).toUtf8());
        file.close();
    }
}
