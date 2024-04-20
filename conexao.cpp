#include "conexao.h"

Conexao::Conexao() {}

void Conexao::open()
{
    if (!global::database.isOpen())
    {
        if (!global::database.open())
        {
            qDebug() << "Conexao::open(): " << global::database.lastError().text();
        }
    }
}

bool Conexao::isOpen()
{
    if (global::database.isOpen())
    {
        return true;
    }
    return false;
}

void Conexao::close()
{
    if (global::database.isOpen())
    {
        global::database.close();
    }
}
