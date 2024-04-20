#include "album.h"

Album::Album() {}

int Album::getId() const
{
    return id;
}

void Album::setId(int newId)
{
    id = newId;
}

QString Album::getNome() const
{
    return nome;
}

void Album::setNome(const QString &newNome)
{
    nome = newNome;
}

int Album::getAno() const
{
    return ano;
}

void Album::setAno(int newAno)
{
    ano = newAno;
}

Banda Album::getBanda() const
{
    return banda;
}

void Album::setBanda(const Banda &newBanda)
{
    banda = newBanda;
}

Colaborador Album::getColaborador() const
{
    return colaborador;
}

void Album::setColaborador(const Colaborador &newColaborador)
{
    colaborador = newColaborador;
}
