#pragma once

#include <memory>

class wxWindow;

namespace MarineNavi {

class CheckPathCase;
class RenderOverlay;

struct Dependencies {
std::shared_ptr<MarineNavi::CheckPathCase> CheckPathCase;
std::shared_ptr<MarineNavi::RenderOverlay> RenderOverlay;
wxWindow* OcpnCanvasWindow;
};

} // namespace MarineNavi