#include "arbreestructura.h"
#include <QtWidgets>

#include <QtWidgets>

#include "arbreestructura.h"
#include "g_Projecte.h"

enum { DomElementRole = Qt::UserRole + 1 };

Q_DECLARE_METATYPE(QDomElement)

static inline QString titleElement() { return QStringLiteral("title"); }
static inline QString folderElement() { return QStringLiteral("folder"); }
static inline QString bookmarkElement() { return QStringLiteral("bookmark"); }

static inline QString versionAttribute() { return QStringLiteral("version"); }
static inline QString hrefAttribute() { return QStringLiteral("href"); }
static inline QString foldedAttribute() { return QStringLiteral("folded"); }

/*
XbelTree::XbelTree(QWidget *parent)
    : QTreeWidget(parent)
{
    QStringList labels;
    labels << tr("Title") << tr("Location");

    header()->setSectionResizeMode(QHeaderView::Stretch);
    setHeaderLabels(labels);

    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirClosedIcon),
                         QIcon::Normal, QIcon::Off);
    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirOpenIcon),
                         QIcon::Normal, QIcon::On);
    bookmarkIcon.addPixmap(style()->standardPixmap(QStyle::SP_FileIcon));
}
*/
ArbreGpx::ArbreGpx (QWidget *parent) {
    QStringList labels;
    labels << tr("Title") << tr("Location");

    header()->setSectionResizeMode(QHeaderView::Stretch);
    setHeaderLabels(labels);

    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirClosedIcon),
                         QIcon::Normal, QIcon::Off);
    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirOpenIcon),
                         QIcon::Normal, QIcon::On);
    bookmarkIcon.addPixmap(style()->standardPixmap(QStyle::SP_FileIcon));

}



void ArbreGpx::Representa(gProjecte prj) {
    QString txt;

    QTreeWidgetItem branca1;

    branca1= addItem("GPX",prj.Nom);
    for (int n=0; n< prj.LlTrk.count();n++ ) {
        QTreeWidgetItem branca2;
        branca2 = addItem("Track",prj.LlTrk.at(n).name, &branca1);
        for (int m=0; m< prj.LlTrk.at(n).segs.count() ;m++ ) {
            QTreeWidgetItem branca3;
            txt= "HI ha " + QString::number(prj.LlTrk.at(n).segs.at(m).punts.count()) + " punts i ";
            txt += QString::number(prj.LlTrk.at(n).segs.at(m).Distancia()) + "m;  +";
            txt += QString::number(prj.LlTrk.at(n).segs.at(m).Puja()) + "m;  -";
            txt += QString::number(prj.LlTrk.at(n).segs.at(m).Baixa()) + "m";
            branca3 = addItem("Segment",txt, &branca2);

        }

    }

}

QTreeWidgetItem ArbreGpx::addItem(QString name, QString description, QTreeWidgetItem *parent) {
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)

    QTreeWidgetItem *treeItem = new QTreeWidgetItem(this);

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, name);
    treeItem->setText(1, description);
    if (parent != nullptr) {
        parent->addChild(treeItem);
    }

    return *treeItem;
}










