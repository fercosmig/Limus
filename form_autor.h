#ifndef FORM_AUTOR_H
#define FORM_AUTOR_H

#include "autor.h"

#include <QDialog>

namespace Ui {
class form_autor;
}

class form_autor : public QDialog
{
    Q_OBJECT

public:
    explicit form_autor(QWidget *parent = nullptr);
    ~form_autor();

    // MEUS MÉTODOS
    void inicializa_form_autor();
    void popula_table_widget(QVector<Autor> listaAutor);
    void atualiza_table_widget(QString nome);
    void limpa_formulario();
    void adiciona_autor_table_widget(Autor autor);
    void altera_autor_table_widget(int row, Autor autor);


private slots:
    void on_pushButton_pesquisar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_tableWidget_autor_itemSelectionChanged();

    void on_pushButton_incluir_clicked();

    void on_pushButton_alterar_clicked();

    void on_pushButton_limpar_clicked();

    void on_pushButton_fechar_clicked();

private:
    Ui::form_autor *ui;
};

#endif // FORM_AUTOR_H
