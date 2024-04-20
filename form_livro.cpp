#include "autor.h"
#include "autorController.h"
#include "form_livro.h"
#include "livroAutorController.h"
#include "livroController.h"
#include "serieController.h"
#include "statusController.h"
#include "ui_form_livro.h"

#include <QMessageBox>

form_livro::form_livro(QWidget *parent) : QDialog(parent), ui(new Ui::form_livro)
{
    ui->setupUi(this);

    form_livro::inicializaFormLivro();
}

form_livro::~form_livro()
{
    delete ui;
}

// MEUS MÉTODOS
void form_livro::inicializaFormLivro()
{
    form_livro::atualizaTableWidgetLivro("");
    form_livro::carregaComboBoxSerie();
    form_livro::carregaComboBoxStatus();
    form_livro::atualizaTableWidgetAutorTodos(0);
    form_livro::atualizaTableWidgetAutorSelecionado(0);
    ui->label_selected_row->setVisible(false);
}

void form_livro::populaTableWidgetLivro(QVector<Livro> listaLivro)
{
    QStringList cabecalho;
    Livro livro;

    cabecalho = {"ID", "Nome", "id_serie", "Série", "Índice", "id_status", "status", "Página", "Autores"};
    global::formataTableWidget(ui->tableWidget_livro, cabecalho);

    for (int i = 0; i < listaLivro.size(); ++i)
    {
        livro = listaLivro[i];
        ui->tableWidget_livro->insertRow(i);
        ui->tableWidget_livro->setItem(i, 0, new QTableWidgetItem(QString::number(livro.getId())));
        ui->tableWidget_livro->setItem(i, 1, new QTableWidgetItem(livro.getNome()));
        ui->tableWidget_livro->setItem(i, 2, new QTableWidgetItem(QString::number(livro.getSerie().getId())));
        ui->tableWidget_livro->setItem(i, 3, new QTableWidgetItem(livro.getSerie().getNome()));
        ui->tableWidget_livro->setItem(i, 4, new QTableWidgetItem(QString::number(livro.getIndice())));
        ui->tableWidget_livro->setItem(i, 5, new QTableWidgetItem(QString::number(livro.getStatus().getId())));
        ui->tableWidget_livro->setItem(i, 6, new QTableWidgetItem(livro.getStatus().getNome()));
        ui->tableWidget_livro->setItem(i, 7, new QTableWidgetItem(QString::number(livro.getPagina())));
        ui->tableWidget_livro->setItem(i, 8, new QTableWidgetItem(form_livro::buscaAutoresString(livro.getId())));
        ui->tableWidget_livro->setRowHeight(i, 20);
    }
    ui->tableWidget_livro->setColumnHidden(2, true);
    ui->tableWidget_livro->setColumnHidden(5, true);
}

void form_livro::atualizaTableWidgetLivro(QString nome)
{
    QVector<Livro> listaLivro;
    LivroController livroController;

    if (global::minimoCaracteres(nome, 3))
    {
        if (ui->radioButton_nome->isChecked())
        {
            listaLivro = livroController.buscaPorColaboradorNome(global::colaboradorLogado.getId(), nome);
        }

        if (ui->radioButton_serie->isChecked())
        {
            listaLivro = livroController.buscaPorColaboradorSerie(global::colaboradorLogado.getId(), nome);
        }
    }
    else
    {
        listaLivro = livroController.buscaPorColaborador(global::colaboradorLogado.getId());
    }
    form_livro::populaTableWidgetLivro(listaLivro);
}

QString form_livro::buscaAutoresString(int id_livro)
{
    int quantidade;
    QString autores = "";
    Autor autor;
    QVector<Autor> listaAutor;
    LivroAutorController livroAutorController;

    listaAutor = livroAutorController.buscaAutorPorIdLivro(id_livro);
    quantidade = listaAutor.size();

    for (int i = 0; i < quantidade; ++i)
    {
        autor = listaAutor[i];
        autores += autor.getNome();
        autores += " / ";
    }
    autores.remove(autores.size() -3, 3);

    return autores;
}

void form_livro::carregaComboBoxSerie()
{
    Serie serie;
    QVector<Serie> listaSerie;
    SerieController serieController;

    listaSerie = serieController.buscaTodos(global::colaboradorLogado.getId());

    ui->comboBox_serie->addItem("Selecione", 0);

    for (int i = 0; i < listaSerie.size(); ++i)
    {
        serie = listaSerie[i];
        ui->comboBox_serie->addItem(serie.getNome(), serie.getId());
    }
}

