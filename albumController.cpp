#include "albumController.h"

AlbumController::AlbumController() {}

Album AlbumController::insere(Album album)
{
    sql = "INSERT INTO tb_album ( nome, ano, id_banda, id_colaborador ) ";
    sql += "VALUES ( :nome, :ano, :id_banda, :id_colaborador ) ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    if (conn.isOpen())
    {
        query.exec("BEGIN IMMEDIATE TRANSACTION");

        query.prepare(sql);
        query.bindValue(":nome", album.getNome());
        query.bindValue(":ano", QString::number(album.getAno()));
        query.bindValue(":id_banda", QString::number(album.getBanda().getId()));
        query.bindValue(":id_colaborador", QString::number(album.getColaborador().getId()));

        if (query.exec())
        {
            sql = "SELECT id FROM tb_album ORDER BY id DESC LIMIT 1";
            query.prepare(sql);
            if (query.exec())
            {
                if (query.next())
                {
                    album.setId(query.record().value("id").toInt());
                }
            }
            else
            {
                qDebug() << "AlbumController::insere() query.exec(SELECT)" << query.lastError().text();
            }
        }
        else
        {
            qDebug() << "AlbumController::insere() query.exec(INSERT)" << query.lastError().text();
        }

        query.exec("COMMIT");
    }
    conn.close();
    return album;
}

Album AlbumController::buscaPorId(int id)
{
    sql = "SELECT ";
    sql += "tb_album.id, ";
    sql += "tb_album.nome, ";
    sql += "tb_album.ano, ";
    sql += "tb_banda.id AS id_banda, ";
    sql += "tb_banda.nome AS nome_banda, ";
    sql += "tb_colaborador.id AS id_colaborador, ";
    sql += "tb_colaborador.nome AS nome_colaborador, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_album ";
    sql += "INNER JOIN tb_banda ";
    sql += "ON tb_album.id_banda = tb_banda.id ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_banda.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_album.id = :id ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Banda banda;
    Album album;

    if (conn.isOpen()){

        query.prepare(sql);
        query.bindValue(":id", id);

        if (query.exec())
        {
            if (query.next())
            {
                grupo.setId(query.record().value("id_grupo").toInt());
                grupo.setNome(query.record().value("nome_grupo").toString());
                grupo.setSigla(query.record().value("sigla").toString());

                colaborador.setId(query.record().value("id_colaborador").toInt());
                colaborador.setNome(query.record().value("nome_colaborador").toString());
                colaborador.setEmail(query.record().value("email").toString());
                colaborador.setSenha(query.record().value("senha").toString());
                colaborador.setGrupo(grupo);

                banda.setId(query.record().value("id_banda").toInt());
                banda.setNome(query.record().value("nome_banda").toString());
                banda.setColaborador(colaborador);

                album.setId(query.record().value("id").toInt());
                album.setNome(query.record().value("nome").toString());
                album.setAno(query.record().value("ano").toInt());
                album.setBanda(banda);
                album.setColaborador(colaborador);
            }
        }
        else
        {
            qDebug() << "AlbumController::buscaPorId() query.exec()" << query.lastError().text();
        }
    }
    conn.close();
    return album;
}

QVector<Album> AlbumController::buscaPorIdBanda(int id_banda)
{
    sql = "SELECT ";
    sql += "tb_album.id, ";
    sql += "tb_album.nome, ";
    sql += "tb_album.ano, ";
    sql += "tb_banda.id AS id_banda, ";
    sql += "tb_banda.nome AS nome_banda, ";
    sql += "tb_colaborador.id AS id_colaborador, ";
    sql += "tb_colaborador.nome AS nome_colaborador, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_album ";
    sql += "INNER JOIN tb_banda ";
    sql += "ON tb_album.id_banda = tb_banda.id ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_banda.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_album.id_banda = :id_banda ";
    sql += "ORDER BY tb_album.ano ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Banda banda;
    Album album;
    QVector<Album> listaAlbum;

    if (conn.isOpen()){

        query.prepare(sql);
        query.bindValue(":id_banda", id_banda);

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

                    banda.setId(query.record().value("id_banda").toInt());
                    banda.setNome(query.record().value("nome_banda").toString());
                    banda.setColaborador(colaborador);

                    album.setId(query.record().value("id").toInt());
                    album.setNome(query.record().value("nome").toString());
                    album.setAno(query.record().value("ano").toInt());
                    album.setBanda(banda);
                    album.setColaborador(colaborador);

                    listaAlbum.push_back(album);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "AlbumController::buscaPorIdBanda() query.exec()" << query.lastError().text();
        }
    }
    conn.close();
    return listaAlbum;
}

