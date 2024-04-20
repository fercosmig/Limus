#ifndef FORM_LIVRO_H
#define FORM_LIVRO_H

#include "autor.h"
#include "livro.h"

#include <QDialog>

namespace Ui {
class form_livro;
}

class form_livro : public QDialog
{
    Q_OBJECT

public:
    explicit form_livro(QWidget *parent = nullptr);
    ~form_livro();

    // MEUS MÉTODOS
    void inicializaFormLivro();
    void populaTableWidgetLivro(QVector<Livro> listaLivro);
    void atualizaTableWidgetLivro(QString nome);
    QString buscaAutoresString(int id_livro);
    void carregaComboBoxSerie();
    void carregaComboBoxStatus();
    void populaTableWidgetAutorTodos(QVector<Autor> listaAutor);
    void atualizaTableWidgetAutorTodos(int id_livro);
    void adicionaAutorTableWidgetAutorSelecionado(Autor autor);
    void adicionaAutorTableWidgetAutorTodos(Autor autor);
    void populaTableWidgetAutorSelecionado(QVector<Autor> ListaAutor);
    void atualizaTableWidgetAutorSelecionado(int id_livro);
    void limpaFormulario();
    Serie converteComboBoxSerie();
    Status converteComboBoxStatus();
    void adicionaLivroTableWidgetLivro(Livro livro);
    void alteraLivroTableWidgetLivro(Livro livro);

private slots:
    void on_pushButton_fechar_clicked();

    void on_comboBox_serie_currentIndexChanged(int index);

    void on_pushButton_adiciona_autor_clicked();

    void on_pushButton_remove_autor_clicked();

    void on_pushButton_limpar_clicked();

    void on_pushButton_pesquisar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_tableWidget_livro_itemSelectionChanged();

    void on_pushButton_incluir_clicked();

    void on_pushButton_alterar_clicked();

    void on_comboBox_status_currentIndexChanged(int index);

private:
    Ui::form_livro *ui;
};

#endif // FORM_LIVRO_H
