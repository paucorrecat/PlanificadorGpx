#ifndef PLANIFICADOR_H
#define PLANIFICADOR_H

#include <QWidget>
#include <QSplitter>
#include <QDockWidget>
#include <QListWidget>

class Planificador : public QDockWidget
{
    Q_OBJECT
public:
    explicit Planificador(QWidget *parent = nullptr);

private:
    QListWidget *zonaNW, *zonaNE, *zonaS;
    QSplitter slp1, spl2;

signals:

};

#endif // PLANIFICADOR_H
