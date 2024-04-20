#ifndef CONEXAO_H
#define CONEXAO_H

#include "global.h"

class Conexao
{
public:
    Conexao();

    // MEUS MÉTODOS
    void open();
    bool isOpen();
    void close();
};

#endif // CONEXAO_H
