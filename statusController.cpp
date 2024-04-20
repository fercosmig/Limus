#include "statusController.h"

StatusController::StatusController() {}

QVector<Status> StatusController::buscaTodos()
{
    sql = "SELECT id, nome ";
    sql += "FROM tb_status ";
    sql += "ORDER BY id ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    QVector<Status> listaStatus;
    Status status;

    if (conn.isOpen())
    {
        query.prepare(sql);

        if (query.exec())
        {
            if (query.next())
            {
                do
                {
                    status.setId(query.record().value("id").toInt());
                    status.setNome(query.record().value("nome").toString());

                    listaStatus.push_back(status);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "StatusController::buscaTodos() query.exec(): " << query.lastError().text();
        }
    }
    conn.close();
    return listaStatus;
}
