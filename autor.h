#ifndef AUTOR_H
#define AUTOR_H

#include "colaborador.h"

class Autor
{
private:
    int id;
    QString nome;
    Colaborador colaborador;

public:
    Autor();

    int getId() const;
    void setId(int newId);
    QString getNome() const;
    void setNome(const QString &newNome);
    Colaborador getColaborador() const;
    void setColaborador(const Colaborador &newColaborador);
};

#endif // AUTOR_H

/*
CREATE TABLE tb_autor (
    id             INTEGER   PRIMARY KEY AUTOINCREMENT,
    nome           TEXT (30) NOT NULL ON CONFLICT ROLLBACK,
    id_colaborador INTEGER   REFERENCES tb_colaborador (id) ON DELETE CASCADE NOT NULL ON CONFLICT ROLLBACK
);
*/
