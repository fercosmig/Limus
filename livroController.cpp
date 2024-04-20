#include "livroController.h"

LivroController::LivroController() {}

Livro LivroController::insere(Livro livro)
{
    sql = "INSERT INTO tb_livro ";
    sql += "( nome, indice, pagina, id_serie, id_status, id_colaborador ) ";
    sql += "VALUES ";
    sql += "( :nome, :indice, :pagina, :id_serie, :id_status, :id_colaborador ) ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    if (conn.isOpen())
    {
        query.exec("BEGIN IMMEDIATE TRANSACTION");

        query.prepare(sql);
        query.bindValue(":nome", livro.getNome());
        query.bindValue(":indice", QString::number(livro.getIndice()));
        query.bindValue(":pagina", QString::number(livro.getPagina()));
        query.bindValue(":id_serie", QString::number(livro.getSerie().getId()));
        query.bindValue(":id_status", QString::number(livro.getStatus().getId()));
        query.bindValue(":id_colaborador", QString::number(livro.getColaborador().getId()));

        if (query.exec())
        {
            sql = "SELECT id FROM tb_livro ORDER BY id DESC LIMIT 1";
            query.prepare(sql);

            if (query.exec())
            {
                if (query.next())
                {
                    livro.setId(query.record().value("id").toInt());
                }
            }
            else
            {
                qDebug() << "LivroController::insere() query.exec(SELECT) " << query.lastError().text();
            }
        }
        else
        {
            qDebug() << "LivroController::insere() query.exec(INSERT) " << query.lastError().text();
        }

        query.exec("COMMIT");
    }
    conn.close();
    return livro;
}

QVector<Livro> LivroController::buscaPorColaborador(int id_colaborador)
{
    sql = "SELECT ";
    sql += "tb_livro.id, ";
    sql += "tb_livro.nome, ";
    sql += "tb_livro.indice, ";
    sql += "tb_livro.pagina, ";
    sql += "tb_serie.id AS id_serie, ";
    sql += "tb_serie.nome AS nome_serie, ";
    sql += "tb_status.id AS id_status, ";
    sql += "tb_status.nome AS nome_status, ";
    sql += "tb_colaborador.id AS id_colaborador, ";
    sql += "tb_colaborador.nome AS nome_colaborador, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_livro ";
    sql += "INNER JOIN tb_serie ";
    sql += "ON tb_livro.id_serie = tb_serie.id ";
    sql += "INNER JOIN tb_status ";
    sql += "ON tb_livro.id_status = tb_status.id ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_livro.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_livro.id_colaborador = :id_colaborador ";
    sql += "ORDER BY tb_serie.nome, tb_livro.indice, tb_livro.nome ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Status status;
    Serie serie;
    Livro livro;
    QVector<Livro> listaLivro;

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

                    status.setId(query.record().value("id_status").toInt());
                    status.setNome(query.record().value("nome_status").toString());

                    serie.setId(query.record().value("id_serie").toInt());
                    serie.setNome(query.record().value("nome_serie").toString());

                    livro.setId(query.record().value("id").toInt());
                    livro.setNome(query.record().value("nome").toString());
                    livro.setIndice(query.record().value("indice").toInt());
                    livro.setPagina(query.record().value("pagina").toInt());
                    livro.setSerie(serie);
                    livro.setStatus(status);
                    livro.setColaborador(colaborador);

                    listaLivro.push_back(livro);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "LivroController::buscaPorColaborador() query.exec() " << query.lastError().text();
        }
    }
    conn.close();
    return listaLivro;
}

