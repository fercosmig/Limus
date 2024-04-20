#include "grupoController.h"

GrupoController::GrupoController() {}

Grupo GrupoController::insere(Grupo grupo)
{
    sql = "INSERT INTO tb_grupo ";
    sql += "( nome, sigla ) ";
    sql += "VALUES ";
    sql += "( :nome, :sigla )";

    if (!conn.isOpen())
    {
        conn.open();
    }
    if (conn.isOpen())
    {
        query.exec("BEGIN IMMEDIATE TRANSACTION");

        query.prepare(sql);
        query.bindValue(":nome", grupo.getNome());
        query.bindValue(":sigla", grupo.getSigla());

        if (query.exec())
        {
            sql = "SELECT id FROM tb_grupo ORDER BY id DESC LIMIT 1";
            query.prepare(sql);
            if (query.exec())
            {
                if (query.next())
                {
                    grupo.setId(query.record().value("id").toInt());
                }
            }
            else
            {
                qDebug() << "GrupoController::insere() query.exec(SELECT): " << query.lastError().text();
            }
        }
        else
        {
            qDebug() << "GrupoController::insere() query.exec(INSERT): " << query.lastError().text();
        }

        query.exec("COMMIT");
    }
    conn.close();
    return grupo;
}

QVector<Grupo> GrupoController::buscaTodos()
{
    sql = "SELECT ";
    sql += "id, nome, sigla ";
    sql += "FROM tb_grupo ";
    sql += "ORDER BY nome ASC";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    QVector<Grupo> listaGrupo;

    if (conn.isOpen())
    {
        query.prepare(sql);

        if (query.exec())
        {
            if (query.next())
            {
                do
                {
                    grupo.setId(query.record().value("id").toInt());
                    grupo.setNome(query.record().value("nome").toString());
                    grupo.setSigla(query.record().value("sigla").toString());
                    listaGrupo.push_back(grupo);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "GrupoController::buscaTodos() query.exec(): " << query.lastError().text();
        }
    }
    conn.close();
    return listaGrupo;
}

QVector<Grupo> GrupoController::buscaPorNome(QString nome)
{
    sql = "SELECT ";
    sql += "id, nome, sigla ";
    sql += "FROM tb_grupo ";
    sql += "WHERE nome LIKE :nome ";
    sql += "ORDER BY nome ASC";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    QVector<Grupo> listaGrupo;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":nome", "%" + nome + "%");

        if (query.exec())
        {
            if (query.next())
            {
                do
                {
                    grupo.setId(query.record().value("id").toInt());
                    grupo.setNome(query.record().value("nome").toString());
                    grupo.setSigla(query.record().value("sigla").toString());
                    listaGrupo.push_back(grupo);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "GrupoController::buscaPorNome() query.exec(): " << query.lastError().text();
        }
    }
    conn.close();
    return listaGrupo;
}

Grupo GrupoController::buscaPorId(int id)
{
    sql = "SELECT ";
    sql += "id, nome, sigla ";
    sql += "FROM tb_grupo ";
    sql += "WHERE id = :id ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":id", id);

        if (query.exec())
        {
            if (query.next())
            {
                    grupo.setId(query.record().value("id").toInt());
                    grupo.setNome(query.record().value("nome").toString());
                    grupo.setSigla(query.record().value("sigla").toString());
            }
        }
        else
        {
            qDebug() << "GrupoController::buscaPorId() query.exec(): " << query.lastError().text();
        }
    }
    conn.close();
    return grupo;
}

bool GrupoController::buscaDuplicidadeSigla(QString sigla)
{
    sql = "SELECT ";
    sql += "id ";
    sql += "FROM tb_grupo ";
    sql += "WHERE sigla = :sigla";

    if (!conn.isOpen())
    {
        conn.open();
    }

    bool retorno = false;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":sigla", sigla);

        if (query.exec())
        {
            if (query.next())
            {
                retorno = true;
            }
        }
        else
        {
            qDebug() << "GrupoController::buscaDuplicidadeSigla() query.exec(): " << query.lastError().text();
        }
    }
    conn.close();
    return retorno;
}

bool GrupoController::altera(Grupo grupo)
{
    sql = "UPDATE tb_grupo SET ";
    sql += "nome = :nome, ";
    sql += "sigla = :sigla ";
    sql += "WHERE id = :id";

    if (!conn.isOpen())
    {
        conn.open();
    }

    bool retorno = false;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":nome", grupo.getNome());
        query.bindValue(":sigla", grupo.getSigla());
        query.bindValue(":id", grupo.getId());

        if (query.exec())
        {
            retorno = true;
        }
        else
        {
            qDebug() << "GrupoController::altera() query.exec(): " << query.lastError().text();
        }

    }
    conn.close();
    return retorno;
}
