#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif  // precompiled headers

#include "ShipDriver_pi.h"
#include "ocpn_plugin.h"

class ShipDriver_pi;
class Dlg;

using namespace std;

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void* ppimgr) {
  return new ShipDriver_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p) { delete p; }

//---------------------------------------------------------------------------------------------------------
//
//    ShipDriver PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

#include "icons.h"

//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

/**
 * Load a icon, possibly using SVG
 * Parameters
 *  - api_name: Argument to GetPluginDataDir()
 *  - icon_name: Base name of icon living in data/ directory. When using
 *    SVG icon_name.svg is used, otherwise icon_name.png
 */

static wxBitmap load_plugin(const char* icon_name, const char* api_name) {
  wxBitmap bitmap;
  wxFileName fn;
  auto path = GetPluginDataDir(api_name);
  fn.SetPath(path);
  fn.AppendDir("data");
  fn.SetName(icon_name);
#ifdef ocpnUSE_SVG
  wxLogDebug("Loading SVG icon");
  fn.SetExt("svg");
  const static int ICON_SIZE = 48;  // FIXME: Needs size from GUI
  bitmap = GetBitmapFromSVGFile(fn.GetFullPath(), ICON_SIZE, ICON_SIZE);
#else
  wxLogDebug("Loading png icon");
  fn.SetExt("png");
  path = fn.GetFullPath();
  if (!wxImage::CanRead(path)) {
    wxLogDebug("Initiating image handlers.");
    wxInitAllImageHandlers();
  }
  wxImage panelIcon(path);
  bitmap = wxBitmap(panelIcon);
#endif
  wxLogDebug("Icon loaded, result: %s", bitmap.IsOk() ? "ok" : "fail");
  return bitmap;
}

ShipDriver_pi::ShipDriver_pi(void* ppimgr) : opencpn_plugin_118(ppimgr) {
  // Create the PlugIn icons
  initialize_images();
  m_panelBitmap = load_plugin("shipdriver_panel_icon", "ShipDriver_pi");
}

ShipDriver_pi::~ShipDriver_pi(void) {
  delete _img_ShipDriverIcon;
}

int ShipDriver_pi::Init(void) {
  AddLocaleCatalog("opencpn-ShipDriver_pi");
  return 0;
  // return (WANTS_OVERLAY_CALLBACK | WANTS_OPENGL_OVERLAY_CALLBACK |
  //         WANTS_TOOLBAR_CALLBACK | INSTALLS_TOOLBAR_TOOL | WANTS_CURSOR_LATLON |
  //         WANTS_NMEA_SENTENCES | WANTS_AIS_SENTENCES | WANTS_PREFERENCES |
  //         WANTS_PLUGIN_MESSAGING | WANTS_CONFIG);
}

bool ShipDriver_pi::DeInit(void) {
  return true;
}

int ShipDriver_pi::GetAPIVersionMajor() { return atoi(API_VERSION); }

int ShipDriver_pi::GetAPIVersionMinor() {
  std::string v(API_VERSION);
  size_t dotpos = v.find('.');
  return atoi(v.substr(dotpos + 1).c_str());
}

int ShipDriver_pi::GetPlugInVersionMajor() { return PLUGIN_VERSION_MAJOR; }

int ShipDriver_pi::GetPlugInVersionMinor() { return PLUGIN_VERSION_MINOR; }

int GetPlugInVersionPatch() { return PLUGIN_VERSION_PATCH; }

int GetPlugInVersionPost() { return PLUGIN_VERSION_TWEAK; };

const char* GetPlugInVersionPre() { return PKG_PRERELEASE; }

const char* GetPlugInVersionBuild() { return PKG_BUILD_INFO; }

wxBitmap* ShipDriver_pi::GetPlugInBitmap() { return &m_panelBitmap; }

wxString ShipDriver_pi::GetCommonName() { return PLUGIN_API_NAME; }

wxString ShipDriver_pi::GetShortDescription() { return PKG_SUMMARY; }

wxString ShipDriver_pi::GetLongDescription() { return PKG_DESCRIPTION; }
