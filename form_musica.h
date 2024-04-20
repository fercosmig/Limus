#ifndef FORM_MUSICA_H
#define FORM_MUSICA_H

#include "musica.h"

#include <QDialog>

namespace Ui {
class form_musica;
}

class form_musica : public QDialog
{
    Q_OBJECT

public:
    explicit form_musica(QWidget *parent = nullptr);
    ~form_musica();

    // MEUS MÉTODOS
    void inicializaFormMusica();
    void populaTableWidget(QVector<Musica> listaMusica);
    void atualizaTableWidget(QString nome);
    void limpaFormulario();
    Banda converteComboBoxBanda(int index);
    Album converteComboBoxAlbum();
    void carregaComboBoxBanda();
    void carregaComboBoxAlbum(Banda banda);
    void adicionaMusicaTableWidget(Musica musica);
    void alteraMusicaTableWidget(int row, Musica musica);

private slots:
    void on_pushButton_pesquisar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_tableWidget_musica_itemSelectionChanged();

    void on_comboBox_banda_currentIndexChanged(int index);

    void on_pushButton_incluir_clicked();

    void on_pushButton_alterar_clicked();

    void on_pushButton_limpar_clicked();

    void on_pushButton_fechar_clicked();

private:
    Ui::form_musica *ui;
};

#endif // FORM_MUSICA_H
