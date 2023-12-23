# Teacher-Function: y = |x|
# Output-Function: Sigmoid
# Batch Size: 1 sample (direct learning)

# Eigener Python-Code für die Berechnung
# der Ausgabefunktion
#
# Variablen:
# z : Aktivierung des Neurons
# c : Steilheit der Fermi-Funktion
#
# Folgende Funktionen können sinnvoll sein:
# exp() -> berechnet die e-Funktion
# min(a,b) - gibt kleineren Wert zurück
# max(a,b) - gibt größeren Werte zurück

# Berechnen Sie die Variable y, für die
# ausgewählte Ausgabefunktion

import numpy
y = 1/(1+numpy.exp(-c*z))
