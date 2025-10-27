#!/bin/bash
# Script para convertir un archivo WebM a frames XPM para el menú

if [ $# -eq 0 ]; then
    echo "Uso: $0 <archivo.webm> [fps]"
    echo "Ejemplo: $0 menu_animation.webm 10"
    exit 1
fi

VIDEO=$1
FPS=${2:-10}  # Por defecto 10 fps si no se especifica

# Crear directorio si no existe
mkdir -p menu_frames

# Convertir WebM a PNG frames (ffmpeg no soporta XPM directamente)
echo "Extrayendo frames del video..."
ffmpeg -i "$VIDEO" -vf "fps=$FPS,scale=800:600" menu_frames/frame_%04d.png

# Convertir PNG a XPM usando ImageMagick
echo "Convirtiendo PNG a XPM..."
cd menu_frames
for png in *.png; do
    xpm="${png%.png}.xpm"
    convert "$png" "$xpm"
    rm "$png"  # Eliminar PNG temporal
    echo "Convertido: $xpm"
done

# Renombrar para que sean frame_0.xpm, frame_1.xpm, etc.
counter=0
for xpm in frame_*.xpm; do
    mv "$xpm" "frame_$counter.xpm"
    counter=$((counter + 1))
done

echo "¡Conversión completada! $counter frames generados en menu_frames/"
