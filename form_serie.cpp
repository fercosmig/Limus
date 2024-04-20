#include "form_serie.h"
#include "global.h"
#include "serieController.h"
#include "ui_form_serie.h"

#include <QMessageBox>

form_serie::form_serie(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::form_serie)
{
    ui->setupUi(this);

    form_serie::inicializa_form_serie();
}

form_serie::~form_serie()
{
    delete ui;
}

// MEUS MÉTODOS
void form_serie::inicializa_form_serie()
{
    form_serie::atualiza_table_widget("");
    ui->label_selected_row->setVisible(false);
}

void form_serie::popula_table_widget(QVector<Serie> listaSerie)
{
    Serie serie;
    QStringList cabecalho;

    cabecalho = {"ID", "Nome"};
    global::formataTableWidget(ui->tableWidget_serie, cabecalho);

    for (int i = 0; i < listaSerie.size(); ++i) {
        serie = listaSerie[i];
        if (serie.getId() != 1)
        {
            ui->tableWidget_serie->insertRow(i);
            ui->tableWidget_serie->setItem(i, 0, new QTableWidgetItem(QString::number(serie.getId())));
            ui->tableWidget_serie->setItem(i, 1, new QTableWidgetItem(serie.getNome()));
            ui->tableWidget_serie->setRowHeight(i, 20);
        }
    }
}

void form_serie::atualiza_table_widget(QString nome)
{
    QVector<Serie> listaSerie;
    SerieController serieController;

    if (global::minimoCaracteres(nome, 3))
    {
        listaSerie = serieController.buscaPorNome(global::colaboradorLogado.getId(), nome);
    }
    else
    {
        listaSerie = serieController.buscaTodos(global::colaboradorLogado.getId());
    }
    form_serie::popula_table_widget(listaSerie);
}

void form_serie::limpa_formulario()
{
    ui->tableWidget_serie->clearSelection();
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_nome->clear();
    ui->label_selected_row->setText("-1");
    ui->lineEdit_pesquisar->setFocus();
    ui->pushButton_incluir->setEnabled(true);
    ui->pushButton_alterar->setEnabled(false);
}

void form_serie::adiciona_serie_table_widget(Serie serie)
{
    int row;

    row = ui->tableWidget_serie->rowCount();
    ui->tableWidget_serie->insertRow(row);
    ui->tableWidget_serie->setItem(row, 0, new QTableWidgetItem(QString::number(serie.getId())));
    ui->tableWidget_serie->setItem(row, 1, new QTableWidgetItem(serie.getNome()));
    ui->tableWidget_serie->setRowHeight(row, 20);
}

void form_serie::altera_serie_table_widget(int row, Serie serie)
{
    ui->tableWidget_serie->item(row, 0)->setText(QString::number(serie.getId()));
    ui->tableWidget_serie->item(row, 1)->setText(serie.getNome());
}

// SLOTS
void form_serie::on_pushButton_pesquisar_clicked()
{
    QString nome;

    nome = ui->lineEdit_pesquisar->text().trimmed();

    if (global::minimoCaracteres(nome, 3))
    {
        form_serie::atualiza_table_widget(nome);
        ui->pushButton_mostrar_todos->setEnabled(true);
        form_serie::limpa_formulario();
    }
    else
    {
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres para pesquisa.");
    }
}

void form_serie::on_pushButton_mostrar_todos_clicked()
{
    form_serie::atualiza_table_widget("");
    ui->pushButton_mostrar_todos->setEnabled(false);
    form_serie::limpa_formulario();
}

void form_serie::on_tableWidget_serie_itemSelectionChanged()
{
    int row, id;
    QString nome;

    row = ui->tableWidget_serie->currentRow();
    id = ui->tableWidget_serie->item(row, 0)->text().toInt();
    nome = ui->tableWidget_serie->item(row, 1)->text();

    ui->label_selected_row->setText(QString::number(row));
    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_nome->setText(nome);

    ui->pushButton_incluir->setEnabled(false);
    ui->pushButton_alterar->setEnabled(true);
}

void form_serie::on_pushButton_incluir_clicked()
{
    QString nome;
    Serie serie;
    SerieController serieController;
    QMessageBox::StandardButton resposta;

    nome = ui->lineEdit_nome->text().trimmed();

    if (!global::minimoCaracteres(nome, 3))
    {
        QMessageBox::warning(this, "", "Nome deve ter no mínimo 3 caracteres.");
        return;
    }

    resposta = QMessageBox::question(this, "Confirma inclusão?", "Tem certeza que quer incluir?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes)
    {
        serie.setNome(nome);
        serie.setColaborador(global::colaboradorLogado);

        serie = serieController.insere(serie);

        form_serie::adiciona_serie_table_widget(serie);
        QMessageBox::about(this, "", "Cadastrado com sucesso!");
        form_serie::limpa_formulario();
    }
}

void form_serie::on_pushButton_alterar_clicked()
{
    int row, id;
    QString nome;
    Serie serie;
    SerieController serieController;
    QMessageBox::StandardButton resposta;

    row = ui->label_selected_row->text().toInt();
    id = ui->lineEdit_id->text().toInt();
    nome = ui->lineEdit_nome->text();

    if (!global::minimoCaracteres(nome, 3))
    {
        QMessageBox::warning(this, "", "Nome deve ter no mínimo 3 caracteres.");
        return;
    }

    resposta = QMessageBox::question(this, "Confirma alteração?", "Tem certeza que quer alterar?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes)
    {
        serie.setId(id);
        serie.setNome(nome);
        serie.setColaborador(global::colaboradorLogado);

        if (serieController.altera(serie))
        {
            form_serie::altera_serie_table_widget(row, serie);
            QMessageBox::about(this, "", "Alterado com sucesso!");
            form_serie::limpa_formulario();
        }
    }
}

void form_serie::on_pushButton_limpar_clicked()
{
    form_serie::limpa_formulario();
}

void form_serie::on_pushButton_fechar_clicked()
{
    close();
}
