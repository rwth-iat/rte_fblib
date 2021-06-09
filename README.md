# ACPLT/RTE function block libraries

This repository is part of the ACPLT/OV runtime environment (RTE).
It provides additional libraries with general purpose and special purpose function block classes, to be used with OV's function block system (FB).
For compiling and using these libraries, the APLT/RTE core project is required: https://github.com/acplt/rte

This Git repository is designed as a "library project", which can included as a subdirectory into an application specific OV project (e.g. as a Git submodule).
See OV's readme file for more information about recommended project structures: https://github.com/acplt/rte#project-structure


## Included OV libraries

* `iec61131stdfb` – standard function block types according to IEC 61131-3
* `vdivde3696` – standard function block types according to VDE/VDE 3696-2
* `ACPLTlab003lindyn` – function block types for simple dynamic functions (differentiation, integration, PT1)
* `fbcomlib` – function block types for communication with other systems via ACPLT/KS
* `opcuafb` – function block types for communicatino with OPC UA (IEC 62541) servers according to PLCopen
* `SSChelper` – serveral function block types to support working with Sequential State Charts (SSCs)
