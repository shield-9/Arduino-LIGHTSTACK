#ifndef LIGHTSTACK_h
#define LIGHTSTACK_h

#include "Arduino.h"

enum _LS_MODE_PATTERN : uint8_t {
	ROTATE = 0x01,
	BLINK  = 0x02
};

class Lightstack {
	public:
		/**
		 * High Level API
		 */
		Lightstack();
		bool begin(const _LS_MODE_PATTERN pattern);
		void next();
		void apply();

		/**
		 * Middle Level API
		 */
		// Single Bit Operations
		void writeBit(const uint8_t bit, const bool state);
		void setBit(const uint8_t bit);
		void clearBit(const uint8_t bit);
		bool readBit(const uint8_t bit);

		void write(byte state);
		void set();
		void clear();
		byte read();

	private:
		uint8_t _leds[8] = {0, 1, 2, 3, 5, 7, 8, 9};

		uint8_t _pattern;
		bool _dynamic;
		byte states;

		/**
		 * Low Level API
		 */
		void initBits(const _LS_MODE_PATTERN pattern);
		void calcNextBits();
};

extern Lightstack tower;

#endif
