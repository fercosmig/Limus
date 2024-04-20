#ifndef SERIECONTROLLER_H
#define SERIECONTROLLER_H

#include "conexao.h"
#include "serie.h"

class SerieController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

public:
    SerieController();

    Serie insere(Serie serie);
    QVector<Serie> buscaTodos(int id_colaborador);
    QVector<Serie> buscaPorNome(int id_colaborador, QString nome);
    bool altera(Serie serie);
};

#endif // SERIECONTROLLER_H
