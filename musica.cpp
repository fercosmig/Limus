#include "musica.h"

Musica::Musica() {}

int Musica::getId() const
{
    return id;
}

void Musica::setId(int newId)
{
    id = newId;
}

QString Musica::getNome() const
{
    return nome;
}

void Musica::setNome(const QString &newNome)
{
    nome = newNome;
}

int Musica::getIndice() const
{
    return indice;
}

void Musica::setIndice(int newIndice)
{
    indice = newIndice;
}

Album Musica::getAlbum() const
{
    return album;
}

void Musica::setAlbum(const Album &newAlbum)
{
    album = newAlbum;
}

Colaborador Musica::getColaborador() const
{
    return colaborador;
}

void Musica::setColaborador(const Colaborador &newColaborador)
{
    colaborador = newColaborador;
}
