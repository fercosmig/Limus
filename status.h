#ifndef STATUS_H
#define STATUS_H

#include <QString>

class Status
{
private:
    int id;
    QString nome;

public:
    Status();

    int getId() const;
    void setId(int newId);
    QString getNome() const;
    void setNome(const QString &newNome);
};

#endif // STATUS_H

/*
CREATE TABLE tb_status (
    id   INTEGER   PRIMARY KEY AUTOINCREMENT,
    nome TEXT (15) UNIQUE ON CONFLICT ROLLBACK NOT NULL ON CONFLICT ROLLBACK
);
INSERT INTO tb_status ( nome )
VALUES ( 'Quero ler' ), ( 'Lendo' ), ( 'Lido' );
*/
