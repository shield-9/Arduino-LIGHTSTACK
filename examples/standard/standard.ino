#include <Lightstack.hpp>

void setup() {
	tower.begin();
}

void loop() {
	for (uint8_t i = 0; i < 5; i++) {
		tower.clearTier(i);
	}

	tower.apply();
	delay(500);

	for (uint8_t i = 0; i < 8; i++) {
		for (uint8_t j = 0; j < 5; j++) {
			byte tier = tower.readTier(j);
			tier += 0x01 << i;

			tower.writeTier(j, tier);
		}

		tower.apply();
		delay(500);
	}
}
