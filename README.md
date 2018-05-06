Graphics homework
===

Ray trace

Distributed ray trace

Photon mapping 

## Components

### Basic types
* `double` float dealers

### Geometry classes

* `point3` 3d points
* `vector` 3d vectors
* `line` 3d lines shown by base point and direction 
* `plane` 3d plane shown in base point and normal vector

### Physics classes

* `object` father class of any shape in the scene
* `colors` color in RGB (TODO: A)
* `triangle` triangle shown in 3 points and its color and smooth

### Construction classes

* `camera` takes picture and renders (TODO: `imwrite` not useable)
* `scene` stores every object in the scene

