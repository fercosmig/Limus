#ifndef FORM_BANDA_H
#define FORM_BANDA_H

#include "banda.h"

#include <QDialog>

namespace Ui {
class form_banda;
}

class form_banda : public QDialog
{
    Q_OBJECT

public:
    explicit form_banda(QWidget *parent = nullptr);
    ~form_banda();

    void inicializaFormBanda();
    void populaTableWidget(QVector<Banda> listaBanda);
    void atualizaTableWidget(QString nome);
    void limpaFormulario();
    void adicionaBandaTableWidget(Banda banda);
    void alteraBandaTableWidget(int row, Banda banda);

private slots:
    void on_pushButton_pesquisar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_tableWidget_banda_itemSelectionChanged();

    void on_pushButton_incluir_clicked();

    void on_pushButton_alterar_clicked();

    void on_pushButton_limpar_clicked();

    void on_pushButton_fechar_clicked();

private:
    Ui::form_banda *ui;
};

#endif // FORM_BANDA_H
