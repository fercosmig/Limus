#ifndef AUTORCONTROLLER_H
#define AUTORCONTROLLER_H

#include "conexao.h"
#include "autor.h"

class AutorController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

public:
    AutorController();

    Autor insere(Autor autor);
    QVector<Autor> buscaTodos(int id_colaborador);
    QVector<Autor> buscaPorNome(int id_colaborador, QString nome);
    bool altera(Autor autor);
};

#endif // AUTORCONTROLLER_H
