#include<Lightstack.hpp>

#include "Arduino.h"
#include <limits.h>

template <typename T>
T rol(T val, int8_t width) {
	size_t max = sizeof(T) * CHAR_BIT;
	width %= max;
	return (val << width) | (val >> (max - width));
}


/**
 * High Level API
 */
Lightstack::Lightstack() {
	_dynamic = false;
	states = 0x00;

	for (uint8_t i = 0; i < 8; i++) {
		pinMode(_leds[i], OUTPUT);
	}

}

bool Lightstack::begin(const _LS_MODE_PATTERN pattern) {
	initBits(pattern);
	apply();

	return true;
}

void Lightstack::next() {
	calcNextBits();
	apply();
}

void Lightstack::apply() {
	for (uint8_t i = 0; i < 8; i++) {
		digitalWrite(_leds[i], readBit(i));
	}
}


/**
 * Middle Level API
 */
// Single Bit Operations
void Lightstack::writeBit(const uint8_t bit, const bool state) {
	if (state) {
		setBit(bit);
	} else {
		clearBit(bit);
	}
}

void Lightstack::setBit(const uint8_t bit) {
	states |= 0x01 << bit;
}

void Lightstack::clearBit(const uint8_t bit) {
	states &= ~(0x01 << bit);
}

bool Lightstack::readBit(const uint8_t bit) {
	return states & (0x01 << bit);
}


void Lightstack::write(byte state) {
	states = state;
}

void Lightstack::set() {
	write(0xFF);
}

void Lightstack::clear() {
	write(0x00);
}

byte Lightstack::read() {
	return states;
}

/**
 * Low Level API
 */
void Lightstack::initBits(const _LS_MODE_PATTERN pattern) {
	_pattern = pattern;

	switch(_pattern) {
		case ROTATE:
			states = 0x01;
			break;
		case BLINK:
			states = 0x00;
			break;
		default:
			states = 0x00;
	}
}

void Lightstack::calcNextBits() {
	switch(_pattern) {
		case ROTATE:
			states = rol(states, 1);
			break;
		case BLINK:
			switch (states) {
				case 0xFF: // Turn off
					states = 0x00;
					break;
				case 0x00: // Init
					states = 0xFF;
					break;
				default:
					states = 0x00;
			}
			break;
		default:
			states = 0x00;
	}
}

Lightstack tower = Lightstack();
