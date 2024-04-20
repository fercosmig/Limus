#ifndef ALBUM_H
#define ALBUM_H

#include "banda.h"

class Album
{
private:
    int id;
    QString nome;
    int ano;
    Banda banda;
    Colaborador colaborador;

public:
    Album();

    int getId() const;
    void setId(int newId);
    QString getNome() const;
    void setNome(const QString &newNome);
    int getAno() const;
    void setAno(int newAno);
    Banda getBanda() const;
    void setBanda(const Banda &newBanda);
    Colaborador getColaborador() const;
    void setColaborador(const Colaborador &newColaborador);
};

#endif // ALBUM_H
