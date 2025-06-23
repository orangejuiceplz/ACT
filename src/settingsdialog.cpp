#include "settingsdialog.h"
#include <QGroupBox>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    setWindowTitle("Settings");
    setModal(true);
    resize(600, 500);
    
    // Modern dialog styling
    setStyleSheet(R"(
        QDialog {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #f8f9fa, stop:1 #e9ecef);
            border-radius: 15px;
        }
        QTabWidget::pane {
            border: 1px solid #dee2e6;
            border-radius: 8px;
            background: white;
            margin-top: 10px;
        }
        QTabWidget::tab-bar {
            alignment: center;
        }
        QTabBar::tab {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #f8f9fa, stop:1 #e9ecef);
            border: 1px solid #dee2e6;
            padding: 12px 24px;
            margin-right: 2px;
            border-top-left-radius: 8px;
            border-top-right-radius: 8px;
            font-weight: 500;
        }
        QTabBar::tab:selected {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #4facfe, stop:1 #00f2fe);
            color: white;
            font-weight: bold;
        }
        QTabBar::tab:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #e3f2fd, stop:1 #bbdefb);
        }
        QGroupBox {
            font-weight: bold;
            font-size: 14px;
            border: 2px solid #dee2e6;
            border-radius: 8px;
            margin-top: 10px;
            padding-top: 10px;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 8px 0 8px;
            color: #495057;
        }
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #667eea, stop:1 #764ba2);
            border: none;
            border-radius: 8px;
            color: white;
            font-weight: bold;
            padding: 10px 20px;
            font-size: 14px;
            min-width: 80px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #43e97b, stop:1 #38f9d7);
        }
        QPushButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #4facfe, stop:1 #00f2fe);
        }
        QCheckBox {
            font-size: 14px;
            spacing: 8px;
        }
        QCheckBox::indicator {
            width: 18px;
            height: 18px;
            border-radius: 9px;
            border: 2px solid #6c757d;
        }
        QCheckBox::indicator:checked {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #43e97b, stop:1 #38f9d7);
            border: 2px solid #38f9d7;
        }
        QSpinBox, QComboBox {
            border: 2px solid #dee2e6;
            border-radius: 6px;
            padding: 8px;
            font-size: 14px;
            background: white;
        }
        QSpinBox:focus, QComboBox:focus {
            border: 2px solid #4facfe;
        }
    )");
}

void SettingsDialog::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    
    m_tabWidget = new QTabWidget(this);
    setupGeneralTab();
    setupAppearanceTab();
    
    m_buttonLayout = new QHBoxLayout();
    m_applyButton = new QPushButton("Apply", this);
    m_cancelButton = new QPushButton("Cancel", this);
    m_resetButton = new QPushButton("Reset", this);
    
    m_buttonLayout->addStretch();
    m_buttonLayout->addWidget(m_resetButton);
    m_buttonLayout->addWidget(m_cancelButton);
    m_buttonLayout->addWidget(m_applyButton);
    
    m_mainLayout->addWidget(m_tabWidget);
    m_mainLayout->addLayout(m_buttonLayout);
    
    connect(m_applyButton, &QPushButton::clicked, this, &SettingsDialog::applySettings);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_resetButton, &QPushButton::clicked, this, &SettingsDialog::resetSettings);
}

void SettingsDialog::setupGeneralTab()
{
    QWidget *generalTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(generalTab);
    
    QGroupBox *autoSaveGroup = new QGroupBox("Auto Save", generalTab);
    QVBoxLayout *autoSaveLayout = new QVBoxLayout(autoSaveGroup);
    
    m_autoSaveCheckBox = new QCheckBox("Enable auto save", autoSaveGroup);
    m_autoSaveCheckBox->setChecked(true);
    
    QHBoxLayout *intervalLayout = new QHBoxLayout();
    intervalLayout->addWidget(new QLabel("Interval (minutes):"));
    m_autoSaveIntervalSpinBox = new QSpinBox();
    m_autoSaveIntervalSpinBox->setRange(1, 60);
    m_autoSaveIntervalSpinBox->setValue(5);
    intervalLayout->addWidget(m_autoSaveIntervalSpinBox);
    intervalLayout->addStretch();
    
    autoSaveLayout->addWidget(m_autoSaveCheckBox);
    autoSaveLayout->addLayout(intervalLayout);
    
    layout->addWidget(autoSaveGroup);
    layout->addStretch();
    
    m_tabWidget->addTab(generalTab, "General");
}

void SettingsDialog::setupAppearanceTab()
{
    QWidget *appearanceTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(appearanceTab);
    
    QGroupBox *themeGroup = new QGroupBox("Theme", appearanceTab);
    QVBoxLayout *themeLayout = new QVBoxLayout(themeGroup);
    
    QHBoxLayout *themeSelectLayout = new QHBoxLayout();
    themeSelectLayout->addWidget(new QLabel("Theme:"));
    m_themeComboBox = new QComboBox();
    m_themeComboBox->addItems({"Default", "Dark", "Light"});
    themeSelectLayout->addWidget(m_themeComboBox);
    themeSelectLayout->addStretch();
    
    m_darkModeCheckBox = new QCheckBox("Enable dark mode", themeGroup);
    
    themeLayout->addLayout(themeSelectLayout);
    themeLayout->addWidget(m_darkModeCheckBox);
    
    layout->addWidget(themeGroup);
    layout->addStretch();
    
    m_tabWidget->addTab(appearanceTab, "Appearance");
}

void SettingsDialog::applySettings()
{
    // Here you would save the settings to QSettings or your preferred storage
    accept();
}

void SettingsDialog::resetSettings()
{
    m_autoSaveCheckBox->setChecked(true);
    m_autoSaveIntervalSpinBox->setValue(5);
    m_themeComboBox->setCurrentIndex(0);
    m_darkModeCheckBox->setChecked(false);
}
