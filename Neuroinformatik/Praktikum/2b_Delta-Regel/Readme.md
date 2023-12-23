# Delta Regel - 2b

## externe Links
-  [Delta Regel](https://www.tu-ilmenau.de/universitaet/fakultaeten/fakultaet-informatik-und-automatisierung/profil/institute-und-fachgebiete/institut-fuer-technische-informatik-und-ingenieurinformatik/fachgebiet-neuroinformatik-und-kognitive-robotik/lehre/lehrveranstaltungen/delta-regel-1)
-  [Bedienungsanleitung](https://www.tu-ilmenau.de/universitaet/fakultaeten/fakultaet-informatik-und-automatisierung/profil/institute-und-fachgebiete/institut-fuer-technische-informatik-und-ingenieurinformatik/fachgebiet-neuroinformatik-und-kognitive-robotik/lehre/lehrveranstaltungen/delta-regel-1-1)
-  [Aufgabenstellung](https://www.tu-ilmenau.de/universitaet/fakultaeten/fakultaet-informatik-und-automatisierung/profil/institute-und-fachgebiete/institut-fuer-technische-informatik-und-ingenieurinformatik/fachgebiet-neuroinformatik-und-kognitive-robotik/lehre/lehrveranstaltungen/delta-regel-1-1-1)



## Interface
![](/Neuroinformatik/Praktikum/2b_Delta-Regel/praktikum.png)

## Lösung
### Sigmoid 
#### Output Function
[Source Code](/Neuroinformatik/Praktikum/2b_Delta-Regel/sigmoid_output.py)
```python
import numpy
y = 1 / (1 + numpy.exp(-c*z))
```
#### Output Function Derivate
[Source Code](/Neuroinformatik/Praktikum/2b_Delta-Regel/sigmoid_output_function_derivate.py)
```python
dy_dz = c * y * (1-y)
```
### RelU  
#### RelU Output Function
[Source Code](/Neuroinformatik/Praktikum/2b_Delta-Regel/rel_output_function.py)
```python
y = max(0,z)
```
#### RelU Output Function Derivate
[Source Code](/Neuroinformatik/Praktikum/2b_Delta-Regel/rel_output_function_derivate.py)
```python
if z < 0:
    dy_dz = 0
else:
    dy_dz = 1
```
