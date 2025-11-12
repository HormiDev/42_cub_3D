/* ************************************************************************** */
/*                                                                            */
/*                DEMO DE TRANSPARENCIA - RESUMEN                             */
/*                                                                            */
/* ************************************************************************** */

================================================================================
  ✅ PRUEBA DE TRANSPARENCIA IMPLEMENTADA
================================================================================

He añadido una demostración visual de transparencia en el MENÚ de tu juego.

--------------------------------------------------------------------------------
ARCHIVOS MODIFICADOS:
--------------------------------------------------------------------------------

1. ✅ src_bonus/ft_image_transparent.c
   - Funciones de transparencia adaptadas a la norma de 42
   - ft_draw_transparent_image() lista para usar

2. ✅ includes/cub_3d_bonus.h
   - Prototipo añadido: void ft_draw_transparent_image(...)

3. ✅ src_bonus/ft_menu.c
   - Añadidas funciones de demo:
     * ft_create_transparent_box() - Crea cuadrados con transparencia
     * ft_draw_transparent_demo() - Dibuja 3 cuadrados transparentes

--------------------------------------------------------------------------------
¿QUÉ VERÁS AL EJECUTAR?
--------------------------------------------------------------------------------

Cuando ejecutes tu juego y veas el MENÚ, aparecerán 3 cuadrados semi-transparentes:

  🟥 CUADRADO ROJO (128 alpha - 50% transparente)
     Posición: (100, 200)
     Tamaño: 200x150

  🟩 CUADRADO VERDE (180 alpha - 70% opaco)
     Posición: (400, 350)
     Tamaño: 250x100

  🟦 CUADRADO AZUL (80 alpha - 31% opaco)
     Posición: esquina superior derecha
     Tamaño: 300x200

Estos cuadrados se dibujan SOBRE la animación del menú, permitiendo ver
el fondo a través de ellos según su nivel de transparencia.

--------------------------------------------------------------------------------
CÓMO FUNCIONA:
--------------------------------------------------------------------------------

1. Se crean las texturas con canal alpha la primera vez
2. En cada frame del menú, se llama a ft_draw_transparent_demo()
3. Esta función usa ft_draw_transparent_image() para dibujar cada cuadrado
4. El alpha blending mezcla los colores automáticamente

--------------------------------------------------------------------------------
NIVELES DE ALPHA:
--------------------------------------------------------------------------------

  255 = Completamente OPACO (no transparente)
  128 = 50% transparente
  64  = 75% transparente
  0   = Completamente TRANSPARENTE (invisible)

--------------------------------------------------------------------------------
PARA COMPILAR Y PROBAR:
--------------------------------------------------------------------------------

$ make bonus
$ ./cub3D_bonus maps/example1.cub

Verás los cuadrados transparentes en el menú inicial.

--------------------------------------------------------------------------------
PARA DESACTIVAR LA DEMO:
--------------------------------------------------------------------------------

En src_bonus/ft_menu.c, línea ~143, comenta esta línea:

    // ft_draw_transparent_demo(game);

--------------------------------------------------------------------------------
USO EN OTROS LUGARES:
--------------------------------------------------------------------------------

Puedes usar ft_draw_transparent_image() en cualquier parte:

1. Para HUD en el juego:
   ft_draw_transparent_image(game->render, mi_textura, x, y);

2. Para sprites con transparencia:
   ft_draw_transparent_image(game->render, sprite, pos_x, pos_y);

3. Para el minimapa con fondo semi-transparente:
   ft_draw_transparent_image(game->render, game->minimap, 10, 10);

================================================================================
  🎮 ¡PRUÉBALO AHORA!
================================================================================

Compila y ejecuta el juego. Los cuadrados transparentes deberían aparecer
automáticamente en el menú, demostrando que la funcionalidad funciona.
