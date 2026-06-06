#!/bin/bash
# Gemini generated script to run all scene files
# If the scene takes too long to render you can skip using Ctrl + C
# Define the scenes directory
SCENES_DIR="scenes"

# Check if scenes directory exists
if [ ! -d "$SCENES_DIR" ]; then
    echo "Error: '$SCENES_DIR' directory not found!"
    exit 1
fi

echo "========================================"
echo " Starting Raytracer Bulk Render"
echo "========================================"

# Find all .xml files, excluding partial components inside three_spheres
find "$SCENES_DIR" -type f -name "*.xml" | while read -r scene; do
    
    # Skip helper XML files that aren't standalone scenes
    filename=$(basename "$scene")
    if [[ "$filename" == "materials.xml" || "$filename" == "geometry.xml"]]; then
        echo "Skipping component file: $scene"
        continue
    fi

    echo "----------------------------------------"
    echo "Running: just run $scene"
    echo "----------------------------------------"
    
    # Execute the command
    just run "$scene"
    
    # Optional: Check if the render succeeded
    if [ $? -eq 0 ]; then
        echo "Finished successfully: $scene"
    else
        echo "Failed rendering: $scene"
    fi
done

echo "========================================"
echo " Bulk rendering complete!"
echo "========================================"