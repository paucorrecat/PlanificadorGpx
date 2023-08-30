#ifndef ARBREESTRUCTURA_H
#define ARBREESTRUCTURA_H

#include <QDomDocument>
#include <QIcon>
#include <QTreeWidget>
#include "g_Projecte.h"

class ArbreGpx : public QTreeWidget
{
    Q_OBJECT

public:
    ArbreGpx(QWidget *parent = nullptr);
    void Representa(gProjecte prj);


/*
protected:
#if !defined(QT_NO_CONTEXTMENU) && !defined(QT_NO_CLIPBOARD)
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif
*/

//private slots:
//    void updateDomElement(const QTreeWidgetItem *item, int column);

private:

    QIcon folderIcon;
    QIcon bookmarkIcon;

    QTreeWidgetItem addItem(QString name, QString description,QTreeWidgetItem *parent = nullptr);

};

#endif // ARBREESTRUCTURA_H
