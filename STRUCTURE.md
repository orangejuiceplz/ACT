# ACT Project Structure Plan

## Current Structure ✅
```
ACT/
├── src/                          # Source code
│   ├── main.cpp                  # Application entry point
│   ├── mainwindow.h/cpp          # Main window with sidebar/content
│   ├── sidebar.h/cpp             # Animated navigation sidebar
│   ├── settingsdialog.h/cpp      # Settings configuration
│   └── moderncard.h/cpp          # Dashboard card components
├── build/                        # CMake build directory
├── CMakeLists.txt               # Build configuration
├── build.sh                     # Build script
├── README.md                    # Project documentation
├── TODO.md                      # Development roadmap
└── CHANGELOG.md                 # Version history
```

## Planned Structure (Phase 1-2) 📋
```
ACT/
├── src/
│   ├── core/                     # Core engine components
│   │   ├── cipher_engine.h/cpp   # Main cipher detection/processing
│   │   ├── cipher_registry.h/cpp # Registry of available ciphers
│   │   ├── analysis/             # Analysis modules
│   │   │   ├── entropy.h/cpp     # Entropy analysis
│   │   │   ├── frequency.h/cpp   # Character frequency analysis
│   │   │   └── dictionary.h/cpp  # Dictionary matching
│   │   └── pipeline/             # Processing pipeline
│   │       ├── pipeline.h/cpp    # Pipeline management
│   │       ├── step.h/cpp        # Individual processing steps
│   │       └── result.h/cpp      # Result handling
│   ├── ciphers/                  # Individual cipher implementations
│   │   ├── base/                 # Base classes
│   │   │   ├── cipher_base.h/cpp # Abstract cipher interface
│   │   │   └── encoder_base.h/cpp# Abstract encoder interface
│   │   ├── classical/            # Classical ciphers
│   │   │   ├── caesar.h/cpp      # Caesar cipher
│   │   │   ├── vigenere.h/cpp    # Vigenère cipher
│   │   │   ├── atbash.h/cpp      # Atbash cipher
│   │   │   └── substitution.h/cpp# Simple substitution
│   │   ├── encoding/             # Encoding schemes
│   │   │   ├── base64.h/cpp      # Base64 encoding
│   │   │   ├── hex.h/cpp         # Hexadecimal encoding
│   │   │   └── binary.h/cpp      # Binary encoding
│   │   └── modern/               # Modern ciphers
│   │       ├── xor.h/cpp         # XOR cipher
│   │       └── affine.h/cpp      # Affine cipher
│   ├── ui/                       # User interface components
│   │   ├── widgets/              # Custom widgets
│   │   │   ├── input_widget.h/cpp    # Text input area
│   │   │   ├── output_widget.h/cpp   # Results display
│   │   │   ├── pipeline_view.h/cpp   # Pipeline visualization
│   │   │   └── cipher_config.h/cpp   # Cipher configuration
│   │   ├── dialogs/              # Dialog windows
│   │   │   ├── about_dialog.h/cpp    # About information
│   │   │   └── help_dialog.h/cpp     # Help system
│   │   └── components/           # Reusable UI components
│   │       ├── progress_bar.h/cpp    # Custom progress display
│   │       └── log_viewer.h/cpp      # Verbose logging display
│   ├── utils/                    # Utility functions
│   │   ├── file_handler.h/cpp    # File I/O operations
│   │   ├── text_processor.h/cpp  # Text manipulation utilities
│   │   ├── encoding_detector.h/cpp # Encoding detection
│   │   └── string_utils.h/cpp    # String utility functions
│   ├── data/                     # Data files and resources
│   │   ├── dictionaries/         # Word lists for analysis
│   │   │   ├── english.txt       # English dictionary
│   │   │   ├── common_words.txt  # Common words list
│   │   │   └── languages/        # Other language dictionaries
│   │   └── patterns/             # Pattern recognition data
│   │       ├── morse.txt         # Morse code patterns
│   │       └── frequencies.txt   # Letter frequency data
│   └── tests/                    # Unit tests
│       ├── test_ciphers.cpp      # Cipher implementation tests
│       ├── test_analysis.cpp     # Analysis module tests
│       └── test_pipeline.cpp     # Pipeline functionality tests
├── resources/                    # Qt resources
│   ├── icons/                    # Application icons
│   ├── styles/                   # Custom stylesheets
│   └── resources.qrc             # Qt resource file
├── docs/                         # Documentation
│   ├── api/                      # API documentation
│   ├── user_guide/               # User documentation
│   └── developer_guide/          # Development documentation
├── examples/                     # Example inputs/outputs
│   ├── sample_ciphers/           # Sample encrypted texts
│   └── test_cases/               # Test case inputs
└── scripts/                      # Build and utility scripts
    ├── build.sh                  # Build script
    ├── test.sh                   # Test runner
    └── install.sh                # Installation script
```

## Phase Implementation Order 🚀

### Phase 1: Core Architecture
1. Create `src/core/` with base classes
2. Implement `cipher_engine.h/cpp` framework
3. Build `cipher_registry.h/cpp` system
4. Create `pipeline/` management system

### Phase 2: Basic Ciphers
1. Implement `ciphers/base/` abstract classes
2. Add `ciphers/classical/` basic ciphers
3. Create `ciphers/encoding/` schemes
4. Build `utils/` support functions

### Phase 3: Analysis Engine
1. Develop `core/analysis/` modules
2. Create `data/dictionaries/` resources
3. Implement pattern recognition
4. Build confidence scoring

### Phase 4: UI Enhancement
1. Create `ui/widgets/` for cipher-specific UI
2. Build `ui/components/` for pipeline visualization
3. Add `resources/` for better styling
4. Implement progress tracking

### Phase 5: Testing & Documentation
1. Comprehensive `tests/` suite
2. Complete `docs/` documentation
3. Add `examples/` for users
4. Performance optimization

## File Naming Conventions 📝
- **Classes**: PascalCase (e.g., `CipherEngine`, `CaesarCipher`)
- **Files**: snake_case (e.g., `cipher_engine.h`, `caesar_cipher.cpp`)
- **Directories**: lowercase (e.g., `ciphers/`, `analysis/`)
- **Constants**: UPPER_SNAKE_CASE (e.g., `MAX_ITERATIONS`)
- **Variables**: camelCase (e.g., `inputText`, `resultConfidence`)

## Dependencies & Libraries 📚
- **Qt5**: Core, Widgets (existing)
- **Future additions**:
  - Qt5::Test (for unit testing)
  - OpenSSL (for cryptographic functions)
  - Boost (for advanced algorithms)
  - JSON library (for configuration files)
