#include <iostream>
#include <cmath>
using namespace std;

// ─────────────────────────────────────────
//  BASE CLASS
// ─────────────────────────────────────────
class Room {
protected:
    float length, width, area;
    float transport;

    void setDimensions() {
        cout << "Enter Length = ";  cin >> length;
        cout << "Enter Width  = ";  cin >> width;
        area = ceil(length * width);
        cout << "Area = " << area << " sqft\n";
    }

    void setTransport() {
        cout << "Enter Transport Charges = ";
        cin >> transport;
    }

    float laborByArea(float minLabor, float ratePerSqft) {
        return (area < 100) ? minLabor : ratePerSqft * area;
    }
};

// ─────────────────────────────────────────
//  CEILING
// ─────────────────────────────────────────
class Ceiling : public Room {
    float ceilingPrice, teePrice, crossPrice, anglePrice;
    int noTiles, noAngles, noTee, noCross, wire;
    float labor, cCeiling, cTee, cCross, cAngle, cWire, cHardware, total;

public:
    void setPrices() {
        setDimensions();
        cout << "Ceiling tile price = "; cin >> ceilingPrice;
        cout << "Tee price (rft)    = "; cin >> teePrice;
        cout << "Cross price (rft)  = "; cin >> crossPrice;
        cout << "Angle price        = "; cin >> anglePrice;
        setTransport();
    }

    void calculate() {
        noTiles  = ceil(area / 4);
        noAngles = ceil((2 * (length + width)) / 10);
        noTee    = ceil(area / 24);
        noCross  = ceil(area / 4);
        wire     = area * 5;
        labor    = (area < 200) ? 2500 : 12 * area;

        cCeiling  = noTiles   * ceilingPrice;
        cTee      = noTee     * teePrice  * 12;
        cCross    = noCross   * crossPrice * 2;
        cAngle    = noAngles  * anglePrice;
        cWire     = wire      * 0.35f;
        cHardware = area      * 3;
        total     = ceil(cCeiling + cTee + cCross + cAngle + cWire + cHardware + labor + transport);
    }

    void display() {
        cout << "\nCeiling  = " << noTiles  << " * " << ceilingPrice << " = " << cCeiling  << "/-\n";
        cout << "Tee      = " << noTee    << " * " << teePrice  << " * 12ft = " << cTee    << "/-\n";
        cout << "Cross    = " << noCross  << " * " << crossPrice << " * 2ft = " << cCross  << "/-\n";
        cout << "Angle    = " << noAngles << " * " << anglePrice << " = "        << cAngle  << "/-\n";
        cout << "Labor    = " << labor    << "/-\n";
        cout << "Wire     = " << cWire    << "/- (" << wire << "g)\n";
        cout << "Hardware = " << cHardware << "/-\n";
        cout << "Transport= " << transport << "/-\n";
        cout << "Total    = " << total     << "/-\n";
        cout << "Rate     = " << total / area << "/- per sqft\n";
    }
};

// ─────────────────────────────────────────
//  WOODEN FLOOR
// ─────────────────────────────────────────
class WoodenFloor : public Room {
    float pricePerSqft, jumbolon, skirtingReducer, siliconPrice;
    float costTiles, costJumbolon, costSkirting, costSilicon, labor, total;

public:
    void setPrices() {
        setDimensions();
        cout << "Wooden floor price/sqft = "; cin >> pricePerSqft;
        cout << "Jumbolon price/sqft     = "; cin >> jumbolon;
        cout << "Skirting/reducer price  = "; cin >> skirtingReducer;
        cout << "Silicon price           = "; cin >> siliconPrice;
        setTransport();
    }

    void calculate() {
        costTiles    = area * pricePerSqft + pricePerSqft * 2.6f;
        costJumbolon = area * jumbolon;
        costSkirting = ceil((2 * (length + width)) / 9 + 1) * skirtingReducer;
        labor        = (area < 100) ? 2500 : 15 * area;
        costSilicon  = ceil(0.01f * area) * siliconPrice;
        total        = ceil(costTiles + costJumbolon + costSkirting + labor + costSilicon + transport);
    }