void form_livro::carregaComboBoxStatus()
{
    Status status;
    QVector<Status> listaStatus;
    StatusController statusController;

    listaStatus = statusController.buscaTodos();

    ui->comboBox_status->addItem("Selecione", 0);

    for (int i = 0; i < listaStatus.size(); ++i) {
        status = listaStatus[i];
        ui->comboBox_status->addItem(status.getNome(), status.getId());
    }
}

void form_livro::populaTableWidgetAutorTodos(QVector<Autor> listaAutor)
{
    Autor autor;
    QStringList cabecalho;

    cabecalho = {"ID", "Nome"};
    global::formataTableWidget(ui->tableWidget_autor_todos, cabecalho);

    for (int i = 0; i < listaAutor.size(); ++i) {
        autor = listaAutor[i];
        ui->tableWidget_autor_todos->insertRow(i);
        ui->tableWidget_autor_todos->setItem(i, 0, new QTableWidgetItem(QString::number(autor.getId())));
        ui->tableWidget_autor_todos->setItem(i, 1, new QTableWidgetItem(autor.getNome()));
        ui->tableWidget_autor_todos->setRowHeight(i, 20);
    }
}

void form_livro::atualizaTableWidgetAutorTodos(int id_livro)
{
    QVector<Autor> listaAutor;
    AutorController autorController;
    LivroAutorController livroAutorController;

    if (id_livro == 0)
    {
        listaAutor = autorController.buscaTodos(global::colaboradorLogado.getId());
    }
    else
    {
        listaAutor = livroAutorController.buscaAutorNaoSelecionado(global::colaboradorLogado.getId(), id_livro);
    }

    form_livro::populaTableWidgetAutorTodos(listaAutor);
}

void form_livro::adicionaAutorTableWidgetAutorSelecionado(Autor autor)
{
    int row;

    row = ui->tableWidget_autor_selecionado->rowCount();
    ui->tableWidget_autor_selecionado->insertRow(row);
    ui->tableWidget_autor_selecionado->setItem(row, 0, new QTableWidgetItem(QString::number(autor.getId())));
    ui->tableWidget_autor_selecionado->setItem(row, 1, new QTableWidgetItem(autor.getNome()));
    ui->tableWidget_autor_selecionado->setRowHeight(row, 20);
}

void form_livro::adicionaAutorTableWidgetAutorTodos(Autor autor)
{
    int row;

    row = ui->tableWidget_autor_todos->rowCount();
    ui->tableWidget_autor_todos->insertRow(row);
    ui->tableWidget_autor_todos->setItem(row, 0, new QTableWidgetItem(QString::number(autor.getId())));
    ui->tableWidget_autor_todos->setItem(row, 1, new QTableWidgetItem(autor.getNome()));
    ui->tableWidget_autor_todos->setRowHeight(row, 20);
}

void form_livro::populaTableWidgetAutorSelecionado(QVector<Autor> listaAutor)
{
    Autor autor;
    QStringList cabecalho;

    cabecalho = {"ID", "Nome"};
    global::formataTableWidget(ui->tableWidget_autor_selecionado, cabecalho);

    for (int i = 0; i < listaAutor.size(); ++i) {
        autor = listaAutor[i];
        ui->tableWidget_autor_selecionado->insertRow(i);
        ui->tableWidget_autor_selecionado->setItem(i, 0, new QTableWidgetItem(QString::number(autor.getId())));
        ui->tableWidget_autor_selecionado->setItem(i, 1, new QTableWidgetItem(autor.getNome()));
        ui->tableWidget_autor_selecionado->setRowHeight(i, 20);
    }
}

void form_livro::atualizaTableWidgetAutorSelecionado(int id_livro)
{
    QVector<Autor> listaAutor;
    LivroAutorController livroAutorController;

    listaAutor = livroAutorController.buscaAutorPorIdLivro(id_livro);
    form_livro::populaTableWidgetAutorSelecionado(listaAutor);
}

