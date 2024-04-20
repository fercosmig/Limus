#include "musicaController.h"

MusicaController::MusicaController() {}

Musica MusicaController::insere(Musica musica)
{
    sql = "INSERT INTO tb_musica ( nome, indice, id_album, id_colaborador ) ";
    sql += "VALUES ( :nome, :indice, :id_album, :id_colaborador ) ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    if (conn.isOpen())
    {
        query.exec("BEGIN IMMEDIATE TRANSACTION");

        query.prepare(sql);
        query.bindValue(":nome", musica.getNome());
        query.bindValue(":indice", QString::number(musica.getIndice()));
        query.bindValue(":id_album", QString::number(musica.getAlbum().getId()));
        query.bindValue(":id_colaborador", QString::number(musica.getColaborador().getId()));

        if (query.exec())
        {
            sql = "SELECT id FROM tb_musica ORDER BY id DESC LIMIT 1";
            query.prepare(sql);
            if (query.exec())
            {
                if (query.next())
                {
                    musica.setId(query.record().value("id").toInt());
                }
            }
            else
            {
                qDebug() << "MusicaController::insere() query.exec(SELECT)" << query.lastError().text();
            }
        }
        else
        {
            qDebug() << "MusicaController::insere() query.exec(INSERT)" << query.lastError().text();
        }

        query.exec("COMMIT");
    }
    conn.close();
    return musica;
}

QVector<Musica> MusicaController::buscaPorColaborador(int id_colaborador)
{
    sql = "SELECT ";
    sql += "tb_musica.id, ";
    sql += "tb_musica.nome, ";
    sql += "tb_musica.indice, ";
    sql += "tb_album.id AS id_album, ";
    sql += "tb_album.nome AS nome_album, ";
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
    sql += "FROM ";
    sql += "tb_musica ";
    sql += "INNER JOIN tb_album ";
    sql += "ON tb_musica.id_album = tb_album.id ";
    sql += "INNER JOIN tb_banda ";
    sql += "ON tb_album.id_banda = tb_banda.id ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_musica.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_musica.id_colaborador = :id AND ";
    sql += "tb_album.id_colaborador = :id AND ";
    sql += "tb_banda.id_colaborador = :id ";
    sql += "ORDER BY tb_banda.nome, tb_album.ano, tb_musica.indice ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Banda banda;
    Album album;
    Musica musica;
    QVector<Musica> listaMusica;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":id", QString::number(id_colaborador));

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

                    album.setId(query.record().value("id_album").toInt());
                    album.setNome(query.record().value("nome_album").toString());
                    album.setAno(query.record().value("ano").toInt());
                    album.setBanda(banda);
                    album.setColaborador(colaborador);

                    musica.setId(query.record().value("id").toInt());
                    musica.setNome(query.record().value("nome").toString());
                    musica.setIndice(query.record().value("indice").toInt());
                    musica.setAlbum(album);
                    musica.setColaborador(colaborador);

                    listaMusica.push_back(musica);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "MusicaController::buscaPorColaborador() query.exec()" << query.lastError().text();
        }
    }
    conn.close();
    return listaMusica;
}

QVector<Musica> MusicaController::buscaPorColaboradorMusica(int id_colaborador, QString nome)
{
    sql = "SELECT ";
    sql += "tb_musica.id, ";
    sql += "tb_musica.nome, ";
    sql += "tb_musica.indice, ";
    sql += "tb_album.id AS id_album, ";
    sql += "tb_album.nome AS nome_album, ";
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
    sql += "FROM ";
    sql += "tb_musica ";
    sql += "INNER JOIN tb_album ";
    sql += "ON tb_musica.id_album = tb_album.id ";
    sql += "INNER JOIN tb_banda ";
    sql += "ON tb_album.id_banda = tb_banda.id ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_musica.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_musica.id_colaborador = :id AND ";
    sql += "tb_album.id_colaborador = :id AND ";
    sql += "tb_banda.id_colaborador = :id AND ";
    sql += "tb_musica.nome LIKE :nome ";
    sql += "ORDER BY tb_banda.nome, tb_album.ano, tb_musica.indice ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Banda banda;
    Album album;
    Musica musica;
    QVector<Musica> listaMusica;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":id", QString::number(id_colaborador));
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

                    album.setId(query.record().value("id_album").toInt());
                    album.setNome(query.record().value("nome_album").toString());
                    album.setAno(query.record().value("ano").toInt());
                    album.setBanda(banda);
                    album.setColaborador(colaborador);

                    musica.setId(query.record().value("id").toInt());
                    musica.setNome(query.record().value("nome").toString());
                    musica.setIndice(query.record().value("indice").toInt());
                    musica.setAlbum(album);
                    musica.setColaborador(colaborador);

                    listaMusica.push_back(musica);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "MusicaController::buscaPorColaboradorMusica() query.exec()" << query.lastError().text();
        }
    }
    conn.close();
    return listaMusica;
}

