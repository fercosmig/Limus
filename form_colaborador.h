#ifndef FORM_COLABORADOR_H
#define FORM_COLABORADOR_H

#include "colaborador.h"

#include <QDialog>

namespace Ui {
class form_colaborador;
}

class form_colaborador : public QDialog
{
    Q_OBJECT

public:
    explicit form_colaborador(QWidget *parent = nullptr);
    ~form_colaborador();

    // MEUS MÉTODOS
    void inicializaFormColaborador();
    void populaTableWidget(QVector<Colaborador> listaColaborador);
    void atualizaTableWidget(QString nome_email);
    void limpaFormulario();
    void carregaComboBoxGrupo();
    void adicionaColaboradorTableWidget(Colaborador colaborador);
    void alteraColaboradorTableWidget(int row, Colaborador colaborador);
    Grupo converteComboBoxGrupo();

private slots:
    void on_pushButton_pesquisar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_tableWidget_colaborador_itemSelectionChanged();

    void on_pushButton_incluir_clicked();

    void on_pushButton_alterar_clicked();

    void on_pushButton_limpar_clicked();

    void on_pushButton_fechar_clicked();

private:
    Ui::form_colaborador *ui;
};

#endif // FORM_COLABORADOR_H
