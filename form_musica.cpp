#include "albumController.h"
#include "bandaController.h"
#include "form_musica.h"
#include "musicaController.h"
#include "ui_form_musica.h"

#include <QMessageBox>

form_musica::form_musica(QWidget *parent) : QDialog(parent), ui(new Ui::form_musica)
{
    ui->setupUi(this);

    form_musica::inicializaFormMusica();
}

form_musica::~form_musica()
{
    delete ui;
}

// MEUS MÉTODOS
void form_musica::inicializaFormMusica()
{
    form_musica::atualizaTableWidget("");
    form_musica::carregaComboBoxBanda();
    ui->label_selected_row->setVisible(false);
}

void form_musica::populaTableWidget(QVector<Musica> listaMusica)
{
    QStringList cabecalho;
    Musica musica;

    cabecalho = {"ID", "Nome", "Indice", "id_album", "Album", "Ano", "id_banda", "Banda"};
    global::formataTableWidget(ui->tableWidget_musica, cabecalho);

    for (int i = 0; i < listaMusica.size(); ++i)
    {
        musica = listaMusica[i];
        ui->tableWidget_musica->insertRow(i);
        ui->tableWidget_musica->setItem(i, 0, new QTableWidgetItem(QString::number(musica.getId())));
        ui->tableWidget_musica->setItem(i, 1, new QTableWidgetItem(musica.getNome()));
        ui->tableWidget_musica->setItem(i, 2, new QTableWidgetItem(QString::number(musica.getIndice())));
        ui->tableWidget_musica->setItem(i, 3, new QTableWidgetItem(QString::number(musica.getAlbum().getId())));
        ui->tableWidget_musica->setItem(i, 4, new QTableWidgetItem(musica.getAlbum().getNome()));
        ui->tableWidget_musica->setItem(i, 5, new QTableWidgetItem(QString::number(musica.getAlbum().getAno())));
        ui->tableWidget_musica->setItem(i, 6, new QTableWidgetItem(QString::number(musica.getAlbum().getBanda().getId())));
        ui->tableWidget_musica->setItem(i, 7, new QTableWidgetItem(musica.getAlbum().getBanda().getNome()));
        ui->tableWidget_musica->setRowHeight(i, 20);
    }
    ui->tableWidget_musica->setColumnHidden(3, true);
    ui->tableWidget_musica->setColumnHidden(6, true);
}

void form_musica::atualizaTableWidget(QString nome)
{
    QVector<Musica> listaMusica;
    MusicaController musicaController;

    if (global::minimoCaracteres(nome, 3))
    {
        if (ui->radioButton_musica->isChecked())
        {
            listaMusica = musicaController.buscaPorColaboradorMusica(global::colaboradorLogado.getId(), nome);
        }

        if (ui->radioButton_album->isChecked())
        {
            listaMusica = musicaController.buscaPorColaboradorAlbum(global::colaboradorLogado.getId(), nome);
        }

        if (ui->radioButton_banda->isChecked())
        {
            listaMusica = musicaController.buscaPorColaboradorBanda(global::colaboradorLogado.getId(), nome);
        }
    }
    else
    {
        listaMusica = musicaController.buscaPorColaborador(global::colaboradorLogado.getId());
    }
    form_musica::populaTableWidget(listaMusica);
}

void form_musica::limpaFormulario()
{
    ui->tableWidget_musica->clearSelection();
    ui->radioButton_musica->setChecked(true);
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_nome->clear();
    ui->spinBox_indice->setValue(0);
    ui->comboBox_banda->setCurrentIndex(0);
    ui->comboBox_album->clear();
    ui->label_selected_row->setText("-1");
    ui->pushButton_incluir->setEnabled(true);
    ui->pushButton_alterar->setEnabled(false);
    ui->lineEdit_pesquisar->setFocus();
}

Banda form_musica::converteComboBoxBanda(int index)
{
    Banda banda;
    banda.setId(ui->comboBox_banda->itemData(index).toInt());
    banda.setNome(ui->comboBox_banda->itemText(index));
    banda.setColaborador(global::colaboradorLogado);
    return banda;
}

Album form_musica::converteComboBoxAlbum()
{
    Album album;
    AlbumController albumController;

    album.setId(ui->comboBox_album->currentData().toInt());
    album = albumController.buscaPorId(album.getId());
    return album;
}

