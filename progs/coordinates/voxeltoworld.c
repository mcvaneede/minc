/* ----------------------------- MNI Header -----------------------------------
@NAME       : voxeltoworld
@INPUT      : argc, argv - command line arguments
@OUTPUT     : (none)
@RETURNS    : status
@DESCRIPTION: Program to convert voxel coordinates to world coordinates
@METHOD     : 
@GLOBALS    : 
@CALLS      : 
@CREATED    : June 13, 1994 (Peter Neelin)
@MODIFIED   : $Log: voxeltoworld.c,v $
@MODIFIED   : Revision 1.1  1994-06-13 10:21:47  neelin
@MODIFIED   : Initial revision
@MODIFIED   :
@COPYRIGHT  :
              Copyright 1993 Peter Neelin, McConnell Brain Imaging Centre, 
              Montreal Neurological Institute, McGill University.
              Permission to use, copy, modify, and distribute this
              software and its documentation for any purpose and without
              fee is hereby granted, provided that the above copyright
              notice appear in all copies.  The author and McGill University
              make no representations about the suitability of this
              software for any purpose.  It is provided "as is" without
              express or implied warranty.
---------------------------------------------------------------------------- */

#ifndef lint
static char rcsid[]="$Header: /private-cvsroot/minc/progs/coordinates/voxeltoworld.c,v 1.1 1994-06-13 10:21:47 neelin Exp $";
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <volume_io.h>
#include <minc_def.h>

/* Constants */
#ifndef TRUE
#  define TRUE 1
#  define FALSE 0
#endif
#ifndef public
#  define public
#  define private static
#endif

/* Function to print to stderr */
void print_to_stderr(char *string)
{
   (void) fprintf(stderr, "%s", string);
   return;
}

/* Main program */

int main(int argc, char *argv[])
{
   Volume volume;
   volume_input_struct input_info;
   char *filename;
   double vx, vy, vz, wx, wy, wz;
   static char *dim_names[] =
      {ANY_SPATIAL_DIMENSION, ANY_SPATIAL_DIMENSION, ANY_SPATIAL_DIMENSION};

   /* Check arguments */
   if (argc != 5) {
      (void) fprintf(stderr, 
      "Usage: %s <image file> <voxel index 1 (slowest)> <index 2> <index 3>\n",
                     argv[0]);
      exit(EXIT_FAILURE);
   }
   filename = argv[1];
   vx = atof(argv[2]);
   vy = atof(argv[3]);
   vz = atof(argv[4]);

   /* Open the image file */
   set_print_function(print_to_stderr);
   if (start_volume_input(filename, 3, dim_names, NC_UNSPECIFIED, TRUE,
                          0.0, 0.0, TRUE, &volume, NULL, &input_info) != OK) {
      (void) fprintf(stderr, "Error opening file %s for input.\n",
                     filename);
      exit(EXIT_FAILURE);
   }

   /* Convert the voxel to world coordinates */
   convert_3D_voxel_to_world(volume, vx, vy, vz, &wx, &wy, &wz);

   /* Write out the result */
   (void) printf("%.20g %.20g %.20g\n", wx, wy, wz);

   exit(EXIT_SUCCESS);
}
