This fun little project is a trial on a ray tracer app.
The concept it follows is that we shoot rays from the camera, through a viewport and then based on the objects the rays intercept a color is calculated for every pixel of the viewport the rays pass through.
The rays have a random change to be reflected in a random way, so as to simulate lighting. Based on the absorbtion of light in the system, shadows appear on the image of the viewport.

The code follows a tutorial called "Ray tracing in a weekend" or sth similar. But its been changed a bit, so that the camera is able to move with *wasd* and rotated with *qe*. It now looks like a little videogame environment, which sadly runs too slow, as it runs on CPU and is completely unoptimized.
