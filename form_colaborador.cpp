#include "colaboradorController.h"
#include "form_colaborador.h"
#include "global.h"
#include "grupoController.h"
#include "ui_form_colaborador.h"

#include <QMessageBox>

form_colaborador::form_colaborador(QWidget *parent) : QDialog(parent), ui(new Ui::form_colaborador)
{
    ui->setupUi(this);

    form_colaborador::inicializaFormColaborador();
}

form_colaborador::~form_colaborador()
{
    delete ui;
}

// MEUS MÉTODOS
void form_colaborador::inicializaFormColaborador()
{
    form_colaborador::atualizaTableWidget("");
    form_colaborador::carregaComboBoxGrupo();

    ui->label_selected_row->setVisible(false);
}

void form_colaborador::populaTableWidget(QVector<Colaborador> listaColaborador)
{
    Colaborador colaborador;
    QStringList cabecalho;

    cabecalho = {"ID", "Nome", "E-mail", "Senha", "ID Grupo", "Nome Grupo", "Sigla"};
    global::formataTableWidget(ui->tableWidget_colaborador, cabecalho);

    for (int i = 0; i < listaColaborador.size(); ++i) {
        colaborador = listaColaborador[i];
        ui->tableWidget_colaborador->insertRow(i);
        ui->tableWidget_colaborador->setItem(i, 0, new QTableWidgetItem(QString::number(colaborador.getId())));
        ui->tableWidget_colaborador->setItem(i, 1, new QTableWidgetItem(colaborador.getNome()));
        ui->tableWidget_colaborador->setItem(i, 2, new QTableWidgetItem(colaborador.getEmail()));
        ui->tableWidget_colaborador->setItem(i, 3, new QTableWidgetItem(colaborador.getSenha()));
        ui->tableWidget_colaborador->setItem(i, 4, new QTableWidgetItem(QString::number(colaborador.getGrupo().getId())));
        ui->tableWidget_colaborador->setItem(i, 5, new QTableWidgetItem(colaborador.getGrupo().getNome()));
        ui->tableWidget_colaborador->setItem(i, 6, new QTableWidgetItem(colaborador.getGrupo().getSigla()));
        ui->tableWidget_colaborador->setRowHeight(i, 20);
    }
    ui->tableWidget_colaborador->setColumnHidden(3, true);
    ui->tableWidget_colaborador->setColumnHidden(4, true);
}

void form_colaborador::atualizaTableWidget(QString nome_email)
{
    QVector<Colaborador> listaColaborador;
    ColaboradorController colaboradorController;

    if (global::minimoCaracteres(nome_email, 3))
    {
        listaColaborador = colaboradorController.buscaPorNomeEmail(nome_email);
    }
    else
    {
        listaColaborador = colaboradorController.buscaTodos();
    }
    form_colaborador::populaTableWidget(listaColaborador);
}

void form_colaborador::limpaFormulario()
{
    ui->tableWidget_colaborador->clearSelection();
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_nome->clear();
    ui->lineEdit_email->clear();
    ui->lineEdit_senha->clear();
    ui->comboBox_grupo->setCurrentIndex(0);
    ui->label_selected_row->setText("-1");
    ui->lineEdit_pesquisar->setFocus();
    ui->pushButton_incluir->setEnabled(true);
    ui->pushButton_alterar->setEnabled(false);
}

void form_colaborador::carregaComboBoxGrupo()
{
    Grupo grupo;
    QVector<Grupo> listaGrupo;
    GrupoController grupoController;

    listaGrupo = grupoController.buscaTodos();

    ui->comboBox_grupo->addItem("Selecione", 0);

    for (int i = 0; i < listaGrupo.size(); ++i)
    {
        grupo = listaGrupo[i];
        ui->comboBox_grupo->addItem(grupo.getNome(), grupo.getId());
    }
}

