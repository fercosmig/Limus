#include "banda.h"

Banda::Banda() {}

int Banda::getId() const
{
    return id;
}

void Banda::setId(int newId)
{
    id = newId;
}

QString Banda::getNome() const
{
    return nome;
}

void Banda::setNome(const QString &newNome)
{
    nome = newNome;
}

Colaborador Banda::getColaborador() const
{
    return colaborador;
}

void Banda::setColaborador(const Colaborador &newColaborador)
{
    colaborador = newColaborador;
}
