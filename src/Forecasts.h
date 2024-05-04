#pragma once

#include "csv_parser.h"
#include "common.h"

#include <wx/curl/http.h>

#include "ocpn_plugin.h"

#include <ctime>
#include <fstream>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

namespace MarineNavi {

enum class ForecastsSource{
    kEsimo = 0,
};

struct Forecast {
    time_t StartedAt;
    time_t FinishedAt;
    ForecastsSource Source;
};

struct ForecastRecord {
    time_t StartedAt;
    time_t Date;
    double Lat;
    double Lon;
    std::optional<double> WaveHeight;
    std::optional<double> SwellHeight;
};

class ForecastsProvider {
public:
    virtual void LoadForecasts() = 0;
    virtual Forecast GetForecast() = 0;
    virtual std::vector<ForecastRecord> GetRecords() = 0;
    virtual ~ForecastsProvider() = default;
};

class EsimoProvider : public ForecastsProvider {
public:
    EsimoProvider(std::string resourceId, std::optional<std::string> filter);

    void LoadForecasts() override;
    Forecast GetForecast() override;
    std::vector<ForecastRecord> GetRecords() override;
    ~EsimoProvider() override = default;

private:
    wxString SaveData(const std::string& data);

private:
    wxCurlHTTP curl_;
    std::string url;
    std::string responseBody_;
};

} // namespace MarineNavi
