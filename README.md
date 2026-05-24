# CS2-Bot-Locker

Metamod:Source plugin. Three orthogonal per-slot bot locks:

- **Weapon** — pin a bot to one weapon slot; AI switches are blocked.
- **Aim** — freeze `CCSBot::Upkeep`; view holds still, AI keeps deciding/moving/shooting.
- **All** — freeze both `CCSBot::Update` and `CCSBot::Upkeep`; external code can take over.

Locks stack and clear independently.

**Version**: 0.3.0 · **ABI**: 4

## Slots

| Target  | Engine | Weapon                  |
| ------- | ------ | ----------------------- |
| `Slot1` | 0      | Primary                 |
| `Slot2` | 1      | Pistol / Zeus           |
| `Slot3` | 2      | Knife                   |
| `Slot4` | 3      | Grenades      			 |
| `Slot5` | 4      | C4                      |

## Install

- `BotLocker.dll` → `csgo/addons/BotLocker/bin/win64/`
- `gamedata.json` → `csgo/addons/BotLocker/`
- `BotLocker.vdf`  → `csgo/addons/metamod/`

## Build

Env: `HL2SDKCS2`, `MMSOURCE_DEV`, `CSGO_PROTO`, `protoc` on PATH.

```
cmake -B build -G "Visual Studio 18 2026" -A x64
cmake --build build --config Release
```

## Commands

```
bl_lock <all|aim|weapon> <slot> [slot1..slot5]
bl_unlock <all|aim|weapon> <slot>
bl_unlock_all <all|aim|weapon>
bl_status
```

`weapon` mode requires the weapon slot as the third argument.

```
bl_lock aim 1                # freeze bot 1's view, AI still runs
bl_lock all 1                # full freeze
bl_lock weapon 1 slot3       # force bot 1 to knife and hold
bl_unlock_all weapon         # clear every weapon lock
```

## CounterStrikeSharp API

Drop `scripts/BotLocker.NativeApi.cs` into your project.

```csharp
using BotLockerApi;

if (!BotLocker.IsCompatible()) return;   // requires ABI 4

BotLocker.Lock(slot, LockKind.Aim);
BotLocker.Lock(slot, LockKind.All);
BotLocker.Lock(slot, LockTarget.Slot3);  // weapon lock
BotLocker.Unlock(slot, LockKind.Aim);
BotLocker.UnlockAll(LockKind.Weapon);
BotLocker.IsLocked(slot, LockKind.Aim);
BotLocker.GetWeaponLock(slot);
```

Main thread only.