QVector<Album> AlbumController::buscaPorColaborador(int id_colaborador)
{
    sql = "SELECT ";
    sql += "tb_album.id, ";
    sql += "tb_album.nome, ";
    sql += "tb_album.ano, ";
    sql += "tb_banda.id AS id_banda, ";
    sql += "tb_banda.nome AS nome_banda, ";
    sql += "tb_colaborador.id AS id_colaborador, ";
    sql += "tb_colaborador.nome AS nome_colaborador, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_album ";
    sql += "INNER JOIN tb_banda ";
    sql += "ON tb_album.id_banda = tb_banda.id ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_banda.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_colaborador.id = :id_colaborador ";
    sql += "ORDER BY tb_banda.nome, tb_album.ano ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Banda banda;
    Album album;
    QVector<Album> listaAlbum;

    if (conn.isOpen()){

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

                    banda.setId(query.record().value("id_banda").toInt());
                    banda.setNome(query.record().value("nome_banda").toString());
                    banda.setColaborador(colaborador);

                    album.setId(query.record().value("id").toInt());
                    album.setNome(query.record().value("nome").toString());
                    album.setAno(query.record().value("ano").toInt());
                    album.setBanda(banda);
                    album.setColaborador(colaborador);

                    listaAlbum.push_back(album);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "AlbumController::buscaPorColaborador() query.exec()" << query.lastError().text();
        }
    }
    conn.close();
    return listaAlbum;
}

QVector<Album> AlbumController::buscaPorColaboradorNome(int id_colaborador, QString nome)
{
    sql = "SELECT ";
    sql += "tb_album.id, ";
    sql += "tb_album.nome, ";
    sql += "tb_album.ano, ";
    sql += "tb_banda.id AS id_banda, ";
    sql += "tb_banda.nome AS nome_banda, ";
    sql += "tb_colaborador.id AS id_colaborador, ";
    sql += "tb_colaborador.nome AS nome_colaborador, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_album ";
    sql += "INNER JOIN tb_banda ";
    sql += "ON tb_album.id_banda = tb_banda.id ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_banda.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_colaborador.id = :id_colaborador AND ";
    sql += "tb_album.nome LIKE :nome ";
    sql += "ORDER BY tb_banda.nome, tb_album.ano ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Banda banda;
    Album album;
    QVector<Album> listaAlbum;

    if (conn.isOpen()){

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

                    banda.setId(query.record().value("id_banda").toInt());
                    banda.setNome(query.record().value("nome_banda").toString());
                    banda.setColaborador(colaborador);

                    album.setId(query.record().value("id").toInt());
                    album.setNome(query.record().value("nome").toString());
                    album.setAno(query.record().value("ano").toInt());
                    album.setBanda(banda);
                    album.setColaborador(colaborador);

                    listaAlbum.push_back(album);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "AlbumController::buscaPorColaboradorNome() query.exec()" << query.lastError().text();
        }
    }
    conn.close();
    return listaAlbum;
}

