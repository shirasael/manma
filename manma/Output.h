#pragma once

#define PRINT(format, ...) try {printf(format##"\n", __VA_ARGS__);} catch (...) {};
