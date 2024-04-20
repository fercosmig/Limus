#include "global.h"

#include <QHeaderView>

global::global() {}

// VARIÁVEIS GLOBAIS
bool global::isLogged;
Colaborador global::colaboradorLogado;
QSqlDatabase global::database;
QString global::version;

// FUNÇÕES GLOBAIS
void global::inicializaVariaveisGlobais()
{
    QString app_path, banco_de_dados;

    app_path = qApp->applicationDirPath();
    banco_de_dados = "/db/limus.db";

    global::database = QSqlDatabase::addDatabase("QSQLITE");
    global::database.setDatabaseName(app_path + banco_de_dados);

    global::isLogged = false;
    global::version = "1.0";
}

bool global::minimoCaracteres(QString texto, int quantidade_caracteres)
{
    if (texto.length() < quantidade_caracteres)
    {
        return false;
    }
    return true;
}

void global::formataTableWidget(QTableWidget *table_widget, QStringList cabecalho)
{
    int colunas = cabecalho.size();

    table_widget->clear();
    table_widget->setRowCount(0);
    table_widget->setColumnCount(colunas);
    table_widget->setHorizontalHeaderLabels(cabecalho);
    table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_widget->verticalHeader()->setVisible(false);
    table_widget->setSelectionMode(QAbstractItemView::SingleSelection);
    table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
