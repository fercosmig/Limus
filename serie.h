#ifndef SERIE_H
#define SERIE_H

#include "colaborador.h"

class Serie
{
protected:
    int id;
    QString nome;
    Colaborador colaborador;

public:
    Serie();

    int getId() const;
    void setId(int newId);
    QString getNome() const;
    void setNome(const QString &newNome);
    Colaborador getColaborador() const;
    void setColaborador(const Colaborador &newColaborador);
};

#endif // SERIE_H

/*
CREATE TABLE tb_serie (
    id             INTEGER   PRIMARY KEY AUTOINCREMENT,
    nome           TEXT (30) NOT NULL ON CONFLICT ROLLBACK,
    id_colaborador INTEGER   REFERENCES tb_colaborador (id) ON DELETE CASCADE NOT NULL ON CONFLICT ROLLBACK
);
*/