void form_livro::limpaFormulario()
{
    ui->tableWidget_livro->clearSelection();
    form_livro::atualizaTableWidgetAutorTodos(0);
    form_livro::atualizaTableWidgetAutorSelecionado(0);
    ui->lineEdit_pesquisar->clear();
    ui->radioButton_nome->setChecked(true);
    ui->lineEdit_id->clear();
    ui->lineEdit_nome->clear();
    ui->comboBox_serie->setCurrentIndex(0);
    ui->spinBox_indice->setValue(0);
    ui->comboBox_status->setCurrentIndex(0);
    ui->spinBox_pagina->setValue(0);
    ui->label_selected_row->setText("-1");
    ui->pushButton_alterar->setEnabled(false);
    ui->pushButton_incluir->setEnabled(true);
}

Serie form_livro::converteComboBoxSerie()
{
    Serie serie;

    serie.setId(ui->comboBox_serie->currentData().toInt());
    serie.setNome(ui->comboBox_serie->currentText());
    serie.setColaborador(global::colaboradorLogado);

    return serie;
}

Status form_livro::converteComboBoxStatus()
{
    Status status;

    status.setId(ui->comboBox_status->currentData().toInt());
    status.setNome(ui->comboBox_status->currentText());

    return status;
}

void form_livro::adicionaLivroTableWidgetLivro(Livro livro)
{
    int row;

    row = ui->tableWidget_livro->rowCount();

    ui->tableWidget_livro->insertRow(row);
    ui->tableWidget_livro->setItem(row, 0, new QTableWidgetItem(QString::number(livro.getId())));
    ui->tableWidget_livro->setItem(row, 1, new QTableWidgetItem(livro.getNome()));
    ui->tableWidget_livro->setItem(row, 2, new QTableWidgetItem(QString::number(livro.getSerie().getId())));
    ui->tableWidget_livro->setItem(row, 3, new QTableWidgetItem(livro.getSerie().getNome()));
    ui->tableWidget_livro->setItem(row, 4, new QTableWidgetItem(QString::number(livro.getIndice())));
    ui->tableWidget_livro->setItem(row, 5, new QTableWidgetItem(QString::number(livro.getStatus().getId())));
    ui->tableWidget_livro->setItem(row, 6, new QTableWidgetItem(livro.getStatus().getNome()));
    ui->tableWidget_livro->setItem(row, 7, new QTableWidgetItem(QString::number(livro.getPagina())));
    ui->tableWidget_livro->setItem(row, 8, new QTableWidgetItem(form_livro::buscaAutoresString(livro.getId())));
    ui->tableWidget_livro->setRowHeight(row, 20);
}

void form_livro::alteraLivroTableWidgetLivro(Livro livro)
{
    int row;

    row = ui->label_selected_row->text().toInt();

    ui->tableWidget_livro->item(row, 1)->setText(livro.getNome());
    ui->tableWidget_livro->item(row, 2)->setText(QString::number(livro.getSerie().getId()));
    ui->tableWidget_livro->item(row, 3)->setText(livro.getSerie().getNome());
    ui->tableWidget_livro->item(row, 4)->setText(QString::number(livro.getIndice()));
    ui->tableWidget_livro->item(row, 5)->setText(QString::number(livro.getStatus().getId()));
    ui->tableWidget_livro->item(row, 6)->setText(livro.getStatus().getNome());
    ui->tableWidget_livro->item(row, 7)->setText(QString::number(livro.getPagina()));
    ui->tableWidget_livro->item(row, 8)->setText(form_livro::buscaAutoresString(livro.getId()));
}

// SLOTS
void form_livro::on_pushButton_fechar_clicked()
{
    close();
}

void form_livro::on_comboBox_serie_currentIndexChanged(int index)
{
    int id;

    id = ui->comboBox_serie->itemData(index).toInt();

    ui->spinBox_indice->setValue(0);
    if (id <= 1)
    {
        ui->spinBox_indice->setEnabled(false);
    }
    else
    {
        ui->spinBox_indice->setEnabled(true);
    }
}

void form_livro::on_pushButton_adiciona_autor_clicked()
{
    int row;
    Autor autor;

    row = ui->tableWidget_autor_todos->currentRow();

    if (row >= 0)
    {
        autor.setId(ui->tableWidget_autor_todos->item(row, 0)->text().toInt());
        autor.setNome(ui->tableWidget_autor_todos->item(row, 1)->text());

        form_livro::adicionaAutorTableWidgetAutorSelecionado(autor);
        ui->tableWidget_autor_todos->removeRow(row);
    }
    else
    {
        QMessageBox::warning(this, "", "Selecione um autor na coluna da esquerda.");
    }
}

