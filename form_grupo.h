#ifndef FORM_GRUPO_H
#define FORM_GRUPO_H

#include "grupo.h"

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
class form_grupo;
}

class form_grupo : public QDialog
{
    Q_OBJECT

public:
    explicit form_grupo(QWidget *parent = nullptr);
    ~form_grupo();

    // MEUS MÉTODOS
    void inicializa_form_grupo();
    void popula_table_widget(QVector<Grupo> listaGrupo);
    void atualiza_table_widget(QString nome);
    void limpa_formulario();
    void carrega_comboBox_sigla();
    void adiciona_grupo_table_widget(Grupo grupo);
    void altera_grupo_table_widget(int row, Grupo grupo);

private slots:
    void on_pushButton_pesquisar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_tableWidget_grupo_itemSelectionChanged();

    void on_pushButton_limpar_clicked();

    void on_pushButton_fechar_clicked();

    void on_pushButton_incluir_clicked();

    void on_pushButton_alterar_clicked();

private:
    Ui::form_grupo *ui;
};

#endif // FORM_GRUPO_H
