# 🐍 Snake Game (C++20 / SFML 3)

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)
![SFML 3.0.2](https://img.shields.io/badge/SFML-3.0.2-green.svg)
![macOS](https://img.shields.io/badge/platform-macOS%20%7C%20Windows-lightgrey.svg)
![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)

A modern, cross-platform classic Snake game built from scratch using **C++20** and **SFML 3.0.2**. Features polished UI, high score management, macOS native bundling, and automated updates integration via Sparkle.

---

## 🎮 Features

- **Classic Gameplay**: Smooth grid movement, food generation, score and survival timer.
- **Modern Input Handling**: Non-blocking window events and responsive controls.
- **Cross-Platform Architecture**: Clean separation of platform-dependent logic (macOS Bundle RPATH and path fixing).
- **Auto-Updater Integration**: Sparkle Framework integrated natively for seamless macOS background updates.
- **Portable Asset Loading**: Dynamic working-directory resolution ensuring seamless execution inside `.app` bundles and standard bin directories.

---

## 📦 Downloads (Play the Game)

Pre-built binaries are available in the **[Releases](../../releases)** section.

- **macOS (Apple Silicon / Intel)**: Download the `.dmg` file, open it, and drag `Snake.app` to your Applications folder.
- **Windows**: Download the `.zip` archive, extract it, and run `Snake.exe`.

---

## 🛠️ Tech Stack & Prerequisites

- **Language**: C++20
- **Graphics & Audio**: SFML 3.0.2
- **Build System**: CMake 3.14+ / CPack
- **Frameworks (macOS)**: Sparkle 2.x, AppKit, Foundation

---

## 🏗️ Building from Source

### macOS

1. **Install Dependencies**:
   ```bash
   brew install sfml cmake