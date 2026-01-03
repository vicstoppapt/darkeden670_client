# DarkEden v670 Client – Organization & Next Actions

## What you copied
You copied the entire Windows XP VM C: drive into `DK670_Source/Client/`. It includes:
- `darkeden/` – Client source and libs (Visual Studio .NET 2003 projects)
- `STLport-4.6.1/` and `STLport-4.6--222.rar` – STLPort sources
- `dx7.1/` – DirectX 7 SDK headers/libs
- `Program Files/` – Installed tools (VS .NET 2003, UltraEdit, WinRAR, 7-Zip, etc.)
- `exe/` and `www/Updater.exe` – Likely built client/updater artifacts
- System folders (`WINDOWS/`, `[SYSTEM]/`, `Documents and Settings/`, etc.)

Currently `dev-workstation/` and `prod-environment/` inside `Client/` are empty. Below is what should go where.

---

## Target layout

### dev-workstation/  (keep source + build tool deps)
- `darkeden/` (full source tree)
- `STLport-4.6.1/` (and optionally the `STLport-4.6--222.rar` archive)
- `dx7.1/` (DirectX 7 SDK headers/libs)
- Build scripts or project files:
  - `darkeden/Designed_Chs/Project/...`
  - `darkeden/Designed_Common/Project/...`
- Any tool-specific SDKs needed to build (e.g., additional libs you find under `Program Files/…` if required by the projects)

### prod-environment/  (runtime/binaries only)
- Game binaries/updaters:
  - `exe/` (contains `fk.exe` etc.)
  - `www/Updater.exe`
  - Any Release output from `darkeden/Designed_*/*/Release/` if those are the shipping client binaries
- Runtime data/assets if present outside the builds (check `Documents and Settings/Administrator/바탕 화면/` for client folder if needed)
- Minimal runtime dependencies (if you identify specific DLLs not present on a clean XP)

### Archives / installers (keep but separate from dev/prod)
- Visual Studio .NET 2003 installers (`a/` looks like VS 2003 media)
- Any other installers you need to preserve
- Keep under a new folder, e.g., `installers/`, so they don’t mix with dev/prod

### Exclude / do not carry into repos
- Windows system files (`WINDOWS/`, `[SYSTEM]/`, `System Volume Information/`, `RECYCLER/`, pagefile, ntldr, etc.)
- User profiles unless you need specific game data

---

## Devcontainer feasibility (client)
- **Client build requires Windows toolchain**: Visual Studio .NET 2003, DirectX 7 SDK, and likely Windows-only dependencies.
- Docker/Linux devcontainers **cannot host the Windows VS2003 toolchain**, so a Linux devcontainer won’t build the client.
- Recommendation:
  - Use a Windows VM with VS .NET 2003 + DX7 SDK to build the client.
  - Keep the Linux devcontainer (already created under `server/.devcontainer/`) for server builds only.

---

## Immediate next actions
1. **Sort files** (manual move):
   - Move `darkeden/`, `STLport-4.6.1/`, `dx7.1/` into `Client/dev-workstation/`.
   - Move `exe/`, `www/Updater.exe`, and any Release binaries into `Client/prod-environment/`.
   - Create `Client/installers/` and move installer media there (e.g., `a/`, `30435a04f32d539a9f/`, `STLport-4.6--222.rar`).

2. **Identify client runtime folder**:
   - Locate the actual deployed client folder (often under `Documents and Settings/Administrator/바탕 화면/` or similar) and copy it into `prod-environment/` as `client-runtime/`.

3. **Document toolchain requirements**:
   - Windows XP/7 VM with Visual Studio .NET 2003.
   - DirectX 7 SDK (`dx7.1`).
   - STLPort 4.6.1 (or adjust to use modern STL if you migrate toolchain).

4. **Decide on build host**:
   - **Preferred**: Keep a dedicated Windows VM for client builds.
   - If you attempt modernization: migrate projects to a newer Visual Studio (may require code/SDK updates).

5. **Backup**:
   - Archive `Client/dev-workstation/` and `Client/prod-environment/` after sorting.

---

## What’s hard/impossible today
- Building the client in the Linux devcontainer (needs Windows VS2003).
- Getting modern downloads for legacy toolchain (VS .NET 2003, DX7) from official sources; rely on existing installers you already have (`a/`, `30435a04f32d539a9f/`).
- Replacing STLPort with modern libstdc++ without touching code/Makefiles—possible but requires project changes and likely a newer compiler/IDE.

---

## References
- Server devcontainer: `server/.devcontainer/` (Linux, for server builds)
- Client docs to update after sorting:
  - `Client/ORGANIZATION_PLAN.md` (this file)

