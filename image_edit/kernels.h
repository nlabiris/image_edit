/*
Basic image processing software
<https://github.com/nlabiris/image_edit>

Copyright (C) 2015  Nikos Labiris

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef KERNELS_
#define KERNELS_

const float sobel_3x3_X[3][3] = {
    {-1,0,1},
    {-2,0,2},
    {-1,0,1}
};

const float sobel_3x3_Y[3][3] = {
    {1,2,1},
    {0,0,0},
    {-1,-2,-1}
};

const float sobel_5x5_X[5][5] = {
    { -1, -2, 0, 2, 1 },
    { -4, -10, 0, 10, 4 },
    { -7, -17, 0, 17, 7 },
    { -4, -10, 0, 10, 4 },
    { -1, -2, 0, 2, 1 }
};

const float sobel_5x5_Y[5][5] = {
    { 1, 4, 7, 4, 1 },
    { 2, 10, 17, 10, 2 },
    { 0, 0, 0, 0, 0 },
    { -2, -10, -17, -10, -2 },
    { -1, -4, -7, -4, -1 }
};

const float sobel_7x7_X[7][7] = {
    { -1, -3, -3, 0, 3, 3, 1 },
    { -4, -11, -13, 0, 13, 11, 4 },
    { -9, -26, -30, 0, 30, 26, 9 },
    { -13, -34, -40, 0, 40, 34, 13 },
    { -9, -26, -30, 0, 30, 26, 9 },
    { -4, -11, -13, 0, 13, 11, 4 },
    { -1, -3, -3, 0, 3, 3, 1 }
};

const float sobel_7x7_Y[7][7] = {
    { 1, 4, 9, 13, 9, 4, 1 },
    { 3, 11, 26, 34, 26, 11, 3 },
    { 3, 13, 30, 40, 30, 13, 3 },
    { 0, 0, 0, 0, 0, 0, 0 },
    { -3, -13, -30, -40, -30, -13, -3 },
    { -3, -11, -26, -34, -26, -11, -3 },
    { -1, -4, -9, -13, -9, -4, -1 }
};

const float gaussian_3x3[3][3] = {
    { 1, 2, 1 },
    { 2, 4, 2 },
    { 1, 2, 1 }
};

const float gaussian_5x5[5][5] = {
    { 2, 4, 5, 4, 2 },
    { 4, 9, 12, 9, 4 },
    { 5, 12, 15, 12, 5 },
    { 4, 9, 12, 9, 4 },
    { 2, 4, 5, 4, 2 }
};

const float gaussian_7x7[7][7] = {
    { 1, 1, 2, 2, 2, 1, 1 },
    { 1, 2, 2, 4, 2, 2, 1 },
    { 2, 2, 4, 8, 4, 2, 2 },
    { 2, 4, 8, 16, 8, 4, 2 },
    { 2, 2, 4, 8, 4, 2, 2 },
    { 1, 2, 2, 4, 2, 2, 1 },
    { 1, 1, 2, 2, 2, 1, 1 }
};

const float mean_3x3[3][3] = {
    { 1, 1, 1 },
    { 1, 1, 1 },
    { 1, 1, 1 }
};

const float mean_5x5[5][5] = {
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 }
};

const float mean_7x7[7][7] = {
    { 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1 }
};

const float lowpass_3x3[3][3] = {
    { 1, 2, 1 },
    { 2, 4, 2 },
    { 1, 2, 1 }
};

const float lowpass_5x5[5][5] = {
    { 1, 1, 1, 1, 1 },
    { 1, 4, 4, 4, 1 },
    { 1, 4, 12, 4, 1 },
    { 1, 4, 4, 4, 1 },
    { 1, 1, 1, 1, 1 }
};

const float sharpen_3x3[3][3] = {
    { -1, -1, -1, },
    { -1, 9, -1 },
    { -1, -1, -1 }
};

const float sharpen_5x5[5][5] = {
    { -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1 },
    { -1, -1, 25, -1, -1 },
    { -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1 }
};

const float sharpen_7x7[7][7] = {
    { -1, -1, -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1, -1, -1 },
    { -1, -1, -1, 49, -1, -1, -1 },
    { -1, -1, -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1, -1, -1 }
};

#endif
