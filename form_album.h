#ifndef FORM_ALBUM_H
#define FORM_ALBUM_H

#include "album.h"

#include <QDialog>

namespace Ui {
class form_album;
}

class form_album : public QDialog
{
    Q_OBJECT

public:
    explicit form_album(QWidget *parent = nullptr);
    ~form_album();

    void inicializaFormAlbum();
    void populaTableWidget(QVector<Album> listaAlbum);
    void atualizaTableWidget(QString nome);
    void carregaComboBoxBanda();
    void limpaFormulario();
    void adicionaAlbumTableWidget(Album album);
    void alteraAlbumTableWidget(int row, Album album);
    Banda converteComboBoxBanda();

private slots:
    void on_pushButton_pesquisar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_tableWidget_album_itemSelectionChanged();

    void on_pushButton_incluir_clicked();

    void on_pushButton_alterar_clicked();

    void on_pushButton_limpar_clicked();

    void on_pushButton_fechar_clicked();

private:
    Ui::form_album *ui;
};

#endif // FORM_ALBUM_H
