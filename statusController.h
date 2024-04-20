#ifndef STATUSCONTROLLER_H
#define STATUSCONTROLLER_H

#include "conexao.h"
#include "status.h"

class StatusController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

public:
    StatusController();

    QVector<Status> buscaTodos();
};

#endif // STATUSCONTROLLER_H
