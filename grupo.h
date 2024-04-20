#ifndef GRUPO_H
#define GRUPO_H

#include <QString>

class Grupo
{
private:
    int id;
    QString nome;
    QString sigla;

public:
    Grupo();
    int getId() const;
    void setId(int newId);
    QString getNome() const;
    void setNome(const QString &newNome);
    QString getSigla() const;
    void setSigla(const QString &newSigla);
};

#endif // GRUPO_H
/*
CREATE TABLE tb_grupo (
    id    INTEGER   PRIMARY KEY AUTOINCREMENT,
    nome  TEXT (20) NOT NULL ON CONFLICT ROLLBACK,
    sigla TEXT (1)  UNIQUE ON CONFLICT ROLLBACK NOT NULL ON CONFLICT ROLLBACK
);
INSERT INTO tb_grupo ( nome, sigla ) VALUES
( 'Usuários', 'U' ), ( 'Administradores', 'A' );
*/
