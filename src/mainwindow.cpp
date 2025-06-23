#include "mainwindow.h"
#include "sidebar.h"
#include "settingsdialog.h"
#include "moderncard.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>
#include <QEasingCurve>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_mainLayout(nullptr)
    , m_sidebar(nullptr)
    , m_contentStack(nullptr)
    , m_contentArea(nullptr)
    , m_settingsDialog(nullptr)
    , m_sidebarToggle(nullptr)
    , m_fadeAnimation(nullptr)
    , m_slideAnimation(nullptr)
    , m_sidebarAnimation(nullptr)
    , m_opacityEffect(nullptr)
    , m_animationGroup(nullptr)
    , m_sidebarVisible(true)
{
    setupUI();
    setupMenuBar();
    setupStatusBar();
    setupAnimations();
    
    // Connect sidebar signals
    connect(m_sidebar, &SideBar::itemClicked, this, &MainWindow::onSidebarItemClicked);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    // Set application style
    setStyleSheet(R"(
        QMainWindow {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #667eea, stop:1 #764ba2);
        }
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #4facfe, stop:1 #00f2fe);
            border: none;
            border-radius: 8px;
            color: white;
            font-weight: bold;
            padding: 10px 20px;
            font-size: 14px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #43e97b, stop:1 #38f9d7);
            transform: translateY(-2px);
        }
        QPushButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #667eea, stop:1 #764ba2);
        }
        QMenuBar {
            background: rgba(255, 255, 255, 0.1);
            border: none;
            color: white;
            font-weight: bold;
        }
        QMenuBar::item {
            background: transparent;
            padding: 8px 12px;
            border-radius: 4px;
        }
        QMenuBar::item:selected {
            background: rgba(255, 255, 255, 0.2);
        }
        QMenu {
            background: rgba(255, 255, 255, 0.95);
            border: 1px solid rgba(0, 0, 0, 0.1);
            border-radius: 8px;
            padding: 5px;
        }
        QMenu::item {
            padding: 8px 20px;
            border-radius: 4px;
        }
        QMenu::item:selected {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #4facfe, stop:1 #00f2fe);
            color: white;
        }
        QStatusBar {
            background: rgba(255, 255, 255, 0.1);
            color: white;
            border: none;
        }
    )");
    
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    
    m_mainLayout = new QHBoxLayout(m_centralWidget);
    m_mainLayout->setSpacing(0);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    
    // Create sidebar toggle button
    m_sidebarToggle = new QPushButton("☰", this);
    m_sidebarToggle->setFixedSize(40, 40);
    m_sidebarToggle->setStyleSheet(R"(
        QPushButton {
            background: rgba(255, 255, 255, 0.2);
            border: 2px solid rgba(255, 255, 255, 0.3);
            border-radius: 20px;
            color: white;
            font-size: 18px;
            font-weight: bold;
        }
        QPushButton:hover {
            background: rgba(255, 255, 255, 0.3);
            border: 2px solid rgba(255, 255, 255, 0.5);
        }
    )");
    m_sidebarToggle->move(10, 10);
    connect(m_sidebarToggle, &QPushButton::clicked, this, &MainWindow::onSidebarToggle);
    
    // Create sidebar
    m_sidebar = new SideBar(this);
    m_sidebar->setFixedWidth(280);
    
    // Create content stack for smooth transitions
    m_contentStack = new QStackedWidget(this);
    m_contentStack->setStyleSheet(R"(
        QStackedWidget {
            background: rgba(255, 255, 255, 0.95);
            border-radius: 15px;
            margin: 10px;
        }
    )");
    
    // Create initial content area
    m_contentArea = new QWidget();
    setupContentArea();
    m_contentStack->addWidget(m_contentArea);
    
    // Add widgets to main layout
    m_mainLayout->addWidget(m_sidebar);
    m_mainLayout->addWidget(m_contentStack, 1);
    
    // Set window properties
    setWindowTitle("ACT - Advanced Control Tool");
    resize(1400, 900);
    
    // Apply shadow effect to sidebar
    QGraphicsDropShadowEffect *sidebarShadow = new QGraphicsDropShadowEffect();
    sidebarShadow->setBlurRadius(20);
    sidebarShadow->setColor(QColor(0, 0, 0, 80));
    sidebarShadow->setOffset(5, 0);
    m_sidebar->setGraphicsEffect(sidebarShadow);
    
    // Apply shadow effect to content area
    QGraphicsDropShadowEffect *contentShadow = new QGraphicsDropShadowEffect();
    contentShadow->setBlurRadius(15);
    contentShadow->setColor(QColor(0, 0, 0, 60));
    contentShadow->setOffset(0, 5);
    m_contentStack->setGraphicsEffect(contentShadow);
}

