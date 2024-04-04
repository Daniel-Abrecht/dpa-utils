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
    char(*)[8]: (T)0xfbllu, \
    char(*)[9]: (T)0x1fdllu, \
    char(*)[10]: (T)0x3f5llu, \
    char(*)[11]: (T)0x7ebllu, \
    char(*)[12]: (T)0xfd3llu, \
    char(*)[13]: (T)0x1fa5llu, \
    char(*)[14]: (T)0x3f41llu, \
    char(*)[15]: (T)0x7e9bllu, \
    char(*)[16]: ((T)0xFD2Bllu), \
    char(*)[17]: ((T)0x1FA47llu), \
    char(*)[18]: ((T)0x3F49Dllu), \
    char(*)[19]: ((T)0x7E949llu), \
    char(*)[20]: ((T)0xFD2C1llu), \
    char(*)[21]: ((T)0x1FA5AFllu), \
    char(*)[22]: ((T)0x3F4B5Bllu), \
    char(*)[23]: ((T)0x7E96A1llu), \
    char(*)[24]: ((T)0xFD2D6Fllu), \
    char(*)[25]: ((T)0x1FA5B05llu), \
    char(*)[26]: ((T)0x3F4B5F5llu), \
    char(*)[27]: ((T)0x7E96C1Fllu), \
    char(*)[28]: ((T)0xFD2D841llu), \
    char(*)[29]: ((T)0x1FA5B077llu), \
    char(*)[30]: ((T)0x3F4B60FDllu), \
    char(*)[31]: ((T)0x7E96C227llu), \
    char(*)[32]: ((T)0xFD2D84B5llu), \
    char(*)[33]: ((T)0x1FA5B0983llu), \
    char(*)[34]: ((T)0x3F4B6131Fllu), \
    char(*)[35]: ((T)0x7E96C264Dllu), \
    char(*)[36]: ((T)0xFD2D84C9Dllu), \
    char(*)[37]: ((T)0x1FA5B09929llu), \
    char(*)[38]: ((T)0x3F4B613271llu), \
    char(*)[39]: ((T)0x7E96C264F1llu), \
    char(*)[40]: ((T)0xFD2D84C9BBllu), \
    char(*)[41]: ((T)0x1FA5B0993E5llu), \
    char(*)[42]: ((T)0x3F4B61327EBllu), \
    char(*)[43]: ((T)0x7E96C264FD1llu), \
    char(*)[44]: ((T)0xFD2D84C9FFDllu), \
    char(*)[45]: ((T)0x1FA5B0993FEFllu), \
    char(*)[46]: ((T)0x3F4B61327FEDllu), \
    char(*)[47]: ((T)0x7E96C264FFFBllu), \
    char(*)[48]: ((T)0xFD2D84C9FFF3llu), \
    char(*)[49]: ((T)0x1FA5B0993FFB3llu), \
    char(*)[50]: ((T)0x3F4B61327FFF9llu), \
    char(*)[51]: ((T)0x7E96C264FFFE3llu), \
    char(*)[52]: ((T)0xFD2D84C9FFFEDllu), \
    char(*)[53]: ((T)0x1FA5B0993FFF91llu), \
    char(*)[54]: ((T)0x3F4B61327FFF8Dllu), \
    char(*)[55]: ((T)0x7E96C264FFFF85llu), \
    char(*)[56]: ((T)0xFD2D84C9FFFFAFllu), \
    char(*)[57]: ((T)0x1FA5B0993FFFFF1llu), \
    char(*)[58]: ((T)0x3F4B61327FFFFDBllu), \
    char(*)[59]: ((T)0x7E96C264FFFFFEFllu), \
    char(*)[60]: ((T)0xFD2D84C9FFFFFF1llu), \
    char(*)[61]: ((T)0x1FA5B0993FFFFFB3llu), \
    char(*)[62]: ((T)0x3F4B613280000045llu), \
    char(*)[63]: ((T)0x7E96C265000000F7llu), \
    char(*)[64]: ((T)0xFD2D84CA00000225llu), \
    char(*)[65]: (((T)0x1llu)<<64) | ((T)0xFA5B09940000041Dllu), \
    char(*)[66]: (((T)0x3llu)<<64) | ((T)0xF4B61328000008A5llu), \
    char(*)[67]: (((T)0x7llu)<<64) | ((T)0xE96C265000001177llu), \
    char(*)[68]: (((T)0xFllu)<<64) | ((T)0xD2D84CA0000022FDllu), \
    char(*)[69]: (((T)0x1Fllu)<<64) | ((T)0xA5B09940000045DFllu), \
    char(*)[70]: (((T)0x3Fllu)<<64) | ((T)0x4B61328000008BAFllu), \
    char(*)[71]: (((T)0x7Ellu)<<64) | ((T)0x96C26500000117DFllu), \
    char(*)[72]: (((T)0xFDllu)<<64) | ((T)0x2D84CA0000022FCDllu), \
    char(*)[73]: (((T)0x1FAllu)<<64) | ((T)0x5B09940000045F69llu), \
    char(*)[74]: (((T)0x3F4llu)<<64) | ((T)0xB61328000008BFB5llu), \
    char(*)[75]: (((T)0x7E9llu)<<64) | ((T)0x6C26500000117FB7llu), \
    char(*)[76]: (((T)0xFD2llu)<<64) | ((T)0xD84CA0000022FF5Bllu), \
    char(*)[77]: (((T)0x1FA5llu)<<64) | ((T)0xB09940000045FEEBllu), \
    char(*)[78]: (((T)0x3F4Bllu)<<64) | ((T)0x61328000008BFDC7llu), \
    char(*)[79]: (((T)0x7E96llu)<<64) | ((T)0xC26500000117FB41llu), \
    char(*)[80]: (((T)0xFD2Dllu)<<64) | ((T)0x84CA0000022FF6FBllu), \
    char(*)[81]: (((T)0x1FA5Bllu)<<64) | ((T)0x9940000045FEEB1llu), \
    char(*)[82]: (((T)0x3F4B6llu)<<64) | ((T)0x1328000008BFDD09llu), \
    char(*)[83]: (((T)0x7E96Cllu)<<64) | ((T)0x26500000117FBA51llu), \
    char(*)[84]: (((T)0xFD2D8llu)<<64) | ((T)0x4CA0000022FF7573llu), \
    char(*)[85]: (((T)0x1FA5B0llu)<<64) | ((T)0x9940000045FEEBC3llu), \
    char(*)[86]: (((T)0x3F4B61llu)<<64) | ((T)0x328000008BFDD815llu), \
    char(*)[87]: (((T)0x7E96C2llu)<<64) | ((T)0x6500000117FBB051llu), \
    char(*)[88]: (((T)0xFD2D84llu)<<64) | ((T)0xCA0000022FF7605Dllu), \
    char(*)[89]: (((T)0x1FA5B09llu)<<64) | ((T)0x940000045FEEC14Dllu), \
    char(*)[90]: (((T)0x3F4B613llu)<<64) | ((T)0x28000008BFDD8267llu), \
    char(*)[91]: (((T)0x7E96C26llu)<<64) | ((T)0x500000117FBB04D9llu), \
    char(*)[92]: (((T)0xFD2D84Cllu)<<64) | ((T)0xA0000022FF760A75llu), \
    char(*)[93]: (((T)0x1FA5B099llu)<<64) | ((T)0x40000045FEEC14A9llu), \
    char(*)[94]: (((T)0x3F4B6132llu)<<64) | ((T)0x8000008BFDD82A3Fllu), \
    char(*)[95]: (((T)0x7E96C265llu)<<64) | ((T)0x117FBB053CFllu), \
    char(*)[96]: (((T)0xFD2D84CAllu)<<64) | ((T)0x22FF760A8E1llu), \
    char(*)[97]: (((T)0x1FA5B0994llu)<<64) | ((T)0x45FEEC15197llu), \
    char(*)[98]: (((T)0x3F4B61328llu)<<64) | ((T)0x8BFDD82A409llu), \
    char(*)[99]: (((T)0x7E96C2650llu)<<64) | ((T)0x117FBB0547F1llu), \
    char(*)[100]: (((T)0xFD2D84CA0llu)<<64) | ((T)0x22FF760A9029llu), \
    char(*)[101]: (((T)0x1FA5B09940llu)<<64) | ((T)0x45FEEC15209Dllu), \
    char(*)[102]: (((T)0x3F4B613280llu)<<64) | ((T)0x8BFDD82A403Bllu), \
    char(*)[103]: (((T)0x7E96C26500llu)<<64) | ((T)0x117FBB0548297llu), \
    char(*)[104]: (((T)0xFD2D84CA00llu)<<64) | ((T)0x22FF760A904C7llu), \
    char(*)[105]: (((T)0x1FA5B099400llu)<<64) | ((T)0x45FEEC1520A2Dllu), \
    char(*)[106]: (((T)0x3F4B6132800llu)<<64) | ((T)0x8BFDD82A414C3llu), \
    char(*)[107]: (((T)0x7E96C265000llu)<<64) | ((T)0x117FBB05482A75llu), \
    char(*)[108]: (((T)0xFD2D84CA000llu)<<64) | ((T)0x22FF760A90555Fllu), \
    char(*)[109]: (((T)0x1FA5B0994000llu)<<64) | ((T)0x45FEEC1520AA9Dllu), \
    char(*)[110]: (((T)0x3F4B61328000llu)<<64) | ((T)0x8BFDD82A4154EFllu), \
    char(*)[111]: (((T)0x7E96C2650000llu)<<64) | ((T)0x117FBB05482ABD3llu), \
    char(*)[112]: (((T)0xFD2D84CA0000llu)<<64) | ((T)0x22FF760A90557C1llu), \
    char(*)[113]: (((T)0x1FA5B09940000llu)<<64) | ((T)0x45FEEC1520AAFBFllu), \
    char(*)[114]: (((T)0x3F4B613280000llu)<<64) | ((T)0x8BFDD82A4155EEFllu), \
    char(*)[115]: (((T)0x7E96C26500000llu)<<64) | ((T)0x117FBB05482ABEC5llu), \
    char(*)[116]: (((T)0xFD2D84CA00000llu)<<64) | ((T)0x22FF760A90557DD5llu), \
    char(*)[117]: (((T)0x1FA5B099400000llu)<<64) | ((T)0x45FEEC1520AAFB9Bllu), \
    char(*)[118]: (((T)0x3F4B6132800000llu)<<64) | ((T)0x8BFDD82A4155F64Bllu), \
    char(*)[119]: (((T)0x7E96C265000001llu)<<64) | ((T)0x17FBB05482ABEFE3llu), \
    char(*)[120]: (((T)0xFD2D84CA000002llu)<<64) | ((T)0x2FF760A90557E131llu), \
    char(*)[121]: (((T)0x1FA5B0994000004llu)<<64) | ((T)0x5FEEC1520AAFC1DBllu), \
    char(*)[122]: (((T)0x3F4B61328000008llu)<<64) | ((T)0xBFDD82A4155F847Bllu), \
    char(*)[123]: (((T)0x7E96C2650000011llu)<<64) | ((T)0x7FBB05482ABF0971llu), \
    char(*)[124]: (((T)0xFD2D84CA0000022llu)<<64) | ((T)0xFF760A90557E1345llu), \
    char(*)[125]: (((T)0x1FA5B09940000045llu)<<64) | ((T)0xFEEC1520AAFC263Fllu), \
    char(*)[126]: (((T)0x3F4B61328000008Bllu)<<64) | ((T)0xFDD82A4155F84CEBllu), \
    char(*)[127]: (((T)0x7E96C26500000117llu)<<64) | ((T)0xFBB05482ABF09A61llu), \
    char(*)[128]: (((T)0xFD2D84CA0000022Fllu)<<64) | ((T)0xF760A90557E13537llu), \
    char(*)[129]: (((T)0x1llu)<<128) | (((T)0xFA5B09940000045Fllu)<<64) | ((T)0xEEC1520AAFC26ABBllu), \
    char(*)[130]: (((T)0x3llu)<<128) | (((T)0xF4B61328000008BFllu)<<64) | ((T)0xDD82A4155F84D587llu), \
    char(*)[131]: (((T)0x7llu)<<128) | (((T)0xE96C26500000117Fllu)<<64) | ((T)0xBB05482ABF09AA2Dllu), \
    char(*)[132]: (((T)0xFllu)<<128) | (((T)0xD2D84CA0000022FFllu)<<64) | ((T)0x760A90557E1355D1llu), \
    char(*)[133]: (((T)0x1Fllu)<<128) | (((T)0xA5B09940000045FEllu)<<64) | ((T)0xEC1520AAFC26ACA3llu), \
    char(*)[134]: (((T)0x3Fllu)<<128) | (((T)0x4B61328000008BFDllu)<<64) | ((T)0xD82A4155F84D5969llu), \
    char(*)[135]: (((T)0x7Ellu)<<128) | (((T)0x96C26500000117FBllu)<<64) | ((T)0xB05482ABF09AB31Fllu), \
    char(*)[136]: (((T)0xFDllu)<<128) | (((T)0x2D84CA0000022FF7llu)<<64) | ((T)0x60A90557E135661Fllu), \
    char(*)[137]: (((T)0x1FAllu)<<128) | (((T)0x5B09940000045FEEllu)<<64) | ((T)0xC1520AAFC26ACCD3llu), \
    char(*)[138]: (((T)0x3F4llu)<<128) | (((T)0xB61328000008BFDDllu)<<64) | ((T)0x82A4155F84D59A39llu), \
    char(*)[139]: (((T)0x7E9llu)<<128) | (((T)0x6C26500000117FBBllu)<<64) | ((T)0x5482ABF09AB3439llu), \
    char(*)[140]: (((T)0xFD2llu)<<128) | (((T)0xD84CA0000022FF76llu)<<64) | ((T)0xA90557E13566913llu), \
    char(*)[141]: (((T)0x1FA5llu)<<128) | (((T)0xB09940000045FEECllu)<<64) | ((T)0x1520AAFC26ACD1DDllu), \
    char(*)[142]: (((T)0x3F4Bllu)<<128) | (((T)0x61328000008BFDD8llu)<<64) | ((T)0x2A4155F84D59A443llu), \
    char(*)[143]: (((T)0x7E96llu)<<128) | (((T)0xC26500000117FBB0llu)<<64) | ((T)0x5482ABF09AB348C7llu), \
    char(*)[144]: (((T)0xFD2Dllu)<<128) | (((T)0x84CA0000022FF760llu)<<64) | ((T)0xA90557E13566904Fllu), \
    char(*)[145]: (((T)0x1FA5Bllu)<<128) | (((T)0x9940000045FEEC1llu)<<64) | ((T)0x520AAFC26ACD232Fllu), \
    char(*)[146]: (((T)0x3F4B6llu)<<128) | (((T)0x1328000008BFDD82llu)<<64) | ((T)0xA4155F84D59A46F1llu), \
    char(*)[147]: (((T)0x7E96Cllu)<<128) | (((T)0x26500000117FBB05llu)<<64) | ((T)0x482ABF09AB348DC9llu), \
    char(*)[148]: (((T)0xFD2D8llu)<<128) | (((T)0x4CA0000022FF760Allu)<<64) | ((T)0x90557E1356691AF9llu), \
    char(*)[149]: (((T)0x1FA5B0llu)<<128) | (((T)0x9940000045FEEC15llu)<<64) | ((T)0x20AAFC26ACD237F3llu), \
    char(*)[150]: (((T)0x3F4B61llu)<<128) | (((T)0x328000008BFDD82Allu)<<64) | ((T)0x4155F84D59A47033llu), \
    char(*)[151]: (((T)0x7E96C2llu)<<128) | (((T)0x6500000117FBB054llu)<<64) | ((T)0x82ABF09AB348E1FBllu), \
    char(*)[152]: (((T)0xFD2D84llu)<<128) | (((T)0xCA0000022FF760A9llu)<<64) | ((T)0x557E1356691C309llu), \
    char(*)[153]: (((T)0x1FA5B09llu)<<128) | (((T)0x940000045FEEC152llu)<<64) | ((T)0xAAFC26ACD2387AFllu), \
    char(*)[154]: (((T)0x3F4B613llu)<<128) | (((T)0x28000008BFDD82A4llu)<<64) | ((T)0x155F84D59A470F99llu), \
    char(*)[155]: (((T)0x7E96C26llu)<<128) | (((T)0x500000117FBB0548llu)<<64) | ((T)0x2ABF09AB348E1F2Fllu), \
    char(*)[156]: (((T)0xFD2D84Cllu)<<128) | (((T)0xA0000022FF760A90llu)<<64) | ((T)0x557E1356691C401Bllu), \
    char(*)[157]: (((T)0x1FA5B099llu)<<128) | (((T)0x40000045FEEC1520llu)<<64) | ((T)0xAAFC26ACD2388075llu), \
    char(*)[158]: (((T)0x3F4B6132llu)<<128) | (((T)0x8000008BFDD82A41llu)<<64) | ((T)0x55F84D59A4710089llu), \
    char(*)[159]: (((T)0x7E96C265llu)<<128) | (((T)0x117FBB05482llu)<<64) | ((T)0xABF09AB348E2025Bllu), \
    char(*)[160]: (((T)0xFD2D84CAllu)<<128) | (((T)0x22FF760A905llu)<<64) | ((T)0x57E1356691C40645llu), \
    char(*)[161]: (((T)0x1FA5B0994llu)<<128) | (((T)0x45FEEC1520Allu)<<64) | ((T)0xAFC26ACD23880C31llu), \
    char(*)[162]: (((T)0x3F4B61328llu)<<128) | (((T)0x8BFDD82A415llu)<<64) | ((T)0x5F84D59A47101937llu), \
    char(*)[163]: (((T)0x7E96C2650llu)<<128) | (((T)0x117FBB05482Allu)<<64) | ((T)0xBF09AB348E2031C3llu), \
    char(*)[164]: (((T)0xFD2D84CA0llu)<<128) | (((T)0x22FF760A9055llu)<<64) | ((T)0x7E1356691C4064D7llu), \
    char(*)[165]: (((T)0x1FA5B09940llu)<<128) | (((T)0x45FEEC1520AAllu)<<64) | ((T)0xFC26ACD23880CA95llu), \
    char(*)[166]: (((T)0x3F4B613280llu)<<128) | (((T)0x8BFDD82A4155llu)<<64) | ((T)0xF84D59A471019539llu), \
    char(*)[167]: (((T)0x7E96C26500llu)<<128) | (((T)0x117FBB05482ABllu)<<64) | ((T)0xF09AB348E2032B2Dllu), \
    char(*)[168]: (((T)0xFD2D84CA00llu)<<128) | (((T)0x22FF760A90557llu)<<64) | ((T)0xE1356691C4065649llu), \
    char(*)[169]: (((T)0x1FA5B099400llu)<<128) | (((T)0x45FEEC1520AAFllu)<<64) | ((T)0xC26ACD23880CACA5llu), \
    char(*)[170]: (((T)0x3F4B6132800llu)<<128) | (((T)0x8BFDD82A4155Fllu)<<64) | ((T)0x84D59A4710195A91llu), \
    char(*)[171]: (((T)0x7E96C265000llu)<<128) | (((T)0x117FBB05482ABFllu)<<64) | ((T)0x9AB348E2032B395llu), \
    char(*)[172]: (((T)0xFD2D84CA000llu)<<128) | (((T)0x22FF760A90557Ellu)<<64) | ((T)0x1356691C40656A3Fllu), \
    char(*)[173]: (((T)0x1FA5B0994000llu)<<128) | (((T)0x45FEEC1520AAFCllu)<<64) | ((T)0x26ACD23880CAD461llu), \
    char(*)[174]: (((T)0x3F4B61328000llu)<<128) | (((T)0x8BFDD82A4155F8llu)<<64) | ((T)0x4D59A4710195A953llu), \
    char(*)[175]: (((T)0x7E96C2650000llu)<<128) | (((T)0x117FBB05482ABF0llu)<<64) | ((T)0x9AB348E2032B533Dllu), \
    char(*)[176]: (((T)0xFD2D84CA0000llu)<<128) | (((T)0x22FF760A90557E1llu)<<64) | ((T)0x356691C40656A31Bllu), \
    char(*)[177]: (((T)0x1FA5B09940000llu)<<128) | (((T)0x45FEEC1520AAFC2llu)<<64) | ((T)0x6ACD23880CAD4C97llu), \
    char(*)[178]: (((T)0x3F4B613280000llu)<<128) | (((T)0x8BFDD82A4155F84llu)<<64) | ((T)0xD59A4710195A9919llu), \
    char(*)[179]: (((T)0x7E96C26500000llu)<<128) | (((T)0x117FBB05482ABF09llu)<<64) | ((T)0xAB348E2032B533B7llu), \
    char(*)[180]: (((T)0xFD2D84CA00000llu)<<128) | (((T)0x22FF760A90557E13llu)<<64) | ((T)0x56691C40656A67EBllu), \
    char(*)[181]: (((T)0x1FA5B099400000llu)<<128) | (((T)0x45FEEC1520AAFC26llu)<<64) | ((T)0xACD23880CAD4CF9Fllu), \
    char(*)[182]: (((T)0x3F4B6132800000llu)<<128) | (((T)0x8BFDD82A4155F84Dllu)<<64) | ((T)0x59A4710195A99EBFllu), \
    char(*)[183]: (((T)0x7E96C265000001llu)<<128) | (((T)0x17FBB05482ABF09Allu)<<64) | ((T)0xB348E2032B533F21llu), \
    char(*)[184]: (((T)0xFD2D84CA000002llu)<<128) | (((T)0x2FF760A90557E135llu)<<64) | ((T)0x6691C40656A67F0Dllu), \
    char(*)[185]: (((T)0x1FA5B0994000004llu)<<128) | (((T)0x5FEEC1520AAFC26Allu)<<64) | ((T)0xCD23880CAD4CFE7Dllu), \
    char(*)[186]: (((T)0x3F4B61328000008llu)<<128) | (((T)0xBFDD82A4155F84D5llu)<<64) | ((T)0x9A4710195A99FD33llu), \
    char(*)[187]: (((T)0x7E96C2650000011llu)<<128) | (((T)0x7FBB05482ABF09ABllu)<<64) | ((T)0x348E2032B533F931llu), \
    char(*)[188]: (((T)0xFD2D84CA0000022llu)<<128) | (((T)0xFF760A90557E1356llu)<<64) | ((T)0x691C40656A67F49Fllu), \
    char(*)[189]: (((T)0x1FA5B09940000045llu)<<128) | (((T)0xFEEC1520AAFC26ACllu)<<64) | ((T)0xD23880CAD4CFE8D1llu), \
    char(*)[190]: (((T)0x3F4B61328000008Bllu)<<128) | (((T)0xFDD82A4155F84D59llu)<<64) | ((T)0xA4710195A99FD345llu), \
    char(*)[191]: (((T)0x7E96C26500000117llu)<<128) | (((T)0xFBB05482ABF09AB3llu)<<64) | ((T)0x48E2032B533FA4FDllu), \
    char(*)[192]: (((T)0xFD2D84CA0000022Fllu)<<128) | (((T)0xF760A90557E13566llu)<<64) | ((T)0x91C40656A67F4D99llu), \
    char(*)[193]: (((T)0x1llu)<<192) | (((T)0xFA5B09940000045Fllu)<<128) | (((T)0xEEC1520AAFC26ACDllu)<<64) | ((T)0x23880CAD4CFE9B4Dllu), \
    char(*)[194]: (((T)0x3llu)<<192) | (((T)0xF4B61328000008BFllu)<<128) | (((T)0xDD82A4155F84D59Allu)<<64) | ((T)0x4710195A99FD35E9llu), \
    char(*)[195]: (((T)0x7llu)<<192) | (((T)0xE96C26500000117Fllu)<<128) | (((T)0xBB05482ABF09AB34llu)<<64) | ((T)0x8E2032B533FA6C77llu), \
    char(*)[196]: (((T)0xFllu)<<192) | (((T)0xD2D84CA0000022FFllu)<<128) | (((T)0x760A90557E135669llu)<<64) | ((T)0x1C40656A67F4DB13llu), \
    char(*)[197]: (((T)0x1Fllu)<<192) | (((T)0xA5B09940000045FEllu)<<128) | (((T)0xEC1520AAFC26ACD2llu)<<64) | ((T)0x3880CAD4CFE9B537llu), \
    char(*)[198]: (((T)0x3Fllu)<<192) | (((T)0x4B61328000008BFDllu)<<128) | (((T)0xD82A4155F84D59A4llu)<<64) | ((T)0x710195A99FD36C8Dllu), \
    char(*)[199]: (((T)0x7Ellu)<<192) | (((T)0x96C26500000117FBllu)<<128) | (((T)0xB05482ABF09AB348llu)<<64) | ((T)0xE2032B533FA6D85Fllu), \
    char(*)[200]: (((T)0xFDllu)<<192) | (((T)0x2D84CA0000022FF7llu)<<128) | (((T)0x60A90557E1356691llu)<<64) | ((T)0xC40656A67F4DB2BFllu), \
    char(*)[201]: (((T)0x1FAllu)<<192) | (((T)0x5B09940000045FEEllu)<<128) | (((T)0xC1520AAFC26ACD23llu)<<64) | ((T)0x880CAD4CFE9B6423llu), \
    char(*)[202]: (((T)0x3F4llu)<<192) | (((T)0xB61328000008BFDDllu)<<128) | (((T)0x82A4155F84D59A47llu)<<64) | ((T)0x10195A99FD36CB3Bllu), \
    char(*)[203]: (((T)0x7E9llu)<<192) | (((T)0x6C26500000117FBBllu)<<128) | (((T)0x5482ABF09AB348Ellu)<<64) | ((T)0x2032B533FA6D97B7llu), \
    char(*)[204]: (((T)0xFD2llu)<<192) | (((T)0xD84CA0000022FF76llu)<<128) | (((T)0xA90557E1356691Cllu)<<64) | ((T)0x40656A67F4DB2F43llu), \
    char(*)[205]: (((T)0x1FA5llu)<<192) | (((T)0xB09940000045FEECllu)<<128) | (((T)0x1520AAFC26ACD238llu)<<64) | ((T)0x80CAD4CFE9B65EEFllu), \
    char(*)[206]: (((T)0x3F4Bllu)<<192) | (((T)0x61328000008BFDD8llu)<<128) | (((T)0x2A4155F84D59A471llu)<<64) | ((T)0x195A99FD36CBE0Bllu), \
    char(*)[207]: (((T)0x7E96llu)<<192) | (((T)0xC26500000117FBB0llu)<<128) | (((T)0x5482ABF09AB348E2llu)<<64) | ((T)0x32B533FA6D97CCDllu), \
    char(*)[208]: (((T)0xFD2Dllu)<<192) | (((T)0x84CA0000022FF760llu)<<128) | (((T)0xA90557E1356691C4llu)<<64) | ((T)0x656A67F4DB2F95Bllu), \
    char(*)[209]: (((T)0x1FA5Bllu)<<192) | (((T)0x9940000045FEEC1llu)<<128) | (((T)0x520AAFC26ACD2388llu)<<64) | ((T)0xCAD4CFE9B65F30Dllu), \
    char(*)[210]: (((T)0x3F4B6llu)<<192) | (((T)0x1328000008BFDD82llu)<<128) | (((T)0xA4155F84D59A4710llu)<<64) | ((T)0x195A99FD36CBE6C3llu), \
    char(*)[211]: (((T)0x7E96Cllu)<<192) | (((T)0x26500000117FBB05llu)<<128) | (((T)0x482ABF09AB348E20llu)<<64) | ((T)0x32B533FA6D97CB31llu), \
    char(*)[212]: (((T)0xFD2D8llu)<<192) | (((T)0x4CA0000022FF760Allu)<<128) | (((T)0x90557E1356691C40llu)<<64) | ((T)0x656A67F4DB2F9BD5llu), \
    char(*)[213]: (((T)0x1FA5B0llu)<<192) | (((T)0x9940000045FEEC15llu)<<128) | (((T)0x20AAFC26ACD23880llu)<<64) | ((T)0xCAD4CFE9B65F37DBllu), \
    char(*)[214]: (((T)0x3F4B61llu)<<192) | (((T)0x328000008BFDD82Allu)<<128) | (((T)0x4155F84D59A47101llu)<<64) | ((T)0x95A99FD36CBE6F47llu), \
    char(*)[215]: (((T)0x7E96C2llu)<<192) | (((T)0x6500000117FBB054llu)<<128) | (((T)0x82ABF09AB348E203llu)<<64) | ((T)0x2B533FA6D97CDFA7llu), \
    char(*)[216]: (((T)0xFD2D84llu)<<192) | (((T)0xCA0000022FF760A9llu)<<128) | (((T)0x557E1356691C406llu)<<64) | ((T)0x56A67F4DB2F9C0A1llu), \
    char(*)[217]: (((T)0x1FA5B09llu)<<192) | (((T)0x940000045FEEC152llu)<<128) | (((T)0xAAFC26ACD23880Cllu)<<64) | ((T)0xAD4CFE9B65F381A3llu), \
    char(*)[218]: (((T)0x3F4B613llu)<<192) | (((T)0x28000008BFDD82A4llu)<<128) | (((T)0x155F84D59A471019llu)<<64) | ((T)0x5A99FD36CBE7043Dllu), \
    char(*)[219]: (((T)0x7E96C26llu)<<192) | (((T)0x500000117FBB0548llu)<<128) | (((T)0x2ABF09AB348E2032llu)<<64) | ((T)0xB533FA6D97CE098Bllu), \
    char(*)[220]: (((T)0xFD2D84Cllu)<<192) | (((T)0xA0000022FF760A90llu)<<128) | (((T)0x557E1356691C4065llu)<<64) | ((T)0x6A67F4DB2F9C1333llu), \
    char(*)[221]: (((T)0x1FA5B099llu)<<192) | (((T)0x40000045FEEC1520llu)<<128) | (((T)0xAAFC26ACD23880CAllu)<<64) | ((T)0xD4CFE9B65F3826E1llu), \
    char(*)[222]: (((T)0x3F4B6132llu)<<192) | (((T)0x8000008BFDD82A41llu)<<128) | (((T)0x55F84D59A4710195llu)<<64) | ((T)0xA99FD36CBE704DA1llu), \
    char(*)[223]: (((T)0x7E96C265llu)<<192) | (((T)0x117FBB05482llu)<<128) | (((T)0xABF09AB348E2032Bllu)<<64) | ((T)0x533FA6D97CE09AF1llu), \
    char(*)[224]: (((T)0xFD2D84CAllu)<<192) | (((T)0x22FF760A905llu)<<128) | (((T)0x57E1356691C40656llu)<<64) | ((T)0xA67F4DB2F9C13769llu), \
    char(*)[225]: (((T)0x1FA5B0994llu)<<192) | (((T)0x45FEEC1520Allu)<<128) | (((T)0xAFC26ACD23880CADllu)<<64) | ((T)0x4CFE9B65F3826E8Dllu), \
    char(*)[226]: (((T)0x3F4B61328llu)<<192) | (((T)0x8BFDD82A415llu)<<128) | (((T)0x5F84D59A4710195Allu)<<64) | ((T)0x99FD36CBE704DB15llu), \
    char(*)[227]: (((T)0x7E96C2650llu)<<192) | (((T)0x117FBB05482Allu)<<128) | (((T)0xBF09AB348E2032B5llu)<<64) | ((T)0x33FA6D97CE09BBE5llu), \
    char(*)[228]: (((T)0xFD2D84CA0llu)<<192) | (((T)0x22FF760A9055llu)<<128) | (((T)0x7E1356691C40656Allu)<<64) | ((T)0x67F4DB2F9C137797llu), \
    char(*)[229]: (((T)0x1FA5B09940llu)<<192) | (((T)0x45FEEC1520AAllu)<<128) | (((T)0xFC26ACD23880CAD4llu)<<64) | ((T)0xCFE9B65F3826EF93llu), \
    char(*)[230]: (((T)0x3F4B613280llu)<<192) | (((T)0x8BFDD82A4155llu)<<128) | (((T)0xF84D59A4710195A9llu)<<64) | ((T)0x9FD36CBE704DDDEDllu), \
    char(*)[231]: (((T)0x7E96C26500llu)<<192) | (((T)0x117FBB05482ABllu)<<128) | (((T)0xF09AB348E2032B53llu)<<64) | ((T)0x3FA6D97CE09BBD65llu), \
    char(*)[232]: (((T)0xFD2D84CA00llu)<<192) | (((T)0x22FF760A90557llu)<<128) | (((T)0xE1356691C40656A6llu)<<64) | ((T)0x7F4DB2F9C1377B93llu), \
    char(*)[233]: (((T)0x1FA5B099400llu)<<192) | (((T)0x45FEEC1520AAFllu)<<128) | (((T)0xC26ACD23880CAD4Cllu)<<64) | ((T)0xFE9B65F3826EF975llu), \
    char(*)[234]: (((T)0x3F4B6132800llu)<<192) | (((T)0x8BFDD82A4155Fllu)<<128) | (((T)0x84D59A4710195A99llu)<<64) | ((T)0xFD36CBE704DDF35Fllu), \
    char(*)[235]: (((T)0x7E96C265000llu)<<192) | (((T)0x117FBB05482ABFllu)<<128) | (((T)0x9AB348E2032B533llu)<<64) | ((T)0xFA6D97CE09BBE713llu), \
    char(*)[236]: (((T)0xFD2D84CA000llu)<<192) | (((T)0x22FF760A90557Ellu)<<128) | (((T)0x1356691C40656A67llu)<<64) | ((T)0xF4DB2F9C1377CF01llu), \
    char(*)[237]: (((T)0x1FA5B0994000llu)<<192) | (((T)0x45FEEC1520AAFCllu)<<128) | (((T)0x26ACD23880CAD4CFllu)<<64) | ((T)0xE9B65F3826EF9D45llu), \
    char(*)[238]: (((T)0x3F4B61328000llu)<<192) | (((T)0x8BFDD82A4155F8llu)<<128) | (((T)0x4D59A4710195A99Fllu)<<64) | ((T)0xD36CBE704DDF3C73llu), \
    char(*)[239]: (((T)0x7E96C2650000llu)<<192) | (((T)0x117FBB05482ABF0llu)<<128) | (((T)0x9AB348E2032B533Fllu)<<64) | ((T)0xA6D97CE09BBE78CDllu), \
    char(*)[240]: (((T)0xFD2D84CA0000llu)<<192) | (((T)0x22FF760A90557E1llu)<<128) | (((T)0x356691C40656A67Fllu)<<64) | ((T)0x4DB2F9C1377CF16Fllu), \
    char(*)[241]: (((T)0x1FA5B09940000llu)<<192) | (((T)0x45FEEC1520AAFC2llu)<<128) | (((T)0x6ACD23880CAD4CFEllu)<<64) | ((T)0x9B65F3826EF9E3A7llu), \
    char(*)[242]: (((T)0x3F4B613280000llu)<<192) | (((T)0x8BFDD82A4155F84llu)<<128) | (((T)0xD59A4710195A99FDllu)<<64) | ((T)0x36CBE704DDF3C785llu), \
    char(*)[243]: (((T)0x7E96C26500000llu)<<192) | (((T)0x117FBB05482ABF09llu)<<128) | (((T)0xAB348E2032B533FAllu)<<64) | ((T)0x6D97CE09BBE78F47llu), \
    char(*)[244]: (((T)0xFD2D84CA00000llu)<<192) | (((T)0x22FF760A90557E13llu)<<128) | (((T)0x56691C40656A67F4llu)<<64) | ((T)0xDB2F9C1377CF1E07llu), \
    char(*)[245]: (((T)0x1FA5B099400000llu)<<192) | (((T)0x45FEEC1520AAFC26llu)<<128) | (((T)0xACD23880CAD4CFE9llu)<<64) | ((T)0xB65F3826EF9E3D01llu), \
    char(*)[246]: (((T)0x3F4B6132800000llu)<<192) | (((T)0x8BFDD82A4155F84Dllu)<<128) | (((T)0x59A4710195A99FD3llu)<<64) | ((T)0x6CBE704DDF3C7B73llu), \
    char(*)[247]: (((T)0x7E96C265000001llu)<<192) | (((T)0x17FBB05482ABF09Allu)<<128) | (((T)0xB348E2032B533FA6llu)<<64) | ((T)0xD97CE09BBE78F69Dllu), \
    char(*)[248]: (((T)0xFD2D84CA000002llu)<<192) | (((T)0x2FF760A90557E135llu)<<128) | (((T)0x6691C40656A67F4Dllu)<<64) | ((T)0xB2F9C1377CF1ED79llu), \
    char(*)[249]: (((T)0x1FA5B0994000004llu)<<192) | (((T)0x5FEEC1520AAFC26Allu)<<128) | (((T)0xCD23880CAD4CFE9Bllu)<<64) | ((T)0x65F3826EF9E3DAADllu), \
    char(*)[250]: (((T)0x3F4B61328000008llu)<<192) | (((T)0xBFDD82A4155F84D5llu)<<128) | (((T)0x9A4710195A99FD36llu)<<64) | ((T)0xCBE704DDF3C7B797llu), \
    char(*)[251]: (((T)0x7E96C2650000011llu)<<192) | (((T)0x7FBB05482ABF09ABllu)<<128) | (((T)0x348E2032B533FA6Dllu)<<64) | ((T)0x97CE09BBE78F6C17llu), \
    char(*)[252]: (((T)0xFD2D84CA0000022llu)<<192) | (((T)0xFF760A90557E1356llu)<<128) | (((T)0x691C40656A67F4DBllu)<<64) | ((T)0x2F9C1377CF1EDE17llu), \
    char(*)[253]: (((T)0x1FA5B09940000045llu)<<192) | (((T)0xFEEC1520AAFC26ACllu)<<128) | (((T)0xD23880CAD4CFE9B6llu)<<64) | ((T)0x5F3826EF9E3DBC0Bllu), \
    char(*)[254]: (((T)0x3F4B61328000008Bllu)<<192) | (((T)0xFDD82A4155F84D59llu)<<128) | (((T)0xA4710195A99FD36Cllu)<<64) | ((T)0xBE704DDF3C7B7997llu), \
    char(*)[255]: (((T)0x7E96C26500000117llu)<<192) | (((T)0xFBB05482ABF09AB3llu)<<128) | (((T)0x48E2032B533FA6D9llu)<<64) | ((T)0x7CE09BBE78F6F425llu), \
    char(*)[256]: (((T)0xFD2D84CA0000022Fllu)<<192) | (((T)0xF760A90557E13566llu)<<128) | (((T)0x91C40656A67F4DB2llu)<<64) | ((T)0xF9C1377CF1EDE5E3llu), \
    char(*)[257]: (((T)0x1llu)<<256) | (((T)0xFA5B09940000045Fllu)<<192) | (((T)0xEEC1520AAFC26ACDllu)<<128) | (((T)0x23880CAD4CFE9B65llu)<<64) | ((T)0xF3826EF9E3DBCFE5llu), \
    char(*)[258]: (((T)0x3llu)<<256) | (((T)0xF4B61328000008BFllu)<<192) | (((T)0xDD82A4155F84D59Allu)<<128) | (((T)0x4710195A99FD36CBllu)<<64) | ((T)0xE704DDF3C7B7A131llu), \
    char(*)[259]: (((T)0x7llu)<<256) | (((T)0xE96C26500000117Fllu)<<192) | (((T)0xBB05482ABF09AB34llu)<<128) | (((T)0x8E2032B533FA6D97llu)<<64) | ((T)0xCE09BBE78F6F4241llu), \
    char(*)[260]: (((T)0xFllu)<<256) | (((T)0xD2D84CA0000022FFllu)<<192) | (((T)0x760A90557E135669llu)<<128) | (((T)0x1C40656A67F4DB2Fllu)<<64) | ((T)0x9C1377CF1EDE84ADllu), \
    char(*)[261]: (((T)0x1Fllu)<<256) | (((T)0xA5B09940000045FEllu)<<192) | (((T)0xEC1520AAFC26ACD2llu)<<128) | (((T)0x3880CAD4CFE9B65Fllu)<<64) | ((T)0x3826EF9E3DBD0A1Dllu), \
    char(*)[262]: (((T)0x3Fllu)<<256) | (((T)0x4B61328000008BFDllu)<<192) | (((T)0xD82A4155F84D59A4llu)<<128) | (((T)0x710195A99FD36CBEllu)<<64) | ((T)0x704DDF3C7B7A1391llu), \
    char(*)[263]: (((T)0x7Ellu)<<256) | (((T)0x96C26500000117FBllu)<<192) | (((T)0xB05482ABF09AB348llu)<<128) | (((T)0xE2032B533FA6D97Cllu)<<64) | ((T)0xE09BBE78F6F428FFllu), \
    char(*)[264]: (((T)0xFDllu)<<256) | (((T)0x2D84CA0000022FF7llu)<<192) | (((T)0x60A90557E1356691llu)<<128) | (((T)0xC40656A67F4DB2F9llu)<<64) | ((T)0xC1377CF1EDE8534Fllu), \
    char(*)[265]: (((T)0x1FAllu)<<256) | (((T)0x5B09940000045FEEllu)<<192) | (((T)0xC1520AAFC26ACD23llu)<<128) | (((T)0x880CAD4CFE9B65F3llu)<<64) | ((T)0x826EF9E3DBD0A65Dllu), \
    char(*)[266]: (((T)0x3F4llu)<<256) | (((T)0xB61328000008BFDDllu)<<192) | (((T)0x82A4155F84D59A47llu)<<128) | (((T)0x10195A99FD36CBE7llu)<<64) | ((T)0x4DDF3C7B7A14D35llu), \
    char(*)[267]: (((T)0x7E9llu)<<256) | (((T)0x6C26500000117FBBllu)<<192) | (((T)0x5482ABF09AB348Ellu)<<128) | (((T)0x2032B533FA6D97CEllu)<<64) | ((T)0x9BBE78F6F429A45llu), \
    char(*)[268]: (((T)0xFD2llu)<<256) | (((T)0xD84CA0000022FF76llu)<<192) | (((T)0xA90557E1356691Cllu)<<128) | (((T)0x40656A67F4DB2F9Cllu)<<64) | ((T)0x1377CF1EDE853595llu), \
    char(*)[269]: (((T)0x1FA5llu)<<256) | (((T)0xB09940000045FEECllu)<<192) | (((T)0x1520AAFC26ACD238llu)<<128) | (((T)0x80CAD4CFE9B65F38llu)<<64) | ((T)0x26EF9E3DBD0A6BDFllu), \
    char(*)[270]: (((T)0x3F4Bllu)<<256) | (((T)0x61328000008BFDD8llu)<<192) | (((T)0x2A4155F84D59A471llu)<<128) | (((T)0x195A99FD36CBE70llu)<<64) | ((T)0x4DDF3C7B7A14D81Bllu), \
    char(*)[271]: (((T)0x7E96llu)<<256) | (((T)0xC26500000117FBB0llu)<<192) | (((T)0x5482ABF09AB348E2llu)<<128) | (((T)0x32B533FA6D97CE0llu)<<64) | ((T)0x9BBE78F6F429AFB5llu), \
    char(*)[272]: (((T)0xFD2Dllu)<<256) | (((T)0x84CA0000022FF760llu)<<192) | (((T)0xA90557E1356691C4llu)<<128) | (((T)0x656A67F4DB2F9C1llu)<<64) | ((T)0x377CF1EDE8535F8Bllu), \
    char(*)[273]: (((T)0x1FA5Bllu)<<256) | (((T)0x9940000045FEEC1llu)<<192) | (((T)0x520AAFC26ACD2388llu)<<128) | (((T)0xCAD4CFE9B65F382llu)<<64) | ((T)0x6EF9E3DBD0A6C0B3llu), \
    char(*)[274]: (((T)0x3F4B6llu)<<256) | (((T)0x1328000008BFDD82llu)<<192) | (((T)0xA4155F84D59A4710llu)<<128) | (((T)0x195A99FD36CBE704llu)<<64) | ((T)0xDDF3C7B7A14D81C9llu), \
    char(*)[275]: (((T)0x7E96Cllu)<<256) | (((T)0x26500000117FBB05llu)<<192) | (((T)0x482ABF09AB348E20llu)<<128) | (((T)0x32B533FA6D97CE09llu)<<64) | ((T)0xBBE78F6F429B03C3llu), \
    char(*)[276]: (((T)0xFD2D8llu)<<256) | (((T)0x4CA0000022FF760Allu)<<192) | (((T)0x90557E1356691C40llu)<<128) | (((T)0x656A67F4DB2F9C13llu)<<64) | ((T)0x77CF1EDE8536077Dllu), \
    char(*)[277]: (((T)0x1FA5B0llu)<<256) | (((T)0x9940000045FEEC15llu)<<192) | (((T)0x20AAFC26ACD23880llu)<<128) | (((T)0xCAD4CFE9B65F3826llu)<<64) | ((T)0xEF9E3DBD0A6C0EA3llu), \
    char(*)[278]: (((T)0x3F4B61llu)<<256) | (((T)0x328000008BFDD82Allu)<<192) | (((T)0x4155F84D59A47101llu)<<128) | (((T)0x95A99FD36CBE704Dllu)<<64) | ((T)0xDF3C7B7A14D81DF5llu), \
    char(*)[279]: (((T)0x7E96C2llu)<<256) | (((T)0x6500000117FBB054llu)<<192) | (((T)0x82ABF09AB348E203llu)<<128) | (((T)0x2B533FA6D97CE09Bllu)<<64) | ((T)0xBE78F6F429B03C65llu), \
    char(*)[280]: (((T)0xFD2D84llu)<<256) | (((T)0xCA0000022FF760A9llu)<<192) | (((T)0x557E1356691C406llu)<<128) | (((T)0x56A67F4DB2F9C137llu)<<64) | ((T)0x7CF1EDE853607923llu), \
    char(*)[281]: (((T)0x1FA5B09llu)<<256) | (((T)0x940000045FEEC152llu)<<192) | (((T)0xAAFC26ACD23880Cllu)<<128) | (((T)0xAD4CFE9B65F3826Ellu)<<64) | ((T)0xF9E3DBD0A6C0F23Fllu), \
    char(*)[282]: (((T)0x3F4B613llu)<<256) | (((T)0x28000008BFDD82A4llu)<<192) | (((T)0x155F84D59A471019llu)<<128) | (((T)0x5A99FD36CBE704DDllu)<<64) | ((T)0xF3C7B7A14D81E4A1llu), \
    char(*)[283]: (((T)0x7E96C26llu)<<256) | (((T)0x500000117FBB0548llu)<<192) | (((T)0x2ABF09AB348E2032llu)<<128) | (((T)0xB533FA6D97CE09BBllu)<<64) | ((T)0xE78F6F429B03CA79llu), \
    char(*)[284]: (((T)0xFD2D84Cllu)<<256) | (((T)0xA0000022FF760A90llu)<<192) | (((T)0x557E1356691C4065llu)<<128) | (((T)0x6A67F4DB2F9C1377llu)<<64) | ((T)0xCF1EDE85360794CDllu), \
    char(*)[285]: (((T)0x1FA5B099llu)<<256) | (((T)0x40000045FEEC1520llu)<<192) | (((T)0xAAFC26ACD23880CAllu)<<128) | (((T)0xD4CFE9B65F3826EFllu)<<64) | ((T)0x9E3DBD0A6C0F286Dllu), \
    char(*)[286]: (((T)0x3F4B6132llu)<<256) | (((T)0x8000008BFDD82A41llu)<<192) | (((T)0x55F84D59A4710195llu)<<128) | (((T)0xA99FD36CBE704DDFllu)<<64) | ((T)0x3C7B7A14D81E557Bllu), \
    char(*)[287]: (((T)0x7E96C265llu)<<256) | (((T)0x117FBB05482llu)<<192) | (((T)0xABF09AB348E2032Bllu)<<128) | (((T)0x533FA6D97CE09BBEllu)<<64) | ((T)0x78F6F429B03CAA81llu), \
    char(*)[288]: (((T)0xFD2D84CAllu)<<256) | (((T)0x22FF760A905llu)<<192) | (((T)0x57E1356691C40656llu)<<128) | (((T)0xA67F4DB2F9C1377Cllu)<<64) | ((T)0xF1EDE85360795681llu) \
  )