QVector<Livro> LivroController::buscaPorColaboradorNome(int id_colaborador, QString nome)
{
    sql = "SELECT ";
    sql += "tb_livro.id, ";
    sql += "tb_livro.nome, ";
    sql += "tb_livro.indice, ";
    sql += "tb_livro.pagina, ";
    sql += "tb_serie.id AS id_serie, ";
    sql += "tb_serie.nome AS nome_serie, ";
    sql += "tb_status.id AS id_status, ";
    sql += "tb_status.nome AS nome_status, ";
    sql += "tb_colaborador.id AS id_colaborador, ";
    sql += "tb_colaborador.nome AS nome_colaborador, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_livro ";
    sql += "INNER JOIN tb_serie ";
    sql += "ON tb_livro.id_serie = tb_serie.id ";
    sql += "INNER JOIN tb_status ";
    sql += "ON tb_livro.id_status = tb_status.id ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_livro.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_livro.id_colaborador = :id_colaborador AND ";
    sql += "tb_livro.nome LIKE :nome ";
    sql += "ORDER BY tb_serie.nome, tb_livro.indice, tb_livro.nome ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Status status;
    Serie serie;
    Livro livro;
    QVector<Livro> listaLivro;

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

                    status.setId(query.record().value("id_status").toInt());
                    status.setNome(query.record().value("nome_status").toString());

                    serie.setId(query.record().value("id_serie").toInt());
                    serie.setNome(query.record().value("nome_serie").toString());

                    livro.setId(query.record().value("id").toInt());
                    livro.setNome(query.record().value("nome").toString());
                    livro.setIndice(query.record().value("indice").toInt());
                    livro.setPagina(query.record().value("pagina").toInt());
                    livro.setSerie(serie);
                    livro.setStatus(status);
                    livro.setColaborador(colaborador);

                    listaLivro.push_back(livro);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "LivroController::buscaPorColaboradorNome() query.exec() " << query.lastError().text();
        }
    }
    conn.close();
    return listaLivro;
}

QVector<Livro> LivroController::buscaPorColaboradorSerie(int id_colaborador, QString nome)
{
    sql = "SELECT ";
    sql += "tb_livro.id, ";
    sql += "tb_livro.nome, ";
    sql += "tb_livro.indice, ";
    sql += "tb_livro.pagina, ";
    sql += "tb_serie.id AS id_serie, ";
    sql += "tb_serie.nome AS nome_serie, ";
    sql += "tb_status.id AS id_status, ";
    sql += "tb_status.nome AS nome_status, ";
    sql += "tb_colaborador.id AS id_colaborador, ";
    sql += "tb_colaborador.nome AS nome_colaborador, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_livro ";
    sql += "INNER JOIN tb_serie ";
    sql += "ON tb_livro.id_serie = tb_serie.id ";
    sql += "INNER JOIN tb_status ";
    sql += "ON tb_livro.id_status = tb_status.id ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_livro.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_livro.id_colaborador = :id_colaborador AND ";
    sql += "tb_serie.nome LIKE :nome ";
    sql += "ORDER BY tb_serie.nome, tb_livro.indice, tb_livro.nome ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Status status;
    Serie serie;
    Livro livro;
    QVector<Livro> listaLivro;

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

                    status.setId(query.record().value("id_status").toInt());
                    status.setNome(query.record().value("nome_status").toString());

                    serie.setId(query.record().value("id_serie").toInt());
                    serie.setNome(query.record().value("nome_serie").toString());

                    livro.setId(query.record().value("id").toInt());
                    livro.setNome(query.record().value("nome").toString());
                    livro.setIndice(query.record().value("indice").toInt());
                    livro.setPagina(query.record().value("pagina").toInt());
                    livro.setSerie(serie);
                    livro.setStatus(status);
                    livro.setColaborador(colaborador);

                    listaLivro.push_back(livro);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "LivroController::buscaPorColaboradorSerie() query.exec() " << query.lastError().text();
        }
    }
    conn.close();
    return listaLivro;
}

bool LivroController::altera(Livro livro)
{
    sql = "UPDATE tb_livro SET ";
    sql += "nome = :nome, ";
    sql += "indice = :indice, ";
    sql += "pagina = :pagina, ";
    sql += "id_serie = :id_serie, ";
    sql += "id_status = :id_status ";
    sql += "WHERE id = :id ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    bool retorno = false;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":nome", livro.getNome());
        query.bindValue(":indice", QString::number(livro.getIndice()));
        query.bindValue(":pagina", QString::number(livro.getPagina()));
        query.bindValue(":id_serie", QString::number(livro.getSerie().getId()));
        query.bindValue(":id_status", QString::number(livro.getStatus().getId()));
        query.bindValue(":id", QString::number(livro.getId()));

        if (query.exec())
        {
            retorno = true;
        }
        else
        {
            qDebug() << "LivroController::altera() query.exec() " << query.lastError().text();
        }
    }
    conn.close();
    return retorno;
}
