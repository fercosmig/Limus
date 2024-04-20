#ifndef GRUPOCONTROLLER_H
#define GRUPOCONTROLLER_H

#include "conexao.h"
#include "grupo.h"

class GrupoController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

public:
    GrupoController();

    Grupo insere(Grupo grupo);
    QVector<Grupo> buscaTodos();
    QVector<Grupo> buscaPorNome(QString nome);
    Grupo buscaPorId(int id);
    bool buscaDuplicidadeSigla(QString sigla);
    bool altera(Grupo grupo);
};

#endif // GRUPOCONTROLLER_H
