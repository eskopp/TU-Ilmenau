# Teacher-Function: y = |x|
# Output-Function: RelU
# Batch Size: 1 sample (direct learning)

# Eigener Python-Code für die Berechnung
# der Ableitung der Ausgabefunktion
#
# Variablen:
# z : Aktivierung des Neurons
#
# Hinweis:
# Überprüfen Sie für die Ableitung
# den Wertebereich der Aktivierung z

# Berechnen Sie die Variable dy_dz, für die
# Ableitung der Ausgabefunktion

if z < 0:
    dy_dz = 0
else:
    dy_dz = 1