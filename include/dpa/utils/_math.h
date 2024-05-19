#ifndef DPA__U_MATH_H
#define DPA__U_MATH_H

// Internal header
// Some math functions for inernal use only

#if __STDC_VERSION__ < 202200L
#define dpa__u_bitwidth(X) (sizeof(X)*CHAR_BIT)
#else
// C2X / C23: widthof() is not yet available, and _BitInt may have a bit width < sizeof(T)*CHAR_BIT
// We only handle bit widths up to 512. Also, this may fail if BITINT_MAXWIDTH < 512.
#define dpa__u_bitwidth(X) _Generic((X), \
    default: sizeof(X)*CHAR_BIT, \
    \
                         _BitInt(0x02): 0x02, _BitInt(0x03): 0x03, _BitInt(0x04): 0x04, \
    _BitInt(0x05): 0x05, _BitInt(0x06): 0x06, _BitInt(0x07): 0x07, _BitInt(0x08): 0x08, \
    _BitInt(0x09): 0x09, _BitInt(0x0A): 0x0A, _BitInt(0x0B): 0x0B, _BitInt(0x0C): 0x0C, \
    _BitInt(0x0D): 0x0D, _BitInt(0x0E): 0x0E, _BitInt(0x0F): 0x0F, _BitInt(0x10): 0x10, \
    \
    _BitInt(0x11): 0x11, _BitInt(0x12): 0x12, _BitInt(0x13): 0x13, _BitInt(0x14): 0x14, \
    _BitInt(0x15): 0x15, _BitInt(0x16): 0x16, _BitInt(0x17): 0x17, _BitInt(0x18): 0x18, \
    _BitInt(0x19): 0x19, _BitInt(0x1A): 0x1A, _BitInt(0x1B): 0x1B, _BitInt(0x1C): 0x1C, \
    _BitInt(0x1D): 0x1D, _BitInt(0x1E): 0x1E, _BitInt(0x1F): 0x1F, _BitInt(0x20): 0x20, \
    \
    _BitInt(0x21): 0x21, _BitInt(0x22): 0x22, _BitInt(0x23): 0x23, _BitInt(0x24): 0x24, \
    _BitInt(0x25): 0x25, _BitInt(0x26): 0x26, _BitInt(0x27): 0x27, _BitInt(0x28): 0x28, \
    _BitInt(0x29): 0x29, _BitInt(0x2A): 0x2A, _BitInt(0x2B): 0x2B, _BitInt(0x2C): 0x2C, \
    _BitInt(0x2D): 0x2D, _BitInt(0x2E): 0x2E, _BitInt(0x2F): 0x2F, _BitInt(0x30): 0x30, \
    \
    _BitInt(0x31): 0x31, _BitInt(0x32): 0x32, _BitInt(0x33): 0x33, _BitInt(0x34): 0x34, \
    _BitInt(0x35): 0x35, _BitInt(0x36): 0x36, _BitInt(0x37): 0x37, _BitInt(0x38): 0x38, \
    _BitInt(0x39): 0x39, _BitInt(0x3A): 0x3A, _BitInt(0x3B): 0x3B, _BitInt(0x3C): 0x3C, \
    _BitInt(0x3D): 0x3D, _BitInt(0x3E): 0x3E, _BitInt(0x3F): 0x3F, _BitInt(0x40): 0x40, \
    \
    _BitInt(0x41): 0x41, _BitInt(0x42): 0x42, _BitInt(0x43): 0x43, _BitInt(0x44): 0x44, \
    _BitInt(0x45): 0x45, _BitInt(0x46): 0x46, _BitInt(0x47): 0x47, _BitInt(0x48): 0x48, \
    _BitInt(0x49): 0x49, _BitInt(0x4A): 0x4A, _BitInt(0x4B): 0x4B, _BitInt(0x4C): 0x4C, \
    _BitInt(0x4D): 0x4D, _BitInt(0x4E): 0x4E, _BitInt(0x4F): 0x4F, _BitInt(0x50): 0x50, \
    \
    _BitInt(0x51): 0x51, _BitInt(0x52): 0x52, _BitInt(0x53): 0x53, _BitInt(0x54): 0x54, \
    _BitInt(0x55): 0x55, _BitInt(0x56): 0x56, _BitInt(0x57): 0x57, _BitInt(0x58): 0x58, \
    _BitInt(0x59): 0x59, _BitInt(0x5A): 0x5A, _BitInt(0x5B): 0x5B, _BitInt(0x5C): 0x5C, \
    _BitInt(0x5D): 0x5D, _BitInt(0x5E): 0x5E, _BitInt(0x5F): 0x5F, _BitInt(0x60): 0x60, \
    \
    _BitInt(0x61): 0x61, _BitInt(0x62): 0x62, _BitInt(0x63): 0x63, _BitInt(0x64): 0x64, \
    _BitInt(0x65): 0x65, _BitInt(0x66): 0x66, _BitInt(0x67): 0x67, _BitInt(0x68): 0x68, \
    _BitInt(0x69): 0x69, _BitInt(0x6A): 0x6A, _BitInt(0x6B): 0x6B, _BitInt(0x6C): 0x6C, \
    _BitInt(0x6D): 0x6D, _BitInt(0x6E): 0x6E, _BitInt(0x6F): 0x6F, _BitInt(0x70): 0x70, \
    \
    _BitInt(0x71): 0x71, _BitInt(0x72): 0x72, _BitInt(0x73): 0x73, _BitInt(0x74): 0x74, \
    _BitInt(0x75): 0x75, _BitInt(0x76): 0x76, _BitInt(0x77): 0x77, _BitInt(0x78): 0x78, \
    _BitInt(0x79): 0x79, _BitInt(0x7A): 0x7A, _BitInt(0x7B): 0x7B, _BitInt(0x7C): 0x7C, \
    _BitInt(0x7D): 0x7D, _BitInt(0x7E): 0x7E, _BitInt(0x7F): 0x7F, _BitInt(0x80): 0x80, \
    \
    _BitInt(0x81): 0x81, _BitInt(0x82): 0x82, _BitInt(0x83): 0x83, _BitInt(0x84): 0x84, \
    _BitInt(0x85): 0x85, _BitInt(0x86): 0x86, _BitInt(0x87): 0x87, _BitInt(0x88): 0x88, \
    _BitInt(0x89): 0x89, _BitInt(0x8A): 0x8A, _BitInt(0x8B): 0x8B, _BitInt(0x8C): 0x8C, \
    _BitInt(0x8D): 0x8D, _BitInt(0x8E): 0x8E, _BitInt(0x8F): 0x8F, _BitInt(0x90): 0x90, \
    \
    _BitInt(0x91): 0x91, _BitInt(0x92): 0x92, _BitInt(0x93): 0x93, _BitInt(0x94): 0x94, \
    _BitInt(0x95): 0x95, _BitInt(0x96): 0x96, _BitInt(0x97): 0x97, _BitInt(0x98): 0x98, \
    _BitInt(0x99): 0x99, _BitInt(0x9A): 0x9A, _BitInt(0x9B): 0x9B, _BitInt(0x9C): 0x9C, \
    _BitInt(0x9D): 0x9D, _BitInt(0x9E): 0x9E, _BitInt(0x9F): 0x9F, _BitInt(0xA0): 0xA0, \
    \
    _BitInt(0xA1): 0xA1, _BitInt(0xA2): 0xA2, _BitInt(0xA3): 0xA3, _BitInt(0xA4): 0xA4, \
    _BitInt(0xA5): 0xA5, _BitInt(0xA6): 0xA6, _BitInt(0xA7): 0xA7, _BitInt(0xA8): 0xA8, \
    _BitInt(0xA9): 0xA9, _BitInt(0xAA): 0xAA, _BitInt(0xAB): 0xAB, _BitInt(0xAC): 0xAC, \
    _BitInt(0xAD): 0xAD, _BitInt(0xAE): 0xAE, _BitInt(0xAF): 0xAF, _BitInt(0xB0): 0xB0, \
    \
    _BitInt(0xB1): 0xB1, _BitInt(0xB2): 0xB2, _BitInt(0xB3): 0xB3, _BitInt(0xB4): 0xB4, \
    _BitInt(0xB5): 0xB5, _BitInt(0xB6): 0xB6, _BitInt(0xB7): 0xB7, _BitInt(0xB8): 0xB8, \
    _BitInt(0xB9): 0xB9, _BitInt(0xBA): 0xBA, _BitInt(0xBB): 0xBB, _BitInt(0xBC): 0xBC, \
    _BitInt(0xBD): 0xBD, _BitInt(0xBE): 0xBE, _BitInt(0xBF): 0xBF, _BitInt(0xC0): 0xC0, \
    \
    _BitInt(0xC1): 0xC1, _BitInt(0xC2): 0xC2, _BitInt(0xC3): 0xC3, _BitInt(0xC4): 0xC4, \
    _BitInt(0xC5): 0xC5, _BitInt(0xC6): 0xC6, _BitInt(0xC7): 0xC7, _BitInt(0xC8): 0xC8, \
    _BitInt(0xC9): 0xC9, _BitInt(0xCA): 0xCA, _BitInt(0xCB): 0xCB, _BitInt(0xCC): 0xCC, \
    _BitInt(0xCD): 0xCD, _BitInt(0xCE): 0xCE, _BitInt(0xCF): 0xCF, _BitInt(0xD0): 0xD0, \
    \
    _BitInt(0xD1): 0xD1, _BitInt(0xD2): 0xD2, _BitInt(0xD3): 0xD3, _BitInt(0xD4): 0xD4, \
    _BitInt(0xD5): 0xD5, _BitInt(0xD6): 0xD6, _BitInt(0xD7): 0xD7, _BitInt(0xD8): 0xD8, \
    _BitInt(0xD9): 0xD9, _BitInt(0xDA): 0xDA, _BitInt(0xDB): 0xDB, _BitInt(0xDC): 0xDC, \
    _BitInt(0xDD): 0xDD, _BitInt(0xDE): 0xDE, _BitInt(0xDF): 0xDF, _BitInt(0xE0): 0xE0, \
    \
    _BitInt(0xE1): 0xE1, _BitInt(0xE2): 0xE2, _BitInt(0xE3): 0xE3, _BitInt(0xE4): 0xE4, \
    _BitInt(0xE5): 0xE5, _BitInt(0xE6): 0xE6, _BitInt(0xE7): 0xE7, _BitInt(0xE8): 0xE8, \
    _BitInt(0xE9): 0xE9, _BitInt(0xEA): 0xEA, _BitInt(0xEB): 0xEB, _BitInt(0xEC): 0xEC, \
    _BitInt(0xED): 0xED, _BitInt(0xEE): 0xEE, _BitInt(0xEF): 0xEF, _BitInt(0xF0): 0xF0, \
    \
    _BitInt(0xF1): 0xF1, _BitInt(0xF2): 0xF2, _BitInt(0xF3): 0xF3, _BitInt(0xF4): 0xF4, \
    _BitInt(0xF5): 0xF5, _BitInt(0xF6): 0xF6, _BitInt(0xF7): 0xF7, _BitInt(0xF8): 0xF8, \
    _BitInt(0xF9): 0xF9, _BitInt(0xFA): 0xFA, _BitInt(0xFB): 0xFB, _BitInt(0xFC): 0xFC, \
    _BitInt(0xFD): 0xFD, _BitInt(0xFE): 0xFE, _BitInt(0xFF): 0xFF, _BitInt(0x100): 0x100, \
    \
    \
    _BitInt(0x101): 0x101, _BitInt(0x102): 0x102, _BitInt(0x103): 0x103, _BitInt(0x104): 0x104, \
    _BitInt(0x105): 0x105, _BitInt(0x106): 0x106, _BitInt(0x107): 0x107, _BitInt(0x108): 0x108, \
    _BitInt(0x109): 0x109, _BitInt(0x10A): 0x10A, _BitInt(0x10B): 0x10B, _BitInt(0x10C): 0x10C, \
    _BitInt(0x10D): 0x10D, _BitInt(0x10E): 0x10E, _BitInt(0x10F): 0x10F, _BitInt(0x110): 0x110, \
    \
    _BitInt(0x111): 0x111, _BitInt(0x112): 0x112, _BitInt(0x113): 0x113, _BitInt(0x114): 0x114, \
    _BitInt(0x115): 0x115, _BitInt(0x116): 0x116, _BitInt(0x117): 0x117, _BitInt(0x118): 0x118, \
    _BitInt(0x119): 0x119, _BitInt(0x11A): 0x11A, _BitInt(0x11B): 0x11B, _BitInt(0x11C): 0x11C, \
    _BitInt(0x11D): 0x11D, _BitInt(0x11E): 0x11E, _BitInt(0x11F): 0x11F, _BitInt(0x120): 0x120, \
    \
    _BitInt(0x121): 0x121, _BitInt(0x122): 0x122, _BitInt(0x123): 0x123, _BitInt(0x124): 0x124, \
    _BitInt(0x125): 0x125, _BitInt(0x126): 0x126, _BitInt(0x127): 0x127, _BitInt(0x128): 0x128, \
    _BitInt(0x129): 0x129, _BitInt(0x12A): 0x12A, _BitInt(0x12B): 0x12B, _BitInt(0x12C): 0x12C, \
    _BitInt(0x12D): 0x12D, _BitInt(0x12E): 0x12E, _BitInt(0x12F): 0x12F, _BitInt(0x130): 0x130, \
    \
    _BitInt(0x131): 0x131, _BitInt(0x132): 0x132, _BitInt(0x133): 0x133, _BitInt(0x134): 0x134, \
    _BitInt(0x135): 0x135, _BitInt(0x136): 0x136, _BitInt(0x137): 0x137, _BitInt(0x138): 0x138, \
    _BitInt(0x139): 0x139, _BitInt(0x13A): 0x13A, _BitInt(0x13B): 0x13B, _BitInt(0x13C): 0x13C, \
    _BitInt(0x13D): 0x13D, _BitInt(0x13E): 0x13E, _BitInt(0x13F): 0x13F, _BitInt(0x140): 0x140, \
    \
    _BitInt(0x141): 0x141, _BitInt(0x142): 0x142, _BitInt(0x143): 0x143, _BitInt(0x144): 0x144, \
    _BitInt(0x145): 0x145, _BitInt(0x146): 0x146, _BitInt(0x147): 0x147, _BitInt(0x148): 0x148, \
    _BitInt(0x149): 0x149, _BitInt(0x14A): 0x14A, _BitInt(0x14B): 0x14B, _BitInt(0x14C): 0x14C, \
    _BitInt(0x14D): 0x14D, _BitInt(0x14E): 0x14E, _BitInt(0x14F): 0x14F, _BitInt(0x150): 0x150, \
    \
    _BitInt(0x151): 0x151, _BitInt(0x152): 0x152, _BitInt(0x153): 0x153, _BitInt(0x154): 0x154, \
    _BitInt(0x155): 0x155, _BitInt(0x156): 0x156, _BitInt(0x157): 0x157, _BitInt(0x158): 0x158, \
    _BitInt(0x159): 0x159, _BitInt(0x15A): 0x15A, _BitInt(0x15B): 0x15B, _BitInt(0x15C): 0x15C, \
    _BitInt(0x15D): 0x15D, _BitInt(0x15E): 0x15E, _BitInt(0x15F): 0x15F, _BitInt(0x160): 0x160, \
    \
    _BitInt(0x161): 0x161, _BitInt(0x162): 0x162, _BitInt(0x163): 0x163, _BitInt(0x164): 0x164, \
    _BitInt(0x165): 0x165, _BitInt(0x166): 0x166, _BitInt(0x167): 0x167, _BitInt(0x168): 0x168, \
    _BitInt(0x169): 0x169, _BitInt(0x16A): 0x16A, _BitInt(0x16B): 0x16B, _BitInt(0x16C): 0x16C, \
    _BitInt(0x16D): 0x16D, _BitInt(0x16E): 0x16E, _BitInt(0x16F): 0x16F, _BitInt(0x170): 0x170, \
    \
    _BitInt(0x171): 0x171, _BitInt(0x172): 0x172, _BitInt(0x173): 0x173, _BitInt(0x174): 0x174, \
    _BitInt(0x175): 0x175, _BitInt(0x176): 0x176, _BitInt(0x177): 0x177, _BitInt(0x178): 0x178, \
    _BitInt(0x179): 0x179, _BitInt(0x17A): 0x17A, _BitInt(0x17B): 0x17B, _BitInt(0x17C): 0x17C, \
    _BitInt(0x17D): 0x17D, _BitInt(0x17E): 0x17E, _BitInt(0x17F): 0x17F, _BitInt(0x180): 0x180, \
    \
    _BitInt(0x181): 0x181, _BitInt(0x182): 0x182, _BitInt(0x183): 0x183, _BitInt(0x184): 0x184, \
    _BitInt(0x185): 0x185, _BitInt(0x186): 0x186, _BitInt(0x187): 0x187, _BitInt(0x188): 0x188, \
    _BitInt(0x189): 0x189, _BitInt(0x18A): 0x18A, _BitInt(0x18B): 0x18B, _BitInt(0x18C): 0x18C, \
    _BitInt(0x18D): 0x18D, _BitInt(0x18E): 0x18E, _BitInt(0x18F): 0x18F, _BitInt(0x190): 0x190, \
    \
    _BitInt(0x191): 0x191, _BitInt(0x192): 0x192, _BitInt(0x193): 0x193, _BitInt(0x194): 0x194, \
    _BitInt(0x195): 0x195, _BitInt(0x196): 0x196, _BitInt(0x197): 0x197, _BitInt(0x198): 0x198, \
    _BitInt(0x199): 0x199, _BitInt(0x19A): 0x19A, _BitInt(0x19B): 0x19B, _BitInt(0x19C): 0x19C, \
    _BitInt(0x19D): 0x19D, _BitInt(0x19E): 0x19E, _BitInt(0x19F): 0x19F, _BitInt(0x1A0): 0x1A0, \
    \
    _BitInt(0x1A1): 0x1A1, _BitInt(0x1A2): 0x1A2, _BitInt(0x1A3): 0x1A3, _BitInt(0x1A4): 0x1A4, \
    _BitInt(0x1A5): 0x1A5, _BitInt(0x1A6): 0x1A6, _BitInt(0x1A7): 0x1A7, _BitInt(0x1A8): 0x1A8, \
    _BitInt(0x1A9): 0x1A9, _BitInt(0x1AA): 0x1AA, _BitInt(0x1AB): 0x1AB, _BitInt(0x1AC): 0x1AC, \
    _BitInt(0x1AD): 0x1AD, _BitInt(0x1AE): 0x1AE, _BitInt(0x1AF): 0x1AF, _BitInt(0x1B0): 0x1B0, \
    \
    _BitInt(0x1B1): 0x1B1, _BitInt(0x1B2): 0x1B2, _BitInt(0x1B3): 0x1B3, _BitInt(0x1B4): 0x1B4, \
    _BitInt(0x1B5): 0x1B5, _BitInt(0x1B6): 0x1B6, _BitInt(0x1B7): 0x1B7, _BitInt(0x1B8): 0x1B8, \
    _BitInt(0x1B9): 0x1B9, _BitInt(0x1BA): 0x1BA, _BitInt(0x1BB): 0x1BB, _BitInt(0x1BC): 0x1BC, \
    _BitInt(0x1BD): 0x1BD, _BitInt(0x1BE): 0x1BE, _BitInt(0x1BF): 0x1BF, _BitInt(0x1C0): 0x1C0, \
    \
    _BitInt(0x1C1): 0x1C1, _BitInt(0x1C2): 0x1C2, _BitInt(0x1C3): 0x1C3, _BitInt(0x1C4): 0x1C4, \
    _BitInt(0x1C5): 0x1C5, _BitInt(0x1C6): 0x1C6, _BitInt(0x1C7): 0x1C7, _BitInt(0x1C8): 0x1C8, \
    _BitInt(0x1C9): 0x1C9, _BitInt(0x1CA): 0x1CA, _BitInt(0x1CB): 0x1CB, _BitInt(0x1CC): 0x1CC, \
    _BitInt(0x1CD): 0x1CD, _BitInt(0x1CE): 0x1CE, _BitInt(0x1CF): 0x1CF, _BitInt(0x1D0): 0x1D0, \
    \
    _BitInt(0x1D1): 0x1D1, _BitInt(0x1D2): 0x1D2, _BitInt(0x1D3): 0x1D3, _BitInt(0x1D4): 0x1D4, \
    _BitInt(0x1D5): 0x1D5, _BitInt(0x1D6): 0x1D6, _BitInt(0x1D7): 0x1D7, _BitInt(0x1D8): 0x1D8, \
    _BitInt(0x1D9): 0x1D9, _BitInt(0x1DA): 0x1DA, _BitInt(0x1DB): 0x1DB, _BitInt(0x1DC): 0x1DC, \
    _BitInt(0x1DD): 0x1DD, _BitInt(0x1DE): 0x1DE, _BitInt(0x1DF): 0x1DF, _BitInt(0x1E0): 0x1E0, \
    \
    _BitInt(0x1E1): 0x1E1, _BitInt(0x1E2): 0x1E2, _BitInt(0x1E3): 0x1E3, _BitInt(0x1E4): 0x1E4, \
    _BitInt(0x1E5): 0x1E5, _BitInt(0x1E6): 0x1E6, _BitInt(0x1E7): 0x1E7, _BitInt(0x1E8): 0x1E8, \
    _BitInt(0x1E9): 0x1E9, _BitInt(0x1EA): 0x1EA, _BitInt(0x1EB): 0x1EB, _BitInt(0x1EC): 0x1EC, \
    _BitInt(0x1ED): 0x1ED, _BitInt(0x1EE): 0x1EE, _BitInt(0x1EF): 0x1EF, _BitInt(0x1F0): 0x1F0, \
    \
    _BitInt(0x1F1): 0x1F1, _BitInt(0x1F2): 0x1F2, _BitInt(0x1F3): 0x1F3, _BitInt(0x1F4): 0x1F4, \
    _BitInt(0x1F5): 0x1F5, _BitInt(0x1F6): 0x1F6, _BitInt(0x1F7): 0x1F7, _BitInt(0x1F8): 0x1F8, \
    _BitInt(0x1F9): 0x1F9, _BitInt(0x1FA): 0x1FA, _BitInt(0x1FB): 0x1FB, _BitInt(0x1FC): 0x1FC, \
    _BitInt(0x1FD): 0x1FD, _BitInt(0x1FE): 0x1FE, _BitInt(0x1FF): 0x1FF, _BitInt(0x200): 0x200, \
    \
    \
    unsigned _BitInt(0x01): 0x01, unsigned _BitInt(0x02): 0x02, unsigned _BitInt(0x03): 0x03, unsigned _BitInt(0x04): 0x04, \
    unsigned _BitInt(0x05): 0x05, unsigned _BitInt(0x06): 0x06, unsigned _BitInt(0x07): 0x07, unsigned _BitInt(0x08): 0x08, \
    unsigned _BitInt(0x09): 0x09, unsigned _BitInt(0x0A): 0x0A, unsigned _BitInt(0x0B): 0x0B, unsigned _BitInt(0x0C): 0x0C, \
    unsigned _BitInt(0x0D): 0x0D, unsigned _BitInt(0x0E): 0x0E, unsigned _BitInt(0x0F): 0x0F, unsigned _BitInt(0x10): 0x10, \
    \
    unsigned _BitInt(0x11): 0x11, unsigned _BitInt(0x12): 0x12, unsigned _BitInt(0x13): 0x13, unsigned _BitInt(0x14): 0x14, \
    unsigned _BitInt(0x15): 0x15, unsigned _BitInt(0x16): 0x16, unsigned _BitInt(0x17): 0x17, unsigned _BitInt(0x18): 0x18, \
    unsigned _BitInt(0x19): 0x19, unsigned _BitInt(0x1A): 0x1A, unsigned _BitInt(0x1B): 0x1B, unsigned _BitInt(0x1C): 0x1C, \
    unsigned _BitInt(0x1D): 0x1D, unsigned _BitInt(0x1E): 0x1E, unsigned _BitInt(0x1F): 0x1F, unsigned _BitInt(0x20): 0x20, \
    \
    unsigned _BitInt(0x21): 0x21, unsigned _BitInt(0x22): 0x22, unsigned _BitInt(0x23): 0x23, unsigned _BitInt(0x24): 0x24, \
    unsigned _BitInt(0x25): 0x25, unsigned _BitInt(0x26): 0x26, unsigned _BitInt(0x27): 0x27, unsigned _BitInt(0x28): 0x28, \
    unsigned _BitInt(0x29): 0x29, unsigned _BitInt(0x2A): 0x2A, unsigned _BitInt(0x2B): 0x2B, unsigned _BitInt(0x2C): 0x2C, \
    unsigned _BitInt(0x2D): 0x2D, unsigned _BitInt(0x2E): 0x2E, unsigned _BitInt(0x2F): 0x2F, unsigned _BitInt(0x30): 0x30, \
    \
    unsigned _BitInt(0x31): 0x31, unsigned _BitInt(0x32): 0x32, unsigned _BitInt(0x33): 0x33, unsigned _BitInt(0x34): 0x34, \
    unsigned _BitInt(0x35): 0x35, unsigned _BitInt(0x36): 0x36, unsigned _BitInt(0x37): 0x37, unsigned _BitInt(0x38): 0x38, \
    unsigned _BitInt(0x39): 0x39, unsigned _BitInt(0x3A): 0x3A, unsigned _BitInt(0x3B): 0x3B, unsigned _BitInt(0x3C): 0x3C, \
    unsigned _BitInt(0x3D): 0x3D, unsigned _BitInt(0x3E): 0x3E, unsigned _BitInt(0x3F): 0x3F, unsigned _BitInt(0x40): 0x40, \
    \
    unsigned _BitInt(0x41): 0x41, unsigned _BitInt(0x42): 0x42, unsigned _BitInt(0x43): 0x43, unsigned _BitInt(0x44): 0x44, \
    unsigned _BitInt(0x45): 0x45, unsigned _BitInt(0x46): 0x46, unsigned _BitInt(0x47): 0x47, unsigned _BitInt(0x48): 0x48, \
    unsigned _BitInt(0x49): 0x49, unsigned _BitInt(0x4A): 0x4A, unsigned _BitInt(0x4B): 0x4B, unsigned _BitInt(0x4C): 0x4C, \
    unsigned _BitInt(0x4D): 0x4D, unsigned _BitInt(0x4E): 0x4E, unsigned _BitInt(0x4F): 0x4F, unsigned _BitInt(0x50): 0x50, \
    \
    unsigned _BitInt(0x51): 0x51, unsigned _BitInt(0x52): 0x52, unsigned _BitInt(0x53): 0x53, unsigned _BitInt(0x54): 0x54, \
    unsigned _BitInt(0x55): 0x55, unsigned _BitInt(0x56): 0x56, unsigned _BitInt(0x57): 0x57, unsigned _BitInt(0x58): 0x58, \
    unsigned _BitInt(0x59): 0x59, unsigned _BitInt(0x5A): 0x5A, unsigned _BitInt(0x5B): 0x5B, unsigned _BitInt(0x5C): 0x5C, \
    unsigned _BitInt(0x5D): 0x5D, unsigned _BitInt(0x5E): 0x5E, unsigned _BitInt(0x5F): 0x5F, unsigned _BitInt(0x60): 0x60, \
    \
    unsigned _BitInt(0x61): 0x61, unsigned _BitInt(0x62): 0x62, unsigned _BitInt(0x63): 0x63, unsigned _BitInt(0x64): 0x64, \
    unsigned _BitInt(0x65): 0x65, unsigned _BitInt(0x66): 0x66, unsigned _BitInt(0x67): 0x67, unsigned _BitInt(0x68): 0x68, \
    unsigned _BitInt(0x69): 0x69, unsigned _BitInt(0x6A): 0x6A, unsigned _BitInt(0x6B): 0x6B, unsigned _BitInt(0x6C): 0x6C, \
    unsigned _BitInt(0x6D): 0x6D, unsigned _BitInt(0x6E): 0x6E, unsigned _BitInt(0x6F): 0x6F, unsigned _BitInt(0x70): 0x70, \
    \
    unsigned _BitInt(0x71): 0x71, unsigned _BitInt(0x72): 0x72, unsigned _BitInt(0x73): 0x73, unsigned _BitInt(0x74): 0x74, \
    unsigned _BitInt(0x75): 0x75, unsigned _BitInt(0x76): 0x76, unsigned _BitInt(0x77): 0x77, unsigned _BitInt(0x78): 0x78, \
    unsigned _BitInt(0x79): 0x79, unsigned _BitInt(0x7A): 0x7A, unsigned _BitInt(0x7B): 0x7B, unsigned _BitInt(0x7C): 0x7C, \
    unsigned _BitInt(0x7D): 0x7D, unsigned _BitInt(0x7E): 0x7E, unsigned _BitInt(0x7F): 0x7F, unsigned _BitInt(0x80): 0x80, \
    \
    unsigned _BitInt(0x81): 0x81, unsigned _BitInt(0x82): 0x82, unsigned _BitInt(0x83): 0x83, unsigned _BitInt(0x84): 0x84, \
    unsigned _BitInt(0x85): 0x85, unsigned _BitInt(0x86): 0x86, unsigned _BitInt(0x87): 0x87, unsigned _BitInt(0x88): 0x88, \
    unsigned _BitInt(0x89): 0x89, unsigned _BitInt(0x8A): 0x8A, unsigned _BitInt(0x8B): 0x8B, unsigned _BitInt(0x8C): 0x8C, \
    unsigned _BitInt(0x8D): 0x8D, unsigned _BitInt(0x8E): 0x8E, unsigned _BitInt(0x8F): 0x8F, unsigned _BitInt(0x90): 0x90, \
    \
    unsigned _BitInt(0x91): 0x91, unsigned _BitInt(0x92): 0x92, unsigned _BitInt(0x93): 0x93, unsigned _BitInt(0x94): 0x94, \
    unsigned _BitInt(0x95): 0x95, unsigned _BitInt(0x96): 0x96, unsigned _BitInt(0x97): 0x97, unsigned _BitInt(0x98): 0x98, \
    unsigned _BitInt(0x99): 0x99, unsigned _BitInt(0x9A): 0x9A, unsigned _BitInt(0x9B): 0x9B, unsigned _BitInt(0x9C): 0x9C, \
    unsigned _BitInt(0x9D): 0x9D, unsigned _BitInt(0x9E): 0x9E, unsigned _BitInt(0x9F): 0x9F, unsigned _BitInt(0xA0): 0xA0, \
    \
    unsigned _BitInt(0xA1): 0xA1, unsigned _BitInt(0xA2): 0xA2, unsigned _BitInt(0xA3): 0xA3, unsigned _BitInt(0xA4): 0xA4, \
    unsigned _BitInt(0xA5): 0xA5, unsigned _BitInt(0xA6): 0xA6, unsigned _BitInt(0xA7): 0xA7, unsigned _BitInt(0xA8): 0xA8, \
    unsigned _BitInt(0xA9): 0xA9, unsigned _BitInt(0xAA): 0xAA, unsigned _BitInt(0xAB): 0xAB, unsigned _BitInt(0xAC): 0xAC, \
    unsigned _BitInt(0xAD): 0xAD, unsigned _BitInt(0xAE): 0xAE, unsigned _BitInt(0xAF): 0xAF, unsigned _BitInt(0xB0): 0xB0, \
    \
    unsigned _BitInt(0xB1): 0xB1, unsigned _BitInt(0xB2): 0xB2, unsigned _BitInt(0xB3): 0xB3, unsigned _BitInt(0xB4): 0xB4, \
    unsigned _BitInt(0xB5): 0xB5, unsigned _BitInt(0xB6): 0xB6, unsigned _BitInt(0xB7): 0xB7, unsigned _BitInt(0xB8): 0xB8, \
    unsigned _BitInt(0xB9): 0xB9, unsigned _BitInt(0xBA): 0xBA, unsigned _BitInt(0xBB): 0xBB, unsigned _BitInt(0xBC): 0xBC, \
    unsigned _BitInt(0xBD): 0xBD, unsigned _BitInt(0xBE): 0xBE, unsigned _BitInt(0xBF): 0xBF, unsigned _BitInt(0xC0): 0xC0, \
    \
    unsigned _BitInt(0xC1): 0xC1, unsigned _BitInt(0xC2): 0xC2, unsigned _BitInt(0xC3): 0xC3, unsigned _BitInt(0xC4): 0xC4, \
    unsigned _BitInt(0xC5): 0xC5, unsigned _BitInt(0xC6): 0xC6, unsigned _BitInt(0xC7): 0xC7, unsigned _BitInt(0xC8): 0xC8, \
    unsigned _BitInt(0xC9): 0xC9, unsigned _BitInt(0xCA): 0xCA, unsigned _BitInt(0xCB): 0xCB, unsigned _BitInt(0xCC): 0xCC, \
    unsigned _BitInt(0xCD): 0xCD, unsigned _BitInt(0xCE): 0xCE, unsigned _BitInt(0xCF): 0xCF, unsigned _BitInt(0xD0): 0xD0, \
    \
    unsigned _BitInt(0xD1): 0xD1, unsigned _BitInt(0xD2): 0xD2, unsigned _BitInt(0xD3): 0xD3, unsigned _BitInt(0xD4): 0xD4, \
    unsigned _BitInt(0xD5): 0xD5, unsigned _BitInt(0xD6): 0xD6, unsigned _BitInt(0xD7): 0xD7, unsigned _BitInt(0xD8): 0xD8, \
    unsigned _BitInt(0xD9): 0xD9, unsigned _BitInt(0xDA): 0xDA, unsigned _BitInt(0xDB): 0xDB, unsigned _BitInt(0xDC): 0xDC, \
    unsigned _BitInt(0xDD): 0xDD, unsigned _BitInt(0xDE): 0xDE, unsigned _BitInt(0xDF): 0xDF, unsigned _BitInt(0xE0): 0xE0, \
    \
    unsigned _BitInt(0xE1): 0xE1, unsigned _BitInt(0xE2): 0xE2, unsigned _BitInt(0xE3): 0xE3, unsigned _BitInt(0xE4): 0xE4, \
    unsigned _BitInt(0xE5): 0xE5, unsigned _BitInt(0xE6): 0xE6, unsigned _BitInt(0xE7): 0xE7, unsigned _BitInt(0xE8): 0xE8, \
    unsigned _BitInt(0xE9): 0xE9, unsigned _BitInt(0xEA): 0xEA, unsigned _BitInt(0xEB): 0xEB, unsigned _BitInt(0xEC): 0xEC, \
    unsigned _BitInt(0xED): 0xED, unsigned _BitInt(0xEE): 0xEE, unsigned _BitInt(0xEF): 0xEF, unsigned _BitInt(0xF0): 0xF0, \
    \
    unsigned _BitInt(0xF1): 0xF1, unsigned _BitInt(0xF2): 0xF2, unsigned _BitInt(0xF3): 0xF3, unsigned _BitInt(0xF4): 0xF4, \
    unsigned _BitInt(0xF5): 0xF5, unsigned _BitInt(0xF6): 0xF6, unsigned _BitInt(0xF7): 0xF7, unsigned _BitInt(0xF8): 0xF8, \
    unsigned _BitInt(0xF9): 0xF9, unsigned _BitInt(0xFA): 0xFA, unsigned _BitInt(0xFB): 0xFB, unsigned _BitInt(0xFC): 0xFC, \
    unsigned _BitInt(0xFD): 0xFD, unsigned _BitInt(0xFE): 0xFE, unsigned _BitInt(0xFF): 0xFF, unsigned _BitInt(0x100): 0x100, \
    \
    \
    unsigned _BitInt(0x101): 0x101, unsigned _BitInt(0x102): 0x102, unsigned _BitInt(0x103): 0x103, unsigned _BitInt(0x104): 0x104, \
    unsigned _BitInt(0x105): 0x105, unsigned _BitInt(0x106): 0x106, unsigned _BitInt(0x107): 0x107, unsigned _BitInt(0x108): 0x108, \
    unsigned _BitInt(0x109): 0x109, unsigned _BitInt(0x10A): 0x10A, unsigned _BitInt(0x10B): 0x10B, unsigned _BitInt(0x10C): 0x10C, \
    unsigned _BitInt(0x10D): 0x10D, unsigned _BitInt(0x10E): 0x10E, unsigned _BitInt(0x10F): 0x10F, unsigned _BitInt(0x110): 0x110, \
    \
    unsigned _BitInt(0x111): 0x111, unsigned _BitInt(0x112): 0x112, unsigned _BitInt(0x113): 0x113, unsigned _BitInt(0x114): 0x114, \
    unsigned _BitInt(0x115): 0x115, unsigned _BitInt(0x116): 0x116, unsigned _BitInt(0x117): 0x117, unsigned _BitInt(0x118): 0x118, \
    unsigned _BitInt(0x119): 0x119, unsigned _BitInt(0x11A): 0x11A, unsigned _BitInt(0x11B): 0x11B, unsigned _BitInt(0x11C): 0x11C, \
    unsigned _BitInt(0x11D): 0x11D, unsigned _BitInt(0x11E): 0x11E, unsigned _BitInt(0x11F): 0x11F, unsigned _BitInt(0x120): 0x120, \
    \
    unsigned _BitInt(0x121): 0x121, unsigned _BitInt(0x122): 0x122, unsigned _BitInt(0x123): 0x123, unsigned _BitInt(0x124): 0x124, \
    unsigned _BitInt(0x125): 0x125, unsigned _BitInt(0x126): 0x126, unsigned _BitInt(0x127): 0x127, unsigned _BitInt(0x128): 0x128, \
    unsigned _BitInt(0x129): 0x129, unsigned _BitInt(0x12A): 0x12A, unsigned _BitInt(0x12B): 0x12B, unsigned _BitInt(0x12C): 0x12C, \
    unsigned _BitInt(0x12D): 0x12D, unsigned _BitInt(0x12E): 0x12E, unsigned _BitInt(0x12F): 0x12F, unsigned _BitInt(0x130): 0x130, \
    \
    unsigned _BitInt(0x131): 0x131, unsigned _BitInt(0x132): 0x132, unsigned _BitInt(0x133): 0x133, unsigned _BitInt(0x134): 0x134, \
    unsigned _BitInt(0x135): 0x135, unsigned _BitInt(0x136): 0x136, unsigned _BitInt(0x137): 0x137, unsigned _BitInt(0x138): 0x138, \
    unsigned _BitInt(0x139): 0x139, unsigned _BitInt(0x13A): 0x13A, unsigned _BitInt(0x13B): 0x13B, unsigned _BitInt(0x13C): 0x13C, \
    unsigned _BitInt(0x13D): 0x13D, unsigned _BitInt(0x13E): 0x13E, unsigned _BitInt(0x13F): 0x13F, unsigned _BitInt(0x140): 0x140, \
    \
    unsigned _BitInt(0x141): 0x141, unsigned _BitInt(0x142): 0x142, unsigned _BitInt(0x143): 0x143, unsigned _BitInt(0x144): 0x144, \
    unsigned _BitInt(0x145): 0x145, unsigned _BitInt(0x146): 0x146, unsigned _BitInt(0x147): 0x147, unsigned _BitInt(0x148): 0x148, \
    unsigned _BitInt(0x149): 0x149, unsigned _BitInt(0x14A): 0x14A, unsigned _BitInt(0x14B): 0x14B, unsigned _BitInt(0x14C): 0x14C, \
    unsigned _BitInt(0x14D): 0x14D, unsigned _BitInt(0x14E): 0x14E, unsigned _BitInt(0x14F): 0x14F, unsigned _BitInt(0x150): 0x150, \
    \
    unsigned _BitInt(0x151): 0x151, unsigned _BitInt(0x152): 0x152, unsigned _BitInt(0x153): 0x153, unsigned _BitInt(0x154): 0x154, \
    unsigned _BitInt(0x155): 0x155, unsigned _BitInt(0x156): 0x156, unsigned _BitInt(0x157): 0x157, unsigned _BitInt(0x158): 0x158, \
    unsigned _BitInt(0x159): 0x159, unsigned _BitInt(0x15A): 0x15A, unsigned _BitInt(0x15B): 0x15B, unsigned _BitInt(0x15C): 0x15C, \
    unsigned _BitInt(0x15D): 0x15D, unsigned _BitInt(0x15E): 0x15E, unsigned _BitInt(0x15F): 0x15F, unsigned _BitInt(0x160): 0x160, \
    \
    unsigned _BitInt(0x161): 0x161, unsigned _BitInt(0x162): 0x162, unsigned _BitInt(0x163): 0x163, unsigned _BitInt(0x164): 0x164, \
    unsigned _BitInt(0x165): 0x165, unsigned _BitInt(0x166): 0x166, unsigned _BitInt(0x167): 0x167, unsigned _BitInt(0x168): 0x168, \
    unsigned _BitInt(0x169): 0x169, unsigned _BitInt(0x16A): 0x16A, unsigned _BitInt(0x16B): 0x16B, unsigned _BitInt(0x16C): 0x16C, \
    unsigned _BitInt(0x16D): 0x16D, unsigned _BitInt(0x16E): 0x16E, unsigned _BitInt(0x16F): 0x16F, unsigned _BitInt(0x170): 0x170, \
    \
    unsigned _BitInt(0x171): 0x171, unsigned _BitInt(0x172): 0x172, unsigned _BitInt(0x173): 0x173, unsigned _BitInt(0x174): 0x174, \
    unsigned _BitInt(0x175): 0x175, unsigned _BitInt(0x176): 0x176, unsigned _BitInt(0x177): 0x177, unsigned _BitInt(0x178): 0x178, \
    unsigned _BitInt(0x179): 0x179, unsigned _BitInt(0x17A): 0x17A, unsigned _BitInt(0x17B): 0x17B, unsigned _BitInt(0x17C): 0x17C, \
    unsigned _BitInt(0x17D): 0x17D, unsigned _BitInt(0x17E): 0x17E, unsigned _BitInt(0x17F): 0x17F, unsigned _BitInt(0x180): 0x180, \
    \
    unsigned _BitInt(0x181): 0x181, unsigned _BitInt(0x182): 0x182, unsigned _BitInt(0x183): 0x183, unsigned _BitInt(0x184): 0x184, \
    unsigned _BitInt(0x185): 0x185, unsigned _BitInt(0x186): 0x186, unsigned _BitInt(0x187): 0x187, unsigned _BitInt(0x188): 0x188, \
    unsigned _BitInt(0x189): 0x189, unsigned _BitInt(0x18A): 0x18A, unsigned _BitInt(0x18B): 0x18B, unsigned _BitInt(0x18C): 0x18C, \
    unsigned _BitInt(0x18D): 0x18D, unsigned _BitInt(0x18E): 0x18E, unsigned _BitInt(0x18F): 0x18F, unsigned _BitInt(0x190): 0x190, \
    \
    unsigned _BitInt(0x191): 0x191, unsigned _BitInt(0x192): 0x192, unsigned _BitInt(0x193): 0x193, unsigned _BitInt(0x194): 0x194, \
    unsigned _BitInt(0x195): 0x195, unsigned _BitInt(0x196): 0x196, unsigned _BitInt(0x197): 0x197, unsigned _BitInt(0x198): 0x198, \
    unsigned _BitInt(0x199): 0x199, unsigned _BitInt(0x19A): 0x19A, unsigned _BitInt(0x19B): 0x19B, unsigned _BitInt(0x19C): 0x19C, \
    unsigned _BitInt(0x19D): 0x19D, unsigned _BitInt(0x19E): 0x19E, unsigned _BitInt(0x19F): 0x19F, unsigned _BitInt(0x1A0): 0x1A0, \
    \
    unsigned _BitInt(0x1A1): 0x1A1, unsigned _BitInt(0x1A2): 0x1A2, unsigned _BitInt(0x1A3): 0x1A3, unsigned _BitInt(0x1A4): 0x1A4, \
    unsigned _BitInt(0x1A5): 0x1A5, unsigned _BitInt(0x1A6): 0x1A6, unsigned _BitInt(0x1A7): 0x1A7, unsigned _BitInt(0x1A8): 0x1A8, \
    unsigned _BitInt(0x1A9): 0x1A9, unsigned _BitInt(0x1AA): 0x1AA, unsigned _BitInt(0x1AB): 0x1AB, unsigned _BitInt(0x1AC): 0x1AC, \
    unsigned _BitInt(0x1AD): 0x1AD, unsigned _BitInt(0x1AE): 0x1AE, unsigned _BitInt(0x1AF): 0x1AF, unsigned _BitInt(0x1B0): 0x1B0, \
    \
    unsigned _BitInt(0x1B1): 0x1B1, unsigned _BitInt(0x1B2): 0x1B2, unsigned _BitInt(0x1B3): 0x1B3, unsigned _BitInt(0x1B4): 0x1B4, \
    unsigned _BitInt(0x1B5): 0x1B5, unsigned _BitInt(0x1B6): 0x1B6, unsigned _BitInt(0x1B7): 0x1B7, unsigned _BitInt(0x1B8): 0x1B8, \
    unsigned _BitInt(0x1B9): 0x1B9, unsigned _BitInt(0x1BA): 0x1BA, unsigned _BitInt(0x1BB): 0x1BB, unsigned _BitInt(0x1BC): 0x1BC, \
    unsigned _BitInt(0x1BD): 0x1BD, unsigned _BitInt(0x1BE): 0x1BE, unsigned _BitInt(0x1BF): 0x1BF, unsigned _BitInt(0x1C0): 0x1C0, \
    \
    unsigned _BitInt(0x1C1): 0x1C1, unsigned _BitInt(0x1C2): 0x1C2, unsigned _BitInt(0x1C3): 0x1C3, unsigned _BitInt(0x1C4): 0x1C4, \
    unsigned _BitInt(0x1C5): 0x1C5, unsigned _BitInt(0x1C6): 0x1C6, unsigned _BitInt(0x1C7): 0x1C7, unsigned _BitInt(0x1C8): 0x1C8, \
    unsigned _BitInt(0x1C9): 0x1C9, unsigned _BitInt(0x1CA): 0x1CA, unsigned _BitInt(0x1CB): 0x1CB, unsigned _BitInt(0x1CC): 0x1CC, \
    unsigned _BitInt(0x1CD): 0x1CD, unsigned _BitInt(0x1CE): 0x1CE, unsigned _BitInt(0x1CF): 0x1CF, unsigned _BitInt(0x1D0): 0x1D0, \
    \
    unsigned _BitInt(0x1D1): 0x1D1, unsigned _BitInt(0x1D2): 0x1D2, unsigned _BitInt(0x1D3): 0x1D3, unsigned _BitInt(0x1D4): 0x1D4, \
    unsigned _BitInt(0x1D5): 0x1D5, unsigned _BitInt(0x1D6): 0x1D6, unsigned _BitInt(0x1D7): 0x1D7, unsigned _BitInt(0x1D8): 0x1D8, \
    unsigned _BitInt(0x1D9): 0x1D9, unsigned _BitInt(0x1DA): 0x1DA, unsigned _BitInt(0x1DB): 0x1DB, unsigned _BitInt(0x1DC): 0x1DC, \
    unsigned _BitInt(0x1DD): 0x1DD, unsigned _BitInt(0x1DE): 0x1DE, unsigned _BitInt(0x1DF): 0x1DF, unsigned _BitInt(0x1E0): 0x1E0, \
    \
    unsigned _BitInt(0x1E1): 0x1E1, unsigned _BitInt(0x1E2): 0x1E2, unsigned _BitInt(0x1E3): 0x1E3, unsigned _BitInt(0x1E4): 0x1E4, \
    unsigned _BitInt(0x1E5): 0x1E5, unsigned _BitInt(0x1E6): 0x1E6, unsigned _BitInt(0x1E7): 0x1E7, unsigned _BitInt(0x1E8): 0x1E8, \
    unsigned _BitInt(0x1E9): 0x1E9, unsigned _BitInt(0x1EA): 0x1EA, unsigned _BitInt(0x1EB): 0x1EB, unsigned _BitInt(0x1EC): 0x1EC, \
    unsigned _BitInt(0x1ED): 0x1ED, unsigned _BitInt(0x1EE): 0x1EE, unsigned _BitInt(0x1EF): 0x1EF, unsigned _BitInt(0x1F0): 0x1F0, \
    \
    unsigned _BitInt(0x1F1): 0x1F1, unsigned _BitInt(0x1F2): 0x1F2, unsigned _BitInt(0x1F3): 0x1F3, unsigned _BitInt(0x1F4): 0x1F4, \
    unsigned _BitInt(0x1F5): 0x1F5, unsigned _BitInt(0x1F6): 0x1F6, unsigned _BitInt(0x1F7): 0x1F7, unsigned _BitInt(0x1F8): 0x1F8, \
    unsigned _BitInt(0x1F9): 0x1F9, unsigned _BitInt(0x1FA): 0x1FA, unsigned _BitInt(0x1FB): 0x1FB, unsigned _BitInt(0x1FC): 0x1FC, \
    unsigned _BitInt(0x1FD): 0x1FD, unsigned _BitInt(0x1FE): 0x1FE, unsigned _BitInt(0x1FF): 0x1FF, unsigned _BitInt(0x200): 0x200 \
  )
