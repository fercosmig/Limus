#include "livro.h"

Livro::Livro() {}

int Livro::getId() const
{
    return id;
}

void Livro::setId(int newId)
{
    id = newId;
}

QString Livro::getNome() const
{
    return nome;
}

void Livro::setNome(const QString &newNome)
{
    nome = newNome;
}

int Livro::getIndice() const
{
    return indice;
}

void Livro::setIndice(int newIndice)
{
    indice = newIndice;
}

int Livro::getPagina() const
{
    return pagina;
}

void Livro::setPagina(int newPagina)
{
    pagina = newPagina;
}

Serie Livro::getSerie() const
{
    return serie;
}

void Livro::setSerie(const Serie &newSerie)
{
    serie = newSerie;
}

Status Livro::getStatus() const
{
    return status;
}

void Livro::setStatus(const Status &newStatus)
{
    status = newStatus;
}

Colaborador Livro::getColaborador() const
{
    return colaborador;
}

void Livro::setColaborador(const Colaborador &newColaborador)
{
    colaborador = newColaborador;
}
