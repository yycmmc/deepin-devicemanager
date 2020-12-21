#ifndef DEVICETABLEWIDGETDELEGATE_H
#define DEVICETABLEWIDGETDELEGATE_H

#include <QStyledItemDelegate>

class DeviceTableWidgetDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DeviceTableWidgetDelegate(QObject *parent);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

protected:
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override;
};

#endif // DEVICETABLEWIDGETDELEGATE_H
