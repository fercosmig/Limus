#ifndef MUSICA_H
#define MUSICA_H

#include "album.h"

class Musica
{
private:
    int id;
    QString nome;
    int indice;
    Album album;
    Colaborador colaborador;

public:
    Musica();

    int getId() const;
    void setId(int newId);
    QString getNome() const;
    void setNome(const QString &newNome);
    int getIndice() const;
    void setIndice(int newIndice);
    Album getAlbum() const;
    void setAlbum(const Album &newAlbum);
    Colaborador getColaborador() const;
    void setColaborador(const Colaborador &newColaborador);
};

#endif // MUSICA_H