void form_livro::on_pushButton_remove_autor_clicked()
{
    int row;
    Autor autor;

    row = ui->tableWidget_autor_selecionado->currentRow();

    if (row >= 0)
    {
        autor.setId(ui->tableWidget_autor_selecionado->item(row, 0)->text().toInt());
        autor.setNome(ui->tableWidget_autor_selecionado->item(row, 1)->text());

        form_livro::adicionaAutorTableWidgetAutorTodos(autor);
        ui->tableWidget_autor_selecionado->removeRow(row);
    }
    else
    {
        QMessageBox::warning(this, "", "Selecione um autor na coluna da direita.");
    }
}

void form_livro::on_pushButton_limpar_clicked()
{
    form_livro::limpaFormulario();
}

void form_livro::on_pushButton_pesquisar_clicked()
{
    QString nome;
    QVector<Livro> listaLivro;
    LivroController livroController;
    LivroAutorController livroAutorController;

    nome = ui->lineEdit_pesquisar->text().trimmed();

    if (global::minimoCaracteres(nome, 3))
    {
        if (ui->radioButton_nome->isChecked())
        {
            listaLivro = livroController.buscaPorColaboradorNome(global::colaboradorLogado.getId(), nome);
        }

        if (ui->radioButton_serie->isChecked())
        {
            listaLivro = livroController.buscaPorColaboradorSerie(global::colaboradorLogado.getId(), nome);
        }

        if (ui->radioButton_autor->isChecked())
        {
            listaLivro = livroAutorController.buscaLivroPorNomeAutor(global::colaboradorLogado.getId(), nome);
        }
        ui->pushButton_mostrar_todos->setEnabled(true);
        form_livro::limpaFormulario();
        form_livro::populaTableWidgetLivro(listaLivro);
    }
    else
    {
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres.");
    }
}

void form_livro::on_pushButton_mostrar_todos_clicked()
{
    ui->pushButton_mostrar_todos->setEnabled(false);
    form_livro::limpaFormulario();
    form_livro::atualizaTableWidgetLivro("");
}

void form_livro::on_tableWidget_livro_itemSelectionChanged()
{
    int row, id, indice, pagina;
    QString nome, nomeSerie, nomeStatus;

    row = ui->tableWidget_livro->currentRow();
    id = ui->tableWidget_livro->item(row, 0)->text().toInt();
    nome = ui->tableWidget_livro->item(row, 1)->text();
    indice = ui->tableWidget_livro->item(row, 4)->text().toInt();
    pagina = ui->tableWidget_livro->item(row, 7)->text().toInt();
    nomeSerie = ui->tableWidget_livro->item(row, 3)->text();
    nomeStatus = ui->tableWidget_livro->item(row, 6)->text();

    ui->label_selected_row->setText(QString::number(row));
    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_nome->setText(nome);
    ui->spinBox_indice->setValue(indice);
    ui->spinBox_pagina->setValue(pagina);
    ui->comboBox_serie->setCurrentText(nomeSerie);
    ui->comboBox_status->setCurrentText(nomeStatus);

    form_livro::atualizaTableWidgetAutorSelecionado(id);
    form_livro::atualizaTableWidgetAutorTodos(id);

    ui->pushButton_incluir->setEnabled(false);
    ui->pushButton_alterar->setEnabled(true);
}

