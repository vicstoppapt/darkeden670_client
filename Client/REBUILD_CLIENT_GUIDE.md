# DarkEden v670 - Client Rebuild Guide

## Overview

The compiled client (`fk.exe`) has hardcoded server addresses that point to non-existent servers. This guide explains how to rebuild the client with the correct server configuration.

## Current Server Configuration

- **WSL IP**: `172.22.45.117` (may change after WSL restart)
- **Login Server Port**: `9999`
- **Game Server TCP Port**: `9998`
- **Game Server UDP Port**: `9997`
- **Shared Server Port**: `9977`

## Quick Solution: Command Line Parameter

The client supports a command-line parameter to override the server address:

```batch
fk.exe NEWSTART Futec(172.22.45.117:9999) 0000000003
```

This bypasses the hardcoded configuration and connects directly to the specified server.

**Note**: The batch files in `prod-environment/client-runtime/` have been updated to use this method.

## Rebuilding the Client

### Prerequisites

1. **Visual Studio 2003** (or compatible version)
2. **DirectX 7 SDK**
3. **STLport 4.6.1** (included in project)
4. All required libraries (see project dependencies)

### Source Code Location

```
DK670_Source/Client/dev-workstation/darkeden/Designed_Common/Project/Client/
```

### Key Files to Modify

#### 1. Server Configuration Files

The client reads server configuration from `.inf` files. These are already configured:

- `prod-environment/client-runtime/data/info/GameClient.inf`
- `prod-environment/client-runtime/data/info/GameClient2.inf`
- `prod-environment/client-runtime/data/info/FileDef.inf`

**Current Configuration**:
```
MaxLoginServerAddress : 1
LoginServerAddress : 172.22.45.117
LoginServerAddress1 : 172.22.45.117
LoginServerPortNum : 1
LoginServerPort : 9999
LoginServerCheckPort : 9999
LoginServerBasePort : 9999
```

#### 2. Source Code Files

The client source code reads from these configuration files. No source code changes are needed if the `.inf` files are correct.

**Key Source Files**:
- `GameInit.cpp` - Reads `LoginServerAddress` and `LoginServerPort` from `GameClient.inf`
- `Client.cpp` - Handles command-line parsing (Futec parameter)

### Build Process

1. **Open the Project**:
   ```
   DK670_Source/Client/dev-workstation/darkeden/Designed_Chs/Project/Client.vcproj
   ```

2. **Verify Configuration**:
   - Ensure `GameClient.inf` and `GameClient2.inf` are in the output directory
   - Check that `FileDef.inf` points to the correct paths

3. **Build**:
   - Select "Release" configuration
   - Build the project
   - Output will be in the configured output directory (typically `C:\exe\fk.exe`)

4. **Copy Files**:
   - Copy the new `fk.exe` to `prod-environment/client-runtime/`
   - Ensure all `.inf` files are in `data/info/` directory

### Updater Configuration

The `Updater.exe` likely has hardcoded update server addresses. To disable or modify:

1. **Option 1**: Skip the updater entirely (use `launch-direct.bat`)
2. **Option 2**: Modify updater source code (if available)
3. **Option 3**: Use command-line parameter to bypass updater

### Testing

After rebuilding:

1. **Test with Command Line**:
   ```batch
   fk.exe NEWSTART Futec(172.22.45.117:9999) 0000000003
   ```

2. **Test with Configuration Files**:
   ```batch
   fk.exe 0000000003
   ```
   (Should read from `GameClient.inf`)

3. **Verify Connection**:
   - Client should connect to login server at `172.22.45.117:9999`
   - Check server logs to confirm connection

## Updating WSL IP Address

If WSL IP changes after restart:

1. **Get New IP**:
   ```powershell
   wsl hostname -I
   ```

2. **Update Configuration Files**:
   - `GameClient.inf`
   - `GameClient2.inf`
   - Batch files (if using Futec parameter)

3. **Or Rebuild Client** with new IP in configuration files

## Troubleshooting

### Client Won't Connect

1. **Check WSL IP**: `wsl hostname -I`
2. **Verify Ports**: Ensure server is running and ports are accessible
3. **Check Firewall**: Windows Firewall may block connections
4. **Use Command Line Parameter**: `Futec(IP:Port)` overrides all configuration

### Updater Issues

- **Skip Updater**: Use `launch-direct.bat` or command-line parameter
- **Updater Source**: If updater source is available, modify update server addresses

### Build Errors

- **Missing Dependencies**: Ensure all required libraries are installed
- **Visual Studio Version**: Client was built with VS 2003, newer versions may have compatibility issues
- **DirectX SDK**: Ensure DirectX 7 SDK is properly installed

## Current Status

✅ **Configuration Files Created**: `GameClient.inf`, `GameClient2.inf`, `FileDef.inf`  
✅ **Batch Files Updated**: All launchers use `Futec(IP:Port)` parameter  
✅ **Server Configuration**: Points to `172.22.45.117:9999`  

⚠️ **Updater**: May still try to connect to non-existent update server (bypassed by using command-line parameter)

## Next Steps

1. **Test Current Setup**: Use `launch-direct.bat` to test with existing compiled client
2. **Rebuild if Needed**: If command-line parameter doesn't work, rebuild the client
3. **Update WSL IP**: Update configuration if WSL IP changes

