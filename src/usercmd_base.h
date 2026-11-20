#ifndef USERCMD_BASE_H
#define USERCMD_BASE_H

// ANVIL: added. A client delta-encodes the first usercmd of a packet against a
// base usercmd built from the last snapshot it received (iw3mp 1.7: 0x505B70,
// called by CL_WritePacket). Fields it sends as unchanged are copied from the
// base, so the server has to build the same base: from the same player state,
// with the same arithmetic. Kept free of engine headers so tests can include it.

#include <stdint.h>

// The client sends clc_move, rather than clc_moveNoDelta, only when its
// snapshot came in the message it acknowledges. The server keeps the frames of
// its last packetBackup messages.
static inline int UsercmdBase_HasAckedSnapshot(int isDelta, int outgoingSequence, int messageAcknowledge, int packetBackup)
{
	int age;

	if ( !isDelta || messageAcknowledge < 0 )
		return 0;
	age = outgoingSequence - messageAcknowledge;
	return age > 0 && age < packetBackup;
}

// The client decodes the snapshot's angles as signed 16-bit values and computes
// (int)((view - delta) * 182.04445 + 0.5), which is their difference, plus 1
// when that's negative, because the cast truncates towards 0.
static inline uint16_t UsercmdBase_Angle(int16_t viewShort, int16_t deltaShort)
{
	int difference = viewShort - deltaShort;

	return (uint16_t)(difference < 0 ? difference + 1 : difference);
}

#endif
