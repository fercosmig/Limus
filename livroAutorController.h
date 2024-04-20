#ifndef LIVROAUTORCONTROLLER_H
#define LIVROAUTORCONTROLLER_H

#include "conexao.h"
#include "livroAutor.h"

class LivroAutorController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

public:
    LivroAutorController();

    bool insere(LivroAutor livroAutor);
    bool buscaRelacionamentoDuplicado(LivroAutor livroAutor);
    QVector<Autor> buscaAutorPorIdLivro(int id_livro);
    QVector<Livro> buscaLivroPorNomeAutor(int id_colaborador, QString nome);
    QVector<Autor> buscaAutorNaoSelecionado(int id_colaborador, int id_livro);
    bool remove(int id_livro);
};

#endif // LIVROAUTORCONTROLLER_H