QVector<Album> AlbumController::buscaPorColaboradorAno(int id_colaborador, int ano)
{
    sql = "SELECT ";
    sql += "tb_album.id, ";
    sql += "tb_album.nome, ";
    sql += "tb_album.ano, ";
    sql += "tb_banda.id AS id_banda, ";
    sql += "tb_banda.nome AS nome_banda, ";
    sql += "tb_colaborador.id AS id_colaborador, ";
    sql += "tb_colaborador.nome AS nome_colaborador, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_album ";
    sql += "INNER JOIN tb_banda ";
    sql += "ON tb_album.id_banda = tb_banda.id ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_banda.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_colaborador.id = :id_colaborador AND ";
    sql += "tb_album.ano = :ano ";
    sql += "ORDER BY tb_banda.nome, tb_album.ano ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Banda banda;
    Album album;
    QVector<Album> listaAlbum;

    if (conn.isOpen()){

        query.prepare(sql);
        query.bindValue(":id_colaborador", id_colaborador);
        query.bindValue(":ano", ano);

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

                    banda.setId(query.record().value("id_banda").toInt());
                    banda.setNome(query.record().value("nome_banda").toString());
                    banda.setColaborador(colaborador);

                    album.setId(query.record().value("id").toInt());
                    album.setNome(query.record().value("nome").toString());
                    album.setAno(query.record().value("ano").toInt());
                    album.setBanda(banda);
                    album.setColaborador(colaborador);

                    listaAlbum.push_back(album);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "AlbumController::buscaPorColaboradorAno() query.exec()" << query.lastError().text();
        }
    }
    conn.close();
    return listaAlbum;
}

QVector<Album> AlbumController::buscaPorColaboradorBanda(int id_colaborador, QString nome)
{
    sql = "SELECT ";
    sql += "tb_album.id, ";
    sql += "tb_album.nome, ";
    sql += "tb_album.ano, ";
    sql += "tb_banda.id AS id_banda, ";
    sql += "tb_banda.nome AS nome_banda, ";
    sql += "tb_colaborador.id AS id_colaborador, ";
    sql += "tb_colaborador.nome AS nome_colaborador, ";
    sql += "tb_colaborador.email, ";
    sql += "tb_colaborador.senha, ";
    sql += "tb_grupo.id AS id_grupo, ";
    sql += "tb_grupo.nome AS nome_grupo, ";
    sql += "tb_grupo.sigla ";
    sql += "FROM tb_album ";
    sql += "INNER JOIN tb_banda ";
    sql += "ON tb_album.id_banda = tb_banda.id ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_banda.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_colaborador.id = :id_colaborador AND ";
    sql += "tb_banda.nome LIKE :nome ";
    sql += "ORDER BY tb_banda.nome, tb_album.ano ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Banda banda;
    Album album;
    QVector<Album> listaAlbum;

    if (conn.isOpen()){

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

                    banda.setId(query.record().value("id_banda").toInt());
                    banda.setNome(query.record().value("nome_banda").toString());
                    banda.setColaborador(colaborador);

                    album.setId(query.record().value("id").toInt());
                    album.setNome(query.record().value("nome").toString());
                    album.setAno(query.record().value("ano").toInt());
                    album.setBanda(banda);
                    album.setColaborador(colaborador);

                    listaAlbum.push_back(album);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "AlbumController::buscaPorColaboradorBanda() query.exec()" << query.lastError().text();
        }
    }
    conn.close();
    return listaAlbum;
}

bool AlbumController::altera(Album album)
{
    sql = "UPDATE tb_album SET ";
    sql += "nome = :nome, ";
    sql += "ano = :ano, ";
    sql += "id_banda = :id_banda ";
    sql += "WHERE id = :id ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    bool retorno = false;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":nome", album.getNome());
        query.bindValue(":ano", QString::number(album.getAno()));
        query.bindValue(":id_banda", QString::number(album.getBanda().getId()));
        query.bindValue(":id", QString::number(album.getId()));

        if (query.exec())
        {
            retorno = true;
        }
        else
        {
            qDebug() << "AlbumController::altera() query.exec()" << query.lastError().text();
        }
    }
    conn.close();
    return retorno;
}