void form_colaborador::adicionaColaboradorTableWidget(Colaborador colaborador)
{
    int row;

    row = ui->tableWidget_colaborador->rowCount();
    ui->tableWidget_colaborador->insertRow(row);
    ui->tableWidget_colaborador->setItem(row, 0, new QTableWidgetItem(QString::number(colaborador.getId())));
    ui->tableWidget_colaborador->setItem(row, 1, new QTableWidgetItem(colaborador.getNome()));
    ui->tableWidget_colaborador->setItem(row, 2, new QTableWidgetItem(colaborador.getEmail()));
    ui->tableWidget_colaborador->setItem(row, 3, new QTableWidgetItem(colaborador.getSenha()));
    ui->tableWidget_colaborador->setItem(row, 4, new QTableWidgetItem(QString::number(colaborador.getGrupo().getId())));
    ui->tableWidget_colaborador->setItem(row, 5, new QTableWidgetItem(colaborador.getGrupo().getNome()));
    ui->tableWidget_colaborador->setItem(row, 6, new QTableWidgetItem(colaborador.getGrupo().getSigla()));
    ui->tableWidget_colaborador->setRowHeight(row, 20);
}

void form_colaborador::alteraColaboradorTableWidget(int row, Colaborador colaborador)
{
    ui->tableWidget_colaborador->item(row, 1)->setText(colaborador.getNome());
    ui->tableWidget_colaborador->item(row, 2)->setText(colaborador.getEmail());
    ui->tableWidget_colaborador->item(row, 3)->setText(colaborador.getSenha());
    ui->tableWidget_colaborador->item(row, 4)->setText(QString::number(colaborador.getGrupo().getId()));
    ui->tableWidget_colaborador->item(row, 5)->setText(colaborador.getGrupo().getNome());
    ui->tableWidget_colaborador->item(row, 6)->setText(colaborador.getGrupo().getSigla());
}

Grupo form_colaborador::converteComboBoxGrupo()
{
    int id;
    Grupo grupo;
    GrupoController grupoController;

    id = ui->comboBox_grupo->currentData().toInt();
    if (id == 0)
    {
        grupo.setId(0);
    }
    else
    {
        grupo = grupoController.buscaPorId(id);
    }
    return grupo;
}

//SLOTS
void form_colaborador::on_pushButton_pesquisar_clicked()
{
    QString nome_email;
    nome_email = ui->lineEdit_pesquisar->text().trimmed();

    if (global::minimoCaracteres(nome_email, 3))
    {
        form_colaborador::atualizaTableWidget(nome_email);
        ui->pushButton_mostrar_todos->setEnabled(true);
        form_colaborador::limpaFormulario();
    }
    else
    {
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres para pesuisa.");
        ui->lineEdit_pesquisar->setFocus();
    }
}

void form_colaborador::on_pushButton_mostrar_todos_clicked()
{
    form_colaborador::atualizaTableWidget("");
    ui->pushButton_mostrar_todos->setEnabled(false);
    form_colaborador::limpaFormulario();
}

void form_colaborador::on_tableWidget_colaborador_itemSelectionChanged()
{
    int row, id;
    QString nome, email, senha, nomeGrupo;

    row = ui->tableWidget_colaborador->currentRow();
    id = ui->tableWidget_colaborador->item(row, 0)->text().toInt();
    nome = ui->tableWidget_colaborador->item(row, 1)->text();
    email = ui->tableWidget_colaborador->item(row, 2)->text();
    senha = ui->tableWidget_colaborador->item(row, 3)->text();
    nomeGrupo = ui->tableWidget_colaborador->item(row, 5)->text();

    ui->label_selected_row->setText(QString::number(row));
    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_nome->setText(nome);
    ui->lineEdit_email->setText(email);
    ui->lineEdit_senha->setText(senha);
    ui->comboBox_grupo->setCurrentText(nomeGrupo);

    ui->pushButton_incluir->setEnabled(false);
    ui->pushButton_alterar->setEnabled(true);
}

