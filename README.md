# CS2-BotWeaponLock

Metamod:Source native plugin. Locks a CS2 bot to a weapon slot and blocks the AI from switching away.

**Version**: 0.1.2
**Native ABI**: 2

## Slot Map

| Target | Engine | Weapons |
|---|---|---|
| `Slot1` | 0 | Primary (rifle/sniper/SMG/shotgun) |
| `Slot2` | 1 | Pistol |
| `Slot3` | 2 | Knife / Zeus |
| `Slot4` | 3 | Grenades (HE/flash/smoke/molotov/decoy) |
| `Slot5` | 4 | C4 |

## Install

- `BotWeaponLock.dll` → `csgo/addons/BotWeaponLock/bin/win64/`
- `gamedata.json` → `csgo/addons/BotWeaponLock/`
- `BotWeaponLock.vdf` → `csgo/addons/metamod/`

## Build

Env vars: `HL2SDKCS2`, `MMSOURCE_DEV`, `CSGO_PROTO`, `protoc` on PATH.

```
cmake -B build -G "Visual Studio 18 2026" -A x64
cmake --build build --config Release
```

## Console Commands

```
blw_lock <slot> <slot1|slot2|slot3|slot4|slot5>
blw_unlock <slot>
blw_unlock_all
blw_status
```

## CounterStrikeSharp API

Drop `scripts/BotWeaponLock.NativeApi.cs` into your project.

```csharp
using BotWeaponLockApi;

BotWeaponLock.IsCompatible();              // bool, check on load
BotWeaponLock.Lock(slot, LockTarget.Slot3);// bool
BotWeaponLock.Unlock(slot);                // bool
BotWeaponLock.UnlockAll();                 // void
BotWeaponLock.GetLock(slot);               // LockTarget
```

Main thread only.
