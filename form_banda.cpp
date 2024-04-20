#include "bandaController.h"
#include "form_banda.h"
#include "global.h"
#include "ui_form_banda.h"

#include <QMessageBox>

form_banda::form_banda(QWidget *parent) : QDialog(parent), ui(new Ui::form_banda)
{
    ui->setupUi(this);

    form_banda::inicializaFormBanda();
}

form_banda::~form_banda()
{
    delete ui;
}

// MEUS MÉTODOS
void form_banda::inicializaFormBanda()
{
    form_banda::atualizaTableWidget("");
    ui->label_selected_row->setVisible(false);
}

void form_banda::populaTableWidget(QVector<Banda> listaBanda)
{
    QStringList cabecalho;
    Banda banda;

    cabecalho = {"ID", "Nome"};
    global::formataTableWidget(ui->tableWidget_banda, cabecalho);

    for (int i = 0; i < listaBanda.size(); ++i)
    {
        banda = listaBanda[i];
        ui->tableWidget_banda->insertRow(i);
        ui->tableWidget_banda->setItem(i, 0, new QTableWidgetItem(QString::number(banda.getId())));
        ui->tableWidget_banda->setItem(i, 1, new QTableWidgetItem(banda.getNome()));
        ui->tableWidget_banda->setRowHeight(i, 20);
    }
}

void form_banda::atualizaTableWidget(QString nome)
{
    QVector<Banda> listaBanda;
    BandaController bandaController;

    if (global::minimoCaracteres(nome, 3))
    {
        listaBanda = bandaController.buscaPorColaboradorNome(global::colaboradorLogado.getId(), nome);
    }
    else
    {
        listaBanda = bandaController.buscaPorColaborador(global::colaboradorLogado.getId());
    }
    form_banda::populaTableWidget(listaBanda);
    form_banda::limpaFormulario();
}

void form_banda::limpaFormulario()
{
    ui->tableWidget_banda->clearSelection();
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_nome->clear();
    ui->label_selected_row->setText("-1");
    ui->lineEdit_pesquisar->setFocus();
    ui->pushButton_incluir->setEnabled(true);
    ui->pushButton_alterar->setEnabled(false);
}

void form_banda::adicionaBandaTableWidget(Banda banda)
{
    int row;

    row = ui->tableWidget_banda->rowCount();

    ui->tableWidget_banda->insertRow(row);
    ui->tableWidget_banda->setItem(row, 0, new QTableWidgetItem(QString::number(banda.getId())));
    ui->tableWidget_banda->setItem(row, 1, new QTableWidgetItem(banda.getNome()));
    ui->tableWidget_banda->setRowHeight(row, 20);
}

void form_banda::alteraBandaTableWidget(int row, Banda banda)
{
    ui->tableWidget_banda->item(row, 1)->setText(banda.getNome());
}

// SLOTS
void form_banda::on_pushButton_pesquisar_clicked()
{
    QString nome;

    nome = ui->lineEdit_pesquisar->text();

    if (global::minimoCaracteres(nome, 3))
    {
        form_banda::atualizaTableWidget(nome);
        ui->pushButton_mostrar_todos->setEnabled(true);
    }
    else
    {
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres.");
    }
}

void form_banda::on_pushButton_mostrar_todos_clicked()
{
    form_banda::atualizaTableWidget("");
    ui->pushButton_mostrar_todos->setEnabled(false);
}

void form_banda::on_tableWidget_banda_itemSelectionChanged()
{
    int row, id;
    QString nome;

    row = ui->tableWidget_banda->currentRow();
    id = ui->tableWidget_banda->item(row, 0)->text().toInt();
    nome = ui->tableWidget_banda->item(row, 1)->text();

    ui->label_selected_row->setText(QString::number(row));
    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_nome->setText(nome);

    ui->pushButton_incluir->setEnabled(false);
    ui->pushButton_alterar->setEnabled(true);
}

void form_banda::on_pushButton_incluir_clicked()
{
    QString nome;
    Banda banda;
    BandaController bandaController;
    QMessageBox::StandardButton resposta;

    nome = ui->lineEdit_nome->text().trimmed();

    if (!global::minimoCaracteres(nome, 3))
    {
        QMessageBox::warning(this, "", "Nome deve ter pelo menos 3 caracteres.");
        return;
    }

    resposta = QMessageBox::question(this, "Confirmação de inclusão", "Tem certeza que deseja incluir?", QMessageBox::Yes | QMessageBox::No);

    if(resposta == QMessageBox::Yes)
    {
        banda.setNome(nome);
        banda.setColaborador(global::colaboradorLogado);

        banda = bandaController.insere(banda);

        form_banda::adicionaBandaTableWidget(banda);
        QMessageBox::about(this, "", "Cadastrado com sucesso.");
        form_banda::limpaFormulario();
    }
}

void form_banda::on_pushButton_alterar_clicked()
{
    int row, id;
    QString nome;
    Banda banda;
    BandaController bandaController;
    QMessageBox::StandardButton resposta;

    row = ui->label_selected_row->text().toInt();
    id = ui->lineEdit_id->text().toInt();
    nome = ui->lineEdit_nome->text().trimmed();

    if (!global::minimoCaracteres(nome, 3))
    {
        QMessageBox::warning(this, "", "Nome deve ter pelo menos 3 caracteres.");
        return;
    }

    resposta = QMessageBox::question(this, "Confirmação de alteração", "Tem certeza que deseja alterar?", QMessageBox::Yes | QMessageBox::No);

    if(resposta == QMessageBox::Yes)
    {
        banda.setId(id);
        banda.setNome(nome);
        banda.setColaborador(global::colaboradorLogado);

        if(bandaController.altera(banda))
        {
            form_banda::alteraBandaTableWidget(row, banda);
            QMessageBox::about(this, "", "Alterado com sucesso.");
            form_banda::limpaFormulario();
        }
    }
}

void form_banda::on_pushButton_limpar_clicked()
{
    form_banda::limpaFormulario();
}

void form_banda::on_pushButton_fechar_clicked()
{
    close();
}
