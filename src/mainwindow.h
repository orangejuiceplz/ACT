#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <QAction>
#include <QMenu>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QGraphicsDropShadowEffect>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QEasingCurve>
#include <QPushButton>
#include <QStackedWidget>

class SideBar;
class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showSettings();
    void onSidebarItemClicked(const QString &item);
    void animateContentChange();
    void onSidebarToggle();

private:
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    void setupAnimations();
    void setupContentArea();
    void animateWidgetIn(QWidget *widget);
    void animateWidgetOut(QWidget *widget);
    void createModernButton(QPushButton *button);
    
    QWidget *m_centralWidget;
    QHBoxLayout *m_mainLayout;
    SideBar *m_sidebar;
    QStackedWidget *m_contentStack;
    QWidget *m_contentArea;
    SettingsDialog *m_settingsDialog;
    QPushButton *m_sidebarToggle;
    
    // Animation objects
    QPropertyAnimation *m_fadeAnimation;
    QPropertyAnimation *m_slideAnimation;
    QPropertyAnimation *m_sidebarAnimation;
    QGraphicsOpacityEffect *m_opacityEffect;
    QParallelAnimationGroup *m_animationGroup;
    
    bool m_sidebarVisible;
};

#endif // MAINWINDOW_H
