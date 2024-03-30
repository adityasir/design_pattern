#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;
/*
 * Base class template for representing different numerical types with uint_8 manipulation
 *  - Employs CRTP (Curiously Recurring Template Pattern) to leverage concrete type information
 *  - Provides a virtual getValue() function for retrieving uint_8 representation
 *  - Simulate CRTP pattern by providing a static function in the base class \
 *    for packing signal values into the derived class type
 */
template <typename Derived>
class HexBase {
public:
    virtual vector<uint8_t> getValue() const = 0; // Pure virtual function
    static Derived packSignal(const vector<uint8_t>& values) {
        return Derived::packSignal(values);
    }
};

// Class for representing 64-bit unsigned integers
class UINT64 : public HexBase<UINT64> {
private:
    uint64_t value;

public:
    UINT64(const uint64_t val) : value(val) {}

    vector<uint8_t> getValue() const override {
        vector<uint8_t> hexValues;
        for (int i = 7; i >= 0; --i) {
            hexValues.push_back((value >> (i * 8)) & 0xFF);
        }
        return hexValues;
    }

    static UINT64 packSignal(const vector<uint8_t>& values) {
        uint64_t packed_signal = 0;
        uint8_t base = 56;
        for (auto& val : values) {
            packed_signal |= static_cast<uint64_t>(val) << base;
            base -= 8;
        }
        return UINT64(packed_signal);
    }
};

// Class for representing 32-bit unsigned integers
class UINT32 : public HexBase<UINT32> {
private:
    uint32_t value;

public:
    UINT32(const uint32_t val) : value(val) {}

    vector<uint8_t> getValue() const override {
        vector<uint8_t> hexValues;
        for (int i = 3; i >= 0; --i) {
            hexValues.push_back((value >> (i * 8)) & 0xFF);
        }
        return hexValues;
    }

    static UINT32 packSignal(const vector<uint8_t>& values) {
        uint32_t packed_signal = 0;
        uint8_t base = 24;
        for (auto& val : values) {
            packed_signal |= static_cast<uint32_t>(val) << base;
            base -= 8;
        }
        return UINT32(packed_signal);
    }
};

int main() {
    std::cout << std::endl << "Simulate RADAR Signal \n";
    vector<uint8_t> RSValues{ 100, 60, 45, 2, 80, 5, 10, 127 };
    UINT64 radar_signal = UINT64::packSignal(RSValues);
    auto RSVec = radar_signal.getValue();

    vector<string> RSFields{ "Distance", "Speed", "Angle", "Target Type", "Signal Strength", "Doppler Shift", "Range Rate", "Identification Info" };
    for (size_t i = 0; i < RSVec.size(); ++i) {
        cout << RSFields[i] << " " << static_cast<int>(RSVec[i]) << endl;
    }

    std::cout << std::endl << "Simulate Vision and Depth Sensing sensor Singal \n";
    vector<uint8_t> VDValues{ 124, 126, 127, 128 };
    UINT32 vision_depth_signal = UINT32::packSignal(VDValues);
    auto VDVec = vision_depth_signal.getValue();

    vector<string> VDFields{ "RED", "GREEN", "BLUE", "DEPTH" };
    for (size_t i = 0; i < VDVec.size(); ++i) {
        cout << VDFields[i] << " " << static_cast<int>(VDVec[i]) << endl;
    }

    return 0;
}

