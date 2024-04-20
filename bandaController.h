#ifndef BANDACONTROLLER_H
#define BANDACONTROLLER_H

#include "banda.h"
#include "conexao.h"


class BandaController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

public:
    BandaController();

    Banda insere(Banda banda);
    QVector<Banda> buscaPorColaborador(int id_colaborador);
    QVector<Banda> buscaPorColaboradorNome(int id_colaborador, QString nome);
    bool altera(Banda banda);
};

#endif // BANDACONTROLLER_H
