
#include <QtWidgets>
#include <QtSql>

#include "dbconnection.h"
#include "taulaTrams.h"

//! [0]
taulaTrams::taulaTrams(const gProjecte &prj, QWidget *parent)
    : QWidget(parent)
{

    if (!createConnection()) {
        QMessageBox::critical(nullptr, QObject::tr("No em puc connectar a la base de dades"),
                              QObject::tr("Unable to establish a database connection.\n"
                                          "This example needs SQLite support. Please read "
                                          "the Qt SQL driver documentation for information how "
                                          "to build it.\n\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }


    QSqlQuery query;
    query.exec("create table tracks (id int primary key, "
               "nom varchar(20), punts double, dist double, puja double, baixa double)");
    QString values;
    for (int n=0; n< prj.LlTrk.count(); n++) {
        values = "insert into tracks values(";
        values += QString::number(n)+ ", '" ;
        values += prj.LlTrk.at(n).name+ "', " ;
        values += QString::number(prj.LlTrk.at(n).NumPunts())+ ", " ;
        values += QString::number(prj.LlTrk.at(n).Distancia())+ ", " ;
        values += QString::number(prj.LlTrk.at(n).Puja())+ ", " ;
        values += QString::number(prj.LlTrk.at(n).Baixa()) + ")" ;
        query.exec (values);
    }

    //query.exec("insert into tracks values(102, 'Prova3', 123)");


    model = new QSqlTableModel(this);
    model->setTable("tracks");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, tr("Punts"));
    model->setHeaderData(3, Qt::Horizontal, tr("Distància"));
        model->setHeaderData(4, Qt::Horizontal, tr("Puja"));
    model->setHeaderData(5, Qt::Horizontal, tr("Baixa"));





    //! [0] //! [1]
    QTableView *view = new QTableView;
    view->setModel(model);
    view->resizeColumnsToContents();
    //! [1]

    //! [2]
    submitButton = new QPushButton(tr("Submit"));
    submitButton->setDefault(true);
    revertButton = new QPushButton(tr("&Revert"));
    quitButton = new QPushButton(tr("Quit"));

    buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);
    //! [2]

    //! [3]
    connect(submitButton, &QPushButton::clicked, this, &taulaTrams::submit);
    connect(revertButton, &QPushButton::clicked,  model, &QSqlTableModel::revertAll);
    connect(quitButton, &QPushButton::clicked, this, &taulaTrams::close);
    //! [3]

    //! [4]
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(view);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Cached Table"));



}
//! [4]

void taulaTrams::CarregaTrams(gProjecte prj) {

}



//! [5]
void taulaTrams::submit()
{
    model->database().transaction();
    if (model->submitAll()) {
        model->database().commit();
    } else {
        model->database().rollback();
        QMessageBox::warning(this, tr("Cached Table"),
                             tr("The database reported an error: %1")
                                 .arg(model->lastError().text()));
    }
}
//! [5]
