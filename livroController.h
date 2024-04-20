#ifndef LIVROCONTROLLER_H
#define LIVROCONTROLLER_H

#include "conexao.h"
#include "livro.h"

class LivroController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

public:
    LivroController();

    Livro insere(Livro livro);
    QVector<Livro> buscaPorColaborador(int id_colaborador);
    QVector<Livro> buscaPorColaboradorNome(int id_colaborador, QString nome);
    QVector<Livro> buscaPorColaboradorSerie(int id_colaborador, QString serie);
    bool altera(Livro livro);
};

#endif // LIVROCONTROLLER_H
