#ifndef MUSICACONTROLLER_H
#define MUSICACONTROLLER_H

#include "conexao.h"
#include "musica.h"

class MusicaController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

public:
    MusicaController();

    Musica insere(Musica musica);
    QVector<Musica> buscaPorColaborador(int id_colaborador);
    QVector<Musica> buscaPorColaboradorMusica(int id_colaborador, QString nome);
    QVector<Musica> buscaPorColaboradorAlbum(int id_colaborador, QString nome);
    QVector<Musica> buscaPorColaboradorBanda(int id_colaborador, QString nome);
    bool altera(Musica musica);
};

#endif // MUSICACONTROLLER_H
