#include "sidebar.h"
#include <QListWidgetItem>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>

SideBar::SideBar(QWidget *parent)
    : QWidget(parent)
    , m_layout(nullptr)
    , m_titleLabel(nullptr)
    , m_listWidget(nullptr)
    , m_hoverAnimation(nullptr)
{
    setupUI();
    
    // Add some default items with icons
    addItem("🏠 Dashboard");
    addItem("📊 Projects");
    addItem("✅ Tasks");
    addItem("📈 Analytics");
    addItem("⚙️ Settings");
    addItem("❓ Help");
}

void SideBar::setupUI()
{
    setStyleSheet(R"(
        SideBar {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #667eea, stop:1 #764ba2);
            border: none;
        }
        QLabel {
            color: white;
            font-size: 24px;
            font-weight: bold;
            padding: 20px 15px;
            background: rgba(255, 255, 255, 0.1);
            border: none;
            border-radius: 0px;
        }
        QListWidget {
            background: transparent;
            border: none;
            outline: none;
            padding: 10px 0px;
        }
        QListWidget::item {
            color: rgba(255, 255, 255, 0.9);
            padding: 15px 20px;
            margin: 2px 8px;
            border-radius: 12px;
            font-size: 14px;
            font-weight: 500;
            border: 1px solid transparent;
            background: transparent;
        }
        QListWidget::item:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 rgba(255, 255, 255, 0.15),
                stop:1 rgba(255, 255, 255, 0.25));
            color: white;
            border: 1px solid rgba(255, 255, 255, 0.3);
            transform: translateX(5px);
        }
        QListWidget::item:selected {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 rgba(255, 255, 255, 0.25),
                stop:1 rgba(255, 255, 255, 0.35));
            color: white;
            border: 1px solid rgba(255, 255, 255, 0.5);
            font-weight: bold;
        }
        QListWidget::item:selected:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 rgba(255, 255, 255, 0.3),
                stop:1 rgba(255, 255, 255, 0.4));
        }
            margin: 2px 10px;
            border-radius: 10px;
            font-size: 16px;
            font-weight: 500;
            border: 2px solid transparent;
        }
        QListWidget::item:hover {
            background: rgba(255, 255, 255, 0.15);
            color: white;
            border: 2px solid rgba(255, 255, 255, 0.3);
            transform: translateX(5px);
        }
        QListWidget::item:selected {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #43e97b, stop:1 #38f9d7);
            color: #2c3e50;
            font-weight: bold;
            border: 2px solid rgba(255, 255, 255, 0.5);
        }
    )");
    
    m_layout = new QVBoxLayout(this);
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0, 0, 0, 0);
    
    m_titleLabel = new QLabel("ACT", this);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    
    m_listWidget = new QListWidget(this);
    m_listWidget->setMouseTracking(true);
    
    m_layout->addWidget(m_titleLabel);
    m_layout->addWidget(m_listWidget);
    
    connect(m_listWidget, &QListWidget::itemClicked, this, &SideBar::onItemClicked);
    connect(m_listWidget, &QListWidget::itemEntered, this, &SideBar::onItemEntered);
    
    // Setup hover animation
    m_hoverAnimation = new QPropertyAnimation(this);
    m_hoverAnimation->setDuration(200);
    m_hoverAnimation->setEasingCurve(QEasingCurve::OutCubic);
}

void SideBar::addItem(const QString &text, const QString & /*icon*/)
{
    new QListWidgetItem(text, m_listWidget);
    // You can add icons later if needed
}

void SideBar::onItemClicked(QListWidgetItem *item)
{
    if (item) {
        emit itemClicked(item->text());
    }
}

void SideBar::onItemEntered(QListWidgetItem *item)
{
    animateItemHover(item, true);
}

void SideBar::onItemLeft(QListWidgetItem *item)
{
    animateItemHover(item, false);
}

void SideBar::animateItemHover(QListWidgetItem *item, bool hover)
{
    if (!item) return;
    
    // Add subtle animation feedback here
    // For now, the CSS hover effects handle the visual feedback
}
