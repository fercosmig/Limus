#ifndef BANDA_H
#define BANDA_H

#include "colaborador.h"

class Banda
{
private:
    int id;
    QString nome;
    Colaborador colaborador;

public:
    Banda();

    int getId() const;
    void setId(int newId);
    QString getNome() const;
    void setNome(const QString &newNome);
    Colaborador getColaborador() const;
    void setColaborador(const Colaborador &newColaborador);
};

#endif // BANDA_H
