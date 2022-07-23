#include "wfc/samples.h"

#include "utils/numutils.h"
#include "utils/printutils.h"
#include "utils/stringutils.h"

#include <cairo.h>

#include <glob.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int draw_tiles(int argc, char **argv) {
  if (argc < 2) {
    errmsg("Please give a folder with tile images!", EXIT_FAILURE);
  }

  char *dirname = argv[1];
  char *buff;
  int r;

  r = strconcat(dirname, "/*.png", &buff);
  if (r == STRINGUTILS_NULLINPUT) {
    errmsg("strconcat() was given a NULL input", EXIT_FAILURE);

  } else if (r == STRINGUTILS_NOSPACE) {
    errmsg("strconcat() there was a problem allocating memory", EXIT_FAILURE);
  }

  glob_t *globbuf = malloc(sizeof(glob_t));
  r = glob(buff, GLOB_ERR | GLOB_MARK, NULL, globbuf);

  if (r == GLOB_ABORTED) {
    errmsg("Some error occurred while globing the tile directory!",
           EXIT_FAILURE);

  } else if (r == GLOB_NOMATCH) {
    errmsg("No .png files on the given directory!", EXIT_FAILURE);
  }

  uint32_t size = next_pow2(globbuf->gl_pathc);
  size = (uint32_t)ceilf(sqrtf((float)size));

  // Get width and height of the tiles
  int w, h;
  cairo_surface_t *tile =
      cairo_image_surface_create_from_png(globbuf->gl_pathv[0]);
  w = cairo_image_surface_get_width(tile);
  h = cairo_image_surface_get_height(tile);
  printf("Tile is %dx%d pixels\n", w, h);

  cairo_surface_t *surface =
      cairo_image_surface_create(CAIRO_FORMAT_ARGB32, size * w, size * h);
  cairo_t *cr = cairo_create(surface);

  uint32_t row = 0;
  uint32_t col = 0;
  for (uint32_t i = 0; i < globbuf->gl_pathc; i++) {
    col = i % size;
    row = (i - col) / size;

    tile = cairo_image_surface_create_from_png(globbuf->gl_pathv[i]);

    cairo_set_source_surface(cr, tile, col * w, row * h);
    cairo_paint(cr);
  }

  // Save tile
  char *lhs, *rhs;
  r = strsplit(dirname, '/', STRSPLIT_LAST, &lhs, &rhs);
  if (r == STRINGUTILS_NOMATCH) {
    errmsg("strsplit() the input string does not contain the splitting char",
           EXIT_FAILURE);

  } else if (r == STRINGUTILS_NULLINPUT) {
    errmsg("strsplit() was given a NULL input", EXIT_FAILURE);

  } else if (r == STRINGUTILS_NOSPACE) {
    errmsg("strsplit() there was a problem allocating memory", EXIT_FAILURE);
  }

  char *savefile;
  r = strconcat(rhs, "-tile.png", &savefile);
  if (r == STRINGUTILS_NULLINPUT) {
    errmsg("strconcat() was given a NULL input", EXIT_FAILURE);

  } else if (r == STRINGUTILS_NOSPACE) {
    errmsg("strconcat() there was a problem allocating memory", EXIT_FAILURE);
  }

  printf("Saving as: %s\n", savefile);
  cairo_surface_write_to_png(surface, savefile);

  // Cleanup
  cairo_destroy(cr);
  cairo_surface_destroy(surface);

  free(lhs);
  free(rhs);
  free(buff);
  free(globbuf);

  return EXIT_SUCCESS;
}

void draw_chessboard(void) {
  const int WIDTH = 256;
  const int HEIGHT = 256;
  const int NCOLS = 8;
  const int NROWS = 8;

  const char *MSG = "Hello, world!";

  // Create surface
  cairo_surface_t *surface =
      cairo_image_surface_create(CAIRO_FORMAT_ARGB32, WIDTH, HEIGHT);
  cairo_t *cr = cairo_create(surface);

  // Set background to black
  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_paint(cr);

  // Draw some kind of grid
  uint32_t w, h;
  w = WIDTH / NCOLS;
  h = HEIGHT / NROWS;
  for (uint32_t i = 0; i < NROWS; i++) {
    for (uint32_t j = 0; j < NCOLS; j++) {
      cairo_rectangle(cr, w * j, h * i, w, h);

      if ((i + j) % 2 == 0) {
        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
      } else {
        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
      }

      cairo_fill(cr);
    }
  }

  // Draw text in the middle
  cairo_text_extents_t *extents = malloc(sizeof(cairo_text_extents_t));
  double x, y;

  cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                         CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(cr, 32.0);
  cairo_set_source_rgb(cr, 0.2, 0.7, 0.5);
  cairo_text_extents(cr, MSG, extents);
  x = WIDTH / 2 - (extents->width / 2 + extents->x_bearing);
  y = HEIGHT / 2 - (extents->height / 2 + extents->y_bearing);
  cairo_move_to(cr, x, y);
  cairo_show_text(cr, MSG);

  // Cleanup
  cairo_destroy(cr);
  cairo_surface_write_to_png(surface, "hello.png");
  cairo_surface_destroy(surface);

  free(extents);
}
