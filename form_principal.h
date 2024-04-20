#ifndef FORM_PRINCIPAL_H
#define FORM_PRINCIPAL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class form_principal;
}
QT_END_NAMESPACE

class form_principal : public QMainWindow
{
    Q_OBJECT

public:
    form_principal(QWidget *parent = nullptr);
    ~form_principal();

    // VARIÁVEIS E OBJETOS
    QIcon cadeadoFechado, cadeadoAberto;

    // MEUS MÉTODOS
    void inicializa_form_principal();
    void configura_imagens();
    void configura_autencicacao();

private slots:
    void on_pushButton_autenticacao_clicked();

    void on_pushButton_fechar_clicked();

    void on_actionGrupos_triggered();

    void on_actionColaboradores_triggered();

    void on_actionSair_triggered();

    void on_actionSobre_triggered();

    void on_actionAutores_triggered();

    void on_actionSeries_triggered();

    void on_pushButton_livros_clicked();

    void on_actionBandas_triggered();

    void on_actionAlbuns_triggered();

    void on_pushButton_musicas_clicked();

private:
    Ui::form_principal *ui;
};
#endif // FORM_PRINCIPAL_H
