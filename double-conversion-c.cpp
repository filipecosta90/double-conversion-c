#include "double-conversion-c.h"
#include "double-conversion/double-conversion.h"
#include <stdbool.h>

void double_to_asci(double v, double_to_asci_mode dtoa_mode,
                    int requested_digits, char *buffer, int buffer_length,
                    bool *sign, int *length, int *point) {
  double_conversion::DoubleToStringConverter::DtoaMode mode =
      double_conversion::DoubleToStringConverter::SHORTEST;
  switch (dtoa_mode) {
  case SHORTEST:
    mode = double_conversion::DoubleToStringConverter::SHORTEST;
    break;
  case SHORTEST_SINGLE:
    mode = double_conversion::DoubleToStringConverter::SHORTEST_SINGLE;
    break;
  case FIXED:
    mode = double_conversion::DoubleToStringConverter::FIXED;
    break;
  case PRECISION:
    mode = double_conversion::DoubleToStringConverter::PRECISION;
    break;
  }
  double_conversion::DoubleToStringConverter::DoubleToAscii(
      v, mode, requested_digits, buffer, buffer_length, sign, length, point);
}