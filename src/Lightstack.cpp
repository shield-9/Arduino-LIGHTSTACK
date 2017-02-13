#include<Lightstack.hpp>

#include "Arduino.h"
#include<Wire.h>

Lightstack::Lightstack(const uint8_t latch_pin, const uint8_t clock_pin,
	                   const uint8_t data_pin, const uint8_t tiers) {
	_latch_pin = latch_pin;
	_clock_pin = clock_pin;
	_data_pin  = data_pin;
	_tiers     = tiers;

	states = new byte[_tiers];
}


/**
 * High Level API
 */
bool Lightstack::begin() {
	begin(BLINK);
}

bool Lightstack::begin(const _LS_MODE_PATTERN pattern) {
	pinMode(_latch_pin, OUTPUT);
	pinMode(_clock_pin, OUTPUT);
	pinMode(_data_pin,  OUTPUT);

	initBits(pattern);
	shiftOut();

	return true;
}

void Lightstack::next() {
	calcBits();
	shiftOut();
}

void Lightstack::apply() {
	shiftOut();
}

/**
 * Middle Level API
 */
// Single Bit Operations
void Lightstack::writeBit(const uint8_t tier, const uint8_t bit, const bool state) {
	if (state) {
		setBit(tier, bit);
	} else {
		clearBit(tier, bit);
	}
}

void Lightstack::setBit(const uint8_t tier, const uint8_t bit) {
	states[tier] |= 0x01 << bit;
}

void Lightstack::clearBit(const uint8_t tier, const uint8_t bit) {
	states[tier] &= ~(0x01 << bit);
}

bool Lightstack::readBit(const uint8_t tier, const uint8_t bit) {
	return states[tier] & (0x01 << bit);
}

// Single Tier Operations
void Lightstack::writeTier(const uint8_t tier, byte state) {
	states[tier] = state;
}

void Lightstack::setTier(const uint8_t tier) {
	states[tier] = 0xFF;
}

void Lightstack::clearTier(const uint8_t tier) {
	states[tier] = 0x00;
}

byte Lightstack::readTier(const uint8_t tier) {
	return states[tier];
}

/**
 * Low Level API
 */
void Lightstack::initBits(const _LS_MODE_PATTERN pattern) {
	_pattern = pattern;

	for (uint8_t i = 0; i < _tiers; i++) {
		switch(_pattern) {
			case BLINK:
				states[i] = 0x00;
				break;
		}
	}
}

void Lightstack::calcBits() {
	for (uint8_t i = 0; i < _tiers; i++) {
		switch(_pattern) {
			case BLINK:
				states[i] = ~states[i];
				break;
		}
	}
}

void Lightstack::shiftOut() {
	digitalWrite(_latch_pin, LOW);

	// Make sure that the clock pin is low.
	digitalWrite(_clock_pin, LOW);

	for (uint8_t i = 0; i < _tiers; i++) {
		::shiftOut(_data_pin, _clock_pin, MSBFIRST, states[i]);
	}

	digitalWrite(_latch_pin, HIGH);
}


Lightstack tower = Lightstack(8, 12, 11, 5);
