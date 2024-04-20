#include "colaboradorController.h"

ColaboradorController::ColaboradorController() {}

Colaborador ColaboradorController::insere(Colaborador colaborador)
{
    sql = "INSERT INTO tb_colaborador ";
    sql += "( nome, email, senha, id_grupo ) ";
    sql += "VALUES ";
    sql += "( :nome, :email, :senha, :id_grupo )";

    if (!conn.isOpen())
    {
        conn.open();
    }

    if (conn.isOpen())
    {
        query.exec("BEGIN IMMEDIATE TRANSACTION");

        query.prepare(sql);
        query.bindValue(":nome", colaborador.getNome());
        query.bindValue(":email", colaborador.getEmail());
        query.bindValue(":senha", colaborador.getSenha());
        query.bindValue(":id_grupo", colaborador.getGrupo().getId());

        if (query.exec())
        {
            sql = "SELECT id FROM tb_colaborador ORDER BY id DESC LIMIT 1";
            query.prepare(sql);

            if (query.exec())
            {
                if (query.next())
                {
                    colaborador.setId(query.record().value("id").toInt());
                }
            }
        }
        else
        {
            qDebug() << " ColaboradorController::insere()" << query.lastError().text();
        }

        query.exec("COMMIT");
    }
    conn.close();
    return colaborador;
}

QVector<Colaborador> ColaboradorController::buscaTodos()
{
    sql = "SELECT ";
    sql += "tb_colaborador.id, ";
    sql += "tb_colaborador.nome, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_colaborador ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "ORDER BY tb_colaborador.nome ASC";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    QVector<Colaborador> listaColaborador;

    if (conn.isOpen())
    {
        query.prepare(sql);

        if (query.exec())
        {
            if (query.next())
            {
                do
                {
                    grupo.setId(query.record().value("id_grupo").toInt());
                    grupo.setNome(query.record().value("nome_grupo").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    colaborador.setId(query.record().value("id").toInt());
                    colaborador.setNome(query.record().value("nome").toString());
                    colaborador.setEmail(query.record().value("email").toString());
                    colaborador.setSenha(query.record().value("senha").toString());
                    colaborador.setGrupo(grupo);
                    listaColaborador.push_back(colaborador);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "ColaboradorController::buscaTodos()" << query.lastError().text();
        }
    }
    conn.close();
    return listaColaborador;
}

QVector<Colaborador> ColaboradorController::buscaPorNomeEmail(QString nome_email)
{
    sql = "SELECT ";
    sql += "tb_colaborador.id, ";
    sql += "tb_colaborador.nome, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_colaborador ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_colaborador.nome LIKE :nome OR ";
    sql += "tb_colaborador.email LIKE :email ";
    sql += "ORDER BY tb_colaborador.nome ASC";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    QVector<Colaborador> listaColaborador;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":nome", "%" + nome_email + "%");
        query.bindValue(":email", "%" + nome_email + "%");

        if (query.exec())
        {
            if (query.next())
            {
                do
                {
                    grupo.setId(query.record().value("id_grupo").toInt());
                    grupo.setNome(query.record().value("nome_grupo").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    colaborador.setId(query.record().value("id").toInt());
                    colaborador.setNome(query.record().value("nome").toString());
                    colaborador.setEmail(query.record().value("email").toString());
                    colaborador.setSenha(query.record().value("senha").toString());
                    colaborador.setGrupo(grupo);
                    listaColaborador.push_back(colaborador);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "ColaboradorController::buscaPorNomeEmail()" << query.lastError().text();
        }
    }
    conn.close();
    return listaColaborador;
}

Colaborador ColaboradorController::autentica(Colaborador colaborador)
{
    sql = "SELECT ";
    sql += "tb_colaborador.id, ";
    sql += "tb_colaborador.nome, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_colaborador ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_colaborador.email = :email AND ";
    sql += "tb_colaborador.senha = :senha";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":email", colaborador.getEmail());
        query.bindValue(":senha", colaborador.getSenha());

        if (query.exec())
        {
            if (query.next())
            {
                grupo.setId(query.record().value("id_grupo").toInt());
                grupo.setNome(query.record().value("nome_grupo").toString());
                grupo.setSigla(query.record().value("sigla").toString());

                colaborador.setId(query.record().value("id").toInt());
                colaborador.setNome(query.record().value("nome").toString());
                // colaborador.setEmail(query.record().value("email").toString());
                // colaborador.setSenha(query.record().value("senha").toString());
                colaborador.setGrupo(grupo);
            }
            else
            {
                colaborador.setId(0);
            }
        }
        else
        {
            qDebug() << "ColaboradorController::autentica()" << query.lastError().text();
        }
    }
    conn.close();
    return colaborador;
}

bool ColaboradorController::buscaDuplicidadeEmail(QString email)
{
    sql = "SELECT id FROM tb_colaborador WHERE email = :email";

    if (!conn.isOpen())
    {
        conn.open();
    }

    bool retorno = false;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":email", email);

        if (query.exec())
        {
            if (query.next())
            {
                retorno = true;
            }
        }
        else
        {
            qDebug() << "ColaboradorController::buscaDuplicidadeEmail()" << query.lastError().text();
        }
    }
    conn.close();
    return retorno;
}

bool ColaboradorController::altera(Colaborador colaborador)
{
    sql = "UPDATE tb_colaborador SET ";
    sql += "nome = :nome, ";
    sql += "email = :email, ";
    sql += "senha = :senha, ";
    sql += "id_grupo = :id_grupo ";
    sql += "WHERE id = :id";

    if (!conn.isOpen())
    {
        conn.open();
    }

    bool retorno = false;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":nome", colaborador.getNome());
        query.bindValue(":email", colaborador.getEmail());
        query.bindValue(":senha", colaborador.getSenha());
        query.bindValue(":id_grupo", colaborador.getGrupo().getId());
        query.bindValue(":id", colaborador.getId());

        if (query.exec())
        {
            retorno = true;
        }
        else
            qDebug() << "ColaboradorController::altera()" << query.lastError().text();
    }
    conn.close();
    return retorno;
}
