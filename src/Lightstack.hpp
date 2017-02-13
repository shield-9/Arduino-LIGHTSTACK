#ifndef LIGHTSTACK_h
#define LIGHTSTACK_h

#include "Arduino.h"

enum _LS_MODE_PATTERN : uint8_t {
	BLINK  = 0x02
};

class Lightstack {
	public:
		Lightstack(uint8_t latch_pin, uint8_t clock_pin, uint8_t data_pin,
		           uint8_t tiers);

		bool begin();
		bool begin(_LS_MODE_PATTERN pattern);

		void next();
		void apply();

		void writeBit(uint8_t tier, uint8_t bit, bool state);
		void setBit(uint8_t tier, uint8_t bit);
		void clearBit(uint8_t tier, uint8_t bit);
		bool readBit(uint8_t tier, uint8_t bit);

		void writeTier(uint8_t tier, byte states);
		void setTier(uint8_t tier);
		void clearTier(uint8_t tier);
		byte readTier(uint8_t tier);

	private:
		uint8_t _latch_pin;
		uint8_t _clock_pin;
		uint8_t _data_pin;
		uint8_t _tiers;
		uint8_t _pattern;

		byte* states;

		void initBits(_LS_MODE_PATTERN pattern);
		void calcBits();

		void shiftOut();
};

extern Lightstack tower;

#endif
