#ifndef LIVROAUTOR_H
#define LIVROAUTOR_H

#include "autor.h"
#include "livro.h"


class LivroAutor
{
private:
    Livro livro;
    Autor autor;

public:
    LivroAutor();

    Livro getLivro() const;
    void setLivro(const Livro &newLivro);
    Autor getAutor() const;
    void setAutor(const Autor &newAutor);
};

#endif // LIVROAUTOR_H
