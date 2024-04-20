#ifndef GLOBAL_H
#define GLOBAL_H

#include "colaborador.h"

#include <QSqlDatabase>
#include <QTableWidget>
#include <QtSql>

class global
{
public:
    global();

    // VARIÁVEIS GLOBAIS
    static bool isLogged;
    static Colaborador colaboradorLogado;
    static QSqlDatabase database;
    static QString version;

    // FUNÇÕES GLOBAIS
    static void inicializaVariaveisGlobais();
    static bool minimoCaracteres(QString texto, int quantidade_caracteres);
    static void formataTableWidget(QTableWidget *table_widget, QStringList cabecalho);
};

#endif // GLOBAL_H
