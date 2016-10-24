#pragma once

// Just a little info object to hold the slotId and the absoluteId
struct GameObjectToken {
	int slotId;
	unsigned int absoluteId;

	GameObjectToken(int _slotId, unsigned int _absoluteId) {
		slotId = _slotId;
		absoluteId = _absoluteId;
	}
};