/*

#if !defined(QT_NO_CONTEXTMENU) && !defined(QT_NO_CLIPBOARD)
void XbelTree::contextMenuEvent(QContextMenuEvent *event)
{
    const QTreeWidgetItem *item = itemAt(event->pos());
    if (!item)
        return;
    const QString url = item->text(1);
    QMenu contextMenu;
    QAction *copyAction = contextMenu.addAction(tr("Copy Link to Clipboard"));
    QAction *openAction = contextMenu.addAction(tr("Open"));
    QAction *action = contextMenu.exec(event->globalPos());
    if (action == copyAction)
        QGuiApplication::clipboard()->setText(url);
    else if (action == openAction)
        QDesktopServices::openUrl(QUrl(url));
}
#endif // !QT_NO_CONTEXTMENU && !QT_NO_CLIPBOARD

bool XbelTree::read(QIODevice *device)
{
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!domDocument.setContent(device, true, &errorStr, &errorLine,
                                &errorColumn)) {
        QMessageBox::information(window(), tr("DOM Bookmarks"),
                                 tr("Parse error at line %1, column %2:\n%3")
                                     .arg(errorLine)
                                     .arg(errorColumn)
                                     .arg(errorStr));
        return false;
    }

    QDomElement root = domDocument.documentElement();
    if (root.tagName() != "xbel") {
        QMessageBox::information(window(), tr("DOM Bookmarks"),
                                 tr("The file is not an XBEL file."));
        return false;
    } else if (root.hasAttribute(versionAttribute())
               && root.attribute(versionAttribute()) != QLatin1String("1.0")) {
        QMessageBox::information(window(), tr("DOM Bookmarks"),
                                 tr("The file is not an XBEL version 1.0 "
                                    "file."));
        return false;
    }

    clear();

    disconnect(this, &QTreeWidget::itemChanged, this, &XbelTree::updateDomElement);

    QDomElement child = root.firstChildElement(folderElement());
    while (!child.isNull()) {
        parseFolderElement(child);
        child = child.nextSiblingElement(folderElement());
    }

    connect(this, &QTreeWidget::itemChanged, this, &XbelTree::updateDomElement);

    return true;
}

bool XbelTree::write(QIODevice *device) const
{
    const int IndentSize = 4;

    QTextStream out(device);
    domDocument.save(out, IndentSize);
    return true;
}

void XbelTree::updateDomElement(const QTreeWidgetItem *item, int column)
{
    QDomElement element = qvariant_cast<QDomElement>(item->data(0, DomElementRole));
    if (!element.isNull()) {
        if (column == 0) {
            QDomElement oldTitleElement = element.firstChildElement(titleElement());
            QDomElement newTitleElement = domDocument.createElement(titleElement());

            QDomText newTitleText = domDocument.createTextNode(item->text(0));
            newTitleElement.appendChild(newTitleText);

            element.replaceChild(newTitleElement, oldTitleElement);
        } else {
            if (element.tagName() == bookmarkElement())
                element.setAttribute(hrefAttribute(), item->text(1));
        }
    }
}

void XbelTree::parseFolderElement(const QDomElement &element,
                                  QTreeWidgetItem *parentItem)
{
    QTreeWidgetItem *item = createItem(element, parentItem);

    QString title = element.firstChildElement(titleElement()).text();
    if (title.isEmpty())
        title = QObject::tr("Folder");

    item->setFlags(item->flags() | Qt::ItemIsEditable);
    item->setIcon(0, folderIcon);
    item->setText(0, title);

    bool folded = (element.attribute(foldedAttribute()) != QLatin1String("no"));
    item->setExpanded(!folded);

    QDomElement child = element.firstChildElement();
    while (!child.isNull()) {
        if (child.tagName() == folderElement()) {
            parseFolderElement(child, item);
        } else if (child.tagName() == bookmarkElement()) {
            QTreeWidgetItem *childItem = createItem(child, item);

            QString title = child.firstChildElement(titleElement()).text();
            if (title.isEmpty())
                title = QObject::tr("Folder");

            childItem->setFlags(item->flags() | Qt::ItemIsEditable);
            childItem->setIcon(0, bookmarkIcon);
            childItem->setText(0, title);
            childItem->setText(1, child.attribute(hrefAttribute()));
        } else if (child.tagName() == QLatin1String("separator")) {
            QTreeWidgetItem *childItem = createItem(child, item);
            childItem->setFlags(item->flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsEditable));
            childItem->setText(0, QString(30, u'\xB7'));
        }
        child = child.nextSiblingElement();
    }
}

QTreeWidgetItem *XbelTree::createItem(const QDomElement &element,
                                      QTreeWidgetItem *parentItem)
{
    QTreeWidgetItem *item;
    if (parentItem) {
        item = new QTreeWidgetItem(parentItem);
    } else {
        item = new QTreeWidgetItem(this);
    }
    item->setData(0, DomElementRole, QVariant::fromValue(element));
    return item;
}
*/
