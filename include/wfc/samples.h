/**
 * @file samples.h
 * @brief This file contains some mini utilities using cairo
 *
 */

#ifndef WFC_SAMPLES_H
#define WFC_SAMPLES_H

/**
 * @brief Main wrapper for all the sample utilites
 *
 * @param argc argc argument from main()
 * @param argv argv argument from main()
 * @return int exit code
 */
int samples_main(int argc, char **argv);

/**
 * @brief Draws a chessboard with "Hello, world!" written on the center.
 *
 * @return int exit code
 */
int draw_chessboard(void);

/**
 * @brief Gets a folder full of png images and creates a square tile of all the
 * images. The size of all the tiles must be the same.
 *
 * @param dirname folder of the png images
 * @return int exit code
 */
int draw_tiles(const char *dirname);

/**
 * @brief Gets a folder full of png images and creates a tileboard of random
 * tiles.
 *
 * @param dirname folder of the png images
 * @param cols number of columns
 * @param rows number of rows
 * @return int exit code
 */
int draw_random_tiles(const char *dirname, int cols, int rows);

#endif // WFC_SAMPLES_H
