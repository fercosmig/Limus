#include "livroAutor.h"

LivroAutor::LivroAutor() {}

Livro LivroAutor::getLivro() const
{
    return livro;
}

void LivroAutor::setLivro(const Livro &newLivro)
{
    livro = newLivro;
}

Autor LivroAutor::getAutor() const
{
    return autor;
}

void LivroAutor::setAutor(const Autor &newAutor)
{
    autor = newAutor;
}
