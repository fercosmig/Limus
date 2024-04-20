#include "form_album.h"
#include "form_autenticacao.h"
#include "form_autor.h"
#include "form_banda.h"
#include "form_colaborador.h"
#include "form_grupo.h"
#include "form_livro.h"
#include "form_musica.h"
#include "form_principal.h"
#include "form_serie.h"
#include "global.h"
#include "ui_form_principal.h"
#include <QMessageBox>

form_principal::form_principal(QWidget *parent) : QMainWindow(parent), ui(new Ui::form_principal)
{
    ui->setupUi(this);

    form_principal::inicializa_form_principal();
}

form_principal::~form_principal()
{
    delete ui;
}

// MEUS MÉTODOS
void form_principal::inicializa_form_principal()
{
    global::inicializaVariaveisGlobais();

    ui->pushButton_autenticacao->setText("");
    ui->label_autenticado->setText("Autentique-se!");

    ui->statusbar->addWidget(ui->pushButton_autenticacao);
    ui->statusbar->addWidget(ui->label_autenticado);

    form_principal::cadeadoFechado.addFile(":/imagens/imagens/fechado.png");
    form_principal::cadeadoAberto.addFile(":/imagens/imagens/aberto.png");

    form_principal::configura_imagens();
    form_principal::configura_autencicacao();
}

void form_principal::configura_imagens()
{
    QPixmap livros(":/imagens/imagens/livros.png");
    QPixmap musicas(":/imagens/imagens/musicas.png");

    ui->label_livros_image->setPixmap(livros.scaled(150, 150, Qt::KeepAspectRatio));
    ui->label_musicas_image->setPixmap(musicas.scaled(150, 150, Qt::KeepAspectRatio));
}

void form_principal::configura_autencicacao()
{
    QString colaboradorLogado;
    if (global::isLogged)
    {
        colaboradorLogado = global::colaboradorLogado.getGrupo().getSigla() + "|" + global::colaboradorLogado.getNome();
        ui->pushButton_autenticacao->setIcon(form_principal::cadeadoAberto);
        ui->label_autenticado->setText(colaboradorLogado);
        ui->label_bem_vindo->setText("Olá " + global::colaboradorLogado.getNome() + ", seja bem vindo!");
    }
    else
    {
        ui->pushButton_autenticacao->setIcon(form_principal::cadeadoFechado);
        ui->label_autenticado->setText("Autentique-se!");
        ui->label_bem_vindo->setText("Bem vindo!");
    }
}

// SLOTS
void form_principal::on_pushButton_autenticacao_clicked()
{
    form_autenticacao f_autenticacao;
    if (global::isLogged)
    {
        global::isLogged = false;
    }
    else
    {
        f_autenticacao.exec();
    }
    form_principal::configura_autencicacao();
}

void form_principal::on_pushButton_fechar_clicked()
{
    QApplication::quit();
}

void form_principal::on_actionGrupos_triggered()
{
    form_grupo f_grupo;
    if (global::isLogged)
    {
        if (global::colaboradorLogado.getGrupo().getSigla() == "A")
        {
            f_grupo.exec();
        }
        else
        {
            QMessageBox::warning(this, "", "Sem permissão de acesso!");
        }
    }
    else
    {
        QMessageBox::warning(this, "", "Autentique-se!");
    }
}

void form_principal::on_actionColaboradores_triggered()
{
    form_colaborador f_colaborador;
    if (global::isLogged)
    {
        if (global::colaboradorLogado.getGrupo().getSigla() == "A")
        {
            f_colaborador.exec();
        }
        else
        {
            QMessageBox::warning(this, "", "Sem permissão de acesso!");
        }
    }
    else
    {
        QMessageBox::warning(this, "", "Autentique-se!");
    }
}

void form_principal::on_actionSair_triggered()
{
    QApplication::quit();
}

void form_principal::on_actionSobre_triggered()
{
    QString mensagem;

    mensagem = "Limus :: Livros e Músicas";
    mensagem += "\n";
    mensagem += "Desenvolvido por Fernando Costa Migliorini";
    mensagem += "\n";
    mensagem += "Desenvolvido entre: 09/04/2024 e 20/04/2024";
    mensagem += "\n";
    mensagem += "Versão: " + global::version;
    mensagem += "\n";
    mensagem += "Desenvolvido em C++ / QT Creator";
    mensagem += "\n";
    mensagem += "SO: Arch Linux :: Kernel: 6.8.2-arch2-1 :: DE: LXQt 1.4.0";

    QMessageBox::about(this, "Sobre o Limus :: Livros e Músicas", mensagem);
}

void form_principal::on_actionAutores_triggered()
{
    form_autor f_autor;
    if (global::isLogged)
    {
        f_autor.exec();
    }
    else
    {
        QMessageBox::warning(this, "", "Autentique-se!");
    }
}

void form_principal::on_actionSeries_triggered()
{
    form_serie f_serie;
    if (global::isLogged)
    {
        f_serie.exec();
    }
    else
    {
        QMessageBox::warning(this, "", "Autentique-se!");
    }
}

void form_principal::on_pushButton_livros_clicked()
{
    form_livro f_livro;
    if (global::isLogged)
    {
        f_livro.exec();
    }
    else
    {
        QMessageBox::warning(this, "", "Autentique-se!");
    }
}

void form_principal::on_actionBandas_triggered()
{
    form_banda f_banda;
    if (global::isLogged)
    {
        f_banda.exec();
    }
    else
    {
        QMessageBox::warning(this, "", "Autentique-se!");
    }
}

void form_principal::on_actionAlbuns_triggered()
{
    form_album f_album;
    if (global::isLogged)
    {
        f_album.exec();
    }
    else
    {
        QMessageBox::warning(this, "", "Autentique-se!");
    }
}

void form_principal::on_pushButton_musicas_clicked()
{
    form_musica f_musica;
    if (global::isLogged)
    {
        f_musica.exec();
    }
    else
    {
        QMessageBox::warning(this, "", "Autentique-se!");
    }

}
