# DarkEden v670 Client - Development & Production

## 📁 Directory Structure

```
Client/
├── dev-workstation/      # Source code and development tools
│   ├── darkeden/         # Client source code (Visual Studio .NET 2003 projects)
│   ├── STLport-4.6.1/    # STLPort library (required for compilation)
│   └── dx7.1/            # DirectX 7 SDK (headers and libraries)
│
├── prod-environment/      # Compiled binaries and runtime files
│   ├── client-runtime/   # Complete client runtime (executable + data)
│   ├── exe/              # Additional executables and build artifacts
│   └── www/              # Updater executable
│
└── installers/           # Installation media and archives
    ├── vs2003-installer/ # Visual Studio .NET 2003 installation files
    ├── vs2003-update/    # VS2003 update/SP files
    ├── client.zip         # Client archive backup
    └── STLport-4.6--222.rar  # STLPort archive
```

---

## 🛠️ Development Environment Requirements

### Required Software

1. **Windows XP / Windows 7** (32-bit recommended)
   - Windows XP SP3 is the original development environment
   - Windows 7 32-bit may work but not tested

2. **Visual Studio .NET 2003** (Visual C++ 7.1)
   - Installation files: `installers/vs2003-installer/`
   - Update files: `installers/vs2003-update/`
   - **Note**: VS2003 is no longer available from Microsoft. Use the provided installers.

3. **DirectX 7 SDK**
   - Headers/Libs: `dev-workstation/dx7.1/`
   - Must be accessible to compiler (add to include/lib paths)

4. **STLPort 4.6.1**
   - Source: `dev-workstation/STLport-4.6.1/`
   - Pre-built libraries: `dev-workstation/STLport-4.6.1/lib/`
   - **Note**: Modern compilers use libstdc++/MSVC STL. STLPort is legacy.

### Project Files

- **Main Client Project**: `dev-workstation/darkeden/Designed_Common/Project/Client/`
  - `Client.sln` - Visual Studio solution file
  - `Client.vcproj` - Project file

- **UI Library**: `dev-workstation/darkeden/Designed_Common/Project/NEW - VS_UI/`
  - UI components library

- **Libraries**: `dev-workstation/darkeden/Designed_Common/Lib/`
  - Pre-compiled static libraries (.lib files)
  - Headers (.h files)

---

## 🔨 Building the Client

### Prerequisites Setup

1. **Install Visual Studio .NET 2003**
   ```powershell
   # Run installer from installers/vs2003-installer/setup.exe
   # Follow installation wizard
   ```

2. **Configure DirectX 7 SDK Paths**
   - Add to Visual Studio include paths: `dev-workstation/dx7.1/INCLUDE`
   - Add to Visual Studio library paths: `dev-workstation/dx7.1/LIB`

3. **Configure STLPort Paths**
   - Add to include paths: `dev-workstation/STLport-4.6.1/stlport`
   - Add to library paths: `dev-workstation/STLport-4.6.1/lib`
   - Link against: `stlport_vc71.lib` (Release) or `stlport_vc71_stldebug.lib` (Debug)

### Build Steps

1. **Open Solution**
   ```
   Open: dev-workstation/darkeden/Designed_Common/Project/Client/Client.sln
   ```

2. **Select Configuration**
   - **Release**: Production build (optimized)
   - **Debug**: Development build (with debug symbols)

3. **Build**
   - Press `F7` or `Build → Build Solution`
   - Output: `dev-workstation/darkeden/Designed_Common/Project/Client/Release/Client.exe`

4. **Copy Runtime Files**
   - Copy built executable to `prod-environment/client-runtime/`
   - Ensure all DLLs and data files are present

---

## 🎮 Running the Client

### Runtime Requirements

- **Windows XP SP3** or compatible Windows version
- **DirectX 7** runtime (usually pre-installed on Windows XP)
- **Visual C++ 7.1 Runtime** (`msvcr71.dll`, `msvcp71.dll`)
  - Included in `prod-environment/client-runtime/`

### Launch

1. Navigate to `prod-environment/client-runtime/`
2. Run `fk.exe` (main client executable)
3. Or run `Updater.exe` to check for updates first

### Configuration Files

