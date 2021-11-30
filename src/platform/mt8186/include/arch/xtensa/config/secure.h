
/* Secure Mode defines. */

/* Customer ID=16990; Build=0x904d8; Copyright (c) 2020 Cadence Design Systems, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef XTENSA_SECURE_H
#define XTENSA_SECURE_H


/* SRAM */
#define XCHAL_HAVE_SECURE_SRAM	0

/* INSTRAM0 */
#define XCHAL_HAVE_SECURE_INSTRAM0	0

/* INSTRAM1 */
#define XCHAL_HAVE_SECURE_INSTRAM1	0

/* DATARAM0 */
#define XCHAL_HAVE_SECURE_DATARAM0	0

/* Array of all secure regions' start/size */
#define XCHAL_SECURE_MEM_LIST \
{ \
}

#endif /* XTENSA_SECURE_H */

