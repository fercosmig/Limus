#include "form_grupo.h"
#include "global.h"
#include "grupoController.h"
#include "ui_form_grupo.h"

#include <QMessageBox>

form_grupo::form_grupo(QWidget *parent) : QDialog(parent), ui(new Ui::form_grupo)
{
    ui->setupUi(this);

    form_grupo::inicializa_form_grupo();
}

form_grupo::~form_grupo()
{
    delete ui;
}

// MEUS METODOS
void form_grupo::inicializa_form_grupo()
{
    form_grupo::atualiza_table_widget("");
    form_grupo::carrega_comboBox_sigla();

    ui->label_selected_row->setVisible(false);
}

void form_grupo::popula_table_widget(QVector<Grupo> listaGrupo)
{
    Grupo grupo;
    QStringList cabecalho;

    cabecalho = {"ID", "Nome", "Sigla"};
    global::formataTableWidget(ui->tableWidget_grupo, cabecalho);

    for (int i = 0; i < listaGrupo.size(); ++i) {
        grupo = listaGrupo[i];
        ui->tableWidget_grupo->insertRow(i);
        ui->tableWidget_grupo->setItem(i, 0, new QTableWidgetItem(QString::number(grupo.getId())));
        ui->tableWidget_grupo->setItem(i, 1, new QTableWidgetItem(grupo.getNome()));
        ui->tableWidget_grupo->setItem(i, 2, new QTableWidgetItem(grupo.getSigla()));
        ui->tableWidget_grupo->setRowHeight(i, 20);
    }
}

void form_grupo::atualiza_table_widget(QString nome)
{
    QVector<Grupo> listaGrupo;
    GrupoController grupoController;

    if (global::minimoCaracteres(nome, 3))
    {
        listaGrupo = grupoController.buscaPorNome(nome);
    }
    else
    {
        listaGrupo = grupoController.buscaTodos();
    }
    form_grupo::popula_table_widget(listaGrupo);
}

void form_grupo::limpa_formulario()
{
    ui->tableWidget_grupo->clearSelection();
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_nome->clear();
    ui->comboBox_sigla->setCurrentIndex(0);
    ui->label_selected_row->setText("-1");
    ui->lineEdit_pesquisar->setFocus();
    ui->pushButton_incluir->setEnabled(true);
    ui->pushButton_alterar->setEnabled(false);
}

void form_grupo::carrega_comboBox_sigla()
{
    QStringList siglas;

    siglas = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "W", "V", "X", "Y", "Z"};

    ui->comboBox_sigla->addItem("Selecione", 0);

    for (int i = 0; i < siglas.size(); ++i)
    {
        ui->comboBox_sigla->addItem(siglas[i], i + 1);
    }
}

void form_grupo::adiciona_grupo_table_widget(Grupo grupo)
{
    int row;

    row = ui->tableWidget_grupo->rowCount();
    ui->tableWidget_grupo->insertRow(row);
    ui->tableWidget_grupo->setItem(row, 0, new QTableWidgetItem(QString::number(grupo.getId())));
    ui->tableWidget_grupo->setItem(row, 1, new QTableWidgetItem(grupo.getNome()));
    ui->tableWidget_grupo->setItem(row, 2, new QTableWidgetItem(grupo.getSigla()));
    ui->tableWidget_grupo->setRowHeight(row, 20);
}

void form_grupo::altera_grupo_table_widget(int row, Grupo grupo)
{
    ui->tableWidget_grupo->item(row, 1)->setText(grupo.getNome());
    ui->tableWidget_grupo->item(row, 2)->setText(grupo.getSigla());
}

// SLOTS

void form_grupo::on_pushButton_pesquisar_clicked()
{
    QString nome;

    nome = ui->lineEdit_pesquisar->text().trimmed();

    if (global::minimoCaracteres(nome, 3))
    {
        form_grupo::atualiza_table_widget(nome);
        ui->pushButton_mostrar_todos->setEnabled(true);
        form_grupo::limpa_formulario();
    }
    else
    {
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres para pesquisa.");
        ui->lineEdit_pesquisar->setFocus();
    }
}

