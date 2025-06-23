#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>

class SideBar : public QWidget
{
    Q_OBJECT

public:
    explicit SideBar(QWidget *parent = nullptr);
    
    void addItem(const QString &text, const QString &icon = QString());

signals:
    void itemClicked(const QString &item);

private slots:
    void onItemClicked(QListWidgetItem *item);
    void onItemEntered(QListWidgetItem *item);
    void onItemLeft(QListWidgetItem *item);

private:
    void setupUI();
    void animateItemHover(QListWidgetItem *item, bool hover);
    
    QVBoxLayout *m_layout;
    QLabel *m_titleLabel;
    QListWidget *m_listWidget;
    QPropertyAnimation *m_hoverAnimation;
};

#endif // SIDEBAR_H