QVector<Musica> MusicaController::buscaPorColaboradorAlbum(int id_colaborador, QString nome)
{
    sql = "SELECT ";
    sql += "tb_musica.id, ";
    sql += "tb_musica.nome, ";
    sql += "tb_musica.indice, ";
    sql += "tb_album.id AS id_album, ";
    sql += "tb_album.nome AS nome_album, ";
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
    sql += "FROM ";
    sql += "tb_musica ";
    sql += "INNER JOIN tb_album ";
    sql += "ON tb_musica.id_album = tb_album.id ";
    sql += "INNER JOIN tb_banda ";
    sql += "ON tb_album.id_banda = tb_banda.id ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_musica.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_musica.id_colaborador = :id AND ";
    sql += "tb_album.id_colaborador = :id AND ";
    sql += "tb_banda.id_colaborador = :id AND ";
    sql += "tb_album.nome LIKE :nome ";
    sql += "ORDER BY tb_banda.nome, tb_album.ano, tb_musica.indice ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Banda banda;
    Album album;
    Musica musica;
    QVector<Musica> listaMusica;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":id", QString::number(id_colaborador));
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

                    album.setId(query.record().value("id_album").toInt());
                    album.setNome(query.record().value("nome_album").toString());
                    album.setAno(query.record().value("ano").toInt());
                    album.setBanda(banda);
                    album.setColaborador(colaborador);

                    musica.setId(query.record().value("id").toInt());
                    musica.setNome(query.record().value("nome").toString());
                    musica.setIndice(query.record().value("indice").toInt());
                    musica.setAlbum(album);
                    musica.setColaborador(colaborador);

                    listaMusica.push_back(musica);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "MusicaController::buscaPorColaboradorAlbum() query.exec()" << query.lastError().text();
        }
    }
    conn.close();
    return listaMusica;
}

QVector<Musica> MusicaController::buscaPorColaboradorBanda(int id_colaborador, QString nome)
{
    sql = "SELECT ";
    sql += "tb_musica.id, ";
    sql += "tb_musica.nome, ";
    sql += "tb_musica.indice, ";
    sql += "tb_album.id AS id_album, ";
    sql += "tb_album.nome AS nome_album, ";
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
    sql += "FROM ";
    sql += "tb_musica ";
    sql += "INNER JOIN tb_album ";
    sql += "ON tb_musica.id_album = tb_album.id ";
    sql += "INNER JOIN tb_banda ";
    sql += "ON tb_album.id_banda = tb_banda.id ";
    sql += "INNER JOIN tb_colaborador ";
    sql += "ON tb_musica.id_colaborador = tb_colaborador.id ";
    sql += "INNER JOIN tb_grupo ";
    sql += "ON tb_colaborador.id_grupo = tb_grupo.id ";
    sql += "WHERE ";
    sql += "tb_musica.id_colaborador = :id AND ";
    sql += "tb_album.id_colaborador = :id AND ";
    sql += "tb_banda.id_colaborador = :id AND ";
    sql += "tb_banda.nome LIKE :nome ";
    sql += "ORDER BY tb_banda.nome, tb_album.ano, tb_musica.indice ASC ";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    Colaborador colaborador;
    Banda banda;
    Album album;
    Musica musica;
    QVector<Musica> listaMusica;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":id", QString::number(id_colaborador));
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

                    album.setId(query.record().value("id_album").toInt());
                    album.setNome(query.record().value("nome_album").toString());
                    album.setAno(query.record().value("ano").toInt());
                    album.setBanda(banda);
                    album.setColaborador(colaborador);

                    musica.setId(query.record().value("id").toInt());
                    musica.setNome(query.record().value("nome").toString());
                    musica.setIndice(query.record().value("indice").toInt());
                    musica.setAlbum(album);
                    musica.setColaborador(colaborador);

                    listaMusica.push_back(musica);
                }
                while (query.next());
            }
        }
        else
        {
            qDebug() << "MusicaController::buscaPorColaboradorBanda() query.exec()" << query.lastError().text();
        }
    }
    conn.close();
    return listaMusica;
}

bool MusicaController::altera(Musica musica)
{
    sql = "UPDATE tb_musica SET ";
    sql += "nome = :nome, ";
    sql += "indice = :indice, ";
    sql += "id_album = :id_album ";
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
        query.bindValue(":nome", musica.getNome());
        query.bindValue(":indice", QString::number(musica.getIndice()));
        query.bindValue(":id_album", QString::number(musica.getAlbum().getId()));
        query.bindValue(":id", QString::number(musica.getId()));

        if (query.exec())
        {
            retorno = true;
        }
        else
        {
            qDebug() << "MusicaController::altera() query.exec()" << query.lastError().text();
        }
    }
    conn.close();
    return retorno;
}
