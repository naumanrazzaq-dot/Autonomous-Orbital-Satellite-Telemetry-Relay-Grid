#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class OrbitalAsset {
protected:
    string satelliteID;
    bool inOrbit;

public:
    static int activeSatellites;

    OrbitalAsset(string id) : satelliteID(id), inOrbit(true) {
        activeSatellites++;
    }

    virtual ~OrbitalAsset() {
        activeSatellites--;
    }

    virtual void transmitTelemetry() = 0;
};

int OrbitalAsset::activeSatellites = 0;

class SolarArrayModule : virtual public OrbitalAsset {
protected:
    double powerOutputKilowatts;

public:
    SolarArrayModule(string id, double power) : OrbitalAsset(id), powerOutputKilowatts(power) {}

    void checkSolarArray() {
        cout << "Solar array [" << satelliteID << "] generating: " << powerOutputKilowatts << " kW." << endl;
    }
};

class TransponderRelayModule : virtual public OrbitalAsset {
protected:
    double signalFrequencyGHz;

public:
    TransponderRelayModule(string id, double frequency) : OrbitalAsset(id), signalFrequencyGHz(frequency) {}

    void checkTransponder() {
        cout << "Transponder [" << satelliteID << "] locked at: " << signalFrequencyGHz << " GHz." << endl;
    }
};

class GeoRelaySatellite : public SolarArrayModule, public TransponderRelayModule {
private:
    int activeGroundLinks;

public:
    GeoRelaySatellite(string id, double power, double frequency, int links)
        : OrbitalAsset(id),
          SolarArrayModule(id, power),
          TransponderRelayModule(id, frequency),
          activeGroundLinks(links) {}

    ~GeoRelaySatellite() {
        cout << "Satellite " << satelliteID << " de-orbited and telemetry terminated." << endl;
    }

    void transmitTelemetry() override {
        cout << "\n--- Orbital Satellite Telemetry Report: " << satelliteID << " ---" << endl;
        checkSolarArray();
        checkTransponder();
        cout << "Active Ground Links: " << activeGroundLinks << endl;
        cout << "Orbital Status: Nominal" << endl;
    }
};

int main() {
    OrbitalAsset* sat = new GeoRelaySatellite("SAT-GEO-12", 18.5, 28.4, 340);

    sat->transmitTelemetry();

    cout << "\nActive Orbital Satellites: " << OrbitalAsset::activeSatellites << endl;

    delete sat;

    cout << "Active Satellites After De-orbit: " << OrbitalAsset::activeSatellites << endl;

    return 0;
}
