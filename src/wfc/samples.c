#include "wfc/samples.h"

#include "argparse/argparse.h"
#include "utils/constutils.h"
#include "utils/numutils.h"
#include "utils/printutils.h"
#include "utils/stringutils.h"

#include <cairo.h>

#include <glob.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static char *progname;

static int usage(int v) {
  if (v < 2) {
    printf("Usage: %s -u <utility> [utility-args ...]\n"
           "Utilities:\n"
           "    0 : draw_chessboard()\n"
           "    1 : draw_tiles()\n"
           "    2 : draw_random_tiles()\n",
           progname);

  } else {
    printf("Usage: %s -u <utility> [utility-args ...]\n"
           "Utilities:\n"
           "    0 : draw_chessboard()\n"
           "    1 : draw_tiles()\n"
           "        -d <directory>\n"
           "    2 : draw_random_tiles()\n"
           "        -d <directory> [-r <rows>] [-c <columns>]\n",
           progname);
  }

  return EXIT_FAILURE;
}

int samples_main(int argc, char **argv) {
  AParse ap;
  argparse_init(&ap, argc, argv, "hu:d:c:r:");
  progname = argv[0];

  // Parse general args
  int h = 0;
  int u = -1;
  int o;
  const char *d, *c, *r;
  while ((o = argparse_next(&ap)) != -1) {
    switch (o) {
    case 'h': h++; break;
    case 'u': u = atoi(ap.arg); break;
    case 'd': d = ap.arg; break;
    case 'c': c = ap.arg; break;
    case 'r': r = ap.arg; break;
    default: return usage(0);
    }
  }

  if (ap.err) {
    return usage(0);
  }

  if (h > 0) {
    return usage(h);
  }

  // Select utlity
  // FIXME: find a nicer way to parse the arguments for each utility.
  switch (u) {
  case 0: draw_chessboard(); break;
  case 1: draw_tiles(d); break;
  case 2: draw_random_tiles(d, atoi(c), atoi(r)); break;
  default: usage(0); break;
  }

  return EXIT_SUCCESS;
}

int draw_chessboard(void) {
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

  // Save image
  const char *savefile = "draw-chessboard.png";
  printf("Saving as: %s\n", savefile);
  cairo_surface_write_to_png(surface, savefile);

  // Cleanup
  cairo_destroy(cr);
  cairo_surface_destroy(surface);

  free(extents);

  return EXIT_SUCCESS;
}

