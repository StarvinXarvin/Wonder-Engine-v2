#include "Primitive.h"
#include "..\MyGameEditor\Globals.h"

Cube::Cube(): 
	a(-1, -1, 1),
	b(1, -1, 1),
	c(1, 1, 1),
	d(-1, 1, 1),
	e(-1, -1, -1),
	f(1, -1, -1),
	g(1, 1, -1),
	h(-1, 1, -1) 
{}

Sphere::Sphere(){

    for (int i = 0; i <= num_subdivisions; ++i) {
        float lat0 = PI * (-0.5f + (i - 1) / num_subdivisions);
        float z0 = radius * sin(lat0);
        float zr0 = radius * cos(lat0);

        float lat1 = PI * (-0.5f + (i) / num_subdivisions);
        float z1 = radius * sin(lat1);
        float zr1 = radius * cos(lat1);

        for (int j = 0; j <= num_subdivisions; ++j) {
            float lng = 2 * PI * (j - 1) / num_subdivisions;
            float x = cos(lng);
            float y = sin(lng);

            vertices.push_back(x * zr0);
            vertices.push_back(y * zr0);
            vertices.push_back(z0);

            vertices.push_back(x * zr1);
            vertices.push_back(y * zr1);
            vertices.push_back(z1);
        }
    }
}