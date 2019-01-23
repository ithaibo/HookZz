#ifndef ARCH_X64_REGISTERS
#define ARCH_X64_REGISTERS

#include "core/arch/x64/constants-x64.h"
#include "macros.h"
#include "core/arch/Cpu.h"

namespace zz {
namespace x64 {

#define GENERAL_REGISTERS(V) \
  V(rax)                     \
  V(rcx)                     \
  V(rdx)                     \
  V(rbx)                     \
  V(rsp)                     \
  V(rbp)                     \
  V(rsi)                     \
  V(rdi)                     \
  V(r8)                      \
  V(r9)                      \
  V(r10)                     \
  V(r11)                     \
  V(r12)                     \
  V(r13)                     \
  V(r14)                     \
  V(r15)
        enum RegisterCode {
#define REGISTER_CODE(R) kRegCode_##R,
            GENERAL_REGISTERS(REGISTER_CODE)
#undef REGISTER_CODE
            kRegAfterLast
        };

class CPURegister : RegisterBase {
public:
  enum RegisterType {

    kInvalid
  };

  constexpr CPURegister(int code, int size, RegisterType type) : RegisterBase(code), reg_size_(size), reg_type_(type) {
  }

  static constexpr CPURegister Create(int code, int size, RegisterType type) {
    return CPURegister(code, size, type);
  }

  static constexpr CPURegister InvalidRegister() {
    return CPURegister(0, 0, kInvalid);
  }

  bool Is(const CPURegister &reg) const {
    return (reg.reg_code_ == this->reg_code_);
  }

  bool Is64Bits() const {
    return reg_size_ == 64;
  }

  RegisterType type() const {
    return reg_type_;
  }

  int32_t code() const {
    return reg_code_;
  };
public:
    bool is_byte_register() const { return reg_code_ <= 3; }
    // Return the high bit of the register code as a 0 or 1.  Used often
    // when constructing the REX prefix byte.
    int high_bit() const { return reg_code_ >> 3; }
    // Return the 3 low bits of the register code.  Used when encoding registers
    // in modR/M, SIB, and opcode bytes.
    int low_bits() const { return reg_code_ & 0x7; }
private:
  RegisterType reg_type_;
  int reg_size_;
};

typedef CPURegister Register;

        typedef Register CPURegister;

#define DECLARE_REGISTER(R) constexpr Register R = Register::Create(kRegCode_##R, 64, CPURegister::kInvalid);
        GENERAL_REGISTERS(DECLARE_REGISTER)
#undef DECLARE_REGISTER

#ifdef _WIN64
        // Windows calling convention
constexpr Register arg_reg_1 = rcx;
constexpr Register arg_reg_2 = rdx;
constexpr Register arg_reg_3 = r8;
constexpr Register arg_reg_4 = r9;
#else
        // AMD64 calling convention
        constexpr Register arg_reg_1 = rdi;
        constexpr Register arg_reg_2 = rsi;
        constexpr Register arg_reg_3 = rdx;
        constexpr Register arg_reg_4 = rcx;
#endif  // _WIN64


#define DOUBLE_REGISTERS(V) \
  V(xmm0)                   \
  V(xmm1)                   \
  V(xmm2)                   \
  V(xmm3)                   \
  V(xmm4)                   \
  V(xmm5)                   \
  V(xmm6)                   \
  V(xmm7)                   \
  V(xmm8)                   \
  V(xmm9)                   \
  V(xmm10)                  \
  V(xmm11)                  \
  V(xmm12)                  \
  V(xmm13)                  \
  V(xmm14)                  \
  V(xmm15)

#define FLOAT_REGISTERS DOUBLE_REGISTERS
#define SIMD128_REGISTERS DOUBLE_REGISTERS

        constexpr bool kPadArguments = false;
        constexpr bool kSimpleFPAliasing = true;
        constexpr bool kSimdMaskRegisters = false;

        enum DoubleRegisterCode {
#define REGISTER_CODE(R) kDoubleCode_##R,
            DOUBLE_REGISTERS(REGISTER_CODE)
#undef REGISTER_CODE
            kDoubleAfterLast
        };

        class XMMRegister : public RegisterBase {

        public:
            // Return the high bit of the register code as a 0 or 1.  Used often
            // when constructing the REX prefix byte.
            int high_bit() const { return reg_code_ >> 3; }
            // Return the 3 low bits of the register code.  Used when encoding registers
            // in modR/M, SIB, and opcode bytes.
            int low_bits() const { return reg_code_ & 0x7; }

        };

    } // namespace x64
} // namespace zz

#endif