#endif

#define dpa__u_choose_prime(T) _Generic((char(*)[dpa__u_bitwidth((T){0})]){0}, \
    char(*)[1]: (T)0x1llu, \
    char(*)[2]: (T)0x3llu, \
    char(*)[3]: (T)0x5llu, \
    char(*)[4]: (T)0xbllu, \
    char(*)[5]: (T)0x13llu, \
    char(*)[6]: (T)0x3dllu, \
    char(*)[7]: (T)0x65llu, \
    char(*)[8]: ((T)0x97llu), \
    char(*)[9]: ((T)0x1BBllu), \
    char(*)[10]: ((T)0xE9llu), \
    char(*)[11]: ((T)0x6A3llu), \
    char(*)[12]: ((T)0xAF1llu), \
    char(*)[13]: ((T)0x78Dllu), \
    char(*)[14]: ((T)0x551llu), \
    char(*)[15]: ((T)0x7F8Dllu), \
    char(*)[16]: ((T)0xD37Bllu), \
    char(*)[17]: ((T)0x12721llu), \
    char(*)[18]: ((T)0x1BA19llu), \
    char(*)[19]: ((T)0x6606Bllu), \
    char(*)[20]: ((T)0x66BCBllu), \
    char(*)[21]: ((T)0x1C97E1llu), \
    char(*)[22]: ((T)0x35D4ABllu), \
    char(*)[23]: ((T)0x379F69llu), \
    char(*)[24]: ((T)0x50026Fllu), \
    char(*)[25]: ((T)0x1C7E6Dllu), \
    char(*)[26]: ((T)0x992DF5llu), \
    char(*)[27]: ((T)0x79053ADllu), \
    char(*)[28]: ((T)0x788A217llu), \
    char(*)[29]: ((T)0x6BB6DC3llu), \
    char(*)[30]: ((T)0x393A422Bllu), \
    char(*)[31]: ((T)0xF77E3CFllu), \
    char(*)[32]: ((T)0x2B5EFFABllu), \
    char(*)[33]: ((T)0x16E503027llu), \
    char(*)[34]: ((T)0x3E0592CE3llu), \
    char(*)[35]: ((T)0x2E5818CC9llu), \
    char(*)[36]: ((T)0x95F22DF61llu), \
    char(*)[37]: ((T)0x444DF2C5llu), \
    char(*)[38]: ((T)0x17B97F18Fllu), \
    char(*)[39]: ((T)0x2C2556F8BBllu), \
    char(*)[40]: ((T)0xBF23BBA91llu), \
    char(*)[41]: ((T)0xC9B8065AD9llu), \
    char(*)[42]: ((T)0x22F68C3C4Fllu), \
    char(*)[43]: ((T)0x6726AD383C9llu), \
    char(*)[44]: ((T)0xEFE428A09CFllu), \
    char(*)[45]: ((T)0x17380C01DB2Dllu), \
    char(*)[46]: ((T)0x1CE2EC6C2835llu), \
    char(*)[47]: ((T)0x768C58BF51B9llu), \
    char(*)[48]: ((T)0x10E12850D2Dllu), \
    char(*)[49]: ((T)0x13DB3D98D2285llu), \
    char(*)[50]: ((T)0x3909FAA27FABllu), \
    char(*)[51]: ((T)0x2BEC545CED291llu), \
    char(*)[52]: ((T)0x5B61382D50B11llu), \
    char(*)[53]: ((T)0x1EDD2778138E67llu), \
    char(*)[54]: ((T)0x1052397014A6C7llu), \
    char(*)[55]: ((T)0x2E81D1E4B3E4D1llu), \
    char(*)[56]: ((T)0xD1673D359CED7Dllu), \
    char(*)[57]: ((T)0xB581F59E2F1ADFllu), \
    char(*)[58]: ((T)0x24A62F126DD5C93llu), \
    char(*)[59]: ((T)0x736A12A98F9A9A3llu), \
    char(*)[60]: ((T)0x27BC02A33F9FB1Fllu), \
    char(*)[61]: ((T)0x1A6F25920B8923B7llu), \
    char(*)[62]: ((T)0xE43947DE0C53943llu), \
    char(*)[63]: ((T)0x3F20AC3847FA1B75llu), \
    char(*)[64]: ((T)0x4169787D2543086Bllu), \
    char(*)[65]: ((T)0x32314B522EB1E8Dllu), \
    char(*)[66]: (((T)0x1llu)<<64) | ((T)0x568CA6AA1340A861llu), \
    char(*)[67]: (((T)0x6llu)<<64) | ((T)0x1FC72317C5036FE9llu), \
    char(*)[68]: (((T)0xEllu)<<64) | ((T)0x46CFDCBDFCB74ACDllu), \
    char(*)[69]: (((T)0x18llu)<<64) | ((T)0x6B6EF9636980FE21llu), \
    char(*)[70]: (((T)0x5llu)<<64) | ((T)0x591EF93879105AABllu), \
    char(*)[71]: (((T)0x27llu)<<64) | ((T)0xEC1D6BC856C4AA2Bllu), \
    char(*)[72]: (((T)0x14llu)<<64) | ((T)0x4BCDF66F5C549DD3llu), \
    char(*)[73]: (((T)0x1BFllu)<<64) | ((T)0xCD57025E347C8D01llu), \
    char(*)[74]: (((T)0x125llu)<<64) | ((T)0x7F019888950B7D0Dllu), \
    char(*)[75]: (((T)0x44Allu)<<64) | ((T)0xFD35A9735BA793BFllu), \
    char(*)[76]: (((T)0xE31llu)<<64) | ((T)0xE347A8B08F24B9CDllu), \
    char(*)[77]: (((T)0x186Bllu)<<64) | ((T)0xDEEB4F9BEAEE2029llu), \
    char(*)[78]: (((T)0x9B0llu)<<64) | ((T)0xF38786BF399E8C5Bllu), \
    char(*)[79]: (((T)0xA48llu)<<64) | ((T)0xD5C57A3B2FBB8ABDllu), \
    char(*)[80]: (((T)0x47A5llu)<<64) | ((T)0x8AC7FC0BB330E131llu), \
    char(*)[81]: (((T)0x6DA9llu)<<64) | ((T)0x67A66D0B0592784Bllu), \
    char(*)[82]: (((T)0x20883llu)<<64) | ((T)0x6A44C3E950EA9453llu), \
    char(*)[83]: (((T)0x6B502llu)<<64) | ((T)0x28D8EF0415CF0A05llu), \
    char(*)[84]: (((T)0x76CE6llu)<<64) | ((T)0x3984D3B8DAED7657llu), \
    char(*)[85]: (((T)0x5F39Fllu)<<64) | ((T)0xD70A7449AE8FDA29llu), \
    char(*)[86]: (((T)0x3D05B9llu)<<64) | ((T)0x12426FB38A283CDDllu), \
    char(*)[87]: (((T)0x1C6C28llu)<<64) | ((T)0xB4672550297E282Bllu), \
    char(*)[88]: (((T)0x8C73D2llu)<<64) | ((T)0x8B275B84F8B6A913llu), \
    char(*)[89]: (((T)0x12913FEllu)<<64) | ((T)0x60FE7244BD1B458Bllu), \
    char(*)[90]: (((T)0x2851609llu)<<64) | ((T)0x8E5EC56C0140FE29llu), \
    char(*)[91]: (((T)0x5FDFA52llu)<<64) | ((T)0x3B7372FAA168C943llu), \
    char(*)[92]: (((T)0x533D15Dllu)<<64) | ((T)0xA845E5542A703D3Dllu), \
    char(*)[93]: (((T)0xA691653llu)<<64) | ((T)0x6BD895FCCE5C3C89llu), \
    char(*)[94]: (((T)0x32507B54llu)<<64) | ((T)0x30BB812990D00063llu), \
    char(*)[95]: (((T)0x76D503D7llu)<<64) | ((T)0x8ADCE439CD840B15llu), \
    char(*)[96]: (((T)0x208ACF86llu)<<64) | ((T)0x39B2BF06F7D4D5C7llu), \
    char(*)[97]: (((T)0x1E64211E1llu)<<64) | ((T)0xE13CD171183394F9llu), \
    char(*)[98]: (((T)0xA879C6B4llu)<<64) | ((T)0xD80D10D540DD9535llu), \
    char(*)[99]: (((T)0x6A9F26AC0llu)<<64) | ((T)0x28FF7BE45BDA75Bllu), \
    char(*)[100]: (((T)0xE79F4D747llu)<<64) | ((T)0x81BD83A124297049llu), \
    char(*)[101]: (((T)0x1013CBEDBBllu)<<64) | ((T)0x2CDA326FD053401Dllu), \
    char(*)[102]: (((T)0x1F6FA73CB2llu)<<64) | ((T)0xCB3E4CFA616F6569llu), \
    char(*)[103]: (((T)0x115A4BF0FAllu)<<64) | ((T)0xA68A4419DF40E9F5llu), \
    char(*)[104]: (((T)0xF1C7CD8D1Dllu)<<64) | ((T)0xB9FA63398A6220EFllu), \
    char(*)[105]: (((T)0xB33E6B3EF4llu)<<64) | ((T)0x9ADA5F26AEF1BA6Bllu), \
    char(*)[106]: (((T)0x3C3BEE82E8Cllu)<<64) | ((T)0x3AC4F8FBA15FCE5Dllu), \
    char(*)[107]: (((T)0x275D087FDCBllu)<<64) | ((T)0xA657900DA9B1C5B7llu), \
    char(*)[108]: (((T)0x88082A3A73Cllu)<<64) | ((T)0x1DCAEF52F4E76BE3llu), \
    char(*)[109]: (((T)0x2AEC7244278llu)<<64) | ((T)0x6C23FB0C3725B861llu), \
    char(*)[110]: (((T)0x1F4FFD5EA08Dllu)<<64) | ((T)0xD7282CA9BBC41261llu), \
    char(*)[111]: (((T)0x29353EA5D7C0llu)<<64) | ((T)0x56E7ED8C2CE0CE29llu), \
    char(*)[112]: (((T)0xD30429DBE8E3llu)<<64) | ((T)0xF2F39947E7F27069llu), \
    char(*)[113]: (((T)0xED63CF067112llu)<<64) | ((T)0xFE839FF2B7CEFC8Dllu), \
    char(*)[114]: (((T)0xD7982E58BD25llu)<<64) | ((T)0x83F9B942D1A50E53llu), \
    char(*)[115]: (((T)0x77A2C9C5F3D4Fllu)<<64) | ((T)0x7DB04C84657AFC1Dllu), \
    char(*)[116]: (((T)0xAAC6AE16FF0EAllu)<<64) | ((T)0x178BEB608CF7519llu), \
    char(*)[117]: (((T)0x10C41BA53B5672llu)<<64) | ((T)0x7B5FA3B48709FA15llu), \
    char(*)[118]: (((T)0x3ABF9D8047AFEBllu)<<64) | ((T)0xB7C7496828FAD1C1llu), \
    char(*)[119]: (((T)0x96D9BB39A6FA7llu)<<64) | ((T)0xD69C55D46882C77llu), \
    char(*)[120]: (((T)0x648DD1C009104Dllu)<<64) | ((T)0x1E0F2C0585C4ED23llu), \
    char(*)[121]: (((T)0x23B09B87DCC233llu)<<64) | ((T)0x2494107445ABFB1Fllu), \
    char(*)[122]: (((T)0x1FEEAB858077967llu)<<64) | ((T)0x664D639C55131CFllu), \
    char(*)[123]: (((T)0x586FFCB6EE9449llu)<<64) | ((T)0xBA3671357F100283llu), \
    char(*)[124]: (((T)0xEB83D9CDDCFBBF4llu)<<64) | ((T)0x4F9034FC842AC309llu), \
    char(*)[125]: (((T)0x57F34942C4A9DAEllu)<<64) | ((T)0xEE415EA2B456DD77llu), \
    char(*)[126]: (((T)0x230DA007557949C4llu)<<64) | ((T)0x9396DB04F0A5510Fllu), \
    char(*)[127]: (((T)0x30D549EA10FDC09llu)<<64) | ((T)0x9DD6B0D4C6AB5A2Fllu), \
    char(*)[128]: (((T)0x883A6B8998395DD1llu)<<64) | ((T)0xDF3D18223572CADllu), \
    char(*)[129]: (((T)0xFBF1A8A25C8AA9Bllu)<<64) | ((T)0x5EB9DBC7D1145D51llu), \
    char(*)[130]: (((T)0x25CD44BDEBDE1733llu)<<64) | ((T)0xBEEDF125A6B8BAAFllu), \
    char(*)[131]: (((T)0x4llu)<<128) | (((T)0xBFA8BF0C7A0989ADllu)<<64) | ((T)0x95D171E7BDBA82CDllu), \
    char(*)[132]: (((T)0x9llu)<<128) | (((T)0xDF107C93C10860F7llu)<<64) | ((T)0xE5F55082B8D40843llu), \
    char(*)[133]: (((T)0xD90824A9059E2649llu)<<64) | ((T)0x3CAE358DB21664EDllu), \
    char(*)[134]: (((T)0x2Cllu)<<128) | (((T)0xF3FC7ABA034E0C28llu)<<64) | ((T)0x6873BA5B50DBA989llu), \
    char(*)[135]: (((T)0x1Ellu)<<128) | (((T)0x22D172E4E114FE0Dllu)<<64) | ((T)0xFD1473D1D6D3661llu), \
    char(*)[136]: (((T)0x7Ellu)<<128) | (((T)0xCE7D704D45FA9752llu)<<64) | ((T)0x19F62CE2A121AF8Dllu), \
    char(*)[137]: (((T)0x1A6llu)<<128) | (((T)0x9AC07316A567AD7Dllu)<<64) | ((T)0x1CC7678833DA7EDBllu), \
    char(*)[138]: (((T)0x166llu)<<128) | (((T)0xA6CA9ECCEFE9214Ellu)<<64) | ((T)0x3C86F7423BEF1485llu), \
    char(*)[139]: (((T)0x4E5llu)<<128) | (((T)0xA3364E2CA6C3ACA6llu)<<64) | ((T)0xF6BDAD64AC8085A1llu), \
    char(*)[140]: (((T)0xFBAllu)<<128) | (((T)0x6D295E21EC68F815llu)<<64) | ((T)0x61F11E57401FE70Fllu), \
    char(*)[141]: (((T)0xB1Ellu)<<128) | (((T)0xD3C40CEFB2F7F5B8llu)<<64) | ((T)0x30357D8859F5FFllu), \
    char(*)[142]: (((T)0x3F8Ellu)<<128) | (((T)0xF9B02578C0F67B6Fllu)<<64) | ((T)0x42F1F8E9D39D89AFllu), \
    char(*)[143]: (((T)0x4605llu)<<128) | (((T)0xDE4E301449BB61DEllu)<<64) | ((T)0xAECB8639C7A9802Dllu), \
    char(*)[144]: (((T)0x491Cllu)<<128) | (((T)0xFE8824853F878027llu)<<64) | ((T)0xE8ACB0D21773D9BBllu), \
    char(*)[145]: (((T)0x19D30llu)<<128) | (((T)0x9C6734E2DA1F0184llu)<<64) | ((T)0x9264A918ECB69AA3llu), \
    char(*)[146]: (((T)0x24385llu)<<128) | (((T)0x362C2705D5AA19CBllu)<<64) | ((T)0x45C0972D5687950Bllu), \
    char(*)[147]: (((T)0x1C1F0llu)<<128) | (((T)0xF14B3405AB48E455llu)<<64) | ((T)0x77FAC7EA19BFFC71llu), \
    char(*)[148]: (((T)0x55665llu)<<128) | (((T)0xBF5384EFD2FD99C2llu)<<64) | ((T)0x64CA3C19459EBA57llu), \
    char(*)[149]: (((T)0x633Cllu)<<128) | (((T)0x3C6222DA9CDBF600llu)<<64) | ((T)0x55DEBC10751202A1llu), \
    char(*)[150]: (((T)0x3E087Fllu)<<128) | (((T)0x78F831991FC5E2F6llu)<<64) | ((T)0xB08C8FCAE7A8C805llu), \
    char(*)[151]: (((T)0x497E8Ellu)<<128) | (((T)0xB40080EA6B53DE9Fllu)<<64) | ((T)0xF0F7E53DDE2EF17llu), \
    char(*)[152]: (((T)0x90D7ECllu)<<128) | (((T)0x736071D8EB965783llu)<<64) | ((T)0xFDFBD2ABA244FBD1llu), \
    char(*)[153]: (((T)0x15D6CCEllu)<<128) | (((T)0xEF7892D43444CBDBllu)<<64) | ((T)0x4FC0A08B4C5B5D61llu), \
    char(*)[154]: (((T)0x3759994llu)<<128) | (((T)0xAC4B6962A3BBE746llu)<<64) | ((T)0xCF6DD921DB033691llu), \
    char(*)[155]: (((T)0x54A5191llu)<<128) | (((T)0x2D77E50AF67CF799llu)<<64) | ((T)0x75D2F482D0A56C27llu), \
    char(*)[156]: (((T)0x4A668B4llu)<<128) | (((T)0xF3D1621E6E959F24llu)<<64) | ((T)0xFECA609939DDB04Fllu), \
    char(*)[157]: (((T)0x154349DEllu)<<128) | (((T)0x353ADAE6135FDCA5llu)<<64) | ((T)0x4DC8F68ADECED653llu), \
    char(*)[158]: (((T)0xA0EDA59llu)<<128) | (((T)0xC1E1D556F0FD6740llu)<<64) | ((T)0x98686050E5592A6Fllu), \
    char(*)[159]: (((T)0x3AD801A7llu)<<128) | (((T)0xB85B3BDB36CB9883llu)<<64) | ((T)0x7C825D6E05F7E9EDllu), \
    char(*)[160]: (((T)0xEE57B1A9llu)<<128) | (((T)0xEB00CB74CCE890ABllu)<<64) | ((T)0x8DC88751CD3ADF87llu), \
    char(*)[161]: (((T)0x1621BE4BEllu)<<128) | (((T)0x506FF931CAEEC22Allu)<<64) | ((T)0xC5449403E7C1FA6Bllu), \
    char(*)[162]: (((T)0x2B2B9A895llu)<<128) | (((T)0x9D07093E59717092llu)<<64) | ((T)0xF0E9313FB9275AC9llu), \
    char(*)[163]: (((T)0x219A25F10llu)<<128) | (((T)0x1F3DEF547A48A01Cllu)<<64) | ((T)0xF859CFAF445D4F15llu), \
    char(*)[164]: (((T)0xEA7A87C32llu)<<128) | (((T)0x40AD73856B5844CCllu)<<64) | ((T)0x56201241346C0661llu), \
    char(*)[165]: (((T)0x7A5975046llu)<<128) | (((T)0xEAA205EBD5226FCBllu)<<64) | ((T)0xB24F988C8770CA5Bllu), \
    char(*)[166]: (((T)0xC905591A4llu)<<128) | (((T)0xB8AFCC058F0141DAllu)<<64) | ((T)0x392B321A98370F69llu), \
    char(*)[167]: (((T)0x5CBAE481D1llu)<<128) | (((T)0x275B09B690ADFA47llu)<<64) | ((T)0x85F2C077F373E659llu), \
    char(*)[168]: (((T)0x931F59E756llu)<<128) | (((T)0xBE33A780081BCD29llu)<<64) | ((T)0x720499BF14AAB967llu), \
    char(*)[169]: (((T)0x13AE2A3C61Bllu)<<128) | (((T)0xB98E6C402162C83Allu)<<64) | ((T)0xE0CA459041CF2477llu), \
    char(*)[170]: (((T)0x3667425B27Dllu)<<128) | (((T)0xAA7B66ED54E49D96llu)<<64) | ((T)0x8020E077F8199C3Bllu), \
    char(*)[171]: (((T)0x62D10B1D85Bllu)<<128) | (((T)0x659F957F4D684881llu)<<64) | ((T)0x8FD625D5CECBE8DDllu), \
    char(*)[172]: (((T)0x829D9983CD6llu)<<128) | (((T)0x19A1F4DF3F872DD2llu)<<64) | ((T)0x3D27ED162CDAE7C1llu), \
    char(*)[173]: (((T)0x4CA256BB3F6llu)<<128) | (((T)0xAC17FDAF0B3CDC95llu)<<64) | ((T)0x889DE24AA5A8A2EDllu), \
    char(*)[174]: (((T)0x971DA007200llu)<<128) | (((T)0xFC39C17186ABE2CFllu)<<64) | ((T)0x12B530A5A68A5B27llu), \
    char(*)[175]: (((T)0x7DB2F499DC90llu)<<128) | (((T)0x5F26A4FDAA7BF3D2llu)<<64) | ((T)0x3DA6361583A65679llu), \
    char(*)[176]: (((T)0x32934DAF6BF0llu)<<128) | (((T)0xBFB79FE772F78B73llu)<<64) | ((T)0x4744599D5B50F229llu), \
    char(*)[177]: (((T)0x198B85FA7C546llu)<<128) | (((T)0x74C4E083D13DB5E7llu)<<64) | ((T)0x902ABC7DFC9E08EBllu), \
    char(*)[178]: (((T)0x1BF8AE45AC9Allu)<<128) | (((T)0xBF7ACC9181C7C8D1llu)<<64) | ((T)0x8B1230D758E1C799llu), \
    char(*)[179]: (((T)0x312996FFC8898llu)<<128) | (((T)0x756232B1B7F7687Cllu)<<64) | ((T)0x527686F687175B43llu), \
    char(*)[180]: (((T)0x4198AB8DC6F20llu)<<128) | (((T)0xCC868953EEF10FE7llu)<<64) | ((T)0x7E8E47B45BB0A7DFllu), \
    char(*)[181]: (((T)0x16CEF16D5C9DD6llu)<<128) | (((T)0x79AA68DD694931F0llu)<<64) | ((T)0x4DC53847B16BB061llu), \
    char(*)[182]: (((T)0x62B539311B0FCllu)<<128) | (((T)0x2B92F563456A0095llu)<<64) | ((T)0x8069965355ABB379llu), \
    char(*)[183]: (((T)0x30E75CDDB74CBAllu)<<128) | (((T)0xE6D9478DD9A9B2D6llu)<<64) | ((T)0x4EAB1A68447D716Dllu), \
    char(*)[184]: (((T)0xC0D28878D1A4FBllu)<<128) | (((T)0xD76AC8531AD386ECllu)<<64) | ((T)0xE70F86925EF7FC23llu), \
    char(*)[185]: (((T)0x49A59005F48FEBllu)<<128) | (((T)0xEBC198B9DCC9572Allu)<<64) | ((T)0x817C92B90241C1CDllu), \
    char(*)[186]: (((T)0x2E6B51894E0E616llu)<<128) | (((T)0x43EBA5BFEEFFBFllu)<<64) | ((T)0x731E3DC458F76CB7llu), \
    char(*)[187]: (((T)0x62E0C9742FC2B32llu)<<128) | (((T)0x723C419456DB5594llu)<<64) | ((T)0xFABA8D8EF3F2F6F3llu), \
    char(*)[188]: (((T)0x8FF9CF941A38A4Bllu)<<128) | (((T)0x6DF3786337E44DECllu)<<64) | ((T)0xEA424175290AF147llu), \
    char(*)[189]: (((T)0x1943740DF8920006llu)<<128) | (((T)0xDE4E29C815583CFllu)<<64) | ((T)0xD0D170D0DBDEDDBFllu), \
    char(*)[190]: (((T)0x1DE0BEB3BD1492D1llu)<<128) | (((T)0xED3C421E9E62D6D6llu)<<64) | ((T)0x9F734426AC21FE61llu), \
    char(*)[191]: (((T)0x1BE84B10F45939F0llu)<<128) | (((T)0xC217A269C3F2E4CDllu)<<64) | ((T)0x2071840BABA2027Dllu), \
    char(*)[192]: (((T)0x6E367A2E5D332448llu)<<128) | (((T)0x99304E5199C1F58Dllu)<<64) | ((T)0xB7681A6A5B557099llu), \
    char(*)[193]: (((T)0x679E88B3927873D1llu)<<128) | (((T)0x7D9D441B16E30037llu)<<64) | ((T)0x392263E95C822F6Dllu), \
    char(*)[194]: (((T)0x3llu)<<192) | (((T)0xD76FC86B30C88412llu)<<128) | (((T)0x890983648397581Ellu)<<64) | ((T)0xA8D7A0EE431F3753llu), \
    char(*)[195]: (((T)0x5llu)<<192) | (((T)0xC377BBE1FD38394llu)<<128) | (((T)0x7DDE6A261A54F5C8llu)<<64) | ((T)0xFC6C6A2090DAFF7Fllu), \
    char(*)[196]: (((T)0xDllu)<<192) | (((T)0x6C1B3600E5AD471Fllu)<<128) | (((T)0xD5DD866CFAC89CA3llu)<<64) | ((T)0xCD7C7396DF2FF419llu), \
    char(*)[197]: (((T)0x6llu)<<192) | (((T)0xBE68FF2C440119BEllu)<<128) | (((T)0x252AA97D6C4D2508llu)<<64) | ((T)0x379445564FA4D01Fllu), \
    char(*)[198]: (((T)0x34llu)<<192) | (((T)0x13C3F2CBA88B3C9Fllu)<<128) | (((T)0xC1941589F60D6FCCllu)<<64) | ((T)0xA57457F04206AE45llu), \
    char(*)[199]: (((T)0x50llu)<<192) | (((T)0xB717BFF4BE1FD161llu)<<128) | (((T)0xF1F5ED02860E4382llu)<<64) | ((T)0xAB6DD4F909263D09llu), \
    char(*)[200]: (((T)0xBllu)<<192) | (((T)0xC2D6350B514B0763llu)<<128) | (((T)0xB361AD6446F3E76Bllu)<<64) | ((T)0xC1AD8D70711EF895llu), \
    char(*)[201]: (((T)0x11Cllu)<<192) | (((T)0x988EBB535A684A32llu)<<128) | (((T)0xFE1CB49B0E0883B8llu)<<64) | ((T)0x5482D9D9116AD1BBllu), \
    char(*)[202]: (((T)0x363llu)<<192) | (((T)0xBA821305A4D0ACCFllu)<<128) | (((T)0xC4D6DD217EF2FA0Bllu)<<64) | ((T)0x56638EC8EC846B2Dllu), \
    char(*)[203]: (((T)0xF6llu)<<192) | (((T)0x21ED8380E043775Allu)<<128) | (((T)0x10B5E663E67A8F60llu)<<64) | ((T)0xE5062658F657B0CFllu), \
    char(*)[204]: (((T)0x9DEllu)<<192) | (((T)0xE9C89D4355B53823llu)<<128) | (((T)0xE5B1C6CBB4D675DCllu)<<64) | ((T)0xB3B44CCD296CDF53llu), \
    char(*)[205]: (((T)0xB6Dllu)<<192) | (((T)0x51E2839B34D9CFFAllu)<<128) | (((T)0x6BCFF645E60211C9llu)<<64) | ((T)0x24A6EAD3BA4711F9llu), \
    char(*)[206]: (((T)0x201Allu)<<192) | (((T)0x9E0CCD5CA1DF95E9llu)<<128) | (((T)0x662493E368784786llu)<<64) | ((T)0x4B1A1DCFED1AE24Bllu), \
    char(*)[207]: (((T)0x501Dllu)<<192) | (((T)0x81542646D11E40BFllu)<<128) | (((T)0x4208B2F5A966663Allu)<<64) | ((T)0x4FDAE0563F54E891llu), \
    char(*)[208]: (((T)0xEE6Fllu)<<192) | (((T)0x342FBB4042E9C05Allu)<<128) | (((T)0xA8FEB07D81C3B9E4llu)<<64) | ((T)0x73D1D2E5631C8BA9llu), \
    char(*)[209]: (((T)0x167DFllu)<<192) | (((T)0xC6F464402ACCE2E2llu)<<128) | (((T)0xF121A459A2D1394llu)<<64) | ((T)0x46DA15947F49E139llu), \
    char(*)[210]: (((T)0x9717llu)<<192) | (((T)0x544C18A44C5DE64llu)<<128) | (((T)0x1564A379D4A7C573llu)<<64) | ((T)0x2DBA8734CFA571llu), \
    char(*)[211]: (((T)0x67C1Allu)<<192) | (((T)0xA86C21997F20B9F4llu)<<128) | (((T)0xB2C634AFC16AB25llu)<<64) | ((T)0x5DBCC81F0462A9D5llu), \
    char(*)[212]: (((T)0xA27A2llu)<<192) | (((T)0x43585F6324A77CC1llu)<<128) | (((T)0x58E44AE0F06399B3llu)<<64) | ((T)0xD82FF8BC2336A5F1llu), \
    char(*)[213]: (((T)0xB1245llu)<<192) | (((T)0x8DC76C1E7A443BA9llu)<<128) | (((T)0x340CC42170C565DCllu)<<64) | ((T)0xCB85E8C242EAD12Dllu), \
    char(*)[214]: (((T)0x2010BAllu)<<192) | (((T)0x9833AE1BA383F79Fllu)<<128) | (((T)0xDC97F97831B9C59Fllu)<<64) | ((T)0xAB2FCE2BE22D254Bllu), \
    char(*)[215]: (((T)0x39822Ellu)<<192) | (((T)0xD2CD24B6821A665Cllu)<<128) | (((T)0xD002EB2968F00Dllu)<<64) | ((T)0x8E8224C7F8C347Bllu), \
    char(*)[216]: (((T)0x6F42F7llu)<<192) | (((T)0x253D797EE025C435llu)<<128) | (((T)0xB414CE452C2CB1DDllu)<<64) | ((T)0x7BE823E0B05BD797llu), \
    char(*)[217]: (((T)0x17C8854llu)<<192) | (((T)0xB0EF15FC6C8E82B0llu)<<128) | (((T)0xEC0101B5E7001E7Cllu)<<64) | ((T)0xA47FD9498DB2E075llu), \
    char(*)[218]: (((T)0x18462F1llu)<<192) | (((T)0x8ADB1BD1458E920llu)<<128) | (((T)0x6FE032A77A710BCAllu)<<64) | ((T)0xD991C3ABD06A40DFllu), \
    char(*)[219]: (((T)0x2C1D91Fllu)<<192) | (((T)0x62D53F4FCBB4F98Dllu)<<128) | (((T)0x937B3415E354C47Ellu)<<64) | ((T)0x4963141FDE95785Dllu), \
    char(*)[220]: (((T)0xF683977llu)<<192) | (((T)0x57541E8E2F5CC8F2llu)<<128) | (((T)0x737FD876C12F58C6llu)<<64) | ((T)0x3D75355309409FFFllu), \
    char(*)[221]: (((T)0x4A1E878llu)<<192) | (((T)0x3F51B27522266689llu)<<128) | (((T)0x29981967CC838E22llu)<<64) | ((T)0xD53BB92EF75293E9llu), \
    char(*)[222]: (((T)0xADE8D0Dllu)<<192) | (((T)0xC3EBE7A8D760B99Allu)<<128) | (((T)0xD94614BA8CED9EA8llu)<<64) | ((T)0xC4A5589C56F0814Bllu), \
    char(*)[223]: (((T)0x52A3893Fllu)<<192) | (((T)0x9D88BAE7CF9556B8llu)<<128) | (((T)0x4077980C48DB14D3llu)<<64) | ((T)0x19CA66E134FE8B45llu), \
    char(*)[224]: (((T)0xB27BBF9Fllu)<<192) | (((T)0x822AE528BB103DE4llu)<<128) | (((T)0x711ED6672127024Ellu)<<64) | ((T)0x6A2519A95C5BE8CBllu), \
    char(*)[225]: (((T)0x120A958Ellu)<<192) | (((T)0x3C3A4926FF35E1D3llu)<<128) | (((T)0x3FA3AF31D5F82A48llu)<<64) | ((T)0x5EAD2BA3E214C51Dllu), \
    char(*)[226]: (((T)0x38746F093llu)<<192) | (((T)0x609F5CA516C197B0llu)<<128) | (((T)0x9982D1839711E02Ellu)<<64) | ((T)0x58923C588E3C329llu), \
    char(*)[227]: (((T)0x291B3BBDCllu)<<192) | (((T)0xA56580022302A8F1llu)<<128) | (((T)0xAAFFDB4ABAB40F2Allu)<<64) | ((T)0xF5CE45A2C08D529Bllu), \
    char(*)[228]: (((T)0x16C83CBDllu)<<192) | (((T)0x2C06A08D1605E725llu)<<128) | (((T)0x8547DE2D5D0EAE18llu)<<64) | ((T)0xC8903BFCDEE7A87llu), \
    char(*)[229]: (((T)0x86672046Dllu)<<192) | (((T)0xEF31F912774CF2BCllu)<<128) | (((T)0x23E25C05CF9FBA64llu)<<64) | ((T)0x643D4909C195D8A3llu), \
    char(*)[230]: (((T)0x1D1C800E40llu)<<192) | (((T)0xC309BD9DF1284D8llu)<<128) | (((T)0x1C13C373A5996BDllu)<<64) | ((T)0x983A890ACE876F71llu), \
    char(*)[231]: (((T)0x3C27C0FFA7llu)<<192) | (((T)0xCF75C5FD80D859CCllu)<<128) | (((T)0x89BF94996835A56Fllu)<<64) | ((T)0xFDA784CF54918FC7llu), \
    char(*)[232]: (((T)0x2E5112A30Dllu)<<192) | (((T)0x51E692F4AF5035D9llu)<<128) | (((T)0x2232C9E80E28B044llu)<<64) | ((T)0x3BCE88581ED204DDllu), \
    char(*)[233]: (((T)0x48A643342Fllu)<<192) | (((T)0x9FFCD4E8F498E36Allu)<<128) | (((T)0xEFDC2123B59A70E5llu)<<64) | ((T)0xF844885386BF4473llu), \
    char(*)[234]: (((T)0x2EC32365B89llu)<<192) | (((T)0x3C867958E0C11D20llu)<<128) | (((T)0xB1939333CA5D1ED7llu)<<64) | ((T)0xE0E9ACD0BEBABE3Fllu), \
    char(*)[235]: (((T)0x4D4832B496Cllu)<<192) | (((T)0x8E8F0FD3E7D3BC92llu)<<128) | (((T)0xD021CB7B8D3F6F6llu)<<64) | ((T)0x7ECD3777379AF247llu), \
    char(*)[236]: (((T)0x3CB176FD546llu)<<192) | (((T)0x63B9440B660F5FE4llu)<<128) | (((T)0x8F705FC32816FEBBllu)<<64) | ((T)0xE9EDFEF72836EBA9llu), \
    char(*)[237]: (((T)0x6154EBC923llu)<<192) | (((T)0x5EC5C71398A4CFC5llu)<<128) | (((T)0x1B9A2677814B4F5llu)<<64) | ((T)0x640E11DF7D01572Dllu), \
    char(*)[238]: (((T)0x21CF8F40EFEEllu)<<192) | (((T)0x2D09DC5417A4AABBllu)<<128) | (((T)0xBFC63529AA4D1A30llu)<<64) | ((T)0xB8DAAC92BE299D41llu), \
    char(*)[239]: (((T)0x7E8FD2EFE5E7llu)<<192) | (((T)0x7BDD74463D29533Ellu)<<128) | (((T)0xC89C933C305D6FE9llu)<<64) | ((T)0xEE50D2E177D73C45llu), \
    char(*)[240]: (((T)0x4F85BD872B57llu)<<192) | (((T)0xCDCFD48B42E3E111llu)<<128) | (((T)0xAD6EC22169889212llu)<<64) | ((T)0xCFB487DE49822583llu), \
    char(*)[241]: (((T)0x1F39B6F0D8B28llu)<<192) | (((T)0xF891542D2B277618llu)<<128) | (((T)0xEBA4D0725B3C432Bllu)<<64) | ((T)0x866AAD612E8D198Dllu), \
    char(*)[242]: (((T)0x320FDA5BF7259llu)<<192) | (((T)0xB99C8BDA2A62077Allu)<<128) | (((T)0x3DA9503AA61D8E68llu)<<64) | ((T)0x53504364BD773947llu), \
    char(*)[243]: (((T)0x6310A0F65A765llu)<<192) | (((T)0x55C6BB10F7E92Ellu)<<128) | (((T)0x8139C98EBE2126FBllu)<<64) | ((T)0x2DA46B1420B4820Dllu), \
    char(*)[244]: (((T)0x4AFDEA01371F7llu)<<192) | (((T)0xA15C00E5133BB1A5llu)<<128) | (((T)0x946D0C152672C1F7llu)<<64) | ((T)0xF462864DDA270FADllu), \
    char(*)[245]: (((T)0x9B39FE4FB0261llu)<<192) | (((T)0xE5A724315D1DC606llu)<<128) | (((T)0xB61530698E54B8CBllu)<<64) | ((T)0xD7A47278F3064121llu), \
    char(*)[246]: (((T)0x1BFD33A8675446llu)<<192) | (((T)0xBF63C1BDBA5611A1llu)<<128) | (((T)0x6C716B268E667CF9llu)<<64) | ((T)0xA3E11435AD3C02DBllu), \
    char(*)[247]: (((T)0x1F3007F682558Cllu)<<192) | (((T)0xBE897A0AF4E9B0B3llu)<<128) | (((T)0x762CD05F8157883Ellu)<<64) | ((T)0x48E345E7FC1477D9llu), \
    char(*)[248]: (((T)0xBD290D66207374llu)<<192) | (((T)0x16B85147D9407630llu)<<128) | (((T)0xF6EA8021654896F9llu)<<64) | ((T)0xA4CAEC979734E3E9llu), \
    char(*)[249]: (((T)0x17581A8F91DB015llu)<<192) | (((T)0xE06CB4E368E2B602llu)<<128) | (((T)0x19A9CF58FF8E4A73llu)<<64) | ((T)0xEC260E6473A1DEEFllu), \
    char(*)[250]: (((T)0x63DF1C091A2DB6llu)<<192) | (((T)0x2531D2F7D232C58Allu)<<128) | (((T)0x68C96E167FA2E675llu)<<64) | ((T)0x9E4F4332D342DABllu), \
    char(*)[251]: (((T)0x5E401BC04F35411llu)<<192) | (((T)0xD6446976A06C64A2llu)<<128) | (((T)0xE80316EC1F54DFEDllu)<<64) | ((T)0x209198C511AF0FBBllu), \
    char(*)[252]: (((T)0xD979FF246AB26AEllu)<<192) | (((T)0xEA187E72AA100639llu)<<128) | (((T)0x20033FD767C6CEFDllu)<<64) | ((T)0xFA1FFD0E409114EFllu), \
    char(*)[253]: (((T)0x1E5513D008B24EE4llu)<<192) | (((T)0xCD1D15F281026F7Ellu)<<128) | (((T)0x941661056069A2BFllu)<<64) | ((T)0x5DCB654EAB500F2Dllu), \
    char(*)[254]: (((T)0x1F35349695FE54D4llu)<<192) | (((T)0xE67E6815C7F3E32Allu)<<128) | (((T)0xFF52437227B9255Bllu)<<64) | ((T)0xD50762E43650CE8Fllu), \
    char(*)[255]: (((T)0x2B1BF66111EF02E1llu)<<192) | (((T)0x9ACEECA695758FD2llu)<<128) | (((T)0x4066F326FF579D87llu)<<64) | ((T)0x53A12034336AF095llu), \
    char(*)[256]: (((T)0x70D0DBB947047F65llu)<<192) | (((T)0xA167C1B191801647llu)<<128) | (((T)0xAFD5E106C6188C5Ellu)<<64) | ((T)0x68212196FF221C91llu), \
    char(*)[257]: (((T)0x89B204E343237E11llu)<<192) | (((T)0x7459F267F66B4F25llu)<<128) | (((T)0xF074C20183C9AA7Cllu)<<64) | ((T)0x535953BD3A6F05BDllu), \
    char(*)[258]: (((T)0x2llu)<<256) | (((T)0x47595EDB12033A84llu)<<192) | (((T)0x5D8852F569FFBDF5llu)<<128) | (((T)0xBEDB7465432ECBF2llu)<<64) | ((T)0x13561942A07AA841llu), \
    char(*)[259]: (((T)0x2llu)<<256) | (((T)0x878D113C4246E5B0llu)<<192) | (((T)0xF277AE6DE82B619Fllu)<<128) | (((T)0xCE5B9F5DE172A5E1llu)<<64) | ((T)0xB93FE03AE8A433Dllu), \
    char(*)[260]: (((T)0xCllu)<<256) | (((T)0xA752C1BD15A92A12llu)<<192) | (((T)0x7EBF2323A8847A45llu)<<128) | (((T)0x3B3433014CE80E58llu)<<64) | ((T)0x5F07DA4FCD2FB781llu), \
    char(*)[261]: (((T)0x7llu)<<256) | (((T)0x7AA2C712EA97755llu)<<192) | (((T)0xE187CC4F3A60EFB0llu)<<128) | (((T)0x5C4CCB356C7D1BC0llu)<<64) | ((T)0x6B57D02FAE8E3F9Dllu), \
    char(*)[262]: (((T)0x1Dllu)<<256) | (((T)0x2AFC5506A1C9D6F6llu)<<192) | (((T)0xCE3A5C695687F74llu)<<128) | (((T)0x87B12CC048FC3F2Fllu)<<64) | ((T)0x9A2B0B34B73C09E9llu), \
    char(*)[263]: (((T)0x2Bllu)<<256) | (((T)0x3361CAAD3282A21Allu)<<192) | (((T)0xA95D7CCDF17119B8llu)<<128) | (((T)0x9A8094DA6C825221llu)<<64) | ((T)0xD4C1285C7F021929llu), \
    char(*)[264]: (((T)0x3Fllu)<<256) | (((T)0x429ED0A83490BB16llu)<<192) | (((T)0x44C3E01FF86F870Ellu)<<128) | (((T)0xB26EBD8C4455661Cllu)<<64) | ((T)0xF47F0CE96C446679llu), \
    char(*)[265]: (((T)0x176llu)<<256) | (((T)0xE86F7B58DAB0F93Ellu)<<192) | (((T)0x932BC2AFD47E76DAllu)<<128) | (((T)0xB379E2BDC3D728B8llu)<<64) | ((T)0x3B7C5D4CC350A2DFllu), \
    char(*)[266]: (((T)0x92llu)<<256) | (((T)0xFD59A91AADF4905llu)<<192) | (((T)0xE7F4AA3CAAB8C668llu)<<128) | (((T)0x8F15157419A7E8EEllu)<<64) | ((T)0xECBD2733A1680091llu), \
    char(*)[267]: (((T)0x642llu)<<256) | (((T)0xE2D68E770DFDA830llu)<<192) | (((T)0xF0F275E4D4012607llu)<<128) | (((T)0x2C0BC1498A436328llu)<<64) | ((T)0x2A4F73E82AD86227llu), \
    char(*)[268]: (((T)0x659llu)<<256) | (((T)0x5C66F45D28716B3Bllu)<<192) | (((T)0xDAA0A0975F3134B7llu)<<128) | (((T)0xC28713E9364D40E5llu)<<64) | ((T)0xB35CD9B307045B0Fllu), \
    char(*)[269]: (((T)0x854llu)<<256) | (((T)0xA229D2FF3957DFBCllu)<<192) | (((T)0x598E0B6446CB9B45llu)<<128) | (((T)0xD9F23734461FC216llu)<<64) | ((T)0x774B15DEFBFB6F57llu), \
    char(*)[270]: (((T)0x344Dllu)<<256) | (((T)0xEB813CD13D5C3FB3llu)<<192) | (((T)0x68E57737AFAF91llu)<<128) | (((T)0x6456B9E2123F830Cllu)<<64) | ((T)0x6306582594B47BD5llu), \
    char(*)[271]: (((T)0x3B94llu)<<256) | (((T)0x308BF6BD1413939Cllu)<<192) | (((T)0xF9C847A711230F87llu)<<128) | (((T)0x7B171DA897036854llu)<<64) | ((T)0x652CC90AFD2F24A5llu), \
    char(*)[272]: (((T)0xEA08llu)<<256) | (((T)0x35AB8C44DA506B0Ellu)<<192) | (((T)0x640BD38DDBBF8945llu)<<128) | (((T)0xDCDEB0EBE7AEE38Bllu)<<64) | ((T)0xC4298BAF3A1D3AC3llu), \
    char(*)[273]: (((T)0xA290llu)<<256) | (((T)0x371C14813973B79Cllu)<<192) | (((T)0x3C61F644F50BEEC4llu)<<128) | (((T)0x37A60485DFA36B91llu)<<64) | ((T)0x1B744D220FE1EA61llu), \
    char(*)[274]: (((T)0xE761llu)<<256) | (((T)0xCB6AC852CC3D19F1llu)<<192) | (((T)0x937CA74F0BAE2651llu)<<128) | (((T)0xB6EEC0A973415ACllu)<<64) | ((T)0xA600C3F811BDA9A5llu), \
    char(*)[275]: (((T)0x5ED73llu)<<256) | (((T)0xFD90FAA2FA84298llu)<<192) | (((T)0x992966A52FBDFEFFllu)<<128) | (((T)0xB4242062D1F1223Allu)<<64) | ((T)0xAC9EE32C666AC04Fllu), \
    char(*)[276]: (((T)0x25D25llu)<<256) | (((T)0x74D8BCB2BD7A6F16llu)<<192) | (((T)0x7BF69F54B1604B08llu)<<128) | (((T)0xD973BF2E4449C0C3llu)<<64) | ((T)0x8132A8DF13180D6Fllu), \
    char(*)[277]: (((T)0x57C39llu)<<256) | (((T)0x9089516541338E9Bllu)<<192) | (((T)0xE802CD0424BBEC21llu)<<128) | (((T)0x3CF4A1027FCDE015llu)<<64) | ((T)0x1D62775FE17354E3llu), \
    char(*)[278]: (((T)0x12313Fllu)<<256) | (((T)0xAFBB6BD279520D71llu)<<192) | (((T)0x1873C9A86F0F063Ellu)<<128) | (((T)0x615BA61404CD7DBllu)<<64) | ((T)0xBA5CFD15CDE8564Fllu), \
    char(*)[279]: (((T)0x253A38llu)<<256) | (((T)0xF05F5086987A4AF3llu)<<192) | (((T)0x1100CFF02440566Cllu)<<128) | (((T)0xA487D698B7A50D0Cllu)<<64) | ((T)0xF664A400E27348F9llu), \
    char(*)[280]: (((T)0x41CF99llu)<<256) | (((T)0x270F9B296A4063Cllu)<<192) | (((T)0x1C8D82E966D79F1Cllu)<<128) | (((T)0xBC8942C8AD4F259Cllu)<<64) | ((T)0x31AF652D367278FBllu), \
    char(*)[281]: (((T)0x1FA0BE6llu)<<256) | (((T)0xE10CF06C469D849llu)<<192) | (((T)0x84DCF8483986BB34llu)<<128) | (((T)0x40E2B05F1142891Allu)<<64) | ((T)0x83C6DCA889AF9FDDllu), \
    char(*)[282]: (((T)0x1B9B246llu)<<256) | (((T)0xBC6198A64FE1B161llu)<<192) | (((T)0x91F9EB0D00A02E40llu)<<128) | (((T)0xCBCC1ABB44454401llu)<<64) | ((T)0x72D8CE715AEB3727llu), \
    char(*)[283]: (((T)0x7434D6Bllu)<<256) | (((T)0x77EF25EF24A7BDE7llu)<<192) | (((T)0xC5DDAB6DB3597B20llu)<<128) | (((T)0x65A859BC51279D35llu)<<64) | ((T)0x6805EAA57B94B679llu), \
    char(*)[284]: (((T)0xCC57A55llu)<<256) | (((T)0x6C92641E3A25D570llu)<<192) | (((T)0xEEED06A3E7B1D47Cllu)<<128) | (((T)0xA449698FE1123470llu)<<64) | ((T)0x1E3AC4343ED1FAB5llu), \
    char(*)[285]: (((T)0x17EADEEEllu)<<256) | (((T)0x808A3B6A6CAFBE8llu)<<192) | (((T)0xFC6DEF775D0AFB94llu)<<128) | (((T)0xBC97E4144993AD5Ellu)<<64) | ((T)0xA6AE186EF5D35B75llu), \
    char(*)[286]: (((T)0x3CA5FE1Ellu)<<256) | (((T)0x6F0A7CBC9C4DEC83llu)<<192) | (((T)0xCCED5784E7E713D9llu)<<128) | (((T)0xE7E9CFCD499B922Ellu)<<64) | ((T)0xDEBD1F5E4CBEB63Fllu), \
    char(*)[287]: (((T)0x25F17C4Bllu)<<256) | (((T)0x6096B7092984BA54llu)<<192) | (((T)0xFAEA58C63188BA57llu)<<128) | (((T)0x7B58E4573EAC3F96llu)<<64) | ((T)0x3DD542928D2B6B39llu), \
    char(*)[288]: (((T)0xEFE11853llu)<<256) | (((T)0xC9C4D5C40960EE9Cllu)<<192) | (((T)0x29604FE408AD73AAllu)<<128) | (((T)0xF3D003ED7B5AB465llu)<<64) | ((T)0x78C2E6A9624307llu) \
  )

