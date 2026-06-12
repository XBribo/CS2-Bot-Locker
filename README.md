# CS2-Bot-Locker

CS2-Bot-Locker is a Metamod:Source plugin for Counter-Strike 2 that can lock Bot's Weapon/Aim/Jump/All
It can be installed on win64 clients.

- **Weapon** — pin a bot to one weapon slot; AI switches are blocked.
- **Aim** — freeze `CCSBot::Upkeep`; view holds still, AI keeps deciding/moving.
- **Jump** — block `CCSBot::Jump`; bot stops jumping, move/fire/aim unaffected.
- **All** — freeze both `CCSBot::Update` and `CCSBot::Upkeep`.
- **Inject** — hook `CCSPlayer_MovementServices::ProcessUsercmd` to drive a bot's
  move/view/buttons from external code . Move values are normalized `-1..+1`, scaled by the engine's maxspeed.

## Your stars⭐ are my motivation to keep updating

**Version**: 0.4.0 · **ABI**: 8

------------------------------------------------------------------------

## Slots

| Target  | Engine | Weapon                  |
| ------- | ------ | ----------------------- |
| `Slot1` | 0      | Primary                 |
| `Slot2` | 1      | Pistol                  |
| `Slot3` | 2      | Knife / Zeus            |
| `Slot4` | 3      | Grenades                |
| `Slot5` | 4      | C4                      |

------------------------------------------------------------------------

## Install

- `BotLocker.dll` → `csgo/addons/BotLocker/bin/win64/`
- `gamedata.json` → `csgo/addons/BotLocker/`
- `BotLocker.vdf`  → `csgo/addons/metamod/`

------------------------------------------------------------------------

## Build

Env: `HL2SDKCS2`, `MMSOURCE_DEV`, `CSGO_PROTO`, `protoc` on PATH.

```
cmake -B build -G "Visual Studio 18 2026" -A x64
cmake --build build --config Release
```

------------------------------------------------------------------------

## Commands

```
bl_lock <all|aim|jump|weapon> <slot> [slot1..slot5]
bl_unlock <all|aim|jump|weapon> <slot>
bl_unlock_all <all|aim|jump|weapon>
bl_inject <slot> <forward> <side> <yaw> [buttons]
bl_inject_clear <slot>
bl_status
```

`weapon` mode requires the weapon slot as the third argument.

```
bl_lock aim 1                # freeze bot 1's view, AI still runs
bl_lock jump 1               # bot 1 can no longer jump
bl_lock all 1                # full freeze
bl_lock weapon 1 slot3       # force bot 1 to knife
bl_unlock_all weapon         # clear every weapon lock
```

`bl_inject` drives a bot's UserCmd directly. `forward`/`side` are normalized
`-1..+1`; `buttons` is an optional bitmask (e.g. `1`=attack, `2`=jump, `4`=duck).

```
bl_inject 1 1 0 0            # bot 1 walks straight forward
bl_inject 1 0 1 90           # bot 1 strafes right, facing yaw 90
bl_inject 1 1 0 0 2          # walk forward while jumping
bl_inject_clear 1            # stop injecting
```

Button bitmask (OR values together, decimal or `0x` hex):

| Button       | Value | Button         | Value |
| ------------ | ----- | -------------- | ----- |
| `IN_ATTACK`  | 1     | `IN_BACK`      | 16    |
| `IN_JUMP`    | 2     | `IN_USE`       | 32    |
| `IN_DUCK`    | 4     | `IN_MOVELEFT`  | 512   |
| `IN_FORWARD` | 8     | `IN_MOVERIGHT` | 1024  |

Movement uses `forward`/`side`, not `IN_FORWARD`; buttons are for actions like
attack/jump/duck. E.g. `bl_inject 1 1 0 0 6` walks forward while jumping and
ducking (`2|4`).

------------------------------------------------------------------------

## CounterStrikeSharp API

Drop `scripts/BotLocker.NativeApi.cs` into your project.

```csharp
using BotLockerApi;

if (!BotLocker.IsCompatible()) return;   // requires ABI 5

BotLocker.Lock(slot, LockKind.Aim);
BotLocker.Lock(slot, LockKind.Jump);
BotLocker.Lock(slot, LockKind.All);
BotLocker.Lock(slot, LockTarget.Slot3);  // weapon lock
BotLocker.Unlock(slot, LockKind.Aim);
BotLocker.UnlockAll(LockKind.Weapon);
BotLocker.IsLocked(slot, LockKind.Aim);
BotLocker.GetWeaponLock(slot);
```

Main thread only.

------------------------------------------------------------------------

## License

GPL-v3.0

------------------------------------------------------------------------

## Author

**XBribo**
