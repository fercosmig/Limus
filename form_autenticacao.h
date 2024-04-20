#ifndef FORM_AUTENTICACAO_H
#define FORM_AUTENTICACAO_H

#include <QDialog>

namespace Ui {
class form_autenticacao;
}

class form_autenticacao : public QDialog
{
    Q_OBJECT

public:
    explicit form_autenticacao(QWidget *parent = nullptr);
    ~form_autenticacao();

    // MEUS MÉTODOS
    void inicializa_form_autenticacao();

private slots:
    void on_pushButton_autenticar_clicked();

    void on_pushButton_fechar_clicked();

private:
    Ui::form_autenticacao *ui;
};

#endif // FORM_AUTENTICACAO_H