void MainWindow::setupContentArea()
{
    QVBoxLayout *contentLayout = new QVBoxLayout(m_contentArea);
    contentLayout->setSpacing(20);
    contentLayout->setContentsMargins(40, 40, 40, 40);
    
    // Welcome title with modern styling
    QLabel *titleLabel = new QLabel("Welcome to ACT", m_contentArea);
    titleLabel->setStyleSheet(R"(
        QLabel {
            color: #2c3e50;
            font-size: 32px;
            font-weight: bold;
            margin-bottom: 10px;
        }
    )");
    titleLabel->setAlignment(Qt::AlignCenter);
    
    // Subtitle
    QLabel *subtitleLabel = new QLabel("Advanced Control Tool - Modern Interface", m_contentArea);
    subtitleLabel->setStyleSheet(R"(
        QLabel {
            color: #7f8c8d;
            font-size: 16px;
            margin-bottom: 30px;
        }
    )");
    subtitleLabel->setAlignment(Qt::AlignCenter);
    
    // Feature cards container
    QWidget *cardsContainer = new QWidget(m_contentArea);
    QHBoxLayout *cardsLayout = new QHBoxLayout(cardsContainer);
    cardsLayout->setSpacing(20);
    
    // Create feature cards
    QStringList features = {"Dashboard", "Analytics", "Settings"};
    QStringList descriptions = {
        "Monitor your system\nand track performance",
        "Detailed insights\nand data visualization", 
        "Customize your\nexperience"
    };
    
    for (int i = 0; i < features.size(); ++i) {
        QWidget *card = new QWidget(cardsContainer);
        card->setStyleSheet(R"(
            QWidget {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #f8f9fa, stop:1 #e9ecef);
                border: 1px solid #dee2e6;
                border-radius: 12px;
                padding: 20px;
            }
            QWidget:hover {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #e3f2fd, stop:1 #bbdefb);
                border: 1px solid #2196f3;
            }
        )");
        card->setFixedHeight(150);
        
        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        
        QLabel *cardTitle = new QLabel(features[i], card);
        cardTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50;");
        cardTitle->setAlignment(Qt::AlignCenter);
        
        QLabel *cardDesc = new QLabel(descriptions[i], card);
        cardDesc->setStyleSheet("font-size: 14px; color: #6c757d; margin-top: 10px;");
        cardDesc->setAlignment(Qt::AlignCenter);
        
        cardLayout->addWidget(cardTitle);
        cardLayout->addWidget(cardDesc);
        cardLayout->addStretch();
        
        cardsLayout->addWidget(card);
    }
    
    contentLayout->addWidget(titleLabel);
    contentLayout->addWidget(subtitleLabel);
    contentLayout->addWidget(cardsContainer);
    contentLayout->addStretch();
}

void MainWindow::setupMenuBar()
{
    // Hide the menu bar completely for a cleaner modern look
    menuBar()->hide();
}

void MainWindow::setupStatusBar()
{
    statusBar()->showMessage("Ready");
}

void MainWindow::setupAnimations()
{
    // Setup opacity effect for content transitions
    m_opacityEffect = new QGraphicsOpacityEffect(this);
    m_opacityEffect->setOpacity(1.0);
    m_contentStack->setGraphicsEffect(m_opacityEffect);
    
    // Fade animation for content changes
    m_fadeAnimation = new QPropertyAnimation(m_opacityEffect, "opacity", this);
    m_fadeAnimation->setDuration(300);
    m_fadeAnimation->setEasingCurve(QEasingCurve::InOutCubic);
    
    // Slide animation for sidebar
    m_sidebarAnimation = new QPropertyAnimation(m_sidebar, "maximumWidth", this);
    m_sidebarAnimation->setDuration(400);
    m_sidebarAnimation->setEasingCurve(QEasingCurve::InOutCubic);
    
    // Animation group for complex transitions
    m_animationGroup = new QParallelAnimationGroup(this);
}

