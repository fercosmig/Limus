#include "serie.h"

Serie::Serie() {}

int Serie::getId() const
{
    return id;
}

void Serie::setId(int newId)
{
    id = newId;
}

QString Serie::getNome() const
{
    return nome;
}

void Serie::setNome(const QString &newNome)
{
    nome = newNome;
}

Colaborador Serie::getColaborador() const
{
    return colaborador;
}

void Serie::setColaborador(const Colaborador &newColaborador)
{
    colaborador = newColaborador;
}
