#ifndef LIVRO_H
#define LIVRO_H

#include "colaborador.h"
#include "serie.h"
#include "status.h"

class Livro
{
private:
    int id;
    QString nome;
    int indice;
    int pagina;
    Serie serie;
    Status status;
    Colaborador colaborador;

public:
    Livro();

    int getId() const;
    void setId(int newId);
    QString getNome() const;
    void setNome(const QString &newNome);
    int getIndice() const;
    void setIndice(int newIndice);
    int getPagina() const;
    void setPagina(int newPagina);
    Serie getSerie() const;
    void setSerie(const Serie &newSerie);
    Status getStatus() const;
    void setStatus(const Status &newStatus);
    Colaborador getColaborador() const;
    void setColaborador(const Colaborador &newColaborador);
};

#endif // LIVRO_H

/*
CREATE TABLE tb_livro (
    id             INTEGER   PRIMARY KEY AUTOINCREMENT,
    nome           TEXT (30) NOT NULL ON CONFLICT ROLLBACK,
    indice         INTEGER   NOT NULL ON CONFLICT ROLLBACK,
    pagina         INTEGER   NOT NULL ON CONFLICT ROLLBACK,
    id_serie       INTEGER   REFERENCES tb_serie (id) ON DELETE CASCADE NOT NULL ON CONFLICT ROLLBACK,
    id_status      INTEGER   REFERENCES tb_status (id) ON DELETE CASCADE NOT NULL ON CONFLICT ROLLBACK,
    id_colaborador INTEGER   REFERENCES tb_colaborador (id) ON DELETE CASCADE NOT NULL ON CONFLICT ROLLBACK
);
*/