    void display() {
        cout << "\nWooden tiles = " << costTiles    << "/-\n";
        cout << "Jumbolon     = " << costJumbolon << "/-\n";
        cout << "Skirting     = " << costSkirting << "/-\n";
        cout << "Labor        = " << labor        << "/-\n";
        cout << "Silicon      = " << costSilicon  << "/-\n";
        cout << "Transport    = " << transport    << "/-\n";
        cout << "Total        = " << total        << "/-\n";
        cout << "Rate         = " << total / area << "/- per sqft\n";
    }
};

// ─────────────────────────────────────────
//  VINYL FLOOR
// ─────────────────────────────────────────
class VinylFloor : public Room {
    float pricePerSqft;
    float costTiles, labor, total;

public:
    void setPrices() {
        setDimensions();
        cout << "Vinyl floor price/sqft = "; cin >> pricePerSqft;
        setTransport();
    }

    void calculate() {
        costTiles = area * pricePerSqft + pricePerSqft * 2;
        labor     = (area < 100) ? 3500 : 35 * area;
        total     = ceil(costTiles + labor + transport);
    }

    void display() {
        cout << "\nVinyl tiles = " << costTiles << "/-\n";
        cout << "Labor       = " << labor     << "/-\n";
        cout << "Transport   = " << transport << "/-\n";
        cout << "Total       = " << total     << "/-\n";
        cout << "Rate        = " << total / area << "/- per sqft\n";
    }
};

// ─────────────────────────────────────────
//  WALL PANELS  (uses wall width, not room area)
// ─────────────────────────────────────────
class WallPanels : public Room {
    float wallWidthFt, panelWidthIn;
    float panelPrice, golaPrice, clipPrice, elfiPrice, laborPerPanel;
    float noPanels, noGola, noClips, noElfi;
    float cPanels, cGola, cClips, cElfi, cHardware, labor, total;

public:
    void setPrices() {
        cout << "Wall width (ft)       = "; cin >> wallWidthFt;
        cout << "Panel width (inches)  = "; cin >> panelWidthIn;
        cout << "Price per panel       = "; cin >> panelPrice;
        cout << "Gola price            = "; cin >> golaPrice;
        cout << "Clip price            = "; cin >> clipPrice;
        cout << "Elfi price            = "; cin >> elfiPrice;
        cout << "Labor per panel       = "; cin >> laborPerPanel;
        setTransport();
    }

    void calculate() {
        noPanels  = ceil((wallWidthFt * 12) / panelWidthIn);
        noGola    = floor(noPanels / 2);
        noClips   = ceil((noPanels * 4) / 25.0f);
        noElfi    = ceil(0.05f * noPanels);

        cPanels   = noPanels * panelPrice;
        cClips    = noClips  * clipPrice;
        cGola     = noGola   * golaPrice;
        cElfi     = noElfi   * elfiPrice;
        cHardware = noPanels * 5;
        labor     = (noPanels < 25) ? 3000 : noPanels * laborPerPanel;
        total     = ceil(cPanels + cClips + cGola + cElfi + cHardware + labor + transport);
    }

    void display() {
        cout << "\nPanels    = " << cPanels   << "/-\n";
        cout << "Clips     = " << cClips    << "/-\n";
        cout << "Gola      = " << cGola     << "/-\n";
        cout << "Elfi      = " << cElfi     << "/-\n";
        cout << "Hardware  = " << cHardware << "/-\n";
        cout << "Labor     = " << labor     << "/-\n";
        cout << "Transport = " << transport << "/-\n";
        cout << "Total     = " << total     << "/-\n";
    }
};

// ─────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────
int main() {
    int choice;
    cout << "1. Ceiling  2. Wooden Floor  3. Vinyl Floor  4. Wall Panels\n";
    cin >> choice;

    if (choice == 1) { Ceiling     c; c.setPrices(); c.calculate(); c.display(); }
    if (choice == 2) { WoodenFloor w; w.setPrices(); w.calculate(); w.display(); }
    if (choice == 3) { VinylFloor  v; v.setPrices(); v.calculate(); v.display(); }
    if (choice == 4) { WallPanels  w; w.setPrices(); w.calculate(); w.display(); }

    return 0;
}
