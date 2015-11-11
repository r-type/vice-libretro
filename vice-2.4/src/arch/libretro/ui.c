/*
 * ui.c - PSP user interface.
 *
 * Written by
 *  Akop Karapetyan <dev@psp.akop.org>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#include "vice.h"
#include "machine.h"
#include <stdio.h>
#include <string.h>

/* Initialization  */
int ui_resources_init(void)
{

    if (machine_class != VICE_MACHINE_VSID) {
        return uistatusbar_init_resources();
    }
    return 0;
}

void ui_resources_shutdown(void)
{

}

int ui_init(void)
{
    return 0;
}

void ui_shutdown(void)
{
}

void ui_check_mouse_cursor(void)
{
    /* needed */
}

void ui_error(const char *format, ...)
{

   	char text[512];	   	
   	va_list	ap;	

   	if (format == NULL)return;		
		
   	va_start(ap,format );		
      		vsprintf(text, format, ap);	
   	va_end(ap);	
    fprintf(stderr, "ui_error: %s\n", text);
}

/* Update all the menus according to the current settings.  */

void ui_update_menus(void)
{
}

int ui_extend_image_dialog()
{
  return 0;
}

void ui_dispatch_events()
{
}

int ui_cmdline_options_init(void)
{
  return cmdline_register_options(cmdline_options);
}

int ui_init_finish()
{
  return 0;
}

int ui_init_finalize()
{
  resources_set_int( "SDLStatusbar", 1);
  return 0;
}

char* ui_get_file(const char *format,...)
{
    return NULL;
}



