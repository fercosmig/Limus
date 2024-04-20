#include "livroAutorController.h"

LivroAutorController::LivroAutorController() {}

bool LivroAutorController::insere(LivroAutor livroAutor)
{
    sql = "INSERT INTO tb_livro_autor ";
    sql += "( id_livro, id_autor ) ";
    sql += "VALUES  ";
    sql += "( :id_livro, :id_autor ) ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    bool retorno = false;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":id_livro", QString::number(livroAutor.getLivro().getId()));
        query.bindValue(":id_autor", QString::number(livroAutor.getAutor().getId()));

        if (query.exec())
        {
            retorno = true;
        }
        else
        {
            qDebug() << "LivroAutorController::insere() query.exec() " << query.lastError().text();
        }
    }
    conn.close();
    return retorno;
}

bool LivroAutorController::buscaRelacionamentoDuplicado(LivroAutor livroAutor)
{
    sql = "SELECT ";
    sql += "id_livro, ";
    sql += "id_autor ";
    sql += "FROM tb_livro_autor ";
    sql += "WHERE ";
    sql += "id_livro = :id_livro AND ";
    sql += "id_autor = :id_autor ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    bool retorno = false;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":id_livro", QString::number(livroAutor.getLivro().getId()));
        query.bindValue(":id_autor", QString::number(livroAutor.getAutor().getId()));

        if (query.exec())
        {
            if (query.next())
            {
                retorno = true;
            }
        }
        else
        {
            qDebug() << "LivroAutorController::buscaRelacionamentoDuplicado() query.exec() " << query.lastError().text();
        }
    }
    conn.close();
    return retorno;
}

QVector<Autor> LivroAutorController::buscaAutorPorIdLivro(int id_livro)
{
    sql = "SELECT ";
    sql += "tb_autor.id, ";
    sql += "tb_autor.nome ";
    sql += "FROM tb_autor ";
    sql += "INNER JOIN tb_livro_autor ";
    sql += "ON tb_autor.id = tb_livro_autor.id_autor ";
    sql += "WHERE ";
    sql += "tb_livro_autor.id_livro = :id_livro ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Autor autor;
    QVector<Autor> listaAutor;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":id_livro", id_livro);

        if (query.exec())
        {
            if (query.next())
            {
                do
                {
                    autor.setId(query.record().value("id").toInt());
                    autor.setNome(query.record().value("nome").toString());

                    listaAutor.push_back(autor);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "LivroAutorController::buscaAutorPorIdLivro() query.exec() " << query.lastError().text();
        }
    }
    conn.close();
    return listaAutor;
}

QVector<Livro> LivroAutorController::buscaLivroPorNomeAutor(int id_colaborador, QString nome)
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
    sql += "INNER JOIN tb_livro_autor ";
    sql += "ON tb_livro.id = tb_livro_autor.id_livro ";
    sql += "INNER JOIN tb_autor ";
    sql += "ON tb_livro_autor.id_autor = tb_autor.id ";
    sql += "WHERE ";
    sql += "tb_livro.id_colaborador = :id_colaborador AND ";
    sql += "tb_autor.nome LIKE :nome ";
    sql += "ORDER BY tb_serie.nome, tb_livro.indice, tb_livro.nome ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Livro livro;
    Status status;
    Serie serie;
    Colaborador colaborador;
    Grupo grupo;
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
            qDebug() << "LivroAutorController::buscaLivroPorNomeAutor() query.exec() " << query.lastError().text();
        }
    }
    conn.close();
    return listaLivro;
}

QVector<Autor> LivroAutorController::buscaAutorNaoSelecionado(int id_colaborador, int id_livro)
{
    sql = "SELECT ";
    sql += "tb_autor.id, ";
    sql += "tb_autor.nome ";
    sql += "FROM tb_autor ";
    sql += "WHERE ";
    sql += "tb_autor.id_colaborador = :id_colaborador AND ";
    sql += "tb_autor.id NOT IN ";
    sql += "( ";
    sql += "SELECT ";
    sql += "id_autor ";
    sql += "FROM ";
    sql += "tb_livro_autor ";
    sql += "WHERE ";
    sql += "tb_livro_autor.id_livro = :id_livro ";
    sql += ") ";
    sql += "ORDER BY tb_autor.nome ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Autor autor;
    QVector<Autor> listaAutor;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":id_colaborador", id_colaborador);
        query.bindValue(":id_livro", id_livro);

        if (query.exec())
        {
            if (query.next())
            {
                do
                {
                    autor.setId(query.record().value("id").toInt());
                    autor.setNome(query.record().value("nome").toString());

                    listaAutor.push_back(autor);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "LivroAutorController::buscaAutorNaoSelecionado() query.exec() " << query.lastError().text();
        }
    }
    conn.close();
    return listaAutor;
}

bool LivroAutorController::remove(int id_livro)
{
    sql = "DELETE FROM tb_livro_autor ";
    sql += "WHERE ";
    sql += "id_livro = :id_livro ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    bool retorno = false;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":id_livro", QString::number(id_livro));

        if (query.exec())
        {
            retorno = true;
        }
        else
        {
            qDebug() << "LivroAutorController::remove() query.exec() " << query.lastError().text();
        }
    }
    conn.close();
    return retorno;
}
