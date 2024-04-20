#include "bandaController.h"

BandaController::BandaController() {}

Banda BandaController::insere(Banda banda)
{
    sql = "INSERT INTO tb_banda ( nome, id_colaborador ) ";
    sql += "VALUES ( :nome, :id_colaborador ) ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    if (conn.isOpen())
    {
        query.exec("BEGIN IMMEDIATE TRANSACTION");

        query.prepare(sql);
        query.bindValue(":nome", banda.getNome());
        query.bindValue(":id_colaborador", QString::number(banda.getColaborador().getId()));

        if (query.exec())
        {
            sql = "SELECT id FROM tb_banda ORDER BY id DESC LIMIT 1";
            query.prepare(sql);
            if (query.exec())
            {
                if (query.next())
                {
                    banda.setId(query.record().value("id").toInt());
                }
            }
            else
            {
                qDebug() << "BandaController::insere() query.exec(SELECT)" << query.lastError().text();
            }
        }
        else
        {
            qDebug() << "BandaController::insere() query.exec(INSERT)" << query.lastError().text();
        }

        query.exec("COMMIT");
    }
    conn.close();
    return banda;
}

QVector<Banda> BandaController::buscaPorColaborador(int id_colaborador)
{
    sql = "SELECT ";
    sql += "tb_banda.id, ";
    sql += "tb_banda.nome, ";
    sql += "tb_colaborador.id AS id_colaborador, ";
    sql += "tb_colaborador.nome AS nome_colaborador, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_banda ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_banda.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_colaborador.id = :id_colaborador ";
    sql += "ORDER BY tb_banda.nome ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Banda banda;
    QVector<Banda> listaBanda;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":id_colaborador", id_colaborador);

        if (query.exec())
        {
            if (query.next())
            {
                do
                {
                    grupo.setId(query.record().value("id_grupo").toInt());
                    grupo.setNome(query.record().value("nome_grupo").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    colaborador.setId(query.record().value("id_colaborador").toInt());
                    colaborador.setNome(query.record().value("nome_colaborador").toString());
                    colaborador.setEmail(query.record().value("email").toString());
                    colaborador.setSenha(query.record().value("senha").toString());
                    colaborador.setGrupo(grupo);

                    banda.setId(query.record().value("id").toInt());
                    banda.setNome(query.record().value("nome").toString());
                    banda.setColaborador(colaborador);

                    listaBanda.push_back(banda);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "BandaController::buscaPorColaborador() query.exec()" << query.lastError().text();
        }
    }
    conn.close();
    return listaBanda;
}

QVector<Banda> BandaController::buscaPorColaboradorNome(int id_colaborador, QString nome)
{
    sql = "SELECT ";
    sql += "tb_banda.id, ";
    sql += "tb_banda.nome, ";
    sql += "tb_colaborador.id AS id_colaborador, ";
    sql += "tb_colaborador.nome AS nome_colaborador, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_banda ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_banda.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_colaborador.id = :id_colaborador AND ";
    sql += "tb_banda.nome LIKE :nome ";
    sql += "ORDER BY tb_banda.nome ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Banda banda;
    QVector<Banda> listaBanda;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":id_colaborador", id_colaborador);
        query.bindValue(":nome", "%" + nome + "%");

        if (query.exec())
        {
            if (query.next())
            {
                do
                {
                    grupo.setId(query.record().value("id_grupo").toInt());
                    grupo.setNome(query.record().value("nome_grupo").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    colaborador.setId(query.record().value("id_colaborador").toInt());
                    colaborador.setNome(query.record().value("nome_colaborador").toString());
                    colaborador.setEmail(query.record().value("email").toString());
                    colaborador.setSenha(query.record().value("senha").toString());
                    colaborador.setGrupo(grupo);

                    banda.setId(query.record().value("id").toInt());
                    banda.setNome(query.record().value("nome").toString());
                    banda.setColaborador(colaborador);

                    listaBanda.push_back(banda);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "BandaController::buscaPorColaboradorNome() query.exec()" << query.lastError().text();
        }
    }
    conn.close();
    return listaBanda;
}

bool BandaController::altera(Banda banda)
{
    sql = "UPDATE tb_banda SET ";
    sql += "nome = :nome ";
    sql += "WHERE ";
    sql += "id = :id ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    bool retorno = false;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":nome", banda.getNome());
        query.bindValue(":id", QString::number(banda.getId()));

        if (query.exec())
        {
            retorno = true;
        }
        else
        {
            qDebug() << "BandaController::altera() query.exec()" << query.lastError().text();
        }
    }
    conn.close();
    return retorno;
}