#define dpa__u_choose_prime_inverse(T) _Generic((char(*)[dpa__u_bitwidth((T){0})]){0}, \
    char(*)[1]: (T)0x1llu, \
    char(*)[2]: (T)0x3llu, \
    char(*)[3]: (T)0x5llu, \
    char(*)[4]: (T)0x3llu, \
    char(*)[5]: (T)0x1bllu, \
    char(*)[6]: (T)0x15llu, \
    char(*)[7]: (T)0x6dllu, \
    char(*)[8]: ((T)0x27llu), \
    char(*)[9]: ((T)0x173llu), \
    char(*)[10]: ((T)0x359llu), \
    char(*)[11]: ((T)0x50Bllu), \
    char(*)[12]: ((T)0x611llu), \
    char(*)[13]: ((T)0x1345llu), \
    char(*)[14]: ((T)0x23B1llu), \
    char(*)[15]: ((T)0x5B45llu), \
    char(*)[16]: ((T)0x13B3llu), \
    char(*)[17]: ((T)0x11CE1llu), \
    char(*)[18]: ((T)0x10229llu), \
    char(*)[19]: ((T)0x74C43llu), \
    char(*)[20]: ((T)0x3E1E3llu), \
    char(*)[21]: ((T)0xDEC21llu), \
    char(*)[22]: ((T)0x278603llu), \
    char(*)[23]: ((T)0x2EE0D9llu), \
    char(*)[24]: ((T)0xDD9C8Fllu), \
    char(*)[25]: ((T)0xBB3B65llu), \
    char(*)[26]: ((T)0x302565Dllu), \
    char(*)[27]: ((T)0x708825llu), \
    char(*)[28]: ((T)0xD5CB5A7llu), \
    char(*)[29]: ((T)0x120AEAEBllu), \
    char(*)[30]: ((T)0x14D26C83llu), \
    char(*)[31]: ((T)0x6342432Fllu), \
    char(*)[32]: ((T)0xCEAC0303llu), \
    char(*)[33]: ((T)0x1A4963F97llu), \
    char(*)[34]: ((T)0x1FDF578CBllu), \
    char(*)[35]: ((T)0x2CD0C4D79llu), \
    char(*)[36]: ((T)0xAC1404A1llu), \
    char(*)[37]: ((T)0x1936DABC0Dllu), \
    char(*)[38]: ((T)0x1D2F860D6Fllu), \
    char(*)[39]: ((T)0x4433388C73llu), \
    char(*)[40]: ((T)0xD19E2F4671llu), \
    char(*)[41]: ((T)0x19506828569llu), \
    char(*)[42]: ((T)0xE301615AAFllu), \
    char(*)[43]: ((T)0x7AA3D700679llu), \
    char(*)[44]: ((T)0xBE8A9685D2Fllu), \
    char(*)[45]: ((T)0xE8C42EA2CA5llu), \
    char(*)[46]: ((T)0x1AC464E3EA1Dllu), \
    char(*)[47]: ((T)0x680CEFB96489llu), \
    char(*)[48]: ((T)0x274004DDCAA5llu), \
    char(*)[49]: ((T)0x1AE3576FF864Dllu), \
    char(*)[50]: ((T)0xB62F064C8303llu), \
    char(*)[51]: ((T)0x23492A96F2E71llu), \
    char(*)[52]: ((T)0x11E36D02545F1llu), \
    char(*)[53]: ((T)0x26402F389AD57llu), \
    char(*)[54]: ((T)0x252D756D663AF7llu), \
    char(*)[55]: ((T)0x44F480B25AF431llu), \
    char(*)[56]: ((T)0xCCA7A7E1E0B3D5llu), \
    char(*)[57]: ((T)0x10E754269CB211Fllu), \
    char(*)[58]: ((T)0x1ABD04B050E219Bllu), \
    char(*)[59]: ((T)0x4C7A0857D4AD20Bllu), \
    char(*)[60]: ((T)0xFABCF04D39C0DFllu), \
    char(*)[61]: ((T)0x18709902B3BC2A07llu), \
    char(*)[62]: ((T)0x30D4E1E356D1B6Bllu), \
    char(*)[63]: ((T)0x6EA678D9E68F9CDDllu), \
    char(*)[64]: ((T)0xFF4F5C9307416443llu), \
    char(*)[65]: ((T)0x8F0FC704BA4D445llu), \
    char(*)[66]: (((T)0x3llu)<<64) | ((T)0x635AF4FCCB9FFBA1llu), \
    char(*)[67]: (((T)0x1llu)<<64) | ((T)0xE71DAE1188E65859llu), \
    char(*)[68]: (((T)0x2llu)<<64) | ((T)0x383098571A0DB205llu), \
    char(*)[69]: (((T)0x18llu)<<64) | ((T)0xFC321D60A76A05E1llu), \
    char(*)[70]: (((T)0x34llu)<<64) | ((T)0xFFA97A29216CD003llu), \
    char(*)[71]: (((T)0x7Dllu)<<64) | ((T)0xB2EFB6C5EF3CC483llu), \
    char(*)[72]: (((T)0xAEllu)<<64) | ((T)0xB2BB53913B26C25Bllu), \
    char(*)[73]: (((T)0x197llu)<<64) | ((T)0x8FCADBB99C2C7301llu), \
    char(*)[74]: (((T)0x281llu)<<64) | ((T)0x80CB1E2C0F1C99C5llu), \
    char(*)[75]: (((T)0x3C2llu)<<64) | ((T)0x33754FDB09D65C3Fllu), \
    char(*)[76]: (((T)0xE4Cllu)<<64) | ((T)0xB1445F2C80AEDB05llu), \
    char(*)[77]: (((T)0xE91llu)<<64) | ((T)0xC0A53EC5B7337C19llu), \
    char(*)[78]: (((T)0x1354llu)<<64) | ((T)0xBC91EB93188BC3D3llu), \
    char(*)[79]: (((T)0x1608llu)<<64) | ((T)0x392C80D6D0DD4095llu), \
    char(*)[80]: (((T)0xD7AFllu)<<64) | ((T)0x5D8BFB0E6978D7D1llu), \
    char(*)[81]: (((T)0x1937Fllu)<<64) | ((T)0x5E882528C50B9163llu), \
    char(*)[82]: (((T)0x267D0llu)<<64) | ((T)0x92454D2B948CCFDBllu), \
    char(*)[83]: (((T)0x40FC8llu)<<64) | ((T)0x74F74E1AB84032CDllu), \
    char(*)[84]: (((T)0x57B33llu)<<64) | ((T)0x746DF2342B99D567llu), \
    char(*)[85]: (((T)0x644B5llu)<<64) | ((T)0x3BA9832EFCF06219llu), \
    char(*)[86]: (((T)0x2C66EAllu)<<64) | ((T)0xD53067F092F67B75llu), \
    char(*)[87]: (((T)0x7DD15Ellu)<<64) | ((T)0x5CF9630944595683llu), \
    char(*)[88]: (((T)0x7482ABllu)<<64) | ((T)0x9C98D823BDB891Bllu), \
    char(*)[89]: (((T)0x12C7347llu)<<64) | ((T)0xD2D329C8BF0C3A23llu), \
    char(*)[90]: (((T)0x1A2532Allu)<<64) | ((T)0x655AE6DC9AF77E19llu), \
    char(*)[91]: (((T)0x73C0D29llu)<<64) | ((T)0x5820E252AD5A0B6Bllu), \
    char(*)[92]: (((T)0xBBFC0A7llu)<<64) | ((T)0x3857F26A5B9A8215llu), \
    char(*)[93]: (((T)0x7432C56llu)<<64) | ((T)0x9C352520FCFFF9B9llu), \
    char(*)[94]: (((T)0x18576615llu)<<64) | ((T)0x6CADFA9F50A814Bllu), \
    char(*)[95]: (((T)0x330161CCllu)<<64) | ((T)0xC97C2042048AEC3Dllu), \
    char(*)[96]: (((T)0xCFD39206llu)<<64) | ((T)0x97E584D859185BF7llu), \
    char(*)[97]: (((T)0x7B3AF088llu)<<64) | ((T)0x895512021360ED49llu), \
    char(*)[98]: (((T)0xE19523B9llu)<<64) | ((T)0x690EC445EFDDD51Dllu), \
    char(*)[99]: (((T)0x1DA321B79llu)<<64) | ((T)0xF181F01CCF4A30D3llu), \
    char(*)[100]: (((T)0x89A87EB92llu)<<64) | ((T)0xFA685AA71B3581F9llu), \
    char(*)[101]: (((T)0x12792C686Dllu)<<64) | ((T)0x5C8889126CF98235llu), \
    char(*)[102]: (((T)0x18715B5693llu)<<64) | ((T)0x9B717604BD677AD9llu), \
    char(*)[103]: (((T)0x6D46A6237Dllu)<<64) | ((T)0xD3A8EAC3BD53BA5Dllu), \
    char(*)[104]: (((T)0xAA55AA5153llu)<<64) | ((T)0xF379912A2ABD0E0Fllu), \
    char(*)[105]: (((T)0x19EB9639F5Ellu)<<64) | ((T)0xB163F716866E2243llu), \
    char(*)[106]: (((T)0x23D1EC4CC82llu)<<64) | ((T)0x1DCF3C81080B75F5llu), \
    char(*)[107]: (((T)0x80A240332Cllu)<<64) | ((T)0xA258E1A0ECB92807llu), \
    char(*)[108]: (((T)0x42D4663B4D0llu)<<64) | ((T)0x6844BD07517D31CBllu), \
    char(*)[109]: (((T)0x175F55BCA3Dllu)<<64) | ((T)0xB14221E4D6C6EBA1llu), \
    char(*)[110]: (((T)0x259610BB0317llu)<<64) | ((T)0x2928B8C3A77811A1llu), \
    char(*)[111]: (((T)0x742DC396875Fllu)<<64) | ((T)0xC22173F0E80CAE19llu), \
    char(*)[112]: (((T)0x27F4BB9ABFE6llu)<<64) | ((T)0xC264AE650C921FD9llu), \
    char(*)[113]: (((T)0x1D2640F1F5842llu)<<64) | ((T)0x4252CAFC0EDD2645llu), \
    char(*)[114]: (((T)0x3A5C67E3B8F42llu)<<64) | ((T)0x446FA3D518265DBllu), \
    char(*)[115]: (((T)0x6F8F360A73CE0llu)<<64) | ((T)0xD10F67C931BA635llu), \
    char(*)[116]: (((T)0xFFCEB676B394Bllu)<<64) | ((T)0x7C09FEBFCC691729llu), \
    char(*)[117]: (((T)0x595C976C1E608llu)<<64) | ((T)0xA48F57E6FE09053Dllu), \
    char(*)[118]: (((T)0x10D63E35DE6E74llu)<<64) | ((T)0x600AAF9532843E41llu), \
    char(*)[119]: (((T)0x6C6D8F6CFA3451llu)<<64) | ((T)0xC7EC160515B6D47llu), \
    char(*)[120]: (((T)0xEA2EFC4B7A0EDCllu)<<64) | ((T)0x19809A0E1F9EAA8Bllu), \
    char(*)[121]: (((T)0x153C5A75500F21Cllu)<<64) | ((T)0x3FC66623EB07C0DFllu), \
    char(*)[122]: (((T)0x331EFA37203F3A8llu)<<64) | ((T)0xE498A95AB6B8352Fllu), \
    char(*)[123]: (((T)0x4224B3C55940830llu)<<64) | ((T)0x735C52862C8DDC2Bllu), \
    char(*)[124]: (((T)0xA42AE6D614D15CFllu)<<64) | ((T)0x9550650B57ABBB39llu), \
    char(*)[125]: (((T)0x1E455208E43999A4llu)<<64) | ((T)0xB9EC97718710C47llu), \
    char(*)[126]: (((T)0x211BEF556824A73Allu)<<64) | ((T)0xB8F2ACFAE79B7DEFllu), \
    char(*)[127]: (((T)0x6B367312075A36B9llu)<<64) | ((T)0x54B17D824AE2CCFllu), \
    char(*)[128]: (((T)0xE51AF71B437AACB1llu)<<64) | ((T)0x2CFBA851E4F1725llu), \
    char(*)[129]: (((T)0x51F9F6342F8A6BE2llu)<<64) | ((T)0x123FC17B34190BB1llu), \
    char(*)[130]: (((T)0x194EA682D55D7BCDllu)<<64) | ((T)0xE3427510E070DC4Fllu), \
    char(*)[131]: (((T)0x3llu)<<128) | (((T)0xE22287BD0D4972BFllu)<<64) | ((T)0x4CB7701A1A9D3A05llu), \
    char(*)[132]: (((T)0x5llu)<<128) | (((T)0xD786A8F5D26386D5llu)<<64) | ((T)0x4A0A03D93D8A846Bllu), \
    char(*)[133]: (((T)0x7llu)<<128) | (((T)0x6A4D2285C10DCEA1llu)<<64) | ((T)0xA0998778CFD798E5llu), \
    char(*)[134]: (((T)0x28llu)<<128) | (((T)0xCBCFBD852BE0208Bllu)<<64) | ((T)0xB0921F60909B9CB9llu), \
    char(*)[135]: (((T)0x7Dllu)<<128) | (((T)0xC297CAE1E4AD4C7Dllu)<<64) | ((T)0x9EFDA941C399EDA1llu), \
    char(*)[136]: (((T)0x2Allu)<<128) | (((T)0xF5C1704141CDC2A9llu)<<64) | ((T)0x6BA487D68FEB2B45llu), \
    char(*)[137]: (((T)0x13Allu)<<128) | (((T)0xACE4279960946482llu)<<64) | ((T)0x51F890AC35534D53llu), \
    char(*)[138]: (((T)0x87llu)<<128) | (((T)0x4FB7EF46DDCBDF90llu)<<64) | ((T)0xF10E5782AA2DC44Dllu), \
    char(*)[139]: (((T)0x100llu)<<128) | (((T)0x73775B7CA6870546llu)<<64) | ((T)0x7740411478549E61llu), \
    char(*)[140]: (((T)0xFDCllu)<<128) | (((T)0xA798196C9743A3C2llu)<<64) | ((T)0x1334CBB5F9BC27EFllu), \
    char(*)[141]: (((T)0x590llu)<<128) | (((T)0xD03500AB1B7A73BEllu)<<64) | ((T)0xB0700101674209FFllu), \
    char(*)[142]: (((T)0x1EF0llu)<<128) | (((T)0x26DC8E18020F525Dllu)<<64) | ((T)0x2B650E64052D6D4Fllu), \
    char(*)[143]: (((T)0x6CDCllu)<<128) | (((T)0x6FD6CD90716777CBllu)<<64) | ((T)0x79B6DAF9B0CCFA5llu), \
    char(*)[144]: (((T)0xED10llu)<<128) | (((T)0x1BED6FC9D46F3A94llu)<<64) | ((T)0x3D73DF1987B80373llu), \
    char(*)[145]: (((T)0xCD55llu)<<128) | (((T)0x6F9B949EE281AE26llu)<<64) | ((T)0xC77727F38083E90Bllu), \
    char(*)[146]: (((T)0x66C1llu)<<128) | (((T)0x3C4578E2D3875C0Allu)<<64) | ((T)0xF9EB1D61F9008EA3llu), \
    char(*)[147]: (((T)0x270E9llu)<<128) | (((T)0xA7155A2DDEDAB2B2llu)<<64) | ((T)0x9C6546D688744491llu), \
    char(*)[148]: (((T)0xEC2C6llu)<<128) | (((T)0xD058DF24801F7002llu)<<64) | ((T)0xCA150B1013CED167llu), \
    char(*)[149]: (((T)0x180D06llu)<<128) | (((T)0x531134C1A3E3A33Dllu)<<64) | ((T)0x8284E05CB06E6161llu), \
    char(*)[150]: (((T)0x2398DBllu)<<128) | (((T)0x777E9C93231B1C0llu)<<64) | ((T)0xADF5365BD424C4CDllu), \
    char(*)[151]: (((T)0x47BFDAllu)<<128) | (((T)0x7575798F62A2D885llu)<<64) | ((T)0x21DD59822A3F38A7llu), \
    char(*)[152]: (((T)0x609A92llu)<<128) | (((T)0x5A9C86BD8338FFFFllu)<<64) | ((T)0xEBC1C0FD05DB3D31llu), \
    char(*)[153]: (((T)0x8B7125llu)<<128) | (((T)0x790B7D15F3517630llu)<<64) | ((T)0x63257C8AEA9A06A1llu), \
    char(*)[154]: (((T)0x3AF00F5llu)<<128) | (((T)0x6EDB5EA70B4C1B30llu)<<64) | ((T)0xB80707BAC65F4A71llu), \
    char(*)[155]: (((T)0x64C3E19llu)<<128) | (((T)0x682C81064681A5CBllu)<<64) | ((T)0x97A6D4B554494397llu), \
    char(*)[156]: (((T)0x974A317llu)<<128) | (((T)0xA93A5EBAEF94D7BAllu)<<64) | ((T)0x9BDA8ACB153B66AFllu), \
    char(*)[157]: (((T)0x2AAA700llu)<<128) | (((T)0x2419D1799F6792E7llu)<<64) | ((T)0xB1BF9845DEB3DDDBllu), \
    char(*)[158]: (((T)0x258AF895llu)<<128) | (((T)0x1F3DE25D406F537Allu)<<64) | ((T)0xD7B4C27D2AF9748Fllu), \
    char(*)[159]: (((T)0x41AC9571llu)<<128) | (((T)0xD64EBAAA6A273A0Fllu)<<64) | ((T)0xAE45D08B28D6DBE5llu), \
    char(*)[160]: (((T)0x6090F3EAllu)<<128) | (((T)0x42F887DCD4398668llu)<<64) | ((T)0xFB322E238310B637llu), \
    char(*)[161]: (((T)0x4DE5A5Cllu)<<128) | (((T)0x6423E2A75E265C5Cllu)<<64) | ((T)0xA36D8192C7BBE243llu), \
    char(*)[162]: (((T)0x1B96E1320llu)<<128) | (((T)0xC2FCAA9BE3CA0183llu)<<64) | ((T)0x90AF679C4949DF79llu), \
    char(*)[163]: (((T)0x3A7C3E456llu)<<128) | (((T)0x33C819AC0A7ED4F8llu)<<64) | ((T)0x5D0BD2C30CFD883Dllu), \
    char(*)[164]: (((T)0xAE4DC7175llu)<<128) | (((T)0xCB63093E6D4D046llu)<<64) | ((T)0x30EE39E6BCB71DA1llu), \
    char(*)[165]: (((T)0xF753B3ACFllu)<<128) | (((T)0xADD266594A6F806Allu)<<64) | ((T)0x4B6225679DDB55D3llu), \
    char(*)[166]: (((T)0x3DFA1D0D8Ellu)<<128) | (((T)0xE736B21C623FBEFBllu)<<64) | ((T)0x1AB1FAA1B12670D9llu), \
    char(*)[167]: (((T)0x11EA781FC0llu)<<128) | (((T)0xF53152C5AB864EA7llu)<<64) | ((T)0x85136740FAE501E9llu), \
    char(*)[168]: (((T)0x5BE42034BAllu)<<128) | (((T)0x55189E65DCFA1895llu)<<64) | ((T)0x5C19F92509A85257llu), \
    char(*)[169]: (((T)0x1A325116232llu)<<128) | (((T)0xF8B2A6C5D65D37EBllu)<<64) | ((T)0xAB93EE9DC851F547llu), \
    char(*)[170]: (((T)0x346652267BCllu)<<128) | (((T)0x8A2EF420CC3F50Allu)<<64) | ((T)0x307592F8976ADCF3llu), \
    char(*)[171]: (((T)0x6EBA98C30F3llu)<<128) | (((T)0x7149F9E4A5A84587llu)<<64) | ((T)0x6B15BC0489662F75llu), \
    char(*)[172]: (((T)0x300227BBA7llu)<<128) | (((T)0xC47C4FD868BB0994llu)<<64) | ((T)0x57F31EF7BD752841llu), \
    char(*)[173]: (((T)0x139D43224607llu)<<128) | (((T)0xA4205E069FDBA131llu)<<64) | ((T)0xEFD8210F8ACD0AE5llu), \
    char(*)[174]: (((T)0x372D86718F6Dllu)<<128) | (((T)0x97007954F1EB6E72llu)<<64) | ((T)0xFD366546828F6497llu), \
    char(*)[175]: (((T)0x4E88DA113307llu)<<128) | (((T)0xCD8885032D67FF69llu)<<64) | ((T)0xB8149C729D8C33C9llu), \
    char(*)[176]: (((T)0x6A98091D08F8llu)<<128) | (((T)0x9D3DAFE71AD8AD1llu)<<64) | ((T)0xB118DFA86E64CA19llu), \
    char(*)[177]: (((T)0x1DB0E6FF1116Allu)<<128) | (((T)0x67FBD5D12B69BD51llu)<<64) | ((T)0xD46433C036F05FC3llu), \
    char(*)[178]: (((T)0x2863A97F2A735llu)<<128) | (((T)0xC285C2BEC838327Cllu)<<64) | ((T)0xA8AACF4AF3229CA9llu), \
    char(*)[179]: (((T)0x4D03B834A9B3Fllu)<<128) | (((T)0x441F24037EBD731Dllu)<<64) | ((T)0x3D59A2A583A2896Bllu), \
    char(*)[180]: (((T)0x54B9957C605E4llu)<<128) | (((T)0x3D8C6843B9A5001llu)<<64) | ((T)0x1534EB2CC449D41Fllu), \
    char(*)[181]: (((T)0x1DB42A3709785Ellu)<<128) | (((T)0x5FEE9C4A678C18CCllu)<<64) | ((T)0xC9324208E91AF3A1llu), \
    char(*)[182]: (((T)0x30A4F901353D3Cllu)<<128) | (((T)0x5AE20C8A3BD2C240llu)<<64) | ((T)0x508AF730D5C546C9llu), \
    char(*)[183]: (((T)0x6291371D8410D7llu)<<128) | (((T)0xF17988AB4D2DE803llu)<<64) | ((T)0x30092D6E25634065llu), \
    char(*)[184]: (((T)0x16CF574B4B2F8Dllu)<<128) | (((T)0x895635FF0C3103E0llu)<<64) | ((T)0x590FC25A0846938Bllu), \
    char(*)[185]: (((T)0x279A11DFCA51Ellu)<<128) | (((T)0x2C0174A7435D8549llu)<<64) | ((T)0x81BC0BA4AFA91305llu), \
    char(*)[186]: (((T)0x1E2A3155EC9DDBBllu)<<128) | (((T)0xD52CE8D69D18F7C6llu)<<64) | ((T)0x4D8AEA5052FB3107llu), \
    char(*)[187]: (((T)0x28DEDC93ED04C3Bllu)<<128) | (((T)0xB82019E29F9AADC1llu)<<64) | ((T)0x4160C25878CC123Bllu), \
    char(*)[188]: (((T)0x7A4381F83099B1Bllu)<<128) | (((T)0x7A995B5E58DFB5F7llu)<<64) | ((T)0x109B3657B1736877llu), \
    char(*)[189]: (((T)0xF50ABD221BEE891llu)<<128) | (((T)0xB7BE4890C20DBC18llu)<<64) | ((T)0x439036E40B70123Fllu), \
    char(*)[190]: (((T)0xD2A62CADC99E2D8llu)<<128) | (((T)0x6027A27C59121940llu)<<64) | ((T)0x13348F8E84BB25A1llu), \
    char(*)[191]: (((T)0x23DD38DC930AC413llu)<<128) | (((T)0x6278E641222DF89Bllu)<<64) | ((T)0xD416945ADAC906D5llu), \
    char(*)[192]: (((T)0x9A26D133CDB123FDllu)<<128) | (((T)0x7CBC8A2E99ADB368llu)<<64) | ((T)0x5083A4D2BB69E3A9llu), \
    char(*)[193]: (((T)0x1llu)<<192) | (((T)0x9265D5D5C616BEDFllu)<<128) | (((T)0xDF2A7FAFE90261B0llu)<<64) | ((T)0x6444F90164E03265llu), \
    char(*)[194]: (((T)0x3llu)<<192) | (((T)0xDB29F7476AB5C7Bllu)<<128) | (((T)0xBE486C6D09A2724Allu)<<64) | ((T)0x5A78B78010EC24DBllu), \
    char(*)[195]: (((T)0x1llu)<<192) | (((T)0xF6DD9DBCC61208F1llu)<<128) | (((T)0xE730AB0343CED025llu)<<64) | ((T)0x4C84AD7AFA44C07Fllu), \
    char(*)[196]: (((T)0xFllu)<<192) | (((T)0x2EB9C7995C260C58llu)<<128) | (((T)0x59B76061114E3908llu)<<64) | ((T)0x7D132DE8725E2829llu), \
    char(*)[197]: (((T)0xBllu)<<192) | (((T)0x8576DD51595CF13Ellu)<<128) | (((T)0x648E6F3D208D9308llu)<<64) | ((T)0x94E378F4A256ABDFllu), \
    char(*)[198]: (((T)0x3Cllu)<<192) | (((T)0xB74C1568EFC784Ellu)<<128) | (((T)0x2D72E3D9A02E100Cllu)<<64) | ((T)0x664DE638FFFC348Dllu), \
    char(*)[199]: (((T)0x6Ellu)<<192) | (((T)0xB8B745CFFA54AE42llu)<<128) | (((T)0x342E5D9893C4755Cllu)<<64) | ((T)0x57824453E17C6139llu), \
    char(*)[200]: (((T)0xCCllu)<<192) | (((T)0xC7C0C27B3B1BEA49llu)<<128) | (((T)0xA994EB976B091935llu)<<64) | ((T)0x156E5CE9E20812BDllu), \
    char(*)[201]: (((T)0x194llu)<<192) | (((T)0x26CC9ABB4BE80479llu)<<128) | (((T)0xBB32EB56834F477Fllu)<<64) | ((T)0x7BB6950D1A964B73llu), \
    char(*)[202]: (((T)0xA9llu)<<192) | (((T)0x757C1CBE056DF18Bllu)<<128) | (((T)0xF3A38ED4E29F5DF5llu)<<64) | ((T)0xE8F820B73B661CA5llu), \
    char(*)[203]: (((T)0x5E3llu)<<192) | (((T)0x3C452D3789EAC634llu)<<128) | (((T)0x50E15ABF23CA0CBCllu)<<64) | ((T)0x137D7F101DAF562Fllu), \
    char(*)[204]: (((T)0xDC3llu)<<192) | (((T)0x616306459AFC344Fllu)<<128) | (((T)0x72A524FFDACA861Dllu)<<64) | ((T)0x9DF40835E534BCDBllu), \
    char(*)[205]: (((T)0x993llu)<<192) | (((T)0xA18C695A0ABC50CCllu)<<128) | (((T)0xA67CA5CC5A6987E6llu)<<64) | ((T)0xA839A9018292E049llu), \
    char(*)[206]: (((T)0x1AD0llu)<<192) | (((T)0xF60409FF474A2EACllu)<<128) | (((T)0xBF877396EA776420llu)<<64) | ((T)0xBA809DEEBB395763llu), \
    char(*)[207]: (((T)0x7931llu)<<192) | (((T)0xF39FDAB8B32D2015llu)<<128) | (((T)0xAF9D626FE26C2AA0llu)<<64) | ((T)0x88BB57DBE01BD871llu), \
    char(*)[208]: (((T)0x6B3Cllu)<<192) | (((T)0x4E232D9AA70E9C70llu)<<128) | (((T)0x20FE5059EE4C7AF9llu)<<64) | ((T)0x1701A85849014899llu), \
    char(*)[209]: (((T)0x12366llu)<<192) | (((T)0x3717961E1974AF80llu)<<128) | (((T)0xF2F18A976BFDB6D9llu)<<64) | ((T)0xF4AC70A47420BD09llu), \
    char(*)[210]: (((T)0x1245Allu)<<192) | (((T)0xFE5E77296C696F68llu)<<128) | (((T)0x10A5BCE349DE8EBEllu)<<64) | ((T)0x2867ACA6E5467B91llu), \
    char(*)[211]: (((T)0x24AE0llu)<<192) | (((T)0xCA539F89EF8009B8llu)<<128) | (((T)0x694CDE76AC1EE15Fllu)<<64) | ((T)0x174DA8672F55477Dllu), \
    char(*)[212]: (((T)0x3B49Ellu)<<192) | (((T)0xEBE82E37E8B45302llu)<<128) | (((T)0x5EC5FBB88902F9FCllu)<<64) | ((T)0x9583E411DDF7AB11llu), \
    char(*)[213]: (((T)0x999E1llu)<<192) | (((T)0xCE42433FD3616880llu)<<128) | (((T)0xBD942AC21CCBBCFBllu)<<64) | ((T)0x102C5BF68194A6A5llu), \
    char(*)[214]: (((T)0x2F72FDllu)<<192) | (((T)0x47E1D4BCA20F2717llu)<<128) | (((T)0xE313EDA84499AB57llu)<<64) | ((T)0x40F680E954473C63llu), \
    char(*)[215]: (((T)0x4FA536llu)<<192) | (((T)0x2072EDFFC587527Cllu)<<128) | (((T)0x134D66FA5FDE691Ellu)<<64) | ((T)0x4597F7BDAEF78AB3llu), \
    char(*)[216]: (((T)0x7F52E9llu)<<192) | (((T)0x4CEBA1950CF15D0llu)<<128) | (((T)0xAA1D9F42139D0F76llu)<<64) | ((T)0x6C2B09B382141827llu), \
    char(*)[217]: (((T)0x4B39A0llu)<<192) | (((T)0xB2D281704AFA310Cllu)<<128) | (((T)0xA153BD5ECB6E6189llu)<<64) | ((T)0x7890C209E80BEFDDllu), \
    char(*)[218]: (((T)0x3739AA0llu)<<192) | (((T)0x6988793A90E386FCllu)<<128) | (((T)0x4EF8967C2FB0B1A0llu)<<64) | ((T)0xA0BB304B5E97B1Fllu), \
    char(*)[219]: (((T)0x22669F6llu)<<192) | (((T)0x63A70002A5A40E2Fllu)<<128) | (((T)0xA7A5F8E9C0C5FD52llu)<<64) | ((T)0xC457439AD82A1BF5llu), \
    char(*)[220]: (((T)0x2DA5206llu)<<192) | (((T)0x7027170A313D3DC1llu)<<128) | (((T)0x9872B19A797BBA8Fllu)<<64) | ((T)0x5C26309C92BF5FFFllu), \
    char(*)[221]: (((T)0xD7D652Bllu)<<192) | (((T)0x47E7DCC878685025llu)<<128) | (((T)0x9F915DD7ADF5AFF8llu)<<64) | ((T)0x3C815E638CFD7459llu), \
    char(*)[222]: (((T)0x17ED0373llu)<<192) | (((T)0x2641CD55A4CD8DBEllu)<<128) | (((T)0x7D53B9D8185697FAllu)<<64) | ((T)0xDB2F7C0F823A0063llu), \
    char(*)[223]: (((T)0x219F3C8Bllu)<<192) | (((T)0xDB7B4CF6C0D3FC62llu)<<128) | (((T)0x6051CAFEDC72F9C4llu)<<64) | ((T)0xC7F92977EB374F8Dllu), \
    char(*)[224]: (((T)0x3D4799FAllu)<<192) | (((T)0x3B6814DADB0F794Fllu)<<128) | (((T)0x5D4BCB059927B3ADllu)<<64) | ((T)0x2E15C0A61EB33CE3llu), \
    char(*)[225]: (((T)0x4BAB7324llu)<<192) | (((T)0x6144ABD8720EFE3Bllu)<<128) | (((T)0x52E15D7FE5EB5104llu)<<64) | ((T)0xF907D3C3FE2E2535llu), \
    char(*)[226]: (((T)0x235202465llu)<<192) | (((T)0x48EB986FE11CDEE0llu)<<128) | (((T)0x2187FFCEBB780118llu)<<64) | ((T)0x6B5154DFEEE98919llu), \
    char(*)[227]: (((T)0x35B6BC8FDllu)<<192) | (((T)0x6763EB2E39318345llu)<<128) | (((T)0x50D30C35C883296Bllu)<<64) | ((T)0x97BCD4D408E14393llu), \
    char(*)[228]: (((T)0xA09221427llu)<<192) | (((T)0x8C32F06F0D1B7945llu)<<128) | (((T)0x4DB9746FCF94ED1Ellu)<<64) | ((T)0xB9AE4BCB64192B37llu), \
    char(*)[229]: (((T)0x14EAA68F91llu)<<192) | (((T)0xA987DDB132EB34AEllu)<<128) | (((T)0x3631913749FE056Dllu)<<64) | ((T)0xC21EEF60A7579B0Bllu), \
    char(*)[230]: (((T)0x12804BCEB0llu)<<192) | (((T)0x5A4346BD66286BD0llu)<<128) | (((T)0xA4CAAA7F7B5FB199llu)<<64) | ((T)0xBB7CE1C2A4297191llu), \
    char(*)[231]: (((T)0xE47A0B642llu)<<192) | (((T)0x48DF4B057197E6F0llu)<<128) | (((T)0xCB7A83F007CD22DCllu)<<64) | ((T)0x683BC670370D81F7llu), \
    char(*)[232]: (((T)0xF52DBF28BBllu)<<192) | (((T)0xEB4F2AFCA946E88Dllu)<<128) | (((T)0xFFA6DE9E8CDB69A2llu)<<64) | ((T)0x2A68FC2B5B9EF375llu), \
    char(*)[233]: (((T)0x12C3A7C3167llu)<<192) | (((T)0xAF64DACB0A72A8E3llu)<<128) | (((T)0x5CE6C9C65D111865llu)<<64) | ((T)0x64570729DB5300BBllu), \
    char(*)[234]: (((T)0x10A2F25E2AFllu)<<192) | (((T)0xDE1830D4EE3C6A21llu)<<128) | (((T)0xA4FA68D722A039BEllu)<<64) | ((T)0x47B917F3DF3E31BFllu), \
    char(*)[235]: (((T)0x5F9E2B2D67Allu)<<192) | (((T)0xC83E482828CE2990llu)<<128) | (((T)0x2CD83FC6DA66A4E0llu)<<64) | ((T)0xD3B656E648A31777llu), \
    char(*)[236]: (((T)0x83FEA4A389Allu)<<192) | (((T)0x4FDA8356C308F598llu)<<128) | (((T)0x43169B7FEBC0869Dllu)<<64) | ((T)0x3ABF0722063CE899llu), \
    char(*)[237]: (((T)0x3008C6376A5llu)<<192) | (((T)0xBF6B7E3D2ED510ADllu)<<128) | (((T)0xE73BA3123F4D7F7llu)<<64) | ((T)0xF031C8F8297010A5llu), \
    char(*)[238]: (((T)0x3111F8DF91C4llu)<<192) | (((T)0x32F177D6FE8EB158llu)<<128) | (((T)0x6F0434E8557C4570llu)<<64) | ((T)0xF93B7ED6A8B9F2C1llu), \
    char(*)[239]: (((T)0x4E9127B34BA7llu)<<192) | (((T)0xC65303DA8660C25llu)<<128) | (((T)0x22C3B83DAA604D0Ellu)<<64) | ((T)0x9D9B3234CEBC768Dllu), \
    char(*)[240]: (((T)0x5D7F4F17F8AAllu)<<192) | (((T)0xB49FFE06C5180102llu)<<128) | (((T)0x44F133B547109998llu)<<64) | ((T)0xD389B85177E2112Bllu), \
    char(*)[241]: (((T)0x15DA924DC2469llu)<<192) | (((T)0xED26AE9379EEC19Ellu)<<128) | (((T)0xBFB5700717F81D2Allu)<<64) | ((T)0x763FBE9BAD8CD145llu), \
    char(*)[242]: (((T)0x13F0811C598C4llu)<<192) | (((T)0xC9D32C30BBACB93Allu)<<128) | (((T)0x5058D7E7CD8A37E6llu)<<64) | ((T)0x595F70C52BF8A077llu), \
    char(*)[243]: (((T)0x5AE754BA08307llu)<<192) | (((T)0xF3F4A401D14C8A8llu)<<128) | (((T)0x82C75B59EF268EA2llu)<<64) | ((T)0x5756FD182F389CC5llu), \
    char(*)[244]: (((T)0xFCB2698EA10DFllu)<<192) | (((T)0xDCF502DE2397633Dllu)<<128) | (((T)0x59EDE4F75650E84Ellu)<<64) | ((T)0x683B399A096D2C25llu), \
    char(*)[245]: (((T)0x1740ED232D1329llu)<<192) | (((T)0xE77ECE7B49F9D56Allu)<<128) | (((T)0x1739567520F56EEBllu)<<64) | ((T)0x296552CC36AE82E1llu), \
    char(*)[246]: (((T)0x307B55130FC993llu)<<192) | (((T)0x8DBFE8095E4A2667llu)<<128) | (((T)0x209D463B3964F7C1llu)<<64) | ((T)0x5A0FD9D108222953llu), \
    char(*)[247]: (((T)0x5E7D2C9C46CEBDllu)<<192) | (((T)0x4ECE38AD5108D414llu)<<128) | (((T)0xEBCCE91E7E525CAFllu)<<64) | ((T)0x9703982C72C29869llu), \
    char(*)[248]: (((T)0xED51CD405243DAllu)<<192) | (((T)0x222E1221D990281Bllu)<<128) | (((T)0xD682D4C68D738792llu)<<64) | ((T)0x7FD96DECC0102459llu), \
    char(*)[249]: (((T)0x418E20C3A7EBE5llu)<<192) | (((T)0x29D130C67AFEF38Ellu)<<128) | (((T)0x8574D64386853D2Allu)<<64) | ((T)0x3DC175DEEDBB100Fllu), \
    char(*)[250]: (((T)0x3432EEEDBCA6443llu)<<192) | (((T)0xB12C750F2159FB86llu)<<128) | (((T)0x7DCF623D6A607D44llu)<<64) | ((T)0xAA3343C5221D6503llu), \
    char(*)[251]: (((T)0x18CEEA778DED696llu)<<192) | (((T)0xBBF9CD754283634Cllu)<<128) | (((T)0x5A68A6BD2322B555llu)<<64) | ((T)0xF4B4D550CA1F5D73llu), \
    char(*)[252]: (((T)0x2E7A47E23A7B5A0llu)<<192) | (((T)0xBBE57EEEB437F669llu)<<128) | (((T)0x3F5FFB428A1501C5llu)<<64) | ((T)0x1313B287AD989A0Fllu), \
    char(*)[253]: (((T)0x62373C1DCE5787Fllu)<<192) | (((T)0x15B29F8C6A0E3E68llu)<<128) | (((T)0xAA952F8DC34321C7llu)<<64) | ((T)0x5C94B3CC502218A5llu), \
    char(*)[254]: (((T)0x2320DD297EB09198llu)<<192) | (((T)0x35221DF17D98AD0Bllu)<<128) | (((T)0x587774A9A976971llu)<<64) | ((T)0xCD7F24FBD7DA906Fllu), \
    char(*)[255]: (((T)0x5D1ECEF3BF600229llu)<<192) | (((T)0xC52F902A71DEBB25llu)<<128) | (((T)0xBE0BBFE4A141FB60llu)<<64) | ((T)0x3F08BED1F5985ABDllu), \
    char(*)[256]: (((T)0x222FBFEFF87B1065llu)<<192) | (((T)0x119D1C1175D9805Bllu)<<128) | (((T)0xC9B9612ECE68E63llu)<<64) | ((T)0xC98979A8819D2471llu), \
    char(*)[257]: (((T)0xA4C5ADBBBC88DD6Bllu)<<192) | (((T)0xADBF2A236A4ABC23llu)<<128) | (((T)0x838985778EE6E132llu)<<64) | ((T)0xE2C87B9F903C5D95llu), \
    char(*)[258]: (((T)0x2llu)<<256) | (((T)0xC137DC05854384BAllu)<<192) | (((T)0xFB37404823F3659Dllu)<<128) | (((T)0x8614CC11C34E44E0llu)<<64) | ((T)0xFD32DB40BC9567C1llu), \
    char(*)[259]: (((T)0x7llu)<<256) | (((T)0x632987893B37608Dllu)<<192) | (((T)0x5B3F3540B4222E2Bllu)<<128) | (((T)0x26A26618B11E89DCllu)<<64) | ((T)0xDC78B589C1222C15llu), \
    char(*)[260]: (((T)0x4llu)<<256) | (((T)0xE9622AC3B6B16A64llu)<<192) | (((T)0xABCA0A863954024Dllu)<<128) | (((T)0x458855AF52A696B3llu)<<64) | ((T)0x693BA7F0BD788881llu), \
    char(*)[261]: (((T)0x6llu)<<256) | (((T)0x51AAD47A2517A8CAllu)<<192) | (((T)0xD97112E2D1D71E83llu)<<128) | (((T)0xBC51018D0D5FEBD8llu)<<64) | ((T)0x7D7AF22143893EB5llu), \
    char(*)[262]: (((T)0x1Ellu)<<256) | (((T)0x9C3846DD13BCCB03llu)<<192) | (((T)0xA1F8ACFC25AAC05Ellu)<<128) | (((T)0xB9112BC47275DC96llu)<<64) | ((T)0xE0FA5FA951755E59llu), \
    char(*)[263]: (((T)0x75llu)<<256) | (((T)0xF61AA223D8F6C6Bllu)<<192) | (((T)0x4DEB34F127C6320Fllu)<<128) | (((T)0x8A4C594E60BA2135llu)<<64) | ((T)0xC84CB812E7B19319llu), \
    char(*)[264]: (((T)0x9Cllu)<<256) | (((T)0xD2A9EF4CC74705B8llu)<<192) | (((T)0x5B8274AFC0A20DEllu)<<128) | (((T)0xFF28B1D5F948886llu)<<64) | ((T)0xB3B8C95BF85123C9llu), \
    char(*)[265]: (((T)0x168llu)<<256) | (((T)0xD66B9B81F1827BB4llu)<<192) | (((T)0x3A3C054163899F66llu)<<128) | (((T)0x72FA7C508EC37864llu)<<64) | ((T)0xBF6AEE4AB1BB991Fllu), \
    char(*)[266]: (((T)0x187llu)<<256) | (((T)0x371085D56D8E6F5Allu)<<192) | (((T)0x49A2B970ED6A7230llu)<<128) | (((T)0xED434A5A584B7B4Dllu)<<64) | ((T)0x4AB876354B7BC071llu), \
    char(*)[267]: (((T)0x26Fllu)<<256) | (((T)0xF115EB348838AFBFllu)<<192) | (((T)0xAE5EBBFFBC3251A4llu)<<128) | (((T)0xE0CC36CDC71196A5llu)<<64) | ((T)0x3069ED0A8C80ED97llu), \
    char(*)[268]: (((T)0xDEAllu)<<256) | (((T)0x9C3A2A16D5FB53E3llu)<<192) | (((T)0xD3E1FC4D21C9546Ellu)<<128) | (((T)0x571B049DF7CA8455llu)<<64) | ((T)0xBC8B32D05A8533EFllu), \
    char(*)[269]: (((T)0x6F6llu)<<256) | (((T)0xF3425FBF3A5805BDllu)<<192) | (((T)0x645FB218CFD66917llu)<<128) | (((T)0x7AA4B5C3DBBEF957llu)<<64) | ((T)0x3567B847111EEC67llu), \
    char(*)[270]: (((T)0x71Allu)<<256) | (((T)0x667C24868A51E4C5llu)<<192) | (((T)0x5DAA500D898F068Dllu)<<128) | (((T)0xD28F6C5CD34DD11Cllu)<<64) | ((T)0x60D4E355FBB2E57Dllu), \
    char(*)[271]: (((T)0x72Ellu)<<256) | (((T)0xAC097DD76982F6D7llu)<<192) | (((T)0x677F57F788639614llu)<<128) | (((T)0x5CE29BB4D6A4678llu)<<64) | ((T)0xF68E4972D7A4232Dllu), \
    char(*)[272]: (((T)0x48C7llu)<<256) | (((T)0x420D30BE81297310llu)<<192) | (((T)0x2DC8C712B96C05FCllu)<<128) | (((T)0x95D67EAA4A741C7Dllu)<<64) | ((T)0x5DCAF8DA9611C5EBllu), \
    char(*)[273]: (((T)0x184A8llu)<<256) | (((T)0x4C00ABB8FD0205F0llu)<<192) | (((T)0xE58EA06E8CF0FA1Fllu)<<128) | (((T)0x1B25688C336799F2llu)<<64) | ((T)0x16108D43273C39A1llu), \
    char(*)[274]: (((T)0x3E5CEllu)<<256) | (((T)0x7E92AE6C4DF19CCBllu)<<192) | (((T)0x7F2C11FEC92A7014llu)<<128) | (((T)0xDF8A85C4D5E6F203llu)<<64) | ((T)0x6FE5E47502B1162Dllu), \
    char(*)[275]: (((T)0x5A777llu)<<256) | (((T)0xD1E13CACE802D9Allu)<<192) | (((T)0xFBF388384E476FA1llu)<<128) | (((T)0x6236E7ED5614E2EEllu)<<64) | ((T)0xA4ECA4CC71D456AFllu), \
    char(*)[276]: (((T)0x5AEAEllu)<<256) | (((T)0x3BBAEE40606F3E6Ellu)<<192) | (((T)0x2CF6A8D345741CF3llu)<<128) | (((T)0x629896EE2B74BC9Ellu)<<64) | ((T)0x5E522B7D0E45F18Fllu), \
    char(*)[277]: (((T)0x197163llu)<<256) | (((T)0xCC5E88C33528AF68llu)<<192) | (((T)0x4FDF366BF7BB0F3Cllu)<<128) | (((T)0x28847B6060EE3B02llu)<<64) | ((T)0xE51EE9E6F4C490CBllu), \
    char(*)[278]: (((T)0x11053llu)<<256) | (((T)0x5C61966144F1A2A0llu)<<192) | (((T)0xB835D110126A0195llu)<<128) | (((T)0x7E13917B2FDD2279llu)<<64) | ((T)0xE7928ED980C300AFllu), \
    char(*)[279]: (((T)0xEDE25llu)<<256) | (((T)0xCB784EA95D1173CDllu)<<192) | (((T)0x7F92970BA05C5CC9llu)<<128) | (((T)0x5C1EB8554DE27DB9llu)<<64) | ((T)0x76149C9663D6F949llu), \
    char(*)[280]: (((T)0x545325llu)<<256) | (((T)0x3102C2A754FCC7D8llu)<<192) | (((T)0x1A5DFAC21BEB9CEFllu)<<128) | (((T)0x4E138ACB15A6F7A5llu)<<64) | ((T)0x9C1EDCEEE59CD233llu), \
    char(*)[281]: (((T)0x1D1F5BAllu)<<256) | (((T)0xB434881B2BCC417Cllu)<<192) | (((T)0xF7C367AA698E4E96llu)<<128) | (((T)0x8B1FEA217EA92412llu)<<64) | ((T)0x59FE23D884E4B075llu), \
    char(*)[282]: (((T)0xC506C2llu)<<256) | (((T)0xF85BE8F05AFA64Ellu)<<192) | (((T)0x502A7B7823002CA6llu)<<128) | (((T)0xCF847078BB0B8829llu)<<64) | ((T)0xA0346C3B7DF4C897llu), \
    char(*)[283]: (((T)0x2AD9240llu)<<256) | (((T)0x41F022FD91B28180llu)<<192) | (((T)0x2EA3231143271D24llu)<<128) | (((T)0x31B97AEE0A20212llu)<<64) | ((T)0x75B3367F2ACFD3C9llu), \
    char(*)[284]: (((T)0xA6185D5llu)<<256) | (((T)0xECCEC4046B5E8D8Dllu)<<192) | (((T)0x30DFB5693E785297llu)<<128) | (((T)0xEF57F73FD585769Cllu)<<64) | ((T)0xCBDDF86D9338A39Dllu), \
    char(*)[285]: (((T)0x7453499llu)<<256) | (((T)0xD22C0AAD701DE140llu)<<192) | (((T)0xFC62D4911C395AC0llu)<<128) | (((T)0x8451171D12684008llu)<<64) | ((T)0xA5006DE18B7C5CDDllu), \
    char(*)[286]: (((T)0x17A8188Allu)<<256) | (((T)0xAE491E06D6782800llu)<<192) | (((T)0x320246D94769CD45llu)<<128) | (((T)0xB29F0F6809529885llu)<<64) | ((T)0xE5C2579A45E39BFllu), \
    char(*)[287]: (((T)0xC36DDD5llu)<<256) | (((T)0xE2AAEE4566DEE409llu)<<192) | (((T)0x3DE818E65459259Allu)<<128) | (((T)0xE44F23511A064F39llu)<<64) | ((T)0x63B7295F20A41309llu), \
    char(*)[288]: (((T)0xEAFB140Cllu)<<256) | (((T)0xBF2D026C8955DD5Fllu)<<192) | (((T)0xE93FA306AD495468llu)<<128) | (((T)0x5A2D392D5FFC6C06llu)<<64) | ((T)0xF31BE87ABAB9BAB7llu) \
  )

#endif
