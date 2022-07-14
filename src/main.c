#include <dirent.h>
#include <errno.h>
#include <glob.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <cairo.h>


#define WIDTH   256
#define HEIGHT  256

#define NCOLS   8
#define NROWS   8

const char *msg = "Hello, world!";

int draw_image(int argc, char **argv);
void draw_chessboard(void);

int main(int argc, char **argv) {
  return draw_image(argc, argv);
  /* return draw_chessboard(); */
}

// Test draw from file
int draw_image(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "[ERROR] Please give a folder with tile images!\n");
    return 1;
  }

  char *dirname = argv[1];
  glob_t *globbuf = malloc(sizeof(glob_t));
  char *expr = "/*.png";
  int r;
  char *buff = (char *)malloc(sizeof(char)*(strlen(expr) + strlen(expr) + 1));

  memcpy(buff, dirname, strlen(dirname));
  memcpy(buff + sizeof(char)*strlen(dirname), expr, strlen(expr));

  r = glob(buff, GLOB_ERR | GLOB_MARK, NULL, globbuf);

  if (r == GLOB_ABORTED) {
    fprintf(stderr, "[ERROR] Some error occurred!\n");
    return 1;

  } else if (r == GLOB_NOMATCH) {
    fprintf(stderr, "[ERROR] No .png files on the given directory!\n");
    return 1;
  }

  // Find next pow 2 of matches
  // Sauce: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
  uint32_t size = globbuf->gl_pathc;
  size--;
  size |= size >> 1;
  size |= size >> 2;
  size |= size >> 4;
  size |= size >> 8;
  size |= size >> 16;
  size++;
  size = (uint32_t)ceilf(sqrtf(size));

  // Get width and height of the tiles
  int w, h;
  cairo_surface_t *tile = cairo_image_surface_create_from_png(globbuf->gl_pathv[0]);
  w = cairo_image_surface_get_width(tile);
  h = cairo_image_surface_get_height(tile);
  printf("Tile is %dx%d\n", w, h);

  cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, size*w, size*h);
  cairo_t *cr = cairo_create(surface);

  uint32_t row = 0;
  uint32_t col = 0;
  for (uint32_t i = 0; i < globbuf->gl_pathc; i++) {
    col = i % size;
    row = (i - col) / size;

    tile = cairo_image_surface_create_from_png(globbuf->gl_pathv[i]);

    cairo_set_source_surface(cr, tile, col*w, row*h);
    cairo_paint(cr);
  }

  // Save tile
  char savefile[128];
  sprintf(savefile, "%s-tile.png", dirname);
  printf("Saving as: %s-tile.png", dirname);
  cairo_surface_write_to_png(surface, savefile);

  // Cleanup
  cairo_destroy(cr);
  cairo_surface_destroy(surface);

  free(buff);
  free(globbuf);

  return 0;
}

// Test draw
void draw_chessboard(void) {
  // Create surface
  cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, WIDTH, HEIGHT);
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
      cairo_rectangle(cr, w*j, h*i, w, h);

      if ((i+j) % 2 == 0) {
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

  cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(cr, 32.0);
  cairo_set_source_rgb(cr, 0.2, 0.7, 0.5);
  cairo_text_extents(cr, msg, extents);
  x = WIDTH / 2 - (extents->width/2 + extents->x_bearing);
  y = HEIGHT / 2 - (extents->height/2 + extents->y_bearing);
  cairo_move_to(cr, x, y);
  cairo_show_text(cr, msg);

  // Cleanup
  cairo_destroy(cr);
  cairo_surface_write_to_png(surface, "hello.png");
  cairo_surface_destroy(surface);
  
  free(extents);
}
