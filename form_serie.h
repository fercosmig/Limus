#ifndef FORM_SERIE_H
#define FORM_SERIE_H

#include "serie.h"

#include <QDialog>

namespace Ui {
class form_serie;
}

class form_serie : public QDialog
{
    Q_OBJECT

public:
    explicit form_serie(QWidget *parent = nullptr);
    ~form_serie();

    // MEUS MÉTODOS
    void inicializa_form_serie();
    void popula_table_widget(QVector<Serie> listaSerie);
    void atualiza_table_widget(QString nome);
    void limpa_formulario();
    void adiciona_serie_table_widget(Serie serie);
    void altera_serie_table_widget(int row, Serie serie);

private slots:
    void on_pushButton_pesquisar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_tableWidget_serie_itemSelectionChanged();

    void on_pushButton_incluir_clicked();

    void on_pushButton_alterar_clicked();

    void on_pushButton_limpar_clicked();

    void on_pushButton_fechar_clicked();

private:
    Ui::form_serie *ui;
};

#endif // FORM_SERIE_H
