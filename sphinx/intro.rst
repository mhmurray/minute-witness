LtFit, a MuSun lifetime fitting library
=======================================

LtFit is awesome

Fitting Classes
---------------

The classes that inherit from ``TLifetimeFitBase`` are as follows:

* ``TLifetimeFitMuMinusExponential``
* ``TLifetimeFitMuPlusExpRelaxation``
* ``TLifetimeFitMuPlusGaussRelaxation``
* ``TLifetimeFitMuMinusMC``

Each class is fitting a different function, or using a different
blinding or fitting strategy. For instance, they all contain the 
methods::

  DoFit()
  GuessInitialParameters()

The constructor is where the fit range is specified.

Properties of classes
^^^^^^^^^^^^^^^^^^^^^

=================================  =============  ==========================
Class                              Blinding       FitFunction
=================================  =============  ==========================
TLifetimeFitMuMinusExponential     :math:`\mu^-`  :math:`N R Exp[-R t] + B`
TLifetimeFitMuPlusExpRelaxation    :math:`\mu^+`  :math:`N R Exp[-R t] [1 + Exp[-R t] [ A_{Sin} Sin(\omega t) + A_{Cos} Cos(\omega t)]] + B`
TLifetimeFitMuPlusGaussRelaxation    mu+          :math:`N R Exp[-R t] + B`
TLifetimeFitMuMinusMC               none          :math:`N R Exp[-R t] + B`
=================================  =============  ==========================
