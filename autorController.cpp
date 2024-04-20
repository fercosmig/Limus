#include "autorController.h"

AutorController::AutorController() {}

Autor AutorController::insere(Autor autor)
{
    sql = "INSERT INTO tb_autor ( nome, id_colaborador ) ";
    sql += "VALUES ( :nome, :id_colaborador )";

    if (!conn.isOpen())
    {
        conn.open();
    }

    if (conn.isOpen())
    {
        query.exec("BEGIN IMMEDIATE TRANSACTION");

        query.prepare(sql);
        query.bindValue(":nome", autor.getNome());
        query.bindValue(":id_colaborador", QString::number(autor.getColaborador().getId()));

        if (query.exec())
        {
            sql = "SELECT id FROM tb_autor ORDER BY id DESC LIMIT 1";
            query.prepare(sql);

            if (query.exec())
            {
                if (query.next())
                {
                    autor.setId(query.record().value("id").toInt());
                }
            }
            else
            {
                qDebug() << " AutorController::insere(SELECT)" << query.lastError().text();
            }
        }
        else
        {
            qDebug() << " AutorController::insere(INSERT)" << query.lastError().text();
        }

        query.exec("COMMIT");
    }
    conn.close();
    return autor;
}

QVector<Autor> AutorController::buscaTodos(int id_colaborador)
{
    sql = "SELECT ";
    sql += "tb_autor.id, ";
    sql += "tb_autor.nome, ";
    sql += "tb_colaborador.id AS id_colaborador, ";
    sql += "tb_colaborador.nome AS nome_colaborador, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_autor ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_autor.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_colaborador.id = :id_colaborador ";
    sql += "ORDER BY tb_autor.nome ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Autor autor;
    QVector<Autor> listaAutor;

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

                    autor.setId(query.record().value("id").toInt());
                    autor.setNome(query.record().value("nome").toString());
                    autor.setColaborador(colaborador);

                    listaAutor.push_back(autor);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << " AutorController::buscaTodos()" << query.lastError().text();
        }
    }
    conn.close();
    return listaAutor;
}

QVector<Autor> AutorController::buscaPorNome(int id_colaborador, QString nome)
{
    sql = "SELECT ";
    sql += "tb_autor.id, ";
    sql += "tb_autor.nome, ";
    sql += "tb_colaborador.id AS id_colaborador, ";
    sql += "tb_colaborador.nome AS nome_colaborador, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_autor ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_autor.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_colaborador.id = :id_colaborador AND ";
    sql += "tb_autor.nome LIKE :nome ";
    sql += "ORDER BY tb_autor.nome ASC ";


    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Autor autor;
    QVector<Autor> listaAutor;

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

                    autor.setId(query.record().value("id").toInt());
                    autor.setNome(query.record().value("nome").toString());
                    autor.setColaborador(colaborador);

                    listaAutor.push_back(autor);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << " AutorController::buscaPorNome()" << query.lastError().text();
        }
    }
    conn.close();
    return listaAutor;
}

bool AutorController::altera(Autor autor)
{
    sql = "UPDATE tb_autor SET ";
    sql += "nome = :nome ";
    sql +=  "WHERE ";
    sql += "id = :id";

    if (!conn.isOpen())
    {
        conn.open();
    }

    bool retorno = false;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":nome", autor.getNome());
        query.bindValue(":id", autor.getId());

        if (query.exec())
        {
            retorno = true;
        }
        else
        {
            qDebug() << "AutorController::altera()" << query.lastError().text();
        }
    }
    conn.close();
    return retorno;
}
