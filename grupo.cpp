#include "grupo.h"

Grupo::Grupo() {}

int Grupo::getId() const
{
    return id;
}

void Grupo::setId(int newId)
{
    id = newId;
}

QString Grupo::getNome() const
{
    return nome;
}

void Grupo::setNome(const QString &newNome)
{
    nome = newNome;
}

QString Grupo::getSigla() const
{
    return sigla;
}

void Grupo::setSigla(const QString &newSigla)
{
    sigla = newSigla;
}
