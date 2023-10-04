
#pragma once

namespace ivd
{

class section_interface
{
public:
    virtual ~section_interface() = default;

public:
    virtual bool initialize() { return true;}
    virtual void finalize() {}
};

} // namespace ivd