void form_musica::carregaComboBoxBanda()
{
    Banda banda;
    BandaController bandaController;
    QVector<Banda> listaBanda;

    ui->comboBox_banda->clear();
    ui->comboBox_banda->addItem("Selecione", 0);

    listaBanda = bandaController.buscaPorColaborador(global::colaboradorLogado.getId());
    for (int i = 0; i < listaBanda.size(); ++i)
    {
        banda = listaBanda[i];
        ui->comboBox_banda->addItem(banda.getNome(), banda.getId());
    }
}

void form_musica::carregaComboBoxAlbum(Banda banda)
{
    Album album;
    AlbumController albumController;
    QVector<Album> listaAlbum;

    ui->comboBox_album->clear();
    ui->comboBox_album->addItem("Selecione", 0);
    listaAlbum = albumController.buscaPorIdBanda(banda.getId());
    for (int i = 0; i < listaAlbum.size(); ++i)
    {
        album = listaAlbum[i];
        ui->comboBox_album->addItem(album.getNome(), album.getId());
    }
}

void form_musica::adicionaMusicaTableWidget(Musica musica)
{
    int row;

    row = ui->tableWidget_musica->rowCount();
    ui->tableWidget_musica->insertRow(row);
    ui->tableWidget_musica->setItem(row, 0, new QTableWidgetItem(QString::number(musica.getId())));
    ui->tableWidget_musica->setItem(row, 1, new QTableWidgetItem(musica.getNome()));
    ui->tableWidget_musica->setItem(row, 2, new QTableWidgetItem(QString::number(musica.getIndice())));
    ui->tableWidget_musica->setItem(row, 3, new QTableWidgetItem(QString::number(musica.getAlbum().getId())));
    ui->tableWidget_musica->setItem(row, 4, new QTableWidgetItem(musica.getAlbum().getNome()));
    ui->tableWidget_musica->setItem(row, 5, new QTableWidgetItem(QString::number(musica.getAlbum().getAno())));
    ui->tableWidget_musica->setItem(row, 6, new QTableWidgetItem(QString::number(musica.getAlbum().getBanda().getId())));
    ui->tableWidget_musica->setItem(row, 7, new QTableWidgetItem(musica.getAlbum().getBanda().getNome()));
    ui->tableWidget_musica->setRowHeight(row, 20);
}

void form_musica::alteraMusicaTableWidget(int row, Musica musica)
{
    ui->tableWidget_musica->item(row, 1)->setText(musica.getNome());
    ui->tableWidget_musica->item(row, 2)->setText(QString::number(musica.getIndice()));
    ui->tableWidget_musica->item(row, 3)->setText(QString::number(musica.getAlbum().getId()));
    ui->tableWidget_musica->item(row, 4)->setText(musica.getAlbum().getNome());
    ui->tableWidget_musica->item(row, 5)->setText(QString::number(musica.getAlbum().getAno()));
    ui->tableWidget_musica->item(row, 6)->setText(QString::number(musica.getAlbum().getBanda().getId()));
    ui->tableWidget_musica->item(row, 7)->setText(musica.getAlbum().getBanda().getNome());
}

// SLOTS
void form_musica::on_pushButton_pesquisar_clicked()
{
    QString nome;

    nome = ui->lineEdit_pesquisar->text().trimmed();

    if (global::minimoCaracteres(nome, 3))
    {
        form_musica::atualizaTableWidget(nome);
        ui->pushButton_mostrar_todos->setEnabled(true);
        form_musica::limpaFormulario();
    }
    else
    {
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres.");
    }
}

void form_musica::on_pushButton_mostrar_todos_clicked()
{
    form_musica::atualizaTableWidget("");
    form_musica::limpaFormulario();
    ui->pushButton_mostrar_todos->setEnabled(false);
}

void form_musica::on_tableWidget_musica_itemSelectionChanged()
{
    int row, id, indice;
    QString nome, nomeBanda, nomeAlbum;

    row = ui->tableWidget_musica->currentRow();
    id = ui->tableWidget_musica->item(row, 0)->text().toInt();
    nome = ui->tableWidget_musica->item(row, 1)->text();
    indice = ui->tableWidget_musica->item(row, 2)->text().toInt();
    nomeBanda = ui->tableWidget_musica->item(row, 7)->text();
    nomeAlbum = ui->tableWidget_musica->item(row, 4)->text();

    ui->label_selected_row->setText(QString::number(row));
    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_nome->setText(nome);
    ui->spinBox_indice->setValue(indice);
    ui->comboBox_banda->setCurrentText(nomeBanda);
    ui->comboBox_album->setCurrentText(nomeAlbum);

    ui->pushButton_incluir->setEnabled(false);
    ui->pushButton_alterar->setEnabled(true);
}

