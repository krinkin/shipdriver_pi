#include "Dependencies.h"

#include "CheckPathCase.h"
#include "RenderOverlay.h"
#include "DbClient.h"

namespace MarineNavi {

Dependencies CreateDependencies(wxWindow* ocpnCanvasWindow) {
    Dependencies deps;
    deps.OcpnCanvasWindow = ocpnCanvasWindow;
    deps.CheckPathCase = std::make_shared<MarineNavi::CheckPathCase>();
    deps.RenderOverlay = std::make_shared<MarineNavi::RenderOverlay>(deps);
    deps.Db = CreateDatabase("marinenavi.db");
    deps.DbClient = std::make_shared<DbClient>(deps.Db);
    return deps;
}

} // namespace MarineNavi
