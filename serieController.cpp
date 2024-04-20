#include "serieController.h"

SerieController::SerieController() {}

Serie SerieController::insere(Serie serie)
{
    sql = "INSERT INTO tb_serie ( nome, id_colaborador ) ";
    sql += "VALUES ( :nome, :id_colaborador )";

    if (!conn.isOpen())
    {
        conn.open();
    }

    if (conn.isOpen())
    {
        query.exec("BEGIN IMMEDIATE TRANSACTION");

        query.prepare(sql);
        query.bindValue(":nome", serie.getNome());
        query.bindValue(":id_colaborador", serie.getColaborador().getId());

        if (query.exec())
        {
            sql = "SELECT id FROM tb_serie ORDER BY id DESC LIMIT 1";
            query.prepare(sql);

            if (query.exec())
            {
                if (query.next())
                {
                    serie.setId(query.record().value("id").toInt());
                }
            }
            else
            {
                qDebug () << "SerieController::insere() query.exec(SELECT) " << query.lastError().text();
            }
        }
        else
        {
            qDebug() << "SerieController::insere() query.exec(INSERT) " << query.lastError().text();
        }

        query.exec("COMMIT");
    }
    conn.close();
    return serie;
}

QVector<Serie> SerieController::buscaTodos(int id_colaborador)
{
    sql = "SELECT ";
    sql += "tb_serie.id, ";
    sql += "tb_serie.nome, ";
    sql += "tb_colaborador.id AS id_colaborador, ";
    sql += "tb_colaborador.nome AS nome_colaborador, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_serie ";
    sql += "LEFT JOIN tb_colaborador ";
    sql += "ON tb_serie.id_colaborador = tb_colaborador.id ";
    sql += "LEFT JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_colaborador.id = :id_colaborador OR ";
    sql += "tb_serie.id_colaborador isNull ";
    sql += "ORDER BY tb_serie.nome ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Serie serie;
    QVector<Serie> listaSerie;

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

                    serie.setId(query.record().value("id").toInt());
                    serie.setNome(query.record().value("nome").toString());
                    serie.setColaborador(colaborador);

                    listaSerie.push_back(serie);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "SerieController::buscaTodos() query.exec() " << query.lastError().text();
        }
    }
    conn.close();
    return listaSerie;
}

QVector<Serie> SerieController::buscaPorNome(int id_colaborador, QString nome)
{
    sql = "SELECT ";
    sql += "tb_serie.id, ";
    sql += "tb_serie.nome, ";
    sql += "tb_colaborador.id AS id_colaborador, ";
    sql += "tb_colaborador.nome AS nome_colaborador, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_serie ";
    sql += "LEFT JOIN tb_colaborador ";
    sql += "ON tb_serie.id_colaborador = tb_colaborador.id ";
    sql += "LEFT JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_colaborador.id = :id_colaborador AND ";
    sql += "tb_serie.nome LIKE :nome OR ";
    sql += "tb_serie.id_colaborador isNull ";
    sql += "ORDER BY tb_serie.nome ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Serie serie;
    QVector<Serie> listaSerie;

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

                    serie.setId(query.record().value("id").toInt());
                    serie.setNome(query.record().value("nome").toString());
                    serie.setColaborador(colaborador);

                    listaSerie.push_back(serie);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "SerieController::buscaPorNome() query.exec() " << query.lastError().text();
        }
    }
    conn.close();
    return listaSerie;
}

bool SerieController::altera(Serie serie)
{
    sql = "UPDATE tb_serie SET ";
    sql += "nome = :nome ";
    sql += "WHERE ";
    sql += "id = :id";

    if (!conn.isOpen())
    {
        conn.open();
    }

    bool retorno = false;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":nome", serie.getNome());
        query.bindValue(":id", serie.getId());

        if (query.exec())
        {
            retorno = true;
        }
        else
        {
            qDebug() << "SerieController::altera() query.exec() " << query.lastError().text();
        }
    }
    conn.close();
    return retorno;
}
