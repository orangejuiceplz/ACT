#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QGroupBox>

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);

private slots:
    void applySettings();
    void resetSettings();

private:
    void setupUI();
    void setupGeneralTab();
    void setupAppearanceTab();
    
    QTabWidget *m_tabWidget;
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_buttonLayout;
    
    // General settings
    QCheckBox *m_autoSaveCheckBox;
    QSpinBox *m_autoSaveIntervalSpinBox;
    
    // Appearance settings
    QComboBox *m_themeComboBox;
    QCheckBox *m_darkModeCheckBox;
    
    QPushButton *m_applyButton;
    QPushButton *m_cancelButton;
    QPushButton *m_resetButton;
};

#endif // SETTINGSDIALOG_H
