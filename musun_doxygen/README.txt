Doxygen documentation for MuSun MU/MTA source code
================

To update the documentation, run ./builddocs.sh. This will update
CVS and run doxygen. When completed, the new html tree will be
copied to /var/www/exp/MuSun/doxygen.

Output and errors will be logged to doxygen.log

The Doxygen config file is MuSunAnalysisCode.cfg.

A custom webpage layout is implemented with MuSunAnalysisCodeLayout.xml.


Testing the build
=================

To test changes, you can build in the testbuild/ directory. This creates
the html tree without copying to the website.

This can be used to test individual directories/files with the line in
the .cfg file:

INPUT = /home/mhmurray/doxygen/sourcecode/mu/src/uiuc/TPC