void form_colaborador::on_pushButton_incluir_clicked()
{
    int id_grupo;
    QString nome, email, senha;
    Grupo grupo;
    Colaborador colaborador;
    ColaboradorController colaboradorController;
    QMessageBox::StandardButton resposta;

    nome = ui->lineEdit_nome->text().trimmed();
    email = ui->lineEdit_email->text().trimmed();
    senha = ui->lineEdit_senha->text().trimmed();
    id_grupo = ui->comboBox_grupo->currentData().toInt();

    if (!global::minimoCaracteres(nome, 3))
    {
        QMessageBox::warning(this, "", "Nome deve ter no mínimo 3 caracteres.");
        return;
    }

    if (!global::minimoCaracteres(email, 7))
    {
        QMessageBox::warning(this, "", "E-mail deve ter no mínimo 7 caracteres.");
        return;
    }

    if (!global::minimoCaracteres(senha, 3))
    {
        QMessageBox::warning(this, "", "Senha deve ter no mínimo 3 caracteres.");
        return;
    }

    if (id_grupo == 0)
    {
        QMessageBox::warning(this, "", "Selecione um grupo.");
        return;
    }

    if (colaboradorController.buscaDuplicidadeEmail(email))
    {
        QMessageBox::warning(this, "", "E-mail já existe no bando de dados.");
        return;
    }

    resposta = QMessageBox::question(this, "Confirma inclusão?", "Tem certeza que quer incluir?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes)
    {
        grupo = form_colaborador::converteComboBoxGrupo();

        colaborador.setNome(nome);
        colaborador.setEmail(email);
        colaborador.setSenha(senha);
        colaborador.setGrupo(grupo);

        colaborador = colaboradorController.insere(colaborador);

        form_colaborador::adicionaColaboradorTableWidget(colaborador);
        QMessageBox::about(this, "", "Cadastrado com sucesso!");
        form_colaborador::limpaFormulario();
    }
}

void form_colaborador::on_pushButton_alterar_clicked()
{
    int row, id, id_grupo;
    QString nome, email, senha, emailAntes;
    Grupo grupo;
    Colaborador colaborador;
    ColaboradorController colaboradorController;
    QMessageBox::StandardButton resposta;

    row = ui->label_selected_row->text().toInt();
    id = ui->lineEdit_id->text().toInt();
    nome = ui->lineEdit_nome->text().trimmed();
    email = ui->lineEdit_email->text().trimmed();
    senha = ui->lineEdit_senha->text().trimmed();
    id_grupo = ui->comboBox_grupo->currentData().toInt();
    emailAntes = ui->tableWidget_colaborador->item(row, 2)->text();

    if (!global::minimoCaracteres(nome, 3))
    {
        QMessageBox::warning(this, "", "Nome deve ter no mínimo 3 caracteres.");
        return;
    }

    if (!global::minimoCaracteres(email, 7))
    {
        QMessageBox::warning(this, "", "E-mail deve ter no mínimo 7 caracteres.");
        return;
    }

    if (!global::minimoCaracteres(senha, 3))
    {
        QMessageBox::warning(this, "", "Senha deve ter no mínimo 3 caracteres.");
        return;
    }

    if (id_grupo == 0)
    {
        QMessageBox::warning(this, "", "Selecione um grupo.");
        return;
    }

    if (emailAntes != email)
    {
        if (colaboradorController.buscaDuplicidadeEmail(email))
        {
            QMessageBox::warning(this, "", "E-mail já existe no banco de dados.");
            return;
        }
    }

    resposta = QMessageBox::question(this, "Confirma alteração?", "Tem certeza que quer alterar?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes)
    {
        grupo = form_colaborador::converteComboBoxGrupo();

        colaborador.setId(id);
        colaborador.setNome(nome);
        colaborador.setEmail(email);
        colaborador.setSenha(senha);
        colaborador.setGrupo(grupo);

        if (colaboradorController.altera(colaborador))
        {
            form_colaborador::alteraColaboradorTableWidget(row, colaborador);
            QMessageBox::about(this, "", "Alterado com sucesso.");
            form_colaborador::limpaFormulario();
        }
    }
}

void form_colaborador::on_pushButton_limpar_clicked()
{
    form_colaborador::limpaFormulario();
}

void form_colaborador::on_pushButton_fechar_clicked()
{
    close();
}
