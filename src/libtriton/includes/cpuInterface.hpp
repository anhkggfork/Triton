//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#ifndef TRITON_CPUINTERFACE_HPP
#define TRITON_CPUINTERFACE_HPP

#include <set>
#include <tuple>
#include <vector>

#include "instruction.hpp"
#include "memoryOperand.hpp"
#include "registerOperand.hpp"
#include "tritonTypes.hpp"



//! The Triton namespace
namespace triton {
/*!
 *  \addtogroup triton
 *  @{
 */

  //! The Architecture namespace
  namespace arch {
  /*!
   *  \ingroup triton
   *  \addtogroup arch
   *  @{
   */


    /*! \interface CpuInterface
        \brief This interface is used as abstract CPU interface. All CPU must use this interface. */
    class CpuInterface  {
      public:
        //! Destructor.
        virtual ~CpuInterface(){};

        //! The first function called when the a CPU is initialized.
        virtual void init(void) = 0;

        //! Clears the architecture states (registers and memory).
        virtual void clear(void) = 0;

        //! Returns true if the regId is a flag.
        /*!
            \param regId the register id.
        */
        virtual bool isFlag(triton::uint32 regId) const = 0;

        //! Returns true if the regId is a register.
        /*!
            \param regId the register id.
        */
        virtual bool isRegister(triton::uint32 regId) const = 0;

        //! Returns true if the regId is valid.
        /*!
            \param regId the register id.
        */
        virtual bool isRegisterValid(triton::uint32 regId) const = 0;

        //! Returns the max size (in byte) of the CPU registers (GPR).
        virtual triton::uint32 registerSize(void) const = 0;

        //! Returns the max size (in bit) of the CPU registers (GPR).
        virtual triton::uint32 registerBitSize(void) const = 0;

        //! Returns the id of the invalid CPU register.
        virtual triton::uint32 invalidRegister(void) const = 0;

        //! Returns the number of registers according to the CPU architecture.
        virtual triton::uint32 numberOfRegisters(void) const = 0;

        //! Returns all information about a register id.
        /*!
            \param reg the register id.
            \return std::tuple<name, b-high, b-low, parentId>
        */
        virtual std::tuple<std::string, triton::uint32, triton::uint32, triton::uint32> getRegisterInformation(triton::uint32 reg) const = 0;

        //! Returns all registers.
        virtual std::set<triton::arch::RegisterOperand*> getAllRegisters(void) const = 0;

        //! Returns all parent registers.
        virtual std::set<triton::arch::RegisterOperand*> getParentRegisters(void) const = 0;

        //! Disassembles the instruction according to the architecture.
        virtual void disassembly(triton::arch::Instruction& inst) const = 0;

        //! Builds the instruction semantics according to the architecture.
        virtual void buildSemantics(triton::arch::Instruction& inst) const = 0;

        //! Returns the last concrete value recorded of a memory access.
        virtual triton::uint8 getLastMemoryValue(triton::uint64 addr) const = 0;

        //! Returns the last concrete value recorded of a memory access.
        virtual triton::uint512 getLastMemoryValue(const triton::arch::MemoryOperand& mem) const = 0;

        //! Returns the last concrete values of a memory area.
        virtual std::vector<triton::uint8> getLastMemoryAreaValue(triton::uint64 baseAddr, triton::usize size) const = 0;

        //! Returns the last concrete value recorded of a register state.
        virtual triton::uint512 getLastRegisterValue(const triton::arch::RegisterOperand& reg) const = 0;

        //! Sets the last concrete value of a memory access.
        virtual void setLastMemoryValue(triton::uint64 addr, triton::uint8 value) = 0;

        //! Sets the last concrete value of a memory access.
        virtual void setLastMemoryValue(const triton::arch::MemoryOperand& mem) = 0;

        //! Sets the last concrete values of a memory area.
        virtual void setLastMemoryAreaValue(triton::uint64 baseAddr, const std::vector<triton::uint8>& values) = 0;

        //! Sets the last concrete values of a memory area.
        virtual void setLastMemoryAreaValue(triton::uint64 baseAddr, const triton::uint8* area, triton::usize size) = 0;

        //! Sets the last concrete value of a register state.
        virtual void setLastRegisterValue(const triton::arch::RegisterOperand& reg) = 0;

        //! Returns true if the range `[baseAddr:size]` is mapped into the internal memory representation. \sa getLastMemoryValue() and getLastMemoryAreaValue().
        virtual bool isMemoryMapped(triton::uint64 baseAddr, triton::usize size=1) = 0;

        //! Removes the range `[baseAddr:size]` from the internal memory representation. \sa isMemoryMapped().
        virtual void unmapMemory(triton::uint64 baseAddr, triton::usize size=1) = 0;
    };

  /*! @} End of arch namespace */
  };
/*! @} End of triton namespace */
};

#endif /* TRITON_CPUINTERFACE_HPP */