int draw_tiles(const char *dirname) {
  char *buff;
  int r;

  r = strconcat(dirname, "/*.png", &buff);
  if (r == STRINGUTILS_NULLINPUT) {
    errmsg(EXIT_FAILURE, "strconcat() was given a NULL input");

  } else if (r == STRINGUTILS_NOSPACE) {
    errmsg(EXIT_FAILURE, "strconcat() there was a problem allocating memory");
  }

  glob_t *globbuf = malloc(sizeof(glob_t));
  r = glob(buff, GLOB_ERR | GLOB_MARK, NULL, globbuf);

  if (r == GLOB_ABORTED) {
    errmsg(EXIT_FAILURE,
           "Some error occurred while globing the tile directory!");

  } else if (r == GLOB_NOMATCH) {
    errmsg(EXIT_FAILURE, "No .png files on the given directory!");
  }

  uint32_t size = next_pow2(globbuf->gl_pathc);
  size = (uint32_t)ceilf(sqrtf((float)size));

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
    if (cairo_image_surface_get_width(tile) != w ||
        cairo_image_surface_get_height(tile) != h) {
      errmsg(EXIT_FAILURE, "Tile \"%s\" differs in size", globbuf->gl_pathv[i]);
    }

    cairo_set_source_surface(cr, tile, col * w, row * h);
    cairo_paint(cr);
    cairo_surface_destroy(tile);
  }

  // Save tile name
  char *lhs, *rhs;
  r = strsplit(dirname, '/', STRSPLIT_LAST, &lhs, &rhs);
  if (r == STRINGUTILS_NOMATCH) {
    errmsg(EXIT_FAILURE,
           "strsplit() the input string does not contain the splitting char");

  } else if (r == STRINGUTILS_NULLINPUT) {
    errmsg(EXIT_FAILURE, "strsplit() was given a NULL input");

  } else if (r == STRINGUTILS_NOSPACE) {
    errmsg(EXIT_FAILURE, "strsplit() there was a problem allocating memory");
  }

  // FIXME: make strconcat() get variadic args to concat
  char *savefile;
  r = strconcat(rhs, ".png", &savefile);
  r = strconcat("draw-tiles-", savefile, &savefile);
  if (r == STRINGUTILS_NULLINPUT) {
    errmsg(EXIT_FAILURE, "strconcat() was given a NULL input");

  } else if (r == STRINGUTILS_NOSPACE) {
    errmsg(EXIT_FAILURE, "strconcat() there was a problem allocating memory");
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

int draw_random_tiles(const char *dirname, int cols, int rows) {
  // Make sure COLS and ROWS are positive int
  cols = cols < 1 ? 16 : cols;
  rows = rows < 1 ? 16 : rows;

  char *buff;
  int r;

  r = strconcat(dirname, "/*.png", &buff);
  if (r == STRINGUTILS_NULLINPUT) {
    errmsg(EXIT_FAILURE, "strconcat() was given a NULL input");

  } else if (r == STRINGUTILS_NOSPACE) {
    errmsg(EXIT_FAILURE, "strconcat() there was a problem allocating memory");
  }

  glob_t *globbuf = malloc(sizeof(glob_t));
  r = glob(buff, GLOB_ERR | GLOB_MARK, NULL, globbuf);

  if (r == GLOB_ABORTED) {
    errmsg(EXIT_FAILURE,
           "Some error occurred while globing the tile directory!");

  } else if (r == GLOB_NOMATCH) {
    errmsg(EXIT_FAILURE, "No .png files on the given directory!");
  }

  int w, h;
  cairo_surface_t *tile =
      cairo_image_surface_create_from_png(globbuf->gl_pathv[0]);
  w = cairo_image_surface_get_width(tile);
  h = cairo_image_surface_get_height(tile);
  printf("Tile is %dx%d pixels\n", w, h);

  cairo_surface_t *surface =
      cairo_image_surface_create(CAIRO_FORMAT_ARGB32, cols * w, rows * h);
  cairo_t *cr = cairo_create(surface);

  // Check that all the images have the same size
  for (uint32_t i = 0; i < globbuf->gl_pathc; i++) {
    tile = cairo_image_surface_create_from_png(globbuf->gl_pathv[i]);
    if (cairo_image_surface_get_width(tile) != w ||
        cairo_image_surface_get_height(tile) != h) {
      errmsg(EXIT_FAILURE, "Tile \"%s\" differs in size", globbuf->gl_pathv[i]);
    }

    if (cairo_image_surface_get_width(tile) !=
        cairo_image_surface_get_height(tile)) {
      errmsg(EXIT_FAILURE, "Tile \"%s\" is not square", globbuf->gl_pathv[i]);
    }

    cairo_surface_destroy(tile);
  }

  // Generate random tileboard of tiles from folder
  uint32_t col, row;
  uint32_t idx;
  uint8_t quadrant;
  srand(time(NULL));
  for (uint32_t i = 0; i < cols * rows; i++) {
    col = i % cols;
    row = (i - col) / cols;

    idx = rand() % globbuf->gl_pathc;
    tile = cairo_image_surface_create_from_png(globbuf->gl_pathv[idx]);

    // 1.- Go to top left of tile that we have to paint
    cairo_translate(cr, w * col, h * row);

    // 2.- Rotate a random amount of pi/2, respect to the center
    quadrant = rand() % 4;
    cairo_translate(cr, w / 2, h / 2);
    cairo_rotate(cr, quadrant * M_PI / 2);

    // 3.- Return to the top left of the tile
    cairo_translate(cr, -w / 2, -h / 2);

    // 4.- Paint tile
    cairo_set_source_surface(cr, tile, 0, 0);
    cairo_paint(cr);

    // 5.- Cleanup
    cairo_identity_matrix(cr);
    cairo_surface_destroy(tile);
  }

  // Save tile name
  char *lhs, *rhs;
  r = strsplit(dirname, '/', STRSPLIT_LAST, &lhs, &rhs);
  if (r == STRINGUTILS_NOMATCH) {
    errmsg(EXIT_FAILURE,
           "strsplit() the input string does not contain the splitting char");

  } else if (r == STRINGUTILS_NULLINPUT) {
    errmsg(EXIT_FAILURE, "strsplit() was given a NULL input");

  } else if (r == STRINGUTILS_NOSPACE) {
    errmsg(EXIT_FAILURE, "strsplit() there was a problem allocating memory");
  }

  // FIXME: make strconcat() get variadic args to concat
  char *savefile;
  r = strconcat(rhs, ".png", &savefile);
  r = strconcat("draw-random-tiles-", savefile, &savefile);
  if (r == STRINGUTILS_NULLINPUT) {
    errmsg(EXIT_FAILURE, "strconcat() was given a NULL input");

  } else if (r == STRINGUTILS_NOSPACE) {
    errmsg(EXIT_FAILURE, "strconcat() there was a problem allocating memory");
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
