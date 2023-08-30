#ifndef TAULATRAMS_H
#define TAULATRAMS_H

#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QPushButton;
class QSqlTableModel;
QT_END_NAMESPACE

//! [0]
class taulaTrams : public QWidget
{
    Q_OBJECT
public:
    explicit taulaTrams(const QString &tableName, QWidget *parent = nullptr);

private slots:
    void submit();

private:
    QPushButton *submitButton;
    QPushButton *revertButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QSqlTableModel *model;
};
//! [0]

#endif

#endif // TAULATRAMS_H
