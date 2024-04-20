#include "status.h"

Status::Status() {}

int Status::getId() const
{
    return id;
}

void Status::setId(int newId)
{
    id = newId;
}

QString Status::getNome() const
{
    return nome;
}

void Status::setNome(const QString &newNome)
{
    nome = newNome;
}
