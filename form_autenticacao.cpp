#include "colaboradorController.h"
#include "form_autenticacao.h"
#include "global.h"
#include "ui_form_autenticacao.h"
#include <QMessageBox>

form_autenticacao::form_autenticacao(QWidget *parent) : QDialog(parent), ui(new Ui::form_autenticacao)
{
    ui->setupUi(this);

    form_autenticacao::inicializa_form_autenticacao();
}

form_autenticacao::~form_autenticacao()
{
    delete ui;
}

// MEUS MÉTODOS
void form_autenticacao::inicializa_form_autenticacao()
{
   ui->lineEdit_email->setFocus();
}

// SLOTS
void form_autenticacao::on_pushButton_autenticar_clicked()
{
    QString email, senha;
    Colaborador colaborador;
    ColaboradorController colaboradorController;

    email = ui->lineEdit_email->text().trimmed();
    senha = ui->lineEdit_senha->text().trimmed();

    if (!global::minimoCaracteres(email, 7))
    {
        QMessageBox::warning(this, "", "E-mail deve ter no mínimo 7 caracteres.");
        return;
    }

    if (!global::minimoCaracteres(senha , 3))
    {
        QMessageBox::warning(this, "", "Senha deve ter no mínimo 3 caracteres.");
        return;
    }

    colaborador.setEmail(email);
    colaborador.setSenha(senha);

    colaborador = colaboradorController.autentica(colaborador);
    if (colaborador.getId() > 0)
    {
        global::isLogged = true;
        global::colaboradorLogado = colaborador;
        close();
    }
    else
    {
        QMessageBox::warning(this, "", "Nome e/ou Senha inválidos!");
    }
}

void form_autenticacao::on_pushButton_fechar_clicked()
{
    close();
}
