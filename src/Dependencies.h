#pragma once

#include <memory>

class wxWindow;

namespace MarineNavi {

class CheckPathCase;

struct Dependencies {
std::shared_ptr<CheckPathCase> CheckPathCase;
wxWindow* OcpnCanvasWindow;
};

} // namespace MarineNavi