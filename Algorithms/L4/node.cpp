#include "edge.h"
#include "node.h"
#include "graphwidget.h"

#include <qmath.h>
#include <memory>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include <QPainter>
#include <QStyleOption>
#include <QColorDialog>
#include <QDebug>
#include <QMenu>
#include <QInputDialog>
#include <QMessageBox>
#include <QByteArray>
#include <QString>


//! [0]
Node::Node(GraphWidget *graphWidget)
    : graph(graphWidget)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}
//! [0]

//! [1]
void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}
//! [1]

//! [2]
void Node::calculateForces()
{
    if (!scene() || scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }
//! [2]

//! [3]
    double av = graph->gr->AverageWeight();
    // Sum up all forces pushing this item away
    qreal xvel = 0;
    qreal yvel = 0;
    foreach (QGraphicsItem *item, scene()->items()) {
        Node *node = qgraphicsitem_cast<Node *>(item);
        if (!node)
            continue;

        QPointF vec = mapToItem(node, 0, 0);
        qreal dx = vec.x();
        qreal dy = vec.y();
        double l = 0.5 * (dx * dx + dy * dy);
        if (l > 0) {
            xvel += (dx * 150.0) / l;
            yvel += (dy * 150.0) / l;
        }
    }
//! [3]

//! [4]
    // Now subtract all forces pulling items together
    double weight = (edgeList.size() + 1) * 20;
    foreach (Edge *edge, edgeList) {
        QPointF vec;
        if (edge->sourceNode() == this)
            vec = mapToItem(edge->destNode(), 0, 0);
        else
            vec = mapToItem(edge->sourceNode(), 0, 0);
        xvel -= (vec.x() / weight) / sqrt(edge->weight_temp / av);
        yvel -= (vec.y() / weight) / sqrt(edge->weight_temp / av);
    }
//! [4]

//! [5]
    if (!gravity){
        xvel = yvel = 0;
    }
    else if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
        xvel = yvel = 0;
//! [5]

//! [6]
    QRectF sceneRect = scene()->sceneRect();
    newPos = pos() + QPointF(xvel, yvel);
    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + 10), sceneRect.right() - 10));
    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + 10), sceneRect.bottom() - 10));
}
//! [6]

//! [7]
bool Node::advance()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}
//! [7]

//! [8]
QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -15 - adjust, -15 - adjust, 33 + adjust, 33 + adjust);
}
//! [8]

//! [9]
QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-15, -15, 30, 30);
    return path;
}
//! [9]

//! [10]
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-12, -12, 30, 30);
    QColor grad0t = grad0;
    QColor grad1t = grad1;
    QRadialGradient gradient(-5, -5, 15);
    if (option->state & QStyle::State_Sunken) {
        grad1t = grad0.light(120);
        grad0t = grad1.light(120);
    } else if (option->state & QStyle::State_Selected){
        grad0t = Qt::blue;
        grad1t = Qt::darkBlue;
    }
    if (graph->gr->marked)
        if (graph->gr->marked->node == this){
            grad0t = Qt::red;
            grad1t = Qt::darkRed;
    }
    if (graph->gr->source)
        if (graph->gr->source->node == this){
            grad0t = Qt::green;
            grad1t = Qt::darkGreen;
        }
    if (graph->gr->sink)
        if (graph->gr->sink->node == this){
            grad0t = Qt::cyan;
            grad1t = Qt::darkCyan;
        }
    gradient.setColorAt(0, grad0t);
    gradient.setColorAt(1, grad1t);
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-15, -15, 30, 30);

    QString temp(name);
    QFont font = painter->font();
    font.setBold(true);
    int fs = 16 - 5.5*log(temp.length());
    font.setPointSize(fs);
    painter->setFont(font);
    QColor col(255 - grad0t.red(), 255 - grad0t.green(), 255 - grad0t.blue());
    painter->setPen(QPen(col, 0));
    painter->drawText(0-temp.length()*fs/2.5, 0+fs/2, temp);
}


//! [10]

//! [11]
QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, edgeList)
            edge->adjust();
        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    std::unique_ptr<QMenu> menu(new QMenu(graph));
    QAction* sourceAction = menu->addAction("Установить исток");
    QAction* sinkAction = menu->addAction("Установить сток");
    QAction* colorAction = menu->addAction("Изменить цвет");
    QAction* renameAction = menu->addAction("Переименовать");
    QAction* linkAction = menu->addAction("Связать с этим");
    QAction* weightAction = menu->addAction("Изменить вес (к этому)");
    QAction* freeAction = menu->addAction("Удалить связи");
    QAction* deleteAction = menu->addAction("Удалить");
    weightAction->setEnabled(graph->gr->weights);
    QAction* selectedAction = menu->exec(event->screenPos());
    if (selectedAction == sourceAction){
        Node* temp = nullptr;
        if (graph->gr->source){
            temp = graph->gr->source->node;
        }
        graph->gr->source = graph->gr->FindElem(name);
        this->update();
        if (temp)
            temp->update();
    }
    else if(selectedAction == sinkAction){
        Node* temp = nullptr;
        if (graph->gr->sink){
            temp = graph->gr->sink->node;
        }
        graph->gr->sink = graph->gr->FindElem(name);
        if (temp)
            temp->update();
        this->update();
    }
    else if (selectedAction == colorAction){
        QColorDialog dia;
        dia.exec();
        grad0 = dia.currentColor();
        grad1 = grad0.darker(300);
        update();
    }
    else if(selectedAction == renameAction){
        bool ok;
        QString name2 = QInputDialog::getText(graph, "Добавить связь", "Введите имя", QLineEdit::Normal, "", &ok);
        QByteArray arr2 = name2.toLocal8Bit();
        char* cname2 = arr2.data();
        if (graph->gr->FindElem(cname2)){
            QMessageBox msg;
            msg.setText("Элемент с таким именем уже существует");
            msg.exec();
        }
        else
            graph->gr->RenameElem(name, cname2);
        update();

    }
    else if (selectedAction == deleteAction){
        graph->gr->RemoveElem(name);
    }
    else if (selectedAction == freeAction){
        graph->gr->RemoveEdges(graph->gr->FindElem(name));
    }
    else if (selectedAction == linkAction){
        int weight = 0;
        foreach (QGraphicsItem *item, graph->scene()->items()) {
            if (Node *node = qgraphicsitem_cast<Node *>(item)){
                if (node->isSelected()){
                    if (weight == 0){
                        if (graph->gr->weights)
                            weight = QInputDialog::getInt(graph, "Добавить связь", "Введите вес", 1);
                        else
                            weight = 1;
                    }
                    graph->gr->AddEdge(graph->gr->FindElem(node->name), graph->gr->FindElem(name), weight);
                }
            }
        }
    }
    else if (selectedAction == weightAction){
        int weight = 0;
        foreach (QGraphicsItem *item, graph->scene()->items()) {
            if (Node *node = qgraphicsitem_cast<Node *>(item)){
                if (node->isSelected()){
                    if (weight == 0){
                        weight = QInputDialog::getInt(graph, "Изменить вес", "Введите вес", 1);
                    }
                    graph->gr->ChangeWeight(graph->gr->FindElem(node->name), graph->gr->FindElem(name), weight);
                }
            }
        }
    }
    graph->mw->update_matr();
}

//! [11]

//! [12]
void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
//! [12]
