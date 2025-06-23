#include "moderncard.h"
#include <QTimer>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QEasingCurve>
#include <QGridLayout>
#include <QSpacerItem>

ModernCard::ModernCard(const QString &title, const QString &subtitle, QWidget *parent)
    : QFrame(parent)
    , m_mainLayout(nullptr)
    , m_headerLayout(nullptr)
    , m_iconLabel(nullptr)
    , m_titleLabel(nullptr)
    , m_subtitleLabel(nullptr)
    , m_contentWidget(nullptr)
    , m_contentLayout(nullptr)
    , m_hoverAnimation(nullptr)
    , m_scaleAnimation(nullptr)
    , m_shadowAnimation(nullptr)
    , m_shadowEffect(nullptr)
    , m_title(title)
    , m_subtitle(subtitle)
{
    setupUI();
    setupAnimations();
}

void ModernCard::setupUI()
{
    setStyleSheet(R"(
        ModernCard {
            background: white;
            border-radius: 15px;
            border: 1px solid rgba(0, 0, 0, 0.1);
            margin: 5px;
        }
        ModernCard:hover {
            border: 1px solid rgba(102, 126, 234, 0.3);
        }
    )");
    
    setFixedSize(280, 200);
    
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(15);
    m_mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Header with icon and title
    m_headerLayout = new QHBoxLayout();
    
    m_iconLabel = new QLabel("📊", this);
    m_iconLabel->setStyleSheet(R"(
        QLabel {
            font-size: 24px;
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #667eea, stop:1 #764ba2);
            border-radius: 20px;
            padding: 8px;
            max-width: 40px;
            max-height: 40px;
        }
    )");
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setFixedSize(40, 40);
    
    QVBoxLayout *titleLayout = new QVBoxLayout();
    titleLayout->setSpacing(2);
    
    m_titleLabel = new QLabel(m_title, this);
    m_titleLabel->setStyleSheet(R"(
        QLabel {
            color: #2c3e50;
            font-size: 16px;
            font-weight: bold;
            background: transparent;
            border: none;
        }
    )");
    
    m_subtitleLabel = new QLabel(m_subtitle, this);
    m_subtitleLabel->setStyleSheet(R"(
        QLabel {
            color: #7f8c8d;
            font-size: 12px;
            background: transparent;
            border: none;
        }
    )");
    
    titleLayout->addWidget(m_titleLabel);
    if (!m_subtitle.isEmpty()) {
        titleLayout->addWidget(m_subtitleLabel);
    }
    
    m_headerLayout->addWidget(m_iconLabel);
    m_headerLayout->addLayout(titleLayout);
    m_headerLayout->addStretch();
    
    // Content area
    m_contentWidget = new QWidget(this);
    m_contentLayout = new QVBoxLayout(m_contentWidget);
    m_contentLayout->setContentsMargins(0, 10, 0, 0);
    
    m_mainLayout->addLayout(m_headerLayout);
    m_mainLayout->addWidget(m_contentWidget);
    m_mainLayout->addStretch();
    
    // Shadow effect
    m_shadowEffect = new QGraphicsDropShadowEffect(this);
    m_shadowEffect->setBlurRadius(15);
    m_shadowEffect->setColor(QColor(0, 0, 0, 50));
    m_shadowEffect->setOffset(0, 5);
    setGraphicsEffect(m_shadowEffect);
}

void ModernCard::setupAnimations()
{
    // Hover animation for shadow
    m_hoverAnimation = new QPropertyAnimation(this, "geometry");
    m_hoverAnimation->setDuration(200);
    m_hoverAnimation->setEasingCurve(QEasingCurve::OutCubic);
    
    // Scale animation
    m_scaleAnimation = new QPropertyAnimation(this, "geometry");
    m_scaleAnimation->setDuration(200);
    m_scaleAnimation->setEasingCurve(QEasingCurve::OutCubic);
}

void ModernCard::setContent(QWidget *content)
{
    m_contentLayout->addWidget(content);
}

void ModernCard::setIcon(const QString &iconText)
{
    m_icon = iconText;
    m_iconLabel->setText(iconText);
}