void MainWindow::animateWidgetIn(QWidget *widget)
{
    if (!widget) return;
    
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
    widget->setGraphicsEffect(effect);
    
    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(400);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::animateWidgetOut(QWidget *widget)
{
    if (!widget) return;
    
    QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(widget->graphicsEffect());
    if (!effect) {
        effect = new QGraphicsOpacityEffect();
        widget->setGraphicsEffect(effect);
    }
    
    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(300);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->setEasingCurve(QEasingCurve::InCubic);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::animateContentChange()
{
    m_fadeAnimation->setStartValue(1.0);
    m_fadeAnimation->setEndValue(0.0);
    
    connect(m_fadeAnimation, &QPropertyAnimation::finished, [this]() {
        m_fadeAnimation->disconnect();
        m_fadeAnimation->setStartValue(0.0);
        m_fadeAnimation->setEndValue(1.0);
        m_fadeAnimation->start();
    });
    
    m_fadeAnimation->start();
}

void MainWindow::onSidebarToggle()
{
    m_sidebarVisible = !m_sidebarVisible;
    
    int targetWidth = m_sidebarVisible ? 280 : 0;
    
    m_sidebarAnimation->setStartValue(m_sidebar->width());
    m_sidebarAnimation->setEndValue(targetWidth);
    m_sidebarAnimation->start();
    
    // Update toggle button text with animation
    QString newText = m_sidebarVisible ? "☰" : "→";
    m_sidebarToggle->setText(newText);
}

void MainWindow::createModernButton(QPushButton *button)
{
    if (!button) return;
    
    button->setStyleSheet(R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #667eea, stop:1 #764ba2);
            border: none;
            border-radius: 12px;
            color: white;
            font-weight: bold;
            padding: 12px 24px;
            font-size: 14px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #f093fb, stop:1 #f5576c);
            transform: translateY(-2px);
        }
        QPushButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #4facfe, stop:1 #00f2fe);
        }
    )");
}

void MainWindow::showSettings()
{
    if (!m_settingsDialog) {
        m_settingsDialog = new SettingsDialog(this);
    }
    m_settingsDialog->exec();
}

void MainWindow::onSidebarItemClicked(const QString &item)
{
    statusBar()->showMessage(QString("Selected: %1").arg(item));
    
    // Animate content change
    animateContentChange();
    
    // Create new content widget based on selection
    QTimer::singleShot(150, [this, item]() {
        QWidget *newContent = nullptr;
        
        // Check if it's Dashboard and create the special dashboard widget
        if (item.contains("Dashboard")) {
            newContent = new DashboardWidget();
        } else {
            // Create regular content for other items
            newContent = new QWidget();
            QVBoxLayout *layout = new QVBoxLayout(newContent);
            layout->setSpacing(20);
            layout->setContentsMargins(40, 40, 40, 40);
            
            // Title
            QLabel *titleLabel = new QLabel(QString("%1 Dashboard").arg(item), newContent);
            titleLabel->setStyleSheet(R"(
                QLabel {
                    color: #2c3e50;
                    font-size: 28px;
                    font-weight: bold;
                    margin-bottom: 20px;
                }
            )");
            
            // Description
            QLabel *descLabel = new QLabel(QString("Welcome to the %1 section. Here you can manage and monitor your %2 activities.").arg(item).arg(item.toLower()), newContent);
            descLabel->setStyleSheet(R"(
                QLabel {
                    color: #7f8c8d;
                    font-size: 16px;
                    line-height: 1.5;
                    margin-bottom: 30px;
                }
            )");
            descLabel->setWordWrap(true);
            
            // Action buttons
            QWidget *buttonContainer = new QWidget(newContent);
            QHBoxLayout *buttonLayout = new QHBoxLayout(buttonContainer);
            
            QPushButton *primaryBtn = new QPushButton(QString("Manage %1").arg(item), buttonContainer);
            QPushButton *secondaryBtn = new QPushButton("View Details", buttonContainer);
            
            createModernButton(primaryBtn);
            createModernButton(secondaryBtn);
            
            buttonLayout->addWidget(primaryBtn);
            buttonLayout->addWidget(secondaryBtn);
            buttonLayout->addStretch();
            
            layout->addWidget(titleLabel);
            layout->addWidget(descLabel);
            layout->addWidget(buttonContainer);
            layout->addStretch();
        }
        
        // Remove old content and add new
        QWidget *oldContent = m_contentStack->currentWidget();
        m_contentStack->addWidget(newContent);
        m_contentStack->setCurrentWidget(newContent);
        
        if (oldContent != m_contentArea) {
            m_contentStack->removeWidget(oldContent);
            oldContent->deleteLater();
        }
        
        // Animate new content in
        animateWidgetIn(newContent);
    });
}
