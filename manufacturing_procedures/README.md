# Smartfin v3 Manufacturing Procedures
## PCB Bringup
### Required Parts
- 1x Smartfin v3 rev a PCB
- 1x Temperature Sensor rev b PCB
- 1x Particle Cellular Antenna
- 1x GPS Antenna
- 1x Battery
- 5x SS Pins (2mm dia, 6mm len)

### Required Tools
- Smartfin USB Test Harness
- Laptop/PC with Chrome 61 or later (Win, Linux, or MacOS), Visual Studio Code, and a serial terminal
- Soldering Rework Station (if wiring version is greater than 0)

### Procedure
1. Apply wiring updates/hardware mods to latest revision (currently xa0)
2. Connect the USB Test Harness from the DUT to the PC
3. In Chrome, log in to Particle as appropriate
4. In Chrome, navigate to https://docs.particle.io/tools/doctor/
5. Follow the instructions from Particle Doctor until the DUT is fully provisioned and claimed
6. Open VS Code to the smartfin-fw3 repo (https://github.com/UCSD-E4E/smartfin-fw3)
7. Flash application and DeviceOS to the DUT
8. Open a serial terminal and connect to the DUT
9. Drop into the CLI using the key sequence `#CLI`.
10. Select `Manufacturing Test`
11. If any test does not pass, notify engineering team and stop here
12. Copy the Device ID
13. Log into https://console.particle.io/smartfin-v3-21900/devices
14. Click `Add Devices`
15. Add this DUT using the device ID
16. Pass the DUT to the potting team.

## Potting Team
### Supplies
- PVA
- Resin
- Slow Hardener

### Equipment
Plastic tool for clearing air relief channels


### Procedure
#### Preparing the Mold
1. Ensure that the mold is clean by rinsing all contact surfaces with water and drying with a microfiber towel

* Use wax to cover the pin holes in the mold.
* Use wax to fill in the "air escape" cracks.
* Add the 3-D printed spacer in the lower area of the fin (where there is a space for a screw to secure the fin onto the surfboard)

2. Using a brush, or spray tool if not available, to apply a coating of PVA to all contact surfaces

* Have 3 coats of PVA (wait for each coat to dry for about 15 minutes each).
* Inlay fiberglass and electronics here
* Coat the spacer with PVA as well

3. Lay the "top" piece of the mold onto the "bottom" piece and check proper alignment 

4. Use bolts to secure the top piece to the bottom piece, switching between bolts frequently to ensure an even application

5. Rotate the mold so that the resin inlets are facing upwards

6. Prepare the resin
- 252 mL resin, 42 ml hardener
- Mix until consistent, then use vacuum pot to remove air bubbles

7. Fill resin to top of inlets
- Add a small amount (~50mL), then tilt the mold side to side to ensure there are no air pockets in the tip of the fin before pouring the remaining resin.
- Vibrate mold to release large air pockets.

8. Transfer to Pressure Vessel

#### Using the Pressure Vessel
1. Line the bottom of the pressure vessel with cardboard or another expendable material to account for any leaking from the mold

2. Place the mold in the vessel so that the resin inlets are facing upwards

3. Check that the pressure vessel gasket is intact and clear of debris

4. Check that the edge of the pressure vessel is intact and clear of debris

5. Begin tightening down the lid of the pressure vessel, hand tightening screws on opposing sides at the same time

6. Once light resistance is met, begin to tighten each screw one quarter turn each, moving in a diamond pattern across the screws

7. Stop tightening once all four screws cannot be hand tightened

8. Ensure that the inlet regulator is closed and locked, and that the inlet valve and bleed valves are closed

9. Attach air hose to the pressure vessel inlet and slowly open the air hose valve

10. Slowly open the inlet valve, and then turn the regulator to begin pressurizing the vessel to 60 psi

11. Once desired pressure is reached, close the regulator fully and lock it

12. Close the inlet valve, then the air hose valve, and then slowly open the bleed valves to remove excess pressure from the air hose

13. Detach the air hose from the pressure vessel

#### Post-Processing
* A minimum of 24 hours for resin to cure is suggested.

1. Slowly open the pressure outlet valve
2. Loosen the wing nuts on the pressure pot
3. Fully detach lid screws, then remove the lid
4. Pull the mold and expendable material from the vessel
5. Lay the mold on a surface with the bottom piece down
6. Remove all bolts securing the top piece to the bottom piece
7. Slowly screw bolts into the threaded holes of the top piece to slowly pry the top piece from the bottom piece, switching between bolts frequently.  As these bolts are inserted, rock the mold top back and forth to separate the halves.  Advance the bolts until the mold halves are fully separated and you can fully separate the halves by hand.
8. Remove the top piece of the mold from the bottom piece, applying only a light amount of force if necessary
9. Inspect the quality of the fin
10. Wash the fin to remove remaining PVA
11. Use a fine pitch saw and file to remove excess resin from the fin
12. Drill a 3/16 in hole for the assigned pin hole on the nose of the fin, and insert spring pin.
13. Drill a 3/16 in hole for the screw hole on the tail of the fin.
14. Use a plastic tool to remove any resin remaining in the relief channels
15. Clean the entire surface of the mold using water
