#include "autor.h"
#include "autorController.h"
#include "form_autor.h"
#include "global.h"
#include "ui_form_autor.h"

#include <QMessageBox>

form_autor::form_autor(QWidget *parent) : QDialog(parent), ui(new Ui::form_autor)
{
    ui->setupUi(this);

    form_autor::inicializa_form_autor();
}

form_autor::~form_autor()
{
    delete ui;
}

// MEUS MÉTODOS
void form_autor::inicializa_form_autor()
{
    form_autor::atualiza_table_widget("");
    ui->label_selected_row->setVisible(false);
}

void form_autor::popula_table_widget(QVector<Autor> listaAutor)
{
    Autor autor;
    QStringList cabecalho;

    cabecalho = {"ID", "Nome"};
    global::formataTableWidget(ui->tableWidget_autor, cabecalho);

    for (int i = 0; i < listaAutor.size(); ++i) {
        autor = listaAutor[i];
        ui->tableWidget_autor->insertRow(i);
        ui->tableWidget_autor->setItem(i, 0, new QTableWidgetItem(QString::number(autor.getId())));
        ui->tableWidget_autor->setItem(i, 1, new QTableWidgetItem(autor.getNome()));
        ui->tableWidget_autor->setRowHeight(i, 20);
    }
}

void form_autor::atualiza_table_widget(QString nome)
{
    QVector<Autor> listaAutor;
    AutorController autorController;

    if (global::minimoCaracteres(nome, 3))
    {
        listaAutor = autorController.buscaPorNome(global::colaboradorLogado.getId(), nome);
    }
    else
    {
        listaAutor = autorController.buscaTodos(global::colaboradorLogado.getId());
    }
    form_autor::popula_table_widget(listaAutor);
}

void form_autor::limpa_formulario()
{
    ui->tableWidget_autor->clearSelection();
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_nome->clear();
    ui->label_selected_row->setText("-1");
    ui->lineEdit_pesquisar->setFocus();
    ui->pushButton_incluir->setEnabled(true);
    ui->pushButton_alterar->setEnabled(false);
}

void form_autor::adiciona_autor_table_widget(Autor autor)
{
    int row;

    row = ui->tableWidget_autor->rowCount();
    ui->tableWidget_autor->insertRow(row);
    ui->tableWidget_autor->setItem(row, 0, new QTableWidgetItem(QString::number(autor.getId())));
    ui->tableWidget_autor->setItem(row, 1, new QTableWidgetItem(autor.getNome()));
    ui->tableWidget_autor->setRowHeight(row, 20);
}

void form_autor::altera_autor_table_widget(int row, Autor autor)
{
    ui->tableWidget_autor->item(row, 0)->setText(QString::number(autor.getId()));
    ui->tableWidget_autor->item(row, 1)->setText(autor.getNome());
}

// SLOTS
void form_autor::on_pushButton_pesquisar_clicked()
{
    QString nome;

    nome = ui->lineEdit_pesquisar->text().trimmed();

    if (global::minimoCaracteres(nome, 3))
    {
        form_autor::atualiza_table_widget(nome);
        ui->pushButton_mostrar_todos->setEnabled(true);
        form_autor::limpa_formulario();
    }
    else
    {
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres para pesquisa.");
    }
}

void form_autor::on_pushButton_mostrar_todos_clicked()
{
    form_autor::atualiza_table_widget("");
    ui->pushButton_mostrar_todos->setEnabled(false);
    form_autor::limpa_formulario();
}

void form_autor::on_tableWidget_autor_itemSelectionChanged()
{
    int row, id;
    QString nome;

    row = ui->tableWidget_autor->currentRow();
    id = ui->tableWidget_autor->item(row, 0)->text().toInt();
    nome = ui->tableWidget_autor->item(row, 1)->text();

    ui->label_selected_row->setText(QString::number(row));
    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_nome->setText(nome);

    ui->pushButton_incluir->setEnabled(false);
    ui->pushButton_alterar->setEnabled(true);
}

void form_autor::on_pushButton_incluir_clicked()
{
    QString nome;
    Autor autor;
    AutorController autorController;
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
        autor.setNome(nome);
        autor.setColaborador(global::colaboradorLogado);

        autor = autorController.insere(autor);

        form_autor::adiciona_autor_table_widget(autor);
        QMessageBox::about(this, "", "Cadastrado com sucesso!");
        form_autor::limpa_formulario();
    }
}

void form_autor::on_pushButton_alterar_clicked()
{
    int row, id;
    QString nome;
    Autor autor;
    AutorController autorController;
    QMessageBox::StandardButton resposta;

    row = ui->label_selected_row->text().toInt();
    id = ui->lineEdit_id->text().toInt();
    nome = ui->lineEdit_nome->text().trimmed();

    if (!global::minimoCaracteres(nome, 3))
    {
        QMessageBox::warning(this, "", "Nome deve ter no mínimo 3 caracteres.");
        return;
    }

    resposta = QMessageBox::question(this, "Confirma alteração?", "Tem certeza que quer alterar?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes)
    {
        autor.setId(id);
        autor.setNome(nome);
        autor.setColaborador(global::colaboradorLogado);

        if (autorController.altera(autor))
        {
            form_autor::altera_autor_table_widget(row, autor);
            QMessageBox::about(this, "", "Alterado com sucesso!");
            form_autor::limpa_formulario();
        }
    }
}

void form_autor::on_pushButton_limpar_clicked()
{
    form_autor::limpa_formulario();
}

void form_autor::on_pushButton_fechar_clicked()
{
    close();
}
