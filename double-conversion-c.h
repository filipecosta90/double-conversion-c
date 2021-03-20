#ifndef __DOUBLE_CONVERSION_DOUBLE_CONVERSION_C_H__
#define __DOUBLE_CONVERSION_DOUBLE_CONVERSION_C_H__

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// The maximal number of digits that are needed to emit a double in base 10.
// A higher precision can be achieved by using more digits, but the shortest
// accurate representation of any double will never use more digits than
// kBase10MaximalLength.
// Note that DoubleToAscii null-terminates its input. So the given buffer
// should be at least kBase10MaximalLength + 1 characters long.
static const int kBase10MaximalLength = 17;

enum double_to_asci_mode {
  // Produce the shortest correct representation.
  // For example the output of 0.299999999999999988897 is (the less accurate
  // but correct) 0.3.
  SHORTEST,
  // Same as SHORTEST, but for single-precision floats.
  SHORTEST_SINGLE,
  // Produce a fixed number of digits after the decimal point.
  // For instance fixed(0.1, 4) becomes 0.1000
  // If the input number is big, the output will be big.
  FIXED,
  // Fixed number of digits (independent of the decimal point).
  PRECISION
};

// Converts the given double 'v' to digit characters. 'v' must not be NaN,
// +Infinity, or -Infinity. In SHORTEST_SINGLE-mode this restriction also
// applies to 'v' after it has been casted to a single-precision float. 
//
// The result should be interpreted as buffer * 10^(point-length).
//
// The digits are written to the buffer in the platform's charset, which is
// often UTF-8 (with ASCII-range digits) but may be another charset, such
// as EBCDIC.
//
// The output depends on the given mode:
//  - SHORTEST: produce the least amount of digits for which the internal
//   identity requirement is still satisfied. If the digits are printed
//   (together with the correct exponent) then reading this number will give
//   'v' again. The buffer will choose the representation that is closest to
//   'v'. If there are two at the same distance, than the one farther away
//   from 0 is chosen (halfway cases - ending with 5 - are rounded up).
//   In this mode the 'requested_digits' parameter is ignored.
//  - SHORTEST_SINGLE: same as SHORTEST but with single-precision.
//  - FIXED: produces digits necessary to print a given number with
//   'requested_digits' digits after the decimal point. The produced digits
//   might be too short in which case the caller has to fill the remainder
//   with '0's.
//   Example: toFixed(0.001, 5) is allowed to return buffer="1", point=-2.
//   Halfway cases are rounded towards +/-Infinity (away from 0). The call
//   toFixed(0.15, 2) thus returns buffer="2", point=0.
//   The returned buffer may contain digits that would be truncated from the
//   shortest representation of the input.
//  - PRECISION: produces 'requested_digits' where the first digit is not '0'.
//   Even though the length of produced digits usually equals
//   'requested_digits', the function is allowed to return fewer digits, in
//   which case the caller has to fill the missing digits with '0's.
//   Halfway cases are again rounded away from 0.
// double_to_ascii expects the given buffer to be big enough to hold all
// digits and a terminating null-character. In SHORTEST-mode it expects a
// buffer of at least kBase10MaximalLength + 1. In all other modes the
// requested_digits parameter and the padding-zeroes limit the size of the
// output. Don't forget the decimal point, the exponent character and the
// terminating null-character when computing the maximal output size.
// The given length is only used in debug mode to ensure the buffer is big
// enough.
void double_to_ascii(double v, double_to_asci_mode mode, int requested_digits,
                     char *buffer, int buffer_length, bool *sign, int *length,
                     int *point);

#ifdef __cplusplus
}
#endif

#endif /* __DOUBLE_CONVERSION_DOUBLE_CONVERSION_C_H__ */