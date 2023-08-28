#include "arbreestructura.h"
#include <QtWidgets>

ArbreEstructura::ArbreEstructura(QWidget *parent)
    : QTreeWidget(parent)
{
    QStringList labels;
    labels << tr("Tipus") << tr("Dades");

    header()->setSectionResizeMode(QHeaderView::Stretch);
    setHeaderLabels(labels);

    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirClosedIcon),
                         QIcon::Normal, QIcon::Off);
    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirOpenIcon),
                         QIcon::Normal, QIcon::On);
    bookmarkIcon.addPixmap(style()->standardPixmap(QStyle::SP_FileIcon));

}
/*

ArbreEstructura::AfegirFill(QString Tipus, QString Dades) {

}
*/
