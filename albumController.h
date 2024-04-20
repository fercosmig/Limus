#ifndef ALBUMCONTROLLER_H
#define ALBUMCONTROLLER_H

#include "album.h"
#include "conexao.h"


class AlbumController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

public:
    AlbumController();

    Album insere(Album album);
    Album buscaPorId(int id);
    QVector<Album> buscaPorIdBanda(int id_banda);
    QVector<Album> buscaPorColaborador(int id_colaborador);
    QVector<Album> buscaPorColaboradorNome(int id_colaborador, QString nome);
    QVector<Album> buscaPorColaboradorAno(int id_colaborador, int ano);
    QVector<Album> buscaPorColaboradorBanda(int id_colaborador, QString nome);
    bool altera(Album album);
};

#endif // ALBUMCONTROLLER_H
