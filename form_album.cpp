#include "albumController.h"
#include "bandaController.h"
#include "form_album.h"
#include "global.h"
#include "ui_form_album.h"

#include <QMessageBox>

form_album::form_album(QWidget *parent) : QDialog(parent), ui(new Ui::form_album)
{
    ui->setupUi(this);

    form_album::inicializaFormAlbum();
}

form_album::~form_album()
{
    delete ui;
}

// MEUS MÉTODOS
void form_album::inicializaFormAlbum()
{
    form_album::atualizaTableWidget("");
    form_album::carregaComboBoxBanda();
    ui->label_selected_row->setVisible(false);
}

void form_album::populaTableWidget(QVector<Album> listaAlbum)
{
    QStringList cabecalho;
    Album album;

    cabecalho = {"ID", "Nome", "Ano", "id_banda", "Banda"};
    global::formataTableWidget(ui->tableWidget_album, cabecalho);

    for (int i = 0; i < listaAlbum.size(); ++i)
    {
        album = listaAlbum[i];
        ui->tableWidget_album->insertRow(i);
        ui->tableWidget_album->setItem(i, 0, new QTableWidgetItem(QString::number(album.getId())));
        ui->tableWidget_album->setItem(i, 1, new QTableWidgetItem(album.getNome()));
        ui->tableWidget_album->setItem(i, 2, new QTableWidgetItem(QString::number(album.getAno())));
        ui->tableWidget_album->setItem(i, 3, new QTableWidgetItem(QString::number(album.getBanda().getId())));
        ui->tableWidget_album->setItem(i, 4, new QTableWidgetItem(album.getBanda().getNome()));
        ui->tableWidget_album->setRowHeight(i, 20);
    }
    ui->tableWidget_album->setColumnHidden(3, true);
}

void form_album::atualizaTableWidget(QString nome)
{
    QVector<Album> listaAlbum;
    AlbumController albumController;

    if (global::minimoCaracteres(nome, 3))
    {
        if (ui->radioButton_nome->isChecked())
        {
            listaAlbum = albumController.buscaPorColaboradorNome(global::colaboradorLogado.getId(), nome);
        }
        if (ui->radioButton_ano->isChecked())
        {
            listaAlbum = albumController.buscaPorColaboradorAno(global::colaboradorLogado.getId(), nome.toInt());
        }
        if (ui->radioButton_banda->isChecked())
        {
            listaAlbum = albumController.buscaPorColaboradorBanda(global::colaboradorLogado.getId(), nome);
        }
    }
    else
    {
        listaAlbum = albumController.buscaPorColaborador(global::colaboradorLogado.getId());
    }
    form_album::populaTableWidget(listaAlbum);
}

void form_album::carregaComboBoxBanda()
{
    Banda banda;
    QVector<Banda> listaBanda;
    BandaController bandaController;

    ui->comboBox_banda->clear();
    ui->comboBox_banda->addItem("Selecione", 0);

    listaBanda = bandaController.buscaPorColaborador(global::colaboradorLogado.getId());
    for (int i = 0; i < listaBanda.size(); ++i)
    {
        banda = listaBanda[i];
        ui->comboBox_banda->addItem(banda.getNome(), banda.getId());
    }
}

void form_album::limpaFormulario()
{
    ui->tableWidget_album->clearSelection();
    ui->radioButton_nome->setChecked(true);
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_nome->clear();
    ui->spinBox_ano->setValue(1900);
    ui->comboBox_banda->setCurrentIndex(0);
    ui->label_selected_row->setText("-1");
    ui->pushButton_incluir->setEnabled(true);
    ui->pushButton_alterar->setEnabled(false);
}

void form_album::adicionaAlbumTableWidget(Album album)
{
    int row;

    row = ui->tableWidget_album->rowCount();
    ui->tableWidget_album->insertRow(row);
    ui->tableWidget_album->setItem(row, 0, new QTableWidgetItem(QString::number(album.getId())));
    ui->tableWidget_album->setItem(row, 1, new QTableWidgetItem(album.getNome()));
    ui->tableWidget_album->setItem(row, 2, new QTableWidgetItem(QString::number(album.getAno())));
    ui->tableWidget_album->setItem(row, 3, new QTableWidgetItem(QString::number(album.getBanda().getId())));
    ui->tableWidget_album->setItem(row, 4, new QTableWidgetItem(album.getBanda().getNome()));
    ui->tableWidget_album->setRowHeight(row, 20);
}

void form_album::alteraAlbumTableWidget(int row, Album album)
{
    ui->tableWidget_album->item(row, 1)->setText(album.getNome());
    ui->tableWidget_album->item(row, 2)->setText(QString::number(album.getAno()));
    ui->tableWidget_album->item(row, 3)->setText(QString::number(album.getBanda().getId()));
    ui->tableWidget_album->item(row, 4)->setText(album.getBanda().getNome());
}

