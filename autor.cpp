#include "autor.h"

Autor::Autor() {}

int Autor::getId() const
{
    return id;
}

void Autor::setId(int newId)
{
    id = newId;
}

QString Autor::getNome() const
{
    return nome;
}

void Autor::setNome(const QString &newNome)
{
    nome = newNome;
}

Colaborador Autor::getColaborador() const
{
    return colaborador;
}

void Autor::setColaborador(const Colaborador &newColaborador)
{
    colaborador = newColaborador;
}
