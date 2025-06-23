# ACT (Automated Cipher Translator) - TODO List

## Project Overview
Multi-layer cipher decoder for CTF and educational purposes with intelligent detection, processing pipeline visualization, and custom algorithm support.

## Phase 1: Core Foundation
### UI Framework ✅
- [x] Modern Qt5 interface with animations
- [x] Sidebar navigation
- [x] Card-based dashboard
- [x] Remove menu bar for cleaner look

### Core Architecture 🔄
- [ ] Design cipher detection engine
- [ ] Implement processing pipeline framework
- [ ] Create cipher registry system
- [ ] Build entropy analysis module
- [ ] Implement dictionary matching system

## Phase 2: Cipher Implementation
### Basic Ciphers 📋
- [ ] Caesar cipher (with auto key detection)
- [ ] ROT13/ROT47
- [ ] Atbash cipher
- [ ] Simple substitution
- [ ] Vigenère cipher
- [ ] Base64/Base32 encoding
- [ ] Hex encoding
- [ ] Binary encoding
- [ ] XOR cipher (single/multi-byte key)
- [ ] Affine cipher

### Advanced Ciphers 📋
- [ ] Playfair cipher
- [ ] Rail fence cipher
- [ ] Columnar transposition
- [ ] Book cipher
- [ ] Morse code
- [ ] Bacon cipher
- [ ] Polybius square

## Phase 3: Detection & Analysis
### Auto-Detection 📋
- [ ] Entropy analysis implementation
- [ ] Character frequency analysis
- [ ] Pattern recognition (repeated sequences)
- [ ] Encoding detection (UTF-8, ASCII, hex, etc.)
- [ ] Statistical analysis for cipher type hints

### Smart Heuristics 📋
- [ ] Develop scoring system for cipher likelihood
- [ ] Implement dictionary matching with multiple languages
- [ ] Create readability assessment algorithms
- [ ] Build confidence scoring for results

## Phase 4: Processing Pipeline
### Pipeline Engine 📋
- [ ] Design pipeline workflow system
- [ ] Implement step-by-step processing
- [ ] Create branching logic for multiple attempts
- [ ] Build fallback to brute force combinations
- [ ] Add user intervention points

### Visualization 📋
- [ ] Pipeline flow diagram UI component
- [ ] Real-time step visualization
- [ ] Intermediate result display
- [ ] Progress indicators with cancel options
- [ ] Verbose logging system

## Phase 5: Input/Output System
### Input Methods 📋
- [ ] Text paste area with syntax highlighting
- [ ] File upload (txt, binary, etc.)
- [ ] Drag & drop support
- [ ] URL input for web content
- [ ] Clipboard integration

### Output Features 📋
- [ ] Multiple format export (txt, json, csv)
- [ ] Save processing sessions
- [ ] Export pipeline configurations
- [ ] Share results functionality

## Phase 6: Custom Algorithms
### Extension System 📋
- [ ] Plugin architecture design
- [ ] Custom cipher definition format
- [ ] User script execution environment (sandboxed)
- [ ] Algorithm validation system
- [ ] Community cipher sharing

### Scripting Support 📋
- [ ] Python script integration
- [ ] JavaScript execution environment
- [ ] Template system for common patterns
- [ ] Debug mode for custom algorithms

## Phase 7: Advanced Features
### Multi-layer Processing 📋
- [ ] Recursive decoding (cipher within cipher)
- [ ] Automatic layer detection
- [ ] Cross-layer analysis
- [ ] Optimization for deep nesting

### Educational Features 📋
- [ ] Step-by-step explanations
- [ ] Cipher theory information
- [ ] Interactive tutorials
- [ ] Historical context for ciphers

### Performance & Optimization 📋
- [ ] Multi-threading for parallel processing
- [ ] Caching system for repeated operations
- [ ] Memory optimization for large inputs
- [ ] Progress persistence across sessions

## Phase 8: User Experience
### Settings & Configuration 📋
- [ ] User preferences system
- [ ] Custom dictionary management
- [ ] Performance tuning options
- [ ] Theme customization

### Help & Documentation 📋
- [ ] In-app help system
- [ ] Cipher reference guide
- [ ] Video tutorials integration
- [ ] Community forum links

## Technical Debt & Maintenance
- [ ] Unit test framework
- [ ] Integration tests
- [ ] Performance benchmarking
- [ ] Code documentation
- [ ] Error handling improvements
- [ ] Memory leak detection

## Future Considerations
- [ ] Web interface version
- [ ] Mobile app adaptation
- [ ] API for external integration
- [ ] Machine learning for pattern recognition
- [ ] Quantum-resistant cipher analysis

---
**Priority Levels:**
- 🔥 Critical (Phase 1-2)
- ⚡ High (Phase 3-4)  
- 📋 Medium (Phase 5-6)
- 💡 Nice to have (Phase 7-8)

**Status Legend:**
- ✅ Completed
- 🔄 In Progress
- 📋 Todo
- ❌ Blocked
- 🧪 Testing