#define dpa__u_choose_prime_inverse(T) _Generic((char(*)[dpa__u_bitwidth((T){0})]){0}, \
    char(*)[1]: (T)0x1llu, \
    char(*)[2]: (T)0x3llu, \
    char(*)[3]: (T)0x5llu, \
    char(*)[4]: (T)0x3llu, \
    char(*)[5]: (T)0x1bllu, \
    char(*)[6]: (T)0x15llu, \
    char(*)[7]: (T)0x6dllu, \
    char(*)[8]: (T)0x33llu, \
    char(*)[9]: (T)0x155llu, \
    char(*)[10]: (T)0x5dllu, \
    char(*)[11]: (T)0xc3llu, \
    char(*)[12]: (T)0x5bllu, \
    char(*)[13]: (T)0x102dllu, \
    char(*)[14]: (T)0x10c1llu, \
    char(*)[15]: (T)0x3793llu, \
    char(*)[16]: ((T)0xD983llu), \
    char(*)[17]: ((T)0x18F77llu), \
    char(*)[18]: ((T)0x231B5llu), \
    char(*)[19]: ((T)0x558F9llu), \
    char(*)[20]: ((T)0x3BD41llu), \
    char(*)[21]: ((T)0x8D14Fllu), \
    char(*)[22]: ((T)0x27ECD3llu), \
    char(*)[23]: ((T)0x2ACD61llu), \
    char(*)[24]: ((T)0x44D18Fllu), \
    char(*)[25]: ((T)0x10D39CDllu), \
    char(*)[26]: ((T)0x2FC8E5Dllu), \
    char(*)[27]: ((T)0x70B0FDFllu), \
    char(*)[28]: ((T)0x85537C1llu), \
    char(*)[29]: ((T)0x11BF2947llu), \
    char(*)[30]: ((T)0x236BBC55llu), \
    char(*)[31]: ((T)0x3D3C8D97llu), \
    char(*)[32]: ((T)0x9406499Dllu), \
    char(*)[33]: ((T)0x199734D2Bllu), \
    char(*)[34]: ((T)0xCD07A8DFllu), \
    char(*)[35]: ((T)0x7F5518285llu), \
    char(*)[36]: ((T)0xC4DE899B5llu), \
    char(*)[37]: ((T)0x1828AB1319llu), \
    char(*)[38]: ((T)0xF1BD44E91llu), \
    char(*)[39]: ((T)0x9361C0C11llu), \
    char(*)[40]: ((T)0x830AD99373llu), \
    char(*)[41]: ((T)0x117BCD271EDllu), \
    char(*)[42]: ((T)0x290BB6BC8C3llu), \
    char(*)[43]: ((T)0x2B5508E6931llu), \
    char(*)[44]: ((T)0x10A5F85B555llu), \
    char(*)[45]: ((T)0x195B25DDCF0Fllu), \
    char(*)[46]: ((T)0x74388C5B5E5llu), \
    char(*)[47]: ((T)0x1B39C5063333llu), \
    char(*)[48]: ((T)0x9944059B13Bllu), \
    char(*)[49]: ((T)0x1912A2D60C77Bllu), \
    char(*)[50]: ((T)0x1CFBEE57C9249llu), \
    char(*)[51]: ((T)0x7341A0CBD3DCBllu), \
    char(*)[52]: ((T)0x7A5AD23F435E5llu), \
    char(*)[53]: ((T)0x3AB69B3A6A171llu), \
    char(*)[54]: ((T)0x1F3EBC6F8D5B45llu), \
    char(*)[55]: ((T)0x3862CAE7D0214Dllu), \
    char(*)[56]: ((T)0xFEBF10FDE6B74Fllu), \
    char(*)[57]: ((T)0xB46F18FD111111llu), \
    char(*)[58]: ((T)0xE329F106B3E453llu), \
    char(*)[59]: ((T)0x786B8C2BF0F0F0Fllu), \
    char(*)[60]: ((T)0xDAC015071111111llu), \
    char(*)[61]: ((T)0x109EE8A780D4C77Bllu), \
    char(*)[62]: ((T)0x156322EE233F128Dllu), \
    char(*)[63]: ((T)0xE3E629AEF6AC0C7llu), \
    char(*)[64]: ((T)0x320B022C873A49ADllu), \
    char(*)[65]: ((T)0xAFBC0506A6C6DE35llu), \
    char(*)[66]: (((T)0x3llu)<<64) | ((T)0xEC7C99406E209F2Dllu), \
    char(*)[67]: (((T)0x4llu)<<64) | ((T)0xC8F15647CA681847llu), \
    char(*)[68]: (((T)0x1llu)<<64) | ((T)0xF445568A8F88A55llu), \
    char(*)[69]: (((T)0x1Allu)<<64) | ((T)0xDCE0E8A4D15B61Fllu), \
    char(*)[70]: (((T)0x3Allu)<<64) | ((T)0x904B361254A9AB4Fllu), \
    char(*)[71]: (((T)0x24llu)<<64) | ((T)0x44D10BD80AD5641Fllu), \
    char(*)[72]: (((T)0xABllu)<<64) | ((T)0x1FA8EDB5AC6E5505llu), \
    char(*)[73]: (((T)0x1AAllu)<<64) | ((T)0xB3B19B75FFAE20D9llu), \
    char(*)[74]: (((T)0x34Allu)<<64) | ((T)0x13B1C9046251769Dllu), \
    char(*)[75]: (((T)0x3E0llu)<<64) | ((T)0x462E69048EC28E07llu), \
    char(*)[76]: (((T)0xBB4llu)<<64) | ((T)0x9A344F04165518D3llu), \
    char(*)[77]: (((T)0xD2Bllu)<<64) | ((T)0x6ABBE2A5B8A5B9C3llu), \
    char(*)[78]: (((T)0x2E8llu)<<64) | ((T)0x5A81A4B4E5A4B3F7llu), \
    char(*)[79]: (((T)0x7D1Cllu)<<64) | ((T)0x75EC4F4B572A94C1llu), \
    char(*)[80]: (((T)0xEC2Ellu)<<64) | ((T)0xD9F6B0F2315BA433llu), \
    char(*)[81]: (((T)0xEA80llu)<<64) | ((T)0x87BDDF2F72BF9A51llu), \
    char(*)[82]: (((T)0x326D1llu)<<64) | ((T)0x7493A746B784C139llu), \
    char(*)[83]: (((T)0x9582llu)<<64) | ((T)0xD56F2ABE2ED3CEB1llu), \
    char(*)[84]: (((T)0x7F2D8llu)<<64) | ((T)0x23491F62C7D0B7BBllu), \
    char(*)[85]: (((T)0x195567llu)<<64) | ((T)0x3F4A317675F6DCEBllu), \
    char(*)[86]: (((T)0x10432Fllu)<<64) | ((T)0xE45D8744657B373Dllu), \
    char(*)[87]: (((T)0x6BBABEllu)<<64) | ((T)0x34EE37295DB98B1llu), \
    char(*)[88]: (((T)0x297CD8llu)<<64) | ((T)0x583612ED446373F5llu), \
    char(*)[89]: (((T)0xA543F2llu)<<64) | ((T)0x548727C4EF225F85llu), \
    char(*)[90]: (((T)0x19B1301llu)<<64) | ((T)0x7A0C9AF0EC7A7957llu), \
    char(*)[91]: (((T)0x21E250llu)<<64) | ((T)0xBD8211F8C3753B69llu), \
    char(*)[92]: (((T)0xD13414Bllu)<<64) | ((T)0x40D43C34B9DBF5DDllu), \
    char(*)[93]: (((T)0x175831FFllu)<<64) | ((T)0x1B3D16BE1B7BCF99llu), \
    char(*)[94]: (((T)0xBAC4360llu)<<64) | ((T)0x9F1AFCD0B34AC5BFllu), \
    char(*)[95]: (((T)0x1484C668llu)<<64) | ((T)0x92C63CF9CBE3D32Fllu), \
    char(*)[96]: (((T)0xB32A5A05llu)<<64) | ((T)0x5E93221F2D8A9B21llu), \
    char(*)[97]: (((T)0x11213397Dllu)<<64) | ((T)0x235E1396CC63E27llu), \
    char(*)[98]: (((T)0x1AF2C7B32llu)<<64) | ((T)0xCF9321D407002A39llu), \
    char(*)[99]: (((T)0x15A9EA88Dllu)<<64) | ((T)0xFC8C28F05BCAC911llu), \
    char(*)[100]: (((T)0xDB6C50FC7llu)<<64) | ((T)0xAF73F07AF7460C19llu), \
    char(*)[101]: (((T)0x128510A5A3llu)<<64) | ((T)0xB585943FE85A65B5llu), \
    char(*)[102]: (((T)0x207ACE06AFllu)<<64) | ((T)0x67E67FBD832698F3llu), \
    char(*)[103]: (((T)0x266230BF70llu)<<64) | ((T)0x771775A09DF31D27llu), \
    char(*)[104]: (((T)0x4360E7B6DFllu)<<64) | ((T)0x46F0C6A358847CF7llu), \
    char(*)[105]: (((T)0x1AB8C22FC23llu)<<64) | ((T)0xD7C8F0D5C348D5A5llu), \
    char(*)[106]: (((T)0x27432877581llu)<<64) | ((T)0x4A8EC529883BEBllu), \
    char(*)[107]: (((T)0x3662A878DAllu)<<64) | ((T)0x1E0F5D5B63E0D5DDllu), \
    char(*)[108]: (((T)0xBDFE42543EFllu)<<64) | ((T)0x28245C5D7ADD469Fllu), \
    char(*)[109]: (((T)0x3EFFDE0E570llu)<<64) | ((T)0x45BBAB80B08B2BB5llu), \
    char(*)[110]: (((T)0x194CCBADA825llu)<<64) | ((T)0xB6D3C33676B05A0Fllu), \
    char(*)[111]: (((T)0x50C64234DAC5llu)<<64) | ((T)0x2CBE77FD3F47E45Bllu), \
    char(*)[112]: (((T)0x80A82971E565llu)<<64) | ((T)0x36A85685D312B841llu), \
    char(*)[113]: (((T)0x11A15576346B5llu)<<64) | ((T)0xE0C957997851403Fllu), \
    char(*)[114]: (((T)0x11FE5935B82FFllu)<<64) | ((T)0x9600525A8837900Fllu), \
    char(*)[115]: (((T)0x59B218791E771llu)<<64) | ((T)0xB31686BF20C8100Dllu), \
    char(*)[116]: (((T)0x6062580A00854llu)<<64) | ((T)0x9D562FC927DFD37Dllu), \
    char(*)[117]: (((T)0xE11370F0651B9llu)<<64) | ((T)0x35074A1F1FBF293llu), \
    char(*)[118]: (((T)0xFB40119E802AAllu)<<64) | ((T)0xE61475C2C9D0A363llu), \
    char(*)[119]: (((T)0x216C609EF40548llu)<<64) | ((T)0xC75DC852E830CDCBllu), \
    char(*)[120]: (((T)0x764ADDEB21BE66llu)<<64) | ((T)0x61CBAF52B6F1D7D1llu), \
    char(*)[121]: (((T)0x2897763CDD0192llu)<<64) | ((T)0x9A4D405558845253llu), \
    char(*)[122]: (((T)0x2212F4C0E029090llu)<<64) | ((T)0x1F10DC3F724FBAB3llu), \
    char(*)[123]: (((T)0x4C80BEF11CB5D87llu)<<64) | ((T)0x9C8C1C7BA1DA9791llu), \
    char(*)[124]: (((T)0x2BF422F883AC2BAllu)<<64) | ((T)0x1DBC49300B2E878Dllu), \
    char(*)[125]: (((T)0x1EC57E0AF16CCF7Cllu)<<64) | ((T)0xD90E16AB0628C9BFllu), \
    char(*)[126]: (((T)0x1C87AF37B2D45A7Fllu)<<64) | ((T)0x892E7F7B4899FBC3llu), \
    char(*)[127]: (((T)0x4433C079283A2DD7llu)<<64) | ((T)0xD3EE4DDC1EB189A1llu), \
    char(*)[128]: (((T)0x952C11F509CEE6ECllu)<<64) | ((T)0xE7C69664DF229087llu), \
    char(*)[129]: (((T)0x1llu)<<128) | (((T)0x8F26C880F48E38A5llu)<<64) | ((T)0x3B0588F985704A73llu), \
    char(*)[130]: (((T)0x1llu)<<128) | (((T)0x16BF2D084EDB93FAllu)<<64) | ((T)0x1957FE45AB60E037llu), \
    char(*)[131]: (((T)0x3llu)<<128) | (((T)0xEA79EE9CDD0F3442llu)<<64) | ((T)0x2D67F3AF00F235A5llu), \
    char(*)[132]: (((T)0x6llu)<<128) | (((T)0x525663763DE9B129llu)<<64) | ((T)0xC024B9C0D7C12331llu), \
    char(*)[133]: (((T)0x15llu)<<128) | (((T)0x4B852C144E40C939llu)<<64) | ((T)0x4DBE76D32EAB670Bllu), \
    char(*)[134]: (((T)0x23llu)<<128) | (((T)0xD303DB70BDBC68AEllu)<<64) | ((T)0x4CD60E75A808C6D9llu), \
    char(*)[135]: (((T)0x45llu)<<128) | (((T)0x3DE09220D9DDECA7llu)<<64) | ((T)0x976E2370C4BB08DFllu), \
    char(*)[136]: (((T)0x96llu)<<128) | (((T)0x9F565A7F28603B89llu)<<64) | ((T)0xAAA98294887495DFllu), \
    char(*)[137]: (((T)0xB6llu)<<128) | (((T)0x2E29781CBE55313llu)<<64) | ((T)0xD6F452875BF6B5Bllu), \
    char(*)[138]: (((T)0x5Bllu)<<128) | (((T)0x619997307C0F74B1llu)<<64) | ((T)0x75F430F1027A3409llu), \
    char(*)[139]: (((T)0x71Ellu)<<128) | (((T)0x4A8B2E7F040FE9Cllu)<<64) | ((T)0xA8B288F512D87A09llu), \
    char(*)[140]: (((T)0x8A3llu)<<128) | (((T)0x5EA9360E5B0851CAllu)<<64) | ((T)0x8C9850CFD471C91Bllu), \
    char(*)[141]: (((T)0x112llu)<<128) | (((T)0x8F546C8EA8BAECC8llu)<<64) | ((T)0xAAD27347B6120E75llu), \
    char(*)[142]: (((T)0xE7llu)<<128) | (((T)0x426D5F2B292A739llu)<<64) | ((T)0x376089F7D6BCC86Bllu), \
    char(*)[143]: (((T)0x6F85llu)<<128) | (((T)0xC8BCEDA0C602A819llu)<<64) | ((T)0xACFA31A8E15CF8F7llu), \
    char(*)[144]: (((T)0x5CA1llu)<<128) | (((T)0xF9EC88D1F4487125llu)<<64) | ((T)0x3160BF9ADA8686AFllu), \
    char(*)[145]: (((T)0x7C5Fllu)<<128) | (((T)0xD42933D2BC6EA55Dllu)<<64) | ((T)0x4E068A4B3CF903CFllu), \
    char(*)[146]: (((T)0x3F9A4llu)<<128) | (((T)0x3C70EFED811CA501llu)<<64) | ((T)0x37C4D75F8479EA11llu), \
    char(*)[147]: (((T)0x5033Ellu)<<128) | (((T)0x6F138120621A247Bllu)<<64) | ((T)0x89D5BD6746EF1C79llu), \
    char(*)[148]: (((T)0xD8EEEllu)<<128) | (((T)0x6F515F55D3312842llu)<<64) | ((T)0x5219F0D0BABE8749llu), \
    char(*)[149]: (((T)0x12E0ADllu)<<128) | (((T)0x8872C04E15C61338llu)<<64) | ((T)0x76C27248CC88393Bllu), \
    char(*)[150]: (((T)0x74279llu)<<128) | (((T)0xA7FB8F4A4DA605B2llu)<<64) | ((T)0x5B00F2EDDF0C0AFBllu), \
    char(*)[151]: (((T)0x7D3A94llu)<<128) | (((T)0x1DA6510CEDDC0EE0llu)<<64) | ((T)0xC846C803847B0133llu), \
    char(*)[152]: (((T)0xD17A0Cllu)<<128) | (((T)0x91F197F2339D0E73llu)<<64) | ((T)0x22FE3A4CD074BB39llu), \
    char(*)[153]: (((T)0x5466llu)<<128) | (((T)0xEE7CC699346D3DCllu)<<64) | ((T)0xEA4D5C167DE02F4Fllu), \
    char(*)[154]: (((T)0x2955B83llu)<<128) | (((T)0x8E2DD49BBEEE5D79llu)<<64) | ((T)0x952A04A0B0CD4A9llu), \
    char(*)[155]: (((T)0x5FCECD7llu)<<128) | (((T)0x98C945A4C971E9E4llu)<<64) | ((T)0x291FEBA94ACD87CFllu), \
    char(*)[156]: (((T)0x12FFF4Cllu)<<128) | (((T)0xE214A19FA9300BD4llu)<<64) | ((T)0x8687E70438759A13llu), \
    char(*)[157]: (((T)0x148414C5llu)<<128) | (((T)0x46575EF8008A4F17llu)<<64) | ((T)0xC6EA3FC39CA14FDDllu), \
    char(*)[158]: (((T)0x289D55A5llu)<<128) | (((T)0xD8AC26F74CBB3E9llu)<<64) | ((T)0xEE7F7B04265875B9llu), \
    char(*)[159]: (((T)0x3A52D7F7llu)<<128) | (((T)0x78685449317EC0F2llu)<<64) | ((T)0x46B8C03315275DD3llu), \
    char(*)[160]: (((T)0x963DA3DDllu)<<128) | (((T)0xD1B324B82AFD1F61llu)<<64) | ((T)0x2D4CFFE57B051C8Dllu), \
    char(*)[161]: (((T)0x32E4DBllu)<<128) | (((T)0x4323DE72CE3658BFllu)<<64) | ((T)0x17605D7AD4E7CCD1llu), \
    char(*)[162]: (((T)0x1997DD76llu)<<128) | (((T)0xC79DF93FC07427FAllu)<<64) | ((T)0x62FE1BC61CDCEC87llu), \
    char(*)[163]: (((T)0x1A3B2963llu)<<128) | (((T)0x6A691825456E6617llu)<<64) | ((T)0x9C7525294D5D46EBllu), \
    char(*)[164]: (((T)0x4443F5B42llu)<<128) | (((T)0xFF52C63A0C0CCD91llu)<<64) | ((T)0x682FD766FD40CEE7llu), \
    char(*)[165]: (((T)0x9BE7C19F7llu)<<128) | (((T)0x59E8D0C8C5235D52llu)<<64) | ((T)0xBD087C23C214B0BDllu), \
    char(*)[166]: (((T)0x226855C065llu)<<128) | (((T)0xC1C07A0A51F07FB6llu)<<64) | ((T)0xBA52A1511708C909llu), \
    char(*)[167]: (((T)0x2F635537DFllu)<<128) | (((T)0x8A0A8A376CC454BBllu)<<64) | ((T)0x7A7363ADD4D55CA5llu), \
    char(*)[168]: (((T)0x7C0033ECB4llu)<<128) | (((T)0xD78365BB1A3ECA1Bllu)<<64) | ((T)0x5D9097EF3597BF9llu), \
    char(*)[169]: (((T)0x1AED23280ECllu)<<128) | (((T)0xDBAF7C44A5283CB3llu)<<64) | ((T)0xC489614BB31B5B2Dllu), \
    char(*)[170]: (((T)0x30BE9181ADFllu)<<128) | (((T)0xDA71979644BEDBC0llu)<<64) | ((T)0x22119C2DB45A671llu), \
    char(*)[171]: (((T)0x713B3F40B66llu)<<128) | (((T)0xB73A34B765F85944llu)<<64) | ((T)0xF22FCBC266F0FFBDllu), \
    char(*)[172]: (((T)0x9A5278BF859llu)<<128) | (((T)0xDFB46BA9D0A38A52llu)<<64) | ((T)0x61BF5059051D85BFllu), \
    char(*)[173]: (((T)0xB5BAE47E878llu)<<128) | (((T)0xE0A7ED3AA9F999A2llu)<<64) | ((T)0xBACD0E0B5A76CFA1llu), \
    char(*)[174]: (((T)0x36A880305C31llu)<<128) | (((T)0x1048B10C1BB096F5llu)<<64) | ((T)0xCBA595CC1B9482DBllu), \
    char(*)[175]: (((T)0x52BDE47A4B0Ellu)<<128) | (((T)0x9DD36B76B3ABC099llu)<<64) | ((T)0x3BCDBA77D92D9C15llu), \
    char(*)[176]: (((T)0xC3C78F9E8F84llu)<<128) | (((T)0x26F3FA697ADC8623llu)<<64) | ((T)0x3348E0A848EEFF13llu), \
    char(*)[177]: (((T)0x69C3502DDFC1llu)<<128) | (((T)0xE99D798F28F8882Allu)<<64) | ((T)0x6C5253DA8C0AF327llu), \
    char(*)[178]: (((T)0x3D73F02208D41llu)<<128) | (((T)0x2729D3A844BAB60Fllu)<<64) | ((T)0x7998D35E4419B329llu), \
    char(*)[179]: (((T)0x611D2794BCD03llu)<<128) | (((T)0xCAE064D95106061Cllu)<<64) | ((T)0xB30F300F168D1A07llu), \
    char(*)[180]: (((T)0xFB25CCEF10476llu)<<128) | (((T)0x1B956FFF05EA59B5llu)<<64) | ((T)0x9EE4351228BA88C3llu), \
    char(*)[181]: (((T)0x1F2E82BD5FE18Ellu)<<128) | (((T)0x5E1B51CAE5CB006Ellu)<<64) | ((T)0x86B344B905048C5Fllu), \
    char(*)[182]: (((T)0x361D66F6673B58llu)<<128) | (((T)0x8866A1415D362F05llu)<<64) | ((T)0x1AB793B8A158D13Fllu), \
    char(*)[183]: (((T)0x6D9A33912A0EBFllu)<<128) | (((T)0xE8AF341684C69E62llu)<<64) | ((T)0x7954F84100B904E1llu), \
    char(*)[184]: (((T)0xAD9CEE1EC7785Ellu)<<128) | (((T)0xEEC3A76090FDD5E1llu)<<64) | ((T)0x66F0B339474A67C5llu), \
    char(*)[185]: (((T)0x17122101EB8892Bllu)<<128) | (((T)0xCF59BDF77A3FC87Dllu)<<64) | ((T)0x868419EDBE3AEAD5llu), \
    char(*)[186]: (((T)0x3A83DB208676492llu)<<128) | (((T)0xDB338C8B9B800E6Fllu)<<64) | ((T)0xD1E7541CD32245FBllu), \
    char(*)[187]: (((T)0x4202739D5DBBF30llu)<<128) | (((T)0xCAF2970A57BFA758llu)<<64) | ((T)0xA8447DFAFA86BFD1llu), \
    char(*)[188]: (((T)0x17A8BC52B91F6DAllu)<<128) | (((T)0x4600058EF72506ECllu)<<64) | ((T)0x813E14DA59D8275Fllu), \
    char(*)[189]: (((T)0x16C04EC3CEBDE4F9llu)<<128) | (((T)0x8D907249838D60FDllu)<<64) | ((T)0xDCCDB9E8EF097031llu), \
    char(*)[190]: (((T)0x2E8D4BE22133057Cllu)<<128) | (((T)0x774539A2C83D3B63llu)<<64) | ((T)0x24ACD947EBA6C78Dllu), \
    char(*)[191]: (((T)0x3AA919F7E0CEA864llu)<<128) | (((T)0xBA480678AB5E252Dllu)<<64) | ((T)0x251A1AAD32089855llu), \
    char(*)[192]: (((T)0x991DD212F53E6C85llu)<<128) | (((T)0x12468FE174678EDllu)<<64) | ((T)0xA88398808C03B6A9llu), \
    char(*)[193]: (((T)0x1llu)<<192) | (((T)0x449E32028DAFB041llu)<<128) | (((T)0xE7CF8484BCE66586llu)<<64) | ((T)0x6862C0FDBAEC1585llu), \
    char(*)[194]: (((T)0x1llu)<<192) | (((T)0x801EB828A0AF7718llu)<<128) | (((T)0xF99F93B2D868A4C7llu)<<64) | ((T)0xC6CAEC19EEB2F259llu), \
    char(*)[195]: (((T)0x3llu)<<192) | (((T)0xC5646E5C1B56F2B1llu)<<128) | (((T)0x86461F461A2BB74Dllu)<<64) | ((T)0x9B91BF79B11D2D47llu), \
    char(*)[196]: (((T)0xBllu)<<192) | (((T)0x426F124F092F9502llu)<<128) | (((T)0x20A312726AAD4D0Dllu)<<64) | ((T)0x11B40C53099F271Bllu), \
    char(*)[197]: (((T)0x16llu)<<192) | (((T)0x24BA23826A49FF73llu)<<128) | (((T)0x3AC01C6888C8B6D4llu)<<64) | ((T)0x33536395A021087llu), \
    char(*)[198]: (((T)0x14llu)<<192) | (((T)0x990ED72293D95CB0llu)<<128) | (((T)0xC90FA8226D2892BDllu)<<64) | ((T)0x4C578247BB163645llu), \
    char(*)[199]: (((T)0x68llu)<<192) | (((T)0x4EAFEFE6E59E5B06llu)<<128) | (((T)0x3D373D6053F74421llu)<<64) | ((T)0x8561953B86B9839Fllu), \
    char(*)[200]: (((T)0x76llu)<<192) | (((T)0x99C92D2AE0BD54D8llu)<<128) | (((T)0xF0072D0ED52DA040llu)<<64) | ((T)0x3AF67CE82D96BD3Fllu), \
    char(*)[201]: (((T)0x158llu)<<192) | (((T)0x497A209A0286A2A2llu)<<128) | (((T)0x34E7546801605D40llu)<<64) | ((T)0x1A77D6EB07826B8Bllu), \
    char(*)[202]: (((T)0x109llu)<<192) | (((T)0x880CEAAE475C02DBllu)<<128) | (((T)0xA2C70A12283D8EB0llu)<<64) | ((T)0x9D8F12A9B95FD5F3llu), \
    char(*)[203]: (((T)0x704llu)<<192) | (((T)0x5D76017B795290F4llu)<<128) | (((T)0x83E0672A6F108C8Fllu)<<64) | ((T)0x9193080DBC81F607llu), \
    char(*)[204]: (((T)0xE6Fllu)<<192) | (((T)0xE895F6E4B3E42284llu)<<128) | (((T)0xDB8DAD4E8007E999llu)<<64) | ((T)0xC696418F6F66556Bllu), \
    char(*)[205]: (((T)0x12EDllu)<<192) | (((T)0xF1A26B8DF99FFA87llu)<<128) | (((T)0x12344C936882C1DAllu)<<64) | ((T)0x777621B075B6900Fllu), \
    char(*)[206]: (((T)0x1272llu)<<192) | (((T)0x62633F3912848C52llu)<<128) | (((T)0x14BD7CEBD80348A5llu)<<64) | ((T)0xD2F50A4C4ACB5DA3llu), \
    char(*)[207]: (((T)0xCC7llu)<<192) | (((T)0xEA1A9329D6624A87llu)<<128) | (((T)0x1529E0139E501930llu)<<64) | ((T)0x2ED81DF249C2D005llu), \
    char(*)[208]: (((T)0x8677llu)<<192) | (((T)0xB28BCA8B03B25DC8llu)<<128) | (((T)0x9C9AEDEA89625791llu)<<64) | ((T)0xE05385A5C9448ED3llu), \
    char(*)[209]: (((T)0x4039llu)<<192) | (((T)0xE65DB8B47CA22F1Allu)<<128) | (((T)0xF920A161B5530CB6llu)<<64) | ((T)0x91EB744D070A13C5llu), \
    char(*)[210]: (((T)0x3259Cllu)<<192) | (((T)0xCD46833DA1D09A49llu)<<128) | (((T)0x63318D2586F5245Allu)<<64) | ((T)0xD9ED270C302B79EBllu), \
    char(*)[211]: (((T)0x4F21Ellu)<<192) | (((T)0x322BAFD38F5AAC43llu)<<128) | (((T)0x799F5BA3E194A88Cllu)<<64) | ((T)0xCD16AEE8F833ADD1llu), \
    char(*)[212]: (((T)0x3813Bllu)<<192) | (((T)0xE17A64633E7EC61Ellu)<<128) | (((T)0xFCDE981185CBBE16llu)<<64) | ((T)0x6D024182147EC57Dllu), \
    char(*)[213]: (((T)0x1D3506llu)<<192) | (((T)0x621AD14E9B767AEDllu)<<128) | (((T)0x61CC4444D73988CDllu)<<64) | ((T)0xFE745F6AEDD9EC53llu), \
    char(*)[214]: (((T)0x23CD56llu)<<192) | (((T)0xC04DE795F4CB4DE0llu)<<128) | (((T)0x2CCBB22F72E36B51llu)<<64) | ((T)0x1C10DF8B83928A77llu), \
    char(*)[215]: (((T)0x5A2659llu)<<192) | (((T)0x9267FF448797DF79llu)<<128) | (((T)0x4C7793127DA17319llu)<<64) | ((T)0x90C8B3048B5D817llu), \
    char(*)[216]: (((T)0x841716llu)<<192) | (((T)0x592AEDD6EA58FC2Dllu)<<128) | (((T)0x5966AE86238D5A1Allu)<<64) | ((T)0x94B84B59E5082361llu), \
    char(*)[217]: (((T)0x395F1Fllu)<<192) | (((T)0x9F9EB65D5D7BDCB2llu)<<128) | (((T)0xC0D22087AC83FDCCllu)<<64) | ((T)0x1D60D1AC53D3BA0Bllu), \
    char(*)[218]: (((T)0x15F4F22llu)<<192) | (((T)0xA9DDEEF5E6E80D93llu)<<128) | (((T)0x8134D78058EB4400llu)<<64) | ((T)0x8A817B32F9CEB315llu), \
    char(*)[219]: (((T)0x7E5246Bllu)<<192) | (((T)0x4F49C2AC3D686A8Bllu)<<128) | (((T)0x7B4E52D90F9C05CFllu)<<64) | ((T)0x13E2B33FCAE05623llu), \
    char(*)[220]: (((T)0x5A7CFCEllu)<<192) | (((T)0x6FA1CF887B2925DCllu)<<128) | (((T)0xA19B5EC7364283DCllu)<<64) | ((T)0xE264339AA5C21FFBllu), \
    char(*)[221]: (((T)0x125971F8llu)<<192) | (((T)0x34CD5C3EA556216llu)<<128) | (((T)0x3CD9C2433096F2E6llu)<<64) | ((T)0xEB89D94FA64B9D21llu), \
    char(*)[222]: (((T)0x2638F1DDllu)<<192) | (((T)0x9813A590D0BE0AEEllu)<<128) | (((T)0xA3A16281E622A96Dllu)<<64) | ((T)0xCF8102B51FCED661llu), \
    char(*)[223]: (((T)0x8076D69llu)<<192) | (((T)0x258A35E7F1ABB9D1llu)<<128) | (((T)0x782733C5C693E27llu)<<64) | ((T)0x8639301DD2151611llu), \
    char(*)[224]: (((T)0x864039EFllu)<<192) | (((T)0x851270B355D2D8AFllu)<<128) | (((T)0x33AA17B37C83E8Bllu)<<64) | ((T)0xBBDDA41378BEC8D9llu), \
    char(*)[225]: (((T)0x19A90CE83llu)<<192) | (((T)0xA8BC70471388AF2Fllu)<<128) | (((T)0x6A2FE5728960B18Bllu)<<64) | ((T)0xD22E5A4E24160445llu), \
    char(*)[226]: (((T)0x1596D92DFllu)<<192) | (((T)0x1A07A754D95EE3DBllu)<<128) | (((T)0x2F1C06C32D215EDEllu)<<64) | ((T)0x98E7E5609EBB9C3Dllu), \
    char(*)[227]: (((T)0x58622FA74llu)<<192) | (((T)0x6DBB0D1903659520llu)<<128) | (((T)0xFE72663AFAEE74D8llu)<<64) | ((T)0x33EC422B81BA09EDllu), \
    char(*)[228]: (((T)0xD5169D1CEllu)<<192) | (((T)0x85B6A1FF065F2A34llu)<<128) | (((T)0xA5FBE6C587A6F499llu)<<64) | ((T)0xCD87EA0EFE167827llu), \
    char(*)[229]: (((T)0x303CE5E79llu)<<192) | (((T)0x4F55D3D931A2B044llu)<<128) | (((T)0x935A8466ADD1CB0Bllu)<<64) | ((T)0x1FF39D256CA2869Bllu), \
    char(*)[230]: (((T)0xCDA5416E6llu)<<192) | (((T)0x5ACCB771354F0655llu)<<128) | (((T)0x52A9F40A4927B4F0llu)<<64) | ((T)0x17758A131D8307E5llu), \
    char(*)[231]: (((T)0x6044A5CF63llu)<<192) | (((T)0x50253E9FA116B176llu)<<128) | (((T)0x840C30BBC60B83D2llu)<<64) | ((T)0xF3E1756D37E72C6Dllu), \
    char(*)[232]: (((T)0x78DA357120llu)<<192) | (((T)0x8F73B95F5FB0FF2Fllu)<<128) | (((T)0x8E9C8DF260C3A4A6llu)<<64) | ((T)0xD54F0122193FDA9Bllu), \
    char(*)[233]: (((T)0x92BB360E70llu)<<192) | (((T)0x8EF7C2BCD6C9144Cllu)<<128) | (((T)0xF604E8437637F2B7llu)<<64) | ((T)0x189764A3964D4EDDllu), \
    char(*)[234]: (((T)0x3DBDC335B01llu)<<192) | (((T)0xE4D6CCC724B78137llu)<<128) | (((T)0x61A85C61015CDEA6llu)<<64) | ((T)0xD716BED21F41289Fllu), \
    char(*)[235]: (((T)0x3542282AC79llu)<<192) | (((T)0xC5BE0B20F3E72909llu)<<128) | (((T)0x9C4C5FC9758D61D2llu)<<64) | ((T)0x718AFADCE4C5FB1Bllu), \
    char(*)[236]: (((T)0x2EA1402B008llu)<<192) | (((T)0x84DDA12051B2A6CBllu)<<128) | (((T)0x94AFCAE5255EF0F6llu)<<64) | ((T)0x530B195496E93101llu), \
    char(*)[237]: (((T)0xB9E2ADB38D6llu)<<192) | (((T)0x4F390A38F034DEE0llu)<<128) | (((T)0xD155AC58E20F57FBllu)<<64) | ((T)0x50B6939FC0D06D8Dllu), \
    char(*)[238]: (((T)0x39115465D673llu)<<192) | (((T)0x790E831FCFF80CF7llu)<<128) | (((T)0x28296AA379C76709llu)<<64) | ((T)0x8C025A85DE37C8BBllu), \
    char(*)[239]: (((T)0x2AAD6498527Dllu)<<192) | (((T)0xE1DC3A8F48DED940llu)<<128) | (((T)0xC590B7BBC49E74Bllu)<<64) | ((T)0xC4ADC6EDEFB63405llu), \
    char(*)[240]: (((T)0x6D9CA0569131llu)<<192) | (((T)0x29C5725F55C3C8Cllu)<<128) | (((T)0x327ACFE554D85E0Dllu)<<64) | ((T)0x25E939C06FF58D8Fllu), \
    char(*)[241]: (((T)0x68425615103Allu)<<192) | (((T)0xD98F2086DE677E61llu)<<128) | (((T)0xB06034E5A6F7909Allu)<<64) | ((T)0xEB1DCA0CAE909417llu), \
    char(*)[242]: (((T)0x807E53E46213llu)<<192) | (((T)0x7DDFD32440629A88llu)<<128) | (((T)0x63B2B221380FE549llu)<<64) | ((T)0x76CAAF563ABD194Dllu), \
    char(*)[243]: (((T)0x608591A965004llu)<<192) | (((T)0x9EC4A21F6B7F86BDllu)<<128) | (((T)0xAD86BD42B4D10E45llu)<<64) | ((T)0xA7C89A7FC82F6A77llu), \
    char(*)[244]: (((T)0x9BE67323680CAllu)<<192) | (((T)0xECC52F18FF7165FBllu)<<128) | (((T)0xE3EA5CD65B007EFAllu)<<64) | ((T)0x86E5D15F088FEFB7llu), \
    char(*)[245]: (((T)0x132734A46A3C5Dllu)<<192) | (((T)0x8FD39F6B8659C242llu)<<128) | (((T)0xDDEAAD8F78938AD3llu)<<64) | ((T)0x56550DBEC5EAC301llu), \
    char(*)[246]: (((T)0x1E8147C7093CE2llu)<<192) | (((T)0x69D18902CE2C486Bllu)<<128) | (((T)0x2484A110292EB40Fllu)<<64) | ((T)0x3D4C4EE6677821BBllu), \
    char(*)[247]: (((T)0x171D1C4A719754llu)<<192) | (((T)0x8E2B15F0CC7FD0BCllu)<<128) | (((T)0x21EDA565F5890C80llu)<<64) | ((T)0x273802F7201D3FB5llu), \
    char(*)[248]: (((T)0x8496C97D75F491llu)<<192) | (((T)0xA6410A8AB6BCB5AEllu)<<128) | (((T)0xC83B3999FD6D6F21llu)<<64) | ((T)0xFFAA88E19CE9ECC9llu), \
    char(*)[249]: (((T)0xA4E73BD089A5CFllu)<<192) | (((T)0x6CB0316F3463EF32llu)<<128) | (((T)0xDB60262F63712F4Fllu)<<64) | ((T)0x2C374C7371E09925llu), \
    char(*)[250]: (((T)0x77206731F8B2F5llu)<<192) | (((T)0xC0E06333CA0D9CE4llu)<<128) | (((T)0x6B3CC34E8A553A43llu)<<64) | ((T)0x5A3C56FDF4263827llu), \
    char(*)[251]: (((T)0x43F562E729962B7llu)<<192) | (((T)0x74378A3F3EB7E2C3llu)<<128) | (((T)0x2A927CE66F7D2AE1llu)<<64) | ((T)0x12B6C125D4408BA7llu), \
    char(*)[252]: (((T)0x8A7FF6B2966B88Cllu)<<192) | (((T)0x6D5050DC47EE3B7Dllu)<<128) | (((T)0x566FCFEA745A9828llu)<<64) | ((T)0x2993E6D6D42639A7llu), \
    char(*)[253]: (((T)0xA23B6DF4C88872Ellu)<<192) | (((T)0x88A8C5ED1EDBD8D4llu)<<128) | (((T)0x47389835C907FF12llu)<<64) | ((T)0xAC85C791749EFA3llu), \
    char(*)[254]: (((T)0x23844462C16B5BCEllu)<<192) | (((T)0x5A3DEE05E198E605llu)<<128) | (((T)0x62A2F4B40BDE7E79llu)<<64) | ((T)0xA7FC1DFFD9DE9627llu), \
    char(*)[255]: (((T)0x703BF55B766876ABllu)<<192) | (((T)0x945B37E01EB1F2C9llu)<<128) | (((T)0xD0379AE3F3FCAA44llu)<<64) | ((T)0x2996DA1EDBB007ADllu), \
    char(*)[256]: (((T)0xBE28F8C46E37F66Allu)<<192) | (((T)0x43B8F994708263E4llu)<<128) | (((T)0x3574DA92C5568F9Dllu)<<64) | ((T)0xFC88E588B56087CBllu), \
    char(*)[257]: (((T)0xCD7AFAFC06D24171llu)<<192) | (((T)0x750096C65CDD1037llu)<<128) | (((T)0xB66C49CC7826C3CFllu)<<64) | ((T)0xC8FDB8BAC4FBD5EDllu), \
    char(*)[258]: (((T)0xC2546DF555B6FC9llu)<<192) | (((T)0x884DDC744455E535llu)<<128) | (((T)0x4700B9F021C494A9llu)<<64) | ((T)0x410C382D36BA17D1llu), \
    char(*)[259]: (((T)0x7llu)<<256) | (((T)0x3F49DC1418D22392llu)<<192) | (((T)0x1A9B5C5B91506017llu)<<128) | (((T)0xD590163EB77AC067llu)<<64) | ((T)0xE4C933D42ED1CDC1llu), \
    char(*)[260]: (((T)0x2llu)<<256) | (((T)0x1247876E221B94D4llu)<<192) | (((T)0x9F14B48D30ADEBE1llu)<<128) | (((T)0x4580FFF776ECD323llu)<<64) | ((T)0xB53B2B3EF9B97F25llu), \
    char(*)[261]: (((T)0x1Bllu)<<256) | (((T)0xE9052B79D89B6982llu)<<192) | (((T)0x6B4C15EBAF8F07DCllu)<<128) | (((T)0x8BB8B4ED423010D0llu)<<64) | ((T)0x426E06B7D7FC0835llu), \
    char(*)[262]: (((T)0x3Ellu)<<256) | (((T)0x1C74044DD0A70BBEllu)<<192) | (((T)0x39CEFABEC27E9FBEllu)<<128) | (((T)0xEBAA548E7C249DA6llu)<<64) | ((T)0xE5F3F0B82CAF0D71llu), \
    char(*)[263]: (((T)0x4Bllu)<<256) | (((T)0xE43CDB7C55B5169llu)<<192) | (((T)0x6C62933BFB054F56llu)<<128) | (((T)0xABAA6BBBC5259D06llu)<<64) | ((T)0x5A5CF912A17AD6FFllu), \
    char(*)[264]: (((T)0x11llu)<<256) | (((T)0x42EDD04E99FE5E29llu)<<192) | (((T)0xF3940FB8A3FB5134llu)<<128) | (((T)0x5CA95E2EC54AB6llu)<<64) | ((T)0x9DB527A10AB0E3AFllu), \
    char(*)[265]: (((T)0xAEllu)<<256) | (((T)0x3AF86ACA09C1AA59llu)<<192) | (((T)0xC37EF8389A2EE9BCllu)<<128) | (((T)0x9447147C76442660llu)<<64) | ((T)0xD445A80578555DF5llu), \
    char(*)[266]: (((T)0x2A4llu)<<256) | (((T)0x77892CCB7C06D5CEllu)<<192) | (((T)0x8DC60F511E4E190Dllu)<<128) | (((T)0x5295F9327B301EF6llu)<<64) | ((T)0xE9D5B6DB9EB65D1Dllu), \
    char(*)[267]: (((T)0x704llu)<<256) | (((T)0xDF979EA6A41A2B7llu)<<192) | (((T)0xC9FFB8D289C6C644llu)<<128) | (((T)0xA96415FF60025C80llu)<<64) | ((T)0x30BAD2A977E1688Dllu), \
    char(*)[268]: (((T)0x338llu)<<256) | (((T)0x81E7E33AE4472A3Cllu)<<192) | (((T)0x8A59D8A5DF932E46llu)<<128) | (((T)0xEBA48F851BDB8A79llu)<<64) | ((T)0x794685D66CBB6DBDllu), \
    char(*)[269]: (((T)0x1A0Allu)<<256) | (((T)0xC9B98CE58535FBD2llu)<<192) | (((T)0x20121D01CF4362ADllu)<<128) | (((T)0x7C6CB5DD9714A40llu)<<64) | ((T)0xF5886D681AE1101Fllu), \
    char(*)[270]: (((T)0x3F1Dllu)<<256) | (((T)0x1C735C1B6E48FE84llu)<<192) | (((T)0xF9E9CF8B60ECA97Allu)<<128) | (((T)0x2986D5C41D056583llu)<<64) | ((T)0x3273485A78074213llu), \
    char(*)[271]: (((T)0x426Allu)<<256) | (((T)0xB103B8CC2B3A6CDAllu)<<192) | (((T)0x86AEA7178CC18885llu)<<128) | (((T)0x4D1B51BBFA6BF2A8llu)<<64) | ((T)0xD194F1023FAD069Dllu), \
    char(*)[272]: (((T)0x6AF9llu)<<256) | (((T)0xEB0FBCA0DD0A548Allu)<<192) | (((T)0x65919BAF51D8B71Fllu)<<128) | (((T)0xC078D5940F4D8053llu)<<64) | ((T)0x6E650DADAC0BD023llu), \
    char(*)[273]: (((T)0x109B5llu)<<256) | (((T)0xFD33536F0E015DE3llu)<<192) | (((T)0xEB1B52E775438354llu)<<128) | (((T)0x6F6420E499E9B9C0llu)<<64) | ((T)0x406C22169BD9EE7Bllu), \
    char(*)[274]: (((T)0x3DDDEllu)<<256) | (((T)0x340CB980587E9B24llu)<<192) | (((T)0xC70EC8952F0716E5llu)<<128) | (((T)0x63F5FF6BB8DD2C99llu)<<64) | ((T)0x5FAD06C08A846879llu), \
    char(*)[275]: (((T)0x7757Bllu)<<256) | (((T)0xD94672C5D48E0FBFllu)<<192) | (((T)0x5137E945D55FB3CAllu)<<128) | (((T)0x179C6376D96966BFllu)<<64) | ((T)0x31CF334CCE0184EBllu), \
    char(*)[276]: (((T)0x9788Ellu)<<256) | (((T)0x72BDE73684165C0Allu)<<192) | (((T)0x29FE1A435871155llu)<<128) | (((T)0xCC99F44BC33ECA90llu)<<64) | ((T)0x8A26A9666517E9D5llu), \
    char(*)[277]: (((T)0x10B3ADllu)<<256) | (((T)0x65F4AE4EFCA2C94Fllu)<<192) | (((T)0x39A1D9C8591824E5llu)<<128) | (((T)0xE1663469F9C60892llu)<<64) | ((T)0xD8333971D9B8150Bllu), \
    char(*)[278]: (((T)0xDF7C5llu)<<256) | (((T)0x4F2C2D04EB316DACllu)<<192) | (((T)0xF47A9EA5D9299A34llu)<<128) | (((T)0x5E2A03EAAE8545A2llu)<<64) | ((T)0x22D936C94167E65Dllu), \
    char(*)[279]: (((T)0x602115llu)<<256) | (((T)0xAAF518810F9B4D17llu)<<192) | (((T)0xBBADD83BEAE53E5Cllu)<<128) | (((T)0x1C9270B6E0B952BDllu)<<64) | ((T)0x34A7C5F799DA156Dllu), \
    char(*)[280]: (((T)0x62E1B0llu)<<256) | (((T)0x1AF2D424B6638037llu)<<192) | (((T)0x1D9F166B85BE6D6Fllu)<<128) | (((T)0x6101FFBA822A17FAllu)<<64) | ((T)0xA8F23629B6757E8Bllu), \
    char(*)[281]: (((T)0x58B502llu)<<256) | (((T)0xABEAD60072FEBB9Allu)<<192) | (((T)0x9D6EBC41A851E50Allu)<<128) | (((T)0x2932E365EB76B50Dllu)<<64) | ((T)0x3739C8C2A9DFDBFllu), \
    char(*)[282]: (((T)0x1AE937Fllu)<<256) | (((T)0x386BECA21A8DDCEAllu)<<192) | (((T)0xBE12B584554D11B5llu)<<128) | (((T)0xEA8093DA6B206A2llu)<<64) | ((T)0x2CBCC101D78CFF61llu), \
    char(*)[283]: (((T)0x53F61E4llu)<<256) | (((T)0x99E88696C8013509llu)<<192) | (((T)0xFD04B79FAB0AB1A3llu)<<128) | (((T)0x95D2F82FB364A9AAllu)<<64) | ((T)0x5454873888347FC9llu), \
    char(*)[284]: (((T)0x913C4C0llu)<<256) | (((T)0xA3A80CAB2B541198llu)<<192) | (((T)0x44489CD2ABB455FEllu)<<128) | (((T)0xF259E5E5E5F2EDC6llu)<<64) | ((T)0x19CF2A7C24827805llu), \
    char(*)[285]: (((T)0xE5E7B03llu)<<256) | (((T)0xA86018BB2A372B92llu)<<192) | (((T)0xE940F5783FF675F8llu)<<128) | (((T)0xCA431E7671AD6966llu)<<64) | ((T)0xC546EDBB6DAB2165llu), \
    char(*)[286]: (((T)0x49B72BBllu)<<256) | (((T)0xFBC8364766BBD146llu)<<192) | (((T)0xF90A87B4935B4873llu)<<128) | (((T)0xB27B91D25929972Ellu)<<64) | ((T)0x7E9CF618826241B3llu), \
    char(*)[287]: (((T)0x773983B4llu)<<256) | (((T)0xB44C699A4B395F84llu)<<192) | (((T)0x15C060F65BF38F8Cllu)<<128) | (((T)0xF149F416CFD767B2llu)<<64) | ((T)0xD84951637FB19581llu), \
    char(*)[288]: (((T)0x1699515Fllu)<<256) | (((T)0x5848205B9B5CD75Dllu)<<192) | (((T)0x914CCA914AB45EAFllu)<<128) | (((T)0xBE74C210A2CFF973llu)<<64) | ((T)0xBA48386FA320E981llu) \
  )

#endif