Banda form_album::converteComboBoxBanda()
{
    Banda banda;

    banda.setId(ui->comboBox_banda->currentData().toInt());
    banda.setNome(ui->comboBox_banda->currentText());
    banda.setColaborador(global::colaboradorLogado);

    return banda;
}

// SLOTS
void form_album::on_pushButton_pesquisar_clicked()
{
    QString nome;

    nome = ui->lineEdit_pesquisar->text().trimmed();

    if (global::minimoCaracteres(nome, 3))
    {
        form_album::atualizaTableWidget(nome);
        ui->pushButton_mostrar_todos->setEnabled(true);
        form_album::limpaFormulario();   }
    else
    {
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres.");
    }
}

void form_album::on_pushButton_mostrar_todos_clicked()
{
    form_album::atualizaTableWidget("");
    form_album::limpaFormulario();
    ui->pushButton_mostrar_todos->setEnabled(false);
}

void form_album::on_tableWidget_album_itemSelectionChanged()
{
    int row, id, ano;
    QString nome, nomeBanda;

    row = ui->tableWidget_album->currentRow();
    id = ui->tableWidget_album->item(row, 0)->text().toInt();
    nome = ui->tableWidget_album->item(row, 1)->text();
    ano = ui->tableWidget_album->item(row, 2)->text().toInt();
    nomeBanda = ui->tableWidget_album->item(row, 4)->text();

    ui->label_selected_row->setText(QString::number(row));
    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_nome->setText(nome);
    ui->spinBox_ano->setValue(ano);
    ui->comboBox_banda->setCurrentText(nomeBanda);

    ui->pushButton_incluir->setEnabled(false);
    ui->pushButton_alterar->setEnabled(true);
}

void form_album::on_pushButton_incluir_clicked()
{
    int ano, id_banda;
    QString nome;
    QDate hoje;
    Banda banda;
    Album album;
    AlbumController albumController;
    QMessageBox::StandardButton resposta;

    hoje = QDate::currentDate();
    nome = ui->lineEdit_nome->text().trimmed();
    ano = ui->spinBox_ano->value();
    id_banda = ui->comboBox_banda->currentData().toInt();

    if (!global::minimoCaracteres(nome, 3))
    {
        QMessageBox::warning(this, "", "Nome precisa ter pelo menos 3 caracteres.");
        return;
    }

    if (ano < 1900 || ano > hoje.year())
    {
        QMessageBox::warning(this, "", "Ano deve ser preenchido.");
        return;
    }

    if (id_banda == 0)
    {
        QMessageBox::warning(this, "", "Selecione uma banda.");
        return;
    }

    resposta = QMessageBox::question(this, "Confirma inclusão", "Tem certeza que deseja incluir?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes)
    {
        banda = form_album::converteComboBoxBanda();

        album.setNome(nome);
        album.setAno(ano);
        album.setBanda(banda);
        album.setColaborador(global::colaboradorLogado);

        album = albumController.insere(album);

        form_album::adicionaAlbumTableWidget(album);
        QMessageBox::about(this, "", "Cadastrado com sucesso.");
        form_album::limpaFormulario();
    }
}

void form_album::on_pushButton_alterar_clicked()
{
    int id, ano, id_banda, row;
    QString nome;
    QDate hoje;
    Banda banda;
    Album album;
    AlbumController albumController;
    QMessageBox::StandardButton resposta;

    hoje = QDate::currentDate();
    row = ui->label_selected_row->text().toInt();
    id = ui->lineEdit_id->text().toInt();
    nome = ui->lineEdit_nome->text().trimmed();
    ano = ui->spinBox_ano->value();
    id_banda = ui->comboBox_banda->currentData().toInt();

    if (!global::minimoCaracteres(nome, 3))
    {
        QMessageBox::warning(this, "", "Nome precisa ter pelo menos 3 caracteres.");
        return;
    }

    if (ano < 1900 || ano > hoje.year())
    {
        QMessageBox::warning(this, "", "Ano deve ser preenchido.");
        return;
    }

    if (id_banda == 0)
    {
        QMessageBox::warning(this, "", "Selecione uma banda.");
        return;
    }

    resposta = QMessageBox::question(this, "Confirma alteração", "Tem certeza que deseja alterar?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes)
    {
        banda = form_album::converteComboBoxBanda();

        album.setId(id);
        album.setNome(nome);
        album.setAno(ano);
        album.setBanda(banda);
        album.setColaborador(global::colaboradorLogado);

        if(albumController.altera(album))
        {
            form_album::alteraAlbumTableWidget(row, album);
            QMessageBox::about(this, "", "Alterado com sucesso.");
            form_album::limpaFormulario();
        }
    }
}

void form_album::on_pushButton_limpar_clicked()
{
    form_album::limpaFormulario();
}

void form_album::on_pushButton_fechar_clicked()
{
    close();
}
