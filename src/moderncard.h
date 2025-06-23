#ifndef MODERNCARD_H
#define MODERNCARD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>
#include <QFrame>

class ModernCard : public QFrame
{
    Q_OBJECT

public:
    explicit ModernCard(const QString &title, const QString &subtitle = QString(), QWidget *parent = nullptr);
    
    void setContent(QWidget *content);
    void setIcon(const QString &iconText);
    void animateIn();
    void animateOut();

signals:
    void clicked();
    void hovered();

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void setupUI();
    void setupAnimations();
    
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_headerLayout;
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_subtitleLabel;
    QWidget *m_contentWidget;
    QVBoxLayout *m_contentLayout;
    
    // Animation objects
    QPropertyAnimation *m_hoverAnimation;
    QPropertyAnimation *m_scaleAnimation;
    QPropertyAnimation *m_shadowAnimation;
    QGraphicsDropShadowEffect *m_shadowEffect;
    
    QString m_title;
    QString m_subtitle;
    QString m_icon;
};

class DashboardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardWidget(QWidget *parent = nullptr);

private:
    void setupCards();
    void animateCardsIn();
    
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_cardsLayout;
    
    QList<ModernCard*> m_cards;
};

#endif // MODERNCARD_H
