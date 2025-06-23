# ACT (Automated Cipher Translator) - Changelog

## [Unreleased]
### Project Planning
- Created comprehensive TODO.md with 8-phase development plan
- Established project structure and documentation standards
- Defined core features and advanced capabilities

---

## [0.1.0] - 2025-06-23 - "Foundation"
### Added ✨
- Modern Qt5 application framework with C++17
- Gradient-based UI design with glass-morphism effects
- Animated sidebar with smooth transitions
- Card-based dashboard with hover effects
- Stacked widget system for content management
- Drop shadow effects and modern styling
- Responsive layout system

### UI Components ✨
- MainWindow with gradient background
- SideBar with animated items and icons
- ModernCard component with animations
- DashboardWidget with interactive cards
- SettingsDialog with tabbed interface

### Technical Features ✨
- CMake build system configuration
- Qt5 Widgets and Core modules integration
- Property animations with easing curves
- Graphics effects (opacity, drop shadow)
- Signal-slot connections for interactivity

### Removed 🗑️
- Traditional menu bar (File/Help menus)
- Default Qt styling in favor of custom CSS

### Project Structure 📁
```
ACT/
├── src/
│   ├── main.cpp
│   ├── mainwindow.h/cpp
│   ├── sidebar.h/cpp
│   ├── settingsdialog.h/cpp
│   └── moderncard.h/cpp
├── build/
├── CMakeLists.txt
├── build.sh
├── README.md
├── TODO.md
└── CHANGELOG.md
```

### Build System 🔧
- Qt5 automatic MOC, UIC, and RCC processing
- Compiler warnings enabled (-Wall -Wextra -pedantic)
- Debug and release configurations
- Executable output to build/bin/ACT

---

## Development Notes

### Design Decisions 💭
- **Qt5 over Qt6**: Chosen to maintain compatibility with user's existing Qt5 environment (Hyprland dependencies)
- **Modern UI**: Implemented gradient backgrounds, animations, and card-based layouts for contemporary feel
- **No Menu Bar**: Removed for cleaner, mobile-app-like interface
- **Animation Framework**: Used Qt's native property animations for smooth transitions

### Technical Debt 🔧
- Minor warning in sidebar.cpp for unused parameter (non-critical)
- MOC warning in moderncard.cpp resolved by removing unnecessary include

### Next Priorities 🎯
1. Design cipher detection engine architecture
2. Implement basic cipher algorithms (Caesar, Base64, ROT13)
3. Create input/output text areas
4. Build processing pipeline visualization
5. Add entropy analysis capabilities

---

## Change Categories
- ✨ **Added**: New features
- 🔧 **Changed**: Changes in existing functionality  
- 🗑️ **Removed**: Removed features
- 🐛 **Fixed**: Bug fixes
- 📁 **Structure**: File/folder organization changes
- 🔒 **Security**: Security improvements
- ⚡ **Performance**: Performance improvements
- 💭 **Design**: Design decisions and rationale
