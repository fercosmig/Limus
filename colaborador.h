#ifndef COLABORADOR_H
#define COLABORADOR_H

#include "grupo.h"

class Colaborador
{
private:
    int id;
    QString nome;
    QString email;
    QString senha;
    Grupo grupo;

public:
    Colaborador();

    int getId() const;
    void setId(int newId);
    QString getNome() const;
    void setNome(const QString &newNome);
    QString getEmail() const;
    void setEmail(const QString &newEmail);
    QString getSenha() const;
    void setSenha(const QString &newSenha);
    Grupo getGrupo() const;
    void setGrupo(const Grupo &newGrupo);
};

#endif // COLABORADOR_H

/*
CREATE TABLE tb_colaborador (
    id       INTEGER   PRIMARY KEY AUTOINCREMENT,
    nome     TEXT (30) NOT NULL ON CONFLICT ROLLBACK,
    email    TEXT (30) NOT NULL ON CONFLICT ROLLBACK UNIQUE ON CONFLICT ROLLBACK,
    senha    TEXT (30) NOT NULL ON CONFLICT ROLLBACK,
    id_grupo INTEGER   REFERENCES tb_grupo (id) ON DELETE CASCADE NOT NULL ON CONFLICT ROLLBACK
);
INSERT INTO tb_colaborador ( nome, email, senha, id_grupo ) VALUES
( 'Usuário Teste', 'teste@u.com', '123', 1 ), ( 'Administrador Teste', 'teste@a.com', '123', 2 );
*/
