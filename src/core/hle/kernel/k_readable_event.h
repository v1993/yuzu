// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/kernel/k_synchronization_object.h"
#include "core/hle/kernel/object.h"

union ResultCode;

namespace Kernel {

class KernelCore;
class KWritableEvent;

class KReadableEvent final : public KSynchronizationObject {
    friend class KWritableEvent;

public:
    ~KReadableEvent() override;

    std::string GetTypeName() const override {
        return "ReadableEvent";
    }
    std::string GetName() const override {
        return name;
    }

    static constexpr HandleType HANDLE_TYPE = HandleType::ReadableEvent;
    HandleType GetHandleType() const override {
        return HANDLE_TYPE;
    }

    /// Unconditionally clears the readable event's state.
    void Clear();

    /// Clears the readable event's state if and only if it
    /// has already been signaled.
    ///
    /// @pre The event must be in a signaled state. If this event
    ///      is in an unsignaled state and this function is called,
    ///      then ERR_INVALID_STATE will be returned.
    ResultCode Reset();

    void Signal();

    bool IsSignaled() const override;

    void Finalize() override {}

private:
    explicit KReadableEvent(KernelCore& kernel);

    bool is_signaled{};
    std::string name; ///< Name of event (optional)
};

} // namespace Kernel
