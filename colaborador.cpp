#include "colaborador.h"

Colaborador::Colaborador() {}

int Colaborador::getId() const
{
    return id;
}

void Colaborador::setId(int newId)
{
    id = newId;
}

QString Colaborador::getNome() const
{
    return nome;
}

void Colaborador::setNome(const QString &newNome)
{
    nome = newNome;
}

QString Colaborador::getEmail() const
{
    return email;
}

void Colaborador::setEmail(const QString &newEmail)
{
    email = newEmail;
}

QString Colaborador::getSenha() const
{
    return senha;
}

void Colaborador::setSenha(const QString &newSenha)
{
    senha = newSenha;
}

Grupo Colaborador::getGrupo() const
{
    return grupo;
}

void Colaborador::setGrupo(const Grupo &newGrupo)
{
    grupo = newGrupo;
}