void form_musica::on_comboBox_banda_currentIndexChanged(int index)
{
    Banda banda;

    banda = form_musica::converteComboBoxBanda(index);
    if (banda.getId() == 0)
    {
        ui->comboBox_album->clear();
        ui->comboBox_album->setEnabled(false);
    }
    else
    {
        form_musica::carregaComboBoxAlbum(banda);
        ui->comboBox_album->setEnabled(true);
    }
}

void form_musica::on_pushButton_incluir_clicked()
{
    int indice, id_banda, id_album;
    QString nome;
    Album album;
    Musica musica;
    MusicaController musicaController;
    QMessageBox::StandardButton resposta;

    nome = ui->lineEdit_nome->text().trimmed();
    indice = ui->spinBox_indice->value();
    id_album = ui->comboBox_album->currentData().toInt();
    id_banda = ui->comboBox_banda->currentData().toInt();

    if (!global::minimoCaracteres(nome, 3))
    {
        QMessageBox::warning(this, "", "Nome deve ter no mínimo 3 caracteres.");
        return;
    }

    if (indice == 0)
    {
        QMessageBox::warning(this, "", "Indice deve ser preenchido.");
        return;
    }

    if (id_banda == 0)
    {
        QMessageBox::warning(this, "", "Uma banda deve ser selecionada.");
        return;
    }
    else
    {
        if (id_album == 0)
        {
            QMessageBox::warning(this, "", "Um album deve ser selecionado.");
            return;
        }
    }

    resposta = QMessageBox::question(this, "Confirmação de inclusão", "Tem certeza que deseja incluir?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes)
    {
        album = form_musica::converteComboBoxAlbum();

        musica.setNome(nome);
        musica.setIndice(indice);
        musica.setAlbum(album);
        musica.setColaborador(global::colaboradorLogado);

        musica = musicaController.insere(musica);

        form_musica::adicionaMusicaTableWidget(musica);
        QMessageBox::about(this, "", "Cadastrado com sucesso!");
        form_musica::limpaFormulario();
    }
}

void form_musica::on_pushButton_alterar_clicked()
{
    int row, id, indice, id_banda, id_album;
    QString nome;
    Album album;
    Musica musica;
    MusicaController musicaController;
    QMessageBox::StandardButton resposta;

    row = ui->label_selected_row->text().toInt();
    id = ui->lineEdit_id->text().toInt();
    nome = ui->lineEdit_nome->text().trimmed();
    indice = ui->spinBox_indice->value();
    id_album = ui->comboBox_album->currentData().toInt();
    id_banda = ui->comboBox_banda->currentData().toInt();

    if (!global::minimoCaracteres(nome, 3))
    {
        QMessageBox::warning(this, "", "Nome deve ter no mínimo 3 caracteres.");
        return;
    }

    if (indice == 0)
    {
        QMessageBox::warning(this, "", "Indice deve ser preenchido.");
        return;
    }

    if (id_banda == 0)
    {
        QMessageBox::warning(this, "", "Uma banda deve ser selecionada.");
        return;
    }
    else
    {
        if (id_album == 0)
        {
            QMessageBox::warning(this, "", "Um album deve ser selecionado.");
            return;
        }
    }

    resposta = QMessageBox::question(this, "Confirmação de alteração", "Tem certeza que deseja alterar?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes)
    {
        album = form_musica::converteComboBoxAlbum();

        musica.setId(id);
        musica.setNome(nome);
        musica.setIndice(indice);
        musica.setAlbum(album);
        musica.setColaborador(global::colaboradorLogado);

        if (musicaController.altera(musica))
        {
            form_musica::alteraMusicaTableWidget(row, musica);
            QMessageBox::about(this, "", "Alterado com sucesso!");
            form_musica::limpaFormulario();
        }
    }
}

void form_musica::on_pushButton_limpar_clicked()
{
    form_musica::limpaFormulario();
}

void form_musica::on_pushButton_fechar_clicked()
{
    close();
}
