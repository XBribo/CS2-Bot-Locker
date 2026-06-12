// version_targets.h
//
// Single source of truth for every reverse-engineered offset referenced by
// the plugin. Grouped by the engine class each offset belongs to.

#pragma once

namespace cs2bl::targets
{
    // ---- CCSBot ----

    // AI-ran-this-tick byte flag; set to 1 to fake a completed tick
    inline constexpr int kBot_AiTickedFlag = 21196;
    // CCSBot -> pawn (CCSPlayerPawn*)
    inline constexpr int kBot_Pawn = 0x18;
    // Look-angle spring targets (m_lookPitch/m_lookYaw) + their velocities,
    // as read by CCSBot::UpdateLookAngles. Unused by 1:1 view replay.
    inline constexpr int kBot_LookPitch = 0x5974;
    inline constexpr int kBot_LookPitchVel = 0x5978;
    inline constexpr int kBot_LookYaw = 0x597C;
    inline constexpr int kBot_LookYawVel = 0x5980;

    // ---- CBaseEntity / CEntityIdentity ----

    // entity -> CEntityIdentity*
    inline constexpr int kEnt_Identity = 0x10;
    // CEntityIdentity -> m_EHandle (low 15 bits = entity index)
    inline constexpr int kEntIdentity_EHandle = 0x10;
    // m_fFlags (bit0 = FL_ONGROUND)
    inline constexpr int kEnt_Flags = 0x388;
    // m_vecAbsVelocity
    inline constexpr int kEnt_AbsVelocity = 0x38C;
    // m_vecVelocity
    inline constexpr int kEnt_Velocity = 0x398;

    // ---- CCSPlayerPawn ----

    // m_pWeaponServices
    inline constexpr int kPawn_WeaponServices = 0xA00;
    // m_hController (CHandle)
    inline constexpr int kPawn_Controller = 0xB80;
    // m_hOriginalController (CHandle)
    inline constexpr int kPawn_OriginalController = 0xB84;
    // CCSPlayerPawn -> v_angle (QAngle)
    inline constexpr int kPawn_ViewAngle = 0xAB8;
    // CCSPlayerPawn vtable byte offset of GetEyeAngles(QAngle &out); from
    // UpdateLookAngles decomp (vtable+1504). Index = 1504/8 = 188.
    inline constexpr int kPawnVt_GetEyeAngles = 1504;

    // ---- CCSPlayer_WeaponServices ----

    // m_hActiveWeapon (CHandle)
    inline constexpr int kWs_ActiveWeapon = 0x60;

    // ---- CBasePlayerWeapon ----

    // m_AttributeManager(0x958) -> m_Item(0x50) -> m_iItemDefinitionIndex(0x38),
    // all embedded; net direct add (no deref)
    inline constexpr int kWeapon_ItemDefIndex = 0x958 + 0x50 + 0x38; // 0x9E0

    // ---- CCSPlayer_MovementServices ----

    // m_pawn (CCSPlayerPawn*)
    inline constexpr int kServices_Pawn = 56;
    // m_nButtons button mask
    inline constexpr int kServices_Buttons = 88;

    // ---- CUserCmd ----

    inline constexpr int kCmd_ForwardMove = 44;
    inline constexpr int kCmd_SideMove = 48;
    inline constexpr int kCmd_UpMove = 52;
    inline constexpr int kCmd_ViewPitch = 68;
    inline constexpr int kCmd_ViewYaw = 72;
    inline constexpr int kCmd_ViewRoll = 76;
    inline constexpr int kCmd_ViewPitchInput = 244;
    inline constexpr int kCmd_ViewYawInput = 248;
    inline constexpr int kCmd_ViewRollInput = 252;

} // namespace cs2bl::targets