void form_livro::on_pushButton_incluir_clicked()
{
    int id_status, id_serie, indice, pagina, quantidade_autores;
    QString nome;
    Status status;
    Serie serie;
    Livro livro;
    Autor autor;
    LivroAutor livroAutor;
    LivroController livroController;
    LivroAutorController livroAutorController;
    QMessageBox::StandardButton resposta;

    quantidade_autores = ui->tableWidget_autor_selecionado->rowCount();
    nome = ui->lineEdit_nome->text().trimmed();
    indice = ui->spinBox_indice->value();
    pagina = ui->spinBox_pagina->value();
    id_serie = ui->comboBox_serie->currentData().toInt();
    id_status = ui->comboBox_status->currentData().toInt();

    if (!global::minimoCaracteres(nome, 3))
    {
        QMessageBox::warning(this, "", "Nome deve ter no mínimo 3 caracteres!");
        return;
    }

    if (id_serie == 0 )
    {
        QMessageBox::warning(this, "", "Serie deve ser preenchido!");
        return;
    }

    if (id_serie > 1 && indice < 1)
    {
        QMessageBox::warning(this, "", "Indice deve ser preenchido!");
        return;
    }

    if (id_status == 0)
    {
        QMessageBox::warning(this, "", "Status deve ser preenchido!");
        return;
    }

    if (id_status == 2 && pagina == 0)
    {
        QMessageBox::warning(this, "", "Página deve ser preenchido!");
        return;
    }

    if (quantidade_autores < 1)
    {
        QMessageBox::warning(this, "", "Pelo menos um autor deve ser selecionado.");
        return;
    }

    resposta = QMessageBox::question(this, "Confirmação de inclusão", "Tem certeza que deseja incluir?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes)
    {
        status = form_livro::converteComboBoxStatus();
        serie = form_livro::converteComboBoxSerie();

        livro.setNome(nome);
        livro.setIndice(indice);
        livro.setPagina(pagina);
        livro.setSerie(serie);
        livro.setStatus(status);
        livro.setColaborador(global::colaboradorLogado);

        livro = livroController.insere(livro);

        livroAutor.setLivro(livro);
        for (int i = 0; i < quantidade_autores; ++i)
        {
            autor.setId(ui->tableWidget_autor_selecionado->item(i, 0)->text().toInt());
            livroAutor.setAutor(autor);

            livroAutorController.insere(livroAutor);
        }
        form_livro::adicionaLivroTableWidgetLivro(livro);
        QMessageBox::about(this, "", "Cadastrado com sucesso!");
        form_livro::limpaFormulario();
    }
}

void form_livro::on_pushButton_alterar_clicked()
{
    int id, id_status, id_serie, indice, pagina, quantidade_autores;
    QString nome;
    Status status;
    Serie serie;
    Livro livro;
    Autor autor;
    LivroAutor livroAutor;
    LivroController livroController;
    LivroAutorController livroAutorController;
    QMessageBox::StandardButton resposta;

    quantidade_autores = ui->tableWidget_autor_selecionado->rowCount();
    id = ui->lineEdit_id->text().toInt();
    nome = ui->lineEdit_nome->text().trimmed();
    indice = ui->spinBox_indice->value();
    pagina = ui->spinBox_pagina->value();
    id_serie = ui->comboBox_serie->currentData().toInt();
    id_status = ui->comboBox_status->currentData().toInt();

    if (!global::minimoCaracteres(nome, 3))
    {
        QMessageBox::warning(this, "", "Nome deve ter no mínimo 3 caracteres!");
        return;
    }

    if (id_serie == 0 )
    {
        QMessageBox::warning(this, "", "Serie deve ser preenchido!");
        return;
    }

    if (id_serie > 1 && indice < 1)
    {
        QMessageBox::warning(this, "", "Indice deve ser preenchido!");
        return;
    }

    if (id_status == 0)
    {
        QMessageBox::warning(this, "", "Status deve ser preenchido!");
        return;
    }

    if (id_status == 2 && pagina == 0)
    {
        QMessageBox::warning(this, "", "Página deve ser preenchido!");
        return;
    }

    if (quantidade_autores < 1)
    {
        QMessageBox::warning(this, "", "Pelo menos um autor deve ser selecionado.");
        return;
    }

    resposta = QMessageBox::question(this, "Confirmação de alteração", "Tem certeza que deseja alterar?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes)
    {
        status = form_livro::converteComboBoxStatus();
        serie = form_livro::converteComboBoxSerie();

        livro.setId(id);
        livro.setNome(nome);
        livro.setIndice(indice);
        livro.setPagina(pagina);
        livro.setSerie(serie);
        livro.setStatus(status);
        livro.setColaborador(global::colaboradorLogado);

        if (livroController.altera(livro))
        {
            livroAutorController.remove(livro.getId());
            livroAutor.setLivro(livro);
            for (int i = 0; i < quantidade_autores; ++i)
            {
                autor.setId(ui->tableWidget_autor_selecionado->item(i, 0)->text().toInt());
                livroAutor.setAutor(autor);

                livroAutorController.insere(livroAutor);
            }
            form_livro::alteraLivroTableWidgetLivro(livro);
            QMessageBox::about(this, "", "Alterado com sucesso!");
            form_livro::limpaFormulario();
        }
    }
}

void form_livro::on_comboBox_status_currentIndexChanged(int index)
{
    int id_status;
    id_status = ui->comboBox_status->itemData(index).toInt();
    ui->spinBox_pagina->setValue(0);
    if (id_status == 2)
    {
        ui->spinBox_pagina->setEnabled(true);
    }
    else
    {
        ui->spinBox_pagina->setEnabled(false);
    }
}