void form_grupo::on_pushButton_mostrar_todos_clicked()
{
    form_grupo::atualiza_table_widget("");
    ui->pushButton_mostrar_todos->setEnabled(false);
    form_grupo::limpa_formulario();
}

void form_grupo::on_tableWidget_grupo_itemSelectionChanged()
{
    int row, id;
    QString nome, sigla;

    row = ui->tableWidget_grupo->currentRow();
    id = ui->tableWidget_grupo->item(row, 0)->text().toInt();
    nome = ui->tableWidget_grupo->item(row, 1)->text();
    sigla = ui->tableWidget_grupo->item(row, 2)->text();

    ui->label_selected_row->setText(QString::number(row));
    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_nome->setText(nome);
    ui->comboBox_sigla->setCurrentText(sigla);

    ui->pushButton_incluir->setEnabled(false);
    ui->pushButton_alterar->setEnabled(true);
}

void form_grupo::on_pushButton_limpar_clicked()
{
    form_grupo::limpa_formulario();
}

void form_grupo::on_pushButton_fechar_clicked()
{
    close();
}

void form_grupo::on_pushButton_incluir_clicked()
{
    int selected;
    QString nome, sigla;
    Grupo grupo;
    GrupoController grupoController;
    QMessageBox::StandardButton resposta;

    selected = ui->comboBox_sigla->currentData().toInt();
    nome = ui->lineEdit_nome->text().trimmed();
    sigla = ui->comboBox_sigla->currentText();

    if (!global::minimoCaracteres(nome, 3))
    {
        QMessageBox::warning(this, "", "Nome deve ter no mínimo 3 caracteres.");
        return;
    }

    if (selected == 0)
    {
        QMessageBox::warning(this, "", "Selecione uma sigla.");
        return;
    }

    if (grupoController.buscaDuplicidadeSigla(sigla))
    {
        QMessageBox::warning(this, "", "Sigla já existe no banco de dados.");
        return;
    }

    resposta = QMessageBox::question(this, "Confirma inclusão?", "Tem certeza que quer incluir?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes)
    {
        grupo.setNome(nome);
        grupo.setSigla(sigla);

        grupo = grupoController.insere(grupo);

        form_grupo::adiciona_grupo_table_widget(grupo);
        QMessageBox::about(this, "", "Cadastrado com sucesso!");
        form_grupo::limpa_formulario();
    }
}

void form_grupo::on_pushButton_alterar_clicked()
{
    int row, selected, id;
    QString nome, sigla, siglaAntes;
    Grupo grupo;
    GrupoController grupoController;
    QMessageBox::StandardButton resposta;

    row = ui->label_selected_row->text().toInt();
    selected = ui->comboBox_sigla->currentData().toInt();
    id = ui->lineEdit_id->text().toInt();
    nome = ui->lineEdit_nome->text().trimmed();
    sigla = ui->comboBox_sigla->currentText();
    siglaAntes = ui->tableWidget_grupo->item(row, 2)->text();

    if (!global::minimoCaracteres(nome, 3))
    {
        QMessageBox::warning(this, "", "Nome deve ter no mínimo 3 caracteres.");
        return;
    }

    if (selected == 0)
    {
        QMessageBox::warning(this, "", "Selecione uma sigla.");
        return;
    }

    if (siglaAntes != sigla)
    {
        if (grupoController.buscaDuplicidadeSigla(sigla))
        {
            QMessageBox::warning(this, "", "Sigla já existe no banco de dados.");
            return;
        }
    }

    resposta = QMessageBox::question(this, "Confirma alteração?", "Tem certeza que quer alterar?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes)
    {
        grupo.setId(id);
        grupo.setNome(nome);
        grupo.setSigla(sigla);

        if (grupoController.altera(grupo))
        {
            form_grupo::altera_grupo_table_widget(row, grupo);
            QMessageBox::about(this, "", "Alterado com sucesso.");
            form_grupo::limpa_formulario();
        }
    }
}