void ModernCard::animateIn()
{
    // Fade and slide in animation
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(opacityEffect);
    
    QPropertyAnimation *fadeIn = new QPropertyAnimation(opacityEffect, "opacity");
    fadeIn->setDuration(500);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);
    fadeIn->setEasingCurve(QEasingCurve::OutCubic);
    
    QPropertyAnimation *slideIn = new QPropertyAnimation(this, "pos");
    slideIn->setDuration(500);
    slideIn->setStartValue(pos() + QPoint(0, 30));
    slideIn->setEndValue(pos());
    slideIn->setEasingCurve(QEasingCurve::OutCubic);
    
    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
    group->addAnimation(fadeIn);
    group->addAnimation(slideIn);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void ModernCard::animateOut()
{
    QGraphicsOpacityEffect *opacityEffect = qobject_cast<QGraphicsOpacityEffect*>(graphicsEffect());
    if (!opacityEffect) {
        opacityEffect = new QGraphicsOpacityEffect(this);
        setGraphicsEffect(opacityEffect);
    }
    
    QPropertyAnimation *fadeOut = new QPropertyAnimation(opacityEffect, "opacity");
    fadeOut->setDuration(300);
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);
    fadeOut->start(QAbstractAnimation::DeleteWhenStopped);
}

void ModernCard::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    
    // Animate shadow intensity
    m_shadowEffect->setBlurRadius(25);
    m_shadowEffect->setOffset(0, 8);
    
    // Scale up slightly
    QRect currentGeometry = geometry();
    QRect hoveredGeometry = currentGeometry.adjusted(-2, -2, 2, 2);
    
    m_scaleAnimation->setStartValue(currentGeometry);
    m_scaleAnimation->setEndValue(hoveredGeometry);
    m_scaleAnimation->start();
    
    emit hovered();
}

void ModernCard::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    
    // Reset shadow
    m_shadowEffect->setBlurRadius(15);
    m_shadowEffect->setOffset(0, 5);
    
    // Scale back to normal
    QRect currentGeometry = geometry();
    QRect normalGeometry = currentGeometry.adjusted(2, 2, -2, -2);
    
    m_scaleAnimation->setStartValue(currentGeometry);
    m_scaleAnimation->setEndValue(normalGeometry);
    m_scaleAnimation->start();
}

void ModernCard::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    emit clicked();
}

// Dashboard Widget Implementation
DashboardWidget::DashboardWidget(QWidget *parent)
    : QWidget(parent)
    , m_mainLayout(nullptr)
    , m_cardsLayout(nullptr)
{
    setupCards();
    QTimer::singleShot(200, this, &DashboardWidget::animateCardsIn);
}

void DashboardWidget::setupCards()
{
    setStyleSheet(R"(
        DashboardWidget {
            background: transparent;
        }
    )");
    
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(20);
    m_mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Title
    QLabel *titleLabel = new QLabel("Dashboard Overview", this);
    titleLabel->setStyleSheet(R"(
        QLabel {
            color: #2c3e50;
            font-size: 28px;
            font-weight: bold;
            margin-bottom: 20px;
        }
    )");
    
    m_mainLayout->addWidget(titleLabel);
    
    // Cards grid
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(15);
    
    // Create cards
    ModernCard *projectsCard = new ModernCard("Active Projects", "12 running projects");
    projectsCard->setIcon("📊");
    QLabel *projectsContent = new QLabel("View and manage your active projects");
    projectsContent->setStyleSheet("color: #7f8c8d; font-size: 14px;");
    projectsCard->setContent(projectsContent);
    
    ModernCard *tasksCard = new ModernCard("Tasks", "24 pending tasks");
    tasksCard->setIcon("✅");
    QLabel *tasksContent = new QLabel("Track your daily tasks and progress");
    tasksContent->setStyleSheet("color: #7f8c8d; font-size: 14px;");
    tasksCard->setContent(tasksContent);
    
    ModernCard *analyticsCard = new ModernCard("Analytics", "Performance metrics");
    analyticsCard->setIcon("📈");
    QLabel *analyticsContent = new QLabel("View detailed analytics and reports");
    analyticsContent->setStyleSheet("color: #7f8c8d; font-size: 14px;");
    analyticsCard->setContent(analyticsContent);
    
    ModernCard *settingsCard = new ModernCard("Quick Settings", "Customize your experience");
    settingsCard->setIcon("⚙️");
    QLabel *settingsContent = new QLabel("Access frequently used settings");
    settingsContent->setStyleSheet("color: #7f8c8d; font-size: 14px;");
    settingsCard->setContent(settingsContent);
    
    m_cards.append(projectsCard);
    m_cards.append(tasksCard);
    m_cards.append(analyticsCard);
    m_cards.append(settingsCard);
    
    gridLayout->addWidget(projectsCard, 0, 0);
    gridLayout->addWidget(tasksCard, 0, 1);
    gridLayout->addWidget(analyticsCard, 1, 0);
    gridLayout->addWidget(settingsCard, 1, 1);
    
    m_mainLayout->addLayout(gridLayout);
    m_mainLayout->addStretch();
}

void DashboardWidget::animateCardsIn()
{
    for (int i = 0; i < m_cards.size(); ++i) {
        QTimer::singleShot(i * 100, m_cards[i], &ModernCard::animateIn);
    }
}
