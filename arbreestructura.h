#ifndef ARBREESTRUCTURA_H
#define ARBREESTRUCTURA_H

#include <QDomDocument>
#include <QIcon>
#include <QTreeWidget>

class ArbreEstructura : public QTreeWidget
{
    Q_OBJECT

public:
    explicit ArbreEstructura(QWidget *parent = nullptr);

private:
    void parseFolderElement(const QTreeWidgetItem &element,
                            QTreeWidgetItem *parentItem = nullptr);
    QTreeWidgetItem *createItem(const QDomElement &element,
                                QTreeWidgetItem *parentItem = nullptr);

    QDomDocument domDocument;
    QIcon folderIcon;
    QIcon bookmarkIcon;


};

#endif // ARBREESTRUCTURA_H