- `interface.ini` - Client interface settings
- `FileListVersion.inf` - File version information
- `data/darkedeneng.ini` - Game data configuration
- `data/info/*.inf` - Various game info files

---

## 📦 Production Deployment

### Client Package Structure

```
client-runtime/
├── fk.exe                 # Main client executable
├── Updater.exe            # Update checker
├── *.dll                  # Required DLLs
├── data/                  # Game data files
│   ├── music/            # Background music (.ogg files)
│   ├── info/             # Configuration files
│   └── font/             # Font files
├── temp/                  # Temporary/cache files
└── UserSet/               # User settings and saves
```

### Distribution

1. **Package** `prod-environment/client-runtime/` into ZIP
2. **Include** all DLLs and data files
3. **Test** on clean Windows XP installation
4. **Document** server connection settings in `interface.ini`

---

## ⚠️ Known Limitations & Challenges

### Impossible/Extremely Difficult Today

1. **Visual Studio .NET 2003**
   - ❌ No longer available from Microsoft
   - ✅ **Solution**: Use provided installers in `installers/`
   - ⚠️ May not install on Windows 10/11 (use Windows XP/7 VM)

2. **DirectX 7 SDK**
   - ❌ No longer available from Microsoft
   - ✅ **Solution**: Use provided SDK in `dev-workstation/dx7.1/`
   - ⚠️ DirectX 7 is deprecated (modern Windows uses DirectX 9+)

3. **STLPort 4.6.1**
   - ❌ No longer maintained (last update: 2008)
   - ✅ **Solution**: Use provided STLPort in `dev-workstation/STLport-4.6.1/`
   - ⚠️ Modern compilers use standard C++ STL (libstdc++/MSVC STL)

4. **Building on Modern Windows**
   - ❌ VS2003 may not install on Windows 10/11
   - ✅ **Solution**: Use Windows XP/7 VM for development
   - ⚠️ Modern Visual Studio (2019+) requires code migration

5. **Linux DevContainer**
   - ❌ **Cannot build Windows client in Linux container**
   - ✅ **Solution**: Use Windows VM with VS2003
   - ⚠️ Client requires Windows-specific toolchain

### Modernization Options (Future)

1. **Migrate to Modern Visual Studio**
   - Update project files to VS2019/2022 format
   - Replace STLPort with standard C++ STL
   - Update DirectX 7 → DirectX 9/11 (major code changes)
   - **Effort**: High (weeks/months of work)

2. **Cross-Platform Build**
   - Port to modern C++ (C++11/14/17)
   - Use cross-platform graphics library (SDL, SFML)
   - **Effort**: Very High (complete rewrite)

---

## 🔍 File Structure Details

### Source Code (`dev-workstation/darkeden/`)

- **Designed_Common/Project/Client/** - Main client application
  - ~1,400 C++ source files (.cpp)
  - ~1,100 header files (.h)
  - Visual Studio project files (.vcproj, .sln)

- **Designed_Common/Lib/** - Static libraries
  - UI libraries, game logic libraries
  - Third-party libraries (Lua, OGG, etc.)

- **Designed_Chs/Project/** - Chinese client variant
  - Separate build configuration
  - Shared libraries with main client

### Runtime (`prod-environment/client-runtime/`)

- **Executables**: `fk.exe`, `Updater.exe`
- **DLLs**: Game libraries, DirectX, audio (OGG/Vorbis)
- **Data**: Game assets, configuration, music
- **User Data**: Settings, screenshots, saves

---

## 📚 Additional Resources

- **Server Documentation**: `../server/README.md`
- **Project Checklist**: `../PROJECT_SETUP_CHECKLIST.md`
- **Organization Plan**: `ORGANIZATION_PLAN.md` (this folder)

---

## 🚀 Quick Start

1. **Set up Windows XP/7 VM**
2. **Install VS2003** from `installers/vs2003-installer/`
3. **Open** `dev-workstation/darkeden/Designed_Common/Project/Client/Client.sln`
4. **Configure** include/lib paths (DirectX, STLPort)
5. **Build** (F7)
6. **Run** from `prod-environment/client-runtime/fk.exe`

---

**Last Updated**: 2024  
**Project**: DarkEden v670 Client

