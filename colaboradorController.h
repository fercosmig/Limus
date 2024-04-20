#ifndef COLABORADORCONTROLLER_H
#define COLABORADORCONTROLLER_H

#include "conexao.h"
#include "colaborador.h"

class ColaboradorController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

public:
    ColaboradorController();

    Colaborador insere(Colaborador colaborador);
    QVector<Colaborador> buscaTodos();
    QVector<Colaborador> buscaPorNomeEmail(QString nome_email);
    Colaborador autentica(Colaborador colaborador);
    bool buscaDuplicidadeEmail(QString email);
    bool altera(Colaborador colaborador);
};

#endif // COLABORADORCONTROLLER_H
