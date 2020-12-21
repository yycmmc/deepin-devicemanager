#include "DeviceTableWidgetDelegate.h"

#include <QPainter>


#include <DApplication>
#include <DStyle>
#include <DApplicationHelper>
#include <DFontSizeManager>

#include <QDebug>

DWIDGET_USE_NAMESPACE

DeviceTableWidgetDelegate::DeviceTableWidgetDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void DeviceTableWidgetDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setOpacity(1);

    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    QWidget *wnd = DApplication::activeWindow();
    DPalette::ColorGroup cg;
    if (!(opt.state & DStyle::State_Enabled)) {
        cg = DPalette::Disabled;
    } else {
        if (!wnd) {
            cg = DPalette::Inactive;
        } else {
            cg = DPalette::Active;
        }
    }

    DStyle *style = dynamic_cast<DStyle *>(DApplication::style());

    DApplicationHelper *dAppHelper = DApplicationHelper::instance();
    DPalette palette = dAppHelper->applicationPalette();
    QBrush background;

    if (opt.features & QStyleOptionViewItem::Alternate) {
        background = palette.color(cg, DPalette::AlternateBase);
        qDebug() << "AlternateBase";
    } else {
        background = palette.color(cg, DPalette::Base);
        qDebug() << "Base";
    }

    QRect rect = opt.rect;
    QPainterPath path;
    QRect rectpath = rect;
    path.addRect(rectpath);
    painter->fillPath(path, background);
    // 绘制文字信息
    QRect textRect = rectpath;
    int margin = style->pixelMetric(DStyle::PM_ContentsMargins, &option);   // 边距

    textRect.setX(textRect.x() + margin);
    textRect.setWidth(textRect.width() - margin);

    QFont fo;
    // 表格第一列，字体加粗
    if (index.column() == 0) {
        fo = opt.font;
        fo.setWeight(63);
    } else {
        fo = DFontSizeManager::instance()->t8();
    }

    painter->setFont(fo);
    QFontMetrics fm(fo);
    QString text = fm.elidedText(opt.text, opt.textElideMode, textRect.width());

    painter->drawText(textRect, Qt::TextSingleLine | static_cast<int>(opt.displayAlignment), text);


    painter->restore();
}

QSize DeviceTableWidgetDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(std::max(50, size.height()));

    if (index.column()) {
        size.setWidth(std::max(150, size.width()));
    }
    return size;
}

void DeviceTableWidgetDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    option->showDecorationSelected = true;
    bool ok = false;
    if (index.data(Qt::TextAlignmentRole).isValid()) {
        uint value = index.data(Qt::TextAlignmentRole).toUInt(&ok);
        option->displayAlignment = static_cast<Qt::Alignment>(value);
    }

    if (!ok)
        option->displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;
    option->textElideMode = Qt::ElideRight;
    option->features = QStyleOptionViewItem::HasDisplay;
    if (index.row() % 2 == 0)
        option->features |= QStyleOptionViewItem::Alternate;
    if (index.data(Qt::DisplayRole).isValid())
        option->text = index.data().toString();
}
