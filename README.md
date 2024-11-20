# Ray Tracing Project

## Project Overview
This project involves the implementation of a ray tracing engine designed to render realistic 3D scenes by simulating the behavior of light. The engine supports features like calculating surface normals, rendering diffuse surfaces, and applying texture patterns such as checkered materials. It also optimizes rendering times through the use of bounding volume hierarchies (BVH).  
You can check out the [**AR_VR Assignment 1 Report.pdf**](./AR_VR%20Assignment%201%20Report.pdf) or the [**images** folder](./images/) to view detailed results and rendered outputs.

## Features Implemented
- **Diffuse Rendering**: Simulated realistic light interactions with diffuse surfaces.
- **Checkered Texturing**: Applied a procedural checkered pattern to objects.
- **Sampling Per Pixel (SPP)**: Incorporated adjustable sampling rates for anti-aliasing and smoother image quality.
- **Bounding Volume Hierarchy (BVH)**: Enhanced performance by implementing BVH for efficient ray-object intersection calculations.

## Testing and Results
### Normals Visualization
Visualized surface normals to ensure correctness of shading and light interaction calculations.

### Sampling Per Pixel (SPP)
- Tested with different SPP values to observe quality improvements in rendered scenes.
  - **SPP 50**: Render time ~83–117 seconds.
  - **SPP 200**: Render time ~335 seconds.
  - **SPP 400**: Render time ~805–899 seconds.

### Performance Optimization with BVH
- **Without BVH**: Render time ~144 seconds for specific scenes.
- **With BVH**: Render time reduced to ~88 seconds.

## Key Observations
1. Higher SPP values result in smoother images but at the cost of increased rendering time.
2. Using BVH significantly improves rendering efficiency, especially for complex scenes with multiple objects.
